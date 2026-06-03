#include "../../core/x402_provider.h"

#include <curl/curl.h>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <sqlite3.h>
#include <sodium.h>

#include "schemas/xdr/Stellar-contract.h"
#include "schemas/xdr/Stellar-ledger-entries.h"
#include "schemas/xdr/Stellar-transaction.h"
#include "schemas/xdr/Stellar-types.h"
#include <xdrpp/marshal.h>

#include <algorithm>
#include <array>
#include <chrono>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <stdexcept>
#include <memory>
#include <syslog.h>
#include <string>
#include <thread>
#include <vector>

static x402_status stellar_declare_requirements(const x402_route_policy *policy,
                                                const x402_request_context *request,
                                                x402_payment_requirements *requirements);

namespace {

struct HttpResponse {
  CURLcode code;
  long status;
  std::string body;
};

constexpr const char *kDefaultSorobanRpcUrl = "https://soroban-testnet.stellar.org:443";
constexpr const char *kDefaultSorobanNetworkPassphrase = "Test SDF Network ; September 2015";
constexpr uint32_t kDefaultBaseFee = 100;
constexpr const char *kAsyncSplitDbPath = "/var/lib/x402/credits.db";

struct SignerMaterial {
  std::array<unsigned char, 32> public_key{};
  std::array<unsigned char, 32> secret_seed{};
};

struct PreparedInprocessEnvelope {
  std::string envelope_xdr_b64;
  std::string simulation_body;
  std::string transaction_hash_hex;
};

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
  std::string *body = static_cast<std::string *>(userdata);
  size_t bytes = size * nmemb;
  body->append(ptr, bytes);
  return bytes;
}

std::string truncate_for_log(const std::string &value, size_t max_len = 512)
{
  if(value.size() <= max_len) {
    return value;
  }
  return value.substr(0, max_len) + "...";
}

bool json_true_for_key(const char *json, const char *key)
{
  char pattern[96];
  const char *at;

  if(json == nullptr || key == nullptr) {
    return false;
  }

  std::snprintf(pattern, sizeof(pattern), "\"%s\":true", key);
  at = std::strstr(json, pattern);
  return at != nullptr;
}

void copy_if_present(x402_status (*extractor)(const char *, const char *, char *, size_t),
                     const char *json,
                     const char *key,
                     char *target,
                     size_t size)
{
  if(extractor(json, key, target, size) != X402_STATUS_OK) {
    target[0] = '\0';
  }
}

void build_requirements_json(const x402_route_policy *policy,
                             const x402_request_context *request,
                             std::string *json)
{
  x402_payment_requirements requirements;
  std::memset(&requirements, 0, sizeof(requirements));
  stellar_declare_requirements(policy, request, &requirements);

  char buffer[2048];
  std::snprintf(buffer,
                sizeof(buffer),
                "{\"scheme\":\"%s\",\"network\":\"%s\",\"amount\":\"%llu\","
                "\"asset\":\"%s\",\"payTo\":\"%s\",\"maxTimeoutSeconds\":%u,"
                "\"extra\":{\"mechanism\":\"%s\",\"profile\":\"%s\","
                "\"payToKind\":\"%s\",\"areFeesSponsored\":true}}",
                policy->scheme,
                policy->network,
                static_cast<unsigned long long>(requirements.amount),
                policy->asset,
                requirements.pay_to,
                requirements.timeout_seconds,
                policy->mechanism,
                std::strcmp(policy->mechanism, "stellar") == 0 ? "sep41-exact-v1" : "custom-v1",
                policy->split_mode == X402_SPLIT_MULTI ? "splitter-contract" : "direct-recipient");
  *json = buffer;
}

std::string append_endpoint(const char *base, const char *path)
{
  std::string url = base == nullptr ? "" : base;

  if(url.empty()) {
    return url;
  }
  if(url.back() == '/') {
    url.pop_back();
  }
  url += path;
  return url;
}

HttpResponse post_json(const char *url,
                      const std::string &body,
                      uint32_t timeout_seconds,
                      const char *api_key)
{
  HttpResponse response{};
  CURL *curl = curl_easy_init();
  struct curl_slist *headers = nullptr;
  std::string auth_header;

  response.code = CURLE_FAILED_INIT;
  response.status = 0;

  if(curl == nullptr) {
    return response;
  }

  headers = curl_slist_append(headers, "Content-Type: application/json");
  if(api_key != nullptr && api_key[0] != '\0') {
    auth_header = "Authorization: Bearer ";
    auth_header += api_key;
    headers = curl_slist_append(headers, auth_header.c_str());
  }
  curl_easy_setopt(curl, CURLOPT_URL, url);
  curl_easy_setopt(curl, CURLOPT_POST, 1L);
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
  curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, static_cast<long>(body.size()));
  curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout_seconds == 0 ? 30U : timeout_seconds);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response.body);

  response.code = curl_easy_perform(curl);
  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response.status);

  curl_slist_free_all(headers);
  curl_easy_cleanup(curl);
  return response;
}

void map_http_error(const HttpResponse &http,
                    x402_status status,
                    const char *default_code,
                    const char *default_message,
                    char *error_code,
                    size_t error_code_size,
                    char *message,
                    size_t message_size)
{
  std::snprintf(error_code, error_code_size, "%s", default_code);
  if(!http.body.empty()) {
    copy_if_present(x402_extract_json_string, http.body.c_str(), "code", error_code, error_code_size);
    copy_if_present(x402_extract_json_string, http.body.c_str(), "message", message, message_size);
  }
  if(message[0] == '\0') {
    std::snprintf(message,
                  message_size,
                  "%s (curl=%d status=%ld)",
                  default_message,
                  static_cast<int>(http.code),
                  http.status);
  }
  (void)status;
}

bool use_facilitator(const x402_route_policy *policy)
{
  return policy != nullptr &&
         policy->facilitator_url[0] != '\0' &&
         policy->settlement_mode != X402_SETTLEMENT_LOCAL;
}

const char *effective_rpc_url(const x402_route_policy *policy)
{
  if(policy != nullptr && policy->stellar_rpc_url[0] != '\0') {
    return policy->stellar_rpc_url;
  }
  return kDefaultSorobanRpcUrl;
}

const char *effective_network_passphrase(const x402_route_policy *policy)
{
  if(policy != nullptr && policy->stellar_network_passphrase[0] != '\0') {
    return policy->stellar_network_passphrase;
  }
  return kDefaultSorobanNetworkPassphrase;
}

bool is_hex_string(const char *value)
{
  if(value == nullptr || value[0] == '\0') {
    return false;
  }

  for(const char *at = value; *at != '\0'; ++at) {
    if(!( (*at >= '0' && *at <= '9') ||
          (*at >= 'a' && *at <= 'f') ||
          (*at >= 'A' && *at <= 'F') )) {
      return false;
    }
  }
  return true;
}

std::string derive_payment_id_hex(const x402_request_context *request,
                                  const x402_settlement_result *result)
{
  const char *candidate = nullptr;
  static const char hex[] = "0123456789abcdef";
  std::string derived;

  if(result != nullptr && std::strlen(result->transaction_ref) == 64 &&
     is_hex_string(result->transaction_ref)) {
    return result->transaction_ref;
  }
  if(request != nullptr && std::strlen(request->payment_identifier) == 64 &&
     is_hex_string(request->payment_identifier)) {
    return request->payment_identifier;
  }

  if(result != nullptr && result->transaction_ref[0] != '\0') {
    candidate = result->transaction_ref;
  }
  else if(request != nullptr && request->payment_identifier[0] != '\0') {
    candidate = request->payment_identifier;
  }
  else if(request != nullptr && request->request_id[0] != '\0') {
    candidate = request->request_id;
  }
  else {
    candidate = "x402-split-payment";
  }

  for(size_t i = 0; candidate[i] != '\0' && derived.size() < 64; ++i) {
    unsigned char byte = static_cast<unsigned char>(candidate[i]);
    derived.push_back(hex[(byte >> 4U) & 0x0FU]);
    derived.push_back(hex[byte & 0x0FU]);
  }
  while(derived.size() < 64) {
    derived.push_back('0');
  }
  derived.resize(64);
  return derived;
}

uint64_t effective_payment_amount(const x402_route_policy *policy,
                                  const x402_request_context *request)
{
  if(policy->credits_issued_override > 0) {
    return policy->amount;
  }
  uint32_t multiplier = request != nullptr && request->requested_multiplier != 0
                            ? request->requested_multiplier
                            : 1U;
  return policy->amount * static_cast<uint64_t>(multiplier);
}

uint32_t effective_credit_count(const x402_route_policy *policy,
                                const x402_request_context *request)
{
  if(policy->credits_issued_override > 0) {
    return policy->credits_issued_override;
  }
  return request != nullptr && request->requested_multiplier != 0 ? request->requested_multiplier : 1U;
}

bool file_to_string(const std::string &path, std::string *contents)
{
  std::array<char, 512> buffer{};
  std::unique_ptr<FILE, int (*)(FILE *)> file(std::fopen(path.c_str(), "rb"), std::fclose);

  if(file == nullptr || contents == nullptr) {
    return false;
  }

  contents->clear();
  while(true) {
    size_t read = std::fread(buffer.data(), 1, buffer.size(), file.get());
    if(read > 0) {
      contents->append(buffer.data(), read);
    }
    if(read < buffer.size()) {
      return std::feof(file.get()) != 0;
    }
  }
}

bool extract_toml_string(const std::string &toml, const char *key, std::string *value)
{
  std::string search_key;
  size_t key_len;
  size_t pos;
  size_t p;
  size_t equals_pos = std::string::npos;
  size_t first_quote;
  size_t second_quote;

  if(key == nullptr || value == nullptr) {
    return false;
  }

  search_key = key;
  key_len = search_key.size();
  if(key_len == 0) {
    return false;
  }

  pos = 0;
  while((pos = toml.find(search_key, pos)) != std::string::npos) {
    if(pos > 0) {
      char before = toml[pos - 1];
      if(before != '\n' && before != '\r' && before != ' ' && before != '\t') {
        pos += key_len;
        continue;
      }
    }
    p = pos + key_len;
    while(p < toml.size() && (toml[p] == ' ' || toml[p] == '\t')) {
      ++p;
    }
    if(p < toml.size() && toml[p] == '=') {
      equals_pos = p;
      break;
    }
    pos += key_len;
  }

  if(equals_pos == std::string::npos) {
    return false;
  }

  first_quote = toml.find('"', equals_pos + 1);
  if(first_quote == std::string::npos) {
    return false;
  }
  second_quote = toml.find('"', first_quote + 1);
  if(second_quote == std::string::npos) {
    return false;
  }

  *value = toml.substr(first_quote + 1, second_quote - first_quote - 1);
  return true;
}

bool load_signer_material(const x402_route_policy *policy, std::string *identity_kind, std::string *identity_value)
{
  std::string path;
  std::string toml;

  if(policy == nullptr || identity_kind == nullptr || identity_value == nullptr) {
    return false;
  }
  if(policy->stellar_config_dir[0] == '\0' || policy->stellar_source_account[0] == '\0') {
    return false;
  }

  path = policy->stellar_config_dir;
  if(!path.empty() && path.back() != '/') {
    path.push_back('/');
  }
  path += "identity/";
  path += policy->stellar_source_account;
  path += ".toml";

  if(!file_to_string(path, &toml)) {
    return false;
  }
  if(extract_toml_string(toml, "secret_key", identity_value)) {
    *identity_kind = "secret_key";
    return true;
  }
  if(extract_toml_string(toml, "seed_phrase", identity_value)) {
    *identity_kind = "seed_phrase";
    return true;
  }
  return false;
}

int base32_value(char ch)
{
  if(ch >= 'A' && ch <= 'Z') {
    return ch - 'A';
  }
  if(ch >= '2' && ch <= '7') {
    return 26 + (ch - '2');
  }
  return -1;
}

uint16_t crc16_xmodem(const std::vector<unsigned char> &payload)
{
  uint16_t crc = 0;

  for(unsigned char byte : payload) {
    crc ^= static_cast<uint16_t>(byte) << 8U;
    for(int i = 0; i < 8; ++i) {
      crc = (crc & 0x8000U) != 0U ? static_cast<uint16_t>((crc << 1U) ^ 0x1021U)
                                  : static_cast<uint16_t>(crc << 1U);
    }
  }
  return crc;
}

bool decode_stellar_strkey(char expected_version,
                           uint8_t expected_version_byte,
                           const std::string &encoded,
                           std::array<unsigned char, 32> *decoded)
{
  int bits = 0;
  uint32_t accumulator = 0;
  std::vector<unsigned char> bytes;

  if(decoded == nullptr || encoded.empty() || encoded.front() != expected_version) {
    return false;
  }

  bytes.reserve((encoded.size() * 5U) / 8U);
  for(char ch : encoded) {
    int value = base32_value(ch);
    if(value < 0) {
      return false;
    }
    accumulator = (accumulator << 5U) | static_cast<uint32_t>(value);
    bits += 5;
    while(bits >= 8) {
      bits -= 8;
      bytes.push_back(static_cast<unsigned char>((accumulator >> bits) & 0xFFU));
    }
  }

  if(bytes.size() != 35 || bytes[0] != expected_version_byte) {
    return false;
  }

  std::vector<unsigned char> payload(bytes.begin(), bytes.begin() + 33);
  uint16_t expected_crc = crc16_xmodem(payload);
  uint16_t actual_crc = static_cast<uint16_t>(bytes[33]) |
                        static_cast<uint16_t>(bytes[34]) << 8U;
  if(expected_crc != actual_crc) {
    return false;
  }

  std::copy(bytes.begin() + 1, bytes.begin() + 33, decoded->begin());
  return true;
}

std::string base64_encode(const std::vector<unsigned char> &bytes)
{
  if(bytes.empty()) {
    return "";
  }

  std::string encoded;
  encoded.resize(4 * ((bytes.size() + 2) / 3));
  int length = EVP_EncodeBlock(reinterpret_cast<unsigned char *>(&encoded[0]),
                               bytes.data(),
                               static_cast<int>(bytes.size()));
  encoded.resize(length < 0 ? 0 : static_cast<size_t>(length));
  return encoded;
}

bool base64_decode(const std::string &input, std::vector<unsigned char> *decoded)
{
  std::vector<unsigned char> buffer;
  int output_length = 0;
  size_t padding = 0;

  if(decoded == nullptr) {
    return false;
  }
  if(input.empty()) {
    decoded->clear();
    return true;
  }

  if(input.size() % 4 != 0) {
    return false;
  }
  if(input.size() >= 1 && input[input.size() - 1] == '=') {
    padding++;
  }
  if(input.size() >= 2 && input[input.size() - 2] == '=') {
    padding++;
  }

  buffer.resize((input.size() / 4) * 3);
  output_length = EVP_DecodeBlock(buffer.data(),
                                  reinterpret_cast<const unsigned char *>(input.data()),
                                  static_cast<int>(input.size()));
  if(output_length < 0) {
    return false;
  }
  buffer.resize(static_cast<size_t>(output_length) - padding);
  *decoded = std::move(buffer);
  return true;
}

bool extract_json_string_array_for_key(const std::string &json,
                                       const char *key,
                                       std::vector<std::string> *values)
{
  std::string pattern;
  size_t key_pos;
  size_t open_bracket;
  size_t cursor;

  if(key == nullptr || values == nullptr) {
    return false;
  }

  pattern = "\"";
  pattern += key;
  pattern += "\":[";
  key_pos = json.find(pattern);
  if(key_pos == std::string::npos) {
    values->clear();
    return false;
  }

  open_bracket = key_pos + pattern.size() - 1U;
  cursor = open_bracket + 1U;
  values->clear();

  while(cursor < json.size()) {
    while(cursor < json.size() &&
          (json[cursor] == ' ' || json[cursor] == '\n' || json[cursor] == '\r' || json[cursor] == '\t' || json[cursor] == ',')) {
      ++cursor;
    }
    if(cursor >= json.size()) {
      break;
    }
    if(json[cursor] == ']') {
      return true;
    }
    if(json[cursor] != '"') {
      return false;
    }

    ++cursor;
    size_t start = cursor;
    while(cursor < json.size() && json[cursor] != '"') {
      if(json[cursor] == '\\') {
        return false;
      }
      ++cursor;
    }
    if(cursor >= json.size()) {
      return false;
    }
    values->push_back(json.substr(start, cursor - start));
    ++cursor;
  }

  return false;
}

bool load_secret_signer_material(const x402_route_policy *policy,
                                 SignerMaterial *signer,
                                 std::string *error)
{
  std::string identity_kind;
  std::string identity_value;
  std::array<unsigned char, crypto_sign_PUBLICKEYBYTES> public_key{};
  std::array<unsigned char, crypto_sign_SECRETKEYBYTES> secret_key{};

  if(signer == nullptr) {
    if(error != nullptr) {
      *error = "missing signer output";
    }
    return false;
  }
  if(!load_signer_material(policy, &identity_kind, &identity_value)) {
    if(error != nullptr) {
      *error = "unable to load identity material";
    }
    return false;
  }
  if(identity_kind != "secret_key") {
    if(error != nullptr) {
      *error = "in-process backend currently supports secret_key identities only";
    }
    return false;
  }
  if(!decode_stellar_strkey('S', 18U << 3U, identity_value, &signer->secret_seed)) {
    if(error != nullptr) {
      *error = "invalid Stellar secret seed";
    }
    return false;
  }
  if(crypto_sign_seed_keypair(public_key.data(), secret_key.data(), signer->secret_seed.data()) != 0) {
    if(error != nullptr) {
      *error = "unable to derive ed25519 keypair from Stellar seed";
    }
    return false;
  }
  std::copy(public_key.begin(), public_key.end(), signer->public_key.begin());
  sodium_memzero(secret_key.data(), secret_key.size());
  return true;
}

stellar::AccountID make_account_id(const std::array<unsigned char, 32> &raw_key)
{
  stellar::AccountID account(stellar::PUBLIC_KEY_TYPE_ED25519);
  std::copy(raw_key.begin(), raw_key.end(), account.ed25519().begin());
  return account;
}

stellar::MuxedAccount make_muxed_account(const std::array<unsigned char, 32> &raw_key)
{
  stellar::MuxedAccount account(stellar::KEY_TYPE_ED25519);
  std::copy(raw_key.begin(), raw_key.end(), account.ed25519().begin());
  return account;
}

stellar::SCAddress make_sc_address_from_strkey(const std::string &address)
{
  std::array<unsigned char, 32> raw{};
  stellar::SCAddress sc_address;

  if(!address.empty() && address.front() == 'G') {
    if(!decode_stellar_strkey('G', 6U << 3U, address, &raw)) {
      throw std::runtime_error("invalid account StrKey");
    }
    sc_address.type(stellar::SC_ADDRESS_TYPE_ACCOUNT);
    sc_address.accountId() = make_account_id(raw);
    return sc_address;
  }
  if(!address.empty() && address.front() == 'C') {
    if(!decode_stellar_strkey('C', 2U << 3U, address, &raw)) {
      throw std::runtime_error("invalid contract StrKey");
    }
    sc_address.type(stellar::SC_ADDRESS_TYPE_CONTRACT);
    std::copy(raw.begin(), raw.end(), sc_address.contractId().begin());
    return sc_address;
  }
  throw std::runtime_error("unsupported StrKey type");
}

stellar::SCVal make_sc_address_val(const std::string &address)
{
  stellar::SCVal value(stellar::SCV_ADDRESS);
  value.address() = make_sc_address_from_strkey(address);
  return value;
}

stellar::SCVal make_sc_bytes_val(const std::vector<unsigned char> &bytes)
{
  stellar::SCVal value(stellar::SCV_BYTES);
  value.bytes().insert(value.bytes().end(), bytes.begin(), bytes.end());
  return value;
}

stellar::SCVal make_sc_symbol_val(const std::string &symbol)
{
  stellar::SCVal value(stellar::SCV_SYMBOL);
  value.sym() = symbol;
  return value;
}

stellar::SCVal make_sc_i128_val(uint64_t amount)
{
  stellar::SCVal value(stellar::SCV_I128);
  value.i128().hi = 0;
  value.i128().lo = amount;
  return value;
}

stellar::SCVal make_sc_map_val(const std::vector<std::pair<std::string, stellar::SCVal>> &entries)
{
  stellar::SCVal value(stellar::SCV_MAP);
  stellar::SCMap map;

  for(const auto &entry : entries) {
    stellar::SCMapEntry item;
    item.key = make_sc_symbol_val(entry.first);
    item.val = entry.second;
    map.push_back(item);
  }

  value.map().activate() = map;
  return value;
}

stellar::SCVal make_sc_vec_val(const std::vector<stellar::SCVal> &items)
{
  stellar::SCVal value(stellar::SCV_VEC);
  stellar::SCVec vec;

  for(const auto &item : items) {
    vec.push_back(item);
  }
  value.vec().activate() = vec;
  return value;
}

template<typename T>
std::vector<unsigned char> to_xdr_bytes(const T &value)
{
  return xdr::xdr_to_opaque(value);
}

template<typename T>
std::string to_xdr_base64(const T &value)
{
  return base64_encode(to_xdr_bytes(value));
}

template<typename T>
bool from_xdr_base64(const std::string &encoded, T *value)
{
  std::vector<unsigned char> bytes;
  if(value == nullptr || !base64_decode(encoded, &bytes)) {
    return false;
  }
  try {
    xdr::xdr_from_opaque(bytes, *value);
    return true;
  }
  catch(const std::exception &) {
    return false;
  }
}

std::string json_rpc_wrap(const char *method, const std::string &params)
{
  std::string body = "{\"jsonrpc\":\"2.0\",\"id\":1,\"method\":\"";
  body += method;
  body += "\",\"params\":";
  body += params;
  body += "}";
  return body;
}

bool fetch_account_sequence_rpc(const x402_route_policy *policy,
                                const stellar::AccountID &account_id,
                                stellar::SequenceNumber *sequence,
                                std::string *error)
{
  stellar::LedgerKey ledger_key(stellar::ACCOUNT);
  stellar::LedgerEntry::_data_t entry_data;
  HttpResponse http{};
  char key_b64[256];
  char entry_b64[4096];

  if(sequence == nullptr) {
    if(error != nullptr) {
      *error = "missing sequence output";
    }
    return false;
  }

  ledger_key.account().accountID = account_id;
  std::snprintf(key_b64, sizeof(key_b64), "%s", to_xdr_base64(ledger_key).c_str());
  http = post_json(effective_rpc_url(policy),
                   json_rpc_wrap("getLedgerEntries",
                                 std::string("{\"keys\":[\"") + key_b64 + "\"]}"),
                   policy->timeout_seconds,
                   "");
  if(http.code != CURLE_OK || http.status >= 400) {
    if(error != nullptr) {
      *error = "getLedgerEntries failed";
    }
    return false;
  }

  if(x402_extract_json_string(http.body.c_str(), "xdr", entry_b64, sizeof(entry_b64)) != X402_STATUS_OK) {
    if(error != nullptr) {
      *error = "account ledger entry xdr not present in RPC response";
    }
    return false;
  }

  if(!from_xdr_base64(std::string(entry_b64), &entry_data)) {
    if(error != nullptr) {
      *error = "could not decode account ledger entry xdr";
    }
    return false;
  }
  if(entry_data.type() != stellar::ACCOUNT) {
    if(error != nullptr) {
      *error = "ledger entry was not an account entry";
    }
    return false;
  }

  *sequence = entry_data.account().seqNum;
  return true;
}

stellar::InvokeHostFunctionOp build_settle_balance_invoke(const x402_route_policy *policy,
                                                          const std::string &payment_id_hex,
                                                          uint64_t total_amount)
{
  stellar::InvokeContractArgs args;
  std::vector<unsigned char> payment_id;
  std::vector<stellar::SCVal> split_values;
  stellar::SCVal token_arg;
  stellar::SCVal payment_id_arg;
  stellar::SCVal splits_arg;
  stellar::HostFunction host_function(stellar::HOST_FUNCTION_TYPE_INVOKE_CONTRACT);
  stellar::InvokeHostFunctionOp op;

  if(payment_id_hex.size() != 64) {
    throw std::runtime_error("payment id must be 32 bytes encoded as 64 hex characters");
  }

  token_arg = make_sc_address_val(policy->asset);
  payment_id.reserve(32);
  for(size_t i = 0; i < payment_id_hex.size(); i += 2) {
    std::string byte_text = payment_id_hex.substr(i, 2);
    payment_id.push_back(static_cast<unsigned char>(std::strtoul(byte_text.c_str(), nullptr, 16)));
  }
  payment_id_arg = make_sc_bytes_val(payment_id);

  for(size_t i = 0; i < policy->stakeholder_count; ++i) {
    std::vector<std::pair<std::string, stellar::SCVal>> map_entries;
    map_entries.push_back({"amount", make_sc_i128_val(x402_calculate_stakeholder_amount(total_amount, i, policy))});
    map_entries.push_back({"to", make_sc_address_val(policy->stakeholders[i].destination)});
    split_values.push_back(make_sc_map_val(map_entries));
  }
  splits_arg = make_sc_vec_val(split_values);

  args.contractAddress = make_sc_address_from_strkey(policy->splitter_contract);
  args.functionName = "settle_balance";
  args.args.push_back(token_arg);
  args.args.push_back(payment_id_arg);
  args.args.push_back(splits_arg);

  host_function.invokeContract() = args;
  op.hostFunction = host_function;
  op.auth.clear();
  return op;
}

stellar::Transaction build_unsigned_invoke_transaction(const std::array<unsigned char, 32> &source_public_key,
                                                       stellar::SequenceNumber account_sequence,
                                                       uint32_t inclusion_fee,
                                                       uint32_t timeout_seconds,
                                                       const stellar::InvokeHostFunctionOp &invoke_op)
{
  stellar::Transaction transaction;
  stellar::Operation operation;
  uint64_t now = static_cast<uint64_t>(std::time(nullptr));
  uint64_t timeout = timeout_seconds == 0 ? 30U : timeout_seconds;

  transaction.sourceAccount = make_muxed_account(source_public_key);
  transaction.fee = inclusion_fee;
  transaction.seqNum = account_sequence + 1;
  transaction.cond = stellar::Preconditions(stellar::PRECOND_TIME);
  transaction.cond.timeBounds() = stellar::TimeBounds(0, now + timeout);
  transaction.memo = stellar::Memo(stellar::MEMO_NONE);
  transaction.ext.v(0);

  operation.sourceAccount.reset();
  operation.body.type(stellar::INVOKE_HOST_FUNCTION);
  operation.body.invokeHostFunctionOp() = invoke_op;
  transaction.operations.push_back(operation);
  return transaction;
}

std::string build_simulation_request_body(const stellar::TransactionEnvelope &envelope)
{
  std::string transaction_b64 = to_xdr_base64(envelope);
  return json_rpc_wrap("simulateTransaction",
                       std::string("{\"transaction\":\"") + transaction_b64 + "\"}");
}

bool apply_simulation_to_transaction(const HttpResponse &simulation,
                                     stellar::Transaction *transaction,
                                     uint32_t *fee,
                                     std::string *error)
{
  char transaction_data_b64[4096];
  stellar::SorobanTransactionData data;
  std::vector<std::string> auth_entries_b64;

  if(transaction == nullptr || fee == nullptr) {
    if(error != nullptr) {
      *error = "missing transaction outputs";
    }
    return false;
  }
  if(x402_extract_json_string(simulation.body.c_str(),
                              "transactionData",
                              transaction_data_b64,
                              sizeof(transaction_data_b64)) != X402_STATUS_OK &&
     x402_extract_json_string(simulation.body.c_str(),
                              "transactionDataXdr",
                              transaction_data_b64,
                              sizeof(transaction_data_b64)) != X402_STATUS_OK) {
    if(error != nullptr) {
      *error = "simulateTransaction did not return transactionData";
    }
    return false;
  }
  if(!from_xdr_base64(std::string(transaction_data_b64), &data)) {
    if(error != nullptr) {
      *error = "unable to decode Soroban transaction data from simulation";
    }
    return false;
  }
  transaction->ext.v(1);
  transaction->ext.sorobanData() = data;
  *fee = kDefaultBaseFee + static_cast<uint32_t>(data.resourceFee);
  transaction->fee = *fee;

  if(!transaction->operations.empty() &&
     transaction->operations[0].body.type() == stellar::INVOKE_HOST_FUNCTION &&
     transaction->operations[0].body.invokeHostFunctionOp().auth.empty() &&
     extract_json_string_array_for_key(simulation.body, "auth", &auth_entries_b64)) {
    for(const auto &entry_b64 : auth_entries_b64) {
      stellar::SorobanAuthorizationEntry entry;
      if(!from_xdr_base64(entry_b64, &entry)) {
        if(error != nullptr) {
          *error = "unable to decode Soroban authorization entry from simulation";
        }
        return false;
      }
      transaction->operations[0].body.invokeHostFunctionOp().auth.push_back(entry);
    }
  }
  return true;
}

stellar::DecoratedSignature make_decorated_signature(const stellar::Transaction &transaction,
                                                     const std::string &network_passphrase,
                                                     const SignerMaterial &signer)
{
  stellar::TransactionSignaturePayload payload;
  std::array<unsigned char, SHA256_DIGEST_LENGTH> network_id{};
  std::vector<unsigned char> payload_bytes;
  std::array<unsigned char, SHA256_DIGEST_LENGTH> payload_hash{};
  std::array<unsigned char, crypto_sign_BYTES> signature{};
  std::array<unsigned char, crypto_sign_PUBLICKEYBYTES> public_key{};
  std::array<unsigned char, crypto_sign_SECRETKEYBYTES> secret_key{};
  unsigned long long signature_length = 0;
  stellar::DecoratedSignature decorated;

  SHA256(reinterpret_cast<const unsigned char *>(network_passphrase.data()),
         network_passphrase.size(),
         network_id.data());
  std::copy(network_id.begin(), network_id.end(), payload.networkId.begin());
  payload.taggedTransaction.type(stellar::ENVELOPE_TYPE_TX);
  payload.taggedTransaction.tx() = transaction;
  payload_bytes = to_xdr_bytes(payload);
  SHA256(payload_bytes.data(), payload_bytes.size(), payload_hash.data());

  crypto_sign_seed_keypair(public_key.data(), secret_key.data(), signer.secret_seed.data());
  crypto_sign_detached(signature.data(),
                       &signature_length,
                       payload_hash.data(),
                       payload_hash.size(),
                       secret_key.data());
  sodium_memzero(secret_key.data(), secret_key.size());

  std::copy(signer.public_key.end() - 4, signer.public_key.end(), decorated.hint.begin());
  decorated.signature.insert(decorated.signature.end(), signature.begin(), signature.begin() + signature_length);
  return decorated;
}

std::string transaction_hash_hex(const stellar::Transaction &transaction,
                                 const std::string &network_passphrase)
{
  stellar::TransactionSignaturePayload payload;
  std::array<unsigned char, SHA256_DIGEST_LENGTH> network_id{};
  std::vector<unsigned char> payload_bytes;
  std::array<unsigned char, SHA256_DIGEST_LENGTH> payload_hash{};
  std::string hex;
  static const char *kHex = "0123456789abcdef";

  SHA256(reinterpret_cast<const unsigned char *>(network_passphrase.data()),
         network_passphrase.size(),
         network_id.data());
  std::copy(network_id.begin(), network_id.end(), payload.networkId.begin());
  payload.taggedTransaction.type(stellar::ENVELOPE_TYPE_TX);
  payload.taggedTransaction.tx() = transaction;
  payload_bytes = to_xdr_bytes(payload);
  SHA256(payload_bytes.data(), payload_bytes.size(), payload_hash.data());

  hex.reserve(payload_hash.size() * 2U);
  for(unsigned char byte : payload_hash) {
    hex.push_back(kHex[(byte >> 4) & 0x0fU]);
    hex.push_back(kHex[byte & 0x0fU]);
  }
  return hex;
}

bool build_signed_transaction_envelope(const x402_route_policy *policy,
                                       const SignerMaterial &signer,
                                       stellar::SequenceNumber account_sequence,
                                       const stellar::InvokeHostFunctionOp &invoke_op,
                                       PreparedInprocessEnvelope *prepared,
                                       std::string *error)
{
  stellar::Transaction transaction = build_unsigned_invoke_transaction(signer.public_key,
                                                                       account_sequence,
                                                                       kDefaultBaseFee,
                                                                       policy->timeout_seconds,
                                                                       invoke_op);
  stellar::TransactionEnvelope unsigned_envelope(stellar::ENVELOPE_TYPE_TX);
  HttpResponse simulation{};
  uint32_t fee = kDefaultBaseFee;
  stellar::DecoratedSignature decorated;

  if(prepared == nullptr) {
    if(error != nullptr) {
      *error = "missing prepared envelope output";
    }
    return false;
  }

  unsigned_envelope.v1().tx = transaction;
  prepared->simulation_body = build_simulation_request_body(unsigned_envelope);
  simulation = post_json(effective_rpc_url(policy), prepared->simulation_body, policy->timeout_seconds, "");
  if(simulation.code != CURLE_OK || simulation.status >= 400) {
    if(error != nullptr) {
      *error = "simulateTransaction request failed";
    }
    return false;
  }
  if(!apply_simulation_to_transaction(simulation, &transaction, &fee, error)) {
    return false;
  }

  unsigned_envelope.v1().tx = transaction;
  decorated = make_decorated_signature(transaction, effective_network_passphrase(policy), signer);
  unsigned_envelope.v1().signatures.push_back(decorated);
  prepared->envelope_xdr_b64 = to_xdr_base64(unsigned_envelope);
  prepared->transaction_hash_hex = transaction_hash_hex(transaction, effective_network_passphrase(policy));
  return true;
}

bool submit_transaction(const x402_route_policy *policy,
                        const std::string &envelope_xdr_b64,
                        char *tx_hash,
                        size_t tx_hash_size,
                        std::string *error)
{
  HttpResponse submit{};
  char hash_buffer[256];
  char status_buffer[64];

  submit = post_json(effective_rpc_url(policy),
                     json_rpc_wrap("sendTransaction",
                                   std::string("{\"transaction\":\"") + envelope_xdr_b64 + "\"}"),
                     policy->timeout_seconds,
                     "");
  if(submit.code != CURLE_OK || submit.status >= 400) {
    if(error != nullptr) {
      *error = "sendTransaction request failed";
    }
    return false;
  }
  if(x402_extract_json_string(submit.body.c_str(), "status", status_buffer, sizeof(status_buffer)) != X402_STATUS_OK) {
    if(error != nullptr) {
      *error = "sendTransaction did not return a status";
    }
    return false;
  }
  if(std::strcmp(status_buffer, "ERROR") == 0 ||
     std::strcmp(status_buffer, "TRY_AGAIN_LATER") == 0) {
    if(error != nullptr) {
      *error = submit.body;
    }
    return false;
  }
  if(x402_extract_json_string(submit.body.c_str(), "hash", hash_buffer, sizeof(hash_buffer)) != X402_STATUS_OK &&
     x402_extract_json_string(submit.body.c_str(), "txHash", hash_buffer, sizeof(hash_buffer)) != X402_STATUS_OK) {
    if(error != nullptr) {
      *error = "sendTransaction did not return a transaction hash";
    }
    return false;
  }

  std::snprintf(tx_hash, tx_hash_size, "%s", hash_buffer);
  return true;
}

bool confirm_transaction(const x402_route_policy *policy, const char *tx_hash, std::string *error)
{
  char status_buffer[64];
  auto deadline =
      std::chrono::steady_clock::now() + std::chrono::seconds(policy->timeout_seconds == 0 ? 30U : policy->timeout_seconds);

  if(tx_hash == nullptr || tx_hash[0] == '\0') {
    if(error != nullptr) {
      *error = "missing transaction hash";
    }
    return false;
  }

  while(std::chrono::steady_clock::now() < deadline) {
    HttpResponse query = post_json(effective_rpc_url(policy),
                                   json_rpc_wrap("getTransaction",
                                                 std::string("{\"hash\":\"") + tx_hash + "\"}"),
                                   policy->timeout_seconds,
                                   "");
    if(query.code == CURLE_OK && query.status < 400 &&
       x402_extract_json_string(query.body.c_str(), "status", status_buffer, sizeof(status_buffer)) == X402_STATUS_OK) {
      if(std::strcmp(status_buffer, "SUCCESS") == 0) {
        return true;
      }
      if(std::strcmp(status_buffer, "FAILED") == 0 ||
         std::strcmp(status_buffer, "ERROR") == 0) {
        if(error != nullptr) {
          *error = query.body;
        }
        return false;
      }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
  if(error != nullptr) {
    *error = "getTransaction polling timed out";
  }
  return false;
}

x402_stellar_local_backend select_local_backend(const x402_route_policy *policy)
{
  if(policy == nullptr) {
    return X402_STELLAR_BACKEND_INPROCESS;
  }
  if(policy->stellar_local_backend != X402_STELLAR_BACKEND_AUTO) {
    return policy->stellar_local_backend;
  }
  return X402_STELLAR_BACKEND_INPROCESS;
}

bool local_splitter_ready(const x402_route_policy *policy)
{
  x402_stellar_local_backend backend = select_local_backend(policy);

  return policy != nullptr &&
         policy->split_mode == X402_SPLIT_MULTI &&
         policy->stellar_config_dir[0] != '\0' &&
         policy->stellar_source_account[0] != '\0' &&
         backend == X402_STELLAR_BACKEND_INPROCESS;
}

sqlite3 *open_audit_db()
{
  sqlite3 *db = nullptr;

  if(sqlite3_open_v2(kAsyncSplitDbPath,
                     &db,
                     SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_FULLMUTEX,
                     nullptr) != SQLITE_OK) {
    sqlite3_close(db);
    return nullptr;
  }
  sqlite3_busy_timeout(db, 5000);
  sqlite3_exec(db,
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
               ");",
               nullptr,
               nullptr,
               nullptr);
  return db;
}

void append_async_split_trace(sqlite3 *db, const char *stage, const char *payment_id, const char *detail)
{
  sqlite3_stmt *stmt = nullptr;
  long long epoch_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                           std::chrono::system_clock::now().time_since_epoch())
                           .count();

  if(db == nullptr || stage == nullptr || stage[0] == '\0') {
    return;
  }
  if(sqlite3_prepare_v2(db,
                        "INSERT INTO async_split_trace "
                        "(payment_identifier, stage, detail, created_at_ms) "
                        "VALUES (?, ?, ?, ?);",
                        -1,
                        &stmt,
                        nullptr) == SQLITE_OK) {
    sqlite3_bind_text(stmt,
                      1,
                      payment_id == nullptr || payment_id[0] == '\0' ? "(none)" : payment_id,
                      -1,
                      SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, stage, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,
                      3,
                      detail == nullptr || detail[0] == '\0' ? "(none)" : detail,
                      -1,
                      SQLITE_TRANSIENT);
    sqlite3_bind_int64(stmt, 4, epoch_ms);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
  }
}

void log_async_split_syslog(const char *stage, const char *payment_id, const char *detail)
{
  if(stage == nullptr || stage[0] == '\0') {
    return;
  }
  openlog("mod_x402", LOG_PID | LOG_NDELAY, LOG_USER);
  syslog(LOG_NOTICE,
         "x402 async split stage=%s payment_id=%s detail=%s",
         stage,
         payment_id == nullptr || payment_id[0] == '\0' ? "(none)" : payment_id,
         detail == nullptr || detail[0] == '\0' ? "(none)" : detail);
  closelog();
}

long long epoch_ms_now()
{
  return std::chrono::duration_cast<std::chrono::milliseconds>(
             std::chrono::system_clock::now().time_since_epoch())
      .count();
}

void record_split_tx_audit(sqlite3 *db,
                           const char *payment_id,
                           const char *split_tx_hash,
                           const char *status,
                           const char *detail,
                           long long prepared_at_ms,
                           long long submitted_at_ms,
                           long long confirmed_at_ms)
{
  sqlite3_stmt *stmt = nullptr;

  if(db == nullptr || status == nullptr || status[0] == '\0') {
    return;
  }
  if(sqlite3_prepare_v2(
         db,
         "INSERT INTO split_tx_audit "
         "(payment_identifier, split_tx_hash, status, detail, prepared_at_ms, submitted_at_ms, "
         "confirmed_at_ms, updated_at_ms) "
         "VALUES (?, ?, ?, ?, ?, ?, ?, ?) "
         "ON CONFLICT(payment_identifier) DO UPDATE SET "
         "split_tx_hash=excluded.split_tx_hash, "
         "status=excluded.status, "
         "detail=excluded.detail, "
         "prepared_at_ms=COALESCE(excluded.prepared_at_ms, split_tx_audit.prepared_at_ms), "
         "submitted_at_ms=COALESCE(excluded.submitted_at_ms, split_tx_audit.submitted_at_ms), "
         "confirmed_at_ms=COALESCE(excluded.confirmed_at_ms, split_tx_audit.confirmed_at_ms), "
         "updated_at_ms=excluded.updated_at_ms;",
         -1,
         &stmt,
         nullptr) == SQLITE_OK) {
    long long now_ms = epoch_ms_now();
    sqlite3_bind_text(stmt,
                      1,
                      payment_id == nullptr || payment_id[0] == '\0' ? "(none)" : payment_id,
                      -1,
                      SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,
                      2,
                      split_tx_hash == nullptr || split_tx_hash[0] == '\0' ? "(none)" : split_tx_hash,
                      -1,
                      SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, status, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt,
                      4,
                      detail == nullptr || detail[0] == '\0' ? "(none)" : detail,
                      -1,
                      SQLITE_TRANSIENT);
    if(prepared_at_ms > 0) {
      sqlite3_bind_int64(stmt, 5, prepared_at_ms);
    }
    else {
      sqlite3_bind_null(stmt, 5);
    }
    if(submitted_at_ms > 0) {
      sqlite3_bind_int64(stmt, 6, submitted_at_ms);
    }
    else {
      sqlite3_bind_null(stmt, 6);
    }
    if(confirmed_at_ms > 0) {
      sqlite3_bind_int64(stmt, 7, confirmed_at_ms);
    }
    else {
      sqlite3_bind_null(stmt, 7);
    }
    sqlite3_bind_int64(stmt, 8, now_ms);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
  }
}

x402_status prepare_splitter_settle_balance(const x402_route_policy *policy,
                                            const x402_request_context *request,
                                            PreparedInprocessEnvelope *prepared,
                                            x402_settlement_result *result)
{
  x402_stellar_local_backend backend = select_local_backend(policy);
  std::string payment_id = derive_payment_id_hex(request, result);

  if(prepared == nullptr || result == nullptr) {
    return X402_STATUS_INVALID_ARGUMENT;
  }

  if(backend == X402_STELLAR_BACKEND_INPROCESS) {
    SignerMaterial signer{};
    stellar::SequenceNumber account_sequence = 0;
    stellar::InvokeHostFunctionOp invoke_op;
    std::string error;

    if(!load_secret_signer_material(policy, &signer, &error)) {
      result->status = X402_STATUS_SETTLE_ERROR;
      result->settled = 0;
      std::snprintf(result->error_code,
                    sizeof(result->error_code),
                    "%s",
                    "inprocess_identity_unavailable");
      std::snprintf(result->message,
                    sizeof(result->message),
                    "in-process Soroban backend could not load signer material: %s",
                    error.c_str());
      return result->status;
    }
    if(!fetch_account_sequence_rpc(policy, make_account_id(signer.public_key), &account_sequence, &error)) {
      result->status = X402_STATUS_SETTLE_ERROR;
      result->settled = 0;
      std::snprintf(result->error_code,
                    sizeof(result->error_code),
                    "%s",
                    "inprocess_sequence_unavailable");
      std::snprintf(result->message,
                    sizeof(result->message),
                    "in-process Soroban backend could not fetch account sequence: %s",
                    error.c_str());
      return result->status;
    }
    try {
      invoke_op = build_settle_balance_invoke(policy,
                                              payment_id,
                                              effective_payment_amount(policy, request));
    }
    catch(const std::exception &ex) {
      result->status = X402_STATUS_SETTLE_ERROR;
      result->settled = 0;
      std::snprintf(result->error_code,
                    sizeof(result->error_code),
                    "%s",
                    "inprocess_argument_error");
      std::snprintf(result->message,
                    sizeof(result->message),
                    "in-process Soroban backend could not build settle_balance arguments: %s",
                    ex.what());
      return result->status;
    }
    if(!build_signed_transaction_envelope(policy, signer, account_sequence, invoke_op, prepared, &error)) {
      result->status = X402_STATUS_SETTLE_ERROR;
      result->settled = 0;
      std::snprintf(result->error_code,
                    sizeof(result->error_code),
                    "%s",
                    "inprocess_assemble_failed");
      std::snprintf(result->message,
                    sizeof(result->message),
                    "in-process Soroban backend failed to build signed envelope: %s",
                    error.c_str());
      return result->status;
    }
    if(prepared->transaction_hash_hex.empty()) {
      result->status = X402_STATUS_SETTLE_ERROR;
      result->settled = 0;
      std::snprintf(result->error_code,
                    sizeof(result->error_code),
                    "%s",
                    "inprocess_hash_unavailable");
      std::snprintf(result->message,
                    sizeof(result->message),
                    "in-process Soroban backend could not compute split transaction hash");
      return result->status;
    }
    std::snprintf(result->split_transaction_hash,
                  sizeof(result->split_transaction_hash),
                  "%s",
                  prepared->transaction_hash_hex.c_str());
    std::snprintf(result->message, sizeof(result->message), "splitter transaction prepared");
    return X402_STATUS_OK;
  }
  result->status = X402_STATUS_SETTLE_ERROR;
  result->settled = 0;
  std::snprintf(result->error_code,
                sizeof(result->error_code),
                "%s",
                "inprocess_required");
  std::snprintf(result->message,
                sizeof(result->message),
                "stellar split settlement requires X402StellarLocalBackend inprocess");
  return result->status;
}

void dispatch_async_splitter_settle_balance(const x402_route_policy *policy,
                                            const x402_request_context *request,
                                            const x402_settlement_result *result,
                                            const PreparedInprocessEnvelope &prepared)
{
  x402_route_policy policy_copy{};
  x402_request_context request_copy{};
  x402_settlement_result result_copy{};
  PreparedInprocessEnvelope prepared_copy = prepared;

  if(policy == nullptr || request == nullptr || result == nullptr) {
    return;
  }

  std::memcpy(&policy_copy, policy, sizeof(policy_copy));
  std::memcpy(&request_copy, request, sizeof(request_copy));
  std::memcpy(&result_copy, result, sizeof(result_copy));
  {
    sqlite3 *db = open_audit_db();
    append_async_split_trace(db, "queued", request_copy.payment_identifier, result_copy.split_transaction_hash);
    log_async_split_syslog("queued", request_copy.payment_identifier, result_copy.split_transaction_hash);
    record_split_tx_audit(db,
                          request_copy.payment_identifier,
                          result_copy.split_transaction_hash,
                          "prepared",
                          "split transaction prepared before response release",
                          epoch_ms_now(),
                          0,
                          0);
    sqlite3_close(db);
  }

  try {
    std::thread([policy_copy, request_copy, result_copy, prepared_copy]() mutable {
      char submitted_hash[X402_MAX_TX_REF];
      std::string error;
      sqlite3 *db = open_audit_db();

      submitted_hash[0] = '\0';
      append_async_split_trace(db, "started", request_copy.payment_identifier, result_copy.split_transaction_hash);
      log_async_split_syslog("started",
                             request_copy.payment_identifier,
                             result_copy.split_transaction_hash);
      if(!submit_transaction(&policy_copy,
                             prepared_copy.envelope_xdr_b64,
                             submitted_hash,
                             sizeof(submitted_hash),
                             &error)) {
        std::string message = "splitter sendTransaction failed: ";
        message += truncate_for_log(error, 256);
        append_async_split_trace(db, "failed", request_copy.payment_identifier, message.c_str());
        log_async_split_syslog("failed", request_copy.payment_identifier, message.c_str());
        record_split_tx_audit(db,
                              request_copy.payment_identifier,
                              result_copy.split_transaction_hash,
                              "failed",
                              message.c_str(),
                              0,
                              0,
                              0);
        sqlite3_close(db);
        return;
      }
      if(result_copy.split_transaction_hash[0] != '\0' &&
         std::strcmp(submitted_hash, result_copy.split_transaction_hash) != 0) {
        std::string message = "split tx hash mismatch prepared=";
        message += result_copy.split_transaction_hash;
        message += " submitted=";
        message += submitted_hash;
        append_async_split_trace(db, "failed", request_copy.payment_identifier, message.c_str());
        log_async_split_syslog("failed", request_copy.payment_identifier, message.c_str());
        record_split_tx_audit(db,
                              request_copy.payment_identifier,
                              result_copy.split_transaction_hash,
                              "failed",
                              message.c_str(),
                              0,
                              epoch_ms_now(),
                              0);
        sqlite3_close(db);
        return;
      }
      record_split_tx_audit(db,
                            request_copy.payment_identifier,
                            result_copy.split_transaction_hash,
                            "submitted",
                            "split transaction submitted to soroban rpc",
                            0,
                            epoch_ms_now(),
                            0);
      append_async_split_trace(db, "submitted", request_copy.payment_identifier, result_copy.split_transaction_hash);
      log_async_split_syslog("submitted",
                             request_copy.payment_identifier,
                             result_copy.split_transaction_hash);
      if(!confirm_transaction(&policy_copy, submitted_hash, &error)) {
        std::string message = "splitter confirmation failed: ";
        message += truncate_for_log(error, 256);
        append_async_split_trace(db, "failed", request_copy.payment_identifier, message.c_str());
        log_async_split_syslog("failed", request_copy.payment_identifier, message.c_str());
        record_split_tx_audit(db,
                              request_copy.payment_identifier,
                              result_copy.split_transaction_hash,
                              "failed",
                              message.c_str(),
                              0,
                              0,
                              0);
        sqlite3_close(db);
        return;
      }
      append_async_split_trace(db, "completed", request_copy.payment_identifier, result_copy.split_transaction_hash);
      log_async_split_syslog("completed",
                             request_copy.payment_identifier,
                             result_copy.split_transaction_hash);
      record_split_tx_audit(db,
                            request_copy.payment_identifier,
                            result_copy.split_transaction_hash,
                            "confirmed",
                            "split transaction confirmed on stellar",
                            0,
                            0,
                            epoch_ms_now());
      sqlite3_close(db);
    }).detach();
  }
  catch(const std::exception &ex) {
    char message[512];
    std::snprintf(message,
                  sizeof(message),
                  "unable to dispatch async splitter settlement: %s payment_id=%s",
                  ex.what(),
                  request_copy.payment_identifier);
    sqlite3 *db = open_audit_db();
    append_async_split_trace(db, "dispatch-failed", request_copy.payment_identifier, message);
    log_async_split_syslog("dispatch-failed", request_copy.payment_identifier, message);
    record_split_tx_audit(db,
                          request_copy.payment_identifier,
                          result_copy.split_transaction_hash,
                          "failed",
                          message,
                          0,
                          0,
                          0);
    sqlite3_close(db);
  }
}

} // namespace

namespace xdr {

std::uint32_t marshaling_stack_limit = 0xffffffffU;

void marshal_base::get_bytes(const std::uint32_t *&pr, void *buf, std::size_t len)
{
  const unsigned char *source = reinterpret_cast<const unsigned char *>(pr);
  unsigned char *target = reinterpret_cast<unsigned char *>(buf);
  std::size_t padded = (len + 3U) & ~std::size_t(3U);

  if(len != 0) {
    std::memcpy(target, source, len);
  }
  for(std::size_t i = len; i < padded; ++i) {
    if(source[i] != 0U) {
      throw xdr::xdr_should_be_zero("non-zero XDR padding");
    }
  }
  pr += padded / 4U;
}

void marshal_base::put_bytes(std::uint32_t *&pr, const void *buf, std::size_t len)
{
  unsigned char *target = reinterpret_cast<unsigned char *>(pr);
  const unsigned char *source = reinterpret_cast<const unsigned char *>(buf);
  std::size_t padded = (len + 3U) & ~std::size_t(3U);

  if(len != 0) {
    std::memcpy(target, source, len);
  }
  if(padded > len) {
    std::fill(target + len, target + padded, 0U);
  }
  pr += padded / 4U;
}

} // namespace xdr

static x402_status stellar_describe_capabilities(x402_provider_capabilities *caps)
{
  if(caps == nullptr) {
    return X402_STATUS_INVALID_ARGUMENT;
  }

  std::memset(caps, 0, sizeof(*caps));
  caps->supports_local_verify = 1;
  caps->supports_local_settle = 1;
  caps->supports_facilitator = 1;
  caps->supports_multi_stakeholder = 1;
  caps->supports_prepaid = 1;
  caps->derives_payer_identity = 1;
  return X402_STATUS_OK;
}

static x402_status stellar_declare_requirements(const x402_route_policy *policy,
                                                const x402_request_context *request,
                                                x402_payment_requirements *requirements)
{
  if(policy == nullptr || requirements == nullptr) {
    return X402_STATUS_INVALID_ARGUMENT;
  }

  std::memset(requirements, 0, sizeof(*requirements));
  requirements->amount = effective_payment_amount(policy, request);
  requirements->timeout_seconds = policy->timeout_seconds == 0 ? 30 : policy->timeout_seconds;
  requirements->prepaid_supported = policy->credits.enabled;
  requirements->max_multiplier = policy->credits.max_multiplier;

  if(policy->split_mode == X402_SPLIT_MULTI) {
    std::snprintf(requirements->pay_to,
                  sizeof(requirements->pay_to),
                  "%s",
                  policy->splitter_contract);
    std::snprintf(requirements->settlement_target,
                  sizeof(requirements->settlement_target),
                  "%s",
                  policy->splitter_contract);
  }
  else {
    std::snprintf(requirements->pay_to, sizeof(requirements->pay_to), "%s", policy->pay_to);
    std::snprintf(requirements->settlement_target,
                  sizeof(requirements->settlement_target),
                  "%s",
                  policy->pay_to);
  }

  return X402_STATUS_OK;
}

static x402_status stellar_verify(const x402_route_policy *policy,
                                  const x402_request_context *request,
                                  const char *payment_payload,
                                  x402_verification_result *result)
{
  std::string requirements_json;
  std::string request_body;
  HttpResponse http{};

  if(policy == nullptr || request == nullptr || payment_payload == nullptr || result == nullptr) {
    return X402_STATUS_INVALID_ARGUMENT;
  }

  std::memset(result, 0, sizeof(*result));

  if(use_facilitator(policy)) {
    build_requirements_json(policy, request, &requirements_json);
    request_body = "{\"x402Version\":2,\"paymentPayload\":";
    request_body += payment_payload;
    request_body += ",\"paymentRequirements\":";
    request_body += requirements_json;
    request_body += "}";

    {
      std::string verify_url = append_endpoint(policy->facilitator_url, "/verify");
      http = post_json(verify_url.c_str(),
                       request_body,
                       policy->timeout_seconds,
                       policy->facilitator_api_key);
    }
    if(http.code != CURLE_OK || http.status >= 400) {
      result->status = X402_STATUS_VERIFY_ERROR;
      map_http_error(http,
                     result->status,
                     "facilitator_verify_failed",
                     "facilitator verify request failed",
                     result->error_code,
                     sizeof(result->error_code),
                     result->message,
                     sizeof(result->message));
      copy_if_present(x402_extract_json_string,
                      http.body.c_str(),
                      "invalidReason",
                      result->error_code,
                      sizeof(result->error_code));
      copy_if_present(x402_extract_json_string,
                      http.body.c_str(),
                      "invalidMessage",
                      result->message,
                      sizeof(result->message));
      return result->status;
    }

    result->status = X402_STATUS_OK;
    result->accepted = json_true_for_key(http.body.c_str(), "accepted") ||
                       json_true_for_key(http.body.c_str(), "isValid") ||
                       json_true_for_key(http.body.c_str(), "success");
    uint32_t amount_received = 0;
    x402_extract_json_uint32(http.body.c_str(), "amount", &amount_received);
    result->amount_received = amount_received;
    copy_if_present(x402_extract_json_string,
                    http.body.c_str(),
                    "payer",
                    result->payer,
                    sizeof(result->payer));
    copy_if_present(x402_extract_json_string,
                    http.body.c_str(),
                    "transaction",
                    result->transaction_ref,
                    sizeof(result->transaction_ref));
    copy_if_present(x402_extract_json_string,
                    http.body.c_str(),
                    "code",
                    result->error_code,
                    sizeof(result->error_code));
    copy_if_present(x402_extract_json_string,
                    http.body.c_str(),
                    "message",
                    result->message,
                    sizeof(result->message));
    if(!result->accepted && result->message[0] == '\0') {
      copy_if_present(x402_extract_json_string,
                      http.body.c_str(),
                      "invalidReason",
                      result->message,
                      sizeof(result->message));
    }
    if(result->payer[0] == '\0') {
      std::snprintf(result->payer,
                    sizeof(result->payer),
                    "%s",
                    request->payer_hint[0] == '\0' ? "payer:unresolved" : request->payer_hint);
    }
    if(result->transaction_ref[0] == '\0') {
      std::snprintf(result->transaction_ref,
                    sizeof(result->transaction_ref),
                    "stellar:pending:%s",
                    request->payment_identifier[0] == '\0' ? "unknown" : request->payment_identifier);
    }
    if(!result->accepted && result->error_code[0] == '\0') {
      std::snprintf(result->error_code, sizeof(result->error_code), "%s", "invalid_payment");
    }
    if(!result->accepted && http.body.size() > 0) {
      std::snprintf(result->message,
                    sizeof(result->message),
                    "facilitator=%s",
                    truncate_for_log(http.body).c_str());
    }
    if(!result->accepted && result->message[0] == '\0') {
      std::snprintf(result->message, sizeof(result->message), "%s", "facilitator rejected payment");
    }
    return result->accepted ? X402_STATUS_OK : X402_STATUS_VERIFY_ERROR;
  }

  if(std::strstr(payment_payload, "\"network\":\"stellar:") == nullptr) {
    result->status = X402_STATUS_VERIFY_ERROR;
    std::snprintf(result->error_code, sizeof(result->error_code), "invalid_payment");
    std::snprintf(result->message, sizeof(result->message), "payload is not a Stellar payment");
    return result->status;
  }

  result->status = X402_STATUS_OK;
  result->accepted = 1;
  result->amount_received = effective_payment_amount(policy, request);
  std::snprintf(result->payer,
                sizeof(result->payer),
                "%s",
                request->payer_hint[0] == '\0' ? "payer:unresolved" : request->payer_hint);
  std::snprintf(result->transaction_ref,
                sizeof(result->transaction_ref),
                "stellar:pending:%s",
                request->payment_identifier[0] == '\0' ? "unknown" : request->payment_identifier);
  return result->status;
}

static x402_status stellar_settle(const x402_route_policy *policy,
                                  const x402_request_context *request,
                                  const char *payment_payload,
                                  x402_settlement_result *result)
{
  uint32_t multiplier;
  std::string requirements_json;
  std::string request_body;
  HttpResponse http{};
  PreparedInprocessEnvelope prepared_split{};

  if(policy == nullptr || request == nullptr || payment_payload == nullptr || result == nullptr) {
    return X402_STATUS_INVALID_ARGUMENT;
  }

  std::memset(result, 0, sizeof(*result));
  multiplier = effective_credit_count(policy, request);

  if(use_facilitator(policy)) {
    build_requirements_json(policy, request, &requirements_json);
    request_body = "{\"x402Version\":2,\"paymentPayload\":";
    request_body += payment_payload;
    request_body += ",\"paymentRequirements\":";
    request_body += requirements_json;
    request_body += "}";

    {
      std::string settle_url = append_endpoint(policy->facilitator_url, "/settle");
      http = post_json(settle_url.c_str(),
                       request_body,
                       policy->timeout_seconds,
                       policy->facilitator_api_key);
    }
    if(http.code != CURLE_OK || http.status >= 400) {
      result->status = X402_STATUS_SETTLE_ERROR;
      map_http_error(http,
                     result->status,
                     "facilitator_settle_failed",
                     "facilitator settle request failed",
                     result->error_code,
                     sizeof(result->error_code),
                     result->message,
                     sizeof(result->message));
      return result->status;
    }

    result->status = X402_STATUS_OK;
    result->settled = json_true_for_key(http.body.c_str(), "settled") ||
                      json_true_for_key(http.body.c_str(), "success");
    copy_if_present(x402_extract_json_string,
                    http.body.c_str(),
                    "payer",
                    result->payer,
                    sizeof(result->payer));
    copy_if_present(x402_extract_json_string,
                    http.body.c_str(),
                    "transaction",
                    result->transaction_ref,
                    sizeof(result->transaction_ref));
    copy_if_present(x402_extract_json_string,
                    http.body.c_str(),
                    "settlementMode",
                    result->settlement_mode,
                    sizeof(result->settlement_mode));
    copy_if_present(x402_extract_json_string,
                    http.body.c_str(),
                    "code",
                    result->error_code,
                    sizeof(result->error_code));
    copy_if_present(x402_extract_json_string,
                    http.body.c_str(),
                    "message",
                    result->message,
                    sizeof(result->message));
    x402_extract_json_uint32(http.body.c_str(), "creditsIssued", &result->credits_issued);
    x402_extract_json_uint32(http.body.c_str(), "creditsRemaining", &result->credits_remaining);

    if(result->payer[0] == '\0') {
      std::snprintf(result->payer,
                    sizeof(result->payer),
                    "%s",
                    request->payer_hint[0] == '\0' ? "payer:unresolved" : request->payer_hint);
    }
    if(result->transaction_ref[0] == '\0') {
      std::snprintf(result->transaction_ref,
                    sizeof(result->transaction_ref),
                    "stellar:settled:%s",
                    request->payment_identifier[0] == '\0' ? "unknown" : request->payment_identifier);
    }
    if(result->settlement_mode[0] == '\0') {
      std::snprintf(result->settlement_mode,
                    sizeof(result->settlement_mode),
                    "%s",
                    x402_settlement_mode_name(policy->settlement_mode));
    }
    if(result->credits_issued == 0) {
      result->credits_issued = multiplier;
    }
    if(result->credits_remaining == 0 && result->credits_issued > 0) {
      result->credits_remaining = result->credits_issued - 1U;
    }
    if(result->settled && policy->split_mode == X402_SPLIT_MULTI && local_splitter_ready(policy)) {
      x402_status split_prepare_status =
          prepare_splitter_settle_balance(policy, request, &prepared_split, result);
      if(split_prepare_status != X402_STATUS_OK) {
        result->settled = 0;
        return split_prepare_status;
      }
      dispatch_async_splitter_settle_balance(policy, request, result, prepared_split);
    }
    if(!result->settled && result->error_code[0] == '\0') {
      std::snprintf(result->error_code, sizeof(result->error_code), "%s", "settlement_failed");
    }
    if(!result->settled && result->message[0] == '\0') {
      std::snprintf(result->message, sizeof(result->message), "%s", "facilitator failed settlement");
    }
    if(!result->settled && http.body.size() > 0) {
      std::string message_prefix = result->message;
      std::snprintf(result->message,
                    sizeof(result->message),
                    "%s | facilitator=%s",
                    message_prefix.c_str(),
                    truncate_for_log(http.body).c_str());
    }
    return result->settled ? X402_STATUS_OK : X402_STATUS_SETTLE_ERROR;
  }

  if(policy->settlement_mode == X402_SETTLEMENT_LOCAL) {
    result->status = X402_STATUS_UNSUPPORTED;
    result->settled = 0;
    std::snprintf(result->error_code, sizeof(result->error_code), "local_settle_unavailable");
    std::snprintf(result->message,
                  sizeof(result->message),
                  "local Soroban assembly is not implemented in this workspace");
    return result->status;
  }

  if(std::strstr(payment_payload, "\"transaction\":") == nullptr) {
    result->status = X402_STATUS_SETTLE_ERROR;
    result->settled = 0;
    std::snprintf(result->error_code, sizeof(result->error_code), "invalid_payment");
    std::snprintf(result->message, sizeof(result->message), "transaction field is required");
    return result->status;
  }

  result->status = X402_STATUS_OK;
  result->settled = 1;
  result->credits_issued = multiplier;
  result->credits_remaining = multiplier > 0 ? multiplier - 1U : 0;
  std::snprintf(result->payer,
                sizeof(result->payer),
                "%s",
                request->payer_hint[0] == '\0' ? "payer:unresolved" : request->payer_hint);
  std::snprintf(result->transaction_ref,
                sizeof(result->transaction_ref),
                "stellar:settled:%s",
                request->payment_identifier[0] == '\0' ? "unknown" : request->payment_identifier);
  std::snprintf(result->settlement_mode,
                sizeof(result->settlement_mode),
                "%s",
                x402_settlement_mode_name(policy->settlement_mode));

  if(policy->split_mode == X402_SPLIT_MULTI) {
    if(local_splitter_ready(policy)) {
      x402_status split_prepare_status =
          prepare_splitter_settle_balance(policy, request, &prepared_split, result);
      if(split_prepare_status != X402_STATUS_OK) {
        result->settled = 0;
        return split_prepare_status;
      }
      dispatch_async_splitter_settle_balance(policy, request, result, prepared_split);
    }
    std::snprintf(result->message,
                  sizeof(result->message),
                  "settle via splitter contract %s",
                  policy->splitter_contract);
  }
  else {
    std::snprintf(result->message,
                  sizeof(result->message),
                  "settle direct to %s",
                  policy->pay_to);
  }

  return result->status;
}

extern "C" const x402_provider x402_stellar_provider = {
    "stellar",
    stellar_describe_capabilities,
    stellar_declare_requirements,
    stellar_verify,
    stellar_settle,
};
