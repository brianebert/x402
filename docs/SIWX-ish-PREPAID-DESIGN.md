# Stellar Repeat-Access And Prepaid Credits

This document describes the current prepaid and repeat-access model in this
repo. It is intentionally scoped to implemented behavior.

## Current Route Shape

Canonical protected route:

- `/app/foo`

Purchase routes:

- `/price`
- `/priceX2`
- `/priceX10`
- `/priceX100`

Each purchase route buys credits for the canonical protected route.

## Purchase Behavior

For a purchase route:

1. an unpaid request returns `402 Payment Required`
2. the challenge advertises the exact route amount
3. the buyer retries with `PAYMENT-SIGNATURE`
4. the server settles once through the facilitator
5. the server stores credits in SQLite
6. the server forwards internally to `/app/foo`
7. the forwarded response serves content and includes:
   - `PAYMENT-RESPONSE`
   - `X402-Stellar-Auth-Challenge`

Current effective purchase sizes:

- `/price` -> `1`
- `/priceX2` -> `2`
- `/priceX10` -> `10`
- `/priceX100` -> `100`

## Credit Storage

Credits are durable and server-side.

Storage:

- SQLite

Configured by:

- `X402CreditDBPath`

Current tables involved in the repeat-access flow:

- `credit_bucket`
- `auth_challenge`
- `auth_session`

## Repeat Access

Repeat access uses the repo’s private Stellar signed-challenge flow.

Flow:

1. server returns `X402-Stellar-Auth-Challenge`
2. buyer signs that challenge with the Stellar key
3. buyer sends `X402-Stellar-Auth`
4. server verifies the signature
5. server checks remaining credits
6. server decrements one credit
7. server serves the protected route

This is not standard SIWX. The filename keeps the `SIWX-ish` label only to
signal the conceptual resemblance.

## Current Limits

- repeat access is Stellar-specific
- repeat access is not standards-based SIWX
- credits are single-host because storage is SQLite
