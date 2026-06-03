#!/usr/bin/env bash

if [[ "${X402_HOST_INSTALL_COMMON_LOADED:-0}" == "1" ]]; then
  return 0
fi
X402_HOST_INSTALL_COMMON_LOADED=1

if [[ "$(uname -s)" != "Linux" ]]; then
  echo "This script is intended to run on a Linux Apache host." >&2
  exit 1
fi

if [[ ! -f /etc/debian_version ]]; then
  echo "This script currently supports Debian/Ubuntu Apache layouts only." >&2
  exit 1
fi

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
ENV_FILE="${X402_ENV_FILE:-$ROOT/.env}"
VHOST_ENV_FILE="${X402_VHOST_ENV_FILE:-}"
declare -A X402_CALLER_ENV=()
for name in $(compgen -v X402_); do
  case "$name" in
    X402_CALLER_ENV|X402_HOST_INSTALL_COMMON_LOADED) continue ;;
  esac
  X402_CALLER_ENV["$name"]="${!name}"
done

source_env_file() {
  local file="$1"

  if [[ -f "$file" ]]; then
    set -a
    # shellcheck disable=SC1090
    source "$file"
    set +a
  fi
}

source_env_file "$ENV_FILE"
if [[ -n "$VHOST_ENV_FILE" ]]; then
  source_env_file "$VHOST_ENV_FILE"
fi
if [[ "${#X402_CALLER_ENV[@]}" -gt 0 ]]; then
  for name in "${!X402_CALLER_ENV[@]}"; do
    printf -v "$name" '%s' "${X402_CALLER_ENV[$name]}"
    export "$name"
  done
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
  local -n target_array="$array_name"

  if [[ -z "$name" || -z "$bps" || -z "$dest" ]]; then
    echo "$label requires NAME, BPS, and DEST" >&2
    exit 1
  fi
  validate_bps "$label" "$bps"
  target_array+=("$name|$bps|$dest")
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
  local -n target_array="$array_name"

  target_array=()
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

route_count() {
  local count="${X402_ROUTE_COUNT:-}"

  if [[ -n "$count" ]]; then
    if [[ ! "$count" =~ ^[0-9]+$ || "$count" -eq 0 ]]; then
      echo "X402_ROUTE_COUNT must be a positive integer" >&2
      exit 1
    fi
    printf '%s\n' "$count"
    return 0
  fi
  printf '%s\n' 5
}

route_path() {
  local index="$1"
  local value

  value="$(env_value "X402_ROUTE_${index}_PATH")"
  if [[ -n "$value" ]]; then
    printf '%s\n' "$value"
    return 0
  fi

  case "$index" in
    1) printf '%s\n' "/app/foo" ;;
    2) printf '%s\n' "/price" ;;
    3) printf '%s\n' "/priceX2" ;;
    4) printf '%s\n' "/priceX10" ;;
    5) printf '%s\n' "/priceX100" ;;
    *) echo "Missing required environment variable: X402_ROUTE_${index}_PATH" >&2; exit 1 ;;
  esac
}

route_amount() {
  local index="$1"
  local value

  value="$(env_value "X402_ROUTE_${index}_AMOUNT")"
  if [[ -n "$value" ]]; then
    printf '%s\n' "$value"
    return 0
  fi

  case "$index" in
    1|2) printf '%s\n' "$AMOUNT" ;;
    3) printf '%s\n' "2000000" ;;
    4) printf '%s\n' "10000000" ;;
    5) printf '%s\n' "100000000" ;;
    *) echo "Missing required environment variable: X402_ROUTE_${index}_AMOUNT" >&2; exit 1 ;;
  esac
}

route_description() {
  local index="$1"
  local value

  value="$(env_value "X402_ROUTE_${index}_DESCRIPTION")"
  if [[ -n "$value" ]]; then
    printf '%s\n' "$value"
    return 0
  fi

  case "$index" in
    1) printf '%s\n' "$DESCRIPTION" ;;
    2) printf '%s\n' "Buy 1 access to foo" ;;
    3) printf '%s\n' "Buy 2 accesses to foo" ;;
    4) printf '%s\n' "Buy 10 accesses to foo" ;;
    5) printf '%s\n' "Buy 100 accesses to foo" ;;
    *) echo "Missing required environment variable: X402_ROUTE_${index}_DESCRIPTION" >&2; exit 1 ;;
  esac
}

route_mimetype() {
  local index="$1"
  local value

  value="$(env_value "X402_ROUTE_${index}_MIMETYPE")"
  printf '%s\n' "${value:-$MIMETYPE}"
}

route_credits_issued() {
  local index="$1"
  local value

  value="$(env_value "X402_ROUTE_${index}_CREDITS_ISSUED")"
  if [[ -n "$value" ]]; then
    printf '%s\n' "$value"
    return 0
  fi

  case "$index" in
    2) printf '%s\n' "1" ;;
    3) printf '%s\n' "2" ;;
    4) printf '%s\n' "10" ;;
    5) printf '%s\n' "100" ;;
    *) printf '%s\n' "" ;;
  esac
}

route_forward_to() {
  local index="$1"
  local value

  value="$(env_value "X402_ROUTE_${index}_FORWARD_TO")"
  if [[ -n "$value" ]]; then
    printf '%s\n' "$value"
    return 0
  fi

  case "$index" in
    2|3|4|5) printf '%s\n' "/app/foo/" ;;
    *) printf '%s\n' "" ;;
  esac
}

route_content_file() {
  local index="$1"
  local value

  value="$(env_value "X402_ROUTE_${index}_CONTENT_FILE")"
  if [[ -n "$value" ]]; then
    printf '%s\n' "$value"
    return 0
  fi

  case "$index" in
    1|2|3|4|5) printf '%s\n' "index.html" ;;
    *) printf '%s\n' "" ;;
  esac
}

route_content_body() {
  local index="$1"
  local value

  value="$(env_value "X402_ROUTE_${index}_CONTENT_BODY")"
  if [[ -n "$value" ]]; then
    printf '%s\n' "$value"
    return 0
  fi

  case "$index" in
    1) printf '%s\n' "yoo hoo" ;;
    2|3|4|5) printf '%s\n' "<html><body>x402 purchase route</body></html>" ;;
    *) printf '%s\n' "" ;;
  esac
}

route_docroot_path() {
  local route="$1"
  printf '%s/%s\n' "$DOCROOT" "${route#/}"
}

init_x402_defaults() {
  PROJECT_DIR="${X402_PROJECT_DIR:-$ROOT}"
  SITE_NAME="${X402_SITE_NAME:-x402}"
  VHOST_ACTION="${X402_VHOST_ACTION:-install}"
  VHOST_MODE="${X402_VHOST_MODE:-static}"
  DOMAIN="${X402_DOMAIN:-}"
  SERVER_NAME="${X402_SERVER_NAME:-}"
  SERVER_ALIASES="${X402_SERVER_ALIASES:-}"
  ENABLE_WWW_ALIAS="${X402_ENABLE_WWW_ALIAS:-1}"
  DOCROOT="${X402_DOCROOT:-/var/www/$SITE_NAME}"
  VHOST_HTTP_SNIPPET_FILE="${X402_VHOST_HTTP_SNIPPET_FILE:-}"
  VHOST_SSL_SNIPPET_FILE="${X402_VHOST_SSL_SNIPPET_FILE:-}"

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
  MAX_STAKEHOLDERS="${X402_MAX_STAKEHOLDERS:-16}"

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

  ENABLE_SSL="${X402_ENABLE_SSL:-0}"
  SSL_CERT_FILE="${X402_SSL_CERT_FILE:-}"
  SSL_KEY_FILE="${X402_SSL_KEY_FILE:-}"

  ENABLE_DYNAMIC_INTENTS="${X402_ENABLE_DYNAMIC_INTENTS:-0}"
  DYNAMIC_SETTLEMENT_MODE="${X402_DYNAMIC_SETTLEMENT_MODE:-facilitator}"
  CHALLENGE_ENDPOINT="${X402_CHALLENGE_ENDPOINT:-/x402/challenge}"
  DYNAMIC_CHECKOUT_ENDPOINT="${X402_DYNAMIC_CHECKOUT_ENDPOINT:-/api/store/checkout}"
  INTENT_SECRET="${X402_INTENT_SECRET:-}"
  INTENT_SECRET_SOURCE_FILE="${X402_INTENT_SECRET_SOURCE_FILE:-}"
  INTENT_SECRET_PATH="${X402_INTENT_SECRET_PATH:-/etc/apache2/x402-secrets/${SITE_NAME}-intent.key}"

  PROXY_TARGET="${X402_PROXY_TARGET:-}"
  PROXY_PRESERVE_HOST="${X402_PROXY_PRESERVE_HOST:-1}"
  PROXY_HTTPS_ONLY="${X402_PROXY_HTTPS_ONLY:-1}"
  PROXY_EXCLUDE_PATHS="${X402_PROXY_EXCLUDE_PATHS:-}"
  PROXY_ERROR_DOCUMENT="${X402_PROXY_ERROR_DOCUMENT:-}"

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

  OPERATOR_STAKEHOLDERS=()
  PUBLISHER_STAKEHOLDERS=()

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
}

publisher_stakeholders_for_route() {
  local array_name="$1"
  local route="$2"
  local index="${3:-}"
  local key
  local -n target_array="$array_name"

  if [[ -n "$index" ]]; then
    collect_route_stakeholders "$array_name" "$index"
    if [[ "${#target_array[@]}" -gt 0 ]]; then
      return 0
    fi
  fi
  key="$(route_key "$route")"
  collect_route_stakeholders "$array_name" "$key"
  if [[ "${#target_array[@]}" -eq 0 ]]; then
    target_array=("${PUBLISHER_STAKEHOLDERS[@]}")
  fi
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
  local index="${2:-}"
  local -a route_stakeholders=()
  local total

  publisher_stakeholders_for_route route_stakeholders "$route" "$index"
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

validate_split_stakeholders_for_routes() {
  local count i route

  collect_split_stakeholders
  if [[ "${#OPERATOR_STAKEHOLDERS[@]}" -eq 0 ]]; then
    echo "Split mode requires at least one operator stakeholder" >&2
    exit 1
  fi

  count="$(route_count)"
  for ((i = 1; i <= count; i++)); do
    route="$(route_path "$i")"
    validate_route_split_bps "$route" "$i"
  done
}

ensure_facilitator_api_key() {
  if [[ -n "${X402_FACILITATOR_API_KEY:-}" || -n "$FACILITATOR_API_KEY_SOURCE_FILE" ]]; then
    return 0
  fi

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
}

ensure_dynamic_intent_secret() {
  if [[ "$ENABLE_DYNAMIC_INTENTS" != "1" ]]; then
    return 0
  fi
  if [[ -n "$INTENT_SECRET" || -n "$INTENT_SECRET_SOURCE_FILE" || -f "$INTENT_SECRET_PATH" ]]; then
    return 0
  fi

  echo "Set X402_INTENT_SECRET, X402_INTENT_SECRET_SOURCE_FILE, or X402_INTENT_SECRET_PATH for dynamic intents." >&2
  exit 1
}

validate_common_config() {
  case "$VHOST_ACTION" in
    install|disable|delete) ;;
    *)
      echo "X402_VHOST_ACTION must be install, disable, or delete." >&2
      exit 1
      ;;
  esac
  case "$VHOST_MODE" in
    static|proxy) ;;
    *)
      echo "X402_VHOST_MODE must be static or proxy." >&2
      exit 1
      ;;
  esac

  if [[ "$VHOST_ACTION" != "install" ]]; then
    return 0
  fi

  if [[ "$VHOST_MODE" == "static" ]]; then
    require_env X402_ASSET
    if [[ "$ENABLE_SPLIT" != "1" ]]; then
      require_env X402_PAY_TO
    fi
  fi

  if [[ "$ENABLE_SPLIT" == "1" ]]; then
    require_env X402_STELLAR_SOURCE_ACCOUNT
    require_env X402_SPLITTER_CONTRACT
    STELLAR_IDENTITY_PATH="$STELLAR_CONFIG_DIR/identity/${STELLAR_SOURCE_ACCOUNT}.toml"
  fi

  if [[ "$VHOST_MODE" == "proxy" ]]; then
    require_env X402_PROXY_TARGET
    if [[ "$PROXY_TARGET" != http://* && "$PROXY_TARGET" != https://* ]]; then
      echo "X402_PROXY_TARGET must start with http:// or https://." >&2
      exit 1
    fi
    case "$PROXY_PRESERVE_HOST" in
      0|1) ;;
      *) echo "X402_PROXY_PRESERVE_HOST must be 0 or 1." >&2; exit 1 ;;
    esac
    case "$PROXY_HTTPS_ONLY" in
      0|1) ;;
      *) echo "X402_PROXY_HTTPS_ONLY must be 0 or 1." >&2; exit 1 ;;
    esac
  fi

  case "$ENABLE_WWW_ALIAS" in
    0|1) ;;
    *) echo "X402_ENABLE_WWW_ALIAS must be 0 or 1." >&2; exit 1 ;;
  esac

  if [[ "$ENABLE_SSL" == "1" ]]; then
    if [[ -z "$DOMAIN" ]]; then
      echo "Set X402_DOMAIN when X402_ENABLE_SSL=1." >&2
      exit 1
    fi
    require_env X402_SSL_CERT_FILE
    require_env X402_SSL_KEY_FILE
  fi

  if [[ -n "$VHOST_HTTP_SNIPPET_FILE" && ! -f "$VHOST_HTTP_SNIPPET_FILE" ]]; then
    echo "X402_VHOST_HTTP_SNIPPET_FILE does not exist: $VHOST_HTTP_SNIPPET_FILE" >&2
    exit 1
  fi
  if [[ -n "$VHOST_SSL_SNIPPET_FILE" && ! -f "$VHOST_SSL_SNIPPET_FILE" ]]; then
    echo "X402_VHOST_SSL_SNIPPET_FILE does not exist: $VHOST_SSL_SNIPPET_FILE" >&2
    exit 1
  fi

  if [[ "$ENABLE_DYNAMIC_INTENTS" == "1" ]]; then
    if [[ "$CHALLENGE_ENDPOINT" != /* ]]; then
      echo "X402_CHALLENGE_ENDPOINT must be an absolute URI path." >&2
      exit 1
    fi
    if [[ "$DYNAMIC_CHECKOUT_ENDPOINT" != /* ]]; then
      echo "X402_DYNAMIC_CHECKOUT_ENDPOINT must be an absolute URI path." >&2
      exit 1
    fi
    ensure_dynamic_intent_secret
  elif [[ "$ENABLE_DYNAMIC_INTENTS" != "0" ]]; then
    echo "X402_ENABLE_DYNAMIC_INTENTS must be 0 or 1." >&2
    exit 1
  fi
}

validate_system_config() {
  validate_common_config
  if [[ "$ENABLE_SPLIT" == "1" ]]; then
    collect_split_stakeholders
    if [[ "${#OPERATOR_STAKEHOLDERS[@]}" -eq 0 ]]; then
      echo "Split mode requires at least one operator stakeholder" >&2
      exit 1
    fi
  fi
}

validate_vhost_config() {
  local count i route

  validate_common_config
  if [[ "$VHOST_ACTION" != "install" ]]; then
    return 0
  fi
  if [[ "$ENABLE_SPLIT" == "1" && "$VHOST_MODE" == "static" ]]; then
    validate_split_stakeholders_for_routes
  fi
  if [[ "$ENABLE_DYNAMIC_INTENTS" == "1" && "$VHOST_MODE" == "static" ]]; then
    count="$(route_count)"
    for ((i = 1; i <= count; i++)); do
      route="$(route_path "$i")"
      if [[ "$route" == "$DYNAMIC_CHECKOUT_ENDPOINT" ]]; then
        echo "X402_DYNAMIC_CHECKOUT_ENDPOINT must not also be configured as a static X402 route: $route" >&2
        exit 1
      fi
    done
  fi
}

apache_reload_or_restart() {
  echo "Validating Apache config..."
  sudo apachectl configtest

  echo "Reloading Apache..."
  if systemctl is-active --quiet apache2; then
    sudo systemctl reload apache2
  else
    sudo systemctl restart apache2
  fi
}
