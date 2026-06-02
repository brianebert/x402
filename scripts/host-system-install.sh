#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
# shellcheck source=lib/host-install-common.sh
source "$SCRIPT_DIR/lib/host-install-common.sh"

init_x402_defaults
validate_system_config
ensure_facilitator_api_key

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
    echo "Missing split signer identity: install $STELLAR_IDENTITY_PATH or pass X402_STELLAR_SOURCE_SECRET_KEY when invoking this script." >&2
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

if [[ "$ENABLE_SPLIT" == "1" ]]; then
  tmp_split="$(mktemp)"
  cat > "$tmp_split" <<EOF
X402SplitMode multi
X402SplitterContract $SPLITTER_CONTRACT
EOF
  emit_stakeholders "$tmp_split" "" "${OPERATOR_STAKEHOLDERS[@]}"
  sudo install -m 644 "$tmp_split" "$SPLIT_CONF"
  rm -f "$tmp_split"
else
  sudo rm -f "$SPLIT_CONF"
fi

echo "Enabling Apache module and systemwide x402 config..."
sudo a2enmod headers rewrite >/dev/null
sudo a2enmod x402 >/dev/null
if [[ "$ENABLE_SPLIT" == "1" ]]; then
  sudo a2enconf x402-splits >/dev/null
else
  sudo a2disconf x402-splits >/dev/null 2>&1 || true
fi

apache_reload_or_restart

echo "System install complete."
echo "Module: $MODULE_PATH"
echo "Facilitator key: $FACILITATOR_KEY_PATH"
echo "Credit DB: $CREDIT_DB_PATH"
if [[ "$ENABLE_SPLIT" == "1" ]]; then
  echo "Split config: $SPLIT_CONF"
fi
echo "Env file: $ENV_FILE"
