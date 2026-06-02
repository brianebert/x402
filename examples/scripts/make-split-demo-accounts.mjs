import { mkdir, readFile, writeFile } from "node:fs/promises";
import path from "node:path";
import process from "node:process";
import { fileURLToPath } from "node:url";

import {
  Asset,
  BASE_FEE,
  Horizon,
  Keypair,
  Networks,
  Operation,
  TransactionBuilder,
} from "@stellar/stellar-sdk";
import { fetch as undiciFetch } from "undici";

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);
const examplesDir = path.resolve(__dirname, "..");

const defaults = {
  network: process.env.STELLAR_NETWORK || "stellar:testnet",
  horizonUrl: process.env.STELLAR_HORIZON_URL || "https://horizon-testnet.stellar.org",
  friendbotUrl: process.env.STELLAR_FRIENDBOT_URL || "https://friendbot.stellar.org",
  usdcCode: process.env.STELLAR_USDC_ASSET_CODE || "USDC",
  usdcIssuer:
    process.env.STELLAR_USDC_ISSUER || "GBBD47IF6LWK7P7MDEVSCWR7DPUWV3NY3DTQEVFL4NAT4AQH3ZLLFLA5",
  splitterContract:
    process.env.X402_SPLITTER_CONTRACT || "CCTVCH6BUWS4XESFHK4BHKK35KY56PQ5PGSIQHKJBNYMTWXXGXLYKMBD",
  sourceAccountName: process.env.X402_STELLAR_SOURCE_ACCOUNT || "operator_demo_split",
  operatorStakeholderName:
    process.env.X402_OPERATOR_STAKEHOLDER_1_NAME || process.env.X402_STAKEHOLDER_1_NAME || "server",
  operatorStakeholderBps:
    process.env.X402_OPERATOR_STAKEHOLDER_1_BPS || process.env.X402_STAKEHOLDER_1_BPS || "7000",
  publisherStakeholderName:
    process.env.X402_PUBLISHER_STAKEHOLDER_1_NAME || process.env.X402_STAKEHOLDER_2_NAME || "creator",
  publisherStakeholderBps:
    process.env.X402_PUBLISHER_STAKEHOLDER_1_BPS || process.env.X402_STAKEHOLDER_2_BPS || "3000",
};

const networkPassphrase =
  defaults.network === "stellar:testnet" ? Networks.TESTNET : process.env.STELLAR_NETWORK_PASSPHRASE;

if (!networkPassphrase) {
  console.error("Unsupported network without STELLAR_NETWORK_PASSPHRASE");
  process.exit(1);
}

const statePath =
  process.env.X402_DEMO_STATE_FILE ||
  path.join(examplesDir, ".demo-accounts", `${defaults.network.replace(/[:/]/g, "-")}.json`);
const outputDir =
  process.env.X402_SPLIT_DEMO_OUTPUT_DIR || path.join(examplesDir, ".demo-accounts", "split-server");

const horizon = new Horizon.Server(defaults.horizonUrl);
const usdcAsset = new Asset(defaults.usdcCode, defaults.usdcIssuer);

async function loadDemoState() {
  await mkdir(path.dirname(statePath), { recursive: true });
  try {
    const text = await readFile(statePath, "utf8");
    return JSON.parse(text);
  } catch {
    return { accounts: {} };
  }
}

async function saveDemoState(state) {
  await writeFile(statePath, `${JSON.stringify(state, null, 2)}\n`, { mode: 0o600 });
}

async function loadAccountIfExists(publicKey) {
  try {
    return await horizon.loadAccount(publicKey);
  } catch (error) {
    if (error?.response?.status === 404) {
      return null;
    }
    throw error;
  }
}

async function ensureFriendbotFunding(publicKey) {
  const response = await undiciFetch(`${defaults.friendbotUrl}?addr=${encodeURIComponent(publicKey)}`);
  if (!response.ok) {
    const body = await response.text();
    throw new Error(`friendbot funding failed for ${publicKey}: ${response.status} ${body}`);
  }
}

async function ensureUsdcTrustline(secretKey) {
  const keypair = Keypair.fromSecret(secretKey);
  const account = await horizon.loadAccount(keypair.publicKey());
  const hasTrustline = account.balances.some(
    (balance) => balance.asset_code === defaults.usdcCode && balance.asset_issuer === defaults.usdcIssuer
  );

  if (hasTrustline) {
    return;
  }

  const transaction = new TransactionBuilder(account, {
    fee: BASE_FEE,
    networkPassphrase,
  })
    .addOperation(
      Operation.changeTrust({
        asset: usdcAsset,
      })
    )
    .setTimeout(30)
    .build();
  transaction.sign(keypair);
  await horizon.submitTransaction(transaction);
}

async function ensureDemoAccount(state, name, options = {}) {
  let account = state.accounts[name];

  if (!account?.secretKey) {
    const keypair = Keypair.random();
    account = {
      publicKey: keypair.publicKey(),
      secretKey: keypair.secret(),
      createdAt: new Date().toISOString(),
    };
    state.accounts[name] = account;
    await saveDemoState(state);
    console.log(`Created demo account ${name}: ${account.publicKey}`);
  } else {
    console.log(`Using saved demo account ${name}: ${account.publicKey}`);
  }

  let loaded = await loadAccountIfExists(account.publicKey);
  if (!loaded) {
    console.log(`Funding ${name} with Friendbot...`);
    await ensureFriendbotFunding(account.publicKey);
    loaded = await horizon.loadAccount(account.publicKey);
  }

  if (options.usdcTrustline) {
    console.log(`Ensuring ${name} has a ${defaults.usdcCode} trustline...`);
    await ensureUsdcTrustline(account.secretKey);
  }

  return account;
}

function serializeEnv(env) {
  return `${Object.entries(env)
    .map(([key, value]) =>
      key === "X402_STELLAR_NETWORK_PASSPHRASE" ? `${key}=${JSON.stringify(value)}` : `${key}=${value}`
    )
    .join("\n")}\n`;
}

async function main() {
  const state = await loadDemoState();
  const buyer = await ensureDemoAccount(state, "buyer", { usdcTrustline: true });
  const server = await ensureDemoAccount(state, "splitServer", { usdcTrustline: true });
  const creator = await ensureDemoAccount(state, "splitCreator", { usdcTrustline: true });
  const source = await ensureDemoAccount(state, "splitSource", { usdcTrustline: false });
  await saveDemoState(state);

  await mkdir(outputDir, { recursive: true });

  const envPath = path.join(outputDir, "split-server.env");
  const identityPath = path.join(outputDir, `${defaults.sourceAccountName}.toml`);
  const accountsPath = path.join(outputDir, "split-accounts.json");

  const env = {
    X402_ENABLE_SPLIT: "1",
    X402_STELLAR_SOURCE_ACCOUNT: defaults.sourceAccountName,
    X402_SPLITTER_CONTRACT: defaults.splitterContract,
    X402_OPERATOR_STAKEHOLDER_1_NAME: defaults.operatorStakeholderName,
    X402_OPERATOR_STAKEHOLDER_1_BPS: defaults.operatorStakeholderBps,
    X402_OPERATOR_STAKEHOLDER_1_DEST: server.publicKey,
    X402_PUBLISHER_STAKEHOLDER_1_NAME: defaults.publisherStakeholderName,
    X402_PUBLISHER_STAKEHOLDER_1_BPS: defaults.publisherStakeholderBps,
    X402_PUBLISHER_STAKEHOLDER_1_DEST: creator.publicKey,
    X402_STELLAR_RPC_URL: process.env.X402_STELLAR_RPC_URL || "https://soroban-testnet.stellar.org:443",
    X402_STELLAR_NETWORK_PASSPHRASE:
      process.env.X402_STELLAR_NETWORK_PASSPHRASE || "Test SDF Network ; September 2015",
  };

  const accounts = {
    buyer,
    server,
    creator,
    source,
  };

  await writeFile(envPath, serializeEnv(env), { mode: 0o600 });
  await writeFile(identityPath, `secret_key = "${source.secretKey}"\n`, { mode: 0o600 });
  await writeFile(accountsPath, `${JSON.stringify(accounts, null, 2)}\n`, { mode: 0o600 });

  console.log("\nSplit server .env additions:");
  console.log(serializeEnv(env));
  console.log(`Identity TOML: ${identityPath}`);
  console.log(`Env fragment: ${envPath}`);
  console.log(`Accounts JSON: ${accountsPath}`);
  console.log("\nInstall on server:");
  console.log(`1. Merge ${envPath} into /srv/x402/.env`);
  console.log(
    `2. Install ${identityPath} as /etc/apache2/x402-stellar/identity/${defaults.sourceAccountName}.toml`
  );
  console.log("3. Run ./scripts/host-system-install.sh, then ./scripts/host-vhost-install.sh");
  console.log("   Or run ./scripts/host-admin-install.sh to execute both phases");
  console.log("\nAccount summary:");
  console.log(`buyer: ${buyer.publicKey}`);
  console.log(`server: ${server.publicKey}`);
  console.log(`creator: ${creator.publicKey}`);
  console.log(`source: ${source.publicKey}`);
}

main().catch((error) => {
  console.error(error instanceof Error ? error.stack || error.message : error);
  process.exit(1);
});
