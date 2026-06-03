#!/usr/bin/env bash
set -euo pipefail

if ! command -v sqlite3 >/dev/null 2>&1; then
  echo "sqlite3 is required" >&2
  exit 1
fi

db="$(mktemp "${TMPDIR:-/tmp}/x402-dynamic-intent-scope.XXXXXX.db")"
trap 'rm -f "$db"' EXIT

sqlite3 "$db" <<'SQL'
CREATE TABLE dynamic_payment_intent (
  payment_identifier TEXT PRIMARY KEY,
  store_id TEXT,
  catalog_id TEXT,
  order_id TEXT,
  resource TEXT NOT NULL,
  network TEXT NOT NULL,
  asset TEXT NOT NULL,
  amount INTEGER NOT NULL,
  pay_to TEXT,
  description TEXT,
  mime_type TEXT,
  timeout_seconds INTEGER NOT NULL,
  scheme TEXT NOT NULL,
  mechanism TEXT NOT NULL,
  split_mode INTEGER NOT NULL,
  splitter_contract TEXT,
  settlement_mode INTEGER NOT NULL,
  status TEXT NOT NULL,
  payer TEXT,
  settlement_tx TEXT,
  created_at INTEGER NOT NULL,
  updated_at INTEGER NOT NULL,
  settled_at INTEGER
);

CREATE TABLE dynamic_payment_stakeholder (
  payment_identifier TEXT NOT NULL,
  position INTEGER NOT NULL,
  name TEXT NOT NULL,
  basis_points INTEGER NOT NULL,
  destination TEXT NOT NULL,
  PRIMARY KEY (payment_identifier, position)
);

INSERT INTO dynamic_payment_intent
VALUES (
  'legacy_ord', 'legacy_store', 'legacy_catalog', 'legacy_order',
  '/api/store/checkout', 'stellar:testnet', 'USDC:GISSUER', 100,
  'GPAYTO', 'legacy order', 'application/json', 30, 'exact', 'stellar',
  0, '', 2, 'pending', NULL, NULL, 1, 1, NULL
);

INSERT INTO dynamic_payment_stakeholder
VALUES ('legacy_ord', 0, 'publisher', 10000, 'GPUBLISHER');

BEGIN IMMEDIATE TRANSACTION;
ALTER TABLE dynamic_payment_intent RENAME TO dynamic_payment_intent_old;
CREATE TABLE dynamic_payment_intent (
  request_host TEXT NOT NULL DEFAULT '',
  payment_identifier TEXT NOT NULL,
  store_id TEXT,
  catalog_id TEXT,
  order_id TEXT,
  resource TEXT NOT NULL,
  network TEXT NOT NULL,
  asset TEXT NOT NULL,
  amount INTEGER NOT NULL,
  pay_to TEXT,
  description TEXT,
  mime_type TEXT,
  timeout_seconds INTEGER NOT NULL,
  scheme TEXT NOT NULL,
  mechanism TEXT NOT NULL,
  split_mode INTEGER NOT NULL,
  splitter_contract TEXT,
  settlement_mode INTEGER NOT NULL,
  status TEXT NOT NULL,
  payer TEXT,
  settlement_tx TEXT,
  created_at INTEGER NOT NULL,
  updated_at INTEGER NOT NULL,
  settled_at INTEGER,
  PRIMARY KEY (request_host, payment_identifier)
);
INSERT INTO dynamic_payment_intent
(request_host, payment_identifier, store_id, catalog_id, order_id, resource, network, asset, amount,
 pay_to, description, mime_type, timeout_seconds, scheme, mechanism, split_mode, splitter_contract,
 settlement_mode, status, payer, settlement_tx, created_at, updated_at, settled_at)
SELECT '', payment_identifier, store_id, catalog_id, order_id, resource, network, asset, amount,
       pay_to, description, mime_type, timeout_seconds, scheme, mechanism, split_mode, splitter_contract,
       settlement_mode, status, payer, settlement_tx, created_at, updated_at, settled_at
FROM dynamic_payment_intent_old;
DROP TABLE dynamic_payment_intent_old;
COMMIT;

BEGIN IMMEDIATE TRANSACTION;
ALTER TABLE dynamic_payment_stakeholder RENAME TO dynamic_payment_stakeholder_old;
CREATE TABLE dynamic_payment_stakeholder (
  request_host TEXT NOT NULL DEFAULT '',
  payment_identifier TEXT NOT NULL,
  position INTEGER NOT NULL,
  name TEXT NOT NULL,
  basis_points INTEGER NOT NULL,
  destination TEXT NOT NULL,
  PRIMARY KEY (request_host, payment_identifier, position)
);
INSERT INTO dynamic_payment_stakeholder
(request_host, payment_identifier, position, name, basis_points, destination)
SELECT '', payment_identifier, position, name, basis_points, destination
FROM dynamic_payment_stakeholder_old;
DROP TABLE dynamic_payment_stakeholder_old;
COMMIT;

INSERT INTO dynamic_payment_intent
(request_host, payment_identifier, store_id, catalog_id, order_id, resource, network, asset, amount,
 pay_to, description, mime_type, timeout_seconds, scheme, mechanism, split_mode, splitter_contract,
 settlement_mode, status, created_at, updated_at)
VALUES
('store-a.example', 'ord_123', 'store_a', 'catalog', 'order_a', '/api/store/checkout',
 'stellar:testnet', 'USDC:GISSUER', 100, 'GPAYTOA', 'a order', 'application/json',
 30, 'exact', 'stellar', 0, '', 2, 'pending', 2, 2),
('store-b.example', 'ord_123', 'store_b', 'catalog', 'order_b', '/api/store/checkout',
 'stellar:testnet', 'USDC:GISSUER', 200, 'GPAYTOB', 'b order', 'application/json',
 30, 'exact', 'stellar', 0, '', 2, 'pending', 2, 2);

INSERT INTO dynamic_payment_stakeholder
(request_host, payment_identifier, position, name, basis_points, destination)
VALUES
('store-a.example', 'ord_123', 0, 'publisher', 10000, 'GPUBLISHERA'),
('store-b.example', 'ord_123', 0, 'publisher', 10000, 'GPUBLISHERB');

UPDATE dynamic_payment_intent
SET status = 'settled',
    payer = COALESCE(NULLIF('GPAYERA', ''), payer),
    settlement_tx = COALESCE(NULLIF('tx-a', ''), settlement_tx),
    updated_at = 3,
    settled_at = CASE WHEN 'settled' = 'settled' THEN 3 ELSE settled_at END
WHERE request_host = 'store-a.example'
  AND payment_identifier = 'ord_123'
  AND status = 'pending';
SQL

expect() {
  local label="$1"
  local expected="$2"
  local query="$3"
  local actual

  actual="$(sqlite3 "$db" "$query")"
  if [[ "$actual" != "$expected" ]]; then
    echo "$label: expected [$expected], got [$actual]" >&2
    exit 1
  fi
}

expect "legacy intent migrated" "|legacy_ord" \
  "SELECT request_host || '|' || payment_identifier FROM dynamic_payment_intent WHERE payment_identifier = 'legacy_ord';"

expect "legacy stakeholder migrated" "|legacy_ord|0" \
  "SELECT request_host || '|' || payment_identifier || '|' || position FROM dynamic_payment_stakeholder WHERE payment_identifier = 'legacy_ord';"

expect "duplicate order IDs allowed across vhosts" "2" \
  "SELECT COUNT(*) FROM dynamic_payment_intent WHERE payment_identifier = 'ord_123';"

expect "host-scoped status update selects store-a" "store_a|100|settled|GPAYERA|tx-a" \
  "SELECT store_id || '|' || amount || '|' || status || '|' || payer || '|' || settlement_tx FROM dynamic_payment_intent WHERE request_host = 'store-a.example' AND payment_identifier = 'ord_123';"

expect "host-scoped load selects store-a by amount" "store_a|100" \
  "SELECT store_id || '|' || amount FROM dynamic_payment_intent WHERE request_host = 'store-a.example' AND payment_identifier = 'ord_123';"

expect "host-scoped status update leaves store-b pending" "store_b|200|pending" \
  "SELECT store_id || '|' || amount || '|' || status FROM dynamic_payment_intent WHERE request_host = 'store-b.example' AND payment_identifier = 'ord_123';"

expect "host-scoped stakeholder positions do not collide" "2" \
  "SELECT COUNT(*) FROM dynamic_payment_stakeholder WHERE payment_identifier = 'ord_123' AND position = 0;"

echo "dynamic intent vhost scope regression passed"
