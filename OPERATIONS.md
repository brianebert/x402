# x402+ Operations

## Scope

This file covers the current Stellar `x402+` build, deploy, configure, test, and inspect workflow.

For host creation, use [DO_AGENT.md](DO_AGENT.md).

## Prerequisites

Local native build dependencies:

- C compiler
- C++ compiler
- `libcurl`
- `openssl`
- `libsodium`
- `sqlite3`
- Apache dev headers

Node demo dependencies:

```sh
cd examples
npm install
```

## Build

`make` is a partial local build check. It currently compiles:

- `core/x402_core.o`
- `providers/stellar/stellar_provider.o`

It does not build `apache/mod_x402.c` or link `apache/.libs/mod_x402.so`.

Local build check:

```sh
make
```

To build and install the Apache module, use either:

- `scripts/host-admin-install.sh`
- the manual compile/link commands in [docs/MANUAL_INSTALLATION.md](docs/MANUAL_INSTALLATION.md)

## Deploy

Active host layout:

- repo: `/srv/x402`
- module: `/usr/lib/apache2/modules/mod_x402.so`
- site config: `/etc/apache2/sites-available/x402.conf`
- credit DB: `/var/lib/x402/credits.db`
- Stellar config dir: `/etc/apache2/x402-stellar`

Canonical install/update path:

```sh
cd /srv/x402
sudo X402_ENV_FILE=/srv/x402/.env ./scripts/host-admin-install.sh
```

If you need a hard module refresh after changing C/C++ code, prefer a full Apache restart:

```sh
sudo systemctl restart apache2
```

## Configuration Model

Canonical protected route:

- `/app/foo`

Prepaid purchase routes:

- `/price`
- `/priceX2`
- `/priceX10`
- `/priceX100`

Single-recipient mode uses:

- `X402PayTo <recipient>`

Split mode uses:

- `X402SplitMode multi`
- `X402SplitterContract <contract>`
- repeated `X402Stakeholder <name> <bps> <destination>`
- `X402StellarLocalBackend inprocess`
- `X402StellarConfigDir /etc/apache2/x402-stellar`
- `X402StellarSourceAccount <identity_name>`

With `X402_ENABLE_SPLIT=1`, the installer converts the existing route family to split settlement rather than creating a separate split-only route.

Facilitator bearer keys should be file-backed:

- `/etc/apache2/x402-secrets/facilitator.key`

## Buyer Tests

Direct paid request:

```sh
cd examples
npm run buyer:stellar -- http://<host>/app/foo/
```

Prepaid purchase plus repeat:

```sh
cd examples
npm run buyer:stellar:prepaid -- http://<host>/priceX 2 2
```

Raw two-step paid flow:

```sh
cd examples
./scripts/raw-stellar-two-step.sh http://<host>/app/foo/
```

Bad-payment limiter test:

```sh
cd examples
npm run test:stellar:bad-payment -- http://<host>/priceX2
```

## Repeat Access

Repeat access uses the private Stellar auth flow:

- response header:
  - `X402-Stellar-Auth-Challenge`
- request header:
  - `X402-Stellar-Auth`

Flow:

1. buyer pays once
2. server returns `X402-Stellar-Auth-Challenge`
3. buyer signs `messageBase64`
4. buyer sends `X402-Stellar-Auth`
5. server consumes one SQLite credit

## Split Settlement

For split-enabled routes:

1. facilitator `/settle` gates access
2. provider prepares and signs the Soroban split transaction before the response is released
3. Apache returns:
   - protected content
   - `PAYMENT-RESPONSE`
   - `X402-Split-Transaction-Hash`
4. provider submits and confirms the split transaction asynchronously
5. state is recorded in SQLite

Relevant SQLite tables:

- `credit_bucket`
- `auth_challenge`
- `auth_session`
- `abuse_counter`
- `async_split_trace`
- `split_tx_audit`

Actual use:

- `credit_bucket`
  - durable prepaid balances by payer and credit scope
- `auth_challenge`
  - one-time Stellar repeat-access challenges
- `auth_session`
  - session-style auth state when issued
- `abuse_counter`
  - route-aware unpaid, bad-payment, and bad-prepaid-auth cooldown counters
- `async_split_trace`
  - split execution trace rows
- `split_tx_audit`
  - prepared/submitted/confirmed async split transaction state

Expired rows are pruned lazily from the request path:

- expired `credit_bucket`
- expired `auth_challenge`
- expired `auth_session`

## Inspect State

List recent credit buckets:

```sh
ssh -i <ssh-key> <ssh-user>@<ssh-host> "
  sudo sqlite3 -line /var/lib/x402/credits.db \
  'select payer, credit_scope, remaining, expires_at, updated_at from credit_bucket order by updated_at desc limit 20;'
"
```

List recent auth challenges:

```sh
ssh -i <ssh-key> <ssh-user>@<ssh-host> "
  sudo sqlite3 -line /var/lib/x402/credits.db \
  'select challenge_token, credit_scope, request_path, issued_at, expires_at, used_at from auth_challenge order by issued_at desc limit 20;'
"
```

List split audit rows:

```sh
ssh -i <ssh-key> <ssh-user>@<ssh-host> "
  sudo sqlite3 -line /var/lib/x402/credits.db \
  'select payment_identifier, split_tx_hash, status, prepared_at_ms, submitted_at_ms, confirmed_at_ms from split_tx_audit order by updated_at_ms desc limit 20;'
"
```

## Reset State

Targeted credit delete example:

```sh
ssh -i <ssh-key> <ssh-user>@<ssh-host> "
  sudo sqlite3 /var/lib/x402/credits.db \
  \"delete from credit_bucket where payer = 'GEXAMPLEPAYER' and credit_scope = 'stellar|/app/foo|CBIELTK6YBZJU5UP2WWQEUCYKLPU6AUNZ2BQ4WWFEIE3USCIHMXQDAMA|stellar:testnet';\"
"
```

## Troubleshooting

Apache restart issues:

```sh
sudo apachectl configtest
sudo systemctl status apache2 --no-pager -l
sudo tail -n 100 /var/log/apache2/error.log
```

Missing `PAYMENT-REQUIRED`:

- module not loaded
- route config not enabled
- Apache returned an error before module handling

Check:

```sh
sudo apachectl -M | grep x402
```

Facilitator rejects payment:

- wrong amount
- wrong asset
- wrong `payTo`
- stale facilitator key
- buyer lacks testnet funds

Split payment returns `200` but split tracking is missing:

- verify Apache was fully restarted after deploying module code
- check `/etc/apache2/sites-available/x402.conf`
- check `split_tx_audit` in `/var/lib/x402/credits.db`

Repeat access fails:

- expired credit
- already-used challenge
- wrong challenge path
- wrong signed message

## Resume Files

If resuming work, start with:

- [README.md](README.md)
- [AGENT-QUICKSTART.md](AGENT-QUICKSTART.md)
- [ARCHITECTURE.md](ARCHITECTURE.md)
- [DO_AGENT.md](DO_AGENT.md)
