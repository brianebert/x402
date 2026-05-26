# Third-Party Dependencies

This directory contains vendored third-party headers required to rebuild the current in-process Soroban backend reproducibly.

## `xdrpp`

- Path: `third_party/xdrpp/`
- Source type: vendored header tree
- Purpose:
  - supports the generated Stellar/Soroban XDR bindings under `providers/stellar/schemas/xdr/`
  - required by `providers/stellar/stellar_provider.cpp` for the in-process Soroban settlement path

The live server previously depended on a manual copy of `xdrpp` headers into `/usr/local/include/xdrpp`. Vendoring the headers here removes that hidden machine dependency for future builds.
