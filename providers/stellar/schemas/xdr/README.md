# Stellar XDR Schema

This directory now tracks the canonical Stellar XDR schema files from the official `stellar/stellar-xdr` repository, plus current C++ headers generated from them with `xdrpp`.

Current source of truth:

- `https://github.com/stellar/stellar-xdr`
- fetched from the repository `master` branch on 2026-05-07

Why this directory changed:

- the older checked-in files predated Soroban
- they did not include the current contract / SCVal / host-function schema needed for Soroban-era transaction work
- the old generated C artifacts were also stale and inconsistent with the current `.x` schema set

Intentional removals:

- stale `rpcgen`-style generated C artifacts:
  - `Stellar-types_xdr.c`
  - `Stellar-ledger-entries.c`

Generated headers:

- `*.h` files in this directory are generated with:
  - `/usr/local/bin/xdrc -hh -o <name>.h <name>.x`
- these are current `xdrpp` C++ headers, not the older `rpcgen` output that was previously checked in

If bindings need to be refreshed later, regenerate the `.h` files from the checked-in `.x` schema set rather than restoring the removed generated C files.
