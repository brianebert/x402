# Serverwide Split Installer Notes

The desired policy model is:

- systemwide config owns only the operator-controlled split policy:
  - `X402SplitMode multi`
  - `X402SplitterContract C...`
  - one or more operator stakeholders, for example:
    - `X402Stakeholder server_operator 300 G...`
- vhost or route config owns publisher/content stakeholders:
  - `X402Stakeholder content_publisher 9700 G...`
- the effective route policy is:
  - global split mode
  - global splitter contract
  - global stakeholders plus vhost/location stakeholders
  - combined stakeholder basis points must equal `10000`

The current generated `x402-splits.conf` is too broad if it writes all splits there. It should not write every stakeholder into the systemwide file. It should write only the server operator's required share. The publisher/content share belongs in the vhost or route config.

## Should There Be More Than One Installer?

Yes, probably.

Recommended shape:

1. `scripts/host-system-install.sh`

   This is run by the server operator. It should:

   - install packages
   - build and install `mod_x402.so`
   - create `/etc/apache2/x402-secrets`
   - create `/etc/apache2/x402-stellar`
   - create `/var/lib/x402`
   - write and enable `/etc/apache2/conf-available/x402-splits.conf`
   - install the systemwide split signer identity if needed
   - avoid creating `/app/foo` or `/priceX*`

2. `scripts/host-vhost-install.sh`

   This is run for a site or publisher. It should:

   - write `/etc/apache2/sites-available/<site>.conf`
   - create the document root and routes
   - write route amounts, asset, facilitator config, prepaid config
   - write vhost or route `X402Stakeholder content_publisher ...`
   - avoid writing `X402SplitMode` or `X402SplitterContract` when global split is active

This maps to the real control boundary:

- server operator controls the global splitter contract and operator payout
- publisher/vhost operator controls content routes and publisher payout share
- Apache validates the combined policy

## Smaller Near-Term Correction

If keeping one installer for now, change it so:

- `/etc/apache2/conf-available/x402-splits.conf` gets only operator-owned stakeholder directives
- route or vhost blocks get publisher stakeholder directives
- docs say the combined basis points must total `10000`
- preferred env names are indexed, for example `X402_OPERATOR_STAKEHOLDER_1_*` and `X402_PUBLISHER_STAKEHOLDER_1_*`
- route-specific publisher env names use route keys, for example `X402_ROUTE_APP_FOO_STAKEHOLDER_1_*`
- compatibility env names are `X402_STAKEHOLDER_1_*` for operator and `X402_STAKEHOLDER_2_*` for publisher

The current monolithic `host-admin-install.sh` is acting as both the server-owner installer and the vhost/publisher installer. That is the reason this policy boundary became unclear.
