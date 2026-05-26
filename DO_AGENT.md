# AGENT

The directory do_artifacts is a local deployment workspace for creating a DigitalOcean reference host for `x402+`.

## Goal

Create a 1 regular CPU, 2 GB RAM Ubuntu host with at least 25 GB SSD that:

- permission is granted to create one new host only
- is reachable by IPv4, not by domain name
- has Apache2 installed
- is ready for later TLS setup
- has a non-root `x402` user with passwordless sudo
- be permissive about ssh and scp to the new host.

## Inputs

- `.do_access`
  - must contain `DIGITAL_OCEAN_TOKEN`
  - operator should create it by copying `.do_access.example`

This flow assumes direct DigitalOcean API use plus cloud-init key injection.
It should pre-register the root SSH public key with DigitalOcean and use that
registered key in the droplet create request.

## SSH Material

Make two SSH keypairs locally and store them in this directory:

- `do_root_ed25519`
  - used for bootstrap/root access
- `do_x402_ed25519`
  - installed for the long-lived `x402` operator user

Record both keypairs in the file `ssh-keys.txt`.

Before creating the droplet:

- upload `do_root_ed25519.pub` to the DigitalOcean account with the SSH keys API
- record the returned SSH key id and fingerprint under `do_artifacts/`
- include that registered key in the droplet create request via `ssh_keys`

## Host Shape

- Record pertinent new droplet information
  - CPUs
  - RAM
  - SSD
  - droplet name
  - droplet id
  - public ipv4
  - private ipv4

Use Cloud-init for:

- installing Apache2 and common admin packages
- creating user `x402`
- adding `x402` to `sudo`
- writing `/etc/sudoers.d/90-x402-nopasswd`
- creating the `x402` SSH login path
- normalizing root password aging during bootstrap so post-bootstrap root SSH does not hit a forced password-change prompt on fresh Ubuntu images

Verify:

- Apache2 is installed and serving the default HTTP site on the IPv4 address
- user `x402` exists
- `x402` can log in via SSH
- `x402` has passwordless sudo
- Ask user whether to install x402 or not. If yes, do so and verify installation.

## Notes

- This directory is intentionally local and secret-bearing.
- keep provisioning artifacts under `do_artifacts/`
- Do not publish `.do_access`, the private keys, or `ssh-keys.txt`.
- If you poll DigitalOcean from `zsh`, do not use `status` as a shell variable name; use something like `droplet_state` instead.
- Register the root public key with DigitalOcean before droplet creation instead of writing `/root/.ssh/authorized_keys` from cloud-init.
- In cloud-init, add `chage -d -1 root && chage -M -1 root` during bootstrap so post-bootstrap root SSH works non-interactively. If a host still comes up with the forced password-change prompt, log in as `x402` and run the same fix via `sudo`, then retry root SSH.
