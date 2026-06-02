#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"

echo "Running x402 systemwide install..."
"$SCRIPT_DIR/host-system-install.sh"

echo "Running x402 vhost install..."
"$SCRIPT_DIR/host-vhost-install.sh"

echo "Deployment complete."
