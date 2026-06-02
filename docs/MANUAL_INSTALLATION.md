# Manual Installation

This guide is for an operator who wants to install and configure the Apache `x402+` module without using the installer scripts.

It covers:

- building the module
- installing it into Apache
- creating the required host directories
- configuring single-recipient and split-settled routes manually
- verifying the live route behavior

This guide assumes:

- Ubuntu or another Apache 2.4 host with similar paths
- a working repo checkout at `/srv/x402`
- Stellar testnet usage

Installer equivalents:

- `scripts/host-system-install.sh` performs package install, module build/install, runtime directory setup, facilitator key install, split signer install, and `/etc/apache2/conf-available/x402-splits.conf` generation.
- `scripts/host-vhost-install.sh` creates document roots and Apache vhost/route config.
- `scripts/host-admin-install.sh` is a compatibility wrapper that runs both phases in order.

## 1. Build Prerequisites

Install the native build dependencies your distro requires for:

- `apache2-dev`
- `build-essential`
- `pkg-config`
- `libcurl`
- `openssl`
- `libsodium`
- `sqlite3`

The build also uses vendored headers already in the repo:

- `third_party/xdrpp/`

## 2. Build The Module

`make` by itself is not enough for manual Apache installation. It currently builds only:

- `core/x402_core.o`
- `providers/stellar/stellar_provider.o`

It does not compile `apache/mod_x402.c` or link `apache/.libs/mod_x402.so`.

From the repo root, build the Apache module with the same compile/link steps the installer uses:

```sh
cd /srv/x402
make

cc -fPIC -I. -I.. -I/usr/include/apache2 -I/usr/include/apr-1.0 \
  -Wall -Wextra -Werror -Wno-error=cpp -Wno-missing-field-initializers -std=c11 \
  -c core/x402_core.c -o core/x402_core.apache.o

g++ -fPIC -I. -I.. -Iproviders/stellar -Iproviders/stellar/schemas -Ithird_party \
  -Wall -Wextra -Werror -Wno-unused-parameter -std=c++17 \
  $(pkg-config --cflags openssl libsodium 2>/dev/null) \
  -c providers/stellar/stellar_provider.cpp -o providers/stellar/stellar_provider.apache.o

cc -fPIC -I. -I.. -I/usr/include/apache2 -I/usr/include/apr-1.0 \
  -Wall -Wextra -Werror -Wno-error=cpp -Wno-missing-field-initializers -std=c11 \
  -c apache/mod_x402.c -o apache/mod_x402.apache.o

mkdir -p apache/.libs
g++ -shared -o apache/.libs/mod_x402.so \
  apache/mod_x402.apache.o core/x402_core.apache.o providers/stellar/stellar_provider.apache.o \
  -lcurl $(pkg-config --libs openssl libsodium 2>/dev/null) -lsqlite3
```

Expected outputs include:

- `apache/.libs/mod_x402.so`
- `core/x402_core.o`
- `providers/stellar/stellar_provider.o`

## 3. Install The Module

Copy the built module into Apache’s module directory:

```sh
sudo install -m 644 apache/.libs/mod_x402.so /usr/lib/apache2/modules/mod_x402.so
```

Create an Apache module load file if you do not already have one:

```sh
cat <<'EOF' | sudo tee /etc/apache2/mods-available/x402.load >/dev/null
LoadModule x402_module /usr/lib/apache2/modules/mod_x402.so
EOF
```

Enable it:

```sh
sudo a2enmod x402
```

## 4. Create Required Directories

Document root example:

```sh
sudo install -d -m 755 /var/www/x402
sudo install -d -m 755 /var/www/x402/app
sudo install -d -m 755 /var/www/x402/app/foo
sudo install -d -m 755 /var/www/x402/price
sudo install -d -m 755 /var/www/x402/priceX2
sudo install -d -m 755 /var/www/x402/priceX10
sudo install -d -m 755 /var/www/x402/priceX100
```

Write example content:

```sh
printf '%s\n' 'yoo hoo' | sudo tee /var/www/x402/app/foo/index.html >/dev/null
printf '%s\n' '<html><body>x402 purchase route</body></html>' | sudo tee /var/www/x402/price/index.html >/dev/null
printf '%s\n' '<html><body>x402 purchase route</body></html>' | sudo tee /var/www/x402/priceX2/index.html >/dev/null
printf '%s\n' '<html><body>x402 purchase route</body></html>' | sudo tee /var/www/x402/priceX10/index.html >/dev/null
printf '%s\n' '<html><body>x402 purchase route</body></html>' | sudo tee /var/www/x402/priceX100/index.html >/dev/null
```

Create runtime directories:

```sh
sudo install -d -m 755 /var/lib/x402
sudo install -d -m 750 -o root -g www-data /etc/apache2/x402-secrets
sudo install -d -m 750 -o root -g www-data /etc/apache2/x402-stellar
sudo install -d -m 750 -o root -g www-data /etc/apache2/x402-stellar/identity
```

Create the SQLite DB file so Apache can write it:

```sh
sudo install -m 640 -o www-data -g www-data /dev/null /var/lib/x402/credits.db
```

SQLite is used for:

- durable prepaid balances in `credit_bucket`
- repeat-access challenges in `auth_challenge`
- session state in `auth_session`
- abuse cooldowns in `abuse_counter`
- async split traces in `async_split_trace`
- split transaction audit rows in `split_tx_audit`

Expired credit and auth rows are cleaned lazily from the request path.

## 5. Facilitator Secret

Place the facilitator bearer key in a root-managed file:

```sh
sudo install -m 640 -o root -g www-data facilitator.key /etc/apache2/x402-secrets/facilitator.key
```

Apache reads this with:

- `X402FacilitatorAPIKeyFile /etc/apache2/x402-secrets/facilitator.key`

## 6. Split Signer Identity

For split settlement with the in-process Soroban backend, place the signer file here:

- `/etc/apache2/x402-stellar/identity/<identity_name>.toml`

Example:

```toml
secret_key = "S..."
```

Install it:

```sh
sudo install -m 640 -o root -g www-data operator_demo_split.toml \
  /etc/apache2/x402-stellar/identity/operator_demo_split.toml
```

This file is the signer material for the local split transaction. It is not where split percentages are configured.

## 7. Minimal Apache Site Config

Create `/etc/apache2/sites-available/x402.conf`:

```apache
<VirtualHost *:80>
    ServerName 64.23.244.67
    DocumentRoot /var/www/x402

    <Directory /var/www/x402>
        Require all granted
        Options Indexes FollowSymLinks
        AllowOverride None
    </Directory>

    <Location "/app/foo">
        X402 On
        X402Scheme exact
        X402Network stellar:testnet
        X402Asset CBIELTK6YBZJU5UP2WWQEUCYKLPU6AUNZ2BQ4WWFEIE3USCIHMXQDAMA
        X402Amount 1000000
        X402Description "Access to foo"
        X402MimeType text/html
        X402Mechanism stellar
        X402SettlementMode facilitator
        X402FacilitatorURL https://channels.openzeppelin.com/x402/testnet
        X402FacilitatorAPIKeyFile /etc/apache2/x402-secrets/facilitator.key
        X402TimeoutSeconds 30
        X402PaymentIdentifier required
        X402PayTo GADQAPRDK6V5GDMD4W5IBQ36FZ5WM7T265GXLTLYMANS3OAYCDITVHQE
        X402Prepay On
        X402PrepayMultiplierMax 100
        X402CreditScope payer-route
        X402CreditTTLSeconds 86400
    </Location>

    <Location "/price">
        X402 On
        X402Scheme exact
        X402Network stellar:testnet
        X402Asset CBIELTK6YBZJU5UP2WWQEUCYKLPU6AUNZ2BQ4WWFEIE3USCIHMXQDAMA
        X402Amount 1000000
        X402Description "Buy 1 access to foo"
        X402MimeType text/html
        X402Mechanism stellar
        X402SettlementMode facilitator
        X402FacilitatorURL https://channels.openzeppelin.com/x402/testnet
        X402FacilitatorAPIKeyFile /etc/apache2/x402-secrets/facilitator.key
        X402TimeoutSeconds 30
        X402PaymentIdentifier required
        X402PayTo GADQAPRDK6V5GDMD4W5IBQ36FZ5WM7T265GXLTLYMANS3OAYCDITVHQE
        X402Prepay On
        X402PrepayMultiplierMax 100
        X402CreditScope payer-route
        X402CreditTTLSeconds 86400
        X402CreditsIssued 1
        X402ForwardTo /app/foo/
    </Location>

    <Location "/priceX2">
        X402 On
        X402Scheme exact
        X402Network stellar:testnet
        X402Asset CBIELTK6YBZJU5UP2WWQEUCYKLPU6AUNZ2BQ4WWFEIE3USCIHMXQDAMA
        X402Amount 2000000
        X402Description "Buy 2 accesses to foo"
        X402MimeType text/html
        X402Mechanism stellar
        X402SettlementMode facilitator
        X402FacilitatorURL https://channels.openzeppelin.com/x402/testnet
        X402FacilitatorAPIKeyFile /etc/apache2/x402-secrets/facilitator.key
        X402TimeoutSeconds 30
        X402PaymentIdentifier required
        X402PayTo GADQAPRDK6V5GDMD4W5IBQ36FZ5WM7T265GXLTLYMANS3OAYCDITVHQE
        X402Prepay On
        X402PrepayMultiplierMax 100
        X402CreditScope payer-route
        X402CreditTTLSeconds 86400
        X402CreditsIssued 2
        X402ForwardTo /app/foo/
    </Location>
</VirtualHost>
```

Add analogous `priceX10` and `priceX100` blocks if needed.

## 8. Split Mode Apache Config

Split payout control can be placed in Apache serverwide config so the server operator owns the splitter contract and operator payout. Create `/etc/apache2/conf-available/x402-splits.conf`:

```apache
X402SplitMode multi
X402SplitterContract CCTVCH6BUWS4XESFHK4BHKK35KY56PQ5PGSIQHKJBNYMTWXXGXLYKMBD
X402Stakeholder server_operator 300 <operator_account>
```

Then enable it:

```sh
sudo a2enconf x402-splits
```

When this file is enabled, its split mode and splitter contract apply to all x402 routes. Route or vhost config must not override them. Route or vhost config may add publisher stakeholders, and the combined basis points across systemwide and local stakeholders must sum to `10000`.

With the installer, use:

- `X402_OPERATOR_STAKEHOLDER_1_NAME`
- `X402_OPERATOR_STAKEHOLDER_1_BPS`
- `X402_OPERATOR_STAKEHOLDER_1_DEST`
- `X402_PUBLISHER_STAKEHOLDER_1_NAME`
- `X402_PUBLISHER_STAKEHOLDER_1_BPS`
- `X402_PUBLISHER_STAKEHOLDER_1_DEST`

Add more stakeholders by incrementing the index up to `X402_MAX_STAKEHOLDERS`, default `16`.

Use route-specific publisher stakeholders when one generated route needs a different payout list:

- `X402_ROUTE_APP_FOO_STAKEHOLDER_1_*`
- `X402_ROUTE_PRICE_STAKEHOLDER_1_*`
- `X402_ROUTE_PRICEX2_STAKEHOLDER_1_*`
- `X402_ROUTE_PRICEX10_STAKEHOLDER_1_*`
- `X402_ROUTE_PRICEX100_STAKEHOLDER_1_*`

For custom indexed routes, use the route index:

- `X402_ROUTE_1_STAKEHOLDER_1_NAME`
- `X402_ROUTE_1_STAKEHOLDER_1_BPS`
- `X402_ROUTE_1_STAKEHOLDER_1_DEST`

The compatibility variables `X402_STAKEHOLDER_1_*` and `X402_STAKEHOLDER_2_*` still map to operator and publisher respectively. With the installers, `host-system-install.sh` emits the operator-owned systemwide stakeholder lines and `host-vhost-install.sh` emits route or publisher stakeholder lines in the site config.

The vhost installer also supports indexed route generation:

- `X402_ROUTE_COUNT`
- `X402_ROUTE_1_PATH`
- `X402_ROUTE_1_AMOUNT`
- `X402_ROUTE_1_DESCRIPTION`
- `X402_ROUTE_1_MIMETYPE`
- `X402_ROUTE_1_CREDITS_ISSUED`
- `X402_ROUTE_1_FORWARD_TO`
- `X402_ROUTE_1_CONTENT_FILE`
- `X402_ROUTE_1_CONTENT_BODY`

For split settlement, replace the single-recipient route directive:

- remove `X402PayTo ...`
- add the Stellar local settlement directives shown below
- optionally add route or vhost `X402Stakeholder` lines for publisher shares

Example split `/app/foo` block with a publisher share:

```apache
<Location "/app/foo">
    X402 On
    X402Scheme exact
    X402Network stellar:testnet
    X402Asset CBIELTK6YBZJU5UP2WWQEUCYKLPU6AUNZ2BQ4WWFEIE3USCIHMXQDAMA
    X402Amount 1000000
    X402Description "Access to foo"
    X402MimeType text/html
    X402Mechanism stellar
    X402SettlementMode facilitator
    X402FacilitatorURL https://channels.openzeppelin.com/x402/testnet
    X402FacilitatorAPIKeyFile /etc/apache2/x402-secrets/facilitator.key
    X402StellarLocalBackend inprocess
    X402StellarConfigDir /etc/apache2/x402-stellar
    X402StellarSourceAccount operator_demo_split
    X402StellarRpcURL https://soroban-testnet.stellar.org:443
    X402StellarNetworkPassphrase "Test SDF Network ; September 2015"
    X402TimeoutSeconds 30
    X402PaymentIdentifier required
    X402Stakeholder content_publisher 9700 GACTCLSHLLAPVXEATOTMR6ZVKRGEJYPO6RDMZXJS76BXRBCAH5YWJ5P2
    X402Prepay On
    X402PrepayMultiplierMax 100
    X402CreditScope payer-route
    X402CreditTTLSeconds 86400
</Location>
```

## 9. Enable The Site

```sh
sudo a2dissite 000-default.conf || true
sudo a2ensite x402.conf
sudo apachectl configtest
sudo systemctl restart apache2
```

Prefer a full restart after installing a newly built module, not only a graceful reload.

## 10. Verify

Unpaid challenge:

```sh
curl -i http://64.23.244.67/app/foo/
```

Expected:

- `HTTP/1.1 402 Payment Required`
- `PAYMENT-REQUIRED`

Raw paid two-step flow:

```sh
cd /srv/x402/examples
STELLAR_PRIVATE_KEY='S...' ./scripts/raw-stellar-two-step.sh http://64.23.244.67/app/foo/
```

Expected single-recipient result:

- `HTTP 200`
- body `yoo hoo`
- `PAYMENT-RESPONSE`

Expected split result:

- `HTTP 200`
- body `yoo hoo`
- `PAYMENT-RESPONSE`
- `X402-Split-Transaction-Hash`

Inspect split audit state:

```sh
sudo sqlite3 -line /var/lib/x402/credits.db \
  'select payment_identifier, split_tx_hash, status, prepared_at_ms, submitted_at_ms, confirmed_at_ms from split_tx_audit order by updated_at_ms desc limit 20;'
```

## 11. Troubleshooting

Apache does not restart:

```sh
sudo apachectl configtest
sudo systemctl status apache2 --no-pager -l
sudo tail -n 100 /var/log/apache2/error.log
```

`PAYMENT-REQUIRED` missing:

- module not loaded
- site not enabled
- request is not hitting the protected location

Split payment returns `200` but no split hash:

- confirm `x402-splits.conf` is enabled with `a2enconf x402-splits`
- confirm Apache was fully restarted after module deployment
- confirm the loaded module is the current one

Split settlement fails:

- check `/etc/apache2/x402-stellar/identity/<name>.toml`
- check directory permissions on `/etc/apache2/x402-stellar` and `identity/`
- confirm `www-data` can read the identity file
- inspect `split_tx_audit`

## 12. Notes

- Non-split routes do not need the split signer identity file.
- Split percentages are defined in Apache directives, not in the identity TOML.
- The SQLite DB grows only in small metadata rows plus page-sized physical allocation steps.
