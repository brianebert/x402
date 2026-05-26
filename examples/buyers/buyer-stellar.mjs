import { x402Client, x402HTTPClient } from "@x402/core/client";
import { wrapFetchWithPayment } from "@x402/fetch";
import { Agent, fetch as undiciFetch } from "undici";
import { createFreshStellarClient } from "../lib/stellar-fresh-client.mjs";

const url = process.argv[2] || process.env.X402_URL || "https://pay.example.com/app/foo";
const prepaidMultiplier = Number.parseInt(
  process.argv[3] || process.env.X402_PREPAID_MULTIPLIER || "1",
  10
);
const originalUrl = new URL(url);
const network = process.env.STELLAR_NETWORK || "stellar:testnet";
const stellarPrivateKey = process.env.STELLAR_PRIVATE_KEY;
const hostOverrideIp = process.env.X402_HOST_OVERRIDE_IP;
const requestOriginHost = originalUrl.host;

if (!stellarPrivateKey) {
  console.error("Missing STELLAR_PRIVATE_KEY");
  process.exit(1);
}
if (!Number.isFinite(prepaidMultiplier) || prepaidMultiplier < 1) {
  console.error("Prepaid multiplier must be a positive integer");
  process.exit(1);
}

const { client } = createFreshStellarClient(stellarPrivateKey, network);

const dispatcher = hostOverrideIp
  ? new Agent({
      connect: {
        servername: originalUrl.hostname,
      },
    })
  : undefined;

function rewriteUrl(inputUrl) {
  if (!hostOverrideIp) {
    return inputUrl;
  }
  const rewritten = new URL(inputUrl);
  rewritten.hostname = hostOverrideIp;
  return rewritten.toString();
}

function withHostHeader(headersLike) {
  const headers = new Headers(headersLike || {});
  if (hostOverrideIp) {
    headers.set("host", requestOriginHost);
  }
  return headers;
}

const fetchImpl = (input, init = {}) => {
  if (input instanceof Request) {
    const requestInit = {
      method: input.method,
      headers: withHostHeader(input.headers),
      body: input.body,
      redirect: input.redirect,
      dispatcher,
    };
    return undiciFetch(rewriteUrl(input.url), requestInit);
  }

  const requestInit = dispatcher ? { ...init, dispatcher } : { ...init };
  requestInit.headers = withHostHeader(requestInit.headers);
  return undiciFetch(rewriteUrl(input), requestInit);
};

const fetchWithPayment = wrapFetchWithPayment(fetchImpl, client);

function withPurchaseMultiplier(inputUrl, multiplier) {
  const target = new URL(inputUrl);
  if (multiplier > 1) {
    target.searchParams.set("x402_prepaid_multiplier", String(multiplier));
  }
  return target.toString();
}

async function main() {
  console.log(`Target: ${url}`);
  console.log(`Network: ${network}`);
  console.log(`Prepaid Multiplier: ${prepaidMultiplier}`);

  const response = await fetchWithPayment(withPurchaseMultiplier(url, prepaidMultiplier), {
    method: "GET",
  });

  console.log(`Status: ${response.status}`);
  console.log("Headers:");
  for (const [name, value] of response.headers.entries()) {
    console.log(`${name}: ${value}`);
  }

  const body = await response.text();
  console.log("\nBody:");
  console.log(body);

  const httpClient = new x402HTTPClient(client);
  const paymentResponse = httpClient.getPaymentSettleResponse((name) =>
    response.headers.get(name)
  );

  if (paymentResponse) {
    console.log("\nPayment Response:");
    console.log(JSON.stringify(paymentResponse, null, 2));
  } else {
    console.log("\nNo PAYMENT-RESPONSE header found.");
  }
}

main().catch((error) => {
  console.error("Buyer flow failed:");
  console.error(error);
  process.exit(1);
});
