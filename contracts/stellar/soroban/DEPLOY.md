# Deploying The First-Pass Receiver Contract

This is the repeatable path for a real Stellar testnet demo using a locally prepared funded account file. Use the tracked examples under `examples/env/` as templates and keep the real funded secret file untracked.

## Preconditions

- local `stellar` CLI installed
- local Rust toolchain installed
- testnet identity funded
- `wasm32-unknown-unknown` target installed

## 1. Load the funded testnet account

```sh
cd examples
set -a
. ./stellar-testnet-account.env
set +a
```

## 2. Add the deployer identity to the local Stellar CLI config

```sh
stellar keys add benobody_deployer --secret-key "$STELLAR_TESTNET_SECRET_KEY" \
  --config-dir examples/.stellar
```

## 3. Build the receiver contract

```sh
rustup target add wasm32-unknown-unknown
cd contracts/stellar/soroban
stellar contract build
```

## 4. Deploy the receiver contract

```sh
stellar contract deploy \
  --network testnet \
  --config-dir ../../../examples/.stellar \
  --source-account benobody_deployer \
  --wasm target/wasm32-unknown-unknown/release/payment_receiver.wasm \
  --alias benobody_payment_receiver
```

## 4b. Deploy the splitter contract

```sh
stellar contract deploy \
  --network testnet \
  --config-dir ../../../examples/.stellar \
  --source-account benobody_deployer \
  --wasm target/wasm32-unknown-unknown/release/payment_splitter.wasm \
  --alias benobody_payment_splitter
```

## 5. Create or choose a real token contract

For the fastest controlled demo, prefer a token contract you control over guessing at a shared public test asset.

Options:

- deploy your own SEP-41 token contract and mint balances for buyer testing
- or wrap a classic test asset with `stellar contract asset deploy`

Example SAC deploy if you already have a classic asset issuer:

```sh
stellar contract asset deploy \
  --network testnet \
  --config-dir ../../../examples/.stellar \
  --source-account benobody_deployer \
  --asset 'CODE:G...ISSUER'
```

## Current deployed testnet values

- classic asset:
  - `BENO:GA7XEDQX4VSVD4BXCJHPVW6GKZQT5HNGIIIZKJNNUAJJON4JSBJRC6O2`
- token contract:
  - `CBLPJLEI6XKF26PLUPD4THCQGF5ZVBMAWAY3M5MX3B6G6OEPQCNAJNGY`
- receiver contract:
  - `CC64UBHYKBXUIPUDSY3Q7F6KLHRMYATW5KGSILYGBMZOMKD7N3DUWNOZ`
- recipient:
  - `GADQAPRDK6V5GDMD4W5IBQ36FZ5WM7T265GXLTLYMANS3OAYCDITVHQE`

Tracked non-secret example values are in:

- [../../../examples/env/stellar-testnet-demo-values.example](../../../examples/env/stellar-testnet-demo-values.example)

## 6. Update Apache config after deployment

Replace placeholders in your TLS vhost, for example `/etc/apache2/sites-available/<your-domain>-ssl.conf`:

- `X402Asset CBLPJLEI6XKF26PLUPD4THCQGF5ZVBMAWAY3M5MX3B6G6OEPQCNAJNGY`
- `X402PayTo GADQAPRDK6V5GDMD4W5IBQ36FZ5WM7T265GXLTLYMANS3OAYCDITVHQE`
- `X402FacilitatorURL https://channels.openzeppelin.com/x402/testnet`
- `X402FacilitatorAPIKeyFile /etc/apache2/x402-secrets/facilitator.key`

For the first-pass receiver demo:

- set `X402SplitMode single`
- use a real recipient with `X402PayTo`
- keep the receiver contract for later contract-mediated settlement work

For the split-payment design:

- set `X402SplitMode multi`
- set `X402SplitterContract` to the deployed `payment_splitter` contract id
- keep `X402Asset` on a supported token contract such as testnet USDC
- declare stakeholder basis-point splits with `X402Stakeholder`
- keep total route price as one logical amount; the contract performs the fan-out

## Notes

- The current best path for a real Stellar x402 buyer flow is the live single-recipient or split route described in `examples/REAL-STELLAR-DEMO.md`.
- The receiver contract above remains available, but it is not the shortest route to the current truthful x402 success case.
- The split route now uses `payment_splitter` with `X402SplitMode multi`; future work is about extending that model, not first deployment.
