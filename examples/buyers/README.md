# Buyer Scripts

This directory contains buyer-side demo clients for x402 on Stellar.

- `buyer-stellar.mjs`
  Single paid-request buyer. It calls one protected URL, handles a `402 Payment Required` challenge, pays once, and prints the response plus decoded `PAYMENT-RESPONSE`.

- `buyer-stellar-prepaid.mjs`
  Prepaid buyer flow. It can target an explicit fixed route such as `/priceX2`, or a base route such as `/priceX` that is completed from the first numeric argument. The second numeric argument is total protected calls, not repeat count.

Typical entrypoints:

```sh
cd examples
npm run buyer:stellar -- http://<host>/app/foo
npm run buyer:stellar:prepaid -- http://<host>/priceX 2 2
```
