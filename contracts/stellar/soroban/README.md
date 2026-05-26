# Soroban Contracts

This directory contains the Soroban contract workspace used by the Stellar x402 demos.

## Included contract

- `payment_receiver`
  - receives a token payment from a payer to a single recipient
  - records a `payment_id` to reject duplicates
  - remains the simple single-recipient contract path

- `payment_splitter`
  - receives one logical payment from a payer
  - fans out multiple token transfers to stakeholder recipients
  - records a `payment_id` to reject duplicates
  - returns the total settled amount

`payment_receiver` remains the simple contract. `payment_splitter` is the active contract path for stakeholder split settlement.

## Build

```sh
cd contracts/stellar/soroban
stellar contract build
```

Expected wasm output:

- `target/wasm32-unknown-unknown/release/payment_receiver.wasm`
- `target/wasm32-unknown-unknown/release/payment_splitter.wasm`

## Deployed testnet values

- token contract:
  - current x402 demo asset:
    - `CBIELTK6YBZJU5UP2WWQEUCYKLPU6AUNZ2BQ4WWFEIE3USCIHMXQDAMA`
- splitter contract:
  - `CCTVCH6BUWS4XESFHK4BHKK35KY56PQ5PGSIQHKJBNYMTWXXGXLYKMBD`
- single-recipient payee account:
  - `GADQAPRDK6V5GDMD4W5IBQ36FZ5WM7T265GXLTLYMANS3OAYCDITVHQE`

Tracked non-secret example values are in:

- [../../../examples/env/stellar-testnet-demo-values.example](../../../examples/env/stellar-testnet-demo-values.example)

For the current x402 demo:

- direct single-recipient payment still exists for simple routes
- split-settled routes use `payment_splitter`
- Apache advertises the splitter contract as `payTo`
- the provider settles through the facilitator first, then prepares a Soroban `settle_balance` invocation locally

For split-enabled Apache routes, the relevant directives are:

- `X402SplitMode multi`
- `X402SplitterContract <deployed_payment_splitter>`
- repeated `X402Stakeholder` allocations that sum to `10000`
- `X402StellarLocalBackend inprocess`
- `X402StellarConfigDir /etc/apache2/x402-stellar`
- `X402StellarSourceAccount <identity_name>`

Current live execution shape:

1. The buyer pays the route challenge normally.
2. The facilitator `/settle` call gates access.
3. If split mode is enabled, the provider constructs and signs the `payment_splitter.settle_balance(...)` transaction before the response is released.
4. Apache returns protected content with:
   - `PAYMENT-RESPONSE`
   - `X402-Split-Transaction-Hash`
5. The signed split transaction is submitted and confirmed asynchronously.
6. Confirmation state is recorded in `/var/lib/x402/credits.db` in `split_tx_audit`.

`split_tx_audit` tracks:

- `payment_identifier`
- `split_tx_hash`
- `status`
- `prepared_at_ms`
- `submitted_at_ms`
- `confirmed_at_ms`

This means split settlement is now decoupled from access latency while still giving the buyer a stable transaction hash to track.
