#!/usr/bin/env bash
set -euo pipefail

if [[ "$(uname -s)" != "Linux" ]]; then
  echo "This script is intended to run on a Linux Apache host." >&2
  exit 1
fi

if [[ ! -f /etc/debian_version ]]; then
  echo "This script currently supports Debian/Ubuntu Apache layouts only." >&2
  exit 1
fi

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
ENV_FILE="${X402_ENV_FILE:-$ROOT/.env}"

if [[ -f "$ENV_FILE" ]]; then
  set -a
  # shellcheck disable=SC1090
  source "$ENV_FILE"
  set +a
fi

require_env() {
  local name="$1"
  if [[ -z "${!name:-}" ]]; then
    echo "Missing required environment variable: $name" >&2
    exit 1
  fi
}

env_value() {
  local name="$1"
  printf '%s' "${!name:-}"
}

validate_bps() {
  local label="$1"
  local value="$2"

  if [[ ! "$value" =~ ^[0-9]+$ || "$value" -gt 10000 ]]; then
    echo "$label basis points must be an integer between 0 and 10000" >&2
    exit 1
  fi
}

add_stakeholder() {
  local array_name="$1"
  local label="$2"
  local name="$3"
  local bps="$4"
  local dest="$5"

  if [[ -z "$name" || -z "$bps" || -z "$dest" ]]; then
    echo "$label requires NAME, BPS, and DEST" >&2
    exit 1
  fi
  validate_bps "$label" "$bps"
  eval "$array_name+=(\"\$name|\$bps|\$dest\")"
}

collect_indexed_stakeholders() {
  local array_name="$1"
  local prefix="$2"
  local label="$3"
  local i name bps dest

  for ((i = 1; i <= MAX_STAKEHOLDERS; i++)); do
    name="$(env_value "${prefix}_${i}_NAME")"
    bps="$(env_value "${prefix}_${i}_BPS")"
    dest="$(env_value "${prefix}_${i}_DEST")"
    if [[ -n "$name" || -n "$bps" || -n "$dest" ]]; then
      add_stakeholder "$array_name" "$label $i" "$name" "$bps" "$dest"
    fi
  done
}

route_key() {
  local route="$1"

  route="${route#/}"
  route="${route//\//_}"
  route="${route//-/_}"
  route="${route^^}"
  printf '%s\n' "$route"
}

collect_route_stakeholders() {
  local array_name="$1"
  local key="$2"
  local i name bps dest

  eval "$array_name=()"
  for ((i = 1; i <= MAX_STAKEHOLDERS; i++)); do
    name="$(env_value "X402_ROUTE_${key}_STAKEHOLDER_${i}_NAME")"
    bps="$(env_value "X402_ROUTE_${key}_STAKEHOLDER_${i}_BPS")"
    dest="$(env_value "X402_ROUTE_${key}_STAKEHOLDER_${i}_DEST")"
    if [[ -n "$name" || -n "$bps" || -n "$dest" ]]; then
      add_stakeholder "$array_name" "route $key stakeholder $i" "$name" "$bps" "$dest"
    fi
  done
}

stakeholder_bps_sum() {
  local sum=0
  local entry bps

  for entry in "$@"; do
    IFS='|' read -r _ bps _ <<< "$entry"
    sum=$((sum + bps))
  done
  printf '%s\n' "$sum"
}

emit_stakeholders() {
  local target="$1"
  local indent="$2"
  shift 2
  local entry name bps dest

  for entry in "$@"; do
    IFS='|' read -r name bps dest <<< "$entry"
    printf '%sX402Stakeholder %s %s %s\n' "$indent" "$name" "$bps" "$dest" >> "$target"
  done
}

detect_host_ipv4() {
  local route_ip
  route_ip="$(ip -o route get 1.1.1.1 2>/dev/null | awk '{print $7; exit}')"
  if [[ -n "$route_ip" ]]; then
    printf '%s\n' "$route_ip"
    return 0
  fi

  local host_ip
  host_ip="$(hostname -I 2>/dev/null | awk '{print $1; exit}')"
  if [[ -n "$host_ip" ]]; then
    printf '%s\n' "$host_ip"
    return 0
  fi

  return 1
}

PROJECT_DIR="${X402_PROJECT_DIR:-$ROOT}"
SITE_NAME="${X402_SITE_NAME:-x402}"
DOMAIN="${X402_DOMAIN:-}"
SERVER_NAME="${X402_SERVER_NAME:-}"
DOCROOT="${X402_DOCROOT:-/var/www/$SITE_NAME}"

FACILITATOR_URL="${X402_FACILITATOR_URL:-https://channels.openzeppelin.com/x402/testnet}"
NETWORK="${X402_NETWORK:-stellar:testnet}"
ASSET="${X402_ASSET:-}"
PAY_TO="${X402_PAY_TO:-}"
AMOUNT="${X402_AMOUNT:-1000000}"
DESCRIPTION="${X402_DESCRIPTION:-Access to foo}"
MIMETYPE="${X402_MIMETYPE:-text/html}"
TIMEOUT_SECONDS="${X402_TIMEOUT_SECONDS:-30}"
PREPAY_MAX="${X402_PREPAY_MULTIPLIER_MAX:-100}"
CREDIT_TTL_SECONDS="${X402_CREDIT_TTL_SECONDS:-86400}"
CREDIT_SCOPE="${X402_CREDIT_SCOPE:-payer-route}"

ENABLE_SPLIT="${X402_ENABLE_SPLIT:-0}"
STELLAR_SOURCE_ACCOUNT="${X402_STELLAR_SOURCE_ACCOUNT:-}"
STELLAR_SOURCE_SECRET_KEY="${X402_STELLAR_SOURCE_SECRET_KEY:-}"
STELLAR_RPC_URL="${X402_STELLAR_RPC_URL:-https://soroban-testnet.stellar.org:443}"
STELLAR_NETWORK_PASSPHRASE="${X402_STELLAR_NETWORK_PASSPHRASE:-Test SDF Network ; September 2015}"
SPLITTER_CONTRACT="${X402_SPLITTER_CONTRACT:-}"
STAKEHOLDER_1_NAME="${X402_STAKEHOLDER_1_NAME:-publisher}"
STAKEHOLDER_1_BPS="${X402_STAKEHOLDER_1_BPS:-7000}"
STAKEHOLDER_1_DEST="${X402_STAKEHOLDER_1_DEST:-}"
STAKEHOLDER_2_NAME="${X402_STAKEHOLDER_2_NAME:-affiliate}"
STAKEHOLDER_2_BPS="${X402_STAKEHOLDER_2_BPS:-3000}"
STAKEHOLDER_2_DEST="${X402_STAKEHOLDER_2_DEST:-}"
OPERATOR_STAKEHOLDER_NAME="${X402_OPERATOR_STAKEHOLDER_NAME:-$STAKEHOLDER_1_NAME}"
OPERATOR_STAKEHOLDER_BPS="${X402_OPERATOR_STAKEHOLDER_BPS:-$STAKEHOLDER_1_BPS}"
OPERATOR_STAKEHOLDER_DEST="${X402_OPERATOR_STAKEHOLDER_DEST:-$STAKEHOLDER_1_DEST}"
PUBLISHER_STAKEHOLDER_NAME="${X402_PUBLISHER_STAKEHOLDER_NAME:-$STAKEHOLDER_2_NAME}"
PUBLISHER_STAKEHOLDER_BPS="${X402_PUBLISHER_STAKEHOLDER_BPS:-$STAKEHOLDER_2_BPS}"
PUBLISHER_STAKEHOLDER_DEST="${X402_PUBLISHER_STAKEHOLDER_DEST:-$STAKEHOLDER_2_DEST}"
MAX_STAKEHOLDERS="${X402_MAX_STAKEHOLDERS:-16}"

OPERATOR_STAKEHOLDERS=()
PUBLISHER_STAKEHOLDERS=()

ENABLE_SSL="${X402_ENABLE_SSL:-0}"
SSL_CERT_FILE="${X402_SSL_CERT_FILE:-}"
SSL_KEY_FILE="${X402_SSL_KEY_FILE:-}"

FACILITATOR_API_KEY_SOURCE_FILE="${X402_FACILITATOR_API_KEY_SOURCE_FILE:-}"
FACILITATOR_KEY_PATH="/etc/apache2/x402-secrets/facilitator.key"
STELLAR_CONFIG_DIR="/etc/apache2/x402-stellar"
CREDIT_DB_DIR="/var/lib/x402"
CREDIT_DB_PATH="$CREDIT_DB_DIR/credits.db"
SITE_CONF="/etc/apache2/sites-available/${SITE_NAME}.conf"
SITE_SSL_CONF="/etc/apache2/sites-available/${SITE_NAME}-ssl.conf"
SPLIT_CONF="/etc/apache2/conf-available/x402-splits.conf"
MODULE_LOAD_CONF="/etc/apache2/mods-available/x402.load"
MODULE_PATH="/usr/lib/apache2/modules/mod_x402.so"
STELLAR_IDENTITY_PATH=""

publisher_stakeholders_for_route() {
  local array_name="$1"
  local route="$2"
  local key

  key="$(route_key "$route")"
  collect_route_stakeholders "$array_name" "$key"
  eval "if [[ \${#$array_name[@]} -eq 0 ]]; then $array_name=(\"\${PUBLISHER_STAKEHOLDERS[@]}\"); fi"
}

collect_split_stakeholders() {
  collect_indexed_stakeholders OPERATOR_STAKEHOLDERS X402_OPERATOR_STAKEHOLDER "operator stakeholder"
  collect_indexed_stakeholders PUBLISHER_STAKEHOLDERS X402_PUBLISHER_STAKEHOLDER "publisher stakeholder"

  if [[ "${#OPERATOR_STAKEHOLDERS[@]}" -eq 0 && -n "$OPERATOR_STAKEHOLDER_DEST" ]]; then
    add_stakeholder OPERATOR_STAKEHOLDERS "operator stakeholder" \
      "$OPERATOR_STAKEHOLDER_NAME" "$OPERATOR_STAKEHOLDER_BPS" "$OPERATOR_STAKEHOLDER_DEST"
  fi
  if [[ "${#PUBLISHER_STAKEHOLDERS[@]}" -eq 0 && -n "$PUBLISHER_STAKEHOLDER_DEST" ]]; then
    add_stakeholder PUBLISHER_STAKEHOLDERS "publisher stakeholder" \
      "$PUBLISHER_STAKEHOLDER_NAME" "$PUBLISHER_STAKEHOLDER_BPS" "$PUBLISHER_STAKEHOLDER_DEST"
  fi
}

validate_route_split_bps() {
  local route="$1"
  local -a route_stakeholders=()
  local total

  publisher_stakeholders_for_route route_stakeholders "$route"
  if [[ "${#route_stakeholders[@]}" -eq 0 ]]; then
    echo "Split mode requires at least one publisher or route-specific stakeholder for $route" >&2
    exit 1
  fi
  if [[ $((${#OPERATOR_STAKEHOLDERS[@]} + ${#route_stakeholders[@]})) -gt "$MAX_STAKEHOLDERS" ]]; then
    echo "Too many combined stakeholders for $route" >&2
    exit 1
  fi
  total="$(stakeholder_bps_sum "${OPERATOR_STAKEHOLDERS[@]}" "${route_stakeholders[@]}")"
  if [[ "$total" -ne 10000 ]]; then
    echo "Combined stakeholder bps for $route must sum to 10000; got $total" >&2
    exit 1
  fi
}

validate_split_stakeholders() {
  local route

  collect_split_stakeholders
  if [[ "${#OPERATOR_STAKEHOLDERS[@]}" -eq 0 ]]; then
    echo "Split mode requires at least one operator stakeholder" >&2
    exit 1
  fi
  for route in "/app/foo" "/price" "/priceX2" "/priceX10" "/priceX100"; do
    validate_route_split_bps "$route"
  done
}

require_env X402_ASSET
if [[ "$ENABLE_SPLIT" != "1" ]]; then
  require_env X402_PAY_TO
fi

if [[ -z "$SERVER_NAME" ]]; then
  if [[ -n "$DOMAIN" ]]; then
    SERVER_NAME="$DOMAIN"
  else
    SERVER_NAME="$(detect_host_ipv4 || true)"
    if [[ -z "$SERVER_NAME" ]]; then
      echo "Set X402_SERVER_NAME explicitly; failed to auto-detect a host IPv4 address." >&2
      exit 1
    fi
  fi
fi

if [[ -z "${X402_FACILITATOR_API_KEY:-}" && -z "$FACILITATOR_API_KEY_SOURCE_FILE" ]]; then
  if [[ "$FACILITATOR_URL" == "https://channels.openzeppelin.com/x402/testnet" ]]; then
    X402_FACILITATOR_API_KEY="$(
      curl -fsS "https://channels.openzeppelin.com/testnet/gen" |
        python3 -c 'import json,sys; print(json.load(sys.stdin)["apiKey"])'
    )"
    if [[ -z "$X402_FACILITATOR_API_KEY" ]]; then
      echo "OpenZeppelin testnet key generator returned an empty apiKey." >&2
      exit 1
    fi
    echo "Fetched OpenZeppelin testnet facilitator key automatically." >&2
  else
    echo "Set X402_FACILITATOR_API_KEY or X402_FACILITATOR_API_KEY_SOURCE_FILE." >&2
    exit 1
  fi
fi

if [[ "$ENABLE_SPLIT" == "1" ]]; then
  require_env X402_STELLAR_SOURCE_ACCOUNT
  require_env X402_SPLITTER_CONTRACT
  validate_split_stakeholders
  STELLAR_IDENTITY_PATH="$STELLAR_CONFIG_DIR/identity/${STELLAR_SOURCE_ACCOUNT}.toml"
fi

if [[ "$ENABLE_SSL" == "1" ]]; then
  if [[ -z "$DOMAIN" ]]; then
    echo "Set X402_DOMAIN when X402_ENABLE_SSL=1." >&2
    exit 1
  fi
  require_env X402_SSL_CERT_FILE
  require_env X402_SSL_KEY_FILE
fi

echo "Installing required packages..."
sudo apt-get update
sudo apt-get install -y \
  apache2 \
  apache2-dev \
  build-essential \
  pkg-config \
  libcurl4-openssl-dev \
  libsodium-dev \
  libsqlite3-dev \
  libssl-dev \
  sqlite3

echo "Preparing Apache document roots..."
sudo install -d -m 755 "$DOCROOT"
sudo install -d -m 755 "$DOCROOT/app/foo"
sudo install -d -m 755 "$DOCROOT/price"
sudo install -d -m 755 "$DOCROOT/priceX2"
sudo install -d -m 755 "$DOCROOT/priceX10"
sudo install -d -m 755 "$DOCROOT/priceX100"
printf '%s\n' 'yoo hoo' | sudo tee "$DOCROOT/app/foo/index.html" >/dev/null
printf '%s\n' '<html><body>x402 purchase route</body></html>' | sudo tee "$DOCROOT/price/index.html" >/dev/null
printf '%s\n' '<html><body>x402 purchase route</body></html>' | sudo tee "$DOCROOT/priceX2/index.html" >/dev/null
printf '%s\n' '<html><body>x402 purchase route</body></html>' | sudo tee "$DOCROOT/priceX10/index.html" >/dev/null
printf '%s\n' '<html><body>x402 purchase route</body></html>' | sudo tee "$DOCROOT/priceX100/index.html" >/dev/null

echo "Building module from $PROJECT_DIR ..."
cd "$PROJECT_DIR"
make

cc -fPIC -I. -I.. -I/usr/include/apache2 -I/usr/include/apr-1.0 \
  -Wall -Wextra -Werror -Wno-error=cpp -Wno-missing-field-initializers -std=c11 \
  -c core/x402_core.c -o core/x402_core.apache.o

g++ -fPIC -I. -I.. -Iproviders/stellar -Iproviders/stellar/schemas -Ithird_party \
  -Wall -Wextra -Werror -Wno-unused-parameter -std=c++17 \
  $(pkg-config --cflags openssl libsodium 2>/dev/null) \
  -c providers/stellar/stellar_provider.cpp -o providers/stellar/stellar_provider.apache.o

cc -fPIC -I. -I.. -I/usr/include/apache2 -I/usr/include/apr-1.0 \
  -Wall -Wextra -Werror -Wno-error=cpp -Wno-missing-field-initializers -std=c11 \
  -c apache/mod_x402.c -o apache/mod_x402.apache.o

mkdir -p apache/.libs
g++ -shared -o apache/.libs/mod_x402.so \
  apache/mod_x402.apache.o core/x402_core.apache.o providers/stellar/stellar_provider.apache.o \
  -lcurl $(pkg-config --libs openssl libsodium 2>/dev/null) -lsqlite3

echo "Installing Apache module..."
sudo install -m 644 apache/.libs/mod_x402.so "$MODULE_PATH"
printf 'LoadModule x402_module %s\n' "$MODULE_PATH" | sudo tee "$MODULE_LOAD_CONF" >/dev/null

echo "Creating x402 local state..."
sudo install -d -m 700 /etc/apache2/x402-secrets
sudo install -d -m 750 "$STELLAR_CONFIG_DIR"
sudo chown root:www-data "$STELLAR_CONFIG_DIR"
sudo install -d -m 750 "$STELLAR_CONFIG_DIR/identity"
sudo chown root:www-data "$STELLAR_CONFIG_DIR/identity"
sudo install -d -m 755 "$CREDIT_DB_DIR"
sudo chown www-data:www-data "$CREDIT_DB_DIR"
sudo touch "$CREDIT_DB_PATH"
sudo chown www-data:www-data "$CREDIT_DB_PATH"
sudo chmod 664 "$CREDIT_DB_PATH"

if [[ "$ENABLE_SPLIT" == "1" && ! -f "$STELLAR_IDENTITY_PATH" ]]; then
  if [[ -z "$STELLAR_SOURCE_SECRET_KEY" ]]; then
    echo "Missing split signer identity: install $STELLAR_IDENTITY_PATH or pass X402_STELLAR_SOURCE_SECRET_KEY when invoking the script." >&2
    exit 1
  fi
  printf 'secret_key = "%s"\n' "$STELLAR_SOURCE_SECRET_KEY" | sudo tee "$STELLAR_IDENTITY_PATH" >/dev/null
  sudo chown root:www-data "$STELLAR_IDENTITY_PATH"
  sudo chmod 640 "$STELLAR_IDENTITY_PATH"
fi

if [[ -n "${X402_FACILITATOR_API_KEY:-}" ]]; then
  printf '%s\n' "$X402_FACILITATOR_API_KEY" | sudo tee "$FACILITATOR_KEY_PATH" >/dev/null
else
  sudo install -m 600 "$FACILITATOR_API_KEY_SOURCE_FILE" "$FACILITATOR_KEY_PATH"
fi
sudo chmod 600 "$FACILITATOR_KEY_PATH"

TMP_HTTP="$(mktemp)"
TMP_SSL=""
TMP_SPLIT=""

if [[ "$ENABLE_SPLIT" == "1" ]]; then
  TMP_SPLIT="$(mktemp)"
  cat > "$TMP_SPLIT" <<EOF
X402SplitMode multi
X402SplitterContract $SPLITTER_CONTRACT
EOF
  emit_stakeholders "$TMP_SPLIT" "" "${OPERATOR_STAKEHOLDERS[@]}"
fi

write_route_block() {
  local target="$1"
  local route="$2"
  local route_amount="$3"
  local route_desc="$4"
  local credits_issued="${5:-}"
  local forward_to="${6:-}"
  local -a route_stakeholders=()
  cat >> "$target" <<EOF
    <Location "$route">
        X402 On
        X402Scheme exact
        X402Network $NETWORK
        X402Asset $ASSET
        X402Amount $route_amount
        X402Description "$route_desc"
        X402MimeType $MIMETYPE
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
    publisher_stakeholders_for_route route_stakeholders "$route"
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

cat > "$TMP_HTTP" <<EOF
X402CreditDBPath $CREDIT_DB_PATH

<VirtualHost *:80>
    ServerName $SERVER_NAME
    DocumentRoot $DOCROOT
    ErrorDocument 402 "protected content: payment required"

    <Directory $DOCROOT>
        Options Indexes FollowSymLinks
        AllowOverride None
        Require all granted
    </Directory>
EOF

if [[ -n "$DOMAIN" ]]; then
  cat >> "$TMP_HTTP" <<EOF
    ServerAlias www.$DOMAIN
EOF
fi

write_route_block "$TMP_HTTP" "/app/foo" "$AMOUNT" "$DESCRIPTION"
write_route_block "$TMP_HTTP" "/price" "$AMOUNT" "Buy 1 access to foo" "1" "/app/foo/"
write_route_block "$TMP_HTTP" "/priceX2" "2000000" "Buy 2 accesses to foo" "2" "/app/foo/"
write_route_block "$TMP_HTTP" "/priceX10" "10000000" "Buy 10 accesses to foo" "10" "/app/foo/"
write_route_block "$TMP_HTTP" "/priceX100" "100000000" "Buy 100 accesses to foo" "100" "/app/foo/"

if [[ "$ENABLE_SSL" == "1" ]]; then
  cat >> "$TMP_HTTP" <<EOF
    RewriteEngine On
    RewriteRule ^/(.*)$ https://$DOMAIN/\$1 [R=301,L]
</VirtualHost>
EOF

  TMP_SSL="$(mktemp)"
  cat > "$TMP_SSL" <<EOF
X402CreditDBPath $CREDIT_DB_PATH

<IfModule mod_ssl.c>
<VirtualHost *:443>
    ServerName $SERVER_NAME
    DocumentRoot $DOCROOT
    ErrorDocument 402 "protected content: payment required"

    SSLEngine on
    SSLCertificateFile $SSL_CERT_FILE
    SSLCertificateKeyFile $SSL_KEY_FILE

    <Directory $DOCROOT>
        Options Indexes FollowSymLinks
        AllowOverride None
        Require all granted
    </Directory>
EOF

  if [[ -n "$DOMAIN" ]]; then
    cat >> "$TMP_SSL" <<EOF
    ServerAlias www.$DOMAIN
EOF
  fi

  write_route_block "$TMP_SSL" "/app/foo" "$AMOUNT" "$DESCRIPTION"
  write_route_block "$TMP_SSL" "/price" "$AMOUNT" "Buy 1 access to foo" "1" "/app/foo"
  write_route_block "$TMP_SSL" "/priceX2" "2000000" "Buy 2 accesses to foo" "2" "/app/foo"
  write_route_block "$TMP_SSL" "/priceX10" "10000000" "Buy 10 accesses to foo" "10" "/app/foo"
  write_route_block "$TMP_SSL" "/priceX100" "100000000" "Buy 100 accesses to foo" "100" "/app/foo"

  cat >> "$TMP_SSL" <<EOF
</VirtualHost>
</IfModule>
EOF
else
  cat >> "$TMP_HTTP" <<EOF
</VirtualHost>
EOF
fi

echo "Installing Apache site config..."
if [[ -n "$TMP_SPLIT" ]]; then
  sudo install -m 644 "$TMP_SPLIT" "$SPLIT_CONF"
  rm -f "$TMP_SPLIT"
fi
sudo install -m 644 "$TMP_HTTP" "$SITE_CONF"
rm -f "$TMP_HTTP"

if [[ -n "$TMP_SSL" ]]; then
  sudo install -m 644 "$TMP_SSL" "$SITE_SSL_CONF"
  rm -f "$TMP_SSL"
fi

echo "Enabling Apache modules and sites..."
sudo a2enmod headers rewrite >/dev/null
sudo a2enmod x402 >/dev/null
if [[ "$ENABLE_SPLIT" == "1" ]]; then
  sudo a2enconf x402-splits >/dev/null
else
  sudo a2disconf x402-splits >/dev/null 2>&1 || true
fi
sudo a2dissite 000-default.conf >/dev/null 2>&1 || true
if [[ "$ENABLE_SSL" == "1" ]]; then
  sudo a2enmod ssl >/dev/null
  sudo a2ensite "${SITE_NAME}.conf" >/dev/null
  sudo a2ensite "${SITE_NAME}-ssl.conf" >/dev/null
else
  sudo a2ensite "${SITE_NAME}.conf" >/dev/null
fi

echo "Validating Apache config..."
sudo apachectl configtest

echo "Reloading Apache..."
if systemctl is-active --quiet apache2; then
  sudo systemctl reload apache2
else
  sudo systemctl restart apache2
fi

echo "Deployment complete."
echo "Site config: $SITE_CONF"
if [[ "$ENABLE_SSL" == "1" ]]; then
  echo "TLS site config: $SITE_SSL_CONF"
fi
echo "Module: $MODULE_PATH"
echo "Facilitator key: $FACILITATOR_KEY_PATH"
echo "Credit DB: $CREDIT_DB_PATH"
if [[ "$ENABLE_SPLIT" == "1" ]]; then
  echo "Split config: $SPLIT_CONF"
fi
echo "Env file: $ENV_FILE"
if [[ -n "$DOMAIN" ]]; then
  echo "HTTP host: http://$DOMAIN/"
else
  echo "HTTP host: use the server IPv4 address"
fi
