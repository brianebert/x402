#if defined(__has_include)
#  if __has_include(<httpd.h>) && __has_include(<http_config.h>) && __has_include(<http_protocol.h>)
#    define X402_HAVE_APACHE_HEADERS 1
#  endif
#endif

#ifdef X402_HAVE_APACHE_HEADERS

#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#include <apr_base64.h>
#include <apr_lib.h>
#include <apr_strings.h>
#include <apr_tables.h>
#include <apr_thread_mutex.h>
#include <apr_time.h>
#include <apr_uuid.h>
#include <httpd.h>
#include <http_config.h>
#include <http_core.h>
#include <http_log.h>
#include <http_protocol.h>
#include <http_request.h>
#include <sqlite3.h>
#include <sodium.h>
#include <syslog.h>

#include "../providers/stellar/stellar_provider.h"
#include "../core/x402_provider.h"

extern module AP_MODULE_DECLARE_DATA x402_module;

#define X402_DEFAULT_CREDIT_DB_PATH "/var/lib/x402/credits.db"

typedef struct x402_dir_config {
  int enabled;
  int pay_to_set;
  int split_mode_set;
  int splitter_contract_set;
  x402_route_policy policy;
} x402_dir_config;

typedef struct x402_server_config {
  int split_mode_set;
  x402_split_mode split_mode;
  int splitter_contract_set;
  char splitter_contract[X402_MAX_DESTINATION];
  int stakeholder_overflow;
  size_t stakeholder_count;
  x402_stakeholder stakeholders[X402_MAX_STAKEHOLDERS];
} x402_server_config;
static apr_thread_mutex_t *x402_credit_mutex = NULL;
static sqlite3 *x402_credit_db = NULL;
static char x402_credit_db_path[X402_MAX_PATH] = X402_DEFAULT_CREDIT_DB_PATH;
static sqlite3_int64 x402_credit_db_last_cleanup = 0;
static int x402_same_route(const char *left, const char *right);

static int x402_server_has_global_split(const x402_server_config *cfg)
{
  return cfg != NULL && cfg->split_mode_set && cfg->split_mode == X402_SPLIT_MULTI;
}

static const char *x402_apply_global_split_policy(request_rec *r,
                                                  x402_route_policy *policy,
                                                  int route_pay_to_set,
                                                  int route_split_mode_set,
                                                  int route_splitter_contract_set)
{
  x402_server_config *server_cfg;
  x402_stakeholder route_stakeholders[X402_MAX_STAKEHOLDERS];
  size_t route_stakeholder_count;
  size_t i;

  if(r == NULL || policy == NULL) {
    return NULL;
  }

  server_cfg = (x402_server_config *)ap_get_module_config(r->server->module_config,
                                                          &x402_module);
  if(!x402_server_has_global_split(server_cfg)) {
    return NULL;
  }
  if(server_cfg->stakeholder_overflow) {
    return "too many stakeholders after merging systemwide and vhost split policy";
  }

  route_stakeholder_count = policy->stakeholder_count;
  if(route_stakeholder_count > X402_MAX_STAKEHOLDERS) {
    route_stakeholder_count = X402_MAX_STAKEHOLDERS;
  }
  memcpy(route_stakeholders,
         policy->stakeholders,
         route_stakeholder_count * sizeof(route_stakeholders[0]));

  if(route_pay_to_set || route_split_mode_set || route_splitter_contract_set) {
    ap_log_rerror(APLOG_MARK,
                  APLOG_WARNING,
                  0,
                  r,
                  "x402: systemwide split policy overrides route pay-to/split mode/contract for %s",
                  policy->route[0] == '\0' ? r->uri : policy->route);
  }

  policy->split_mode = X402_SPLIT_MULTI;
  policy->pay_to[0] = '\0';
  snprintf(policy->splitter_contract,
           sizeof(policy->splitter_contract),
           "%s",
           server_cfg->splitter_contract);
  policy->stakeholder_count = 0;

  for(i = 0; i < server_cfg->stakeholder_count; ++i) {
    if(policy->stakeholder_count >= X402_MAX_STAKEHOLDERS) {
      return "too many stakeholders after applying systemwide split policy";
    }
    policy->stakeholders[policy->stakeholder_count++] = server_cfg->stakeholders[i];
  }
  for(i = 0; i < route_stakeholder_count; ++i) {
    if(policy->stakeholder_count >= X402_MAX_STAKEHOLDERS) {
      return "too many stakeholders after applying systemwide split policy";
    }
    policy->stakeholders[policy->stakeholder_count++] = route_stakeholders[i];
  }

  return NULL;
}

#define X402_STELLAR_AUTH_HEADER "X402-Stellar-Auth"
#define X402_STELLAR_AUTH_CHALLENGE_HEADER "X402-Stellar-Auth-Challenge"
#define X402_STELLAR_AUTH_CHALLENGE_TTL 300
#define X402_DB_CLEANUP_INTERVAL 300

#define X402_ABUSE_SCOPE_IP "ip"
#define X402_ABUSE_SCOPE_PAYER "payer"
#define X402_ABUSE_BUCKET_UNPAID "unpaid"
#define X402_ABUSE_BUCKET_BAD_PAYMENT "bad-payment"
#define X402_ABUSE_BUCKET_BAD_PREPAID_AUTH "bad-prepaid-auth"
#define X402_ABUSE_BUCKET_REPLAYED_CHALLENGE "replayed-challenge"
#define X402_ABUSE_UNPAID_LIMIT 30
#define X402_ABUSE_UNPAID_WINDOW 60
#define X402_ABUSE_UNPAID_BLOCK 60
#define X402_ABUSE_BAD_PAYMENT_LIMIT 10
#define X402_ABUSE_BAD_PAYMENT_WINDOW 600
#define X402_ABUSE_BAD_PAYMENT_BLOCK 300
#define X402_ABUSE_BAD_PREPAID_AUTH_LIMIT 10
#define X402_ABUSE_BAD_PREPAID_AUTH_WINDOW 600
#define X402_ABUSE_BAD_PREPAID_AUTH_BLOCK 300
#define X402_ABUSE_REPLAY_LIMIT 5
#define X402_ABUSE_REPLAY_WINDOW 600
#define X402_ABUSE_REPLAY_BLOCK 600

static const x402_provider *x402_get_provider(const x402_route_policy *policy)
{
  if(policy != NULL && strcmp(policy->mechanism, "stellar") == 0) {
    return &x402_stellar_provider;
  }
  return NULL;
}

static int x402_policy_uses_stellar(const x402_route_policy *policy)
{
  return policy != NULL && strncmp(policy->network, "stellar:", 8) == 0;
}

static const char *x402_client_key(request_rec *r)
{
  if(r != NULL && r->useragent_ip != NULL && r->useragent_ip[0] != '\0') {
    return r->useragent_ip;
  }
  return "unknown";
}

static char *x402_normalize_route(apr_pool_t *pool, const char *route)
{
  size_t length;

  if(pool == NULL || route == NULL || route[0] == '\0') {
    return apr_pstrdup(pool, "/");
  }

  length = strlen(route);
  while(length > 1 && route[length - 1] == '/') {
    --length;
  }
  return apr_pstrmemdup(pool, route, length);
}

static int x402_base32_value(char ch)
{
  ch = (char)toupper((unsigned char)ch);
  if(ch >= 'A' && ch <= 'Z') {
    return ch - 'A';
  }
  if(ch >= '2' && ch <= '7') {
    return 26 + (ch - '2');
  }
  return -1;
}

static uint16_t x402_crc16_xmodem(const unsigned char *data, size_t length)
{
  uint16_t crc = 0;
  size_t i;

  for(i = 0; i < length; ++i) {
    int bit;

    crc ^= (uint16_t)data[i] << 8;
    for(bit = 0; bit < 8; ++bit) {
      crc = (crc & 0x8000U) != 0 ? (uint16_t)((crc << 1) ^ 0x1021U) : (uint16_t)(crc << 1);
    }
  }
  return crc;
}

static int x402_decode_stellar_strkey(char expected_version_char,
                                      unsigned char expected_version_byte,
                                      const char *input,
                                      unsigned char *raw_out,
                                      size_t raw_out_size)
{
  unsigned char decoded[64];
  size_t decoded_len = 0;
  unsigned int buffer = 0;
  int bits = 0;
  size_t i;

  if(input == NULL || raw_out == NULL || raw_out_size != 32 || input[0] != expected_version_char) {
    return 0;
  }

  memset(decoded, 0, sizeof(decoded));
  for(i = 0; input[i] != '\0'; ++i) {
    int value = x402_base32_value(input[i]);

    if(value < 0) {
      return 0;
    }
    buffer = (buffer << 5) | (unsigned int)value;
    bits += 5;
    while(bits >= 8) {
      bits -= 8;
      if(decoded_len >= sizeof(decoded)) {
        return 0;
      }
      decoded[decoded_len++] = (unsigned char)((buffer >> bits) & 0xffU);
    }
  }

  if(decoded_len < 35 || decoded[0] != expected_version_byte) {
    return 0;
  }

  if(x402_crc16_xmodem(decoded, 33) != (uint16_t)(decoded[33] | (decoded[34] << 8))) {
    return 0;
  }

  memcpy(raw_out, decoded + 1, 32);
  return 1;
}

static void *x402_create_dir_config(apr_pool_t *pool, char *path)
{
  x402_dir_config *cfg = (x402_dir_config *)apr_pcalloc(pool, sizeof(*cfg));

  (void)path;
  cfg->enabled = 0;
  snprintf(cfg->policy.resource_method, sizeof(cfg->policy.resource_method), "GET");
  snprintf(cfg->policy.scheme, sizeof(cfg->policy.scheme), "exact");
  snprintf(cfg->policy.mime_type, sizeof(cfg->policy.mime_type), "application/json");
  cfg->policy.split_mode = X402_SPLIT_SINGLE;
  cfg->policy.settlement_mode = X402_SETTLEMENT_HYBRID;
  cfg->policy.stellar_local_backend = X402_STELLAR_BACKEND_AUTO;
  cfg->policy.payment_identifier_required = 1;
  cfg->policy.timeout_seconds = 30;
  snprintf(cfg->policy.stellar_rpc_url,
           sizeof(cfg->policy.stellar_rpc_url),
           "%s",
           "https://soroban-testnet.stellar.org:443");
  snprintf(cfg->policy.stellar_network_passphrase,
           sizeof(cfg->policy.stellar_network_passphrase),
           "%s",
           "Test SDF Network ; September 2015");
  cfg->policy.credits.scope = X402_CREDIT_SCOPE_PAYER_ROUTE;
  return cfg;
}

static void *x402_merge_dir_config(apr_pool_t *pool, void *basev, void *addv)
{
  x402_dir_config *base = (x402_dir_config *)basev;
  x402_dir_config *add = (x402_dir_config *)addv;
  x402_dir_config *merged = (x402_dir_config *)apr_pcalloc(pool, sizeof(*merged));

  *merged = *base;

  if(add->enabled) {
    *merged = *add;
  }

  return merged;
}

static void *x402_create_server_config(apr_pool_t *pool, server_rec *server)
{
  x402_server_config *cfg = (x402_server_config *)apr_pcalloc(pool, sizeof(*cfg));

  (void)server;
  cfg->split_mode = X402_SPLIT_SINGLE;
  return cfg;
}

static void *x402_merge_server_config(apr_pool_t *pool, void *basev, void *addv)
{
  x402_server_config *base = (x402_server_config *)basev;
  x402_server_config *add = (x402_server_config *)addv;
  x402_server_config *merged = (x402_server_config *)apr_pcalloc(pool, sizeof(*merged));
  size_t i;

  *merged = *base;
  if(add->split_mode_set) {
    merged->split_mode_set = add->split_mode_set;
    merged->split_mode = add->split_mode;
  }
  if(add->splitter_contract_set) {
    merged->splitter_contract_set = add->splitter_contract_set;
    snprintf(merged->splitter_contract,
             sizeof(merged->splitter_contract),
             "%s",
             add->splitter_contract);
  }
  merged->stakeholder_overflow = base->stakeholder_overflow || add->stakeholder_overflow;
  for(i = 0; i < add->stakeholder_count; ++i) {
    if(merged->stakeholder_count >= X402_MAX_STAKEHOLDERS) {
      merged->stakeholder_overflow = 1;
      continue;
    }
    merged->stakeholders[merged->stakeholder_count++] = add->stakeholders[i];
  }

  return merged;
}

static const char *x402_set_enabled(cmd_parms *cmd, void *cfgv, int flag)
{
  x402_dir_config *cfg = (x402_dir_config *)cfgv;
  cfg->enabled = flag;
  snprintf(cfg->policy.route, sizeof(cfg->policy.route), "%s", cmd->path == NULL ? "/" : cmd->path);
  return NULL;
}

static const char *x402_set_string(char *target, size_t size, const char *value)
{
  if(value == NULL) {
    return "missing value";
  }
  snprintf(target, size, "%s", value);
  return NULL;
}

static const char *x402_cmd_scheme(cmd_parms *cmd, void *cfgv, const char *arg)
{
  x402_dir_config *cfg = (x402_dir_config *)cfgv;
  (void)cmd;
  return x402_set_string(cfg->policy.scheme, sizeof(cfg->policy.scheme), arg);
}

static const char *x402_cmd_network(cmd_parms *cmd, void *cfgv, const char *arg)
{
  x402_dir_config *cfg = (x402_dir_config *)cfgv;
  (void)cmd;
  return x402_set_string(cfg->policy.network, sizeof(cfg->policy.network), arg);
}

static const char *x402_cmd_asset(cmd_parms *cmd, void *cfgv, const char *arg)
{
  x402_dir_config *cfg = (x402_dir_config *)cfgv;
  (void)cmd;
  return x402_set_string(cfg->policy.asset, sizeof(cfg->policy.asset), arg);
}

static const char *x402_cmd_amount(cmd_parms *cmd, void *cfgv, const char *arg)
{
  char *endptr = NULL;
  x402_dir_config *cfg = (x402_dir_config *)cfgv;
  unsigned long long value;

  (void)cmd;
  value = strtoull(arg, &endptr, 10);
  if(endptr == arg || *endptr != '\0') {
    return "X402Amount must be an integer string";
  }
  cfg->policy.amount = (uint64_t)value;
  return NULL;
}

static const char *x402_cmd_description(cmd_parms *cmd, void *cfgv, const char *arg)
{
  x402_dir_config *cfg = (x402_dir_config *)cfgv;
  (void)cmd;
  return x402_set_string(cfg->policy.description, sizeof(cfg->policy.description), arg);
}

static const char *x402_cmd_mime_type(cmd_parms *cmd, void *cfgv, const char *arg)
{
  x402_dir_config *cfg = (x402_dir_config *)cfgv;
  (void)cmd;
  return x402_set_string(cfg->policy.mime_type, sizeof(cfg->policy.mime_type), arg);
}

static const char *x402_cmd_mechanism(cmd_parms *cmd, void *cfgv, const char *arg)
{
  x402_dir_config *cfg = (x402_dir_config *)cfgv;
  (void)cmd;
  return x402_set_string(cfg->policy.mechanism, sizeof(cfg->policy.mechanism), arg);
}

static const char *x402_cmd_settlement_mode(cmd_parms *cmd, void *cfgv, const char *arg)
{
  x402_dir_config *cfg = (x402_dir_config *)cfgv;
  (void)cmd;
  if(strcmp(arg, "local") == 0) {
    cfg->policy.settlement_mode = X402_SETTLEMENT_LOCAL;
  }
  else if(strcmp(arg, "facilitator") == 0) {
    cfg->policy.settlement_mode = X402_SETTLEMENT_FACILITATOR;
  }
  else if(strcmp(arg, "hybrid") == 0) {
    cfg->policy.settlement_mode = X402_SETTLEMENT_HYBRID;
  }
  else {
    return "X402SettlementMode must be local, facilitator, or hybrid";
  }
  return NULL;
}

static const char *x402_cmd_facilitator_url(cmd_parms *cmd, void *cfgv, const char *arg)
{
  x402_dir_config *cfg = (x402_dir_config *)cfgv;
  (void)cmd;
  return x402_set_string(cfg->policy.facilitator_url, sizeof(cfg->policy.facilitator_url), arg);
}

static const char *x402_cmd_facilitator_api_key(cmd_parms *cmd, void *cfgv, const char *arg)
{
  x402_dir_config *cfg = (x402_dir_config *)cfgv;
  (void)cmd;
  return x402_set_string(cfg->policy.facilitator_api_key,
                         sizeof(cfg->policy.facilitator_api_key),
                         arg);
}

static const char *x402_trim_secret(char *value)
{
  size_t len;

  if(value == NULL) {
    return "missing secret content";
  }
  while(*value != '\0' && apr_isspace(*value)) {
    ++value;
  }
  len = strlen(value);
  while(len > 0 && apr_isspace(value[len - 1])) {
    value[--len] = '\0';
  }
  if(len == 0) {
    return "secret file was empty";
  }
  return NULL;
}

static const char *x402_cmd_facilitator_api_key_file(cmd_parms *cmd, void *cfgv, const char *arg)
{
  x402_dir_config *cfg = (x402_dir_config *)cfgv;
  apr_file_t *file = NULL;
  apr_finfo_t finfo;
  apr_status_t rv;
  apr_size_t bytes_read;
  apr_pool_t *pool;
  char *buffer;
  const char *trim_error;

  if(arg == NULL || arg[0] == '\0') {
    return "X402FacilitatorAPIKeyFile requires a file path";
  }

  pool = cmd->temp_pool != NULL ? cmd->temp_pool : cmd->pool;
  rv = apr_file_open(&file, arg, APR_READ | APR_BINARY, APR_OS_DEFAULT, pool);
  if(rv != APR_SUCCESS) {
    return "X402FacilitatorAPIKeyFile could not open file";
  }
  rv = apr_file_info_get(&finfo, APR_FINFO_SIZE, file);
  if(rv != APR_SUCCESS || finfo.size <= 0 || finfo.size >= (apr_off_t)sizeof(cfg->policy.facilitator_api_key)) {
    apr_file_close(file);
    return "X402FacilitatorAPIKeyFile size was invalid";
  }

  buffer = (char *)apr_pcalloc(pool, (apr_size_t)finfo.size + 1);
  bytes_read = (apr_size_t)finfo.size;
  rv = apr_file_read_full(file, buffer, bytes_read, &bytes_read);
  apr_file_close(file);
  if(rv != APR_SUCCESS) {
    return "X402FacilitatorAPIKeyFile could not read file";
  }

  trim_error = x402_trim_secret(buffer);
  if(trim_error != NULL) {
    return trim_error;
  }
  return x402_set_string(cfg->policy.facilitator_api_key,
                         sizeof(cfg->policy.facilitator_api_key),
                         buffer);
}

static const char *x402_cmd_timeout(cmd_parms *cmd, void *cfgv, const char *arg)
{
  char *endptr = NULL;
  x402_dir_config *cfg = (x402_dir_config *)cfgv;
  unsigned long value;

  (void)cmd;
  value = strtoul(arg, &endptr, 10);
  if(endptr == arg || *endptr != '\0') {
    return "X402TimeoutSeconds must be an integer";
  }
  cfg->policy.timeout_seconds = (uint32_t)value;
  return NULL;
}

static const char *x402_cmd_stellar_config_dir(cmd_parms *cmd, void *cfgv, const char *arg)
{
  x402_dir_config *cfg = (x402_dir_config *)cfgv;
  (void)cmd;
  return x402_set_string(cfg->policy.stellar_config_dir,
                         sizeof(cfg->policy.stellar_config_dir),
                         arg);
}

static const char *x402_cmd_stellar_source_account(cmd_parms *cmd, void *cfgv, const char *arg)
{
  x402_dir_config *cfg = (x402_dir_config *)cfgv;
  (void)cmd;
  return x402_set_string(cfg->policy.stellar_source_account,
                         sizeof(cfg->policy.stellar_source_account),
                         arg);
}

static const char *x402_cmd_stellar_rpc_url(cmd_parms *cmd, void *cfgv, const char *arg)
{
  x402_dir_config *cfg = (x402_dir_config *)cfgv;
  (void)cmd;
  return x402_set_string(cfg->policy.stellar_rpc_url,
                         sizeof(cfg->policy.stellar_rpc_url),
                         arg);
}

static const char *x402_cmd_stellar_network_passphrase(cmd_parms *cmd,
                                                       void *cfgv,
                                                       const char *arg)
{
  x402_dir_config *cfg = (x402_dir_config *)cfgv;
  (void)cmd;
  return x402_set_string(cfg->policy.stellar_network_passphrase,
                         sizeof(cfg->policy.stellar_network_passphrase),
                         arg);
}

static const char *x402_cmd_stellar_local_backend(cmd_parms *cmd, void *cfgv, const char *arg)
{
  x402_dir_config *cfg = (x402_dir_config *)cfgv;
  (void)cmd;
  if(strcmp(arg, "auto") == 0) {
    cfg->policy.stellar_local_backend = X402_STELLAR_BACKEND_AUTO;
  }
  else if(strcmp(arg, "inprocess") == 0) {
    cfg->policy.stellar_local_backend = X402_STELLAR_BACKEND_INPROCESS;
  }
  else {
    return "X402StellarLocalBackend must be auto or inprocess";
  }
  return NULL;
}

static const char *x402_cmd_payment_identifier(cmd_parms *cmd, void *cfgv, const char *arg)
{
  x402_dir_config *cfg = (x402_dir_config *)cfgv;
  (void)cmd;
  if(strcmp(arg, "required") == 0) {
    cfg->policy.payment_identifier_required = 1;
  }
  else if(strcmp(arg, "optional") == 0 || strcmp(arg, "off") == 0) {
    cfg->policy.payment_identifier_required = 0;
  }
  else {
    return "X402PaymentIdentifier must be required, optional, or off";
  }
  return NULL;
}

static const char *x402_cmd_pay_to(cmd_parms *cmd, void *cfgv, const char *arg)
{
  x402_server_config *server_cfg;
  x402_dir_config *cfg = (x402_dir_config *)cfgv;

  server_cfg = (x402_server_config *)ap_get_module_config(cmd->server->module_config,
                                                          &x402_module);
  if(x402_server_has_global_split(server_cfg)) {
    return "X402PayTo cannot be set inside a route when a systemwide split policy is configured";
  }
  cfg->pay_to_set = 1;
  return x402_set_string(cfg->policy.pay_to, sizeof(cfg->policy.pay_to), arg);
}

static const char *x402_cmd_split_mode(cmd_parms *cmd, void *cfgv, const char *arg)
{
  x402_server_config *server_cfg;
  x402_dir_config *cfg = (x402_dir_config *)cfgv;

  if(cmd->path == NULL) {
    server_cfg = (x402_server_config *)ap_get_module_config(cmd->server->module_config,
                                                            &x402_module);
    if(cmd->server->is_virtual) {
      return "X402SplitMode is only allowed in serverwide config or route/location config";
    }
    if(strcmp(arg, "multi") != 0) {
      return "systemwide X402SplitMode must be multi";
    }
    server_cfg->split_mode_set = 1;
    server_cfg->split_mode = X402_SPLIT_MULTI;
    return NULL;
  }

  server_cfg = (x402_server_config *)ap_get_module_config(cmd->server->module_config,
                                                          &x402_module);
  if(x402_server_has_global_split(server_cfg)) {
    return "X402SplitMode cannot be set inside a route when a systemwide split policy is configured";
  }

  if(strcmp(arg, "single") == 0) {
    cfg->policy.split_mode = X402_SPLIT_SINGLE;
  }
  else if(strcmp(arg, "multi") == 0) {
    cfg->policy.split_mode = X402_SPLIT_MULTI;
  }
  else {
    return "X402SplitMode must be single or multi";
  }
  cfg->split_mode_set = 1;
  return NULL;
}

static const char *x402_cmd_splitter_contract(cmd_parms *cmd, void *cfgv, const char *arg)
{
  x402_server_config *server_cfg;
  x402_dir_config *cfg = (x402_dir_config *)cfgv;

  if(cmd->path == NULL) {
    server_cfg = (x402_server_config *)ap_get_module_config(cmd->server->module_config,
                                                            &x402_module);
    if(cmd->server->is_virtual) {
      return "X402SplitterContract is only allowed in serverwide config or route/location config";
    }
    server_cfg->splitter_contract_set = 1;
    return x402_set_string(server_cfg->splitter_contract,
                           sizeof(server_cfg->splitter_contract),
                           arg);
  }

  server_cfg = (x402_server_config *)ap_get_module_config(cmd->server->module_config,
                                                          &x402_module);
  if(x402_server_has_global_split(server_cfg)) {
    return "X402SplitterContract cannot be set inside a route when a systemwide split policy is configured";
  }
  cfg->splitter_contract_set = 1;
  return x402_set_string(cfg->policy.splitter_contract,
                         sizeof(cfg->policy.splitter_contract),
                         arg);
}

static const char *x402_cmd_stakeholder(cmd_parms *cmd,
                                        void *cfgv,
                                        const char *name,
                                        const char *bps,
                                        const char *destination)
{
  char *endptr = NULL;
  x402_server_config *server_cfg;
  x402_dir_config *cfg = (x402_dir_config *)cfgv;
  unsigned long value;
  x402_stakeholder *stakeholder;
  size_t index;

  value = strtoul(bps, &endptr, 10);
  if(endptr == bps || *endptr != '\0' || value > 10000) {
    return "X402Stakeholder basis points must be an integer between 0 and 10000";
  }

  if(cmd->path == NULL) {
    server_cfg = (x402_server_config *)ap_get_module_config(cmd->server->module_config,
                                                            &x402_module);
    index = server_cfg->stakeholder_count;
    if(index >= X402_MAX_STAKEHOLDERS) {
      return "too many X402Stakeholder directives";
    }
    stakeholder = &server_cfg->stakeholders[index];
    server_cfg->stakeholder_count++;
  }
  else {
    index = cfg->policy.stakeholder_count;
    if(index >= X402_MAX_STAKEHOLDERS) {
      return "too many X402Stakeholder directives";
    }
    stakeholder = &cfg->policy.stakeholders[index];
    cfg->policy.stakeholder_count++;
  }

  snprintf(stakeholder->name,
           sizeof(stakeholder->name),
           "%s",
           name);
  stakeholder->basis_points = (uint16_t)value;
  snprintf(stakeholder->destination,
           sizeof(stakeholder->destination),
           "%s",
           destination);
  return NULL;
}

static const char *x402_cmd_prepay(cmd_parms *cmd, void *cfgv, int flag)
{
  x402_dir_config *cfg = (x402_dir_config *)cfgv;
  (void)cmd;
  cfg->policy.credits.enabled = flag;
  return NULL;
}

static const char *x402_cmd_prepay_multiplier(cmd_parms *cmd, void *cfgv, const char *arg)
{
  char *endptr = NULL;
  x402_dir_config *cfg = (x402_dir_config *)cfgv;
  unsigned long value;

  (void)cmd;
  value = strtoul(arg, &endptr, 10);
  if(endptr == arg || *endptr != '\0') {
    return "X402PrepayMultiplierMax must be an integer";
  }
  cfg->policy.credits.max_multiplier = (uint32_t)value;
  return NULL;
}

static const char *x402_cmd_credit_scope(cmd_parms *cmd, void *cfgv, const char *arg)
{
  x402_dir_config *cfg = (x402_dir_config *)cfgv;
  (void)cmd;
  if(strcmp(arg, "payer") == 0) {
    cfg->policy.credits.scope = X402_CREDIT_SCOPE_PAYER;
  }
  else if(strcmp(arg, "payer-route") == 0) {
    cfg->policy.credits.scope = X402_CREDIT_SCOPE_PAYER_ROUTE;
  }
  else {
    return "X402CreditScope must be payer or payer-route";
  }
  return NULL;
}

static const char *x402_cmd_credit_ttl(cmd_parms *cmd, void *cfgv, const char *arg)
{
  char *endptr = NULL;
  x402_dir_config *cfg = (x402_dir_config *)cfgv;
  unsigned long value;

  (void)cmd;
  value = strtoul(arg, &endptr, 10);
  if(endptr == arg || *endptr != '\0') {
    return "X402CreditTTLSeconds must be an integer";
  }
  cfg->policy.credits.ttl_seconds = (uint32_t)value;
  return NULL;
}

static const char *x402_cmd_credit_db_path(cmd_parms *cmd, void *cfgv, const char *arg)
{
  (void)cmd;
  (void)cfgv;
  return x402_set_string(x402_credit_db_path, sizeof(x402_credit_db_path), arg);
}

static const char *x402_cmd_credits_issued(cmd_parms *cmd, void *cfgv, const char *arg)
{
  char *endptr = NULL;
  x402_dir_config *cfg = (x402_dir_config *)cfgv;
  unsigned long value;

  (void)cmd;
  value = strtoul(arg, &endptr, 10);
  if(endptr == arg || *endptr != '\0' || value == 0) {
    return "X402CreditsIssued must be a positive integer";
  }
  cfg->policy.credits_issued_override = (uint32_t)value;
  return NULL;
}

static const char *x402_cmd_forward_to(cmd_parms *cmd, void *cfgv, const char *arg)
{
  x402_dir_config *cfg = (x402_dir_config *)cfgv;
  (void)cmd;
  return x402_set_string(cfg->policy.forward_to, sizeof(cfg->policy.forward_to), arg);
}

static const char *x402_decode_signature(request_rec *r,
                                         const char *header,
                                         apr_pool_t *pool,
                                         char **decoded)
{
  int needed;

  if(header == NULL || decoded == NULL) {
    return "missing PAYMENT-SIGNATURE";
  }

  needed = apr_base64_decode_len(header);
  *decoded = (char *)apr_pcalloc(pool, (apr_size_t)needed + 1);
  apr_base64_decode(*decoded, header);
  if((*decoded)[0] == '\0') {
    return "failed to decode PAYMENT-SIGNATURE";
  }

  ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, "decoded PAYMENT-SIGNATURE");
  return NULL;
}

static const char *x402_encode_header_value(apr_pool_t *pool, const char *json)
{
  int encoded_len;
  char *encoded;

  if(pool == NULL || json == NULL) {
    return NULL;
  }

  encoded_len = apr_base64_encode_len((int)strlen(json));
  encoded = (char *)apr_pcalloc(pool, (apr_size_t)encoded_len + 1);
  apr_base64_encode(encoded, json, (int)strlen(json));
  return encoded;
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

static uint32_t x402_requested_multiplier(request_rec *r, const x402_route_policy *policy)
{
  const char *header;
  const char *args;
  const char *query_key = "x402_prepaid_multiplier=";
  const char *at = NULL;
  char *endptr = NULL;
  unsigned long parsed;

  if(policy == NULL || !policy->credits.enabled) {
    return 1U;
  }

  args = r == NULL ? NULL : r->args;
  if(args != NULL) {
    at = strstr(args, query_key);
    if(at != NULL) {
      at += strlen(query_key);
      parsed = strtoul(at, &endptr, 10);
      if(endptr != at && (*endptr == '\0' || *endptr == '&') &&
         x402_prepaid_option_supported(policy, (uint32_t)parsed)) {
        return (uint32_t)parsed;
      }
    }
  }

  header = apr_table_get(r->headers_in, "X402-Prepaid-Multiplier");
  if(header == NULL || header[0] == '\0') {
    return 1U;
  }

  parsed = strtoul(header, &endptr, 10);
  if(endptr == header || *endptr != '\0' || !x402_prepaid_option_supported(policy, (uint32_t)parsed)) {
    return 1U;
  }

  return (uint32_t)parsed;
}

static char *x402_credit_scope_key(apr_pool_t *pool,
                                   const x402_route_policy *policy)
{
  const char *scope_route = policy->forward_to[0] != '\0' ? policy->forward_to : policy->route;
  size_t scope_len;
  char *normalized_scope;

  if(policy->credits.scope == X402_CREDIT_SCOPE_PAYER) {
    return apr_psprintf(pool,
                        "%s|%s|%s",
                        policy->mechanism,
                        policy->network,
                        policy->asset);
  }

  scope_len = strlen(scope_route);
  while(scope_len > 1 && scope_route[scope_len - 1] == '/') {
    --scope_len;
  }
  normalized_scope = apr_pstrmemdup(pool, scope_route, scope_len);

  return apr_psprintf(pool,
                      "%s|%s|%s|%s",
                      policy->mechanism,
                      normalized_scope,
                      policy->asset,
                      policy->network);
}

static const char *x402_credit_route(const x402_route_policy *policy)
{
  return policy->forward_to[0] != '\0' ? policy->forward_to : policy->route;
}

static const char *x402_challenge_path(request_rec *r, const x402_route_policy *policy)
{
  if(r != NULL && r->uri != NULL && r->uri[0] != '\0') {
    if(policy->forward_to[0] == '\0' || x402_same_route(r->uri, policy->forward_to)) {
      return r->uri;
    }
  }
  return x402_credit_route(policy);
}

static int x402_credit_db_exec(sqlite3 *db, const char *sql, server_rec *server)
{
  char *errmsg = NULL;
  int rc = sqlite3_exec(db, sql, NULL, NULL, &errmsg);

  if(rc != SQLITE_OK) {
    ap_log_error(APLOG_MARK,
                 APLOG_ERR,
                 0,
                 server,
                 "x402 sqlite exec failed: %s (%s)",
                 sql,
                 errmsg == NULL ? sqlite3_errmsg(db) : errmsg);
    sqlite3_free(errmsg);
    return 0;
  }
  return 1;
}

static int x402_credit_db_prepare(sqlite3 *db,
                                  const char *sql,
                                  sqlite3_stmt **stmt,
                                  server_rec *server)
{
  int rc = sqlite3_prepare_v2(db, sql, -1, stmt, NULL);

  if(rc != SQLITE_OK) {
    ap_log_error(APLOG_MARK,
                 APLOG_ERR,
                 0,
                 server,
                 "x402 sqlite prepare failed: %s (%s)",
                 sql,
                 sqlite3_errmsg(db));
    return 0;
  }
  return 1;
}

static void x402_credit_db_close(void)
{
  if(x402_credit_db != NULL) {
    sqlite3_close(x402_credit_db);
    x402_credit_db = NULL;
  }
}

static int x402_credit_db_open(server_rec *server, int apply_schema)
{
  static const char *schema_sql =
      "PRAGMA journal_mode=WAL;"
      "CREATE TABLE IF NOT EXISTS credit_bucket ("
      " payer TEXT NOT NULL,"
      " credit_scope TEXT NOT NULL,"
      " remaining INTEGER NOT NULL,"
      " expires_at INTEGER NOT NULL,"
      " updated_at INTEGER NOT NULL,"
      " last_payment_identifier TEXT,"
      " last_settlement_tx TEXT,"
      " PRIMARY KEY (payer, credit_scope)"
      ");"
      "CREATE TABLE IF NOT EXISTS auth_challenge ("
      " challenge_token TEXT PRIMARY KEY,"
      " credit_scope TEXT NOT NULL,"
      " request_host TEXT NOT NULL,"
      " request_path TEXT NOT NULL,"
      " nonce TEXT NOT NULL,"
      " issued_at INTEGER NOT NULL,"
      " expires_at INTEGER NOT NULL,"
      " used_at INTEGER"
      ");"
      "CREATE INDEX IF NOT EXISTS auth_challenge_scope_idx "
      "ON auth_challenge (credit_scope, expires_at);"
      "CREATE TABLE IF NOT EXISTS async_split_trace ("
      " id INTEGER PRIMARY KEY AUTOINCREMENT,"
      " payment_identifier TEXT NOT NULL,"
      " stage TEXT NOT NULL,"
      " detail TEXT,"
      " created_at_ms INTEGER NOT NULL"
      ");"
      "CREATE INDEX IF NOT EXISTS async_split_trace_payment_idx "
      "ON async_split_trace (payment_identifier, created_at_ms);"
      "CREATE TABLE IF NOT EXISTS split_tx_audit ("
      " payment_identifier TEXT PRIMARY KEY,"
      " split_tx_hash TEXT NOT NULL,"
      " status TEXT NOT NULL,"
      " detail TEXT,"
      " prepared_at_ms INTEGER,"
      " submitted_at_ms INTEGER,"
      " confirmed_at_ms INTEGER,"
      " updated_at_ms INTEGER NOT NULL"
      ");"
      "CREATE TABLE IF NOT EXISTS abuse_counter ("
      " scope TEXT NOT NULL,"
      " route TEXT NOT NULL,"
      " bucket TEXT NOT NULL,"
      " key TEXT NOT NULL,"
      " window_start INTEGER NOT NULL,"
      " count INTEGER NOT NULL,"
      " blocked_until INTEGER,"
      " updated_at INTEGER NOT NULL,"
      " PRIMARY KEY (scope, route, bucket, key, window_start)"
      ");"
      "CREATE INDEX IF NOT EXISTS abuse_counter_lookup_idx "
      "ON abuse_counter (scope, route, bucket, key, blocked_until, window_start);";
  int rc;

  if(x402_credit_db != NULL) {
    if(apply_schema) {
      return x402_credit_db_exec(x402_credit_db, schema_sql, server);
    }
    return 1;
  }

  rc = sqlite3_open_v2(x402_credit_db_path,
                       &x402_credit_db,
                       SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_FULLMUTEX,
                       NULL);
  if(rc != SQLITE_OK) {
    ap_log_error(APLOG_MARK,
                 APLOG_ERR,
                 0,
                 server,
                 "x402 could not open credit db %s: %s",
                 x402_credit_db_path,
                 x402_credit_db == NULL ? "unknown error" : sqlite3_errmsg(x402_credit_db));
    if(x402_credit_db != NULL) {
      sqlite3_close(x402_credit_db);
      x402_credit_db = NULL;
    }
    return 0;
  }

  sqlite3_busy_timeout(x402_credit_db, 5000);

  if(apply_schema && !x402_credit_db_exec(x402_credit_db, schema_sql, server)) {
    x402_credit_db_close();
    return 0;
  }

  return 1;
}

static void x402_credit_db_cleanup_expired(server_rec *server)
{
  sqlite3_int64 now = (sqlite3_int64)time(NULL);

  if(server == NULL || x402_credit_db == NULL || x402_credit_mutex == NULL) {
    return;
  }

  apr_thread_mutex_lock(x402_credit_mutex);
  if(x402_credit_db_last_cleanup != 0 && now - x402_credit_db_last_cleanup < X402_DB_CLEANUP_INTERVAL) {
    apr_thread_mutex_unlock(x402_credit_mutex);
    return;
  }

  sqlite3_exec(x402_credit_db,
               "DELETE FROM credit_bucket WHERE expires_at <= strftime('%s','now') OR remaining <= 0;",
               NULL,
               NULL,
               NULL);
  sqlite3_exec(x402_credit_db,
               "DELETE FROM auth_challenge WHERE expires_at <= strftime('%s','now') OR "
               "(used_at IS NOT NULL AND used_at <= strftime('%s','now') - 300);",
               NULL,
               NULL,
               NULL);
  x402_credit_db_last_cleanup = now;
  apr_thread_mutex_unlock(x402_credit_mutex);
}

static int x402_credit_consume(request_rec *r,
                               const x402_route_policy *policy,
                               const char *payer,
                               uint32_t *remaining_after)
{
  char *scope_key;
  sqlite3_stmt *stmt = NULL;
  sqlite3_int64 now = (sqlite3_int64)time(NULL);
  int consumed = 0;

  if(x402_credit_db == NULL || x402_credit_mutex == NULL || payer == NULL || payer[0] == '\0') {
    ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, "x402 credit consume skipped");
    return 0;
  }

  scope_key = x402_credit_scope_key(r->pool, policy);
  apr_thread_mutex_lock(x402_credit_mutex);
  if(sqlite3_exec(x402_credit_db, "BEGIN IMMEDIATE TRANSACTION;", NULL, NULL, NULL) != SQLITE_OK) {
    ap_log_rerror(APLOG_MARK,
                  APLOG_WARNING,
                  0,
                  r,
                  "x402 credit consume failed: begin txn sqlite=%d message=%s scope=%s payer=%s",
                  sqlite3_errcode(x402_credit_db),
                  sqlite3_errmsg(x402_credit_db),
                  scope_key == NULL ? "(null)" : scope_key,
                  payer);
    apr_thread_mutex_unlock(x402_credit_mutex);
    return 0;
  }
  if(x402_credit_db_prepare(x402_credit_db,
                            "UPDATE credit_bucket "
                            "SET remaining = remaining - 1, updated_at = ? "
                            "WHERE payer = ? AND credit_scope = ? AND remaining > 0 AND expires_at > ?;",
                            &stmt,
                            r->server)) {
    sqlite3_bind_int64(stmt, 1, now);
    sqlite3_bind_text(stmt, 2, payer, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, scope_key, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int64(stmt, 4, now);
    if(sqlite3_step(stmt) == SQLITE_DONE && sqlite3_changes(x402_credit_db) == 1) {
      consumed = 1;
    }
    else {
      ap_log_rerror(APLOG_MARK,
                    APLOG_WARNING,
                    0,
                    r,
                    "x402 credit consume missed: sqlite=%d message=%s scope=%s payer=%s now=%lld",
                    sqlite3_errcode(x402_credit_db),
                    sqlite3_errmsg(x402_credit_db),
                    scope_key == NULL ? "(null)" : scope_key,
                    payer,
                    (long long)now);
    }
    sqlite3_finalize(stmt);
    stmt = NULL;
  }
  if(consumed && remaining_after != NULL &&
     x402_credit_db_prepare(x402_credit_db,
                            "SELECT remaining FROM credit_bucket WHERE payer = ? AND credit_scope = ?;",
                            &stmt,
                            r->server)) {
    sqlite3_bind_text(stmt, 1, payer, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, scope_key, -1, SQLITE_TRANSIENT);
    if(sqlite3_step(stmt) == SQLITE_ROW) {
      *remaining_after = (uint32_t)sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);
    stmt = NULL;
  }
  sqlite3_exec(x402_credit_db, consumed ? "COMMIT;" : "ROLLBACK;", NULL, NULL, NULL);
  apr_thread_mutex_unlock(x402_credit_mutex);
  if(consumed) {
    ap_log_rerror(APLOG_MARK,
                  APLOG_DEBUG,
                  0,
                  r,
                  "x402 credit consume success: scope=%s payer=%s remaining=%u",
                  scope_key == NULL ? "(null)" : scope_key,
                  payer,
                  remaining_after == NULL ? 0U : *remaining_after);
  }
  return consumed;
}

static int x402_abuse_retry_after(request_rec *r,
                                  const char *scope,
                                  const char *route,
                                  const char *bucket,
                                  const char *key)
{
  sqlite3_stmt *stmt = NULL;
  sqlite3_int64 now = (sqlite3_int64)time(NULL);
  sqlite3_int64 blocked_until = 0;
  int retry_after = 0;

  if(r == NULL || x402_credit_db == NULL || x402_credit_mutex == NULL || scope == NULL ||
     route == NULL || bucket == NULL || key == NULL || key[0] == '\0') {
    return 0;
  }

  apr_thread_mutex_lock(x402_credit_mutex);
  if(x402_credit_db_prepare(x402_credit_db,
                            "SELECT MAX(blocked_until) FROM abuse_counter "
                            "WHERE scope = ? AND route = ? AND bucket = ? AND key = ? "
                            "AND blocked_until IS NOT NULL AND blocked_until > ?;",
                            &stmt,
                            r->server)) {
    sqlite3_bind_text(stmt, 1, scope, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, route, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, bucket, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, key, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int64(stmt, 5, now);
    if(sqlite3_step(stmt) == SQLITE_ROW && sqlite3_column_type(stmt, 0) != SQLITE_NULL) {
      blocked_until = sqlite3_column_int64(stmt, 0);
    }
    sqlite3_finalize(stmt);
  }
  apr_thread_mutex_unlock(x402_credit_mutex);

  if(blocked_until > now) {
    retry_after = (int)(blocked_until - now);
  }
  return retry_after;
}

static int x402_abuse_hit(request_rec *r,
                          const char *scope,
                          const char *route,
                          const char *bucket,
                          const char *key,
                          int limit,
                          int window_seconds,
                          int block_seconds)
{
  sqlite3_stmt *stmt = NULL;
  sqlite3_int64 now = (sqlite3_int64)time(NULL);
  sqlite3_int64 window_start;
  sqlite3_int64 blocked_until = now + block_seconds;

  if(r == NULL || x402_credit_db == NULL || x402_credit_mutex == NULL || scope == NULL ||
     route == NULL || bucket == NULL || key == NULL || key[0] == '\0' || limit <= 0 ||
     window_seconds <= 0 || block_seconds <= 0) {
    return 0;
  }

  window_start = now - (now % window_seconds);
  apr_thread_mutex_lock(x402_credit_mutex);
  if(x402_credit_db_prepare(
         x402_credit_db,
         "INSERT INTO abuse_counter "
         "(scope, route, bucket, key, window_start, count, blocked_until, updated_at) "
         "VALUES (?, ?, ?, ?, ?, 1, NULL, ?) "
         "ON CONFLICT(scope, route, bucket, key, window_start) DO UPDATE SET "
         "count = abuse_counter.count + 1, "
         "blocked_until = CASE "
         "WHEN abuse_counter.count + 1 >= ? "
         "THEN MAX(COALESCE(abuse_counter.blocked_until, 0), ?) "
         "ELSE abuse_counter.blocked_until END, "
         "updated_at = excluded.updated_at;",
         &stmt,
         r->server)) {
    sqlite3_bind_text(stmt, 1, scope, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, route, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, bucket, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, key, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int64(stmt, 5, window_start);
    sqlite3_bind_int64(stmt, 6, now);
    sqlite3_bind_int(stmt, 7, limit);
    sqlite3_bind_int64(stmt, 8, blocked_until);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
  }
  apr_thread_mutex_unlock(x402_credit_mutex);

  return x402_abuse_retry_after(r, scope, route, bucket, key);
}

static int x402_emit_too_many_requests(request_rec *r,
                                       const char *bucket,
                                       const char *key,
                                       int retry_after)
{
  if(r == NULL) {
    return HTTP_TOO_MANY_REQUESTS;
  }

  if(retry_after <= 0) {
    retry_after = 1;
  }

  apr_table_setn(r->err_headers_out, "Retry-After", apr_itoa(r->pool, retry_after));
  ap_log_rerror(APLOG_MARK,
                APLOG_WARNING,
                0,
                r,
                "x402 rate limit triggered: bucket=%s key=%s route=%s retry_after=%d",
                bucket == NULL ? "(none)" : bucket,
                key == NULL ? "(none)" : key,
                r->uri == NULL ? "(null)" : r->uri,
                retry_after);
  return HTTP_TOO_MANY_REQUESTS;
}

static void x402_trace_async_split(request_rec *r,
                                   const char *payment_identifier,
                                   const char *stage,
                                   const char *detail)
{
  sqlite3_stmt *stmt = NULL;
  sqlite3_int64 now_ms;

  if(r == NULL || x402_credit_db == NULL || x402_credit_mutex == NULL || stage == NULL ||
     stage[0] == '\0') {
    if(r != NULL) {
      ap_log_rerror(APLOG_MARK,
                    APLOG_WARNING,
                    0,
                    r,
                    "x402 async trace skipped: db=%d mutex=%d stage=%s",
                    x402_credit_db != NULL,
                    x402_credit_mutex != NULL,
                    stage == NULL ? "(null)" : stage);
    }
    return;
  }

  now_ms = (sqlite3_int64)(apr_time_now() / 1000);
  apr_thread_mutex_lock(x402_credit_mutex);
  if(x402_credit_db_prepare(x402_credit_db,
                            "INSERT INTO async_split_trace "
                            "(payment_identifier, stage, detail, created_at_ms) "
                            "VALUES (?, ?, ?, ?);",
                            &stmt,
                            r->server)) {
    sqlite3_bind_text(stmt,
                      1,
                      payment_identifier == NULL || payment_identifier[0] == '\0'
                          ? "(none)"
                          : payment_identifier,
                      -1,
                      SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, stage, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,
                      3,
                      detail == NULL || detail[0] == '\0' ? "(none)" : detail,
                      -1,
                      SQLITE_TRANSIENT);
    sqlite3_bind_int64(stmt, 4, now_ms);
    if(sqlite3_step(stmt) != SQLITE_DONE) {
      ap_log_rerror(APLOG_MARK,
                    APLOG_WARNING,
                    0,
                    r,
                    "x402 async trace insert failed: sqlite=%d message=%s stage=%s payment_id=%s",
                    sqlite3_errcode(x402_credit_db),
                    sqlite3_errmsg(x402_credit_db),
                    stage,
                    payment_identifier == NULL ? "(null)" : payment_identifier);
    }
    sqlite3_finalize(stmt);
  }
  apr_thread_mutex_unlock(x402_credit_mutex);
}

static void x402_log_syslog_proof(const char *stage,
                                  const char *payment_identifier,
                                  const char *payer,
                                  const char *route,
                                  const char *detail)
{
  if(stage == NULL || stage[0] == '\0') {
    return;
  }
  openlog("mod_x402", LOG_PID | LOG_NDELAY, LOG_USER);
  syslog(LOG_NOTICE,
         "x402 proof stage=%s payment_id=%s payer=%s route=%s detail=%s",
         stage,
         payment_identifier == NULL || payment_identifier[0] == '\0' ? "(none)" : payment_identifier,
         payer == NULL || payer[0] == '\0' ? "(none)" : payer,
         route == NULL || route[0] == '\0' ? "(none)" : route,
         detail == NULL || detail[0] == '\0' ? "(none)" : detail);
  closelog();
}

static void x402_credit_store(request_rec *r,
                              const x402_route_policy *policy,
                              const x402_settlement_result *settlement)
{
  char *scope_key;
  const char *payment_identifier = NULL;
  sqlite3_stmt *stmt = NULL;
  sqlite3_int64 now = (sqlite3_int64)time(NULL);
  sqlite3_int64 ttl = policy->credits.ttl_seconds == 0 ? 86400 : policy->credits.ttl_seconds;
  sqlite3_int64 expires_at = now + ttl;

  if(x402_credit_db == NULL || x402_credit_mutex == NULL || settlement == NULL ||
     settlement->payer[0] == '\0' || settlement->credits_remaining == 0) {
    return;
  }

  scope_key = x402_credit_scope_key(r->pool, policy);
  payment_identifier = apr_table_get(r->notes, "x402-payment-identifier");
  apr_thread_mutex_lock(x402_credit_mutex);
  if(x402_credit_db_prepare(x402_credit_db,
                            "INSERT INTO credit_bucket (payer, credit_scope, remaining, expires_at, updated_at, "
                            "last_payment_identifier, last_settlement_tx) "
                            "VALUES (?, ?, ?, ?, ?, ?, ?) "
                            "ON CONFLICT(payer, credit_scope) DO UPDATE SET "
                            "remaining = credit_bucket.remaining + excluded.remaining, "
                            "expires_at = excluded.expires_at, "
                            "updated_at = excluded.updated_at, "
                            "last_payment_identifier = excluded.last_payment_identifier, "
                            "last_settlement_tx = excluded.last_settlement_tx;",
                            &stmt,
                            r->server)) {
    sqlite3_bind_text(stmt, 1, settlement->payer, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, scope_key, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, (int)settlement->credits_remaining);
    sqlite3_bind_int64(stmt, 4, expires_at);
    sqlite3_bind_int64(stmt, 5, now);
    sqlite3_bind_text(stmt, 6, payment_identifier == NULL ? "" : payment_identifier, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 7, settlement->transaction_ref, -1, SQLITE_TRANSIENT);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
  }
  apr_thread_mutex_unlock(x402_credit_mutex);
}

static const char *x402_request_host(request_rec *r)
{
  const char *host = apr_table_get(r->headers_in, "Host");
  if(host != NULL && host[0] != '\0') {
    return host;
  }
  return ap_get_server_name(r);
}

static char *x402_stellar_auth_message(apr_pool_t *pool,
                                       const char *host,
                                       const char *path,
                                       const char *nonce,
                                       sqlite3_int64 issued_at,
                                       sqlite3_int64 expires_at)
{
  return apr_psprintf(pool,
                      "x402-stellar-auth-v1\nhost:%s\npath:%s\nnonce:%s\nissuedAt:%ld\nexpiresAt:%ld",
                      host,
                      path,
                      nonce,
                      (long)issued_at,
                      (long)expires_at);
}

static int x402_issue_stellar_auth_challenge(request_rec *r,
                                             const x402_route_policy *policy,
                                             char *json_out,
                                             size_t json_out_size)
{
  apr_uuid_t challenge_uuid;
  apr_uuid_t nonce_uuid;
  char token_text[APR_UUID_FORMATTED_LENGTH + 1];
  char nonce_text[APR_UUID_FORMATTED_LENGTH + 1];
  char challenge_token[X402_MAX_IDENTIFIER];
  char *scope_key;
  const char *host;
  const char *challenge_path;
  char *message;
  char *message_b64;
  int message_b64_len;
  sqlite3_stmt *stmt = NULL;
  sqlite3_int64 now = (sqlite3_int64)time(NULL);
  sqlite3_int64 expires_at = now + X402_STELLAR_AUTH_CHALLENGE_TTL;
  int ok = 0;

  if(!x402_policy_uses_stellar(policy) || x402_credit_db == NULL || x402_credit_mutex == NULL ||
     json_out == NULL || json_out_size == 0) {
    ap_log_rerror(APLOG_MARK,
                  APLOG_WARNING,
                  0,
                  r,
                  "x402 auth challenge skipped: stellar=%d db=%d mutex=%d json_out=%d json_size=%lu",
                  x402_policy_uses_stellar(policy),
                  x402_credit_db != NULL,
                  x402_credit_mutex != NULL,
                  json_out != NULL,
                  (unsigned long)json_out_size);
    return 0;
  }

  host = x402_request_host(r);
  scope_key = x402_credit_scope_key(r->pool, policy);
  challenge_path = x402_challenge_path(r, policy);
  apr_uuid_get(&challenge_uuid);
  apr_uuid_get(&nonce_uuid);
  apr_uuid_format(token_text, &challenge_uuid);
  apr_uuid_format(nonce_text, &nonce_uuid);
  if(snprintf(challenge_token, sizeof(challenge_token), "xc_%s", token_text) <= 0) {
    ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, "x402 auth challenge token format failed");
    return 0;
  }
  message = x402_stellar_auth_message(r->pool,
                                      host,
                                      challenge_path,
                                      nonce_text,
                                      now,
                                      expires_at);

  apr_thread_mutex_lock(x402_credit_mutex);
  if(x402_credit_db_prepare(x402_credit_db,
                            "INSERT INTO auth_challenge (challenge_token, credit_scope, request_host, "
                            "request_path, nonce, issued_at, expires_at, used_at) "
                            "VALUES (?, ?, ?, ?, ?, ?, ?, NULL);",
                            &stmt,
                            r->server)) {
    sqlite3_bind_text(stmt, 1, challenge_token, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, scope_key, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, host, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, challenge_path, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, nonce_text, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int64(stmt, 6, now);
    sqlite3_bind_int64(stmt, 7, expires_at);
    ok = sqlite3_step(stmt) == SQLITE_DONE;
    if(!ok) {
      ap_log_rerror(APLOG_MARK,
                    APLOG_WARNING,
                    0,
                    r,
                    "x402 auth challenge insert failed: sqlite=%d message=%s token=%s scope=%s host=%s path=%s",
                    sqlite3_errcode(x402_credit_db),
                    sqlite3_errmsg(x402_credit_db),
                    challenge_token,
                    scope_key == NULL ? "(null)" : scope_key,
                    host == NULL ? "(null)" : host,
                    challenge_path);
    }
    sqlite3_finalize(stmt);
  }
  else {
    ap_log_rerror(APLOG_MARK,
                  APLOG_WARNING,
                  0,
                  r,
                  "x402 auth challenge prepare failed: sqlite=%d message=%s token=%s scope=%s host=%s path=%s",
                  sqlite3_errcode(x402_credit_db),
                  sqlite3_errmsg(x402_credit_db),
                  challenge_token,
                  scope_key == NULL ? "(null)" : scope_key,
                  host == NULL ? "(null)" : host,
                  challenge_path);
  }
  apr_thread_mutex_unlock(x402_credit_mutex);
  if(!ok) {
    return 0;
  }

  message_b64_len = apr_base64_encode_len((int)strlen(message));
  message_b64 = (char *)apr_pcalloc(r->pool, (apr_size_t)message_b64_len + 1);
  apr_base64_encode(message_b64, message, (int)strlen(message));

  snprintf(json_out,
           json_out_size,
           "{\"scheme\":\"stellar-signin-v1\",\"header\":\"%s\",\"token\":\"%s\","
           "\"host\":\"%s\",\"path\":\"%s\",\"nonce\":\"%s\",\"issuedAt\":%lld,"
           "\"expiresAt\":%lld,\"messageBase64\":\"%s\"}",
           X402_STELLAR_AUTH_HEADER,
           challenge_token,
           host,
           challenge_path,
           nonce_text,
           (long long)now,
           (long long)expires_at,
           message_b64);
  ap_log_rerror(APLOG_MARK,
                APLOG_DEBUG,
                0,
                r,
                "x402 auth challenge issued: token=%s scope=%s host=%s path=%s",
                challenge_token,
                scope_key == NULL ? "(null)" : scope_key,
                host == NULL ? "(null)" : host,
                challenge_path);
  return 1;
}

static int x402_verify_stellar_auth(request_rec *r,
                                    const x402_route_policy *policy,
                                    const char *header_value,
                                    char *payer_out,
                                    size_t payer_out_size)
{
  char *decoded = NULL;
  char challenge_token[X402_MAX_IDENTIFIER];
  char address[X402_MAX_PAYER];
  char signature_b64[256];
  char *scope_key;
  sqlite3_stmt *stmt = NULL;
  sqlite3_int64 now = (sqlite3_int64)time(NULL);
  char host_buf[X402_MAX_TEXT];
  char path_buf[X402_MAX_ROUTE];
  char nonce_buf[X402_MAX_IDENTIFIER];
  sqlite3_int64 issued_at = 0;
  sqlite3_int64 expires_at = 0;
  char *message;
  char *route_key;
  unsigned char public_key[32];
  int sig_needed;
  unsigned char *signature = NULL;
  int verified = 0;
  int claimed = 0;

  route_key = x402_normalize_route(r->pool, policy == NULL ? r->uri : policy->route);

  if(!x402_policy_uses_stellar(policy) || header_value == NULL || payer_out == NULL ||
     payer_out_size == 0) {
    ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, "x402 stellar auth rejected: invalid input");
    return 0;
  }

  if(x402_decode_signature(r, header_value, r->pool, &decoded) != NULL) {
    ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, "x402 stellar auth rejected: decode failed");
    x402_abuse_hit(r,
                   X402_ABUSE_SCOPE_IP,
                   route_key,
                   X402_ABUSE_BUCKET_BAD_PREPAID_AUTH,
                   x402_client_key(r),
                   X402_ABUSE_BAD_PREPAID_AUTH_LIMIT,
                   X402_ABUSE_BAD_PREPAID_AUTH_WINDOW,
                   X402_ABUSE_BAD_PREPAID_AUTH_BLOCK);
    return 0;
  }
  memset(challenge_token, 0, sizeof(challenge_token));
  memset(address, 0, sizeof(address));
  memset(signature_b64, 0, sizeof(signature_b64));
  if(x402_extract_json_string(decoded, "token", challenge_token, sizeof(challenge_token)) != X402_STATUS_OK ||
     x402_extract_json_string(decoded, "address", address, sizeof(address)) != X402_STATUS_OK ||
     x402_extract_json_string(decoded, "signature", signature_b64, sizeof(signature_b64)) != X402_STATUS_OK) {
    ap_log_rerror(APLOG_MARK,
                  APLOG_WARNING,
                  0,
                  r,
                  "x402 stellar auth rejected: token/address/signature missing");
    x402_abuse_hit(r,
                   X402_ABUSE_SCOPE_IP,
                   route_key,
                   X402_ABUSE_BUCKET_BAD_PREPAID_AUTH,
                   x402_client_key(r),
                   X402_ABUSE_BAD_PREPAID_AUTH_LIMIT,
                   X402_ABUSE_BAD_PREPAID_AUTH_WINDOW,
                   X402_ABUSE_BAD_PREPAID_AUTH_BLOCK);
    return 0;
  }

  if(!x402_decode_stellar_strkey('G', 6U << 3U, address, public_key, sizeof(public_key))) {
    ap_log_rerror(APLOG_MARK,
                  APLOG_WARNING,
                  0,
                  r,
                  "x402 stellar auth rejected: invalid address %s",
                  address);
    x402_abuse_hit(r,
                   X402_ABUSE_SCOPE_IP,
                   route_key,
                   X402_ABUSE_BUCKET_BAD_PREPAID_AUTH,
                   x402_client_key(r),
                   X402_ABUSE_BAD_PREPAID_AUTH_LIMIT,
                   X402_ABUSE_BAD_PREPAID_AUTH_WINDOW,
                   X402_ABUSE_BAD_PREPAID_AUTH_BLOCK);
    return 0;
  }

  scope_key = x402_credit_scope_key(r->pool, policy);
  apr_thread_mutex_lock(x402_credit_mutex);
  if(x402_credit_db_prepare(x402_credit_db,
                            "SELECT request_host, request_path, nonce, issued_at, expires_at "
                            "FROM auth_challenge WHERE challenge_token = ? AND credit_scope = ? "
                            "AND expires_at > ? AND used_at IS NULL;",
                            &stmt,
                            r->server)) {
    sqlite3_bind_text(stmt, 1, challenge_token, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, scope_key, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int64(stmt, 3, now);
    if(sqlite3_step(stmt) == SQLITE_ROW) {
      const unsigned char *host_text = sqlite3_column_text(stmt, 0);
      const unsigned char *path_text = sqlite3_column_text(stmt, 1);
      const unsigned char *nonce_text = sqlite3_column_text(stmt, 2);

      snprintf(host_buf, sizeof(host_buf), "%s", host_text == NULL ? "" : (const char *)host_text);
      snprintf(path_buf, sizeof(path_buf), "%s", path_text == NULL ? "" : (const char *)path_text);
      snprintf(nonce_buf, sizeof(nonce_buf), "%s", nonce_text == NULL ? "" : (const char *)nonce_text);
      issued_at = sqlite3_column_int64(stmt, 3);
      expires_at = sqlite3_column_int64(stmt, 4);
      verified = 1;
    }
    sqlite3_finalize(stmt);
    stmt = NULL;
  }
  apr_thread_mutex_unlock(x402_credit_mutex);
  if(!verified) {
    ap_log_rerror(APLOG_MARK,
                  APLOG_WARNING,
                  0,
                  r,
                  "x402 stellar auth rejected: challenge lookup failed token=%s scope=%s now=%lld",
                  challenge_token,
                  scope_key == NULL ? "(null)" : scope_key,
                  (long long)now);
    x402_abuse_hit(r,
                   X402_ABUSE_SCOPE_IP,
                   route_key,
                   X402_ABUSE_BUCKET_REPLAYED_CHALLENGE,
                   x402_client_key(r),
                   X402_ABUSE_REPLAY_LIMIT,
                   X402_ABUSE_REPLAY_WINDOW,
                   X402_ABUSE_REPLAY_BLOCK);
    return 0;
  }

  message = x402_stellar_auth_message(r->pool, host_buf, path_buf, nonce_buf, issued_at, expires_at);
  sig_needed = apr_base64_decode_len(signature_b64);
  signature = (unsigned char *)apr_pcalloc(r->pool, (apr_size_t)sig_needed + 1);
  sig_needed = apr_base64_decode((char *)signature, signature_b64);
  if(sig_needed != crypto_sign_BYTES) {
    ap_log_rerror(APLOG_MARK,
                  APLOG_WARNING,
                  0,
                  r,
                  "x402 stellar auth rejected: signature length %d",
                  sig_needed);
    x402_abuse_hit(r,
                   X402_ABUSE_SCOPE_IP,
                   route_key,
                   X402_ABUSE_BUCKET_BAD_PREPAID_AUTH,
                   x402_client_key(r),
                   X402_ABUSE_BAD_PREPAID_AUTH_LIMIT,
                   X402_ABUSE_BAD_PREPAID_AUTH_WINDOW,
                   X402_ABUSE_BAD_PREPAID_AUTH_BLOCK);
    return 0;
  }
  if(crypto_sign_verify_detached(signature,
                                 (const unsigned char *)message,
                                 (unsigned long long)strlen(message),
                                 public_key) != 0) {
    ap_log_rerror(APLOG_MARK,
                  APLOG_WARNING,
                  0,
                  r,
                  "x402 stellar auth rejected: signature verify failed token=%s address=%s host=%s path=%s",
                  challenge_token,
                  address,
                  host_buf,
                  path_buf);
    x402_abuse_hit(r,
                   X402_ABUSE_SCOPE_IP,
                   route_key,
                   X402_ABUSE_BUCKET_BAD_PREPAID_AUTH,
                   x402_client_key(r),
                   X402_ABUSE_BAD_PREPAID_AUTH_LIMIT,
                   X402_ABUSE_BAD_PREPAID_AUTH_WINDOW,
                   X402_ABUSE_BAD_PREPAID_AUTH_BLOCK);
    return 0;
  }

  apr_thread_mutex_lock(x402_credit_mutex);
  if(sqlite3_exec(x402_credit_db, "BEGIN IMMEDIATE TRANSACTION;", NULL, NULL, NULL) == SQLITE_OK) {
    if(x402_credit_db_prepare(x402_credit_db,
                              "UPDATE auth_challenge SET used_at = ? "
                              "WHERE challenge_token = ? AND used_at IS NULL;",
                              &stmt,
                              r->server)) {
      sqlite3_bind_int64(stmt, 1, now);
      sqlite3_bind_text(stmt, 2, challenge_token, -1, SQLITE_TRANSIENT);
      sqlite3_step(stmt);
      claimed = (sqlite3_changes(x402_credit_db) == 1);
      sqlite3_finalize(stmt);
      stmt = NULL;
    }
    sqlite3_exec(x402_credit_db, claimed ? "COMMIT;" : "ROLLBACK;", NULL, NULL, NULL);
  }
  apr_thread_mutex_unlock(x402_credit_mutex);
  if(!claimed) {
    ap_log_rerror(APLOG_MARK,
                  APLOG_WARNING,
                  0,
                  r,
                  "x402 stellar auth rejected: challenge replay race token=%s scope=%s",
                  challenge_token,
                  scope_key == NULL ? "(null)" : scope_key);
    x402_abuse_hit(r,
                   X402_ABUSE_SCOPE_IP,
                   route_key,
                   X402_ABUSE_BUCKET_REPLAYED_CHALLENGE,
                   x402_client_key(r),
                   X402_ABUSE_REPLAY_LIMIT,
                   X402_ABUSE_REPLAY_WINDOW,
                   X402_ABUSE_REPLAY_BLOCK);
    return 0;
  }

  ap_log_rerror(APLOG_MARK,
                APLOG_DEBUG,
                0,
                r,
                "x402 stellar auth verified: token=%s payer=%s scope=%s",
                challenge_token,
                address,
                scope_key == NULL ? "(null)" : scope_key);
  snprintf(payer_out, payer_out_size, "%s", address);
  return 1;
}

static void x402_fill_request_context(x402_request_context *request,
                                      request_rec *r,
                                      const x402_route_policy *policy,
                                      const x402_payment_payload_view *payload)
{
  memset(request, 0, sizeof(*request));
  snprintf(request->request_id, sizeof(request->request_id), "%ld", (long)r->request_time);
  snprintf(request->client_id,
           sizeof(request->client_id),
           "%s",
           r->useragent_ip == NULL ? "unknown" : r->useragent_ip);
  request->requested_multiplier = x402_requested_multiplier(r, policy);
  if(payload != NULL) {
    snprintf(request->payer_hint, sizeof(request->payer_hint), "%s", payload->payer);
    snprintf(request->payment_identifier,
             sizeof(request->payment_identifier),
             "%s",
             payload->payment_identifier);
    apr_table_setn(r->notes,
                   "x402-payment-identifier",
                   apr_pstrdup(r->pool, payload->payment_identifier));
    if(payload->multiplier != 0 && x402_prepaid_option_supported(policy, payload->multiplier)) {
      request->requested_multiplier = payload->multiplier;
    }
  }
}

static int x402_try_prepaid_access(request_rec *r, x402_dir_config *cfg, int *served)
{
  const char *auth_header = apr_table_get(r->headers_in, X402_STELLAR_AUTH_HEADER);
  char *route_key;
  char payer[X402_MAX_PAYER];
  char challenge_json[X402_MAX_JSON];
  char response_json[X402_MAX_JSON];
  x402_settlement_result synthetic;
  uint32_t remaining = 0;
  x402_status status;
  int retry_after = 0;

  if(served != NULL) {
    *served = 0;
  }
  if(!cfg->policy.credits.enabled) {
    return DECLINED;
  }
  route_key = x402_normalize_route(r->pool, cfg->policy.route[0] == '\0' ? r->uri : cfg->policy.route);

  if(auth_header != NULL && auth_header[0] != '\0') {
    retry_after = x402_abuse_retry_after(r,
                                         X402_ABUSE_SCOPE_IP,
                                         route_key,
                                         X402_ABUSE_BUCKET_BAD_PREPAID_AUTH,
                                         x402_client_key(r));
    if(retry_after <= 0) {
      retry_after = x402_abuse_retry_after(r,
                                           X402_ABUSE_SCOPE_IP,
                                           route_key,
                                           X402_ABUSE_BUCKET_REPLAYED_CHALLENGE,
                                           x402_client_key(r));
    }
    if(retry_after > 0) {
      return x402_emit_too_many_requests(r,
                                         X402_ABUSE_BUCKET_BAD_PREPAID_AUTH,
                                         x402_client_key(r),
                                         retry_after);
    }
  }

  memset(payer, 0, sizeof(payer));
  if(auth_header == NULL || auth_header[0] == '\0' ||
     !x402_verify_stellar_auth(r, &cfg->policy, auth_header, payer, sizeof(payer))) {
    if(auth_header != NULL && auth_header[0] != '\0') {
      retry_after = x402_abuse_retry_after(r,
                                           X402_ABUSE_SCOPE_IP,
                                           route_key,
                                           X402_ABUSE_BUCKET_BAD_PREPAID_AUTH,
                                           x402_client_key(r));
      if(retry_after <= 0) {
        retry_after = x402_abuse_retry_after(r,
                                             X402_ABUSE_SCOPE_IP,
                                             route_key,
                                             X402_ABUSE_BUCKET_REPLAYED_CHALLENGE,
                                             x402_client_key(r));
      }
      if(retry_after > 0) {
        return x402_emit_too_many_requests(r,
                                           X402_ABUSE_BUCKET_BAD_PREPAID_AUTH,
                                           x402_client_key(r),
                                           retry_after);
      }
    }
    return DECLINED;
  }

  if(!x402_credit_consume(r, &cfg->policy, payer, &remaining)) {
    return DECLINED;
  }

  memset(&synthetic, 0, sizeof(synthetic));
  synthetic.status = X402_STATUS_OK;
  synthetic.settled = 1;
  synthetic.credits_issued = 0;
  synthetic.credits_remaining = remaining;
  snprintf(synthetic.payer, sizeof(synthetic.payer), "%s", payer);
  snprintf(synthetic.transaction_ref, sizeof(synthetic.transaction_ref), "%s", "prepaid-cache");
  snprintf(synthetic.settlement_mode, sizeof(synthetic.settlement_mode), "%s", "prepaid");

  status = x402_build_payment_response_json(&cfg->policy,
                                            &synthetic,
                                            response_json,
                                            sizeof(response_json));
  if(status != X402_STATUS_OK) {
    return HTTP_INTERNAL_SERVER_ERROR;
  }

  apr_table_setn(r->notes, "x402-settled", "1");
  apr_table_setn(r->notes, "x402-payer", apr_pstrdup(r->pool, payer));
  apr_table_setn(r->headers_out,
                 "PAYMENT-RESPONSE",
                 x402_encode_header_value(r->pool, response_json));
  if(x402_issue_stellar_auth_challenge(r, &cfg->policy, challenge_json, sizeof(challenge_json))) {
    apr_table_setn(r->headers_out,
                   X402_STELLAR_AUTH_CHALLENGE_HEADER,
                   x402_encode_header_value(r->pool, challenge_json));
  }
  ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, "served from prepaid credits for payer %s", payer);
  if(served != NULL) {
    *served = 1;
  }
  return DECLINED;
}

static int x402_emit_required(request_rec *r,
                              x402_dir_config *cfg,
                              const x402_provider *provider)
{
  char error[X402_MAX_TEXT];
  char json[X402_MAX_JSON];
  char challenge_json[X402_MAX_JSON];
  x402_payment_requirements requirements;
  x402_request_context request;
  x402_status status;
  char *route_key;
  int retry_after;

  route_key = x402_normalize_route(r->pool, cfg->policy.route[0] == '\0' ? r->uri : cfg->policy.route);
  retry_after = x402_abuse_retry_after(r,
                                       X402_ABUSE_SCOPE_IP,
                                       route_key,
                                       X402_ABUSE_BUCKET_UNPAID,
                                       x402_client_key(r));
  if(retry_after > 0) {
    return x402_emit_too_many_requests(r, X402_ABUSE_BUCKET_UNPAID, x402_client_key(r), retry_after);
  }
  retry_after = x402_abuse_hit(r,
                               X402_ABUSE_SCOPE_IP,
                               route_key,
                               X402_ABUSE_BUCKET_UNPAID,
                               x402_client_key(r),
                               X402_ABUSE_UNPAID_LIMIT,
                               X402_ABUSE_UNPAID_WINDOW,
                               X402_ABUSE_UNPAID_BLOCK);
  if(retry_after > 0) {
    return x402_emit_too_many_requests(r, X402_ABUSE_BUCKET_UNPAID, x402_client_key(r), retry_after);
  }

  status = x402_validate_policy(&cfg->policy, error, sizeof(error));
  if(status != X402_STATUS_OK) {
    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "x402 policy invalid: %s", error);
    return HTTP_INTERNAL_SERVER_ERROR;
  }

  memset(&request, 0, sizeof(request));
  request.requested_multiplier = x402_requested_multiplier(r, &cfg->policy);
  status = provider->declare_requirements(&cfg->policy, &request, &requirements);
  if(status != X402_STATUS_OK) {
    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "x402 requirements failed");
    return HTTP_INTERNAL_SERVER_ERROR;
  }

  status = x402_build_payment_required_json(&cfg->policy, &requirements, json, sizeof(json));
  if(status != X402_STATUS_OK) {
    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "x402 challenge build failed");
    return HTTP_INTERNAL_SERVER_ERROR;
  }

  apr_table_setn(r->err_headers_out,
                 "PAYMENT-REQUIRED",
                 x402_encode_header_value(r->pool, json));
  if(cfg->policy.credits.enabled &&
     x402_issue_stellar_auth_challenge(r, &cfg->policy, challenge_json, sizeof(challenge_json))) {
    apr_table_setn(r->err_headers_out,
                   X402_STELLAR_AUTH_CHALLENGE_HEADER,
                   x402_encode_header_value(r->pool, challenge_json));
  }
  return HTTP_PAYMENT_REQUIRED;
}

static int x402_same_route(const char *left, const char *right)
{
  size_t left_len;
  size_t right_len;

  if(left == NULL || right == NULL) {
    return 0;
  }

  left_len = strlen(left);
  right_len = strlen(right);
  while(left_len > 1 && left[left_len - 1] == '/') {
    --left_len;
  }
  while(right_len > 1 && right[right_len - 1] == '/') {
    --right_len;
  }

  if(left_len != right_len) {
    return 0;
  }
  return strncmp(left, right, left_len) == 0;
}

static const char *x402_forward_note(request_rec *r, const char *key)
{
  const char *value;

  if(r == NULL || key == NULL) {
    return NULL;
  }

  value = apr_table_get(r->notes, key);
  if(value != NULL) {
    return value;
  }
  if(r->prev != NULL) {
    return apr_table_get(r->prev->notes, key);
  }
  return NULL;
}

static int x402_check_access(request_rec *r)
{
  char error[X402_MAX_TEXT];
  char response_json[X402_MAX_JSON];
  char challenge_json[X402_MAX_JSON];
  char *decoded = NULL;
  const char *signature;
  const char *decode_error;
  x402_dir_config *cfg = (x402_dir_config *)ap_get_module_config(r->per_dir_config,
                                                                 &x402_module);
  x402_dir_config effective_cfg;
  const char *policy_error;
  const x402_provider *provider;
  x402_payment_payload_view payload;
  x402_request_context request;
  x402_verification_result verification;
  x402_settlement_result settlement;
  x402_status status;
  char *route_key;
  int retry_after;
  const char *forward_target;
  const char *forward_payment_response;
  const char *forward_payer;
  const char *forward_auth_challenge;
  const char *forward_proof_response_released;
  const char *forward_split_transaction_hash;

  if(cfg == NULL || !cfg->enabled || r->main != NULL) {
    return DECLINED;
  }

  effective_cfg = *cfg;
  policy_error = x402_apply_global_split_policy(r,
                                                &effective_cfg.policy,
                                                cfg->pay_to_set,
                                                cfg->split_mode_set,
                                                cfg->splitter_contract_set);
  if(policy_error != NULL) {
    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "x402 policy invalid: %s", policy_error);
    return HTTP_INTERNAL_SERVER_ERROR;
  }
  cfg = &effective_cfg;

  x402_credit_db_cleanup_expired(r->server);

  forward_target = x402_forward_note(r, "x402-forward-target");
  forward_payment_response = x402_forward_note(r, "x402-forward-payment-response");
  forward_payer = x402_forward_note(r, "x402-forward-payer");
  forward_auth_challenge = x402_forward_note(r, "x402-forward-auth-challenge");
  forward_proof_response_released = x402_forward_note(r, "x402-forward-proof-response-released");
  forward_split_transaction_hash = x402_forward_note(r, "x402-forward-split-transaction-hash");
  if(forward_payment_response != NULL &&
     (forward_target == NULL || x402_same_route(forward_target, r->uri) || r->prev != NULL)) {
    if(forward_auth_challenge != NULL) {
      apr_table_setn(r->headers_out,
                     X402_STELLAR_AUTH_CHALLENGE_HEADER,
                     forward_auth_challenge);
    }
    else if(cfg->policy.credits.enabled &&
            x402_issue_stellar_auth_challenge(r, &cfg->policy, challenge_json, sizeof(challenge_json))) {
      apr_table_setn(r->headers_out,
                     X402_STELLAR_AUTH_CHALLENGE_HEADER,
                     x402_encode_header_value(r->pool, challenge_json));
    }
    if(forward_payment_response != NULL) {
      apr_table_setn(r->headers_out, "PAYMENT-RESPONSE", forward_payment_response);
    }
    if(forward_proof_response_released != NULL) {
      apr_table_setn(r->headers_out,
                     "X402-Proof-Response-Released",
                     forward_proof_response_released);
    }
    if(forward_split_transaction_hash != NULL) {
      apr_table_setn(r->headers_out,
                     "X402-Split-Transaction-Hash",
                     forward_split_transaction_hash);
    }
    if(forward_payer != NULL) {
      apr_table_setn(r->notes, "x402-payer", forward_payer);
    }
    ap_log_rerror(APLOG_MARK,
                  APLOG_NOTICE,
                  0,
                  r,
                  "x402 proof response_forwarded payment_id=%s payer=%s route=%s ts_us=%" APR_TIME_T_FMT,
                  x402_forward_note(r, "x402-payment-identifier"),
                  forward_payer == NULL ? "(none)" : forward_payer,
                  r->uri == NULL ? "(null)" : r->uri,
                  apr_time_now());
    x402_log_syslog_proof("response-forwarded",
                          x402_forward_note(r, "x402-payment-identifier"),
                          forward_payer,
                          r->uri,
                          forward_proof_response_released);
    apr_table_setn(r->notes, "x402-settled", "1");
    return DECLINED;
  }

  provider = x402_get_provider(&cfg->policy);
  if(provider == NULL) {
    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "no x402 provider for mechanism %s",
                  cfg->policy.mechanism);
    return HTTP_INTERNAL_SERVER_ERROR;
  }

  status = x402_validate_policy(&cfg->policy, error, sizeof(error));
  if(status != X402_STATUS_OK) {
    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "x402 policy invalid: %s", error);
    return HTTP_INTERNAL_SERVER_ERROR;
  }

  signature = apr_table_get(r->headers_in, "PAYMENT-SIGNATURE");
  if(signature == NULL) {
    int served_from_credits = 0;
    int prepaid = x402_try_prepaid_access(r, cfg, &served_from_credits);
    if(prepaid != DECLINED) {
      return prepaid;
    }
    if(served_from_credits) {
      return DECLINED;
    }
    return x402_emit_required(r, cfg, provider);
  }

  route_key = x402_normalize_route(r->pool, cfg->policy.route[0] == '\0' ? r->uri : cfg->policy.route);

  decode_error = x402_decode_signature(r, signature, r->pool, &decoded);
  if(decode_error != NULL) {
    ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, "x402 decode error: %s", decode_error);
    retry_after = x402_abuse_hit(r,
                                 X402_ABUSE_SCOPE_IP,
                                 route_key,
                                 X402_ABUSE_BUCKET_BAD_PAYMENT,
                                 x402_client_key(r),
                                 X402_ABUSE_BAD_PAYMENT_LIMIT,
                                 X402_ABUSE_BAD_PAYMENT_WINDOW,
                                 X402_ABUSE_BAD_PAYMENT_BLOCK);
    if(retry_after > 0) {
      return x402_emit_too_many_requests(r,
                                         X402_ABUSE_BUCKET_BAD_PAYMENT,
                                         x402_client_key(r),
                                         retry_after);
    }
    return x402_emit_required(r, cfg, provider);
  }

  memset(&payload, 0, sizeof(payload));
  x402_parse_payment_payload(decoded, &payload);
  x402_fill_request_context(&request, r, &cfg->policy, &payload);

  if(payload.payer[0] != '\0') {
    retry_after = x402_abuse_retry_after(r,
                                         X402_ABUSE_SCOPE_PAYER,
                                         route_key,
                                         X402_ABUSE_BUCKET_BAD_PAYMENT,
                                         payload.payer);
    if(retry_after > 0) {
      return x402_emit_too_many_requests(r,
                                         X402_ABUSE_BUCKET_BAD_PAYMENT,
                                         payload.payer,
                                         retry_after);
    }
  }
  else {
    retry_after = x402_abuse_retry_after(r,
                                         X402_ABUSE_SCOPE_IP,
                                         route_key,
                                         X402_ABUSE_BUCKET_BAD_PAYMENT,
                                         x402_client_key(r));
    if(retry_after > 0) {
      return x402_emit_too_many_requests(r,
                                         X402_ABUSE_BUCKET_BAD_PAYMENT,
                                         x402_client_key(r),
                                         retry_after);
    }
  }

  status = provider->verify(&cfg->policy, &request, decoded, &verification);
  if(status != X402_STATUS_OK || !verification.accepted) {
    ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, "x402 verify failed: %s",
                  verification.message);
    if(payload.payer[0] != '\0') {
      retry_after = x402_abuse_hit(r,
                                   X402_ABUSE_SCOPE_PAYER,
                                   route_key,
                                   X402_ABUSE_BUCKET_BAD_PAYMENT,
                                   payload.payer,
                                   X402_ABUSE_BAD_PAYMENT_LIMIT,
                                   X402_ABUSE_BAD_PAYMENT_WINDOW,
                                   X402_ABUSE_BAD_PAYMENT_BLOCK);
    }
    else {
      retry_after = x402_abuse_hit(r,
                                   X402_ABUSE_SCOPE_IP,
                                   route_key,
                                   X402_ABUSE_BUCKET_BAD_PAYMENT,
                                   x402_client_key(r),
                                   X402_ABUSE_BAD_PAYMENT_LIMIT,
                                   X402_ABUSE_BAD_PAYMENT_WINDOW,
                                   X402_ABUSE_BAD_PAYMENT_BLOCK);
    }
    if(retry_after > 0) {
      return x402_emit_too_many_requests(r,
                                         X402_ABUSE_BUCKET_BAD_PAYMENT,
                                         payload.payer[0] == '\0' ? x402_client_key(r) : payload.payer,
                                         retry_after);
    }
    return x402_emit_required(r, cfg, provider);
  }

  status = provider->settle(&cfg->policy, &request, decoded, &settlement);
  if(status != X402_STATUS_OK || !settlement.settled) {
    ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, "x402 settle failed: %s",
                  settlement.message);
    return x402_emit_required(r, cfg, provider);
  }

  if(cfg->policy.forward_to[0] != '\0' && cfg->policy.credits_issued_override > 0) {
    settlement.credits_issued = cfg->policy.credits_issued_override;
    settlement.credits_remaining = cfg->policy.credits_issued_override > 0
                                       ? cfg->policy.credits_issued_override - 1U
                                       : 0U;
  }

  status = x402_build_payment_response_json(&cfg->policy,
                                            &settlement,
                                            response_json,
                                            sizeof(response_json));
  if(status != X402_STATUS_OK) {
    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "x402 response build failed");
    return HTTP_INTERNAL_SERVER_ERROR;
  }

  apr_table_setn(r->notes, "x402-settled", "1");
  apr_table_setn(r->notes, "x402-payer", apr_pstrdup(r->pool, settlement.payer));
  ap_log_rerror(APLOG_MARK,
                APLOG_NOTICE,
                0,
                r,
                "x402 proof response_released payment_id=%s payer=%s route=%s settlement_mode=%s ts_us=%" APR_TIME_T_FMT,
                request.payment_identifier,
                settlement.payer,
                r->uri == NULL ? "(null)" : r->uri,
                settlement.settlement_mode,
                apr_time_now());
  apr_table_setn(r->headers_out,
                 "X402-Proof-Response-Released",
                 apr_psprintf(r->pool,
                              "payment_id=%s;settlement_mode=%s;ts_us=%" APR_TIME_T_FMT,
                              request.payment_identifier,
                              settlement.settlement_mode,
                              apr_time_now()));
  x402_log_syslog_proof("response-released",
                        request.payment_identifier,
                        settlement.payer,
                        r->uri,
                        settlement.transaction_ref);
  x402_trace_async_split(r,
                         request.payment_identifier,
                         "response-released",
                         settlement.transaction_ref);
  apr_table_setn(r->headers_out,
                 "PAYMENT-RESPONSE",
                 x402_encode_header_value(r->pool, response_json));
  if(settlement.split_transaction_hash[0] != '\0') {
    apr_table_setn(r->headers_out,
                   "X402-Split-Transaction-Hash",
                   apr_pstrdup(r->pool, settlement.split_transaction_hash));
  }
  if(cfg->policy.credits.enabled &&
     x402_issue_stellar_auth_challenge(r, &cfg->policy, challenge_json, sizeof(challenge_json))) {
    apr_table_setn(r->headers_out,
                   X402_STELLAR_AUTH_CHALLENGE_HEADER,
                   x402_encode_header_value(r->pool, challenge_json));
  }

  if(cfg->policy.credits.enabled && settlement.credits_remaining > 0) {
    x402_credit_store(r, &cfg->policy, &settlement);
  }

  if(cfg->policy.forward_to[0] != '\0') {
    apr_table_setn(r->notes, "x402-forward-target", apr_pstrdup(r->pool, cfg->policy.forward_to));
    apr_table_setn(r->notes,
                   "x402-forward-payment-response",
                   apr_pstrdup(r->pool, apr_table_get(r->headers_out, "PAYMENT-RESPONSE")));
    apr_table_setn(r->notes, "x402-forward-payer", apr_pstrdup(r->pool, settlement.payer));
    apr_table_setn(r->notes,
                   "x402-forward-auth-challenge",
                   apr_pstrdup(r->pool,
                               apr_table_get(r->headers_out, X402_STELLAR_AUTH_CHALLENGE_HEADER)));
    apr_table_setn(r->notes,
                   "x402-forward-proof-response-released",
                   apr_pstrdup(r->pool,
                               apr_table_get(r->headers_out,
                                             "X402-Proof-Response-Released")));
    apr_table_setn(r->notes,
                   "x402-forward-split-transaction-hash",
                   apr_pstrdup(r->pool, settlement.split_transaction_hash));
    ap_internal_redirect(cfg->policy.forward_to, r);
    return OK;
  }

  if(strcmp(r->method, "GET") == 0 || strcmp(r->method, "HEAD") == 0) {
    return DECLINED;
  }

  ap_set_content_type(r, "application/json");
  ap_rprintf(r, "{\"status\":200,\"paymentResponse\":%s}\n", response_json);
  return OK;
}

static const command_rec x402_cmds[] = {
    AP_INIT_FLAG("X402", x402_set_enabled, NULL, OR_AUTHCFG, "Enable x402 for this location"),
    AP_INIT_TAKE1("X402Scheme", x402_cmd_scheme, NULL, OR_AUTHCFG, "x402 scheme"),
    AP_INIT_TAKE1("X402Network", x402_cmd_network, NULL, OR_AUTHCFG, "x402 network"),
    AP_INIT_TAKE1("X402Asset", x402_cmd_asset, NULL, OR_AUTHCFG, "asset identifier"),
    AP_INIT_TAKE1("X402Amount", x402_cmd_amount, NULL, OR_AUTHCFG, "payment amount"),
    AP_INIT_TAKE1("X402Description", x402_cmd_description, NULL, OR_AUTHCFG, "description"),
    AP_INIT_TAKE1("X402MimeType", x402_cmd_mime_type, NULL, OR_AUTHCFG, "mime type"),
    AP_INIT_TAKE1("X402Mechanism", x402_cmd_mechanism, NULL, OR_AUTHCFG, "mechanism provider"),
    AP_INIT_TAKE1("X402SettlementMode",
                  x402_cmd_settlement_mode,
                  NULL,
                  OR_AUTHCFG,
                  "settlement mode"),
    AP_INIT_TAKE1("X402FacilitatorURL",
                  x402_cmd_facilitator_url,
                  NULL,
                  OR_AUTHCFG,
                  "facilitator URL"),
    AP_INIT_TAKE1("X402FacilitatorAPIKey",
                  x402_cmd_facilitator_api_key,
                  NULL,
                  OR_AUTHCFG,
                  "facilitator bearer API key"),
    AP_INIT_TAKE1("X402FacilitatorAPIKeyFile",
                  x402_cmd_facilitator_api_key_file,
                  NULL,
                  OR_AUTHCFG,
                  "path to facilitator bearer API key file"),
    AP_INIT_TAKE1("X402StellarConfigDir",
                  x402_cmd_stellar_config_dir,
                  NULL,
                  OR_AUTHCFG,
                  "stellar config directory"),
    AP_INIT_TAKE1("X402StellarSourceAccount",
                  x402_cmd_stellar_source_account,
                  NULL,
                  OR_AUTHCFG,
                  "stellar source account or alias for local settlement"),
    AP_INIT_TAKE1("X402StellarRpcURL",
                  x402_cmd_stellar_rpc_url,
                  NULL,
                  OR_AUTHCFG,
                  "Soroban RPC URL for local settlement"),
    AP_INIT_TAKE1("X402StellarNetworkPassphrase",
                  x402_cmd_stellar_network_passphrase,
                  NULL,
                  OR_AUTHCFG,
                  "network passphrase for local settlement"),
    AP_INIT_TAKE1("X402StellarLocalBackend",
                  x402_cmd_stellar_local_backend,
                  NULL,
                  OR_AUTHCFG,
                  "local settlement backend: auto or inprocess"),
    AP_INIT_TAKE1("X402TimeoutSeconds", x402_cmd_timeout, NULL, OR_AUTHCFG, "timeout seconds"),
    AP_INIT_TAKE1("X402PaymentIdentifier",
                  x402_cmd_payment_identifier,
                  NULL,
                  OR_AUTHCFG,
                  "payment identifier policy"),
    AP_INIT_TAKE1("X402PayTo", x402_cmd_pay_to, NULL, OR_AUTHCFG, "recipient"),
    AP_INIT_TAKE1("X402SplitMode", x402_cmd_split_mode, NULL, OR_AUTHCFG | RSRC_CONF, "split mode"),
    AP_INIT_TAKE1("X402SplitterContract",
                  x402_cmd_splitter_contract,
                  NULL,
                  OR_AUTHCFG | RSRC_CONF,
                  "splitter contract"),
    AP_INIT_TAKE3("X402Stakeholder",
                  x402_cmd_stakeholder,
                  NULL,
                  OR_AUTHCFG | RSRC_CONF,
                  "stakeholder name, basis points, destination"),
    AP_INIT_FLAG("X402Prepay", x402_cmd_prepay, NULL, OR_AUTHCFG, "enable prepaid requests"),
    AP_INIT_TAKE1("X402PrepayMultiplierMax",
                  x402_cmd_prepay_multiplier,
                  NULL,
                  OR_AUTHCFG,
                  "maximum prepaid multiplier"),
    AP_INIT_TAKE1("X402CreditScope", x402_cmd_credit_scope, NULL, OR_AUTHCFG, "credit scope"),
    AP_INIT_TAKE1("X402CreditTTLSeconds",
                  x402_cmd_credit_ttl,
                  NULL,
                  OR_AUTHCFG,
                  "credit TTL seconds"),
    AP_INIT_TAKE1("X402CreditsIssued",
                  x402_cmd_credits_issued,
                  NULL,
                  OR_AUTHCFG,
                  "credits issued by this purchase route"),
    AP_INIT_TAKE1("X402ForwardTo",
                  x402_cmd_forward_to,
                  NULL,
                  OR_AUTHCFG,
                  "internal forward target after successful purchase"),
    AP_INIT_TAKE1("X402CreditDBPath",
                  x402_cmd_credit_db_path,
                  NULL,
                  RSRC_CONF,
                  "sqlite database path for durable prepaid credits"),
    {NULL}};

static void x402_child_init(apr_pool_t *pool, server_rec *server)
{
  if(sodium_init() < 0) {
    ap_log_error(APLOG_MARK, APLOG_CRIT, 0, server, "x402: libsodium init failed");
  }
  if(x402_credit_mutex == NULL) {
    apr_thread_mutex_create(&x402_credit_mutex, APR_THREAD_MUTEX_DEFAULT, pool);
  }
  x402_credit_db_close();
  x402_credit_db_open(server, 0);
}

static int x402_post_config(apr_pool_t *pool,
                            apr_pool_t *log_pool,
                            apr_pool_t *temp_pool,
                            server_rec *server)
{
  (void)pool;
  (void)log_pool;
  (void)temp_pool;

  x402_credit_db_close();
  return x402_credit_db_open(server, 1) ? OK : HTTP_INTERNAL_SERVER_ERROR;
}

static void x402_register_hooks(apr_pool_t *pool)
{
  (void)pool;
  ap_hook_post_config(x402_post_config, NULL, NULL, APR_HOOK_MIDDLE);
  ap_hook_child_init(x402_child_init, NULL, NULL, APR_HOOK_MIDDLE);
  ap_hook_access_checker(x402_check_access, NULL, NULL, APR_HOOK_MIDDLE);
}

module AP_MODULE_DECLARE_DATA x402_module = {
    STANDARD20_MODULE_STUFF,
    x402_create_dir_config,
    x402_merge_dir_config,
    x402_create_server_config,
    x402_merge_server_config,
    x402_cmds,
    x402_register_hooks,
    0};

#else

int mod_x402_requires_apache_dev_headers(void)
{
  return 0;
}

#endif
