#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
# shellcheck source=lib/host-install-common.sh
source "$SCRIPT_DIR/lib/host-install-common.sh"

init_x402_defaults
validate_vhost_config

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

    SSLEngine on
    SSLCertificateFile $SSL_CERT_FILE
    SSLCertificateKeyFile $SSL_KEY_FILE
EOF
  else
    cat >> "$target" <<EOF
<VirtualHost *:80>
    ServerName $SERVER_NAME
    DocumentRoot $DOCROOT
    ErrorDocument 402 "protected content: payment required"
EOF
  fi

  cat >> "$target" <<EOF

    <Directory $DOCROOT>
        Options Indexes FollowSymLinks
        AllowOverride None
        Require all granted
    </Directory>
EOF

  if [[ -n "$DOMAIN" ]]; then
    cat >> "$target" <<EOF
    ServerAlias www.$DOMAIN
EOF
  fi

  count="$(route_count)"
  for ((i = 1; i <= count; i++)); do
    write_route_block "$target" "$i"
  done

  if [[ "$is_ssl" == "1" ]]; then
    cat >> "$target" <<EOF
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

prepare_document_roots

tmp_http="$(mktemp)"
tmp_ssl=""
write_site_config "$tmp_http" "0"

if [[ "$ENABLE_SSL" == "1" ]]; then
  tmp_ssl="$(mktemp)"
  write_site_config "$tmp_ssl" "1"
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
echo "Site config: $SITE_CONF"
if [[ "$ENABLE_SSL" == "1" ]]; then
  echo "TLS site config: $SITE_SSL_CONF"
fi
if [[ -n "$DOMAIN" ]]; then
  echo "HTTP host: http://$DOMAIN/"
else
  echo "HTTP host: http://$SERVER_NAME/"
fi
