# x402+ Architecture

## Overview

This repo implements an Apache-native Stellar `x402` server with:

- facilitator-backed exact-payment settlement
- durable prepaid credits in SQLite
- optional split settlement through a Soroban splitter contract

The core live route set is:

- `/app/foo`
- `/price`
- `/priceX2`
- `/priceX10`
- `/priceX100`

With `X402_ENABLE_SPLIT=1`, those same routes switch from single-recipient settlement to split settlement. A separate split-only route is no longer the main model.

## Main Components

### Apache module

Primary file:

- `apache/mod_x402.c`

Responsibilities:

- parses Apache directives into route policy
- emits `PAYMENT-REQUIRED` and `PAYMENT-RESPONSE`
- stores and consumes prepaid credits in SQLite
- issues and verifies the private Stellar repeat-access challenge
- forwards prepaid purchase routes internally to `/app/foo/`
- records split-settlement audit state in SQLite

### Shared x402 layer

Primary files:

- `core/x402_core.c`
- `core/x402_provider.h`

Responsibilities:

- shared policy validation
- x402 request/response JSON construction
- common provider ABI types

### Stellar provider

Primary files:

- `providers/stellar/stellar_provider.cpp`
- `providers/stellar/stellar_provider.h`

Responsibilities:

- builds Stellar payment requirements
- calls facilitator `/verify` and `/settle`
- prepares split-settlement Soroban transactions
- submits and confirms split transactions asynchronously

### Soroban contracts

Primary location:

- `contracts/stellar/soroban/contracts/`

Current contracts:

- `payment_receiver`
- `payment_splitter`

`payment_splitter` is the active split-settlement contract path.

## Route Behavior

### Direct protected content

Route:

- `/app/foo`

Flow:

1. unpaid request returns `402` with `PAYMENT-REQUIRED`
2. buyer retries with `PAYMENT-SIGNATURE`
3. provider verifies and settles through the facilitator
4. Apache returns protected content and `PAYMENT-RESPONSE`

When split is enabled:

- the route advertises the splitter contract as `payTo`
- Apache returns `X402-Split-Transaction-Hash`
- split submission and confirmation continue asynchronously

### Prepaid purchase routes

Routes:

- `/price`
- `/priceX2`
- `/priceX10`
- `/priceX100`

Flow:

1. unpaid request returns `402`
2. buyer pays once on the purchase route
3. Apache stores any remaining credits in SQLite
4. Apache forwards internally to `/app/foo/`
5. response includes:
   - `PAYMENT-RESPONSE`
   - `X402-Stellar-Auth-Challenge`

## Credit and Auth Model

Credits are durable and server-side.

SQLite tables used by the repeat-access path:

- `credit_bucket`
- `auth_challenge`
- `auth_session`

Repeat access works by:

1. server issues `X402-Stellar-Auth-Challenge`
2. buyer signs `messageBase64` with the Stellar key
3. buyer sends `X402-Stellar-Auth`
4. server verifies the signature
5. server consumes one credit

This is a repo-specific Stellar extension, not standard SIWX.

## Split Settlement Model

For split-enabled routes:

1. facilitator `/settle` still gates access
2. provider prepares and signs the Soroban `settle_balance(...)` transaction before the response is released
3. Apache returns:
   - protected content
   - `PAYMENT-RESPONSE`
   - `X402-Split-Transaction-Hash`
4. provider submits and confirms the split transaction asynchronously
5. Apache/provider record progress in SQLite

Split tracking tables:

- `async_split_trace`
- `split_tx_audit`

`split_tx_audit` stores:

- `payment_identifier`
- `split_tx_hash`
- `status`
- `prepared_at_ms`
- `submitted_at_ms`
- `confirmed_at_ms`

## Deployment Shape

The normal deployment shape is:

- build with `make`
- install with `scripts/host-admin-install.sh`
- run Apache with facilitator-backed Stellar settlement
- keep prepaid and split audit state in `/var/lib/x402/credits.db`

For host creation, use `DO_AGENT.md`.

## Known Limits

- SQLite is single-host persistence
- repeat access is a private Stellar extension
- split settlement still depends on facilitator `/settle` first
- split submission is asynchronous but still in-process in the Apache module/provider runtime
