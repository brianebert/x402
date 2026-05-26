#!/bin/sh
set -eu

usage() {
  cat <<'EOF'
Usage:
  test-x402-flow.sh [URL]

Environment:
  PAYMENT_SIGNATURE_B64   Base64-encoded PAYMENT-SIGNATURE header to send
  PAYMENT_JSON_FILE       Path to a JSON file; script base64-encodes it as PAYMENT-SIGNATURE
  X402_PAYER              Optional X402-Payer header for legacy prepaid bootstrap tests
  X402_STELLAR_AUTH       Optional base64-encoded X402-Stellar-Auth header
  CURL_INSECURE=1         Pass -k to curl for local/self-signed testing

Examples:
  ./test-x402-flow.sh https://pay.example.com/app/foo
  PAYMENT_JSON_FILE=./sample-payment.json ./test-x402-flow.sh https://pay.example.com/app/foo
  PAYMENT_SIGNATURE_B64="$(printf %s '{"scheme":"exact"}' | base64)" ./test-x402-flow.sh
  X402_PAYER='payer:GABC123' ./test-x402-flow.sh https://pay.example.com/app/foo
  X402_STELLAR_AUTH='eyJ0b2tlbiI6Ii4uLiJ9' ./test-x402-flow.sh https://pay.example.com/app/foo
EOF
}

URL="${1:-https://pay.example.com/app/foo}"
WORKDIR="${TMPDIR:-/tmp}/x402-flow.$$"
mkdir -p "$WORKDIR"
trap 'rm -rf "$WORKDIR"' EXIT INT TERM

if [ "${1:-}" = "--help" ] || [ "${1:-}" = "-h" ]; then
  usage
  exit 0
fi

CURL_FLAGS="-sS"
if [ "${CURL_INSECURE:-0}" = "1" ]; then
  CURL_FLAGS="$CURL_FLAGS -k"
fi

PAYMENT_HEADER=""
if [ -n "${PAYMENT_SIGNATURE_B64:-}" ]; then
  PAYMENT_HEADER="$PAYMENT_SIGNATURE_B64"
elif [ -n "${PAYMENT_JSON_FILE:-}" ]; then
  if [ ! -f "$PAYMENT_JSON_FILE" ]; then
    echo "PAYMENT_JSON_FILE does not exist: $PAYMENT_JSON_FILE" >&2
    exit 1
  fi
  PAYMENT_HEADER="$(base64 < "$PAYMENT_JSON_FILE" | tr -d '\n')"
fi

run_request() {
  label="$1"
  headers="$WORKDIR/$label.headers"
  body="$WORKDIR/$label.body"

  CMD="curl $CURL_FLAGS -D '$headers' -o '$body'"
  if [ -n "${X402_PAYER:-}" ]; then
    CMD="$CMD -H 'X402-Payer: $X402_PAYER'"
  fi
  if [ -n "${X402_STELLAR_AUTH:-}" ]; then
    CMD="$CMD -H 'X402-Stellar-Auth: $X402_STELLAR_AUTH'"
  fi
  if [ -n "$PAYMENT_HEADER" ]; then
    CMD="$CMD -H 'PAYMENT-SIGNATURE: $PAYMENT_HEADER'"
  fi
  CMD="$CMD '$URL'"

  # shellcheck disable=SC2086
  sh -c "$CMD"

  echo "--- $label HEADERS ---"
  sed -n '1,60p' "$headers"
  echo "--- $label BODY ---"
  sed -n '1,80p' "$body"
  echo

  PAYMENT_REQUIRED_LINE="$(grep -i '^PAYMENT-REQUIRED:' "$headers" || true)"
  if [ -n "$PAYMENT_REQUIRED_LINE" ]; then
    echo "--- $label PAYMENT-REQUIRED ---"
    printf '%s\n\n' "${PAYMENT_REQUIRED_LINE#*: }"
  fi
}

echo "Target: $URL"
if [ -n "$PAYMENT_HEADER" ]; then
  echo "Mode: challenge + paid retry"
else
  echo "Mode: challenge only"
fi
if [ -n "${X402_PAYER:-}" ]; then
  echo "X402-Payer: $X402_PAYER"
fi
if [ -n "${X402_STELLAR_AUTH:-}" ]; then
  echo "X402-Stellar-Auth: $X402_STELLAR_AUTH"
fi
echo

PAYMENT_HEADER=""
run_request unpaid

if [ -n "${PAYMENT_SIGNATURE_B64:-}" ] || [ -n "${PAYMENT_JSON_FILE:-}" ]; then
  if [ -n "${PAYMENT_SIGNATURE_B64:-}" ]; then
    PAYMENT_HEADER="$PAYMENT_SIGNATURE_B64"
  else
    PAYMENT_HEADER="$(base64 < "$PAYMENT_JSON_FILE" | tr -d '\n')"
  fi
  run_request paid
fi
