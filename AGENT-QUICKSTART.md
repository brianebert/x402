# Agent Quickstart

This file is for a fresh agent entering the rooted `x402+` repo.

Use these files first:

- `DO_AGENT.md`
- `OPERATIONS.md`
- `README.md`

## Default Assumptions

Assume:

- this repo is the source of truth
- the default branch is `main`
- the primary deployment path is:
  - `scripts/host-admin-install.sh`
- the default practical payment path is:
  - Stellar testnet
  - single-recipient
  - facilitator-backed

## Current Practical Test Values

- `X402_ASSET=CBIELTK6YBZJU5UP2WWQEUCYKLPU6AUNZ2BQ4WWFEIE3USCIHMXQDAMA`
- `X402_PAY_TO=GADQAPRDK6V5GDMD4W5IBQ36FZ5WM7T265GXLTLYMANS3OAYCDITVHQE`
- protected route example:
  - `/app/foo`
- purchase routes:
  - `/price`
  - `/priceX2`
  - `/priceX10`
  - `/priceX100`

## First Checks

Build locally:

```sh
make
```

If deployment work is involved, verify the installer assumptions in:

- `.env.example`
- `scripts/host-admin-install.sh`

For a plain HTTP by IPv4 install, remember:

- `X402_SERVER_NAME` may be auto-detected
- `000-default.conf` is disabled by the installer

Expected first smoke test after install:

```sh
curl -i http://<host-ip>/app/foo
```

Expected result:

- `402 Payment Required`

## If You Need A New DigitalOcean Host

Use:

- `DO_AGENT.md`
- `OPERATIONS.md`

Before proceeding, the operator should create:

- `.do_access`

from:

- `.do_access.example`

and place `DIGITAL_OCEAN_TOKEN` there.

Keep deployment artifacts local-only under:

- `do_artifacts/`

Do not commit:

- private keys
- cloud tokens
- funded wallet secrets
- droplet API responses

## If You Need Buyer Tests

Buyer assets live under:

- `examples/buyers/`
- `examples/env/`
- `examples/scripts/`

Typical local buyer flow:

```sh
cd examples
npm install
cp env/.env.stellar.example .env
# fill in STELLAR_PRIVATE_KEY locally
npm run buyer:stellar -- http://<host-ip>/app/foo
```

For more detail, continue with:

- `OPERATIONS.md`
- `examples/buyers/README.md`
- `examples/scripts/README.md`
- `docs/design/SIWX-ish-PREPAID-DESIGN.md`
