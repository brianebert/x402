#!/bin/sh
set -eu

usage() {
  cat <<'EOF'
Usage:
  raw-stellar-two-step.sh [IP_ADDRESS|URL]

Environment:
  STELLAR_PRIVATE_KEY   Required Stellar testnet secret key for signing the payment
  STELLAR_NETWORK       Optional network override; defaults to stellar:testnet
  CURL_INSECURE=1       Pass -k to curl for local/self-signed testing

Examples:
  STELLAR_PRIVATE_KEY='S...' ./scripts/raw-stellar-two-step.sh
  STELLAR_PRIVATE_KEY='S...' ./scripts/raw-stellar-two-step.sh 64.23.244.67
  STELLAR_PRIVATE_KEY='S...' ./scripts/raw-stellar-two-step.sh http://64.23.244.67/app/foo/
EOF
}

if [ "${1:-}" = "--help" ] || [ "${1:-}" = "-h" ]; then
  usage
  exit 0
fi

if [ -z "${STELLAR_PRIVATE_KEY:-}" ]; then
  echo "Missing STELLAR_PRIVATE_KEY" >&2
  exit 1
fi

TARGET="${1:-64.23.244.67}"
case "$TARGET" in
  http://*|https://*)
    URL="$TARGET"
    ;;
  *)
    URL="http://$TARGET/app/foo/"
    ;;
esac
NETWORK="${STELLAR_NETWORK:-stellar:testnet}"
WORKDIR="${TMPDIR:-/tmp}/x402-raw-two-step.$$"
mkdir -p "$WORKDIR"
trap 'rm -rf "$WORKDIR"' EXIT INT TERM

CURL_FLAGS="-sS"
if [ "${CURL_INSECURE:-0}" = "1" ]; then
  CURL_FLAGS="$CURL_FLAGS -k"
fi

step1_headers="$WORKDIR/step1.headers"
step1_body="$WORKDIR/step1.body"
step2_headers="$WORKDIR/step2.headers"
step2_body="$WORKDIR/step2.body"

print_headers_with_decoded_marker() {
  headers_file="$1"
  node --input-type=module -e '
    import { readFileSync } from "node:fs";
    const text = readFileSync(process.argv[1], "utf8");
    for (const line of text.split(/\r?\n/)) {
      if (!line) continue;
      if (/^PAYMENT-REQUIRED:/i.test(line)) {
        console.log("PAYMENT-REQUIRED: Decoded below");
        continue;
      }
      console.log(line);
    }
  ' "$headers_file"
}

decode_payment_required() {
  PAYMENT_REQUIRED_B64="$1" node --input-type=module -e '
    const value = JSON.parse(Buffer.from(process.env.PAYMENT_REQUIRED_B64, "base64").toString("utf8"));
    value.extensions = "not used in this demo";

    const keyColor = "\x1b[36m";
    const valueColor = "\x1b[33m";
    const reset = "\x1b[0m";
    const highlighted = new Set(["asset", "amount", "payTo"]);

    function scalar(value) {
      return JSON.stringify(value);
    }

    function format(current, indent = 0, key = "") {
      const pad = " ".repeat(indent);
      if (Array.isArray(current)) {
        if (current.length === 0) return "[]";
        const lines = current.map((item) => `${" ".repeat(indent + 2)}${format(item, indent + 2)}`);
        return `[\n${lines.join(",\n")}\n${pad}]`;
      }
      if (current && typeof current === "object") {
        const entries = Object.entries(current);
        if (entries.length === 0) return "{}";
        const lines = entries.map(([childKey, childValue]) => {
          const renderedKey = highlighted.has(childKey)
            ? `${keyColor}"${childKey}"${reset}`
            : `"${childKey}"`;
          const renderedValue =
            childValue && typeof childValue === "object"
              ? format(childValue, indent + 2, childKey)
              : highlighted.has(childKey)
                ? `${valueColor}${scalar(childValue)}${reset}`
                : scalar(childValue);
          return `${" ".repeat(indent + 2)}${renderedKey}: ${renderedValue}`;
        });
        return `{\n${lines.join(",\n")}\n${pad}}`;
      }
      return highlighted.has(key) ? `${valueColor}${scalar(current)}${reset}` : scalar(current);
    }

    console.log(format(value));
  '
}

decode_payment_signature() {
  PAYMENT_SIGNATURE_B64="$1" node --input-type=module -e '
    const value = JSON.parse(Buffer.from(process.env.PAYMENT_SIGNATURE_B64, "base64").toString("utf8"));
    value.extensions = "not used in this demo";
    if (value.payload && typeof value.payload === "object") {
      delete value.payload.transaction;
      if (Object.keys(value.payload).length === 0) {
        delete value.payload;
      }
    }
    console.log(JSON.stringify(value, null, 2));
  '
}

echo "Target: $URL"
echo "Network: $NETWORK"
echo

echo "== Step 1: unpaid request =="
# shellcheck disable=SC2086
curl $CURL_FLAGS \
  -D "$step1_headers" \
  -o "$step1_body" \
  -w 'Step 1 response: HTTP %{http_code} in %{time_total}s\n' \
  "$URL"
echo
echo "-- Step 1 Headers --"
print_headers_with_decoded_marker "$step1_headers"
echo "-- Step 1 Body --"
cat "$step1_body"
echo

PAYMENT_REQUIRED_B64="$(
  STEP1_HEADERS="$step1_headers" node --input-type=module -e '
    import { readFileSync } from "node:fs";
    const text = readFileSync(process.env.STEP1_HEADERS, "utf8");
    const match = text.match(/^PAYMENT-REQUIRED:\s*(\S+)$/mi);
    if (!match) {
      process.exit(1);
    }
    process.stdout.write(match[1]);
  '
)"

if [ -z "$PAYMENT_REQUIRED_B64" ]; then
  echo "PAYMENT-REQUIRED header not found" >&2
  exit 1
fi

echo "== Decoded PAYMENT-REQUIRED =="
decode_payment_required "$PAYMENT_REQUIRED_B64"
echo

PAYMENT_SIGNATURE_B64="$(
  STELLAR_PRIVATE_KEY="$STELLAR_PRIVATE_KEY" \
  STELLAR_NETWORK="$NETWORK" \
  PAYMENT_REQUIRED_B64="$PAYMENT_REQUIRED_B64" \
  node --input-type=module -e '
    import { createFreshStellarClient } from "./lib/stellar-fresh-client.mjs";
    const network = process.env.STELLAR_NETWORK || "stellar:testnet";
    const paymentRequired = JSON.parse(Buffer.from(process.env.PAYMENT_REQUIRED_B64, "base64").toString("utf8"));
    const { client } = createFreshStellarClient(process.env.STELLAR_PRIVATE_KEY, network);
    const payload = await client.createPaymentPayload(paymentRequired);
    process.stdout.write(Buffer.from(JSON.stringify(payload)).toString("base64"));
  '
)"

if [ -z "$PAYMENT_SIGNATURE_B64" ]; then
  echo "Failed to build PAYMENT-SIGNATURE" >&2
  exit 1
fi

echo "== Decoded PAYMENT-SIGNATURE =="
decode_payment_signature "$PAYMENT_SIGNATURE_B64"
echo

echo "== Step 2: paid request =="
# shellcheck disable=SC2086
curl $CURL_FLAGS \
  -D "$step2_headers" \
  -o "$step2_body" \
  -H "PAYMENT-SIGNATURE: $PAYMENT_SIGNATURE_B64" \
  -w 'Step 2 response: HTTP %{http_code} in %{time_total}s\n' \
  "$URL"
echo
echo "-- Step 2 Headers --"
sed -n '1,20p' "$step2_headers"
echo "-- Step 2 Body --"
cat "$step2_body"
echo

PAYMENT_RESPONSE_B64="$(
  STEP2_HEADERS="$step2_headers" node --input-type=module -e '
    import { readFileSync } from "node:fs";
    const text = readFileSync(process.env.STEP2_HEADERS, "utf8");
    const match = text.match(/^PAYMENT-RESPONSE:\s*(\S+)$/mi);
    process.stdout.write(match ? match[1] : "");
  '
)"

if [ -n "$PAYMENT_RESPONSE_B64" ]; then
  echo "== Decoded PAYMENT-RESPONSE =="
  PAYMENT_RESPONSE_B64="$PAYMENT_RESPONSE_B64" node --input-type=module -e '
    const value = JSON.parse(Buffer.from(process.env.PAYMENT_RESPONSE_B64, "base64").toString("utf8"));
    console.log(JSON.stringify(value, null, 2));
  '
  echo
else
  echo "No PAYMENT-RESPONSE header found."
fi
