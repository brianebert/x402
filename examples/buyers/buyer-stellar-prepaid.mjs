import { wrapFetchWithPayment } from "@x402/fetch";
import { performance } from "node:perf_hooks";
import { Keypair } from "@stellar/stellar-sdk";
import { Agent, fetch as undiciFetch } from "undici";
import { createFreshStellarClient } from "../lib/stellar-fresh-client.mjs";

function resolvePrepaidPath(multiplier) {
  switch (multiplier) {
    case 1:
      return "/price";
    case 2:
      return "/priceX2";
    case 10:
      return "/priceX10";
    case 100:
      return "/priceX100";
    default:
      return null;
  }
}

function resolveCliConfig(argv, env) {
  const targetArg = argv[2] || env.X402_URL || "https://pay.example.com/priceX2";
  const purchaseArg = argv[3] || env.X402_PREPAID_MULTIPLIER || "2";
  const totalCallsArg = argv[4] || env.X402_TOTAL_PROTECTED_CALLS || "";
  const purchaseMultiplier = Number.parseInt(purchaseArg, 10);
  const totalProtectedCalls = Number.parseInt(
    totalCallsArg || String(purchaseMultiplier),
    10
  );
  let url = targetArg;
  const derivedPrepaidPath = resolvePrepaidPath(purchaseMultiplier);
  const targetUrl = new URL(targetArg);

  if (targetUrl.pathname === "/priceX") {
    if (!derivedPrepaidPath) {
      throw new Error(
        `Unsupported prepaid route selector for multiplier ${purchaseMultiplier}. Use 1, 2, 10, or 100.`
      );
    }
    url = new URL(derivedPrepaidPath, targetArg).toString();
  }

  return {
    url,
    purchaseMultiplier,
    totalProtectedCalls,
    repeatCount: Math.max(totalProtectedCalls - 1, 0),
  };
}

const { url, purchaseMultiplier, totalProtectedCalls, repeatCount } = resolveCliConfig(
  process.argv,
  process.env
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

if (!Number.isFinite(repeatCount) || repeatCount < 0) {
  console.error("Repeat count must be a non-negative integer");
  process.exit(1);
}
if (!Number.isFinite(purchaseMultiplier) || purchaseMultiplier < 1) {
  console.error("Purchase multiplier must be a positive integer");
  process.exit(1);
}
if (!Number.isFinite(totalProtectedCalls) || totalProtectedCalls < 1) {
  console.error("Total protected calls must be a positive integer");
  process.exit(1);
}

const keypair = Keypair.fromSecret(stellarPrivateKey);
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
  const explicitFixedRoute = ["/price", "/priceX2", "/priceX10", "/priceX100"].includes(target.pathname);
  if (explicitFixedRoute) {
    return target.toString();
  }
  if (multiplier > 1) {
    target.searchParams.set("x402_prepaid_multiplier", String(multiplier));
  }
  return target.toString();
}

function decodeHeaderJson(headerValue) {
  return JSON.parse(Buffer.from(headerValue, "base64").toString("utf8"));
}

function encodeHeaderJson(value) {
  return Buffer.from(JSON.stringify(value)).toString("base64");
}

function buildStellarAuthHeader(challengeHeader) {
  const challenge = decodeHeaderJson(challengeHeader);
  const message = Buffer.from(challenge.messageBase64, "base64");
  const signature = Buffer.from(keypair.sign(message)).toString("base64");

  return encodeHeaderJson({
    token: challenge.token,
    address: keypair.publicKey(),
    signature,
  });
}

function canonicalProtectedPath(pathname) {
  if (!pathname || pathname === "/") {
    return pathname || "/";
  }
  if (pathname.endsWith("/")) {
    return pathname;
  }
  const lastSegment = pathname.split("/").filter(Boolean).at(-1) || "";
  if (lastSegment.includes(".")) {
    return pathname;
  }
  return `${pathname}/`;
}

function targetUrlForChallenge(challengeHeader) {
  const challenge = decodeHeaderJson(challengeHeader);
  const target = new URL(url);
  target.pathname = canonicalProtectedPath(challenge.path || target.pathname);
  target.search = "";
  return target.toString();
}

function printPaymentRequired(headerValue) {
  if (!headerValue) {
    console.log("PAYMENT-REQUIRED header not found.");
    return;
  }
  console.log(JSON.stringify(decodeHeaderJson(headerValue), null, 2));
}

function printInitialPaidResponse(response, body) {
  const splitHash = response.headers.get("x402-split-transaction-hash");

  console.log("\nInitial Paid Response");
  console.log(`Status: ${response.status}`);
  if (splitHash) {
    console.log("Header:");
    console.log(`x402-split-transaction-hash: ${splitHash}`);
  }
  console.log("\nBody:");
  console.log(body);
}

function printSignedRepeatResponse(index, response, body) {
  console.log(`\nSigned Repeat Response ${index}`);
  console.log(`Status: ${response.status}`);
  console.log("\nBody:");
  console.log(body);
}

function printUnpaidResponse(response, body) {
  console.log("\nInitial 402 Response");
  console.log(`Status: ${response.status}`);
  console.log("\nBody:");
  console.log(body);
  console.log("\nDecoded PAYMENT-REQUIRED:");
  printPaymentRequired(response.headers.get("payment-required"));
}

async function timedRequest(label, targetUrl, fn) {
  console.log(`\n${label} Request: GET ${targetUrl}`);
  const started = performance.now();
  const response = await fn();
  const elapsedMs = performance.now() - started;
  console.log(`${label} Time: ${elapsedMs.toFixed(3)} ms`);
  return response;
}

async function fetchSignedWithChallenge(challengeHeader) {
  const authHeader = buildStellarAuthHeader(challengeHeader);
  const challengeUrl = targetUrlForChallenge(challengeHeader);
  return timedRequest("Signed Repeat", challengeUrl, () =>
    fetchImpl(challengeUrl, {
      method: "GET",
      headers: {
        "X402-Stellar-Auth": authHeader,
      },
    })
  );
}

async function main() {
  console.log(`Target: ${url}`);
  console.log(`Network: ${network}`);
  console.log(`Purchase Multiplier: ${purchaseMultiplier}`);
  console.log(`Total Protected Calls: ${totalProtectedCalls}`);

  const purchaseUrl = withPurchaseMultiplier(url, purchaseMultiplier);
  const unpaidResponse = await timedRequest("Initial 402", purchaseUrl, () =>
    fetchImpl(purchaseUrl, {
      method: "GET",
    })
  );
  const unpaidBody = await unpaidResponse.text();
  printUnpaidResponse(unpaidResponse, unpaidBody);

  const initialResponse = await timedRequest("Initial Purchase", purchaseUrl, () =>
    fetchWithPayment(purchaseUrl, {
      method: "GET",
    })
  );
  const initialBody = await initialResponse.text();
  printInitialPaidResponse(initialResponse, initialBody);

  let challengeHeader = initialResponse.headers.get("x402-stellar-auth-challenge");
  for (let i = 0; i < repeatCount; i += 1) {
    if (!challengeHeader) {
      console.log(`\nNo further X402-Stellar-Auth-Challenge available before repeat request ${i + 1}.`);
      break;
    }

    const response = await fetchSignedWithChallenge(challengeHeader);
    const body = await response.text();
    printSignedRepeatResponse(i + 1, response, body);
    challengeHeader = response.headers.get("x402-stellar-auth-challenge");
  }
}

main().catch((error) => {
  console.error("Prepaid Stellar buyer flow failed:");
  console.error(error);
  process.exit(1);
});
