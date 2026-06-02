# Script Utilities

This directory contains operator-facing scripts for inspecting and demoing x402 flows.

- `test-x402-flow.sh`
  Low-level `curl` harness for challenge-only or challenge-plus-paid-retry testing. Useful for inspecting raw headers and bodies.

- `raw-stellar-two-step.sh`
  Explicit two-step Stellar payment demo. It shows the unpaid challenge, decodes `PAYMENT-REQUIRED`, builds a signed `PAYMENT-SIGNATURE`, performs the paid retry, and decodes `PAYMENT-RESPONSE`.

- `bad-stellar-payment.mjs`
  Negative-test helper for bad-payment handling. It creates a random Stellar keypair, prints the public key under test, and sends ten parseable but deliberately invalid payer-bearing payment payloads so operators can exercise `402` and `429` behavior deterministically.

- `make-split-demo-accounts.mjs`
  Creates or reuses the demo accounts needed for split-payment testing and writes the generated `.env`, identity, and account metadata artifacts. The generated `split-server.env` uses indexed `X402_OPERATOR_STAKEHOLDER_1_*` and `X402_PUBLISHER_STAKEHOLDER_1_*` variables.
