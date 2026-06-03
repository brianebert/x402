#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"

usage() {
  cat <<EOF
Usage: $0 [vhost_name]

If vhost_name is provided, the installer loads .<vhost_name>.env from the
project root unless X402_ENV_FILE is already set.
EOF
}

if [[ "${1:-}" == "-h" || "${1:-}" == "--help" ]]; then
  usage
  exit 0
fi

if [[ "$#" -gt 1 ]]; then
  usage >&2
  exit 1
fi

if [[ "$#" -eq 1 ]]; then
  vhost_name="$1"
  if [[ ! "$vhost_name" =~ ^[A-Za-z0-9_.-]+$ || "$vhost_name" == .* || "$vhost_name" == *..* ]]; then
    echo "vhost_name must contain only letters, numbers, dot, underscore, or dash, and must not start with dot or contain '..'." >&2
    exit 1
  fi
  X402_VHOST_ENV_FILE="$(cd "$SCRIPT_DIR/.." && pwd)/.${vhost_name}.env"
  export X402_VHOST_ENV_FILE
  if [[ ! -f "$X402_VHOST_ENV_FILE" ]]; then
    echo "Missing vhost env file: $X402_VHOST_ENV_FILE" >&2
    echo "Copy .vhost.env.example to .${vhost_name}.env and fill in the vhost values." >&2
    exit 1
  fi
fi

# shellcheck source=lib/host-install-common.sh
source "$SCRIPT_DIR/lib/host-install-common.sh"

init_x402_defaults
validate_vhost_config

normalize_proxy_target() {
  local target="$1"
  if [[ "$target" != */ ]]; then
    target="$target/"
  fi
  printf '%s\n' "$target"
}

emit_server_aliases() {
  local target="$1"
  local alias

  if [[ -n "$DOMAIN" && "$ENABLE_WWW_ALIAS" == "1" ]]; then
    printf '    ServerAlias www.%s\n' "$DOMAIN" >> "$target"
  fi
  for alias in $SERVER_ALIASES; do
    printf '    ServerAlias %s\n' "$alias" >> "$target"
  done
}

emit_vhost_snippet() {
  local target="$1"
  local snippet_file="$2"

  if [[ -n "$snippet_file" ]]; then
    cat "$snippet_file" >> "$target"
    printf '\n' >> "$target"
  fi
}

emit_dynamic_intent_config() {
  local target="$1"

  if [[ "$ENABLE_DYNAMIC_INTENTS" == "1" ]]; then
    cat >> "$target" <<EOF
    X402ChallengeEndpoint $CHALLENGE_ENDPOINT
    X402DynamicCheckoutEndpoint $DYNAMIC_CHECKOUT_ENDPOINT
    X402IntentSecretFile $INTENT_SECRET_PATH
EOF
    if [[ "$ENABLE_SPLIT" == "1" ]]; then
      cat >> "$target" <<EOF
    X402StellarLocalBackend inprocess
    X402StellarConfigDir $STELLAR_CONFIG_DIR
    X402StellarSourceAccount $STELLAR_SOURCE_ACCOUNT
    X402StellarRpcURL $STELLAR_RPC_URL
    X402StellarNetworkPassphrase "$STELLAR_NETWORK_PASSPHRASE"
EOF
    fi
  fi
}

install_dynamic_intent_secret() {
  if [[ "$ENABLE_DYNAMIC_INTENTS" != "1" ]]; then
    return 0
  fi

  sudo install -d -o root -g www-data -m 750 /etc/apache2/x402-secrets
  if [[ -n "$INTENT_SECRET" ]]; then
    printf '%s\n' "$INTENT_SECRET" | sudo tee "$INTENT_SECRET_PATH" >/dev/null
  elif [[ -n "$INTENT_SECRET_SOURCE_FILE" ]]; then
    sudo install -m 600 "$INTENT_SECRET_SOURCE_FILE" "$INTENT_SECRET_PATH"
  elif [[ ! -f "$INTENT_SECRET_PATH" ]]; then
    echo "Missing dynamic intent secret at $INTENT_SECRET_PATH" >&2
    exit 1
  fi
  sudo chown root:www-data "$INTENT_SECRET_PATH"
  sudo chmod 640 "$INTENT_SECRET_PATH"
}

disable_site() {
  echo "Disabling Apache site $SITE_NAME..."
  sudo a2dissite "${SITE_NAME}.conf" >/dev/null 2>&1 || true
  sudo a2dissite "${SITE_NAME}-ssl.conf" >/dev/null 2>&1 || true
  apache_reload_or_restart
  echo "Vhost disabled: $SITE_NAME"
}

delete_site() {
  disable_site
  echo "Deleting Apache site config..."
  sudo rm -f "$SITE_CONF" "$SITE_SSL_CONF"
  apache_reload_or_restart
  echo "Vhost config deleted: $SITE_NAME"
}

write_route_block() {
  local target="$1"
  local index="$2"
  local route amount desc mimetype credits_issued forward_to
  local -a route_stakeholders=()

  route="$(route_path "$index")"
  amount="$(route_amount "$index")"
  desc="$(route_description "$index")"
  mimetype="$(route_mimetype "$index")"
  credits_issued="$(route_credits_issued "$index")"
  forward_to="$(route_forward_to "$index")"

  cat >> "$target" <<EOF
    <Location "$route">
        X402 On
        X402Scheme exact
        X402Network $NETWORK
        X402Asset $ASSET
        X402Amount $amount
        X402Description "$desc"
        X402MimeType $mimetype
        X402Mechanism stellar
        X402SettlementMode facilitator
        X402FacilitatorURL $FACILITATOR_URL
        X402FacilitatorAPIKeyFile $FACILITATOR_KEY_PATH
EOF
  if [[ "$ENABLE_SPLIT" == "1" ]]; then
    cat >> "$target" <<EOF
        X402StellarLocalBackend inprocess
        X402StellarConfigDir $STELLAR_CONFIG_DIR
        X402StellarSourceAccount $STELLAR_SOURCE_ACCOUNT
        X402StellarRpcURL $STELLAR_RPC_URL
        X402StellarNetworkPassphrase "$STELLAR_NETWORK_PASSPHRASE"
EOF
  fi
  cat >> "$target" <<EOF
        X402TimeoutSeconds $TIMEOUT_SECONDS
        X402PaymentIdentifier required
EOF
  if [[ "$ENABLE_SPLIT" == "1" ]]; then
    publisher_stakeholders_for_route route_stakeholders "$route" "$index"
    emit_stakeholders "$target" "        " "${route_stakeholders[@]}"
  else
    cat >> "$target" <<EOF
        X402SplitMode single
        X402PayTo $PAY_TO
EOF
  fi
  cat >> "$target" <<EOF
        X402Prepay On
        X402PrepayMultiplierMax $PREPAY_MAX
        X402CreditScope $CREDIT_SCOPE
        X402CreditTTLSeconds $CREDIT_TTL_SECONDS
EOF
  if [[ -n "$credits_issued" ]]; then
    cat >> "$target" <<EOF
        X402CreditsIssued $credits_issued
        X402ForwardTo $forward_to
EOF
  fi
  cat >> "$target" <<EOF
    </Location>
EOF
}

prepare_document_roots() {
  local count i route target_dir content_file content_body

  echo "Preparing Apache document roots..."
  sudo install -d -m 755 "$DOCROOT"
  count="$(route_count)"
  for ((i = 1; i <= count; i++)); do
    route="$(route_path "$i")"
    target_dir="$(route_docroot_path "$route")"
    content_file="$(route_content_file "$i")"
    content_body="$(route_content_body "$i")"

    sudo install -d -m 755 "$target_dir"
    if [[ -n "$content_file" && -n "$content_body" ]]; then
      printf '%s\n' "$content_body" | sudo tee "$target_dir/$content_file" >/dev/null
    fi
  done
}

write_proxy_rules() {
  local target="$1"
  local proxy_target="$2"
  local forwarded_proto="$3"
  local forwarded_port="$4"
  local path

  cat >> "$target" <<EOF
    ProxyPreserveHost $(if [[ "$PROXY_PRESERVE_HOST" == "1" ]]; then printf 'On'; else printf 'Off'; fi)
    RequestHeader set X-Forwarded-Proto "$forwarded_proto"
    RequestHeader set X-Forwarded-Port "$forwarded_port"
EOF
  if [[ "$ENABLE_DYNAMIC_INTENTS" == "1" ]]; then
    cat >> "$target" <<EOF
    ProxyPass $CHALLENGE_ENDPOINT !
EOF
  fi
  for path in ${PROXY_EXCLUDE_PATHS//,/ }; do
    [[ -n "$path" ]] || continue
    cat >> "$target" <<EOF
    ProxyPass $path !
EOF
  done
  cat >> "$target" <<EOF
    ProxyPass / $proxy_target
    ProxyPassReverse / $proxy_target
EOF
  if [[ -n "$PROXY_ERROR_DOCUMENT" ]]; then
    cat >> "$target" <<EOF

    ProxyErrorOverride On 500 502 503 504
    ErrorDocument 500 $PROXY_ERROR_DOCUMENT
    ErrorDocument 502 $PROXY_ERROR_DOCUMENT
    ErrorDocument 503 $PROXY_ERROR_DOCUMENT
    ErrorDocument 504 $PROXY_ERROR_DOCUMENT
EOF
  fi
}

write_proxy_site_config() {
  local target="$1"
  local is_ssl="$2"
  local proxy_target

  proxy_target="$(normalize_proxy_target "$PROXY_TARGET")"

  cat > "$target" <<EOF
X402CreditDBPath $CREDIT_DB_PATH

EOF

  if [[ "$is_ssl" == "1" ]]; then
    cat >> "$target" <<EOF
<IfModule mod_ssl.c>
<VirtualHost *:443>
    ServerName $SERVER_NAME

EOF
    emit_server_aliases "$target"
    emit_vhost_snippet "$target" "$VHOST_SSL_SNIPPET_FILE"
    emit_dynamic_intent_config "$target"
    write_proxy_rules "$target" "$proxy_target" "https" "443"
    cat >> "$target" <<EOF

    SSLEngine on
    SSLCertificateFile $SSL_CERT_FILE
    SSLCertificateKeyFile $SSL_KEY_FILE
</VirtualHost>
</IfModule>
EOF
  else
    cat >> "$target" <<EOF
<VirtualHost *:80>
    ServerName $SERVER_NAME
EOF
    emit_server_aliases "$target"
    emit_vhost_snippet "$target" "$VHOST_HTTP_SNIPPET_FILE"
    if [[ "$ENABLE_SSL" == "1" && "$PROXY_HTTPS_ONLY" == "1" ]]; then
      cat >> "$target" <<EOF

    RewriteEngine On
    RewriteRule ^ https://$SERVER_NAME%{REQUEST_URI} [R=301,L]
</VirtualHost>
EOF
    else
      emit_dynamic_intent_config "$target"
      write_proxy_rules "$target" "$proxy_target" "http" "80"
      cat >> "$target" <<EOF
</VirtualHost>
EOF
    fi
  fi
}

write_site_config() {
  local target="$1"
  local is_ssl="$2"
  local count i

  cat > "$target" <<EOF
X402CreditDBPath $CREDIT_DB_PATH

EOF

  if [[ "$is_ssl" == "1" ]]; then
    cat >> "$target" <<EOF
<IfModule mod_ssl.c>
<VirtualHost *:443>
    ServerName $SERVER_NAME
    DocumentRoot $DOCROOT
    ErrorDocument 402 "protected content: payment required"
EOF
  else
    cat >> "$target" <<EOF
<VirtualHost *:80>
    ServerName $SERVER_NAME
    DocumentRoot $DOCROOT
    ErrorDocument 402 "protected content: payment required"
EOF
  fi

  if [[ "$ENABLE_SSL" != "1" || "$is_ssl" == "1" ]]; then
    emit_dynamic_intent_config "$target"
  fi

  if [[ "$is_ssl" == "1" ]]; then
    emit_vhost_snippet "$target" "$VHOST_SSL_SNIPPET_FILE"
  else
    emit_vhost_snippet "$target" "$VHOST_HTTP_SNIPPET_FILE"
  fi

  cat >> "$target" <<EOF

    <Directory $DOCROOT>
        Options Indexes FollowSymLinks
        AllowOverride None
        Require all granted
    </Directory>
EOF

  emit_server_aliases "$target"

  count="$(route_count)"
  for ((i = 1; i <= count; i++)); do
    write_route_block "$target" "$i"
  done

  if [[ "$is_ssl" == "1" ]]; then
    cat >> "$target" <<EOF
    SSLEngine on
    SSLCertificateFile $SSL_CERT_FILE
    SSLCertificateKeyFile $SSL_KEY_FILE
</VirtualHost>
</IfModule>
EOF
  elif [[ "$ENABLE_SSL" == "1" ]]; then
    cat >> "$target" <<EOF
    RewriteEngine On
    RewriteRule ^/(.*)$ https://$DOMAIN/\$1 [R=301,L]
</VirtualHost>
EOF
  else
    cat >> "$target" <<EOF
</VirtualHost>
EOF
  fi
}

case "$VHOST_ACTION" in
  disable)
    disable_site
    exit 0
    ;;
  delete)
    delete_site
    exit 0
    ;;
esac

if [[ "$VHOST_MODE" == "static" ]]; then
  prepare_document_roots
fi
install_dynamic_intent_secret

tmp_http="$(mktemp)"
tmp_ssl=""
if [[ "$VHOST_MODE" == "proxy" ]]; then
  write_proxy_site_config "$tmp_http" "0"
else
  write_site_config "$tmp_http" "0"
fi

if [[ "$ENABLE_SSL" == "1" ]]; then
  tmp_ssl="$(mktemp)"
  if [[ "$VHOST_MODE" == "proxy" ]]; then
    write_proxy_site_config "$tmp_ssl" "1"
  else
    write_site_config "$tmp_ssl" "1"
  fi
fi

echo "Installing Apache site config..."
sudo install -m 644 "$tmp_http" "$SITE_CONF"
rm -f "$tmp_http"

if [[ -n "$tmp_ssl" ]]; then
  sudo install -m 644 "$tmp_ssl" "$SITE_SSL_CONF"
  rm -f "$tmp_ssl"
fi

echo "Enabling Apache site..."
sudo a2enmod headers rewrite >/dev/null
sudo a2enmod x402 >/dev/null
if [[ "$VHOST_MODE" == "proxy" ]]; then
  sudo a2enmod proxy proxy_http >/dev/null
fi
sudo a2dissite 000-default.conf >/dev/null 2>&1 || true
if [[ "$ENABLE_SSL" == "1" ]]; then
  sudo a2enmod ssl >/dev/null
  sudo a2ensite "${SITE_NAME}.conf" >/dev/null
  sudo a2ensite "${SITE_NAME}-ssl.conf" >/dev/null
else
  sudo a2ensite "${SITE_NAME}.conf" >/dev/null
fi

apache_reload_or_restart

echo "Vhost install complete."
echo "Mode: $VHOST_MODE"
echo "Site config: $SITE_CONF"
if [[ "$ENABLE_SSL" == "1" ]]; then
  echo "TLS site config: $SITE_SSL_CONF"
fi
if [[ -n "$DOMAIN" ]]; then
  echo "HTTP host: http://$DOMAIN/"
else
  echo "HTTP host: http://$SERVER_NAME/"
fi
if [[ "$ENABLE_DYNAMIC_INTENTS" == "1" ]]; then
  echo "Dynamic challenge endpoint: $CHALLENGE_ENDPOINT"
  echo "Dynamic checkout endpoint: $DYNAMIC_CHECKOUT_ENDPOINT"
fi
if [[ "$VHOST_MODE" == "proxy" ]]; then
  echo "Proxy target: $(normalize_proxy_target "$PROXY_TARGET")"
fi
