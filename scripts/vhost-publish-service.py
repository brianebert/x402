#!/usr/bin/env python3
import json
import os
import re
import shlex
import subprocess
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
from pathlib import Path


ROOT = Path(os.environ.get("X402_ROOT", "/srv/x402"))
HOST = os.environ.get("X402_VHOST_PUBLISH_HOST", "127.0.0.1")
PORT = int(os.environ.get("X402_VHOST_PUBLISH_PORT", "8017"))
ALLOW_UNPAID = os.environ.get("X402_VHOST_PUBLISH_ALLOW_UNPAID", "0") == "1"
ALLOWED_REMOTE_RE = re.compile(
    os.environ.get("X402_VHOST_PUBLISH_REMOTE_RE", r"^(127\.0\.0\.1|::1|10\.)")
)
SERVER_RE = re.compile(r"^[a-z0-9](?:[a-z0-9-]{0,61}[a-z0-9])?\.cryptify\.shop$")
STORE_RE = re.compile(r"^[A-Za-z0-9_-]+$")
ENV_KEY_RE = re.compile(r"^[A-Z0-9_]+$")

REQUIRED_ENV = {
    "X402_SITE_NAME",
    "X402_SERVER_NAME",
    "X402_VHOST_MODE",
    "X402_ENABLE_SSL",
    "X402_DOMAIN",
    "X402_SSL_CERT_FILE",
    "X402_SSL_KEY_FILE",
    "X402_PROXY_TARGET",
    "X402_PROXY_EXCLUDE_PATHS",
    "X402_PROXY_ERROR_DOCUMENT",
    "X402_ENABLE_DYNAMIC_INTENTS",
    "X402_CHALLENGE_ENDPOINT",
    "X402_DYNAMIC_CHECKOUT_ENDPOINT",
    "X402_INTENT_SECRET_PATH",
}

OPTIONAL_ENV = {
    "X402_VHOST_ACTION",
    "X402_PROXY_PRESERVE_HOST",
    "X402_PROXY_HTTPS_ONLY",
    "X402_DYNAMIC_SETTLEMENT_MODE",
    "X402_INTENT_SECRET",
    "X402_INTENT_SECRET_SOURCE_FILE",
    "X402_PUBLISHER_STAKEHOLDER_1_NAME",
    "X402_PUBLISHER_STAKEHOLDER_1_BPS",
    "X402_PUBLISHER_STAKEHOLDER_1_DEST",
    "X402_PUBLISHER_STAKEHOLDER_2_NAME",
    "X402_PUBLISHER_STAKEHOLDER_2_BPS",
    "X402_PUBLISHER_STAKEHOLDER_2_DEST",
    "X402_PUBLISHER_STAKEHOLDER_3_NAME",
    "X402_PUBLISHER_STAKEHOLDER_3_BPS",
    "X402_PUBLISHER_STAKEHOLDER_3_DEST",
}


def json_response(handler, status, payload):
    body = json.dumps(payload, indent=2, sort_keys=True).encode("utf-8")
    handler.send_response(status)
    handler.send_header("Content-Type", "application/json")
    handler.send_header("Content-Length", str(len(body)))
    handler.end_headers()
    handler.wfile.write(body)


def parse_env(text):
    values = {}
    for raw_line in text.splitlines():
        line = raw_line.strip()
        if not line or line.startswith("#"):
            continue
        if "=" not in line:
            raise ValueError(f"invalid env line: {raw_line}")
        key, value = line.split("=", 1)
        key = key.strip()
        if not ENV_KEY_RE.fullmatch(key):
            raise ValueError(f"invalid env key: {key}")
        value = value.strip()
        if (value.startswith('"') and value.endswith('"')) or (
            value.startswith("'") and value.endswith("'")
        ):
            value = value[1:-1]
        values[key] = value
    return values


def render_env(values):
    return "".join(f"{key}={shlex.quote(values[key])}\n" for key in sorted(values))


def validate_payload(payload):
    server_name = str(payload.get("server_name", "")).strip().lower()
    store_id = str(payload.get("store_id", "")).strip()
    env_text = str(payload.get("env", ""))
    if not SERVER_RE.fullmatch(server_name):
        raise ValueError("server_name must be a single *.cryptify.shop hostname")
    if server_name.startswith(("admin.", "www.", "cryptify.")):
        raise ValueError("server_name is reserved")
    if not STORE_RE.fullmatch(store_id):
        raise ValueError("store_id may contain only letters, digits, hyphen, and underscore")

    env_values = parse_env(env_text)
    missing = sorted(REQUIRED_ENV - set(env_values))
    if missing:
        raise ValueError(f"missing env keys: {', '.join(missing)}")
    unsupported = sorted(set(env_values) - REQUIRED_ENV - OPTIONAL_ENV)
    if unsupported:
        raise ValueError(f"unsupported env keys: {', '.join(unsupported)}")

    expected_target = f"http://10.120.0.4:8007/stores/{store_id}/"
    expected = {
        "X402_SITE_NAME": server_name,
        "X402_SERVER_NAME": server_name,
        "X402_VHOST_MODE": "proxy",
        "X402_ENABLE_SSL": "1",
        "X402_DOMAIN": server_name,
        "X402_SSL_CERT_FILE": "/etc/apache2/ssl/cryptify.shop/fullchain.pem",
        "X402_SSL_KEY_FILE": "/etc/apache2/ssl/cryptify.shop/privkey.pem",
        "X402_PROXY_TARGET": expected_target,
        "X402_PROXY_ERROR_DOCUMENT": "/errors/as-404.php",
        "X402_ENABLE_DYNAMIC_INTENTS": "1",
        "X402_CHALLENGE_ENDPOINT": "/x402/challenge",
        "X402_DYNAMIC_CHECKOUT_ENDPOINT": "/api/store/checkout",
        "X402_INTENT_SECRET_PATH": "/etc/apache2/x402-secrets/x402-intent.key",
    }
    for key, value in expected.items():
        if env_values.get(key) != value:
            raise ValueError(f"{key} must be {value}")
    if env_values["X402_PROXY_EXCLUDE_PATHS"] != "/staging /staging/":
        raise ValueError("X402_PROXY_EXCLUDE_PATHS must exclude /staging and /staging/")
    for key in ("X402_PROXY_PRESERVE_HOST", "X402_PROXY_HTTPS_ONLY"):
        if key in env_values and env_values[key] not in {"0", "1"}:
            raise ValueError(f"{key} must be 0 or 1")

    return server_name, store_id, env_values


class Handler(BaseHTTPRequestHandler):
    server_version = "x402-vhost-publish/1"

    def do_POST(self):
        if self.path != "/internal/vhosts/publish":
            json_response(self, 404, {"error": "not found"})
            return
        remote_ip = self.client_address[0]
        if not ALLOWED_REMOTE_RE.search(remote_ip):
            json_response(self, 403, {"error": "private network access required"})
            return
        if not ALLOW_UNPAID and self.headers.get("X-X402-Paid") != "true":
            json_response(self, 402, {"error": "x402 payment required"})
            return

        try:
            length = int(self.headers.get("Content-Length", "0"))
            if length <= 0 or length > 65536:
                raise ValueError("request body must be 1..65536 bytes")
            payload = json.loads(self.rfile.read(length))
            server_name, store_id, env_values = validate_payload(payload)
            env_path = ROOT / f".{server_name}.env"
            env_path.write_text(render_env(env_values), encoding="utf-8")
            env_path.chmod(0o640)

            command = ["sudo", str(ROOT / "scripts" / "host-vhost-install.sh"), server_name]
            completed = subprocess.run(
                command,
                cwd=str(ROOT),
                text=True,
                capture_output=True,
                timeout=90,
                check=False,
            )
            if completed.returncode != 0:
                json_response(
                    self,
                    500,
                    {
                        "error": "host-vhost-install failed",
                        "returncode": completed.returncode,
                        "stdout": completed.stdout[-4000:],
                        "stderr": completed.stderr[-4000:],
                    },
                )
                return

            json_response(
                self,
                200,
                {
                    "ok": True,
                    "server_name": server_name,
                    "store_id": store_id,
                    "env_path": str(env_path),
                    "public_url": f"https://{server_name}/",
                    "stdout": completed.stdout[-4000:],
                },
            )
        except Exception as error:
            json_response(self, 400, {"error": str(error)})

    def log_message(self, fmt, *args):
        print(f"{self.client_address[0]} - {fmt % args}", flush=True)


def main():
    server = ThreadingHTTPServer((HOST, PORT), Handler)
    print(f"Serving private x402 vhost publisher on {HOST}:{PORT}", flush=True)
    server.serve_forever()


if __name__ == "__main__":
    main()
