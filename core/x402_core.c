#include "x402_provider.h"

#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

static x402_status x402_append(char *buffer,
                               size_t buffer_size,
                               size_t *offset,
                               const char *text)
{
  size_t len = strlen(text);

  if(*offset + len + 1 > buffer_size) {
    return X402_STATUS_BUFFER_TOO_SMALL;
  }

  memcpy(buffer + *offset, text, len);
  *offset += len;
  buffer[*offset] = '\0';
  return X402_STATUS_OK;
}

static x402_status x402_appendf(char *buffer,
                                size_t buffer_size,
                                size_t *offset,
                                const char *fmt,
                                ...)
{
  int written;
  va_list args;

  va_start(args, fmt);
  written = vsnprintf(buffer + *offset, buffer_size - *offset, fmt, args);
  va_end(args);

  if(written < 0 || (size_t)written >= buffer_size - *offset) {
    return X402_STATUS_BUFFER_TOO_SMALL;
  }

  *offset += (size_t)written;
  return X402_STATUS_OK;
}

const char *x402_split_mode_name(x402_split_mode mode)
{
  return mode == X402_SPLIT_MULTI ? "multi" : "single";
}

const char *x402_settlement_mode_name(x402_settlement_mode mode)
{
  switch(mode) {
    case X402_SETTLEMENT_LOCAL:
      return "local";
    case X402_SETTLEMENT_FACILITATOR:
      return "facilitator";
    default:
      return "hybrid";
  }
}

const char *x402_credit_scope_name(x402_credit_scope scope)
{
  return scope == X402_CREDIT_SCOPE_PAYER ? "payer" : "payer-route";
}

static const char *x402_split_execution_name(const x402_route_policy *policy)
{
  x402_stellar_local_backend backend;

  if(policy == NULL || policy->split_mode != X402_SPLIT_MULTI) {
    return "direct-recipient";
  }

  backend = policy->stellar_local_backend == X402_STELLAR_BACKEND_AUTO
                ? X402_STELLAR_BACKEND_INPROCESS
                : policy->stellar_local_backend;

  if(backend == X402_STELLAR_BACKEND_INPROCESS &&
     policy->stellar_config_dir[0] != '\0' &&
     policy->stellar_source_account[0] != '\0' &&
     policy->stellar_rpc_url[0] != '\0' &&
     policy->stellar_network_passphrase[0] != '\0') {
    return "splitter-invoke";
  }

  return "contract-fund-only";
}

static int x402_policy_uses_stellar(const x402_route_policy *policy)
{
  return policy != NULL && strncmp(policy->network, "stellar:", 8) == 0;
}

static int x402_prepaid_option_supported(const x402_route_policy *policy, uint32_t multiplier)
{
  static const uint32_t options[] = {1U, 2U, 10U, 100U};
  size_t i;

  if(policy == NULL || !policy->credits.enabled || multiplier == 0 ||
     multiplier > policy->credits.max_multiplier) {
    return 0;
  }
  for(i = 0; i < sizeof(options) / sizeof(options[0]); ++i) {
    if(options[i] == multiplier) {
      return 1;
    }
  }
  return 0;
}

x402_status x402_validate_policy(const x402_route_policy *policy,
                                 char *error,
                                 size_t error_size)
{
  size_t i;
  uint32_t total_bps = 0;

  if(policy == NULL) {
    snprintf(error, error_size, "missing policy");
    return X402_STATUS_INVALID_ARGUMENT;
  }

  if(policy->route[0] == '\0' || policy->scheme[0] == '\0' ||
     policy->network[0] == '\0' || policy->mechanism[0] == '\0') {
    snprintf(error, error_size, "route, scheme, network, and mechanism are required");
    return X402_STATUS_POLICY_ERROR;
  }

  if(policy->amount == 0) {
    snprintf(error, error_size, "amount must be greater than 0");
    return X402_STATUS_POLICY_ERROR;
  }

  if(policy->split_mode == X402_SPLIT_SINGLE) {
    if(policy->pay_to[0] == '\0') {
      snprintf(error, error_size, "single-recipient mode requires pay_to");
      return X402_STATUS_POLICY_ERROR;
    }
    if(policy->stakeholder_count != 0) {
      snprintf(error, error_size, "single-recipient mode cannot define stakeholders");
      return X402_STATUS_POLICY_ERROR;
    }
  }
  else {
    if(policy->stakeholder_count == 0) {
      snprintf(error, error_size, "multi-stakeholder mode requires stakeholders");
      return X402_STATUS_POLICY_ERROR;
    }
    if(policy->splitter_contract[0] == '\0') {
      snprintf(error, error_size, "multi-stakeholder mode requires splitter_contract");
      return X402_STATUS_POLICY_ERROR;
    }
    if(policy->stakeholder_count > X402_MAX_STAKEHOLDERS) {
      snprintf(error, error_size, "too many stakeholders");
      return X402_STATUS_POLICY_ERROR;
    }

    for(i = 0; i < policy->stakeholder_count; ++i) {
      total_bps += policy->stakeholders[i].basis_points;
    }

    if(total_bps != 10000) {
      snprintf(error, error_size, "stakeholder basis points must sum to 10000");
      return X402_STATUS_POLICY_ERROR;
    }
  }

  if(policy->credits.enabled && policy->credits.max_multiplier == 0) {
    snprintf(error, error_size, "prepay enabled requires max_multiplier > 0");
    return X402_STATUS_POLICY_ERROR;
  }

  if(policy->forward_to[0] != '\0') {
    if(!policy->credits.enabled) {
      snprintf(error, error_size, "forward_to requires prepaid credits");
      return X402_STATUS_POLICY_ERROR;
    }
    if(policy->credits_issued_override == 0) {
      snprintf(error, error_size, "forward_to requires credits_issued_override");
      return X402_STATUS_POLICY_ERROR;
    }
  }

  snprintf(error, error_size, "ok");
  return X402_STATUS_OK;
}

uint64_t x402_calculate_stakeholder_amount(uint64_t total_amount,
                                           size_t stakeholder_index,
                                           const x402_route_policy *policy)
{
  size_t i;
  uint64_t paid = 0;

  if(policy == NULL || stakeholder_index >= policy->stakeholder_count) {
    return 0;
  }

  for(i = 0; i < policy->stakeholder_count; ++i) {
    uint64_t share = (total_amount * policy->stakeholders[i].basis_points) / 10000U;

    if(i == stakeholder_index) {
      if(i == policy->stakeholder_count - 1) {
        return total_amount - paid;
      }
      return share;
    }

    if(i == policy->stakeholder_count - 1) {
      paid = total_amount;
    }
    else {
      paid += share;
    }
  }

  return 0;
}

x402_status x402_build_payment_required_json(const x402_route_policy *policy,
                                             const x402_payment_requirements *requirements,
                                             char *buffer,
                                             size_t buffer_size)
{
  x402_status status;
  size_t offset = 0;

  if(policy == NULL || requirements == NULL || buffer == NULL || buffer_size == 0) {
    return X402_STATUS_INVALID_ARGUMENT;
  }

  buffer[0] = '\0';

  status = x402_appendf(
      buffer, buffer_size, &offset,
      "{\"x402Version\":2,\"accepts\":[{\"scheme\":\"%s\",\"network\":\"%s\","
      "\"asset\":\"%s\",\"amount\":\"%" PRIu64 "\",\"payTo\":\"%s\","
      "\"maxTimeoutSeconds\":%u,\"extra\":{\"mechanism\":\"%s\",\"profile\":\"%s\","
      "\"payToKind\":\"%s\",\"areFeesSponsored\":true}}],\"resource\":{\"url\":\"%s\",\"description\":\"%s\","
      "\"mimeType\":\"%s\"},\"extensions\":{\"payment-identifier\":{\"required\":%s}",
      policy->scheme,
      policy->network,
      policy->asset,
      requirements->amount,
      requirements->pay_to,
      requirements->timeout_seconds,
      policy->mechanism,
      strcmp(policy->mechanism, "stellar") == 0 ? "sep41-exact-v1" : "custom-v1",
      policy->split_mode == X402_SPLIT_MULTI ? "splitter-contract" : "direct-recipient",
      policy->route,
      policy->description,
      policy->mime_type,
      policy->payment_identifier_required ? "true" : "false");
  if(status != X402_STATUS_OK) {
    return status;
  }

  if(policy->split_mode == X402_SPLIT_MULTI) {
    status = x402_appendf(
        buffer, buffer_size, &offset,
        ",\"stakeholder-split\":{\"mode\":\"multi\",\"contract\":\"%s\","
        "\"execution\":\"%s\",\"shares\":[",
        policy->splitter_contract,
        x402_split_execution_name(policy));
    if(status != X402_STATUS_OK) {
      return status;
    }

    for(size_t i = 0; i < policy->stakeholder_count; ++i) {
      status = x402_appendf(
          buffer, buffer_size, &offset,
          "%s{\"name\":\"%s\",\"bps\":%u,\"destination\":\"%s\"}",
          i == 0 ? "" : ",",
          policy->stakeholders[i].name,
          policy->stakeholders[i].basis_points,
          policy->stakeholders[i].destination);
      if(status != X402_STATUS_OK) {
        return status;
      }
    }

    status = x402_append(buffer, buffer_size, &offset, "]}");
    if(status != X402_STATUS_OK) {
      return status;
    }
  }

  if(policy->credits.enabled) {
    size_t i;
    static const uint32_t options[] = {1U, 2U, 10U, 100U};

    status = x402_appendf(
        buffer, buffer_size, &offset,
        ",\"prepaid-requests\":{\"supported\":true,\"maxMultiplier\":%u,"
        "\"creditScope\":\"%s\",\"unit\":\"requests\",\"options\":[",
        policy->credits.max_multiplier,
        x402_credit_scope_name(policy->credits.scope));
    if(status != X402_STATUS_OK) {
      return status;
    }
    for(i = 0; i < sizeof(options) / sizeof(options[0]); ++i) {
      uint64_t option_amount;
      if(!x402_prepaid_option_supported(policy, options[i])) {
        continue;
      }
      option_amount = policy->amount * (uint64_t)options[i];
      status = x402_appendf(
          buffer,
          buffer_size,
          &offset,
          "%s{\"multiplier\":%u,\"amount\":\"%" PRIu64 "\",\"creditsIssued\":%u}",
          buffer[offset - 1] == '[' ? "" : ",",
          options[i],
          option_amount,
          options[i]);
      if(status != X402_STATUS_OK) {
        return status;
      }
    }
    status = x402_append(buffer, buffer_size, &offset, "]}");
    if(status != X402_STATUS_OK) {
      return status;
    }
  }

  if(policy->credits.enabled && x402_policy_uses_stellar(policy)) {
    status = x402_append(
        buffer,
        buffer_size,
        &offset,
        ",\"stellar-signin\":{\"supported\":true,\"challengeHeader\":\"X402-Stellar-Auth-Challenge\","
        "\"responseHeader\":\"X402-Stellar-Auth\",\"scheme\":\"stellar-signin-v1\"}");
    if(status != X402_STATUS_OK) {
      return status;
    }
  }

  return x402_append(buffer, buffer_size, &offset, "}}");
}

x402_status x402_build_payment_response_json(const x402_route_policy *policy,
                                             const x402_settlement_result *result,
                                             char *buffer,
                                             size_t buffer_size)
{
  size_t offset = 0;

  if(policy == NULL || result == NULL || buffer == NULL || buffer_size == 0) {
    return X402_STATUS_INVALID_ARGUMENT;
  }

  if(result->settled) {
    x402_status status = x402_appendf(
        buffer, buffer_size, &offset,
        "{\"success\":true,\"scheme\":\"%s\",\"network\":\"%s\","
        "\"payer\":\"%s\",\"transaction\":\"%s\",\"settlementMode\":\"%s\","
        "\"extensions\":{",
        policy->scheme,
        policy->network,
        result->payer,
        result->transaction_ref,
        result->settlement_mode);
    if(status != X402_STATUS_OK) {
      return status;
    }

    if(policy->credits.enabled) {
      status = x402_appendf(
          buffer, buffer_size, &offset,
          "\"prepaid-requests\":{\"issued\":%u,\"remaining\":%u,\"scope\":\"%s\"}",
          result->credits_issued,
          result->credits_remaining,
          x402_credit_scope_name(policy->credits.scope));
      if(status != X402_STATUS_OK) {
        return status;
      }
    }

    if(policy->split_mode == X402_SPLIT_MULTI) {
      status = x402_appendf(
          buffer, buffer_size, &offset,
          "%s\"stakeholder-split\":{\"mode\":\"multi\",\"contract\":\"%s\","
          "\"execution\":\"%s\"}",
          policy->credits.enabled ? "," : "",
          policy->splitter_contract,
          x402_split_execution_name(policy));
      if(status != X402_STATUS_OK) {
        return status;
      }
    }

    if(result->session_token[0] != '\0') {
      status = x402_appendf(
          buffer, buffer_size, &offset,
          "%s\"stellar-session-auth\":{\"token\":\"%s\",\"header\":\"X402-Session\","
          "\"scheme\":\"stellar-prepaid-session-v1\",\"expiresAt\":%" PRIu64 "}",
          (policy->credits.enabled || policy->split_mode == X402_SPLIT_MULTI) ? "," : "",
          result->session_token,
          result->session_expires_at);
      if(status != X402_STATUS_OK) {
        return status;
      }
    }

    return x402_append(buffer, buffer_size, &offset, "}}");
  }

  return x402_appendf(
      buffer, buffer_size, &offset,
      "{\"success\":false,\"code\":\"%s\",\"message\":\"%s\",\"retryable\":true}",
      result->error_code[0] == '\0' ? "settlement_failed" : result->error_code,
      result->message[0] == '\0' ? "payment failed" : result->message);
}

static const char *x402_find_json_key(const char *json, const char *key)
{
  char pattern[96];
  size_t pattern_len;
  const char *at;
  const char *p;

  if(json == NULL || key == NULL) {
    return NULL;
  }

  if(snprintf(pattern, sizeof(pattern), "\"%s\"", key) < 0) {
    return NULL;
  }

  pattern_len = strlen(pattern);
  at = json;
  while((at = strstr(at, pattern)) != NULL) {
    p = at + pattern_len;
    while(*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r') {
      ++p;
    }
    if(*p == ':') {
      return at;
    }
    at += pattern_len;
  }
  return NULL;
}

x402_status x402_extract_json_string(const char *json,
                                     const char *key,
                                     char *buffer,
                                     size_t buffer_size)
{
  const char *at;
  const char *quote;
  const char *end;
  size_t len;

  if(json == NULL || key == NULL || buffer == NULL || buffer_size == 0) {
    return X402_STATUS_INVALID_ARGUMENT;
  }

  at = x402_find_json_key(json, key);
  if(at == NULL) {
    return X402_STATUS_VERIFY_ERROR;
  }

  quote = strchr(at, ':');
  if(quote == NULL) {
    return X402_STATUS_VERIFY_ERROR;
  }

  quote = strchr(quote, '"');
  if(quote == NULL) {
    return X402_STATUS_VERIFY_ERROR;
  }

  ++quote;
  end = strchr(quote, '"');
  if(end == NULL) {
    return X402_STATUS_VERIFY_ERROR;
  }

  len = (size_t)(end - quote);
  if(len + 1 > buffer_size) {
    return X402_STATUS_BUFFER_TOO_SMALL;
  }

  memcpy(buffer, quote, len);
  buffer[len] = '\0';
  return X402_STATUS_OK;
}

x402_status x402_extract_json_uint32(const char *json,
                                     const char *key,
                                     uint32_t *value)
{
  const char *at;
  const char *colon;
  char *endptr;
  unsigned long parsed;

  if(json == NULL || key == NULL || value == NULL) {
    return X402_STATUS_INVALID_ARGUMENT;
  }

  at = x402_find_json_key(json, key);
  if(at == NULL) {
    return X402_STATUS_VERIFY_ERROR;
  }

  colon = strchr(at, ':');
  if(colon == NULL) {
    return X402_STATUS_VERIFY_ERROR;
  }

  parsed = strtoul(colon + 1, &endptr, 10);
  if(endptr == colon + 1) {
    return X402_STATUS_VERIFY_ERROR;
  }

  *value = (uint32_t)parsed;
  return X402_STATUS_OK;
}

x402_status x402_parse_payment_payload(const char *json,
                                       x402_payment_payload_view *view)
{
  if(json == NULL || view == NULL) {
    return X402_STATUS_INVALID_ARGUMENT;
  }

  memset(view, 0, sizeof(*view));
  view->multiplier = 1;

  x402_extract_json_string(json, "scheme", view->scheme, sizeof(view->scheme));
  x402_extract_json_string(json, "network", view->network, sizeof(view->network));
  x402_extract_json_string(json, "payer", view->payer, sizeof(view->payer));
  x402_extract_json_string(json,
                           "paymentIdentifier",
                           view->payment_identifier,
                           sizeof(view->payment_identifier));
  x402_extract_json_string(json,
                           "transaction",
                           view->transaction,
                           sizeof(view->transaction));
  x402_extract_json_uint32(json, "multiplier", &view->multiplier);

  return X402_STATUS_OK;
}
