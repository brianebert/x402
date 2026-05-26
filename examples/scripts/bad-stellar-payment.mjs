import { randomUUID } from "node:crypto";
import { Keypair } from "@stellar/stellar-sdk";
import { Agent, fetch as undiciFetch } from "undici";

function usage() {
  console.log(`Usage:
  node scripts/bad-stellar-payment.mjs [URL]

Environment:
  STELLAR_NETWORK       Optional network override; defaults to stellar:testnet
  X402_HOST_OVERRIDE_IP Optional IP override while preserving the original Host header

Examples:
  node scripts/bad-stellar-payment.mjs
  node scripts/bad-stellar-payment.mjs http://64.23.244.67/priceX2`);
}

function withHostHeader(headersLike, hostOverrideIp, requestOriginHost) {
  const headers = new Headers(headersLike || {});
  if (hostOverrideIp) {
    headers.set("host", requestOriginHost);
  }
  return headers;
}

function rewriteUrl(inputUrl, hostOverrideIp) {
  if (!hostOverrideIp) {
    return inputUrl;
  }
  const rewritten = new URL(inputUrl);
  rewritten.hostname = hostOverrideIp;
  return rewritten.toString();
}

function makeFetchImpl(originalUrl, hostOverrideIp) {
  const dispatcher = hostOverrideIp
    ? new Agent({
        connect: {
          servername: originalUrl.hostname,
        },
      })
    : undefined;
  const requestOriginHost = originalUrl.host;

  return (input, init = {}) => {
    if (input instanceof Request) {
      const requestInit = {
        method: input.method,
        headers: withHostHeader(input.headers, hostOverrideIp, requestOriginHost),
        body: input.body,
        redirect: input.redirect,
        dispatcher,
      };
      return undiciFetch(rewriteUrl(input.url, hostOverrideIp), requestInit);
    }

    const requestInit = dispatcher ? { ...init, dispatcher } : { ...init };
    requestInit.headers = withHostHeader(requestInit.headers, hostOverrideIp, requestOriginHost);
    return undiciFetch(rewriteUrl(input, hostOverrideIp), requestInit);
  };
}

function decodeRequiredHeader(headers) {
  const value = headers.get("payment-required");
  if (!value) {
    throw new Error("PAYMENT-REQUIRED header not found");
  }
  return JSON.parse(Buffer.from(value, "base64").toString("utf8"));
}

function buildBadPaymentPayload(paymentRequired, payer, network) {
  const selected = paymentRequired?.accepts?.[0];
  if (!selected) {
    throw new Error("PAYMENT-REQUIRED does not contain an accepts entry");
  }

  return {
    x402Version: 2,
    scheme: selected.scheme || "exact",
    network: selected.network || network,
    payer,
    paymentIdentifier: `pay_${randomUUID()}`,
    multiplier: 1,
    payload: {
      transaction: "AAAA",
    },
    transaction: "AAAA",
  };
}

async function main() {
  if (process.argv[2] === "--help" || process.argv[2] === "-h") {
    usage();
    return;
  }

  const url = process.argv[2] || process.env.X402_URL || "http://64.23.244.67/priceX2";
  const network = process.env.STELLAR_NETWORK || "stellar:testnet";
  const hostOverrideIp = process.env.X402_HOST_OVERRIDE_IP;
  const originalUrl = new URL(url);
  const fetchImpl = makeFetchImpl(originalUrl, hostOverrideIp);
  const keypair = Keypair.random();

  console.log(`Target: ${url}`);
  console.log(`Network: ${network}`);
  console.log(`Testing Public Key: ${keypair.publicKey()}`);

  const challengeResponse = await fetchImpl(url, { method: "GET" });
  await challengeResponse.text();
  const paymentRequired = decodeRequiredHeader(challengeResponse.headers);

  for (let i = 1; i <= 10; i += 1) {
    const badPayload = buildBadPaymentPayload(paymentRequired, keypair.publicKey(), network);
    const paymentSignature = Buffer.from(JSON.stringify(badPayload)).toString("base64");
    const response = await fetchImpl(url, {
      method: "GET",
      headers: {
        "PAYMENT-SIGNATURE": paymentSignature,
      },
    });
    const body = await response.text();
    console.log(`${i}. ${response.status}`);
    console.log(body);
  }
}

main().catch((error) => {
  console.error("Bad Stellar payment test failed:");
  console.error(error);
  process.exit(1);
});
