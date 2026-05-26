import { x402Client } from "@x402/core/client";
import { randomUUID } from "node:crypto";
import {
  createEd25519Signer,
  getEstimatedLedgerCloseTimeSeconds,
  getNetworkPassphrase,
  getRpcClient,
  getRpcUrl,
  handleSimulationResult,
  isStellarNetwork,
  validateStellarAssetAddress,
  validateStellarDestinationAddress,
} from "@x402/stellar";
import { contract, nativeToScVal } from "@stellar/stellar-sdk";

function deriveLegacyMultiplier(paymentRequired, selectedRequirements) {
  const options = paymentRequired?.extensions?.["prepaid-requests"]?.options;
  if (!Array.isArray(options)) {
    return 1;
  }

  const match = options.find((option) => option?.amount === selectedRequirements?.amount);
  return Number.isInteger(match?.multiplier) && match.multiplier > 0 ? match.multiplier : 1;
}

function clientLedgerSecondsEstimate(network, estimatedLedgerSeconds) {
  if (network === "stellar:testnet") {
    return estimatedLedgerSeconds;
  }
  return estimatedLedgerSeconds;
}

function clientMaxLedgerDelta(network, maxTimeoutSeconds, estimatedLedgerSeconds) {
  const requestedDelta = Math.max(1, Math.ceil(maxTimeoutSeconds / estimatedLedgerSeconds));
  if (network === "stellar:testnet") {
    // OpenZeppelin's testnet facilitator currently rejects auth expirations beyond 7 ledgers.
    return Math.min(requestedDelta, 7);
  }
  return requestedDelta;
}

export class FreshExactStellarScheme {
  constructor(signer, rpcConfig) {
    this.signer = signer;
    this.rpcConfig = rpcConfig;
    this.scheme = "exact";
  }

  async createPaymentPayload(x402Version, paymentRequirements) {
    this.validateCreateAndSignPaymentInput(paymentRequirements);

    const sourcePublicKey = this.signer.address;
    const { network, payTo, asset, amount, extra, maxTimeoutSeconds } = paymentRequirements;
    const networkPassphrase = getNetworkPassphrase(network);
    const rpcUrl = getRpcUrl(network, this.rpcConfig);

    if (!extra.areFeesSponsored) {
      throw new Error("Exact scheme requires areFeesSponsored to be true");
    }

    const tx = await contract.AssembledTransaction.build({
      contractId: asset,
      method: "transfer",
      args: [
        nativeToScVal(sourcePublicKey, { type: "address" }),
        nativeToScVal(payTo, { type: "address" }),
        nativeToScVal(amount, { type: "i128" }),
      ],
      networkPassphrase,
      rpcUrl,
      parseResultXdr: (result) => result,
    });

    handleSimulationResult(tx.simulation);

    let missingSigners = tx.needsNonInvokerSigningBy();
    if (!missingSigners.includes(sourcePublicKey) || missingSigners.length > 1) {
      throw new Error(
        `Expected to sign with [${sourcePublicKey}], but got [${missingSigners.join(", ")}]`
      );
    }

    const rpcServer = getRpcClient(network, this.rpcConfig);
    const latestLedger = await rpcServer.getLatestLedger();
    const estimatedLedgerSeconds = clientLedgerSecondsEstimate(
      network,
      await getEstimatedLedgerCloseTimeSeconds(network)
    );
    const maxLedger =
      latestLedger.sequence +
      clientMaxLedgerDelta(network, maxTimeoutSeconds, estimatedLedgerSeconds);

    await tx.signAuthEntries({
      address: sourcePublicKey,
      signAuthEntry: this.signer.signAuthEntry,
      expiration: maxLedger,
    });

    await tx.simulate();
    handleSimulationResult(tx.simulation);

    missingSigners = tx.needsNonInvokerSigningBy();
    if (missingSigners.length > 0) {
      throw new Error(`unexpected signer(s) required: [${missingSigners.join(", ")}]`);
    }

    return {
      x402Version,
      payload: {
        transaction: tx.built.toXDR(),
      },
    };
  }

  validateCreateAndSignPaymentInput(paymentRequirements) {
    const { scheme, network, payTo, asset, amount } = paymentRequirements;

    if (typeof amount !== "string" || !Number.isInteger(Number(amount)) || Number(amount) <= 0) {
      throw new Error(`Invalid amount: ${amount}. Amount must be a positive integer.`);
    }
    if (scheme !== "exact") {
      throw new Error(`Unsupported scheme: ${scheme}`);
    }
    if (!isStellarNetwork(network)) {
      throw new Error(`Unsupported Stellar network: ${network}`);
    }
    if (!validateStellarDestinationAddress(payTo)) {
      throw new Error(`Invalid Stellar destination address: ${payTo}`);
    }
    if (!validateStellarAssetAddress(asset)) {
      throw new Error(`Invalid Stellar asset address: ${asset}`);
    }
  }
}

export function createFreshStellarClient(secretKey, network, rpcConfig) {
  const signer = createEd25519Signer(secretKey, network);
  const client = new x402Client();
  client.register("stellar:*", new FreshExactStellarScheme(signer, rpcConfig));
  client.onAfterPaymentCreation(({ paymentRequired, selectedRequirements, paymentPayload }) => {
    paymentPayload.scheme = selectedRequirements.scheme;
    paymentPayload.network = selectedRequirements.network;
    paymentPayload.payer = signer.address;
    paymentPayload.paymentIdentifier = `pay_${randomUUID()}`;
    paymentPayload.multiplier = deriveLegacyMultiplier(paymentRequired, selectedRequirements);
    if (paymentPayload?.payload?.transaction) {
      paymentPayload.transaction = paymentPayload.payload.transaction;
    }
  });
  return { signer, client };
}
