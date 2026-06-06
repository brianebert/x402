#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"

sudo install -m 755 "$ROOT/scripts/vhost-publish-service.py" /usr/local/bin/x402-vhost-publish-service

sudo tee /etc/systemd/system/x402-vhost-publish.service >/dev/null <<'EOF'
[Unit]
Description=x402 private vhost publish service
After=network-online.target
Wants=network-online.target

[Service]
User=x402
Group=x402
WorkingDirectory=/srv/x402
Environment=X402_ROOT=/srv/x402
Environment=X402_VHOST_PUBLISH_HOST=127.0.0.1
Environment=X402_VHOST_PUBLISH_PORT=8017
Environment="X402_VHOST_PUBLISH_REMOTE_RE=^(127\\.0\\.0\\.1|::1)$"
ExecStart=/usr/local/bin/x402-vhost-publish-service
Restart=always
RestartSec=3

[Install]
WantedBy=multi-user.target
EOF

sudo systemctl daemon-reload
sudo systemctl enable --now x402-vhost-publish.service
sudo systemctl is-active x402-vhost-publish.service
