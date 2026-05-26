# [x402+](https://www.x402.org) Apache Module with [Stellar](https://github.com/stellar) Payment Provider

## This repo is:
- core x402 HTTP payment flow for Stellar exact-payment routes
- plus private Stellar extensions for:
  - signed prepaid repeat access
  - durable prepaid credit storage
  - instant split settlement

An Apache2 module is chosen to execute the x402 protocol. The `+` in `x402+` recognizes two features added to `x402`:
- [SIWX](https://docs.x402.org/extensions/sign-in-with-x) is not implemented for Stellar yet, but I really like SIWX so `x402+` immitates SIWX with Stellar.
- `x402+` comes configured to split `x402` payments. In the demos the server calls for the split concurrently with serving the content paid for. Payment splits are established with Apache2 .conf files, easily splitting payments in real time between server operator and site content sellers.

This directory contains the current implementation slice of an Apache-native `x402+` design:
- `core/x402_provider.h`
  - shared policy types and provider ABI
- `core/x402_core.c`
  - portable policy validation, stakeholder split math, and first-pass x402 message builders
- `providers/stellar/stellar_provider.cpp`
  - Stellar provider stub that targets Soroban and SAC settlement patterns
- `apache/mod_x402.c`
  - Apache module with route directives, x402 challenge generation, and provider dispatch
- `apache/mod_x402_stellar.cc`
  - Apache-visible Stellar provider hook stub

## Try the public demo

```sh
# Clome the repo locally and install dependencies from @x402, @Stellar, and undici
git clone https://github.com/brianebert/x402inside x402
cd x402/examples
npm i

# Create testnet accounts for buyer, 2 split receivers, and a server account to run splits
# The split accounts are saved for later, when you set up your own server
# Use the buyer account to test against 64.23.244.67
node scripts/make-split-demo-accounts.mjs
```
### Don't forget to arm your `x402` buyer account with USDC from the circle [faucet](https://faucet.circle.com/)!!!
```sh
cat .demo-accounts/split-server/split-accounts.json
# Use buyer.secretKey in place of 'S12345...DEF'
STELLAR_PRIVATE_KEY='S12345...DEF'
# To run tests against a testnet server at 64.23.244.67
# Buy single access, view decoded PAYMENT-REQUIRED and PAYMENT-SIGNATURE
./scripts/raw-stellar-two-step.sh 64.23.244.67
```
You can also pre-pay for faster access to the content
```sh
STELLAR_PRIVATE_KEY='S12345...DEF'
# Where N = 2|10|100, buy N accesses to /app/foo and call it  M times
# node buyers/buyer-stellar-prepaid.mjs http://64.23.244.67/priceX N M
# Buys 2 accesses and calls the protected endpoint 2 times
node buyers/buyer-stellar-prepaid.mjs http://64.23.244.67/priceX 2 2
```
The server at 64.23.244.67 is set up to split payments 70/30 between accounts [GAQH3...LHEBX](https://horizon-testnet.stellar.org/accounts/GAQH3VXDLXCUESK4CGC77BBA5X4CFSR2HAWTVXYAC2H6AHI6BE7LHEBX) and [GACTC...WJ5P2](https://horizon-testnet.stellar.org/accounts/GACTCLSHLLAPVXEATOTMR6ZVKRGEJYPO6RDMZXJS76BXRBCAH5YWJ5P2). Both scripts display response header `X402-Split-Transaction-Hash: <hash>`. You can use a tool like [Laboratory](https://lab.stellar.org/endpoints/horizon/operations/transaction?$=network$id=testnet&label=Testnet&horizonUrl=https:////horizon-testnet.stellar.org&rpcUrl=https:////soroban-testnet.stellar.org&passphrase=Test%20SDF%20Network%20/;%20September%202015;;) to view the split payments. The shell script will show you a 7¢/3¢ split and the node script will show the 70/30 split of N X 10¢.


## Run your own server
### Modify an Apache2 http server
  - Clone this repo into /srv/x402 and cd to the directory
  - Copy .env.example to .env and set up for your accounts
    - set X402_SERVER_NAME to your name or ip address
    - double check the value of X402_DESCRIPTION is quoted
    - if not splitting, set X402_PAY_TO to a testnet account that can receive USDC
    - if you wish to test split payments:
      - append the contents of your local examples/.demo-accounts/split-server/split-server.env to your server's /srv/x402/.env
      - copy your local examples/.demo-accounts/split-server/operator_demo_split.toml to your server as /etc/apache2/x402-stellar/identity/operator_demo_split.toml
    - now you must either:
      - follow the [manual installation](docs/MANUAL_INSTALLATION.md) instructions
      - run X402_STELLAR_SOURCE_SECRET_KEY=S123...DEF ./scripts/host-admin-install.sh
        - X402_STELLAR_SOURCE_SECRET_KEY value is output by scripts/make-split-demo-accounts.mjs
### Or give a DigitalOcean access token to an agent.
  - Copy .do_access.example to .do_access, and paste your token where 'replace-me' appears.
  - The file [DO_AGENT](./DO_AGENT.md) instructs agents to build a 1 cpu, 2 GB DigitalOcean droplet with at least 25 GB of SSD, load Apache2 onto it, do some testing and ask whether you want to continiue loading x402+.
    - You can ssh into your new droplet and proceed with instructions above
    - Or you can let your agent finish loading `x402+` on your new server.
  - The $12/month droplet is more than sufficient for x402 testing and is easily grown. 
  - The new server is not firewalled.
    - The demo server running at 64.23.244.67 is open on ports 80 and 443, with ssh via its private ip address.

#### now change the ip address when calling the test scripts to run off your own server.


# Demo features

## Soroban Receiver Contract

A Soroban contract workspace [contracts/stellar/soroban](contracts/stellar/soroban) contains:

- `payment_receiver` for single-recipient settlement
- `payment_splitter` for stakeholder fan-out settlement

## Durable Credits

Prepaid request credits have a durable SQLite-backed implementation.

Config:

- `X402CreditDBPath`

Server path:

- `/var/lib/x402/credits.db`

Scope:

- server or vhost config

Because the current official SIWX standard does not include Stellar, the live repeat-access path uses a private Stellar-specific signed-challenge extension instead:

- challenge advertises `extensions["stellar-signin"]`
- unpaid or exhausted-credit responses return `X402-Stellar-Auth-Challenge`
- paid responses also return the next `X402-Stellar-Auth-Challenge`
- repeat requests spend credits by signing the challenge and sending `X402-Stellar-Auth`

This requires a fresh wallet signature for each repeat-access request, while credit TTL continues to enforce "use or lose" expiration on the server side.

## Variable Split Configuration

Variable split sets are already supported at the Apache config layer. The current provider passes a server-built split array into the Soroban splitter invocation at settlement time, so the contract can accommodate different split schedules by route without hardcoding one split table on-chain.

Important boundary:

- split definitions are server-controlled
- buyer requests do not supply their own split list

## Split-Payment Direction

Current live split-route status:

- `payment_splitter` v2 is deployed at CCTVCH6BUWS4XESFHK4BHKK35KY56PQ5PGSIQHKJBNYMTWXXGXLYKMBD
- Any Stellar x402 buyer can complete payment against that route
- The Apache module settles through the facilitator, then invokes `settle_balance` through its Soroban backend

## Reference docs
Start with [ARCHITECTURE.md](./ARCHITECTURE.md) and [OPERATIONS.md](./OPERATIONS.md).
