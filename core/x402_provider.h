#ifndef X402_PROVIDER_H
#define X402_PROVIDER_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define X402_MAX_STAKEHOLDERS 16
#define X402_MAX_TEXT 256
#define X402_MAX_JSON 4096
#define X402_MAX_SCHEME 32
#define X402_MAX_NETWORK 64
#define X402_MAX_MECHANISM 64
#define X402_MAX_ASSET 128
#define X402_MAX_DESTINATION 160
#define X402_MAX_ROUTE 160
#define X402_MAX_IDENTIFIER 128
#define X402_MAX_TX_REF 160
#define X402_MAX_PAYER 160
#define X402_MAX_PATH 256

typedef enum x402_split_mode {
  X402_SPLIT_SINGLE = 0,
  X402_SPLIT_MULTI = 1
} x402_split_mode;

typedef enum x402_settlement_mode {
  X402_SETTLEMENT_LOCAL = 0,
  X402_SETTLEMENT_FACILITATOR = 1,
  X402_SETTLEMENT_HYBRID = 2
} x402_settlement_mode;

typedef enum x402_credit_scope {
  X402_CREDIT_SCOPE_PAYER = 0,
  X402_CREDIT_SCOPE_PAYER_ROUTE = 1
} x402_credit_scope;

typedef enum x402_stellar_local_backend {
  X402_STELLAR_BACKEND_AUTO = 0,
  X402_STELLAR_BACKEND_INPROCESS = 1
} x402_stellar_local_backend;

typedef enum x402_status {
  X402_STATUS_OK = 0,
  X402_STATUS_INVALID_ARGUMENT = 1,
  X402_STATUS_UNSUPPORTED = 2,
  X402_STATUS_POLICY_ERROR = 3,
  X402_STATUS_VERIFY_ERROR = 4,
  X402_STATUS_SETTLE_ERROR = 5,
  X402_STATUS_BUFFER_TOO_SMALL = 6
} x402_status;

typedef struct x402_stakeholder {
  char name[64];
  uint16_t basis_points;
  char destination[X402_MAX_DESTINATION];
} x402_stakeholder;

typedef struct x402_credit_policy {
  int enabled;
  uint32_t max_multiplier;
  uint32_t ttl_seconds;
  x402_credit_scope scope;
} x402_credit_policy;

typedef struct x402_route_policy {
  char route[X402_MAX_ROUTE];
  char resource_method[16];
  char scheme[X402_MAX_SCHEME];
  char network[X402_MAX_NETWORK];
  char mechanism[X402_MAX_MECHANISM];
  char asset[X402_MAX_ASSET];
  uint64_t amount;
  char description[X402_MAX_TEXT];
  char mime_type[64];
  x402_split_mode split_mode;
  x402_settlement_mode settlement_mode;
  int payment_identifier_required;
  char pay_to[X402_MAX_DESTINATION];
  char facilitator_url[X402_MAX_TEXT];
  char facilitator_api_key[X402_MAX_TEXT];
  char splitter_contract[X402_MAX_DESTINATION];
  char stellar_config_dir[X402_MAX_PATH];
  char stellar_source_account[X402_MAX_IDENTIFIER];
  char stellar_rpc_url[X402_MAX_TEXT];
  char stellar_network_passphrase[X402_MAX_TEXT];
  x402_stellar_local_backend stellar_local_backend;
  uint32_t timeout_seconds;
  uint32_t credits_issued_override;
  char forward_to[X402_MAX_ROUTE];
  x402_credit_policy credits;
  size_t stakeholder_count;
  x402_stakeholder stakeholders[X402_MAX_STAKEHOLDERS];
} x402_route_policy;

typedef struct x402_request_context {
  char payer_hint[X402_MAX_PAYER];
  char client_id[X402_MAX_PAYER];
  char payment_identifier[X402_MAX_IDENTIFIER];
  char request_id[X402_MAX_IDENTIFIER];
  uint32_t requested_multiplier;
} x402_request_context;

typedef struct x402_payment_requirements {
  char pay_to[X402_MAX_DESTINATION];
  char settlement_target[X402_MAX_DESTINATION];
  uint64_t amount;
  uint32_t timeout_seconds;
  int prepaid_supported;
  uint32_t max_multiplier;
} x402_payment_requirements;

typedef struct x402_provider_capabilities {
  int supports_local_verify;
  int supports_local_settle;
  int supports_facilitator;
  int supports_multi_stakeholder;
  int supports_prepaid;
  int derives_payer_identity;
} x402_provider_capabilities;

typedef struct x402_verification_result {
  x402_status status;
  int accepted;
  uint64_t amount_received;
  char payer[X402_MAX_PAYER];
  char transaction_ref[X402_MAX_TX_REF];
  char error_code[64];
  char message[X402_MAX_TEXT];
} x402_verification_result;

typedef struct x402_settlement_result {
  x402_status status;
  int settled;
  uint32_t credits_issued;
  uint32_t credits_remaining;
  char payer[X402_MAX_PAYER];
  char transaction_ref[X402_MAX_TX_REF];
  char split_transaction_hash[X402_MAX_TX_REF];
  char settlement_mode[24];
  char session_token[X402_MAX_IDENTIFIER];
  uint64_t session_expires_at;
  char error_code[64];
  char message[X402_MAX_TEXT];
} x402_settlement_result;

typedef struct x402_payment_payload_view {
  char scheme[X402_MAX_SCHEME];
  char network[X402_MAX_NETWORK];
  char payer[X402_MAX_PAYER];
  char payment_identifier[X402_MAX_IDENTIFIER];
  char transaction[X402_MAX_TX_REF];
  uint32_t multiplier;
} x402_payment_payload_view;

typedef struct x402_provider {
  const char *name;
  x402_status (*describe_capabilities)(x402_provider_capabilities *caps);
  x402_status (*declare_requirements)(const x402_route_policy *policy,
                                      const x402_request_context *request,
                                      x402_payment_requirements *requirements);
  x402_status (*verify)(const x402_route_policy *policy,
                        const x402_request_context *request,
                        const char *payment_payload,
                        x402_verification_result *result);
  x402_status (*settle)(const x402_route_policy *policy,
                        const x402_request_context *request,
                        const char *payment_payload,
                        x402_settlement_result *result);
} x402_provider;

x402_status x402_validate_policy(const x402_route_policy *policy,
                                 char *error,
                                 size_t error_size);
uint64_t x402_calculate_stakeholder_amount(uint64_t total_amount,
                                           size_t stakeholder_index,
                                           const x402_route_policy *policy);
x402_status x402_build_payment_required_json(const x402_route_policy *policy,
                                             const x402_payment_requirements *requirements,
                                             char *buffer,
                                             size_t buffer_size);
x402_status x402_build_payment_response_json(const x402_route_policy *policy,
                                             const x402_settlement_result *result,
                                             char *buffer,
                                             size_t buffer_size);
x402_status x402_extract_json_string(const char *json,
                                     const char *key,
                                     char *buffer,
                                     size_t buffer_size);
x402_status x402_extract_json_uint32(const char *json,
                                     const char *key,
                                     uint32_t *value);
x402_status x402_parse_payment_payload(const char *json,
                                       x402_payment_payload_view *view);
const char *x402_split_mode_name(x402_split_mode mode);
const char *x402_settlement_mode_name(x402_settlement_mode mode);
const char *x402_credit_scope_name(x402_credit_scope scope);

#ifdef __cplusplus
}
#endif

#endif
