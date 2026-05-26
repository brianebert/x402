// -*- C++ -*-
// Automatically generated from Stellar-transaction.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_TRANSACTION_H_INCLUDED__
#define __XDR_STELLAR_TRANSACTION_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-contract.h"
#include "xdr/Stellar-ledger-entries.h"

namespace stellar {

Constexpr const std::uint32_t MAX_OPS_PER_TX = 100;

struct LiquidityPoolParameters {
  using _xdr_case_type = xdr::xdr_traits<LiquidityPoolType>::case_type;
private:
  _xdr_case_type type_;
  union {
    LiquidityPoolConstantProductParameters constantProduct_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<LiquidityPoolType> &_xdr_case_values() {
    static const std::vector<LiquidityPoolType> _xdr_disc_vec {
      LIQUIDITY_POOL_CONSTANT_PRODUCT
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == LIQUIDITY_POOL_CONSTANT_PRODUCT ? 1
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case LIQUIDITY_POOL_CONSTANT_PRODUCT:
      _f(&LiquidityPoolParameters::constantProduct_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return type_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of type in LiquidityPoolParameters");
    if (fnum != _xdr_field_number(type_)) {
      this->~LiquidityPoolParameters();
      type_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
    }
    else
      type_ = which;
  }
  explicit LiquidityPoolParameters(LiquidityPoolType which = LiquidityPoolType{}) : type_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
  }
  LiquidityPoolParameters(const LiquidityPoolParameters &source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this, source);
  }
  LiquidityPoolParameters(LiquidityPoolParameters &&source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this,
                      std::move(source));
  }
  ~LiquidityPoolParameters() { _xdr_with_mem_ptr(xdr::field_destructor, type_, *this); }
  LiquidityPoolParameters &operator=(const LiquidityPoolParameters &source) {
    if (_xdr_field_number(type_)
        == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this, source);
    else {
      this->~LiquidityPoolParameters();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this, source);
    }
    type_ = source.type_;
    return *this;
  }
  LiquidityPoolParameters &operator=(LiquidityPoolParameters &&source) {
    if (_xdr_field_number(type_)
         == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this,
                        std::move(source));
    else {
      this->~LiquidityPoolParameters();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this,
                        std::move(source));
    }
    type_ = source.type_;
    return *this;
  }

  LiquidityPoolType type() const { return LiquidityPoolType(type_); }
  LiquidityPoolParameters &type(LiquidityPoolType _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  LiquidityPoolConstantProductParameters &constantProduct() {
    if (_xdr_field_number(type_) == 1)
      return constantProduct_;
    throw xdr::xdr_wrong_union("LiquidityPoolParameters: constantProduct accessed when not selected");
  }
  const LiquidityPoolConstantProductParameters &constantProduct() const {
    if (_xdr_field_number(type_) == 1)
      return constantProduct_;
    throw xdr::xdr_wrong_union("LiquidityPoolParameters: constantProduct accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::LiquidityPoolParameters> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::LiquidityPoolParameters;
  using case_type = ::stellar::LiquidityPoolParameters::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().type());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "constantProduct";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::LiquidityPoolParameters &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of type in LiquidityPoolParameters");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LiquidityPoolParameters &obj) {
    xdr::archive(ar, obj.type(), "type");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of type in LiquidityPoolParameters");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LiquidityPoolParameters &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "type");
    obj.type(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

struct MuxedAccount {
  struct _med25519_t {
    uint64 id{};
    uint256 ed25519{};

    _med25519_t() = default;
    template<typename _id_T,
             typename _ed25519_T,
             typename = typename
             std::enable_if<std::is_constructible<uint64, _id_T>::value
                            && std::is_constructible<uint256, _ed25519_T>::value
                           >::type>
    explicit _med25519_t(_id_T &&_id,
                         _ed25519_T &&_ed25519)
      : id(std::forward<_id_T>(_id)),
        ed25519(std::forward<_ed25519_T>(_ed25519)) {}
  };

  using _xdr_case_type = xdr::xdr_traits<CryptoKeyType>::case_type;
private:
  _xdr_case_type type_;
  union {
    uint256 ed25519_;
    _med25519_t med25519_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<CryptoKeyType> &_xdr_case_values() {
    static const std::vector<CryptoKeyType> _xdr_disc_vec {
      KEY_TYPE_ED25519,
      KEY_TYPE_MUXED_ED25519
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == KEY_TYPE_ED25519 ? 1
      : which == KEY_TYPE_MUXED_ED25519 ? 2
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case KEY_TYPE_ED25519:
      _f(&MuxedAccount::ed25519_, std::forward<_A>(_a)...);
      return true;
    case KEY_TYPE_MUXED_ED25519:
      _f(&MuxedAccount::med25519_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return type_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of type in MuxedAccount");
    if (fnum != _xdr_field_number(type_)) {
      this->~MuxedAccount();
      type_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
    }
    else
      type_ = which;
  }
  explicit MuxedAccount(CryptoKeyType which = CryptoKeyType{}) : type_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
  }
  MuxedAccount(const MuxedAccount &source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this, source);
  }
  MuxedAccount(MuxedAccount &&source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this,
                      std::move(source));
  }
  ~MuxedAccount() { _xdr_with_mem_ptr(xdr::field_destructor, type_, *this); }
  MuxedAccount &operator=(const MuxedAccount &source) {
    if (_xdr_field_number(type_)
        == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this, source);
    else {
      this->~MuxedAccount();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this, source);
    }
    type_ = source.type_;
    return *this;
  }
  MuxedAccount &operator=(MuxedAccount &&source) {
    if (_xdr_field_number(type_)
         == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this,
                        std::move(source));
    else {
      this->~MuxedAccount();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this,
                        std::move(source));
    }
    type_ = source.type_;
    return *this;
  }

  CryptoKeyType type() const { return CryptoKeyType(type_); }
  MuxedAccount &type(CryptoKeyType _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  uint256 &ed25519() {
    if (_xdr_field_number(type_) == 1)
      return ed25519_;
    throw xdr::xdr_wrong_union("MuxedAccount: ed25519 accessed when not selected");
  }
  const uint256 &ed25519() const {
    if (_xdr_field_number(type_) == 1)
      return ed25519_;
    throw xdr::xdr_wrong_union("MuxedAccount: ed25519 accessed when not selected");
  }
  _med25519_t &med25519() {
    if (_xdr_field_number(type_) == 2)
      return med25519_;
    throw xdr::xdr_wrong_union("MuxedAccount: med25519 accessed when not selected");
  }
  const _med25519_t &med25519() const {
    if (_xdr_field_number(type_) == 2)
      return med25519_;
    throw xdr::xdr_wrong_union("MuxedAccount: med25519 accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::MuxedAccount::_med25519_t>
  : xdr_struct_base<field_ptr<::stellar::MuxedAccount::_med25519_t,
                              decltype(::stellar::MuxedAccount::_med25519_t::id),
                              &::stellar::MuxedAccount::_med25519_t::id>,
                    field_ptr<::stellar::MuxedAccount::_med25519_t,
                              decltype(::stellar::MuxedAccount::_med25519_t::ed25519),
                              &::stellar::MuxedAccount::_med25519_t::ed25519>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::MuxedAccount::_med25519_t &obj) {
    archive(ar, obj.id, "id");
    archive(ar, obj.ed25519, "ed25519");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::MuxedAccount::_med25519_t &obj) {
    archive(ar, obj.id, "id");
    archive(ar, obj.ed25519, "ed25519");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::MuxedAccount> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::MuxedAccount;
  using case_type = ::stellar::MuxedAccount::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().type());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "ed25519";
    case 2:
      return "med25519";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::MuxedAccount &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of type in MuxedAccount");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::MuxedAccount &obj) {
    xdr::archive(ar, obj.type(), "type");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of type in MuxedAccount");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::MuxedAccount &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "type");
    obj.type(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

struct DecoratedSignature {
  SignatureHint hint{};
  Signature signature{};

  DecoratedSignature() = default;
  template<typename _hint_T,
           typename _signature_T,
           typename = typename
           std::enable_if<std::is_constructible<SignatureHint, _hint_T>::value
                          && std::is_constructible<Signature, _signature_T>::value
                         >::type>
  explicit DecoratedSignature(_hint_T &&_hint,
                              _signature_T &&_signature)
    : hint(std::forward<_hint_T>(_hint)),
      signature(std::forward<_signature_T>(_signature)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::DecoratedSignature>
  : xdr_struct_base<field_ptr<::stellar::DecoratedSignature,
                              decltype(::stellar::DecoratedSignature::hint),
                              &::stellar::DecoratedSignature::hint>,
                    field_ptr<::stellar::DecoratedSignature,
                              decltype(::stellar::DecoratedSignature::signature),
                              &::stellar::DecoratedSignature::signature>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::DecoratedSignature &obj) {
    archive(ar, obj.hint, "hint");
    archive(ar, obj.signature, "signature");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::DecoratedSignature &obj) {
    archive(ar, obj.hint, "hint");
    archive(ar, obj.signature, "signature");
    xdr::validate(obj);
  }
};
} namespace stellar {

enum OperationType : std::int32_t {
  CREATE_ACCOUNT = 0,
  PAYMENT = 1,
  PATH_PAYMENT_STRICT_RECEIVE = 2,
  MANAGE_SELL_OFFER = 3,
  CREATE_PASSIVE_SELL_OFFER = 4,
  SET_OPTIONS = 5,
  CHANGE_TRUST = 6,
  ALLOW_TRUST = 7,
  ACCOUNT_MERGE = 8,
  INFLATION = 9,
  MANAGE_DATA = 10,
  BUMP_SEQUENCE = 11,
  MANAGE_BUY_OFFER = 12,
  PATH_PAYMENT_STRICT_SEND = 13,
  CREATE_CLAIMABLE_BALANCE = 14,
  CLAIM_CLAIMABLE_BALANCE = 15,
  BEGIN_SPONSORING_FUTURE_RESERVES = 16,
  END_SPONSORING_FUTURE_RESERVES = 17,
  REVOKE_SPONSORSHIP = 18,
  CLAWBACK = 19,
  CLAWBACK_CLAIMABLE_BALANCE = 20,
  SET_TRUST_LINE_FLAGS = 21,
  LIQUIDITY_POOL_DEPOSIT = 22,
  LIQUIDITY_POOL_WITHDRAW = 23,
  INVOKE_HOST_FUNCTION = 24,
  EXTEND_FOOTPRINT_TTL = 25,
  RESTORE_FOOTPRINT = 26,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::OperationType>
  : xdr_integral_base<::stellar::OperationType, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::OperationType val) {
    switch (val) {
    case ::stellar::CREATE_ACCOUNT:
      return "CREATE_ACCOUNT";
    case ::stellar::PAYMENT:
      return "PAYMENT";
    case ::stellar::PATH_PAYMENT_STRICT_RECEIVE:
      return "PATH_PAYMENT_STRICT_RECEIVE";
    case ::stellar::MANAGE_SELL_OFFER:
      return "MANAGE_SELL_OFFER";
    case ::stellar::CREATE_PASSIVE_SELL_OFFER:
      return "CREATE_PASSIVE_SELL_OFFER";
    case ::stellar::SET_OPTIONS:
      return "SET_OPTIONS";
    case ::stellar::CHANGE_TRUST:
      return "CHANGE_TRUST";
    case ::stellar::ALLOW_TRUST:
      return "ALLOW_TRUST";
    case ::stellar::ACCOUNT_MERGE:
      return "ACCOUNT_MERGE";
    case ::stellar::INFLATION:
      return "INFLATION";
    case ::stellar::MANAGE_DATA:
      return "MANAGE_DATA";
    case ::stellar::BUMP_SEQUENCE:
      return "BUMP_SEQUENCE";
    case ::stellar::MANAGE_BUY_OFFER:
      return "MANAGE_BUY_OFFER";
    case ::stellar::PATH_PAYMENT_STRICT_SEND:
      return "PATH_PAYMENT_STRICT_SEND";
    case ::stellar::CREATE_CLAIMABLE_BALANCE:
      return "CREATE_CLAIMABLE_BALANCE";
    case ::stellar::CLAIM_CLAIMABLE_BALANCE:
      return "CLAIM_CLAIMABLE_BALANCE";
    case ::stellar::BEGIN_SPONSORING_FUTURE_RESERVES:
      return "BEGIN_SPONSORING_FUTURE_RESERVES";
    case ::stellar::END_SPONSORING_FUTURE_RESERVES:
      return "END_SPONSORING_FUTURE_RESERVES";
    case ::stellar::REVOKE_SPONSORSHIP:
      return "REVOKE_SPONSORSHIP";
    case ::stellar::CLAWBACK:
      return "CLAWBACK";
    case ::stellar::CLAWBACK_CLAIMABLE_BALANCE:
      return "CLAWBACK_CLAIMABLE_BALANCE";
    case ::stellar::SET_TRUST_LINE_FLAGS:
      return "SET_TRUST_LINE_FLAGS";
    case ::stellar::LIQUIDITY_POOL_DEPOSIT:
      return "LIQUIDITY_POOL_DEPOSIT";
    case ::stellar::LIQUIDITY_POOL_WITHDRAW:
      return "LIQUIDITY_POOL_WITHDRAW";
    case ::stellar::INVOKE_HOST_FUNCTION:
      return "INVOKE_HOST_FUNCTION";
    case ::stellar::EXTEND_FOOTPRINT_TTL:
      return "EXTEND_FOOTPRINT_TTL";
    case ::stellar::RESTORE_FOOTPRINT:
      return "RESTORE_FOOTPRINT";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::CREATE_ACCOUNT,
      ::stellar::PAYMENT,
      ::stellar::PATH_PAYMENT_STRICT_RECEIVE,
      ::stellar::MANAGE_SELL_OFFER,
      ::stellar::CREATE_PASSIVE_SELL_OFFER,
      ::stellar::SET_OPTIONS,
      ::stellar::CHANGE_TRUST,
      ::stellar::ALLOW_TRUST,
      ::stellar::ACCOUNT_MERGE,
      ::stellar::INFLATION,
      ::stellar::MANAGE_DATA,
      ::stellar::BUMP_SEQUENCE,
      ::stellar::MANAGE_BUY_OFFER,
      ::stellar::PATH_PAYMENT_STRICT_SEND,
      ::stellar::CREATE_CLAIMABLE_BALANCE,
      ::stellar::CLAIM_CLAIMABLE_BALANCE,
      ::stellar::BEGIN_SPONSORING_FUTURE_RESERVES,
      ::stellar::END_SPONSORING_FUTURE_RESERVES,
      ::stellar::REVOKE_SPONSORSHIP,
      ::stellar::CLAWBACK,
      ::stellar::CLAWBACK_CLAIMABLE_BALANCE,
      ::stellar::SET_TRUST_LINE_FLAGS,
      ::stellar::LIQUIDITY_POOL_DEPOSIT,
      ::stellar::LIQUIDITY_POOL_WITHDRAW,
      ::stellar::INVOKE_HOST_FUNCTION,
      ::stellar::EXTEND_FOOTPRINT_TTL,
      ::stellar::RESTORE_FOOTPRINT
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct CreateAccountOp {
  AccountID destination{};
  int64 startingBalance{};

  CreateAccountOp() = default;
  template<typename _destination_T,
           typename _startingBalance_T,
           typename = typename
           std::enable_if<std::is_constructible<AccountID, _destination_T>::value
                          && std::is_constructible<int64, _startingBalance_T>::value
                         >::type>
  explicit CreateAccountOp(_destination_T &&_destination,
                           _startingBalance_T &&_startingBalance)
    : destination(std::forward<_destination_T>(_destination)),
      startingBalance(std::forward<_startingBalance_T>(_startingBalance)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateAccountOp>
  : xdr_struct_base<field_ptr<::stellar::CreateAccountOp,
                              decltype(::stellar::CreateAccountOp::destination),
                              &::stellar::CreateAccountOp::destination>,
                    field_ptr<::stellar::CreateAccountOp,
                              decltype(::stellar::CreateAccountOp::startingBalance),
                              &::stellar::CreateAccountOp::startingBalance>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateAccountOp &obj) {
    archive(ar, obj.destination, "destination");
    archive(ar, obj.startingBalance, "startingBalance");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateAccountOp &obj) {
    archive(ar, obj.destination, "destination");
    archive(ar, obj.startingBalance, "startingBalance");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct PaymentOp {
  MuxedAccount destination{};
  Asset asset{};
  int64 amount{};

  PaymentOp() = default;
  template<typename _destination_T,
           typename _asset_T,
           typename _amount_T,
           typename = typename
           std::enable_if<std::is_constructible<MuxedAccount, _destination_T>::value
                          && std::is_constructible<Asset, _asset_T>::value
                          && std::is_constructible<int64, _amount_T>::value
                         >::type>
  explicit PaymentOp(_destination_T &&_destination,
                     _asset_T &&_asset,
                     _amount_T &&_amount)
    : destination(std::forward<_destination_T>(_destination)),
      asset(std::forward<_asset_T>(_asset)),
      amount(std::forward<_amount_T>(_amount)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::PaymentOp>
  : xdr_struct_base<field_ptr<::stellar::PaymentOp,
                              decltype(::stellar::PaymentOp::destination),
                              &::stellar::PaymentOp::destination>,
                    field_ptr<::stellar::PaymentOp,
                              decltype(::stellar::PaymentOp::asset),
                              &::stellar::PaymentOp::asset>,
                    field_ptr<::stellar::PaymentOp,
                              decltype(::stellar::PaymentOp::amount),
                              &::stellar::PaymentOp::amount>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::PaymentOp &obj) {
    archive(ar, obj.destination, "destination");
    archive(ar, obj.asset, "asset");
    archive(ar, obj.amount, "amount");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::PaymentOp &obj) {
    archive(ar, obj.destination, "destination");
    archive(ar, obj.asset, "asset");
    archive(ar, obj.amount, "amount");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct PathPaymentStrictReceiveOp {
  Asset sendAsset{};
  int64 sendMax{};
  MuxedAccount destination{};
  Asset destAsset{};
  int64 destAmount{};
  xdr::xvector<Asset,5> path{};

  PathPaymentStrictReceiveOp() = default;
  template<typename _sendAsset_T,
           typename _sendMax_T,
           typename _destination_T,
           typename _destAsset_T,
           typename _destAmount_T,
           typename _path_T,
           typename = typename
           std::enable_if<std::is_constructible<Asset, _sendAsset_T>::value
                          && std::is_constructible<int64, _sendMax_T>::value
                          && std::is_constructible<MuxedAccount, _destination_T>::value
                          && std::is_constructible<Asset, _destAsset_T>::value
                          && std::is_constructible<int64, _destAmount_T>::value
                          && std::is_constructible<xdr::xvector<Asset,5>, _path_T>::value
                         >::type>
  explicit PathPaymentStrictReceiveOp(_sendAsset_T &&_sendAsset,
                                      _sendMax_T &&_sendMax,
                                      _destination_T &&_destination,
                                      _destAsset_T &&_destAsset,
                                      _destAmount_T &&_destAmount,
                                      _path_T &&_path)
    : sendAsset(std::forward<_sendAsset_T>(_sendAsset)),
      sendMax(std::forward<_sendMax_T>(_sendMax)),
      destination(std::forward<_destination_T>(_destination)),
      destAsset(std::forward<_destAsset_T>(_destAsset)),
      destAmount(std::forward<_destAmount_T>(_destAmount)),
      path(std::forward<_path_T>(_path)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::PathPaymentStrictReceiveOp>
  : xdr_struct_base<field_ptr<::stellar::PathPaymentStrictReceiveOp,
                              decltype(::stellar::PathPaymentStrictReceiveOp::sendAsset),
                              &::stellar::PathPaymentStrictReceiveOp::sendAsset>,
                    field_ptr<::stellar::PathPaymentStrictReceiveOp,
                              decltype(::stellar::PathPaymentStrictReceiveOp::sendMax),
                              &::stellar::PathPaymentStrictReceiveOp::sendMax>,
                    field_ptr<::stellar::PathPaymentStrictReceiveOp,
                              decltype(::stellar::PathPaymentStrictReceiveOp::destination),
                              &::stellar::PathPaymentStrictReceiveOp::destination>,
                    field_ptr<::stellar::PathPaymentStrictReceiveOp,
                              decltype(::stellar::PathPaymentStrictReceiveOp::destAsset),
                              &::stellar::PathPaymentStrictReceiveOp::destAsset>,
                    field_ptr<::stellar::PathPaymentStrictReceiveOp,
                              decltype(::stellar::PathPaymentStrictReceiveOp::destAmount),
                              &::stellar::PathPaymentStrictReceiveOp::destAmount>,
                    field_ptr<::stellar::PathPaymentStrictReceiveOp,
                              decltype(::stellar::PathPaymentStrictReceiveOp::path),
                              &::stellar::PathPaymentStrictReceiveOp::path>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::PathPaymentStrictReceiveOp &obj) {
    archive(ar, obj.sendAsset, "sendAsset");
    archive(ar, obj.sendMax, "sendMax");
    archive(ar, obj.destination, "destination");
    archive(ar, obj.destAsset, "destAsset");
    archive(ar, obj.destAmount, "destAmount");
    archive(ar, obj.path, "path");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::PathPaymentStrictReceiveOp &obj) {
    archive(ar, obj.sendAsset, "sendAsset");
    archive(ar, obj.sendMax, "sendMax");
    archive(ar, obj.destination, "destination");
    archive(ar, obj.destAsset, "destAsset");
    archive(ar, obj.destAmount, "destAmount");
    archive(ar, obj.path, "path");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct PathPaymentStrictSendOp {
  Asset sendAsset{};
  int64 sendAmount{};
  MuxedAccount destination{};
  Asset destAsset{};
  int64 destMin{};
  xdr::xvector<Asset,5> path{};

  PathPaymentStrictSendOp() = default;
  template<typename _sendAsset_T,
           typename _sendAmount_T,
           typename _destination_T,
           typename _destAsset_T,
           typename _destMin_T,
           typename _path_T,
           typename = typename
           std::enable_if<std::is_constructible<Asset, _sendAsset_T>::value
                          && std::is_constructible<int64, _sendAmount_T>::value
                          && std::is_constructible<MuxedAccount, _destination_T>::value
                          && std::is_constructible<Asset, _destAsset_T>::value
                          && std::is_constructible<int64, _destMin_T>::value
                          && std::is_constructible<xdr::xvector<Asset,5>, _path_T>::value
                         >::type>
  explicit PathPaymentStrictSendOp(_sendAsset_T &&_sendAsset,
                                   _sendAmount_T &&_sendAmount,
                                   _destination_T &&_destination,
                                   _destAsset_T &&_destAsset,
                                   _destMin_T &&_destMin,
                                   _path_T &&_path)
    : sendAsset(std::forward<_sendAsset_T>(_sendAsset)),
      sendAmount(std::forward<_sendAmount_T>(_sendAmount)),
      destination(std::forward<_destination_T>(_destination)),
      destAsset(std::forward<_destAsset_T>(_destAsset)),
      destMin(std::forward<_destMin_T>(_destMin)),
      path(std::forward<_path_T>(_path)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::PathPaymentStrictSendOp>
  : xdr_struct_base<field_ptr<::stellar::PathPaymentStrictSendOp,
                              decltype(::stellar::PathPaymentStrictSendOp::sendAsset),
                              &::stellar::PathPaymentStrictSendOp::sendAsset>,
                    field_ptr<::stellar::PathPaymentStrictSendOp,
                              decltype(::stellar::PathPaymentStrictSendOp::sendAmount),
                              &::stellar::PathPaymentStrictSendOp::sendAmount>,
                    field_ptr<::stellar::PathPaymentStrictSendOp,
                              decltype(::stellar::PathPaymentStrictSendOp::destination),
                              &::stellar::PathPaymentStrictSendOp::destination>,
                    field_ptr<::stellar::PathPaymentStrictSendOp,
                              decltype(::stellar::PathPaymentStrictSendOp::destAsset),
                              &::stellar::PathPaymentStrictSendOp::destAsset>,
                    field_ptr<::stellar::PathPaymentStrictSendOp,
                              decltype(::stellar::PathPaymentStrictSendOp::destMin),
                              &::stellar::PathPaymentStrictSendOp::destMin>,
                    field_ptr<::stellar::PathPaymentStrictSendOp,
                              decltype(::stellar::PathPaymentStrictSendOp::path),
                              &::stellar::PathPaymentStrictSendOp::path>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::PathPaymentStrictSendOp &obj) {
    archive(ar, obj.sendAsset, "sendAsset");
    archive(ar, obj.sendAmount, "sendAmount");
    archive(ar, obj.destination, "destination");
    archive(ar, obj.destAsset, "destAsset");
    archive(ar, obj.destMin, "destMin");
    archive(ar, obj.path, "path");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::PathPaymentStrictSendOp &obj) {
    archive(ar, obj.sendAsset, "sendAsset");
    archive(ar, obj.sendAmount, "sendAmount");
    archive(ar, obj.destination, "destination");
    archive(ar, obj.destAsset, "destAsset");
    archive(ar, obj.destMin, "destMin");
    archive(ar, obj.path, "path");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ManageSellOfferOp {
  Asset selling{};
  Asset buying{};
  int64 amount{};
  Price price{};
  int64 offerID{};

  ManageSellOfferOp() = default;
  template<typename _selling_T,
           typename _buying_T,
           typename _amount_T,
           typename _price_T,
           typename _offerID_T,
           typename = typename
           std::enable_if<std::is_constructible<Asset, _selling_T>::value
                          && std::is_constructible<Asset, _buying_T>::value
                          && std::is_constructible<int64, _amount_T>::value
                          && std::is_constructible<Price, _price_T>::value
                          && std::is_constructible<int64, _offerID_T>::value
                         >::type>
  explicit ManageSellOfferOp(_selling_T &&_selling,
                             _buying_T &&_buying,
                             _amount_T &&_amount,
                             _price_T &&_price,
                             _offerID_T &&_offerID)
    : selling(std::forward<_selling_T>(_selling)),
      buying(std::forward<_buying_T>(_buying)),
      amount(std::forward<_amount_T>(_amount)),
      price(std::forward<_price_T>(_price)),
      offerID(std::forward<_offerID_T>(_offerID)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageSellOfferOp>
  : xdr_struct_base<field_ptr<::stellar::ManageSellOfferOp,
                              decltype(::stellar::ManageSellOfferOp::selling),
                              &::stellar::ManageSellOfferOp::selling>,
                    field_ptr<::stellar::ManageSellOfferOp,
                              decltype(::stellar::ManageSellOfferOp::buying),
                              &::stellar::ManageSellOfferOp::buying>,
                    field_ptr<::stellar::ManageSellOfferOp,
                              decltype(::stellar::ManageSellOfferOp::amount),
                              &::stellar::ManageSellOfferOp::amount>,
                    field_ptr<::stellar::ManageSellOfferOp,
                              decltype(::stellar::ManageSellOfferOp::price),
                              &::stellar::ManageSellOfferOp::price>,
                    field_ptr<::stellar::ManageSellOfferOp,
                              decltype(::stellar::ManageSellOfferOp::offerID),
                              &::stellar::ManageSellOfferOp::offerID>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageSellOfferOp &obj) {
    archive(ar, obj.selling, "selling");
    archive(ar, obj.buying, "buying");
    archive(ar, obj.amount, "amount");
    archive(ar, obj.price, "price");
    archive(ar, obj.offerID, "offerID");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageSellOfferOp &obj) {
    archive(ar, obj.selling, "selling");
    archive(ar, obj.buying, "buying");
    archive(ar, obj.amount, "amount");
    archive(ar, obj.price, "price");
    archive(ar, obj.offerID, "offerID");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ManageBuyOfferOp {
  Asset selling{};
  Asset buying{};
  int64 buyAmount{};
  Price price{};
  int64 offerID{};

  ManageBuyOfferOp() = default;
  template<typename _selling_T,
           typename _buying_T,
           typename _buyAmount_T,
           typename _price_T,
           typename _offerID_T,
           typename = typename
           std::enable_if<std::is_constructible<Asset, _selling_T>::value
                          && std::is_constructible<Asset, _buying_T>::value
                          && std::is_constructible<int64, _buyAmount_T>::value
                          && std::is_constructible<Price, _price_T>::value
                          && std::is_constructible<int64, _offerID_T>::value
                         >::type>
  explicit ManageBuyOfferOp(_selling_T &&_selling,
                            _buying_T &&_buying,
                            _buyAmount_T &&_buyAmount,
                            _price_T &&_price,
                            _offerID_T &&_offerID)
    : selling(std::forward<_selling_T>(_selling)),
      buying(std::forward<_buying_T>(_buying)),
      buyAmount(std::forward<_buyAmount_T>(_buyAmount)),
      price(std::forward<_price_T>(_price)),
      offerID(std::forward<_offerID_T>(_offerID)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageBuyOfferOp>
  : xdr_struct_base<field_ptr<::stellar::ManageBuyOfferOp,
                              decltype(::stellar::ManageBuyOfferOp::selling),
                              &::stellar::ManageBuyOfferOp::selling>,
                    field_ptr<::stellar::ManageBuyOfferOp,
                              decltype(::stellar::ManageBuyOfferOp::buying),
                              &::stellar::ManageBuyOfferOp::buying>,
                    field_ptr<::stellar::ManageBuyOfferOp,
                              decltype(::stellar::ManageBuyOfferOp::buyAmount),
                              &::stellar::ManageBuyOfferOp::buyAmount>,
                    field_ptr<::stellar::ManageBuyOfferOp,
                              decltype(::stellar::ManageBuyOfferOp::price),
                              &::stellar::ManageBuyOfferOp::price>,
                    field_ptr<::stellar::ManageBuyOfferOp,
                              decltype(::stellar::ManageBuyOfferOp::offerID),
                              &::stellar::ManageBuyOfferOp::offerID>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageBuyOfferOp &obj) {
    archive(ar, obj.selling, "selling");
    archive(ar, obj.buying, "buying");
    archive(ar, obj.buyAmount, "buyAmount");
    archive(ar, obj.price, "price");
    archive(ar, obj.offerID, "offerID");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageBuyOfferOp &obj) {
    archive(ar, obj.selling, "selling");
    archive(ar, obj.buying, "buying");
    archive(ar, obj.buyAmount, "buyAmount");
    archive(ar, obj.price, "price");
    archive(ar, obj.offerID, "offerID");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct CreatePassiveSellOfferOp {
  Asset selling{};
  Asset buying{};
  int64 amount{};
  Price price{};

  CreatePassiveSellOfferOp() = default;
  template<typename _selling_T,
           typename _buying_T,
           typename _amount_T,
           typename _price_T,
           typename = typename
           std::enable_if<std::is_constructible<Asset, _selling_T>::value
                          && std::is_constructible<Asset, _buying_T>::value
                          && std::is_constructible<int64, _amount_T>::value
                          && std::is_constructible<Price, _price_T>::value
                         >::type>
  explicit CreatePassiveSellOfferOp(_selling_T &&_selling,
                                    _buying_T &&_buying,
                                    _amount_T &&_amount,
                                    _price_T &&_price)
    : selling(std::forward<_selling_T>(_selling)),
      buying(std::forward<_buying_T>(_buying)),
      amount(std::forward<_amount_T>(_amount)),
      price(std::forward<_price_T>(_price)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreatePassiveSellOfferOp>
  : xdr_struct_base<field_ptr<::stellar::CreatePassiveSellOfferOp,
                              decltype(::stellar::CreatePassiveSellOfferOp::selling),
                              &::stellar::CreatePassiveSellOfferOp::selling>,
                    field_ptr<::stellar::CreatePassiveSellOfferOp,
                              decltype(::stellar::CreatePassiveSellOfferOp::buying),
                              &::stellar::CreatePassiveSellOfferOp::buying>,
                    field_ptr<::stellar::CreatePassiveSellOfferOp,
                              decltype(::stellar::CreatePassiveSellOfferOp::amount),
                              &::stellar::CreatePassiveSellOfferOp::amount>,
                    field_ptr<::stellar::CreatePassiveSellOfferOp,
                              decltype(::stellar::CreatePassiveSellOfferOp::price),
                              &::stellar::CreatePassiveSellOfferOp::price>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreatePassiveSellOfferOp &obj) {
    archive(ar, obj.selling, "selling");
    archive(ar, obj.buying, "buying");
    archive(ar, obj.amount, "amount");
    archive(ar, obj.price, "price");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreatePassiveSellOfferOp &obj) {
    archive(ar, obj.selling, "selling");
    archive(ar, obj.buying, "buying");
    archive(ar, obj.amount, "amount");
    archive(ar, obj.price, "price");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct SetOptionsOp {
  xdr::pointer<AccountID> inflationDest{};
  xdr::pointer<uint32> clearFlags{};
  xdr::pointer<uint32> setFlags{};
  xdr::pointer<uint32> masterWeight{};
  xdr::pointer<uint32> lowThreshold{};
  xdr::pointer<uint32> medThreshold{};
  xdr::pointer<uint32> highThreshold{};
  xdr::pointer<string32> homeDomain{};
  xdr::pointer<Signer> signer{};

  SetOptionsOp() = default;
  template<typename _inflationDest_T,
           typename _clearFlags_T,
           typename _setFlags_T,
           typename _masterWeight_T,
           typename _lowThreshold_T,
           typename _medThreshold_T,
           typename _highThreshold_T,
           typename _homeDomain_T,
           typename _signer_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::pointer<AccountID>, _inflationDest_T>::value
                          && std::is_constructible<xdr::pointer<uint32>, _clearFlags_T>::value
                          && std::is_constructible<xdr::pointer<uint32>, _setFlags_T>::value
                          && std::is_constructible<xdr::pointer<uint32>, _masterWeight_T>::value
                          && std::is_constructible<xdr::pointer<uint32>, _lowThreshold_T>::value
                          && std::is_constructible<xdr::pointer<uint32>, _medThreshold_T>::value
                          && std::is_constructible<xdr::pointer<uint32>, _highThreshold_T>::value
                          && std::is_constructible<xdr::pointer<string32>, _homeDomain_T>::value
                          && std::is_constructible<xdr::pointer<Signer>, _signer_T>::value
                         >::type>
  explicit SetOptionsOp(_inflationDest_T &&_inflationDest,
                        _clearFlags_T &&_clearFlags,
                        _setFlags_T &&_setFlags,
                        _masterWeight_T &&_masterWeight,
                        _lowThreshold_T &&_lowThreshold,
                        _medThreshold_T &&_medThreshold,
                        _highThreshold_T &&_highThreshold,
                        _homeDomain_T &&_homeDomain,
                        _signer_T &&_signer)
    : inflationDest(std::forward<_inflationDest_T>(_inflationDest)),
      clearFlags(std::forward<_clearFlags_T>(_clearFlags)),
      setFlags(std::forward<_setFlags_T>(_setFlags)),
      masterWeight(std::forward<_masterWeight_T>(_masterWeight)),
      lowThreshold(std::forward<_lowThreshold_T>(_lowThreshold)),
      medThreshold(std::forward<_medThreshold_T>(_medThreshold)),
      highThreshold(std::forward<_highThreshold_T>(_highThreshold)),
      homeDomain(std::forward<_homeDomain_T>(_homeDomain)),
      signer(std::forward<_signer_T>(_signer)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SetOptionsOp>
  : xdr_struct_base<field_ptr<::stellar::SetOptionsOp,
                              decltype(::stellar::SetOptionsOp::inflationDest),
                              &::stellar::SetOptionsOp::inflationDest>,
                    field_ptr<::stellar::SetOptionsOp,
                              decltype(::stellar::SetOptionsOp::clearFlags),
                              &::stellar::SetOptionsOp::clearFlags>,
                    field_ptr<::stellar::SetOptionsOp,
                              decltype(::stellar::SetOptionsOp::setFlags),
                              &::stellar::SetOptionsOp::setFlags>,
                    field_ptr<::stellar::SetOptionsOp,
                              decltype(::stellar::SetOptionsOp::masterWeight),
                              &::stellar::SetOptionsOp::masterWeight>,
                    field_ptr<::stellar::SetOptionsOp,
                              decltype(::stellar::SetOptionsOp::lowThreshold),
                              &::stellar::SetOptionsOp::lowThreshold>,
                    field_ptr<::stellar::SetOptionsOp,
                              decltype(::stellar::SetOptionsOp::medThreshold),
                              &::stellar::SetOptionsOp::medThreshold>,
                    field_ptr<::stellar::SetOptionsOp,
                              decltype(::stellar::SetOptionsOp::highThreshold),
                              &::stellar::SetOptionsOp::highThreshold>,
                    field_ptr<::stellar::SetOptionsOp,
                              decltype(::stellar::SetOptionsOp::homeDomain),
                              &::stellar::SetOptionsOp::homeDomain>,
                    field_ptr<::stellar::SetOptionsOp,
                              decltype(::stellar::SetOptionsOp::signer),
                              &::stellar::SetOptionsOp::signer>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SetOptionsOp &obj) {
    archive(ar, obj.inflationDest, "inflationDest");
    archive(ar, obj.clearFlags, "clearFlags");
    archive(ar, obj.setFlags, "setFlags");
    archive(ar, obj.masterWeight, "masterWeight");
    archive(ar, obj.lowThreshold, "lowThreshold");
    archive(ar, obj.medThreshold, "medThreshold");
    archive(ar, obj.highThreshold, "highThreshold");
    archive(ar, obj.homeDomain, "homeDomain");
    archive(ar, obj.signer, "signer");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SetOptionsOp &obj) {
    archive(ar, obj.inflationDest, "inflationDest");
    archive(ar, obj.clearFlags, "clearFlags");
    archive(ar, obj.setFlags, "setFlags");
    archive(ar, obj.masterWeight, "masterWeight");
    archive(ar, obj.lowThreshold, "lowThreshold");
    archive(ar, obj.medThreshold, "medThreshold");
    archive(ar, obj.highThreshold, "highThreshold");
    archive(ar, obj.homeDomain, "homeDomain");
    archive(ar, obj.signer, "signer");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ChangeTrustAsset {
  using _xdr_case_type = xdr::xdr_traits<AssetType>::case_type;
private:
  _xdr_case_type type_;
  union {
    AlphaNum4 alphaNum4_;
    AlphaNum12 alphaNum12_;
    LiquidityPoolParameters liquidityPool_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<AssetType> &_xdr_case_values() {
    static const std::vector<AssetType> _xdr_disc_vec {
      ASSET_TYPE_NATIVE,
      ASSET_TYPE_CREDIT_ALPHANUM4,
      ASSET_TYPE_CREDIT_ALPHANUM12,
      ASSET_TYPE_POOL_SHARE
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == ASSET_TYPE_NATIVE ? 0
      : which == ASSET_TYPE_CREDIT_ALPHANUM4 ? 1
      : which == ASSET_TYPE_CREDIT_ALPHANUM12 ? 2
      : which == ASSET_TYPE_POOL_SHARE ? 3
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case ASSET_TYPE_NATIVE:
      return true;
    case ASSET_TYPE_CREDIT_ALPHANUM4:
      _f(&ChangeTrustAsset::alphaNum4_, std::forward<_A>(_a)...);
      return true;
    case ASSET_TYPE_CREDIT_ALPHANUM12:
      _f(&ChangeTrustAsset::alphaNum12_, std::forward<_A>(_a)...);
      return true;
    case ASSET_TYPE_POOL_SHARE:
      _f(&ChangeTrustAsset::liquidityPool_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return type_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of type in ChangeTrustAsset");
    if (fnum != _xdr_field_number(type_)) {
      this->~ChangeTrustAsset();
      type_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
    }
    else
      type_ = which;
  }
  explicit ChangeTrustAsset(AssetType which = AssetType{}) : type_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
  }
  ChangeTrustAsset(const ChangeTrustAsset &source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this, source);
  }
  ChangeTrustAsset(ChangeTrustAsset &&source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this,
                      std::move(source));
  }
  ~ChangeTrustAsset() { _xdr_with_mem_ptr(xdr::field_destructor, type_, *this); }
  ChangeTrustAsset &operator=(const ChangeTrustAsset &source) {
    if (_xdr_field_number(type_)
        == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this, source);
    else {
      this->~ChangeTrustAsset();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this, source);
    }
    type_ = source.type_;
    return *this;
  }
  ChangeTrustAsset &operator=(ChangeTrustAsset &&source) {
    if (_xdr_field_number(type_)
         == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this,
                        std::move(source));
    else {
      this->~ChangeTrustAsset();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this,
                        std::move(source));
    }
    type_ = source.type_;
    return *this;
  }

  AssetType type() const { return AssetType(type_); }
  ChangeTrustAsset &type(AssetType _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  AlphaNum4 &alphaNum4() {
    if (_xdr_field_number(type_) == 1)
      return alphaNum4_;
    throw xdr::xdr_wrong_union("ChangeTrustAsset: alphaNum4 accessed when not selected");
  }
  const AlphaNum4 &alphaNum4() const {
    if (_xdr_field_number(type_) == 1)
      return alphaNum4_;
    throw xdr::xdr_wrong_union("ChangeTrustAsset: alphaNum4 accessed when not selected");
  }
  AlphaNum12 &alphaNum12() {
    if (_xdr_field_number(type_) == 2)
      return alphaNum12_;
    throw xdr::xdr_wrong_union("ChangeTrustAsset: alphaNum12 accessed when not selected");
  }
  const AlphaNum12 &alphaNum12() const {
    if (_xdr_field_number(type_) == 2)
      return alphaNum12_;
    throw xdr::xdr_wrong_union("ChangeTrustAsset: alphaNum12 accessed when not selected");
  }
  LiquidityPoolParameters &liquidityPool() {
    if (_xdr_field_number(type_) == 3)
      return liquidityPool_;
    throw xdr::xdr_wrong_union("ChangeTrustAsset: liquidityPool accessed when not selected");
  }
  const LiquidityPoolParameters &liquidityPool() const {
    if (_xdr_field_number(type_) == 3)
      return liquidityPool_;
    throw xdr::xdr_wrong_union("ChangeTrustAsset: liquidityPool accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ChangeTrustAsset> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ChangeTrustAsset;
  using case_type = ::stellar::ChangeTrustAsset::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().type());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "alphaNum4";
    case 2:
      return "alphaNum12";
    case 3:
      return "liquidityPool";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ChangeTrustAsset &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of type in ChangeTrustAsset");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ChangeTrustAsset &obj) {
    xdr::archive(ar, obj.type(), "type");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of type in ChangeTrustAsset");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ChangeTrustAsset &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "type");
    obj.type(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ChangeTrustOp {
  ChangeTrustAsset line{};
  int64 limit{};

  ChangeTrustOp() = default;
  template<typename _line_T,
           typename _limit_T,
           typename = typename
           std::enable_if<std::is_constructible<ChangeTrustAsset, _line_T>::value
                          && std::is_constructible<int64, _limit_T>::value
                         >::type>
  explicit ChangeTrustOp(_line_T &&_line,
                         _limit_T &&_limit)
    : line(std::forward<_line_T>(_line)),
      limit(std::forward<_limit_T>(_limit)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ChangeTrustOp>
  : xdr_struct_base<field_ptr<::stellar::ChangeTrustOp,
                              decltype(::stellar::ChangeTrustOp::line),
                              &::stellar::ChangeTrustOp::line>,
                    field_ptr<::stellar::ChangeTrustOp,
                              decltype(::stellar::ChangeTrustOp::limit),
                              &::stellar::ChangeTrustOp::limit>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ChangeTrustOp &obj) {
    archive(ar, obj.line, "line");
    archive(ar, obj.limit, "limit");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ChangeTrustOp &obj) {
    archive(ar, obj.line, "line");
    archive(ar, obj.limit, "limit");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct AllowTrustOp {
  AccountID trustor{};
  AssetCode asset{};
  uint32 authorize{};

  AllowTrustOp() = default;
  template<typename _trustor_T,
           typename _asset_T,
           typename _authorize_T,
           typename = typename
           std::enable_if<std::is_constructible<AccountID, _trustor_T>::value
                          && std::is_constructible<AssetCode, _asset_T>::value
                          && std::is_constructible<uint32, _authorize_T>::value
                         >::type>
  explicit AllowTrustOp(_trustor_T &&_trustor,
                        _asset_T &&_asset,
                        _authorize_T &&_authorize)
    : trustor(std::forward<_trustor_T>(_trustor)),
      asset(std::forward<_asset_T>(_asset)),
      authorize(std::forward<_authorize_T>(_authorize)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::AllowTrustOp>
  : xdr_struct_base<field_ptr<::stellar::AllowTrustOp,
                              decltype(::stellar::AllowTrustOp::trustor),
                              &::stellar::AllowTrustOp::trustor>,
                    field_ptr<::stellar::AllowTrustOp,
                              decltype(::stellar::AllowTrustOp::asset),
                              &::stellar::AllowTrustOp::asset>,
                    field_ptr<::stellar::AllowTrustOp,
                              decltype(::stellar::AllowTrustOp::authorize),
                              &::stellar::AllowTrustOp::authorize>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::AllowTrustOp &obj) {
    archive(ar, obj.trustor, "trustor");
    archive(ar, obj.asset, "asset");
    archive(ar, obj.authorize, "authorize");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::AllowTrustOp &obj) {
    archive(ar, obj.trustor, "trustor");
    archive(ar, obj.asset, "asset");
    archive(ar, obj.authorize, "authorize");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ManageDataOp {
  string64 dataName{};
  xdr::pointer<DataValue> dataValue{};

  ManageDataOp() = default;
  template<typename _dataName_T,
           typename _dataValue_T,
           typename = typename
           std::enable_if<std::is_constructible<string64, _dataName_T>::value
                          && std::is_constructible<xdr::pointer<DataValue>, _dataValue_T>::value
                         >::type>
  explicit ManageDataOp(_dataName_T &&_dataName,
                        _dataValue_T &&_dataValue)
    : dataName(std::forward<_dataName_T>(_dataName)),
      dataValue(std::forward<_dataValue_T>(_dataValue)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageDataOp>
  : xdr_struct_base<field_ptr<::stellar::ManageDataOp,
                              decltype(::stellar::ManageDataOp::dataName),
                              &::stellar::ManageDataOp::dataName>,
                    field_ptr<::stellar::ManageDataOp,
                              decltype(::stellar::ManageDataOp::dataValue),
                              &::stellar::ManageDataOp::dataValue>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageDataOp &obj) {
    archive(ar, obj.dataName, "dataName");
    archive(ar, obj.dataValue, "dataValue");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageDataOp &obj) {
    archive(ar, obj.dataName, "dataName");
    archive(ar, obj.dataValue, "dataValue");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct BumpSequenceOp {
  SequenceNumber bumpTo{};

  BumpSequenceOp() = default;
  template<typename _bumpTo_T,
           typename = typename
           std::enable_if<std::is_constructible<SequenceNumber, _bumpTo_T>::value
                         >::type>
  explicit BumpSequenceOp(_bumpTo_T &&_bumpTo)
    : bumpTo(std::forward<_bumpTo_T>(_bumpTo)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::BumpSequenceOp>
  : xdr_struct_base<field_ptr<::stellar::BumpSequenceOp,
                              decltype(::stellar::BumpSequenceOp::bumpTo),
                              &::stellar::BumpSequenceOp::bumpTo>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::BumpSequenceOp &obj) {
    archive(ar, obj.bumpTo, "bumpTo");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::BumpSequenceOp &obj) {
    archive(ar, obj.bumpTo, "bumpTo");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct CreateClaimableBalanceOp {
  Asset asset{};
  int64 amount{};
  xdr::xvector<Claimant,10> claimants{};

  CreateClaimableBalanceOp() = default;
  template<typename _asset_T,
           typename _amount_T,
           typename _claimants_T,
           typename = typename
           std::enable_if<std::is_constructible<Asset, _asset_T>::value
                          && std::is_constructible<int64, _amount_T>::value
                          && std::is_constructible<xdr::xvector<Claimant,10>, _claimants_T>::value
                         >::type>
  explicit CreateClaimableBalanceOp(_asset_T &&_asset,
                                    _amount_T &&_amount,
                                    _claimants_T &&_claimants)
    : asset(std::forward<_asset_T>(_asset)),
      amount(std::forward<_amount_T>(_amount)),
      claimants(std::forward<_claimants_T>(_claimants)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateClaimableBalanceOp>
  : xdr_struct_base<field_ptr<::stellar::CreateClaimableBalanceOp,
                              decltype(::stellar::CreateClaimableBalanceOp::asset),
                              &::stellar::CreateClaimableBalanceOp::asset>,
                    field_ptr<::stellar::CreateClaimableBalanceOp,
                              decltype(::stellar::CreateClaimableBalanceOp::amount),
                              &::stellar::CreateClaimableBalanceOp::amount>,
                    field_ptr<::stellar::CreateClaimableBalanceOp,
                              decltype(::stellar::CreateClaimableBalanceOp::claimants),
                              &::stellar::CreateClaimableBalanceOp::claimants>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateClaimableBalanceOp &obj) {
    archive(ar, obj.asset, "asset");
    archive(ar, obj.amount, "amount");
    archive(ar, obj.claimants, "claimants");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateClaimableBalanceOp &obj) {
    archive(ar, obj.asset, "asset");
    archive(ar, obj.amount, "amount");
    archive(ar, obj.claimants, "claimants");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ClaimClaimableBalanceOp {
  ClaimableBalanceID balanceID{};

  ClaimClaimableBalanceOp() = default;
  template<typename _balanceID_T,
           typename = typename
           std::enable_if<std::is_constructible<ClaimableBalanceID, _balanceID_T>::value
                         >::type>
  explicit ClaimClaimableBalanceOp(_balanceID_T &&_balanceID)
    : balanceID(std::forward<_balanceID_T>(_balanceID)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ClaimClaimableBalanceOp>
  : xdr_struct_base<field_ptr<::stellar::ClaimClaimableBalanceOp,
                              decltype(::stellar::ClaimClaimableBalanceOp::balanceID),
                              &::stellar::ClaimClaimableBalanceOp::balanceID>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ClaimClaimableBalanceOp &obj) {
    archive(ar, obj.balanceID, "balanceID");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ClaimClaimableBalanceOp &obj) {
    archive(ar, obj.balanceID, "balanceID");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct BeginSponsoringFutureReservesOp {
  AccountID sponsoredID{};

  BeginSponsoringFutureReservesOp() = default;
  template<typename _sponsoredID_T,
           typename = typename
           std::enable_if<std::is_constructible<AccountID, _sponsoredID_T>::value
                         >::type>
  explicit BeginSponsoringFutureReservesOp(_sponsoredID_T &&_sponsoredID)
    : sponsoredID(std::forward<_sponsoredID_T>(_sponsoredID)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::BeginSponsoringFutureReservesOp>
  : xdr_struct_base<field_ptr<::stellar::BeginSponsoringFutureReservesOp,
                              decltype(::stellar::BeginSponsoringFutureReservesOp::sponsoredID),
                              &::stellar::BeginSponsoringFutureReservesOp::sponsoredID>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::BeginSponsoringFutureReservesOp &obj) {
    archive(ar, obj.sponsoredID, "sponsoredID");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::BeginSponsoringFutureReservesOp &obj) {
    archive(ar, obj.sponsoredID, "sponsoredID");
    xdr::validate(obj);
  }
};
} namespace stellar {

enum RevokeSponsorshipType : std::int32_t {
  REVOKE_SPONSORSHIP_LEDGER_ENTRY = 0,
  REVOKE_SPONSORSHIP_SIGNER = 1,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::RevokeSponsorshipType>
  : xdr_integral_base<::stellar::RevokeSponsorshipType, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::RevokeSponsorshipType val) {
    switch (val) {
    case ::stellar::REVOKE_SPONSORSHIP_LEDGER_ENTRY:
      return "REVOKE_SPONSORSHIP_LEDGER_ENTRY";
    case ::stellar::REVOKE_SPONSORSHIP_SIGNER:
      return "REVOKE_SPONSORSHIP_SIGNER";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::REVOKE_SPONSORSHIP_LEDGER_ENTRY,
      ::stellar::REVOKE_SPONSORSHIP_SIGNER
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct RevokeSponsorshipOp {
  struct _signer_t {
    AccountID accountID{};
    SignerKey signerKey{};

    _signer_t() = default;
    template<typename _accountID_T,
             typename _signerKey_T,
             typename = typename
             std::enable_if<std::is_constructible<AccountID, _accountID_T>::value
                            && std::is_constructible<SignerKey, _signerKey_T>::value
                           >::type>
    explicit _signer_t(_accountID_T &&_accountID,
                       _signerKey_T &&_signerKey)
      : accountID(std::forward<_accountID_T>(_accountID)),
        signerKey(std::forward<_signerKey_T>(_signerKey)) {}
  };

  using _xdr_case_type = xdr::xdr_traits<RevokeSponsorshipType>::case_type;
private:
  _xdr_case_type type_;
  union {
    LedgerKey ledgerKey_;
    _signer_t signer_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<RevokeSponsorshipType> &_xdr_case_values() {
    static const std::vector<RevokeSponsorshipType> _xdr_disc_vec {
      REVOKE_SPONSORSHIP_LEDGER_ENTRY,
      REVOKE_SPONSORSHIP_SIGNER
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == REVOKE_SPONSORSHIP_LEDGER_ENTRY ? 1
      : which == REVOKE_SPONSORSHIP_SIGNER ? 2
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case REVOKE_SPONSORSHIP_LEDGER_ENTRY:
      _f(&RevokeSponsorshipOp::ledgerKey_, std::forward<_A>(_a)...);
      return true;
    case REVOKE_SPONSORSHIP_SIGNER:
      _f(&RevokeSponsorshipOp::signer_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return type_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of type in RevokeSponsorshipOp");
    if (fnum != _xdr_field_number(type_)) {
      this->~RevokeSponsorshipOp();
      type_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
    }
    else
      type_ = which;
  }
  explicit RevokeSponsorshipOp(RevokeSponsorshipType which = RevokeSponsorshipType{}) : type_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
  }
  RevokeSponsorshipOp(const RevokeSponsorshipOp &source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this, source);
  }
  RevokeSponsorshipOp(RevokeSponsorshipOp &&source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this,
                      std::move(source));
  }
  ~RevokeSponsorshipOp() { _xdr_with_mem_ptr(xdr::field_destructor, type_, *this); }
  RevokeSponsorshipOp &operator=(const RevokeSponsorshipOp &source) {
    if (_xdr_field_number(type_)
        == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this, source);
    else {
      this->~RevokeSponsorshipOp();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this, source);
    }
    type_ = source.type_;
    return *this;
  }
  RevokeSponsorshipOp &operator=(RevokeSponsorshipOp &&source) {
    if (_xdr_field_number(type_)
         == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this,
                        std::move(source));
    else {
      this->~RevokeSponsorshipOp();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this,
                        std::move(source));
    }
    type_ = source.type_;
    return *this;
  }

  RevokeSponsorshipType type() const { return RevokeSponsorshipType(type_); }
  RevokeSponsorshipOp &type(RevokeSponsorshipType _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  LedgerKey &ledgerKey() {
    if (_xdr_field_number(type_) == 1)
      return ledgerKey_;
    throw xdr::xdr_wrong_union("RevokeSponsorshipOp: ledgerKey accessed when not selected");
  }
  const LedgerKey &ledgerKey() const {
    if (_xdr_field_number(type_) == 1)
      return ledgerKey_;
    throw xdr::xdr_wrong_union("RevokeSponsorshipOp: ledgerKey accessed when not selected");
  }
  _signer_t &signer() {
    if (_xdr_field_number(type_) == 2)
      return signer_;
    throw xdr::xdr_wrong_union("RevokeSponsorshipOp: signer accessed when not selected");
  }
  const _signer_t &signer() const {
    if (_xdr_field_number(type_) == 2)
      return signer_;
    throw xdr::xdr_wrong_union("RevokeSponsorshipOp: signer accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::RevokeSponsorshipOp::_signer_t>
  : xdr_struct_base<field_ptr<::stellar::RevokeSponsorshipOp::_signer_t,
                              decltype(::stellar::RevokeSponsorshipOp::_signer_t::accountID),
                              &::stellar::RevokeSponsorshipOp::_signer_t::accountID>,
                    field_ptr<::stellar::RevokeSponsorshipOp::_signer_t,
                              decltype(::stellar::RevokeSponsorshipOp::_signer_t::signerKey),
                              &::stellar::RevokeSponsorshipOp::_signer_t::signerKey>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::RevokeSponsorshipOp::_signer_t &obj) {
    archive(ar, obj.accountID, "accountID");
    archive(ar, obj.signerKey, "signerKey");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::RevokeSponsorshipOp::_signer_t &obj) {
    archive(ar, obj.accountID, "accountID");
    archive(ar, obj.signerKey, "signerKey");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::RevokeSponsorshipOp> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::RevokeSponsorshipOp;
  using case_type = ::stellar::RevokeSponsorshipOp::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().type());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "ledgerKey";
    case 2:
      return "signer";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::RevokeSponsorshipOp &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of type in RevokeSponsorshipOp");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::RevokeSponsorshipOp &obj) {
    xdr::archive(ar, obj.type(), "type");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of type in RevokeSponsorshipOp");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::RevokeSponsorshipOp &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "type");
    obj.type(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ClawbackOp {
  Asset asset{};
  MuxedAccount from{};
  int64 amount{};

  ClawbackOp() = default;
  template<typename _asset_T,
           typename _from_T,
           typename _amount_T,
           typename = typename
           std::enable_if<std::is_constructible<Asset, _asset_T>::value
                          && std::is_constructible<MuxedAccount, _from_T>::value
                          && std::is_constructible<int64, _amount_T>::value
                         >::type>
  explicit ClawbackOp(_asset_T &&_asset,
                      _from_T &&_from,
                      _amount_T &&_amount)
    : asset(std::forward<_asset_T>(_asset)),
      from(std::forward<_from_T>(_from)),
      amount(std::forward<_amount_T>(_amount)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ClawbackOp>
  : xdr_struct_base<field_ptr<::stellar::ClawbackOp,
                              decltype(::stellar::ClawbackOp::asset),
                              &::stellar::ClawbackOp::asset>,
                    field_ptr<::stellar::ClawbackOp,
                              decltype(::stellar::ClawbackOp::from),
                              &::stellar::ClawbackOp::from>,
                    field_ptr<::stellar::ClawbackOp,
                              decltype(::stellar::ClawbackOp::amount),
                              &::stellar::ClawbackOp::amount>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ClawbackOp &obj) {
    archive(ar, obj.asset, "asset");
    archive(ar, obj.from, "from");
    archive(ar, obj.amount, "amount");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ClawbackOp &obj) {
    archive(ar, obj.asset, "asset");
    archive(ar, obj.from, "from");
    archive(ar, obj.amount, "amount");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ClawbackClaimableBalanceOp {
  ClaimableBalanceID balanceID{};

  ClawbackClaimableBalanceOp() = default;
  template<typename _balanceID_T,
           typename = typename
           std::enable_if<std::is_constructible<ClaimableBalanceID, _balanceID_T>::value
                         >::type>
  explicit ClawbackClaimableBalanceOp(_balanceID_T &&_balanceID)
    : balanceID(std::forward<_balanceID_T>(_balanceID)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ClawbackClaimableBalanceOp>
  : xdr_struct_base<field_ptr<::stellar::ClawbackClaimableBalanceOp,
                              decltype(::stellar::ClawbackClaimableBalanceOp::balanceID),
                              &::stellar::ClawbackClaimableBalanceOp::balanceID>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ClawbackClaimableBalanceOp &obj) {
    archive(ar, obj.balanceID, "balanceID");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ClawbackClaimableBalanceOp &obj) {
    archive(ar, obj.balanceID, "balanceID");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct SetTrustLineFlagsOp {
  AccountID trustor{};
  Asset asset{};
  uint32 clearFlags{};
  uint32 setFlags{};

  SetTrustLineFlagsOp() = default;
  template<typename _trustor_T,
           typename _asset_T,
           typename _clearFlags_T,
           typename _setFlags_T,
           typename = typename
           std::enable_if<std::is_constructible<AccountID, _trustor_T>::value
                          && std::is_constructible<Asset, _asset_T>::value
                          && std::is_constructible<uint32, _clearFlags_T>::value
                          && std::is_constructible<uint32, _setFlags_T>::value
                         >::type>
  explicit SetTrustLineFlagsOp(_trustor_T &&_trustor,
                               _asset_T &&_asset,
                               _clearFlags_T &&_clearFlags,
                               _setFlags_T &&_setFlags)
    : trustor(std::forward<_trustor_T>(_trustor)),
      asset(std::forward<_asset_T>(_asset)),
      clearFlags(std::forward<_clearFlags_T>(_clearFlags)),
      setFlags(std::forward<_setFlags_T>(_setFlags)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SetTrustLineFlagsOp>
  : xdr_struct_base<field_ptr<::stellar::SetTrustLineFlagsOp,
                              decltype(::stellar::SetTrustLineFlagsOp::trustor),
                              &::stellar::SetTrustLineFlagsOp::trustor>,
                    field_ptr<::stellar::SetTrustLineFlagsOp,
                              decltype(::stellar::SetTrustLineFlagsOp::asset),
                              &::stellar::SetTrustLineFlagsOp::asset>,
                    field_ptr<::stellar::SetTrustLineFlagsOp,
                              decltype(::stellar::SetTrustLineFlagsOp::clearFlags),
                              &::stellar::SetTrustLineFlagsOp::clearFlags>,
                    field_ptr<::stellar::SetTrustLineFlagsOp,
                              decltype(::stellar::SetTrustLineFlagsOp::setFlags),
                              &::stellar::SetTrustLineFlagsOp::setFlags>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SetTrustLineFlagsOp &obj) {
    archive(ar, obj.trustor, "trustor");
    archive(ar, obj.asset, "asset");
    archive(ar, obj.clearFlags, "clearFlags");
    archive(ar, obj.setFlags, "setFlags");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SetTrustLineFlagsOp &obj) {
    archive(ar, obj.trustor, "trustor");
    archive(ar, obj.asset, "asset");
    archive(ar, obj.clearFlags, "clearFlags");
    archive(ar, obj.setFlags, "setFlags");
    xdr::validate(obj);
  }
};
} namespace stellar {

Constexpr const std::uint32_t LIQUIDITY_POOL_FEE_V18 = 30;

struct LiquidityPoolDepositOp {
  PoolID liquidityPoolID{};
  int64 maxAmountA{};
  int64 maxAmountB{};
  Price minPrice{};
  Price maxPrice{};

  LiquidityPoolDepositOp() = default;
  template<typename _liquidityPoolID_T,
           typename _maxAmountA_T,
           typename _maxAmountB_T,
           typename _minPrice_T,
           typename _maxPrice_T,
           typename = typename
           std::enable_if<std::is_constructible<PoolID, _liquidityPoolID_T>::value
                          && std::is_constructible<int64, _maxAmountA_T>::value
                          && std::is_constructible<int64, _maxAmountB_T>::value
                          && std::is_constructible<Price, _minPrice_T>::value
                          && std::is_constructible<Price, _maxPrice_T>::value
                         >::type>
  explicit LiquidityPoolDepositOp(_liquidityPoolID_T &&_liquidityPoolID,
                                  _maxAmountA_T &&_maxAmountA,
                                  _maxAmountB_T &&_maxAmountB,
                                  _minPrice_T &&_minPrice,
                                  _maxPrice_T &&_maxPrice)
    : liquidityPoolID(std::forward<_liquidityPoolID_T>(_liquidityPoolID)),
      maxAmountA(std::forward<_maxAmountA_T>(_maxAmountA)),
      maxAmountB(std::forward<_maxAmountB_T>(_maxAmountB)),
      minPrice(std::forward<_minPrice_T>(_minPrice)),
      maxPrice(std::forward<_maxPrice_T>(_maxPrice)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::LiquidityPoolDepositOp>
  : xdr_struct_base<field_ptr<::stellar::LiquidityPoolDepositOp,
                              decltype(::stellar::LiquidityPoolDepositOp::liquidityPoolID),
                              &::stellar::LiquidityPoolDepositOp::liquidityPoolID>,
                    field_ptr<::stellar::LiquidityPoolDepositOp,
                              decltype(::stellar::LiquidityPoolDepositOp::maxAmountA),
                              &::stellar::LiquidityPoolDepositOp::maxAmountA>,
                    field_ptr<::stellar::LiquidityPoolDepositOp,
                              decltype(::stellar::LiquidityPoolDepositOp::maxAmountB),
                              &::stellar::LiquidityPoolDepositOp::maxAmountB>,
                    field_ptr<::stellar::LiquidityPoolDepositOp,
                              decltype(::stellar::LiquidityPoolDepositOp::minPrice),
                              &::stellar::LiquidityPoolDepositOp::minPrice>,
                    field_ptr<::stellar::LiquidityPoolDepositOp,
                              decltype(::stellar::LiquidityPoolDepositOp::maxPrice),
                              &::stellar::LiquidityPoolDepositOp::maxPrice>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LiquidityPoolDepositOp &obj) {
    archive(ar, obj.liquidityPoolID, "liquidityPoolID");
    archive(ar, obj.maxAmountA, "maxAmountA");
    archive(ar, obj.maxAmountB, "maxAmountB");
    archive(ar, obj.minPrice, "minPrice");
    archive(ar, obj.maxPrice, "maxPrice");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LiquidityPoolDepositOp &obj) {
    archive(ar, obj.liquidityPoolID, "liquidityPoolID");
    archive(ar, obj.maxAmountA, "maxAmountA");
    archive(ar, obj.maxAmountB, "maxAmountB");
    archive(ar, obj.minPrice, "minPrice");
    archive(ar, obj.maxPrice, "maxPrice");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct LiquidityPoolWithdrawOp {
  PoolID liquidityPoolID{};
  int64 amount{};
  int64 minAmountA{};
  int64 minAmountB{};

  LiquidityPoolWithdrawOp() = default;
  template<typename _liquidityPoolID_T,
           typename _amount_T,
           typename _minAmountA_T,
           typename _minAmountB_T,
           typename = typename
           std::enable_if<std::is_constructible<PoolID, _liquidityPoolID_T>::value
                          && std::is_constructible<int64, _amount_T>::value
                          && std::is_constructible<int64, _minAmountA_T>::value
                          && std::is_constructible<int64, _minAmountB_T>::value
                         >::type>
  explicit LiquidityPoolWithdrawOp(_liquidityPoolID_T &&_liquidityPoolID,
                                   _amount_T &&_amount,
                                   _minAmountA_T &&_minAmountA,
                                   _minAmountB_T &&_minAmountB)
    : liquidityPoolID(std::forward<_liquidityPoolID_T>(_liquidityPoolID)),
      amount(std::forward<_amount_T>(_amount)),
      minAmountA(std::forward<_minAmountA_T>(_minAmountA)),
      minAmountB(std::forward<_minAmountB_T>(_minAmountB)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::LiquidityPoolWithdrawOp>
  : xdr_struct_base<field_ptr<::stellar::LiquidityPoolWithdrawOp,
                              decltype(::stellar::LiquidityPoolWithdrawOp::liquidityPoolID),
                              &::stellar::LiquidityPoolWithdrawOp::liquidityPoolID>,
                    field_ptr<::stellar::LiquidityPoolWithdrawOp,
                              decltype(::stellar::LiquidityPoolWithdrawOp::amount),
                              &::stellar::LiquidityPoolWithdrawOp::amount>,
                    field_ptr<::stellar::LiquidityPoolWithdrawOp,
                              decltype(::stellar::LiquidityPoolWithdrawOp::minAmountA),
                              &::stellar::LiquidityPoolWithdrawOp::minAmountA>,
                    field_ptr<::stellar::LiquidityPoolWithdrawOp,
                              decltype(::stellar::LiquidityPoolWithdrawOp::minAmountB),
                              &::stellar::LiquidityPoolWithdrawOp::minAmountB>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LiquidityPoolWithdrawOp &obj) {
    archive(ar, obj.liquidityPoolID, "liquidityPoolID");
    archive(ar, obj.amount, "amount");
    archive(ar, obj.minAmountA, "minAmountA");
    archive(ar, obj.minAmountB, "minAmountB");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LiquidityPoolWithdrawOp &obj) {
    archive(ar, obj.liquidityPoolID, "liquidityPoolID");
    archive(ar, obj.amount, "amount");
    archive(ar, obj.minAmountA, "minAmountA");
    archive(ar, obj.minAmountB, "minAmountB");
    xdr::validate(obj);
  }
};
} namespace stellar {

enum HostFunctionType : std::int32_t {
  HOST_FUNCTION_TYPE_INVOKE_CONTRACT = 0,
  HOST_FUNCTION_TYPE_CREATE_CONTRACT = 1,
  HOST_FUNCTION_TYPE_UPLOAD_CONTRACT_WASM = 2,
  HOST_FUNCTION_TYPE_CREATE_CONTRACT_V2 = 3,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::HostFunctionType>
  : xdr_integral_base<::stellar::HostFunctionType, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::HostFunctionType val) {
    switch (val) {
    case ::stellar::HOST_FUNCTION_TYPE_INVOKE_CONTRACT:
      return "HOST_FUNCTION_TYPE_INVOKE_CONTRACT";
    case ::stellar::HOST_FUNCTION_TYPE_CREATE_CONTRACT:
      return "HOST_FUNCTION_TYPE_CREATE_CONTRACT";
    case ::stellar::HOST_FUNCTION_TYPE_UPLOAD_CONTRACT_WASM:
      return "HOST_FUNCTION_TYPE_UPLOAD_CONTRACT_WASM";
    case ::stellar::HOST_FUNCTION_TYPE_CREATE_CONTRACT_V2:
      return "HOST_FUNCTION_TYPE_CREATE_CONTRACT_V2";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::HOST_FUNCTION_TYPE_INVOKE_CONTRACT,
      ::stellar::HOST_FUNCTION_TYPE_CREATE_CONTRACT,
      ::stellar::HOST_FUNCTION_TYPE_UPLOAD_CONTRACT_WASM,
      ::stellar::HOST_FUNCTION_TYPE_CREATE_CONTRACT_V2
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

enum ContractIDPreimageType : std::int32_t {
  CONTRACT_ID_PREIMAGE_FROM_ADDRESS = 0,
  CONTRACT_ID_PREIMAGE_FROM_ASSET = 1,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ContractIDPreimageType>
  : xdr_integral_base<::stellar::ContractIDPreimageType, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ContractIDPreimageType val) {
    switch (val) {
    case ::stellar::CONTRACT_ID_PREIMAGE_FROM_ADDRESS:
      return "CONTRACT_ID_PREIMAGE_FROM_ADDRESS";
    case ::stellar::CONTRACT_ID_PREIMAGE_FROM_ASSET:
      return "CONTRACT_ID_PREIMAGE_FROM_ASSET";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::CONTRACT_ID_PREIMAGE_FROM_ADDRESS,
      ::stellar::CONTRACT_ID_PREIMAGE_FROM_ASSET
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct ContractIDPreimage {
  struct _fromAddress_t {
    SCAddress address{};
    uint256 salt{};

    _fromAddress_t() = default;
    template<typename _address_T,
             typename _salt_T,
             typename = typename
             std::enable_if<std::is_constructible<SCAddress, _address_T>::value
                            && std::is_constructible<uint256, _salt_T>::value
                           >::type>
    explicit _fromAddress_t(_address_T &&_address,
                            _salt_T &&_salt)
      : address(std::forward<_address_T>(_address)),
        salt(std::forward<_salt_T>(_salt)) {}
  };

  using _xdr_case_type = xdr::xdr_traits<ContractIDPreimageType>::case_type;
private:
  _xdr_case_type type_;
  union {
    _fromAddress_t fromAddress_;
    Asset fromAsset_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<ContractIDPreimageType> &_xdr_case_values() {
    static const std::vector<ContractIDPreimageType> _xdr_disc_vec {
      CONTRACT_ID_PREIMAGE_FROM_ADDRESS,
      CONTRACT_ID_PREIMAGE_FROM_ASSET
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == CONTRACT_ID_PREIMAGE_FROM_ADDRESS ? 1
      : which == CONTRACT_ID_PREIMAGE_FROM_ASSET ? 2
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case CONTRACT_ID_PREIMAGE_FROM_ADDRESS:
      _f(&ContractIDPreimage::fromAddress_, std::forward<_A>(_a)...);
      return true;
    case CONTRACT_ID_PREIMAGE_FROM_ASSET:
      _f(&ContractIDPreimage::fromAsset_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return type_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of type in ContractIDPreimage");
    if (fnum != _xdr_field_number(type_)) {
      this->~ContractIDPreimage();
      type_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
    }
    else
      type_ = which;
  }
  explicit ContractIDPreimage(ContractIDPreimageType which = ContractIDPreimageType{}) : type_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
  }
  ContractIDPreimage(const ContractIDPreimage &source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this, source);
  }
  ContractIDPreimage(ContractIDPreimage &&source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this,
                      std::move(source));
  }
  ~ContractIDPreimage() { _xdr_with_mem_ptr(xdr::field_destructor, type_, *this); }
  ContractIDPreimage &operator=(const ContractIDPreimage &source) {
    if (_xdr_field_number(type_)
        == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this, source);
    else {
      this->~ContractIDPreimage();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this, source);
    }
    type_ = source.type_;
    return *this;
  }
  ContractIDPreimage &operator=(ContractIDPreimage &&source) {
    if (_xdr_field_number(type_)
         == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this,
                        std::move(source));
    else {
      this->~ContractIDPreimage();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this,
                        std::move(source));
    }
    type_ = source.type_;
    return *this;
  }

  ContractIDPreimageType type() const { return ContractIDPreimageType(type_); }
  ContractIDPreimage &type(ContractIDPreimageType _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  _fromAddress_t &fromAddress() {
    if (_xdr_field_number(type_) == 1)
      return fromAddress_;
    throw xdr::xdr_wrong_union("ContractIDPreimage: fromAddress accessed when not selected");
  }
  const _fromAddress_t &fromAddress() const {
    if (_xdr_field_number(type_) == 1)
      return fromAddress_;
    throw xdr::xdr_wrong_union("ContractIDPreimage: fromAddress accessed when not selected");
  }
  Asset &fromAsset() {
    if (_xdr_field_number(type_) == 2)
      return fromAsset_;
    throw xdr::xdr_wrong_union("ContractIDPreimage: fromAsset accessed when not selected");
  }
  const Asset &fromAsset() const {
    if (_xdr_field_number(type_) == 2)
      return fromAsset_;
    throw xdr::xdr_wrong_union("ContractIDPreimage: fromAsset accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ContractIDPreimage::_fromAddress_t>
  : xdr_struct_base<field_ptr<::stellar::ContractIDPreimage::_fromAddress_t,
                              decltype(::stellar::ContractIDPreimage::_fromAddress_t::address),
                              &::stellar::ContractIDPreimage::_fromAddress_t::address>,
                    field_ptr<::stellar::ContractIDPreimage::_fromAddress_t,
                              decltype(::stellar::ContractIDPreimage::_fromAddress_t::salt),
                              &::stellar::ContractIDPreimage::_fromAddress_t::salt>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ContractIDPreimage::_fromAddress_t &obj) {
    archive(ar, obj.address, "address");
    archive(ar, obj.salt, "salt");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ContractIDPreimage::_fromAddress_t &obj) {
    archive(ar, obj.address, "address");
    archive(ar, obj.salt, "salt");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ContractIDPreimage> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ContractIDPreimage;
  using case_type = ::stellar::ContractIDPreimage::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().type());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "fromAddress";
    case 2:
      return "fromAsset";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ContractIDPreimage &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of type in ContractIDPreimage");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ContractIDPreimage &obj) {
    xdr::archive(ar, obj.type(), "type");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of type in ContractIDPreimage");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ContractIDPreimage &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "type");
    obj.type(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

struct CreateContractArgs {
  ContractIDPreimage contractIDPreimage{};
  ContractExecutable executable{};

  CreateContractArgs() = default;
  template<typename _contractIDPreimage_T,
           typename _executable_T,
           typename = typename
           std::enable_if<std::is_constructible<ContractIDPreimage, _contractIDPreimage_T>::value
                          && std::is_constructible<ContractExecutable, _executable_T>::value
                         >::type>
  explicit CreateContractArgs(_contractIDPreimage_T &&_contractIDPreimage,
                              _executable_T &&_executable)
    : contractIDPreimage(std::forward<_contractIDPreimage_T>(_contractIDPreimage)),
      executable(std::forward<_executable_T>(_executable)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateContractArgs>
  : xdr_struct_base<field_ptr<::stellar::CreateContractArgs,
                              decltype(::stellar::CreateContractArgs::contractIDPreimage),
                              &::stellar::CreateContractArgs::contractIDPreimage>,
                    field_ptr<::stellar::CreateContractArgs,
                              decltype(::stellar::CreateContractArgs::executable),
                              &::stellar::CreateContractArgs::executable>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateContractArgs &obj) {
    archive(ar, obj.contractIDPreimage, "contractIDPreimage");
    archive(ar, obj.executable, "executable");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateContractArgs &obj) {
    archive(ar, obj.contractIDPreimage, "contractIDPreimage");
    archive(ar, obj.executable, "executable");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct CreateContractArgsV2 {
  ContractIDPreimage contractIDPreimage{};
  ContractExecutable executable{};
  xdr::xvector<SCVal> constructorArgs{};

  CreateContractArgsV2() = default;
  template<typename _contractIDPreimage_T,
           typename _executable_T,
           typename _constructorArgs_T,
           typename = typename
           std::enable_if<std::is_constructible<ContractIDPreimage, _contractIDPreimage_T>::value
                          && std::is_constructible<ContractExecutable, _executable_T>::value
                          && std::is_constructible<xdr::xvector<SCVal>, _constructorArgs_T>::value
                         >::type>
  explicit CreateContractArgsV2(_contractIDPreimage_T &&_contractIDPreimage,
                                _executable_T &&_executable,
                                _constructorArgs_T &&_constructorArgs)
    : contractIDPreimage(std::forward<_contractIDPreimage_T>(_contractIDPreimage)),
      executable(std::forward<_executable_T>(_executable)),
      constructorArgs(std::forward<_constructorArgs_T>(_constructorArgs)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateContractArgsV2>
  : xdr_struct_base<field_ptr<::stellar::CreateContractArgsV2,
                              decltype(::stellar::CreateContractArgsV2::contractIDPreimage),
                              &::stellar::CreateContractArgsV2::contractIDPreimage>,
                    field_ptr<::stellar::CreateContractArgsV2,
                              decltype(::stellar::CreateContractArgsV2::executable),
                              &::stellar::CreateContractArgsV2::executable>,
                    field_ptr<::stellar::CreateContractArgsV2,
                              decltype(::stellar::CreateContractArgsV2::constructorArgs),
                              &::stellar::CreateContractArgsV2::constructorArgs>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateContractArgsV2 &obj) {
    archive(ar, obj.contractIDPreimage, "contractIDPreimage");
    archive(ar, obj.executable, "executable");
    archive(ar, obj.constructorArgs, "constructorArgs");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateContractArgsV2 &obj) {
    archive(ar, obj.contractIDPreimage, "contractIDPreimage");
    archive(ar, obj.executable, "executable");
    archive(ar, obj.constructorArgs, "constructorArgs");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct InvokeContractArgs {
  SCAddress contractAddress{};
  SCSymbol functionName{};
  xdr::xvector<SCVal> args{};

  InvokeContractArgs() = default;
  template<typename _contractAddress_T,
           typename _functionName_T,
           typename _args_T,
           typename = typename
           std::enable_if<std::is_constructible<SCAddress, _contractAddress_T>::value
                          && std::is_constructible<SCSymbol, _functionName_T>::value
                          && std::is_constructible<xdr::xvector<SCVal>, _args_T>::value
                         >::type>
  explicit InvokeContractArgs(_contractAddress_T &&_contractAddress,
                              _functionName_T &&_functionName,
                              _args_T &&_args)
    : contractAddress(std::forward<_contractAddress_T>(_contractAddress)),
      functionName(std::forward<_functionName_T>(_functionName)),
      args(std::forward<_args_T>(_args)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::InvokeContractArgs>
  : xdr_struct_base<field_ptr<::stellar::InvokeContractArgs,
                              decltype(::stellar::InvokeContractArgs::contractAddress),
                              &::stellar::InvokeContractArgs::contractAddress>,
                    field_ptr<::stellar::InvokeContractArgs,
                              decltype(::stellar::InvokeContractArgs::functionName),
                              &::stellar::InvokeContractArgs::functionName>,
                    field_ptr<::stellar::InvokeContractArgs,
                              decltype(::stellar::InvokeContractArgs::args),
                              &::stellar::InvokeContractArgs::args>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::InvokeContractArgs &obj) {
    archive(ar, obj.contractAddress, "contractAddress");
    archive(ar, obj.functionName, "functionName");
    archive(ar, obj.args, "args");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::InvokeContractArgs &obj) {
    archive(ar, obj.contractAddress, "contractAddress");
    archive(ar, obj.functionName, "functionName");
    archive(ar, obj.args, "args");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct HostFunction {
  using _xdr_case_type = xdr::xdr_traits<HostFunctionType>::case_type;
private:
  _xdr_case_type type_;
  union {
    InvokeContractArgs invokeContract_;
    CreateContractArgs createContract_;
    xdr::opaque_vec<> wasm_;
    CreateContractArgsV2 createContractV2_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<HostFunctionType> &_xdr_case_values() {
    static const std::vector<HostFunctionType> _xdr_disc_vec {
      HOST_FUNCTION_TYPE_INVOKE_CONTRACT,
      HOST_FUNCTION_TYPE_CREATE_CONTRACT,
      HOST_FUNCTION_TYPE_UPLOAD_CONTRACT_WASM,
      HOST_FUNCTION_TYPE_CREATE_CONTRACT_V2
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == HOST_FUNCTION_TYPE_INVOKE_CONTRACT ? 1
      : which == HOST_FUNCTION_TYPE_CREATE_CONTRACT ? 2
      : which == HOST_FUNCTION_TYPE_UPLOAD_CONTRACT_WASM ? 3
      : which == HOST_FUNCTION_TYPE_CREATE_CONTRACT_V2 ? 4
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case HOST_FUNCTION_TYPE_INVOKE_CONTRACT:
      _f(&HostFunction::invokeContract_, std::forward<_A>(_a)...);
      return true;
    case HOST_FUNCTION_TYPE_CREATE_CONTRACT:
      _f(&HostFunction::createContract_, std::forward<_A>(_a)...);
      return true;
    case HOST_FUNCTION_TYPE_UPLOAD_CONTRACT_WASM:
      _f(&HostFunction::wasm_, std::forward<_A>(_a)...);
      return true;
    case HOST_FUNCTION_TYPE_CREATE_CONTRACT_V2:
      _f(&HostFunction::createContractV2_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return type_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of type in HostFunction");
    if (fnum != _xdr_field_number(type_)) {
      this->~HostFunction();
      type_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
    }
    else
      type_ = which;
  }
  explicit HostFunction(HostFunctionType which = HostFunctionType{}) : type_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
  }
  HostFunction(const HostFunction &source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this, source);
  }
  HostFunction(HostFunction &&source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this,
                      std::move(source));
  }
  ~HostFunction() { _xdr_with_mem_ptr(xdr::field_destructor, type_, *this); }
  HostFunction &operator=(const HostFunction &source) {
    if (_xdr_field_number(type_)
        == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this, source);
    else {
      this->~HostFunction();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this, source);
    }
    type_ = source.type_;
    return *this;
  }
  HostFunction &operator=(HostFunction &&source) {
    if (_xdr_field_number(type_)
         == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this,
                        std::move(source));
    else {
      this->~HostFunction();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this,
                        std::move(source));
    }
    type_ = source.type_;
    return *this;
  }

  HostFunctionType type() const { return HostFunctionType(type_); }
  HostFunction &type(HostFunctionType _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  InvokeContractArgs &invokeContract() {
    if (_xdr_field_number(type_) == 1)
      return invokeContract_;
    throw xdr::xdr_wrong_union("HostFunction: invokeContract accessed when not selected");
  }
  const InvokeContractArgs &invokeContract() const {
    if (_xdr_field_number(type_) == 1)
      return invokeContract_;
    throw xdr::xdr_wrong_union("HostFunction: invokeContract accessed when not selected");
  }
  CreateContractArgs &createContract() {
    if (_xdr_field_number(type_) == 2)
      return createContract_;
    throw xdr::xdr_wrong_union("HostFunction: createContract accessed when not selected");
  }
  const CreateContractArgs &createContract() const {
    if (_xdr_field_number(type_) == 2)
      return createContract_;
    throw xdr::xdr_wrong_union("HostFunction: createContract accessed when not selected");
  }
  xdr::opaque_vec<> &wasm() {
    if (_xdr_field_number(type_) == 3)
      return wasm_;
    throw xdr::xdr_wrong_union("HostFunction: wasm accessed when not selected");
  }
  const xdr::opaque_vec<> &wasm() const {
    if (_xdr_field_number(type_) == 3)
      return wasm_;
    throw xdr::xdr_wrong_union("HostFunction: wasm accessed when not selected");
  }
  CreateContractArgsV2 &createContractV2() {
    if (_xdr_field_number(type_) == 4)
      return createContractV2_;
    throw xdr::xdr_wrong_union("HostFunction: createContractV2 accessed when not selected");
  }
  const CreateContractArgsV2 &createContractV2() const {
    if (_xdr_field_number(type_) == 4)
      return createContractV2_;
    throw xdr::xdr_wrong_union("HostFunction: createContractV2 accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::HostFunction> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::HostFunction;
  using case_type = ::stellar::HostFunction::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().type());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "invokeContract";
    case 2:
      return "createContract";
    case 3:
      return "wasm";
    case 4:
      return "createContractV2";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::HostFunction &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of type in HostFunction");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::HostFunction &obj) {
    xdr::archive(ar, obj.type(), "type");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of type in HostFunction");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::HostFunction &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "type");
    obj.type(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

enum SorobanAuthorizedFunctionType : std::int32_t {
  SOROBAN_AUTHORIZED_FUNCTION_TYPE_CONTRACT_FN = 0,
  SOROBAN_AUTHORIZED_FUNCTION_TYPE_CREATE_CONTRACT_HOST_FN = 1,
  SOROBAN_AUTHORIZED_FUNCTION_TYPE_CREATE_CONTRACT_V2_HOST_FN = 2,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SorobanAuthorizedFunctionType>
  : xdr_integral_base<::stellar::SorobanAuthorizedFunctionType, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::SorobanAuthorizedFunctionType val) {
    switch (val) {
    case ::stellar::SOROBAN_AUTHORIZED_FUNCTION_TYPE_CONTRACT_FN:
      return "SOROBAN_AUTHORIZED_FUNCTION_TYPE_CONTRACT_FN";
    case ::stellar::SOROBAN_AUTHORIZED_FUNCTION_TYPE_CREATE_CONTRACT_HOST_FN:
      return "SOROBAN_AUTHORIZED_FUNCTION_TYPE_CREATE_CONTRACT_HOST_FN";
    case ::stellar::SOROBAN_AUTHORIZED_FUNCTION_TYPE_CREATE_CONTRACT_V2_HOST_FN:
      return "SOROBAN_AUTHORIZED_FUNCTION_TYPE_CREATE_CONTRACT_V2_HOST_FN";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::SOROBAN_AUTHORIZED_FUNCTION_TYPE_CONTRACT_FN,
      ::stellar::SOROBAN_AUTHORIZED_FUNCTION_TYPE_CREATE_CONTRACT_HOST_FN,
      ::stellar::SOROBAN_AUTHORIZED_FUNCTION_TYPE_CREATE_CONTRACT_V2_HOST_FN
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct SorobanAuthorizedFunction {
  using _xdr_case_type = xdr::xdr_traits<SorobanAuthorizedFunctionType>::case_type;
private:
  _xdr_case_type type_;
  union {
    InvokeContractArgs contractFn_;
    CreateContractArgs createContractHostFn_;
    CreateContractArgsV2 createContractV2HostFn_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<SorobanAuthorizedFunctionType> &_xdr_case_values() {
    static const std::vector<SorobanAuthorizedFunctionType> _xdr_disc_vec {
      SOROBAN_AUTHORIZED_FUNCTION_TYPE_CONTRACT_FN,
      SOROBAN_AUTHORIZED_FUNCTION_TYPE_CREATE_CONTRACT_HOST_FN,
      SOROBAN_AUTHORIZED_FUNCTION_TYPE_CREATE_CONTRACT_V2_HOST_FN
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == SOROBAN_AUTHORIZED_FUNCTION_TYPE_CONTRACT_FN ? 1
      : which == SOROBAN_AUTHORIZED_FUNCTION_TYPE_CREATE_CONTRACT_HOST_FN ? 2
      : which == SOROBAN_AUTHORIZED_FUNCTION_TYPE_CREATE_CONTRACT_V2_HOST_FN ? 3
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case SOROBAN_AUTHORIZED_FUNCTION_TYPE_CONTRACT_FN:
      _f(&SorobanAuthorizedFunction::contractFn_, std::forward<_A>(_a)...);
      return true;
    case SOROBAN_AUTHORIZED_FUNCTION_TYPE_CREATE_CONTRACT_HOST_FN:
      _f(&SorobanAuthorizedFunction::createContractHostFn_, std::forward<_A>(_a)...);
      return true;
    case SOROBAN_AUTHORIZED_FUNCTION_TYPE_CREATE_CONTRACT_V2_HOST_FN:
      _f(&SorobanAuthorizedFunction::createContractV2HostFn_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return type_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of type in SorobanAuthorizedFunction");
    if (fnum != _xdr_field_number(type_)) {
      this->~SorobanAuthorizedFunction();
      type_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
    }
    else
      type_ = which;
  }
  explicit SorobanAuthorizedFunction(SorobanAuthorizedFunctionType which = SorobanAuthorizedFunctionType{}) : type_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
  }
  SorobanAuthorizedFunction(const SorobanAuthorizedFunction &source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this, source);
  }
  SorobanAuthorizedFunction(SorobanAuthorizedFunction &&source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this,
                      std::move(source));
  }
  ~SorobanAuthorizedFunction() { _xdr_with_mem_ptr(xdr::field_destructor, type_, *this); }
  SorobanAuthorizedFunction &operator=(const SorobanAuthorizedFunction &source) {
    if (_xdr_field_number(type_)
        == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this, source);
    else {
      this->~SorobanAuthorizedFunction();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this, source);
    }
    type_ = source.type_;
    return *this;
  }
  SorobanAuthorizedFunction &operator=(SorobanAuthorizedFunction &&source) {
    if (_xdr_field_number(type_)
         == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this,
                        std::move(source));
    else {
      this->~SorobanAuthorizedFunction();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this,
                        std::move(source));
    }
    type_ = source.type_;
    return *this;
  }

  SorobanAuthorizedFunctionType type() const { return SorobanAuthorizedFunctionType(type_); }
  SorobanAuthorizedFunction &type(SorobanAuthorizedFunctionType _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  InvokeContractArgs &contractFn() {
    if (_xdr_field_number(type_) == 1)
      return contractFn_;
    throw xdr::xdr_wrong_union("SorobanAuthorizedFunction: contractFn accessed when not selected");
  }
  const InvokeContractArgs &contractFn() const {
    if (_xdr_field_number(type_) == 1)
      return contractFn_;
    throw xdr::xdr_wrong_union("SorobanAuthorizedFunction: contractFn accessed when not selected");
  }
  CreateContractArgs &createContractHostFn() {
    if (_xdr_field_number(type_) == 2)
      return createContractHostFn_;
    throw xdr::xdr_wrong_union("SorobanAuthorizedFunction: createContractHostFn accessed when not selected");
  }
  const CreateContractArgs &createContractHostFn() const {
    if (_xdr_field_number(type_) == 2)
      return createContractHostFn_;
    throw xdr::xdr_wrong_union("SorobanAuthorizedFunction: createContractHostFn accessed when not selected");
  }
  CreateContractArgsV2 &createContractV2HostFn() {
    if (_xdr_field_number(type_) == 3)
      return createContractV2HostFn_;
    throw xdr::xdr_wrong_union("SorobanAuthorizedFunction: createContractV2HostFn accessed when not selected");
  }
  const CreateContractArgsV2 &createContractV2HostFn() const {
    if (_xdr_field_number(type_) == 3)
      return createContractV2HostFn_;
    throw xdr::xdr_wrong_union("SorobanAuthorizedFunction: createContractV2HostFn accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SorobanAuthorizedFunction> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::SorobanAuthorizedFunction;
  using case_type = ::stellar::SorobanAuthorizedFunction::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().type());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "contractFn";
    case 2:
      return "createContractHostFn";
    case 3:
      return "createContractV2HostFn";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::SorobanAuthorizedFunction &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of type in SorobanAuthorizedFunction");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SorobanAuthorizedFunction &obj) {
    xdr::archive(ar, obj.type(), "type");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of type in SorobanAuthorizedFunction");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SorobanAuthorizedFunction &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "type");
    obj.type(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

struct SorobanAuthorizedInvocation {
  SorobanAuthorizedFunction function{};
  xdr::xvector<SorobanAuthorizedInvocation> subInvocations{};

  SorobanAuthorizedInvocation() = default;
  template<typename _function_T,
           typename _subInvocations_T,
           typename = typename
           std::enable_if<std::is_constructible<SorobanAuthorizedFunction, _function_T>::value
                          && std::is_constructible<xdr::xvector<SorobanAuthorizedInvocation>, _subInvocations_T>::value
                         >::type>
  explicit SorobanAuthorizedInvocation(_function_T &&_function,
                                       _subInvocations_T &&_subInvocations)
    : function(std::forward<_function_T>(_function)),
      subInvocations(std::forward<_subInvocations_T>(_subInvocations)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SorobanAuthorizedInvocation>
  : xdr_struct_base<field_ptr<::stellar::SorobanAuthorizedInvocation,
                              decltype(::stellar::SorobanAuthorizedInvocation::function),
                              &::stellar::SorobanAuthorizedInvocation::function>,
                    field_ptr<::stellar::SorobanAuthorizedInvocation,
                              decltype(::stellar::SorobanAuthorizedInvocation::subInvocations),
                              &::stellar::SorobanAuthorizedInvocation::subInvocations>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SorobanAuthorizedInvocation &obj) {
    archive(ar, obj.function, "function");
    archive(ar, obj.subInvocations, "subInvocations");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SorobanAuthorizedInvocation &obj) {
    archive(ar, obj.function, "function");
    archive(ar, obj.subInvocations, "subInvocations");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct SorobanAddressCredentials {
  SCAddress address{};
  int64 nonce{};
  uint32 signatureExpirationLedger{};
  SCVal signature{};

  SorobanAddressCredentials() = default;
  template<typename _address_T,
           typename _nonce_T,
           typename _signatureExpirationLedger_T,
           typename _signature_T,
           typename = typename
           std::enable_if<std::is_constructible<SCAddress, _address_T>::value
                          && std::is_constructible<int64, _nonce_T>::value
                          && std::is_constructible<uint32, _signatureExpirationLedger_T>::value
                          && std::is_constructible<SCVal, _signature_T>::value
                         >::type>
  explicit SorobanAddressCredentials(_address_T &&_address,
                                     _nonce_T &&_nonce,
                                     _signatureExpirationLedger_T &&_signatureExpirationLedger,
                                     _signature_T &&_signature)
    : address(std::forward<_address_T>(_address)),
      nonce(std::forward<_nonce_T>(_nonce)),
      signatureExpirationLedger(std::forward<_signatureExpirationLedger_T>(_signatureExpirationLedger)),
      signature(std::forward<_signature_T>(_signature)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SorobanAddressCredentials>
  : xdr_struct_base<field_ptr<::stellar::SorobanAddressCredentials,
                              decltype(::stellar::SorobanAddressCredentials::address),
                              &::stellar::SorobanAddressCredentials::address>,
                    field_ptr<::stellar::SorobanAddressCredentials,
                              decltype(::stellar::SorobanAddressCredentials::nonce),
                              &::stellar::SorobanAddressCredentials::nonce>,
                    field_ptr<::stellar::SorobanAddressCredentials,
                              decltype(::stellar::SorobanAddressCredentials::signatureExpirationLedger),
                              &::stellar::SorobanAddressCredentials::signatureExpirationLedger>,
                    field_ptr<::stellar::SorobanAddressCredentials,
                              decltype(::stellar::SorobanAddressCredentials::signature),
                              &::stellar::SorobanAddressCredentials::signature>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SorobanAddressCredentials &obj) {
    archive(ar, obj.address, "address");
    archive(ar, obj.nonce, "nonce");
    archive(ar, obj.signatureExpirationLedger, "signatureExpirationLedger");
    archive(ar, obj.signature, "signature");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SorobanAddressCredentials &obj) {
    archive(ar, obj.address, "address");
    archive(ar, obj.nonce, "nonce");
    archive(ar, obj.signatureExpirationLedger, "signatureExpirationLedger");
    archive(ar, obj.signature, "signature");
    xdr::validate(obj);
  }
};
} namespace stellar {

enum SorobanCredentialsType : std::int32_t {
  SOROBAN_CREDENTIALS_SOURCE_ACCOUNT = 0,
  SOROBAN_CREDENTIALS_ADDRESS = 1,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SorobanCredentialsType>
  : xdr_integral_base<::stellar::SorobanCredentialsType, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::SorobanCredentialsType val) {
    switch (val) {
    case ::stellar::SOROBAN_CREDENTIALS_SOURCE_ACCOUNT:
      return "SOROBAN_CREDENTIALS_SOURCE_ACCOUNT";
    case ::stellar::SOROBAN_CREDENTIALS_ADDRESS:
      return "SOROBAN_CREDENTIALS_ADDRESS";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::SOROBAN_CREDENTIALS_SOURCE_ACCOUNT,
      ::stellar::SOROBAN_CREDENTIALS_ADDRESS
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct SorobanCredentials {
  using _xdr_case_type = xdr::xdr_traits<SorobanCredentialsType>::case_type;
private:
  _xdr_case_type type_;
  union {
    SorobanAddressCredentials address_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<SorobanCredentialsType> &_xdr_case_values() {
    static const std::vector<SorobanCredentialsType> _xdr_disc_vec {
      SOROBAN_CREDENTIALS_SOURCE_ACCOUNT,
      SOROBAN_CREDENTIALS_ADDRESS
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == SOROBAN_CREDENTIALS_SOURCE_ACCOUNT ? 0
      : which == SOROBAN_CREDENTIALS_ADDRESS ? 1
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case SOROBAN_CREDENTIALS_SOURCE_ACCOUNT:
      return true;
    case SOROBAN_CREDENTIALS_ADDRESS:
      _f(&SorobanCredentials::address_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return type_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of type in SorobanCredentials");
    if (fnum != _xdr_field_number(type_)) {
      this->~SorobanCredentials();
      type_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
    }
    else
      type_ = which;
  }
  explicit SorobanCredentials(SorobanCredentialsType which = SorobanCredentialsType{}) : type_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
  }
  SorobanCredentials(const SorobanCredentials &source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this, source);
  }
  SorobanCredentials(SorobanCredentials &&source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this,
                      std::move(source));
  }
  ~SorobanCredentials() { _xdr_with_mem_ptr(xdr::field_destructor, type_, *this); }
  SorobanCredentials &operator=(const SorobanCredentials &source) {
    if (_xdr_field_number(type_)
        == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this, source);
    else {
      this->~SorobanCredentials();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this, source);
    }
    type_ = source.type_;
    return *this;
  }
  SorobanCredentials &operator=(SorobanCredentials &&source) {
    if (_xdr_field_number(type_)
         == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this,
                        std::move(source));
    else {
      this->~SorobanCredentials();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this,
                        std::move(source));
    }
    type_ = source.type_;
    return *this;
  }

  SorobanCredentialsType type() const { return SorobanCredentialsType(type_); }
  SorobanCredentials &type(SorobanCredentialsType _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  SorobanAddressCredentials &address() {
    if (_xdr_field_number(type_) == 1)
      return address_;
    throw xdr::xdr_wrong_union("SorobanCredentials: address accessed when not selected");
  }
  const SorobanAddressCredentials &address() const {
    if (_xdr_field_number(type_) == 1)
      return address_;
    throw xdr::xdr_wrong_union("SorobanCredentials: address accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SorobanCredentials> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::SorobanCredentials;
  using case_type = ::stellar::SorobanCredentials::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().type());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "address";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::SorobanCredentials &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of type in SorobanCredentials");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SorobanCredentials &obj) {
    xdr::archive(ar, obj.type(), "type");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of type in SorobanCredentials");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SorobanCredentials &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "type");
    obj.type(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

struct SorobanAuthorizationEntry {
  SorobanCredentials credentials{};
  SorobanAuthorizedInvocation rootInvocation{};

  SorobanAuthorizationEntry() = default;
  template<typename _credentials_T,
           typename _rootInvocation_T,
           typename = typename
           std::enable_if<std::is_constructible<SorobanCredentials, _credentials_T>::value
                          && std::is_constructible<SorobanAuthorizedInvocation, _rootInvocation_T>::value
                         >::type>
  explicit SorobanAuthorizationEntry(_credentials_T &&_credentials,
                                     _rootInvocation_T &&_rootInvocation)
    : credentials(std::forward<_credentials_T>(_credentials)),
      rootInvocation(std::forward<_rootInvocation_T>(_rootInvocation)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SorobanAuthorizationEntry>
  : xdr_struct_base<field_ptr<::stellar::SorobanAuthorizationEntry,
                              decltype(::stellar::SorobanAuthorizationEntry::credentials),
                              &::stellar::SorobanAuthorizationEntry::credentials>,
                    field_ptr<::stellar::SorobanAuthorizationEntry,
                              decltype(::stellar::SorobanAuthorizationEntry::rootInvocation),
                              &::stellar::SorobanAuthorizationEntry::rootInvocation>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SorobanAuthorizationEntry &obj) {
    archive(ar, obj.credentials, "credentials");
    archive(ar, obj.rootInvocation, "rootInvocation");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SorobanAuthorizationEntry &obj) {
    archive(ar, obj.credentials, "credentials");
    archive(ar, obj.rootInvocation, "rootInvocation");
    xdr::validate(obj);
  }
};
} namespace stellar {

using SorobanAuthorizationEntries = xdr::xvector<SorobanAuthorizationEntry>;

struct InvokeHostFunctionOp {
  HostFunction hostFunction{};
  xdr::xvector<SorobanAuthorizationEntry> auth{};

  InvokeHostFunctionOp() = default;
  template<typename _hostFunction_T,
           typename _auth_T,
           typename = typename
           std::enable_if<std::is_constructible<HostFunction, _hostFunction_T>::value
                          && std::is_constructible<xdr::xvector<SorobanAuthorizationEntry>, _auth_T>::value
                         >::type>
  explicit InvokeHostFunctionOp(_hostFunction_T &&_hostFunction,
                                _auth_T &&_auth)
    : hostFunction(std::forward<_hostFunction_T>(_hostFunction)),
      auth(std::forward<_auth_T>(_auth)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::InvokeHostFunctionOp>
  : xdr_struct_base<field_ptr<::stellar::InvokeHostFunctionOp,
                              decltype(::stellar::InvokeHostFunctionOp::hostFunction),
                              &::stellar::InvokeHostFunctionOp::hostFunction>,
                    field_ptr<::stellar::InvokeHostFunctionOp,
                              decltype(::stellar::InvokeHostFunctionOp::auth),
                              &::stellar::InvokeHostFunctionOp::auth>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::InvokeHostFunctionOp &obj) {
    archive(ar, obj.hostFunction, "hostFunction");
    archive(ar, obj.auth, "auth");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::InvokeHostFunctionOp &obj) {
    archive(ar, obj.hostFunction, "hostFunction");
    archive(ar, obj.auth, "auth");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ExtendFootprintTTLOp {
  ExtensionPoint ext{};
  uint32 extendTo{};

  ExtendFootprintTTLOp() = default;
  template<typename _ext_T,
           typename _extendTo_T,
           typename = typename
           std::enable_if<std::is_constructible<ExtensionPoint, _ext_T>::value
                          && std::is_constructible<uint32, _extendTo_T>::value
                         >::type>
  explicit ExtendFootprintTTLOp(_ext_T &&_ext,
                                _extendTo_T &&_extendTo)
    : ext(std::forward<_ext_T>(_ext)),
      extendTo(std::forward<_extendTo_T>(_extendTo)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ExtendFootprintTTLOp>
  : xdr_struct_base<field_ptr<::stellar::ExtendFootprintTTLOp,
                              decltype(::stellar::ExtendFootprintTTLOp::ext),
                              &::stellar::ExtendFootprintTTLOp::ext>,
                    field_ptr<::stellar::ExtendFootprintTTLOp,
                              decltype(::stellar::ExtendFootprintTTLOp::extendTo),
                              &::stellar::ExtendFootprintTTLOp::extendTo>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ExtendFootprintTTLOp &obj) {
    archive(ar, obj.ext, "ext");
    archive(ar, obj.extendTo, "extendTo");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ExtendFootprintTTLOp &obj) {
    archive(ar, obj.ext, "ext");
    archive(ar, obj.extendTo, "extendTo");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct RestoreFootprintOp {
  ExtensionPoint ext{};

  RestoreFootprintOp() = default;
  template<typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<ExtensionPoint, _ext_T>::value
                         >::type>
  explicit RestoreFootprintOp(_ext_T &&_ext)
    : ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::RestoreFootprintOp>
  : xdr_struct_base<field_ptr<::stellar::RestoreFootprintOp,
                              decltype(::stellar::RestoreFootprintOp::ext),
                              &::stellar::RestoreFootprintOp::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::RestoreFootprintOp &obj) {
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::RestoreFootprintOp &obj) {
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct Operation {
  struct _body_t {
    using _xdr_case_type = xdr::xdr_traits<OperationType>::case_type;
  private:
    _xdr_case_type type_;
    union {
      CreateAccountOp createAccountOp_;
      PaymentOp paymentOp_;
      PathPaymentStrictReceiveOp pathPaymentStrictReceiveOp_;
      ManageSellOfferOp manageSellOfferOp_;
      CreatePassiveSellOfferOp createPassiveSellOfferOp_;
      SetOptionsOp setOptionsOp_;
      ChangeTrustOp changeTrustOp_;
      AllowTrustOp allowTrustOp_;
      MuxedAccount destination_;
      ManageDataOp manageDataOp_;
      BumpSequenceOp bumpSequenceOp_;
      ManageBuyOfferOp manageBuyOfferOp_;
      PathPaymentStrictSendOp pathPaymentStrictSendOp_;
      CreateClaimableBalanceOp createClaimableBalanceOp_;
      ClaimClaimableBalanceOp claimClaimableBalanceOp_;
      BeginSponsoringFutureReservesOp beginSponsoringFutureReservesOp_;
      RevokeSponsorshipOp revokeSponsorshipOp_;
      ClawbackOp clawbackOp_;
      ClawbackClaimableBalanceOp clawbackClaimableBalanceOp_;
      SetTrustLineFlagsOp setTrustLineFlagsOp_;
      LiquidityPoolDepositOp liquidityPoolDepositOp_;
      LiquidityPoolWithdrawOp liquidityPoolWithdrawOp_;
      InvokeHostFunctionOp invokeHostFunctionOp_;
      ExtendFootprintTTLOp extendFootprintTTLOp_;
      RestoreFootprintOp restoreFootprintOp_;
    };

  public:
    static Constexpr const bool _xdr_has_default_case = false;
    static const std::vector<OperationType> &_xdr_case_values() {
      static const std::vector<OperationType> _xdr_disc_vec {
        CREATE_ACCOUNT,
        PAYMENT,
        PATH_PAYMENT_STRICT_RECEIVE,
        MANAGE_SELL_OFFER,
        CREATE_PASSIVE_SELL_OFFER,
        SET_OPTIONS,
        CHANGE_TRUST,
        ALLOW_TRUST,
        ACCOUNT_MERGE,
        INFLATION,
        MANAGE_DATA,
        BUMP_SEQUENCE,
        MANAGE_BUY_OFFER,
        PATH_PAYMENT_STRICT_SEND,
        CREATE_CLAIMABLE_BALANCE,
        CLAIM_CLAIMABLE_BALANCE,
        BEGIN_SPONSORING_FUTURE_RESERVES,
        END_SPONSORING_FUTURE_RESERVES,
        REVOKE_SPONSORSHIP,
        CLAWBACK,
        CLAWBACK_CLAIMABLE_BALANCE,
        SET_TRUST_LINE_FLAGS,
        LIQUIDITY_POOL_DEPOSIT,
        LIQUIDITY_POOL_WITHDRAW,
        INVOKE_HOST_FUNCTION,
        EXTEND_FOOTPRINT_TTL,
        RESTORE_FOOTPRINT
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == CREATE_ACCOUNT ? 1
        : which == PAYMENT ? 2
        : which == PATH_PAYMENT_STRICT_RECEIVE ? 3
        : which == MANAGE_SELL_OFFER ? 4
        : which == CREATE_PASSIVE_SELL_OFFER ? 5
        : which == SET_OPTIONS ? 6
        : which == CHANGE_TRUST ? 7
        : which == ALLOW_TRUST ? 8
        : which == ACCOUNT_MERGE ? 9
        : which == INFLATION ? 0
        : which == MANAGE_DATA ? 10
        : which == BUMP_SEQUENCE ? 11
        : which == MANAGE_BUY_OFFER ? 12
        : which == PATH_PAYMENT_STRICT_SEND ? 13
        : which == CREATE_CLAIMABLE_BALANCE ? 14
        : which == CLAIM_CLAIMABLE_BALANCE ? 15
        : which == BEGIN_SPONSORING_FUTURE_RESERVES ? 16
        : which == END_SPONSORING_FUTURE_RESERVES ? 0
        : which == REVOKE_SPONSORSHIP ? 17
        : which == CLAWBACK ? 18
        : which == CLAWBACK_CLAIMABLE_BALANCE ? 19
        : which == SET_TRUST_LINE_FLAGS ? 20
        : which == LIQUIDITY_POOL_DEPOSIT ? 21
        : which == LIQUIDITY_POOL_WITHDRAW ? 22
        : which == INVOKE_HOST_FUNCTION ? 23
        : which == EXTEND_FOOTPRINT_TTL ? 24
        : which == RESTORE_FOOTPRINT ? 25
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case CREATE_ACCOUNT:
        _f(&_body_t::createAccountOp_, std::forward<_A>(_a)...);
        return true;
      case PAYMENT:
        _f(&_body_t::paymentOp_, std::forward<_A>(_a)...);
        return true;
      case PATH_PAYMENT_STRICT_RECEIVE:
        _f(&_body_t::pathPaymentStrictReceiveOp_, std::forward<_A>(_a)...);
        return true;
      case MANAGE_SELL_OFFER:
        _f(&_body_t::manageSellOfferOp_, std::forward<_A>(_a)...);
        return true;
      case CREATE_PASSIVE_SELL_OFFER:
        _f(&_body_t::createPassiveSellOfferOp_, std::forward<_A>(_a)...);
        return true;
      case SET_OPTIONS:
        _f(&_body_t::setOptionsOp_, std::forward<_A>(_a)...);
        return true;
      case CHANGE_TRUST:
        _f(&_body_t::changeTrustOp_, std::forward<_A>(_a)...);
        return true;
      case ALLOW_TRUST:
        _f(&_body_t::allowTrustOp_, std::forward<_A>(_a)...);
        return true;
      case ACCOUNT_MERGE:
        _f(&_body_t::destination_, std::forward<_A>(_a)...);
        return true;
      case INFLATION:
        return true;
      case MANAGE_DATA:
        _f(&_body_t::manageDataOp_, std::forward<_A>(_a)...);
        return true;
      case BUMP_SEQUENCE:
        _f(&_body_t::bumpSequenceOp_, std::forward<_A>(_a)...);
        return true;
      case MANAGE_BUY_OFFER:
        _f(&_body_t::manageBuyOfferOp_, std::forward<_A>(_a)...);
        return true;
      case PATH_PAYMENT_STRICT_SEND:
        _f(&_body_t::pathPaymentStrictSendOp_, std::forward<_A>(_a)...);
        return true;
      case CREATE_CLAIMABLE_BALANCE:
        _f(&_body_t::createClaimableBalanceOp_, std::forward<_A>(_a)...);
        return true;
      case CLAIM_CLAIMABLE_BALANCE:
        _f(&_body_t::claimClaimableBalanceOp_, std::forward<_A>(_a)...);
        return true;
      case BEGIN_SPONSORING_FUTURE_RESERVES:
        _f(&_body_t::beginSponsoringFutureReservesOp_, std::forward<_A>(_a)...);
        return true;
      case END_SPONSORING_FUTURE_RESERVES:
        return true;
      case REVOKE_SPONSORSHIP:
        _f(&_body_t::revokeSponsorshipOp_, std::forward<_A>(_a)...);
        return true;
      case CLAWBACK:
        _f(&_body_t::clawbackOp_, std::forward<_A>(_a)...);
        return true;
      case CLAWBACK_CLAIMABLE_BALANCE:
        _f(&_body_t::clawbackClaimableBalanceOp_, std::forward<_A>(_a)...);
        return true;
      case SET_TRUST_LINE_FLAGS:
        _f(&_body_t::setTrustLineFlagsOp_, std::forward<_A>(_a)...);
        return true;
      case LIQUIDITY_POOL_DEPOSIT:
        _f(&_body_t::liquidityPoolDepositOp_, std::forward<_A>(_a)...);
        return true;
      case LIQUIDITY_POOL_WITHDRAW:
        _f(&_body_t::liquidityPoolWithdrawOp_, std::forward<_A>(_a)...);
        return true;
      case INVOKE_HOST_FUNCTION:
        _f(&_body_t::invokeHostFunctionOp_, std::forward<_A>(_a)...);
        return true;
      case EXTEND_FOOTPRINT_TTL:
        _f(&_body_t::extendFootprintTTLOp_, std::forward<_A>(_a)...);
        return true;
      case RESTORE_FOOTPRINT:
        _f(&_body_t::restoreFootprintOp_, std::forward<_A>(_a)...);
        return true;
      }
      return false;
    }

    _xdr_case_type _xdr_discriminant() const { return type_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of type in _body_t");
      if (fnum != _xdr_field_number(type_)) {
        this->~_body_t();
        type_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
      }
      else
        type_ = which;
    }
    explicit _body_t(OperationType which = OperationType{}) : type_(which) {
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
    }
    _body_t(const _body_t &source) : type_(source.type_) {
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this, source);
    }
    _body_t(_body_t &&source) : type_(source.type_) {
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this,
                        std::move(source));
    }
    ~_body_t() { _xdr_with_mem_ptr(xdr::field_destructor, type_, *this); }
    _body_t &operator=(const _body_t &source) {
      if (_xdr_field_number(type_)
          == _xdr_field_number(source.type_))
        _xdr_with_mem_ptr(xdr::field_assigner, type_, *this, source);
      else {
        this->~_body_t();
        type_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this, source);
      }
      type_ = source.type_;
      return *this;
    }
    _body_t &operator=(_body_t &&source) {
      if (_xdr_field_number(type_)
           == _xdr_field_number(source.type_))
        _xdr_with_mem_ptr(xdr::field_assigner, type_, *this,
                          std::move(source));
      else {
        this->~_body_t();
        type_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this,
                          std::move(source));
      }
      type_ = source.type_;
      return *this;
    }

    OperationType type() const { return OperationType(type_); }
    _body_t &type(OperationType _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant(_xdr_d, _xdr_validate);
      return *this;
    }

    CreateAccountOp &createAccountOp() {
      if (_xdr_field_number(type_) == 1)
        return createAccountOp_;
      throw xdr::xdr_wrong_union("_body_t: createAccountOp accessed when not selected");
    }
    const CreateAccountOp &createAccountOp() const {
      if (_xdr_field_number(type_) == 1)
        return createAccountOp_;
      throw xdr::xdr_wrong_union("_body_t: createAccountOp accessed when not selected");
    }
    PaymentOp &paymentOp() {
      if (_xdr_field_number(type_) == 2)
        return paymentOp_;
      throw xdr::xdr_wrong_union("_body_t: paymentOp accessed when not selected");
    }
    const PaymentOp &paymentOp() const {
      if (_xdr_field_number(type_) == 2)
        return paymentOp_;
      throw xdr::xdr_wrong_union("_body_t: paymentOp accessed when not selected");
    }
    PathPaymentStrictReceiveOp &pathPaymentStrictReceiveOp() {
      if (_xdr_field_number(type_) == 3)
        return pathPaymentStrictReceiveOp_;
      throw xdr::xdr_wrong_union("_body_t: pathPaymentStrictReceiveOp accessed when not selected");
    }
    const PathPaymentStrictReceiveOp &pathPaymentStrictReceiveOp() const {
      if (_xdr_field_number(type_) == 3)
        return pathPaymentStrictReceiveOp_;
      throw xdr::xdr_wrong_union("_body_t: pathPaymentStrictReceiveOp accessed when not selected");
    }
    ManageSellOfferOp &manageSellOfferOp() {
      if (_xdr_field_number(type_) == 4)
        return manageSellOfferOp_;
      throw xdr::xdr_wrong_union("_body_t: manageSellOfferOp accessed when not selected");
    }
    const ManageSellOfferOp &manageSellOfferOp() const {
      if (_xdr_field_number(type_) == 4)
        return manageSellOfferOp_;
      throw xdr::xdr_wrong_union("_body_t: manageSellOfferOp accessed when not selected");
    }
    CreatePassiveSellOfferOp &createPassiveSellOfferOp() {
      if (_xdr_field_number(type_) == 5)
        return createPassiveSellOfferOp_;
      throw xdr::xdr_wrong_union("_body_t: createPassiveSellOfferOp accessed when not selected");
    }
    const CreatePassiveSellOfferOp &createPassiveSellOfferOp() const {
      if (_xdr_field_number(type_) == 5)
        return createPassiveSellOfferOp_;
      throw xdr::xdr_wrong_union("_body_t: createPassiveSellOfferOp accessed when not selected");
    }
    SetOptionsOp &setOptionsOp() {
      if (_xdr_field_number(type_) == 6)
        return setOptionsOp_;
      throw xdr::xdr_wrong_union("_body_t: setOptionsOp accessed when not selected");
    }
    const SetOptionsOp &setOptionsOp() const {
      if (_xdr_field_number(type_) == 6)
        return setOptionsOp_;
      throw xdr::xdr_wrong_union("_body_t: setOptionsOp accessed when not selected");
    }
    ChangeTrustOp &changeTrustOp() {
      if (_xdr_field_number(type_) == 7)
        return changeTrustOp_;
      throw xdr::xdr_wrong_union("_body_t: changeTrustOp accessed when not selected");
    }
    const ChangeTrustOp &changeTrustOp() const {
      if (_xdr_field_number(type_) == 7)
        return changeTrustOp_;
      throw xdr::xdr_wrong_union("_body_t: changeTrustOp accessed when not selected");
    }
    AllowTrustOp &allowTrustOp() {
      if (_xdr_field_number(type_) == 8)
        return allowTrustOp_;
      throw xdr::xdr_wrong_union("_body_t: allowTrustOp accessed when not selected");
    }
    const AllowTrustOp &allowTrustOp() const {
      if (_xdr_field_number(type_) == 8)
        return allowTrustOp_;
      throw xdr::xdr_wrong_union("_body_t: allowTrustOp accessed when not selected");
    }
    MuxedAccount &destination() {
      if (_xdr_field_number(type_) == 9)
        return destination_;
      throw xdr::xdr_wrong_union("_body_t: destination accessed when not selected");
    }
    const MuxedAccount &destination() const {
      if (_xdr_field_number(type_) == 9)
        return destination_;
      throw xdr::xdr_wrong_union("_body_t: destination accessed when not selected");
    }
    ManageDataOp &manageDataOp() {
      if (_xdr_field_number(type_) == 10)
        return manageDataOp_;
      throw xdr::xdr_wrong_union("_body_t: manageDataOp accessed when not selected");
    }
    const ManageDataOp &manageDataOp() const {
      if (_xdr_field_number(type_) == 10)
        return manageDataOp_;
      throw xdr::xdr_wrong_union("_body_t: manageDataOp accessed when not selected");
    }
    BumpSequenceOp &bumpSequenceOp() {
      if (_xdr_field_number(type_) == 11)
        return bumpSequenceOp_;
      throw xdr::xdr_wrong_union("_body_t: bumpSequenceOp accessed when not selected");
    }
    const BumpSequenceOp &bumpSequenceOp() const {
      if (_xdr_field_number(type_) == 11)
        return bumpSequenceOp_;
      throw xdr::xdr_wrong_union("_body_t: bumpSequenceOp accessed when not selected");
    }
    ManageBuyOfferOp &manageBuyOfferOp() {
      if (_xdr_field_number(type_) == 12)
        return manageBuyOfferOp_;
      throw xdr::xdr_wrong_union("_body_t: manageBuyOfferOp accessed when not selected");
    }
    const ManageBuyOfferOp &manageBuyOfferOp() const {
      if (_xdr_field_number(type_) == 12)
        return manageBuyOfferOp_;
      throw xdr::xdr_wrong_union("_body_t: manageBuyOfferOp accessed when not selected");
    }
    PathPaymentStrictSendOp &pathPaymentStrictSendOp() {
      if (_xdr_field_number(type_) == 13)
        return pathPaymentStrictSendOp_;
      throw xdr::xdr_wrong_union("_body_t: pathPaymentStrictSendOp accessed when not selected");
    }
    const PathPaymentStrictSendOp &pathPaymentStrictSendOp() const {
      if (_xdr_field_number(type_) == 13)
        return pathPaymentStrictSendOp_;
      throw xdr::xdr_wrong_union("_body_t: pathPaymentStrictSendOp accessed when not selected");
    }
    CreateClaimableBalanceOp &createClaimableBalanceOp() {
      if (_xdr_field_number(type_) == 14)
        return createClaimableBalanceOp_;
      throw xdr::xdr_wrong_union("_body_t: createClaimableBalanceOp accessed when not selected");
    }
    const CreateClaimableBalanceOp &createClaimableBalanceOp() const {
      if (_xdr_field_number(type_) == 14)
        return createClaimableBalanceOp_;
      throw xdr::xdr_wrong_union("_body_t: createClaimableBalanceOp accessed when not selected");
    }
    ClaimClaimableBalanceOp &claimClaimableBalanceOp() {
      if (_xdr_field_number(type_) == 15)
        return claimClaimableBalanceOp_;
      throw xdr::xdr_wrong_union("_body_t: claimClaimableBalanceOp accessed when not selected");
    }
    const ClaimClaimableBalanceOp &claimClaimableBalanceOp() const {
      if (_xdr_field_number(type_) == 15)
        return claimClaimableBalanceOp_;
      throw xdr::xdr_wrong_union("_body_t: claimClaimableBalanceOp accessed when not selected");
    }
    BeginSponsoringFutureReservesOp &beginSponsoringFutureReservesOp() {
      if (_xdr_field_number(type_) == 16)
        return beginSponsoringFutureReservesOp_;
      throw xdr::xdr_wrong_union("_body_t: beginSponsoringFutureReservesOp accessed when not selected");
    }
    const BeginSponsoringFutureReservesOp &beginSponsoringFutureReservesOp() const {
      if (_xdr_field_number(type_) == 16)
        return beginSponsoringFutureReservesOp_;
      throw xdr::xdr_wrong_union("_body_t: beginSponsoringFutureReservesOp accessed when not selected");
    }
    RevokeSponsorshipOp &revokeSponsorshipOp() {
      if (_xdr_field_number(type_) == 17)
        return revokeSponsorshipOp_;
      throw xdr::xdr_wrong_union("_body_t: revokeSponsorshipOp accessed when not selected");
    }
    const RevokeSponsorshipOp &revokeSponsorshipOp() const {
      if (_xdr_field_number(type_) == 17)
        return revokeSponsorshipOp_;
      throw xdr::xdr_wrong_union("_body_t: revokeSponsorshipOp accessed when not selected");
    }
    ClawbackOp &clawbackOp() {
      if (_xdr_field_number(type_) == 18)
        return clawbackOp_;
      throw xdr::xdr_wrong_union("_body_t: clawbackOp accessed when not selected");
    }
    const ClawbackOp &clawbackOp() const {
      if (_xdr_field_number(type_) == 18)
        return clawbackOp_;
      throw xdr::xdr_wrong_union("_body_t: clawbackOp accessed when not selected");
    }
    ClawbackClaimableBalanceOp &clawbackClaimableBalanceOp() {
      if (_xdr_field_number(type_) == 19)
        return clawbackClaimableBalanceOp_;
      throw xdr::xdr_wrong_union("_body_t: clawbackClaimableBalanceOp accessed when not selected");
    }
    const ClawbackClaimableBalanceOp &clawbackClaimableBalanceOp() const {
      if (_xdr_field_number(type_) == 19)
        return clawbackClaimableBalanceOp_;
      throw xdr::xdr_wrong_union("_body_t: clawbackClaimableBalanceOp accessed when not selected");
    }
    SetTrustLineFlagsOp &setTrustLineFlagsOp() {
      if (_xdr_field_number(type_) == 20)
        return setTrustLineFlagsOp_;
      throw xdr::xdr_wrong_union("_body_t: setTrustLineFlagsOp accessed when not selected");
    }
    const SetTrustLineFlagsOp &setTrustLineFlagsOp() const {
      if (_xdr_field_number(type_) == 20)
        return setTrustLineFlagsOp_;
      throw xdr::xdr_wrong_union("_body_t: setTrustLineFlagsOp accessed when not selected");
    }
    LiquidityPoolDepositOp &liquidityPoolDepositOp() {
      if (_xdr_field_number(type_) == 21)
        return liquidityPoolDepositOp_;
      throw xdr::xdr_wrong_union("_body_t: liquidityPoolDepositOp accessed when not selected");
    }
    const LiquidityPoolDepositOp &liquidityPoolDepositOp() const {
      if (_xdr_field_number(type_) == 21)
        return liquidityPoolDepositOp_;
      throw xdr::xdr_wrong_union("_body_t: liquidityPoolDepositOp accessed when not selected");
    }
    LiquidityPoolWithdrawOp &liquidityPoolWithdrawOp() {
      if (_xdr_field_number(type_) == 22)
        return liquidityPoolWithdrawOp_;
      throw xdr::xdr_wrong_union("_body_t: liquidityPoolWithdrawOp accessed when not selected");
    }
    const LiquidityPoolWithdrawOp &liquidityPoolWithdrawOp() const {
      if (_xdr_field_number(type_) == 22)
        return liquidityPoolWithdrawOp_;
      throw xdr::xdr_wrong_union("_body_t: liquidityPoolWithdrawOp accessed when not selected");
    }
    InvokeHostFunctionOp &invokeHostFunctionOp() {
      if (_xdr_field_number(type_) == 23)
        return invokeHostFunctionOp_;
      throw xdr::xdr_wrong_union("_body_t: invokeHostFunctionOp accessed when not selected");
    }
    const InvokeHostFunctionOp &invokeHostFunctionOp() const {
      if (_xdr_field_number(type_) == 23)
        return invokeHostFunctionOp_;
      throw xdr::xdr_wrong_union("_body_t: invokeHostFunctionOp accessed when not selected");
    }
    ExtendFootprintTTLOp &extendFootprintTTLOp() {
      if (_xdr_field_number(type_) == 24)
        return extendFootprintTTLOp_;
      throw xdr::xdr_wrong_union("_body_t: extendFootprintTTLOp accessed when not selected");
    }
    const ExtendFootprintTTLOp &extendFootprintTTLOp() const {
      if (_xdr_field_number(type_) == 24)
        return extendFootprintTTLOp_;
      throw xdr::xdr_wrong_union("_body_t: extendFootprintTTLOp accessed when not selected");
    }
    RestoreFootprintOp &restoreFootprintOp() {
      if (_xdr_field_number(type_) == 25)
        return restoreFootprintOp_;
      throw xdr::xdr_wrong_union("_body_t: restoreFootprintOp accessed when not selected");
    }
    const RestoreFootprintOp &restoreFootprintOp() const {
      if (_xdr_field_number(type_) == 25)
        return restoreFootprintOp_;
      throw xdr::xdr_wrong_union("_body_t: restoreFootprintOp accessed when not selected");
    }
  };

  xdr::pointer<MuxedAccount> sourceAccount{};
  _body_t body{};

  Operation() = default;
  template<typename _sourceAccount_T,
           typename _body_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::pointer<MuxedAccount>, _sourceAccount_T>::value
                          && std::is_constructible<_body_t, _body_T>::value
                         >::type>
  explicit Operation(_sourceAccount_T &&_sourceAccount,
                     _body_T &&_body)
    : sourceAccount(std::forward<_sourceAccount_T>(_sourceAccount)),
      body(std::forward<_body_T>(_body)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::Operation::_body_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::Operation::_body_t;
  using case_type = ::stellar::Operation::_body_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().type());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "createAccountOp";
    case 2:
      return "paymentOp";
    case 3:
      return "pathPaymentStrictReceiveOp";
    case 4:
      return "manageSellOfferOp";
    case 5:
      return "createPassiveSellOfferOp";
    case 6:
      return "setOptionsOp";
    case 7:
      return "changeTrustOp";
    case 8:
      return "allowTrustOp";
    case 9:
      return "destination";
    case 10:
      return "manageDataOp";
    case 11:
      return "bumpSequenceOp";
    case 12:
      return "manageBuyOfferOp";
    case 13:
      return "pathPaymentStrictSendOp";
    case 14:
      return "createClaimableBalanceOp";
    case 15:
      return "claimClaimableBalanceOp";
    case 16:
      return "beginSponsoringFutureReservesOp";
    case 17:
      return "revokeSponsorshipOp";
    case 18:
      return "clawbackOp";
    case 19:
      return "clawbackClaimableBalanceOp";
    case 20:
      return "setTrustLineFlagsOp";
    case 21:
      return "liquidityPoolDepositOp";
    case 22:
      return "liquidityPoolWithdrawOp";
    case 23:
      return "invokeHostFunctionOp";
    case 24:
      return "extendFootprintTTLOp";
    case 25:
      return "restoreFootprintOp";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::Operation::_body_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of type in _body_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::Operation::_body_t &obj) {
    xdr::archive(ar, obj.type(), "type");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of type in _body_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::Operation::_body_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "type");
    obj.type(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::Operation>
  : xdr_struct_base<field_ptr<::stellar::Operation,
                              decltype(::stellar::Operation::sourceAccount),
                              &::stellar::Operation::sourceAccount>,
                    field_ptr<::stellar::Operation,
                              decltype(::stellar::Operation::body),
                              &::stellar::Operation::body>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::Operation &obj) {
    archive(ar, obj.sourceAccount, "sourceAccount");
    archive(ar, obj.body, "body");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::Operation &obj) {
    archive(ar, obj.sourceAccount, "sourceAccount");
    archive(ar, obj.body, "body");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct HashIDPreimage {
  struct _operationID_t {
    AccountID sourceAccount{};
    SequenceNumber seqNum{};
    uint32 opNum{};

    _operationID_t() = default;
    template<typename _sourceAccount_T,
             typename _seqNum_T,
             typename _opNum_T,
             typename = typename
             std::enable_if<std::is_constructible<AccountID, _sourceAccount_T>::value
                            && std::is_constructible<SequenceNumber, _seqNum_T>::value
                            && std::is_constructible<uint32, _opNum_T>::value
                           >::type>
    explicit _operationID_t(_sourceAccount_T &&_sourceAccount,
                            _seqNum_T &&_seqNum,
                            _opNum_T &&_opNum)
      : sourceAccount(std::forward<_sourceAccount_T>(_sourceAccount)),
        seqNum(std::forward<_seqNum_T>(_seqNum)),
        opNum(std::forward<_opNum_T>(_opNum)) {}
  };
  struct _revokeID_t {
    AccountID sourceAccount{};
    SequenceNumber seqNum{};
    uint32 opNum{};
    PoolID liquidityPoolID{};
    Asset asset{};

    _revokeID_t() = default;
    template<typename _sourceAccount_T,
             typename _seqNum_T,
             typename _opNum_T,
             typename _liquidityPoolID_T,
             typename _asset_T,
             typename = typename
             std::enable_if<std::is_constructible<AccountID, _sourceAccount_T>::value
                            && std::is_constructible<SequenceNumber, _seqNum_T>::value
                            && std::is_constructible<uint32, _opNum_T>::value
                            && std::is_constructible<PoolID, _liquidityPoolID_T>::value
                            && std::is_constructible<Asset, _asset_T>::value
                           >::type>
    explicit _revokeID_t(_sourceAccount_T &&_sourceAccount,
                         _seqNum_T &&_seqNum,
                         _opNum_T &&_opNum,
                         _liquidityPoolID_T &&_liquidityPoolID,
                         _asset_T &&_asset)
      : sourceAccount(std::forward<_sourceAccount_T>(_sourceAccount)),
        seqNum(std::forward<_seqNum_T>(_seqNum)),
        opNum(std::forward<_opNum_T>(_opNum)),
        liquidityPoolID(std::forward<_liquidityPoolID_T>(_liquidityPoolID)),
        asset(std::forward<_asset_T>(_asset)) {}
  };
  struct _contractID_t {
    Hash networkID{};
    ContractIDPreimage contractIDPreimage{};

    _contractID_t() = default;
    template<typename _networkID_T,
             typename _contractIDPreimage_T,
             typename = typename
             std::enable_if<std::is_constructible<Hash, _networkID_T>::value
                            && std::is_constructible<ContractIDPreimage, _contractIDPreimage_T>::value
                           >::type>
    explicit _contractID_t(_networkID_T &&_networkID,
                           _contractIDPreimage_T &&_contractIDPreimage)
      : networkID(std::forward<_networkID_T>(_networkID)),
        contractIDPreimage(std::forward<_contractIDPreimage_T>(_contractIDPreimage)) {}
  };
  struct _sorobanAuthorization_t {
    Hash networkID{};
    int64 nonce{};
    uint32 signatureExpirationLedger{};
    SorobanAuthorizedInvocation invocation{};

    _sorobanAuthorization_t() = default;
    template<typename _networkID_T,
             typename _nonce_T,
             typename _signatureExpirationLedger_T,
             typename _invocation_T,
             typename = typename
             std::enable_if<std::is_constructible<Hash, _networkID_T>::value
                            && std::is_constructible<int64, _nonce_T>::value
                            && std::is_constructible<uint32, _signatureExpirationLedger_T>::value
                            && std::is_constructible<SorobanAuthorizedInvocation, _invocation_T>::value
                           >::type>
    explicit _sorobanAuthorization_t(_networkID_T &&_networkID,
                                     _nonce_T &&_nonce,
                                     _signatureExpirationLedger_T &&_signatureExpirationLedger,
                                     _invocation_T &&_invocation)
      : networkID(std::forward<_networkID_T>(_networkID)),
        nonce(std::forward<_nonce_T>(_nonce)),
        signatureExpirationLedger(std::forward<_signatureExpirationLedger_T>(_signatureExpirationLedger)),
        invocation(std::forward<_invocation_T>(_invocation)) {}
  };

  using _xdr_case_type = xdr::xdr_traits<EnvelopeType>::case_type;
private:
  _xdr_case_type type_;
  union {
    _operationID_t operationID_;
    _revokeID_t revokeID_;
    _contractID_t contractID_;
    _sorobanAuthorization_t sorobanAuthorization_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<EnvelopeType> &_xdr_case_values() {
    static const std::vector<EnvelopeType> _xdr_disc_vec {
      ENVELOPE_TYPE_OP_ID,
      ENVELOPE_TYPE_POOL_REVOKE_OP_ID,
      ENVELOPE_TYPE_CONTRACT_ID,
      ENVELOPE_TYPE_SOROBAN_AUTHORIZATION
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == ENVELOPE_TYPE_OP_ID ? 1
      : which == ENVELOPE_TYPE_POOL_REVOKE_OP_ID ? 2
      : which == ENVELOPE_TYPE_CONTRACT_ID ? 3
      : which == ENVELOPE_TYPE_SOROBAN_AUTHORIZATION ? 4
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case ENVELOPE_TYPE_OP_ID:
      _f(&HashIDPreimage::operationID_, std::forward<_A>(_a)...);
      return true;
    case ENVELOPE_TYPE_POOL_REVOKE_OP_ID:
      _f(&HashIDPreimage::revokeID_, std::forward<_A>(_a)...);
      return true;
    case ENVELOPE_TYPE_CONTRACT_ID:
      _f(&HashIDPreimage::contractID_, std::forward<_A>(_a)...);
      return true;
    case ENVELOPE_TYPE_SOROBAN_AUTHORIZATION:
      _f(&HashIDPreimage::sorobanAuthorization_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return type_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of type in HashIDPreimage");
    if (fnum != _xdr_field_number(type_)) {
      this->~HashIDPreimage();
      type_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
    }
    else
      type_ = which;
  }
  explicit HashIDPreimage(EnvelopeType which = EnvelopeType{}) : type_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
  }
  HashIDPreimage(const HashIDPreimage &source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this, source);
  }
  HashIDPreimage(HashIDPreimage &&source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this,
                      std::move(source));
  }
  ~HashIDPreimage() { _xdr_with_mem_ptr(xdr::field_destructor, type_, *this); }
  HashIDPreimage &operator=(const HashIDPreimage &source) {
    if (_xdr_field_number(type_)
        == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this, source);
    else {
      this->~HashIDPreimage();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this, source);
    }
    type_ = source.type_;
    return *this;
  }
  HashIDPreimage &operator=(HashIDPreimage &&source) {
    if (_xdr_field_number(type_)
         == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this,
                        std::move(source));
    else {
      this->~HashIDPreimage();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this,
                        std::move(source));
    }
    type_ = source.type_;
    return *this;
  }

  EnvelopeType type() const { return EnvelopeType(type_); }
  HashIDPreimage &type(EnvelopeType _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  _operationID_t &operationID() {
    if (_xdr_field_number(type_) == 1)
      return operationID_;
    throw xdr::xdr_wrong_union("HashIDPreimage: operationID accessed when not selected");
  }
  const _operationID_t &operationID() const {
    if (_xdr_field_number(type_) == 1)
      return operationID_;
    throw xdr::xdr_wrong_union("HashIDPreimage: operationID accessed when not selected");
  }
  _revokeID_t &revokeID() {
    if (_xdr_field_number(type_) == 2)
      return revokeID_;
    throw xdr::xdr_wrong_union("HashIDPreimage: revokeID accessed when not selected");
  }
  const _revokeID_t &revokeID() const {
    if (_xdr_field_number(type_) == 2)
      return revokeID_;
    throw xdr::xdr_wrong_union("HashIDPreimage: revokeID accessed when not selected");
  }
  _contractID_t &contractID() {
    if (_xdr_field_number(type_) == 3)
      return contractID_;
    throw xdr::xdr_wrong_union("HashIDPreimage: contractID accessed when not selected");
  }
  const _contractID_t &contractID() const {
    if (_xdr_field_number(type_) == 3)
      return contractID_;
    throw xdr::xdr_wrong_union("HashIDPreimage: contractID accessed when not selected");
  }
  _sorobanAuthorization_t &sorobanAuthorization() {
    if (_xdr_field_number(type_) == 4)
      return sorobanAuthorization_;
    throw xdr::xdr_wrong_union("HashIDPreimage: sorobanAuthorization accessed when not selected");
  }
  const _sorobanAuthorization_t &sorobanAuthorization() const {
    if (_xdr_field_number(type_) == 4)
      return sorobanAuthorization_;
    throw xdr::xdr_wrong_union("HashIDPreimage: sorobanAuthorization accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::HashIDPreimage::_operationID_t>
  : xdr_struct_base<field_ptr<::stellar::HashIDPreimage::_operationID_t,
                              decltype(::stellar::HashIDPreimage::_operationID_t::sourceAccount),
                              &::stellar::HashIDPreimage::_operationID_t::sourceAccount>,
                    field_ptr<::stellar::HashIDPreimage::_operationID_t,
                              decltype(::stellar::HashIDPreimage::_operationID_t::seqNum),
                              &::stellar::HashIDPreimage::_operationID_t::seqNum>,
                    field_ptr<::stellar::HashIDPreimage::_operationID_t,
                              decltype(::stellar::HashIDPreimage::_operationID_t::opNum),
                              &::stellar::HashIDPreimage::_operationID_t::opNum>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::HashIDPreimage::_operationID_t &obj) {
    archive(ar, obj.sourceAccount, "sourceAccount");
    archive(ar, obj.seqNum, "seqNum");
    archive(ar, obj.opNum, "opNum");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::HashIDPreimage::_operationID_t &obj) {
    archive(ar, obj.sourceAccount, "sourceAccount");
    archive(ar, obj.seqNum, "seqNum");
    archive(ar, obj.opNum, "opNum");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::HashIDPreimage::_revokeID_t>
  : xdr_struct_base<field_ptr<::stellar::HashIDPreimage::_revokeID_t,
                              decltype(::stellar::HashIDPreimage::_revokeID_t::sourceAccount),
                              &::stellar::HashIDPreimage::_revokeID_t::sourceAccount>,
                    field_ptr<::stellar::HashIDPreimage::_revokeID_t,
                              decltype(::stellar::HashIDPreimage::_revokeID_t::seqNum),
                              &::stellar::HashIDPreimage::_revokeID_t::seqNum>,
                    field_ptr<::stellar::HashIDPreimage::_revokeID_t,
                              decltype(::stellar::HashIDPreimage::_revokeID_t::opNum),
                              &::stellar::HashIDPreimage::_revokeID_t::opNum>,
                    field_ptr<::stellar::HashIDPreimage::_revokeID_t,
                              decltype(::stellar::HashIDPreimage::_revokeID_t::liquidityPoolID),
                              &::stellar::HashIDPreimage::_revokeID_t::liquidityPoolID>,
                    field_ptr<::stellar::HashIDPreimage::_revokeID_t,
                              decltype(::stellar::HashIDPreimage::_revokeID_t::asset),
                              &::stellar::HashIDPreimage::_revokeID_t::asset>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::HashIDPreimage::_revokeID_t &obj) {
    archive(ar, obj.sourceAccount, "sourceAccount");
    archive(ar, obj.seqNum, "seqNum");
    archive(ar, obj.opNum, "opNum");
    archive(ar, obj.liquidityPoolID, "liquidityPoolID");
    archive(ar, obj.asset, "asset");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::HashIDPreimage::_revokeID_t &obj) {
    archive(ar, obj.sourceAccount, "sourceAccount");
    archive(ar, obj.seqNum, "seqNum");
    archive(ar, obj.opNum, "opNum");
    archive(ar, obj.liquidityPoolID, "liquidityPoolID");
    archive(ar, obj.asset, "asset");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::HashIDPreimage::_contractID_t>
  : xdr_struct_base<field_ptr<::stellar::HashIDPreimage::_contractID_t,
                              decltype(::stellar::HashIDPreimage::_contractID_t::networkID),
                              &::stellar::HashIDPreimage::_contractID_t::networkID>,
                    field_ptr<::stellar::HashIDPreimage::_contractID_t,
                              decltype(::stellar::HashIDPreimage::_contractID_t::contractIDPreimage),
                              &::stellar::HashIDPreimage::_contractID_t::contractIDPreimage>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::HashIDPreimage::_contractID_t &obj) {
    archive(ar, obj.networkID, "networkID");
    archive(ar, obj.contractIDPreimage, "contractIDPreimage");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::HashIDPreimage::_contractID_t &obj) {
    archive(ar, obj.networkID, "networkID");
    archive(ar, obj.contractIDPreimage, "contractIDPreimage");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::HashIDPreimage::_sorobanAuthorization_t>
  : xdr_struct_base<field_ptr<::stellar::HashIDPreimage::_sorobanAuthorization_t,
                              decltype(::stellar::HashIDPreimage::_sorobanAuthorization_t::networkID),
                              &::stellar::HashIDPreimage::_sorobanAuthorization_t::networkID>,
                    field_ptr<::stellar::HashIDPreimage::_sorobanAuthorization_t,
                              decltype(::stellar::HashIDPreimage::_sorobanAuthorization_t::nonce),
                              &::stellar::HashIDPreimage::_sorobanAuthorization_t::nonce>,
                    field_ptr<::stellar::HashIDPreimage::_sorobanAuthorization_t,
                              decltype(::stellar::HashIDPreimage::_sorobanAuthorization_t::signatureExpirationLedger),
                              &::stellar::HashIDPreimage::_sorobanAuthorization_t::signatureExpirationLedger>,
                    field_ptr<::stellar::HashIDPreimage::_sorobanAuthorization_t,
                              decltype(::stellar::HashIDPreimage::_sorobanAuthorization_t::invocation),
                              &::stellar::HashIDPreimage::_sorobanAuthorization_t::invocation>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::HashIDPreimage::_sorobanAuthorization_t &obj) {
    archive(ar, obj.networkID, "networkID");
    archive(ar, obj.nonce, "nonce");
    archive(ar, obj.signatureExpirationLedger, "signatureExpirationLedger");
    archive(ar, obj.invocation, "invocation");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::HashIDPreimage::_sorobanAuthorization_t &obj) {
    archive(ar, obj.networkID, "networkID");
    archive(ar, obj.nonce, "nonce");
    archive(ar, obj.signatureExpirationLedger, "signatureExpirationLedger");
    archive(ar, obj.invocation, "invocation");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::HashIDPreimage> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::HashIDPreimage;
  using case_type = ::stellar::HashIDPreimage::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().type());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "operationID";
    case 2:
      return "revokeID";
    case 3:
      return "contractID";
    case 4:
      return "sorobanAuthorization";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::HashIDPreimage &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of type in HashIDPreimage");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::HashIDPreimage &obj) {
    xdr::archive(ar, obj.type(), "type");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of type in HashIDPreimage");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::HashIDPreimage &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "type");
    obj.type(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

enum MemoType : std::int32_t {
  MEMO_NONE = 0,
  MEMO_TEXT = 1,
  MEMO_ID = 2,
  MEMO_HASH = 3,
  MEMO_RETURN = 4,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::MemoType>
  : xdr_integral_base<::stellar::MemoType, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::MemoType val) {
    switch (val) {
    case ::stellar::MEMO_NONE:
      return "MEMO_NONE";
    case ::stellar::MEMO_TEXT:
      return "MEMO_TEXT";
    case ::stellar::MEMO_ID:
      return "MEMO_ID";
    case ::stellar::MEMO_HASH:
      return "MEMO_HASH";
    case ::stellar::MEMO_RETURN:
      return "MEMO_RETURN";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::MEMO_NONE,
      ::stellar::MEMO_TEXT,
      ::stellar::MEMO_ID,
      ::stellar::MEMO_HASH,
      ::stellar::MEMO_RETURN
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct Memo {
  using _xdr_case_type = xdr::xdr_traits<MemoType>::case_type;
private:
  _xdr_case_type type_;
  union {
    xdr::xstring<28> text_;
    uint64 id_;
    Hash hash_;
    Hash retHash_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<MemoType> &_xdr_case_values() {
    static const std::vector<MemoType> _xdr_disc_vec {
      MEMO_NONE,
      MEMO_TEXT,
      MEMO_ID,
      MEMO_HASH,
      MEMO_RETURN
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == MEMO_NONE ? 0
      : which == MEMO_TEXT ? 1
      : which == MEMO_ID ? 2
      : which == MEMO_HASH ? 3
      : which == MEMO_RETURN ? 4
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case MEMO_NONE:
      return true;
    case MEMO_TEXT:
      _f(&Memo::text_, std::forward<_A>(_a)...);
      return true;
    case MEMO_ID:
      _f(&Memo::id_, std::forward<_A>(_a)...);
      return true;
    case MEMO_HASH:
      _f(&Memo::hash_, std::forward<_A>(_a)...);
      return true;
    case MEMO_RETURN:
      _f(&Memo::retHash_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return type_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of type in Memo");
    if (fnum != _xdr_field_number(type_)) {
      this->~Memo();
      type_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
    }
    else
      type_ = which;
  }
  explicit Memo(MemoType which = MemoType{}) : type_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
  }
  Memo(const Memo &source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this, source);
  }
  Memo(Memo &&source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this,
                      std::move(source));
  }
  ~Memo() { _xdr_with_mem_ptr(xdr::field_destructor, type_, *this); }
  Memo &operator=(const Memo &source) {
    if (_xdr_field_number(type_)
        == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this, source);
    else {
      this->~Memo();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this, source);
    }
    type_ = source.type_;
    return *this;
  }
  Memo &operator=(Memo &&source) {
    if (_xdr_field_number(type_)
         == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this,
                        std::move(source));
    else {
      this->~Memo();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this,
                        std::move(source));
    }
    type_ = source.type_;
    return *this;
  }

  MemoType type() const { return MemoType(type_); }
  Memo &type(MemoType _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  xdr::xstring<28> &text() {
    if (_xdr_field_number(type_) == 1)
      return text_;
    throw xdr::xdr_wrong_union("Memo: text accessed when not selected");
  }
  const xdr::xstring<28> &text() const {
    if (_xdr_field_number(type_) == 1)
      return text_;
    throw xdr::xdr_wrong_union("Memo: text accessed when not selected");
  }
  uint64 &id() {
    if (_xdr_field_number(type_) == 2)
      return id_;
    throw xdr::xdr_wrong_union("Memo: id accessed when not selected");
  }
  const uint64 &id() const {
    if (_xdr_field_number(type_) == 2)
      return id_;
    throw xdr::xdr_wrong_union("Memo: id accessed when not selected");
  }
  Hash &hash() {
    if (_xdr_field_number(type_) == 3)
      return hash_;
    throw xdr::xdr_wrong_union("Memo: hash accessed when not selected");
  }
  const Hash &hash() const {
    if (_xdr_field_number(type_) == 3)
      return hash_;
    throw xdr::xdr_wrong_union("Memo: hash accessed when not selected");
  }
  Hash &retHash() {
    if (_xdr_field_number(type_) == 4)
      return retHash_;
    throw xdr::xdr_wrong_union("Memo: retHash accessed when not selected");
  }
  const Hash &retHash() const {
    if (_xdr_field_number(type_) == 4)
      return retHash_;
    throw xdr::xdr_wrong_union("Memo: retHash accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::Memo> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::Memo;
  using case_type = ::stellar::Memo::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().type());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "text";
    case 2:
      return "id";
    case 3:
      return "hash";
    case 4:
      return "retHash";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::Memo &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of type in Memo");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::Memo &obj) {
    xdr::archive(ar, obj.type(), "type");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of type in Memo");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::Memo &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "type");
    obj.type(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

struct TimeBounds {
  TimePoint minTime{};
  TimePoint maxTime{};

  TimeBounds() = default;
  template<typename _minTime_T,
           typename _maxTime_T,
           typename = typename
           std::enable_if<std::is_constructible<TimePoint, _minTime_T>::value
                          && std::is_constructible<TimePoint, _maxTime_T>::value
                         >::type>
  explicit TimeBounds(_minTime_T &&_minTime,
                      _maxTime_T &&_maxTime)
    : minTime(std::forward<_minTime_T>(_minTime)),
      maxTime(std::forward<_maxTime_T>(_maxTime)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::TimeBounds>
  : xdr_struct_base<field_ptr<::stellar::TimeBounds,
                              decltype(::stellar::TimeBounds::minTime),
                              &::stellar::TimeBounds::minTime>,
                    field_ptr<::stellar::TimeBounds,
                              decltype(::stellar::TimeBounds::maxTime),
                              &::stellar::TimeBounds::maxTime>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::TimeBounds &obj) {
    archive(ar, obj.minTime, "minTime");
    archive(ar, obj.maxTime, "maxTime");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::TimeBounds &obj) {
    archive(ar, obj.minTime, "minTime");
    archive(ar, obj.maxTime, "maxTime");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct LedgerBounds {
  uint32 minLedger{};
  uint32 maxLedger{};

  LedgerBounds() = default;
  template<typename _minLedger_T,
           typename _maxLedger_T,
           typename = typename
           std::enable_if<std::is_constructible<uint32, _minLedger_T>::value
                          && std::is_constructible<uint32, _maxLedger_T>::value
                         >::type>
  explicit LedgerBounds(_minLedger_T &&_minLedger,
                        _maxLedger_T &&_maxLedger)
    : minLedger(std::forward<_minLedger_T>(_minLedger)),
      maxLedger(std::forward<_maxLedger_T>(_maxLedger)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::LedgerBounds>
  : xdr_struct_base<field_ptr<::stellar::LedgerBounds,
                              decltype(::stellar::LedgerBounds::minLedger),
                              &::stellar::LedgerBounds::minLedger>,
                    field_ptr<::stellar::LedgerBounds,
                              decltype(::stellar::LedgerBounds::maxLedger),
                              &::stellar::LedgerBounds::maxLedger>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerBounds &obj) {
    archive(ar, obj.minLedger, "minLedger");
    archive(ar, obj.maxLedger, "maxLedger");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerBounds &obj) {
    archive(ar, obj.minLedger, "minLedger");
    archive(ar, obj.maxLedger, "maxLedger");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct PreconditionsV2 {
  xdr::pointer<TimeBounds> timeBounds{};
  xdr::pointer<LedgerBounds> ledgerBounds{};
  xdr::pointer<SequenceNumber> minSeqNum{};
  Duration minSeqAge{};
  uint32 minSeqLedgerGap{};
  xdr::xvector<SignerKey,2> extraSigners{};

  PreconditionsV2() = default;
  template<typename _timeBounds_T,
           typename _ledgerBounds_T,
           typename _minSeqNum_T,
           typename _minSeqAge_T,
           typename _minSeqLedgerGap_T,
           typename _extraSigners_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::pointer<TimeBounds>, _timeBounds_T>::value
                          && std::is_constructible<xdr::pointer<LedgerBounds>, _ledgerBounds_T>::value
                          && std::is_constructible<xdr::pointer<SequenceNumber>, _minSeqNum_T>::value
                          && std::is_constructible<Duration, _minSeqAge_T>::value
                          && std::is_constructible<uint32, _minSeqLedgerGap_T>::value
                          && std::is_constructible<xdr::xvector<SignerKey,2>, _extraSigners_T>::value
                         >::type>
  explicit PreconditionsV2(_timeBounds_T &&_timeBounds,
                           _ledgerBounds_T &&_ledgerBounds,
                           _minSeqNum_T &&_minSeqNum,
                           _minSeqAge_T &&_minSeqAge,
                           _minSeqLedgerGap_T &&_minSeqLedgerGap,
                           _extraSigners_T &&_extraSigners)
    : timeBounds(std::forward<_timeBounds_T>(_timeBounds)),
      ledgerBounds(std::forward<_ledgerBounds_T>(_ledgerBounds)),
      minSeqNum(std::forward<_minSeqNum_T>(_minSeqNum)),
      minSeqAge(std::forward<_minSeqAge_T>(_minSeqAge)),
      minSeqLedgerGap(std::forward<_minSeqLedgerGap_T>(_minSeqLedgerGap)),
      extraSigners(std::forward<_extraSigners_T>(_extraSigners)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::PreconditionsV2>
  : xdr_struct_base<field_ptr<::stellar::PreconditionsV2,
                              decltype(::stellar::PreconditionsV2::timeBounds),
                              &::stellar::PreconditionsV2::timeBounds>,
                    field_ptr<::stellar::PreconditionsV2,
                              decltype(::stellar::PreconditionsV2::ledgerBounds),
                              &::stellar::PreconditionsV2::ledgerBounds>,
                    field_ptr<::stellar::PreconditionsV2,
                              decltype(::stellar::PreconditionsV2::minSeqNum),
                              &::stellar::PreconditionsV2::minSeqNum>,
                    field_ptr<::stellar::PreconditionsV2,
                              decltype(::stellar::PreconditionsV2::minSeqAge),
                              &::stellar::PreconditionsV2::minSeqAge>,
                    field_ptr<::stellar::PreconditionsV2,
                              decltype(::stellar::PreconditionsV2::minSeqLedgerGap),
                              &::stellar::PreconditionsV2::minSeqLedgerGap>,
                    field_ptr<::stellar::PreconditionsV2,
                              decltype(::stellar::PreconditionsV2::extraSigners),
                              &::stellar::PreconditionsV2::extraSigners>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::PreconditionsV2 &obj) {
    archive(ar, obj.timeBounds, "timeBounds");
    archive(ar, obj.ledgerBounds, "ledgerBounds");
    archive(ar, obj.minSeqNum, "minSeqNum");
    archive(ar, obj.minSeqAge, "minSeqAge");
    archive(ar, obj.minSeqLedgerGap, "minSeqLedgerGap");
    archive(ar, obj.extraSigners, "extraSigners");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::PreconditionsV2 &obj) {
    archive(ar, obj.timeBounds, "timeBounds");
    archive(ar, obj.ledgerBounds, "ledgerBounds");
    archive(ar, obj.minSeqNum, "minSeqNum");
    archive(ar, obj.minSeqAge, "minSeqAge");
    archive(ar, obj.minSeqLedgerGap, "minSeqLedgerGap");
    archive(ar, obj.extraSigners, "extraSigners");
    xdr::validate(obj);
  }
};
} namespace stellar {

enum PreconditionType : std::int32_t {
  PRECOND_NONE = 0,
  PRECOND_TIME = 1,
  PRECOND_V2 = 2,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::PreconditionType>
  : xdr_integral_base<::stellar::PreconditionType, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::PreconditionType val) {
    switch (val) {
    case ::stellar::PRECOND_NONE:
      return "PRECOND_NONE";
    case ::stellar::PRECOND_TIME:
      return "PRECOND_TIME";
    case ::stellar::PRECOND_V2:
      return "PRECOND_V2";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::PRECOND_NONE,
      ::stellar::PRECOND_TIME,
      ::stellar::PRECOND_V2
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct Preconditions {
  using _xdr_case_type = xdr::xdr_traits<PreconditionType>::case_type;
private:
  _xdr_case_type type_;
  union {
    TimeBounds timeBounds_;
    PreconditionsV2 v2_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<PreconditionType> &_xdr_case_values() {
    static const std::vector<PreconditionType> _xdr_disc_vec {
      PRECOND_NONE,
      PRECOND_TIME,
      PRECOND_V2
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == PRECOND_NONE ? 0
      : which == PRECOND_TIME ? 1
      : which == PRECOND_V2 ? 2
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case PRECOND_NONE:
      return true;
    case PRECOND_TIME:
      _f(&Preconditions::timeBounds_, std::forward<_A>(_a)...);
      return true;
    case PRECOND_V2:
      _f(&Preconditions::v2_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return type_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of type in Preconditions");
    if (fnum != _xdr_field_number(type_)) {
      this->~Preconditions();
      type_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
    }
    else
      type_ = which;
  }
  explicit Preconditions(PreconditionType which = PreconditionType{}) : type_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
  }
  Preconditions(const Preconditions &source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this, source);
  }
  Preconditions(Preconditions &&source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this,
                      std::move(source));
  }
  ~Preconditions() { _xdr_with_mem_ptr(xdr::field_destructor, type_, *this); }
  Preconditions &operator=(const Preconditions &source) {
    if (_xdr_field_number(type_)
        == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this, source);
    else {
      this->~Preconditions();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this, source);
    }
    type_ = source.type_;
    return *this;
  }
  Preconditions &operator=(Preconditions &&source) {
    if (_xdr_field_number(type_)
         == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this,
                        std::move(source));
    else {
      this->~Preconditions();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this,
                        std::move(source));
    }
    type_ = source.type_;
    return *this;
  }

  PreconditionType type() const { return PreconditionType(type_); }
  Preconditions &type(PreconditionType _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  TimeBounds &timeBounds() {
    if (_xdr_field_number(type_) == 1)
      return timeBounds_;
    throw xdr::xdr_wrong_union("Preconditions: timeBounds accessed when not selected");
  }
  const TimeBounds &timeBounds() const {
    if (_xdr_field_number(type_) == 1)
      return timeBounds_;
    throw xdr::xdr_wrong_union("Preconditions: timeBounds accessed when not selected");
  }
  PreconditionsV2 &v2() {
    if (_xdr_field_number(type_) == 2)
      return v2_;
    throw xdr::xdr_wrong_union("Preconditions: v2 accessed when not selected");
  }
  const PreconditionsV2 &v2() const {
    if (_xdr_field_number(type_) == 2)
      return v2_;
    throw xdr::xdr_wrong_union("Preconditions: v2 accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::Preconditions> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::Preconditions;
  using case_type = ::stellar::Preconditions::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().type());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "timeBounds";
    case 2:
      return "v2";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::Preconditions &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of type in Preconditions");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::Preconditions &obj) {
    xdr::archive(ar, obj.type(), "type");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of type in Preconditions");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::Preconditions &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "type");
    obj.type(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

struct LedgerFootprint {
  xdr::xvector<LedgerKey> readOnly{};
  xdr::xvector<LedgerKey> readWrite{};

  LedgerFootprint() = default;
  template<typename _readOnly_T,
           typename _readWrite_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::xvector<LedgerKey>, _readOnly_T>::value
                          && std::is_constructible<xdr::xvector<LedgerKey>, _readWrite_T>::value
                         >::type>
  explicit LedgerFootprint(_readOnly_T &&_readOnly,
                           _readWrite_T &&_readWrite)
    : readOnly(std::forward<_readOnly_T>(_readOnly)),
      readWrite(std::forward<_readWrite_T>(_readWrite)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::LedgerFootprint>
  : xdr_struct_base<field_ptr<::stellar::LedgerFootprint,
                              decltype(::stellar::LedgerFootprint::readOnly),
                              &::stellar::LedgerFootprint::readOnly>,
                    field_ptr<::stellar::LedgerFootprint,
                              decltype(::stellar::LedgerFootprint::readWrite),
                              &::stellar::LedgerFootprint::readWrite>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerFootprint &obj) {
    archive(ar, obj.readOnly, "readOnly");
    archive(ar, obj.readWrite, "readWrite");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerFootprint &obj) {
    archive(ar, obj.readOnly, "readOnly");
    archive(ar, obj.readWrite, "readWrite");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct SorobanResources {
  LedgerFootprint footprint{};
  uint32 instructions{};
  uint32 diskReadBytes{};
  uint32 writeBytes{};

  SorobanResources() = default;
  template<typename _footprint_T,
           typename _instructions_T,
           typename _diskReadBytes_T,
           typename _writeBytes_T,
           typename = typename
           std::enable_if<std::is_constructible<LedgerFootprint, _footprint_T>::value
                          && std::is_constructible<uint32, _instructions_T>::value
                          && std::is_constructible<uint32, _diskReadBytes_T>::value
                          && std::is_constructible<uint32, _writeBytes_T>::value
                         >::type>
  explicit SorobanResources(_footprint_T &&_footprint,
                            _instructions_T &&_instructions,
                            _diskReadBytes_T &&_diskReadBytes,
                            _writeBytes_T &&_writeBytes)
    : footprint(std::forward<_footprint_T>(_footprint)),
      instructions(std::forward<_instructions_T>(_instructions)),
      diskReadBytes(std::forward<_diskReadBytes_T>(_diskReadBytes)),
      writeBytes(std::forward<_writeBytes_T>(_writeBytes)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SorobanResources>
  : xdr_struct_base<field_ptr<::stellar::SorobanResources,
                              decltype(::stellar::SorobanResources::footprint),
                              &::stellar::SorobanResources::footprint>,
                    field_ptr<::stellar::SorobanResources,
                              decltype(::stellar::SorobanResources::instructions),
                              &::stellar::SorobanResources::instructions>,
                    field_ptr<::stellar::SorobanResources,
                              decltype(::stellar::SorobanResources::diskReadBytes),
                              &::stellar::SorobanResources::diskReadBytes>,
                    field_ptr<::stellar::SorobanResources,
                              decltype(::stellar::SorobanResources::writeBytes),
                              &::stellar::SorobanResources::writeBytes>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SorobanResources &obj) {
    archive(ar, obj.footprint, "footprint");
    archive(ar, obj.instructions, "instructions");
    archive(ar, obj.diskReadBytes, "diskReadBytes");
    archive(ar, obj.writeBytes, "writeBytes");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SorobanResources &obj) {
    archive(ar, obj.footprint, "footprint");
    archive(ar, obj.instructions, "instructions");
    archive(ar, obj.diskReadBytes, "diskReadBytes");
    archive(ar, obj.writeBytes, "writeBytes");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct SorobanResourcesExtV0 {
  xdr::xvector<uint32> archivedSorobanEntries{};

  SorobanResourcesExtV0() = default;
  template<typename _archivedSorobanEntries_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::xvector<uint32>, _archivedSorobanEntries_T>::value
                         >::type>
  explicit SorobanResourcesExtV0(_archivedSorobanEntries_T &&_archivedSorobanEntries)
    : archivedSorobanEntries(std::forward<_archivedSorobanEntries_T>(_archivedSorobanEntries)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SorobanResourcesExtV0>
  : xdr_struct_base<field_ptr<::stellar::SorobanResourcesExtV0,
                              decltype(::stellar::SorobanResourcesExtV0::archivedSorobanEntries),
                              &::stellar::SorobanResourcesExtV0::archivedSorobanEntries>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SorobanResourcesExtV0 &obj) {
    archive(ar, obj.archivedSorobanEntries, "archivedSorobanEntries");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SorobanResourcesExtV0 &obj) {
    archive(ar, obj.archivedSorobanEntries, "archivedSorobanEntries");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct SorobanTransactionData {
  struct _ext_t {
    using _xdr_case_type = xdr::xdr_traits<int>::case_type;
  private:
    _xdr_case_type v_;
    union {
      SorobanResourcesExtV0 resourceExt_;
    };

  public:
    static Constexpr const bool _xdr_has_default_case = false;
    static const std::vector<int> &_xdr_case_values() {
      static const std::vector<int> _xdr_disc_vec {
        0,
        1
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == 0 ? 0
        : which == 1 ? 1
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case 0:
        return true;
      case 1:
        _f(&_ext_t::resourceExt_, std::forward<_A>(_a)...);
        return true;
      }
      return false;
    }

    _xdr_case_type _xdr_discriminant() const { return v_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of v in _ext_t");
      if (fnum != _xdr_field_number(v_)) {
        this->~_ext_t();
        v_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
      }
      else
        v_ = which;
    }
    explicit _ext_t(std::int32_t which = std::int32_t{}) : v_(which) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
    }
    _ext_t(const _ext_t &source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this, source);
    }
    _ext_t(_ext_t &&source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this,
                        std::move(source));
    }
    ~_ext_t() { _xdr_with_mem_ptr(xdr::field_destructor, v_, *this); }
    _ext_t &operator=(const _ext_t &source) {
      if (_xdr_field_number(v_)
          == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this, source);
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this, source);
      }
      v_ = source.v_;
      return *this;
    }
    _ext_t &operator=(_ext_t &&source) {
      if (_xdr_field_number(v_)
           == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this,
                          std::move(source));
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this,
                          std::move(source));
      }
      v_ = source.v_;
      return *this;
    }

    std::int32_t v() const { return std::int32_t(v_); }
    _ext_t &v(int _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant(_xdr_d, _xdr_validate);
      return *this;
    }

    SorobanResourcesExtV0 &resourceExt() {
      if (_xdr_field_number(v_) == 1)
        return resourceExt_;
      throw xdr::xdr_wrong_union("_ext_t: resourceExt accessed when not selected");
    }
    const SorobanResourcesExtV0 &resourceExt() const {
      if (_xdr_field_number(v_) == 1)
        return resourceExt_;
      throw xdr::xdr_wrong_union("_ext_t: resourceExt accessed when not selected");
    }
  };

  _ext_t ext{};
  SorobanResources resources{};
  int64 resourceFee{};

  SorobanTransactionData() = default;
  template<typename _ext_T,
           typename _resources_T,
           typename _resourceFee_T,
           typename = typename
           std::enable_if<std::is_constructible<_ext_t, _ext_T>::value
                          && std::is_constructible<SorobanResources, _resources_T>::value
                          && std::is_constructible<int64, _resourceFee_T>::value
                         >::type>
  explicit SorobanTransactionData(_ext_T &&_ext,
                                  _resources_T &&_resources,
                                  _resourceFee_T &&_resourceFee)
    : ext(std::forward<_ext_T>(_ext)),
      resources(std::forward<_resources_T>(_resources)),
      resourceFee(std::forward<_resourceFee_T>(_resourceFee)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SorobanTransactionData::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::SorobanTransactionData::_ext_t;
  using case_type = ::stellar::SorobanTransactionData::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "resourceExt";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::SorobanTransactionData::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SorobanTransactionData::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SorobanTransactionData::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.v(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::SorobanTransactionData>
  : xdr_struct_base<field_ptr<::stellar::SorobanTransactionData,
                              decltype(::stellar::SorobanTransactionData::ext),
                              &::stellar::SorobanTransactionData::ext>,
                    field_ptr<::stellar::SorobanTransactionData,
                              decltype(::stellar::SorobanTransactionData::resources),
                              &::stellar::SorobanTransactionData::resources>,
                    field_ptr<::stellar::SorobanTransactionData,
                              decltype(::stellar::SorobanTransactionData::resourceFee),
                              &::stellar::SorobanTransactionData::resourceFee>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SorobanTransactionData &obj) {
    archive(ar, obj.ext, "ext");
    archive(ar, obj.resources, "resources");
    archive(ar, obj.resourceFee, "resourceFee");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SorobanTransactionData &obj) {
    archive(ar, obj.ext, "ext");
    archive(ar, obj.resources, "resources");
    archive(ar, obj.resourceFee, "resourceFee");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct TransactionV0 {
  struct _ext_t {
    using _xdr_case_type = xdr::xdr_traits<int>::case_type;
  private:
    _xdr_case_type v_;
  public:
    static Constexpr const bool _xdr_has_default_case = false;
    static const std::vector<int> &_xdr_case_values() {
      static const std::vector<int> _xdr_disc_vec {
        0
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == 0 ? 0
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case 0:
        return true;
      }
      return false;
    }

    _xdr_case_type _xdr_discriminant() const { return v_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of v in _ext_t");
      if (fnum != _xdr_field_number(v_)) {
        this->~_ext_t();
        v_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
      }
      else
        v_ = which;
    }
    explicit _ext_t(std::int32_t which = std::int32_t{}) : v_(which) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
    }
    _ext_t(const _ext_t &source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this, source);
    }
    _ext_t(_ext_t &&source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this,
                        std::move(source));
    }
    ~_ext_t() { _xdr_with_mem_ptr(xdr::field_destructor, v_, *this); }
    _ext_t &operator=(const _ext_t &source) {
      if (_xdr_field_number(v_)
          == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this, source);
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this, source);
      }
      v_ = source.v_;
      return *this;
    }
    _ext_t &operator=(_ext_t &&source) {
      if (_xdr_field_number(v_)
           == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this,
                          std::move(source));
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this,
                          std::move(source));
      }
      v_ = source.v_;
      return *this;
    }

    std::int32_t v() const { return std::int32_t(v_); }
    _ext_t &v(int _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant(_xdr_d, _xdr_validate);
      return *this;
    }

  };

  uint256 sourceAccountEd25519{};
  uint32 fee{};
  SequenceNumber seqNum{};
  xdr::pointer<TimeBounds> timeBounds{};
  Memo memo{};
  xdr::xvector<Operation,MAX_OPS_PER_TX> operations{};
  _ext_t ext{};

  TransactionV0() = default;
  template<typename _sourceAccountEd25519_T,
           typename _fee_T,
           typename _seqNum_T,
           typename _timeBounds_T,
           typename _memo_T,
           typename _operations_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint256, _sourceAccountEd25519_T>::value
                          && std::is_constructible<uint32, _fee_T>::value
                          && std::is_constructible<SequenceNumber, _seqNum_T>::value
                          && std::is_constructible<xdr::pointer<TimeBounds>, _timeBounds_T>::value
                          && std::is_constructible<Memo, _memo_T>::value
                          && std::is_constructible<xdr::xvector<Operation,MAX_OPS_PER_TX>, _operations_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit TransactionV0(_sourceAccountEd25519_T &&_sourceAccountEd25519,
                         _fee_T &&_fee,
                         _seqNum_T &&_seqNum,
                         _timeBounds_T &&_timeBounds,
                         _memo_T &&_memo,
                         _operations_T &&_operations,
                         _ext_T &&_ext)
    : sourceAccountEd25519(std::forward<_sourceAccountEd25519_T>(_sourceAccountEd25519)),
      fee(std::forward<_fee_T>(_fee)),
      seqNum(std::forward<_seqNum_T>(_seqNum)),
      timeBounds(std::forward<_timeBounds_T>(_timeBounds)),
      memo(std::forward<_memo_T>(_memo)),
      operations(std::forward<_operations_T>(_operations)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::TransactionV0::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::TransactionV0::_ext_t;
  using case_type = ::stellar::TransactionV0::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::TransactionV0::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::TransactionV0::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::TransactionV0::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.v(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::TransactionV0>
  : xdr_struct_base<field_ptr<::stellar::TransactionV0,
                              decltype(::stellar::TransactionV0::sourceAccountEd25519),
                              &::stellar::TransactionV0::sourceAccountEd25519>,
                    field_ptr<::stellar::TransactionV0,
                              decltype(::stellar::TransactionV0::fee),
                              &::stellar::TransactionV0::fee>,
                    field_ptr<::stellar::TransactionV0,
                              decltype(::stellar::TransactionV0::seqNum),
                              &::stellar::TransactionV0::seqNum>,
                    field_ptr<::stellar::TransactionV0,
                              decltype(::stellar::TransactionV0::timeBounds),
                              &::stellar::TransactionV0::timeBounds>,
                    field_ptr<::stellar::TransactionV0,
                              decltype(::stellar::TransactionV0::memo),
                              &::stellar::TransactionV0::memo>,
                    field_ptr<::stellar::TransactionV0,
                              decltype(::stellar::TransactionV0::operations),
                              &::stellar::TransactionV0::operations>,
                    field_ptr<::stellar::TransactionV0,
                              decltype(::stellar::TransactionV0::ext),
                              &::stellar::TransactionV0::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::TransactionV0 &obj) {
    archive(ar, obj.sourceAccountEd25519, "sourceAccountEd25519");
    archive(ar, obj.fee, "fee");
    archive(ar, obj.seqNum, "seqNum");
    archive(ar, obj.timeBounds, "timeBounds");
    archive(ar, obj.memo, "memo");
    archive(ar, obj.operations, "operations");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::TransactionV0 &obj) {
    archive(ar, obj.sourceAccountEd25519, "sourceAccountEd25519");
    archive(ar, obj.fee, "fee");
    archive(ar, obj.seqNum, "seqNum");
    archive(ar, obj.timeBounds, "timeBounds");
    archive(ar, obj.memo, "memo");
    archive(ar, obj.operations, "operations");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct TransactionV0Envelope {
  TransactionV0 tx{};
  xdr::xvector<DecoratedSignature,20> signatures{};

  TransactionV0Envelope() = default;
  template<typename _tx_T,
           typename _signatures_T,
           typename = typename
           std::enable_if<std::is_constructible<TransactionV0, _tx_T>::value
                          && std::is_constructible<xdr::xvector<DecoratedSignature,20>, _signatures_T>::value
                         >::type>
  explicit TransactionV0Envelope(_tx_T &&_tx,
                                 _signatures_T &&_signatures)
    : tx(std::forward<_tx_T>(_tx)),
      signatures(std::forward<_signatures_T>(_signatures)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::TransactionV0Envelope>
  : xdr_struct_base<field_ptr<::stellar::TransactionV0Envelope,
                              decltype(::stellar::TransactionV0Envelope::tx),
                              &::stellar::TransactionV0Envelope::tx>,
                    field_ptr<::stellar::TransactionV0Envelope,
                              decltype(::stellar::TransactionV0Envelope::signatures),
                              &::stellar::TransactionV0Envelope::signatures>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::TransactionV0Envelope &obj) {
    archive(ar, obj.tx, "tx");
    archive(ar, obj.signatures, "signatures");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::TransactionV0Envelope &obj) {
    archive(ar, obj.tx, "tx");
    archive(ar, obj.signatures, "signatures");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct Transaction {
  struct _ext_t {
    using _xdr_case_type = xdr::xdr_traits<int>::case_type;
  private:
    _xdr_case_type v_;
    union {
      SorobanTransactionData sorobanData_;
    };

  public:
    static Constexpr const bool _xdr_has_default_case = false;
    static const std::vector<int> &_xdr_case_values() {
      static const std::vector<int> _xdr_disc_vec {
        0,
        1
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == 0 ? 0
        : which == 1 ? 1
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case 0:
        return true;
      case 1:
        _f(&_ext_t::sorobanData_, std::forward<_A>(_a)...);
        return true;
      }
      return false;
    }

    _xdr_case_type _xdr_discriminant() const { return v_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of v in _ext_t");
      if (fnum != _xdr_field_number(v_)) {
        this->~_ext_t();
        v_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
      }
      else
        v_ = which;
    }
    explicit _ext_t(std::int32_t which = std::int32_t{}) : v_(which) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
    }
    _ext_t(const _ext_t &source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this, source);
    }
    _ext_t(_ext_t &&source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this,
                        std::move(source));
    }
    ~_ext_t() { _xdr_with_mem_ptr(xdr::field_destructor, v_, *this); }
    _ext_t &operator=(const _ext_t &source) {
      if (_xdr_field_number(v_)
          == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this, source);
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this, source);
      }
      v_ = source.v_;
      return *this;
    }
    _ext_t &operator=(_ext_t &&source) {
      if (_xdr_field_number(v_)
           == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this,
                          std::move(source));
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this,
                          std::move(source));
      }
      v_ = source.v_;
      return *this;
    }

    std::int32_t v() const { return std::int32_t(v_); }
    _ext_t &v(int _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant(_xdr_d, _xdr_validate);
      return *this;
    }

    SorobanTransactionData &sorobanData() {
      if (_xdr_field_number(v_) == 1)
        return sorobanData_;
      throw xdr::xdr_wrong_union("_ext_t: sorobanData accessed when not selected");
    }
    const SorobanTransactionData &sorobanData() const {
      if (_xdr_field_number(v_) == 1)
        return sorobanData_;
      throw xdr::xdr_wrong_union("_ext_t: sorobanData accessed when not selected");
    }
  };

  MuxedAccount sourceAccount{};
  uint32 fee{};
  SequenceNumber seqNum{};
  Preconditions cond{};
  Memo memo{};
  xdr::xvector<Operation,MAX_OPS_PER_TX> operations{};
  _ext_t ext{};

  Transaction() = default;
  template<typename _sourceAccount_T,
           typename _fee_T,
           typename _seqNum_T,
           typename _cond_T,
           typename _memo_T,
           typename _operations_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<MuxedAccount, _sourceAccount_T>::value
                          && std::is_constructible<uint32, _fee_T>::value
                          && std::is_constructible<SequenceNumber, _seqNum_T>::value
                          && std::is_constructible<Preconditions, _cond_T>::value
                          && std::is_constructible<Memo, _memo_T>::value
                          && std::is_constructible<xdr::xvector<Operation,MAX_OPS_PER_TX>, _operations_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit Transaction(_sourceAccount_T &&_sourceAccount,
                       _fee_T &&_fee,
                       _seqNum_T &&_seqNum,
                       _cond_T &&_cond,
                       _memo_T &&_memo,
                       _operations_T &&_operations,
                       _ext_T &&_ext)
    : sourceAccount(std::forward<_sourceAccount_T>(_sourceAccount)),
      fee(std::forward<_fee_T>(_fee)),
      seqNum(std::forward<_seqNum_T>(_seqNum)),
      cond(std::forward<_cond_T>(_cond)),
      memo(std::forward<_memo_T>(_memo)),
      operations(std::forward<_operations_T>(_operations)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::Transaction::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::Transaction::_ext_t;
  using case_type = ::stellar::Transaction::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "sorobanData";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::Transaction::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::Transaction::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::Transaction::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.v(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::Transaction>
  : xdr_struct_base<field_ptr<::stellar::Transaction,
                              decltype(::stellar::Transaction::sourceAccount),
                              &::stellar::Transaction::sourceAccount>,
                    field_ptr<::stellar::Transaction,
                              decltype(::stellar::Transaction::fee),
                              &::stellar::Transaction::fee>,
                    field_ptr<::stellar::Transaction,
                              decltype(::stellar::Transaction::seqNum),
                              &::stellar::Transaction::seqNum>,
                    field_ptr<::stellar::Transaction,
                              decltype(::stellar::Transaction::cond),
                              &::stellar::Transaction::cond>,
                    field_ptr<::stellar::Transaction,
                              decltype(::stellar::Transaction::memo),
                              &::stellar::Transaction::memo>,
                    field_ptr<::stellar::Transaction,
                              decltype(::stellar::Transaction::operations),
                              &::stellar::Transaction::operations>,
                    field_ptr<::stellar::Transaction,
                              decltype(::stellar::Transaction::ext),
                              &::stellar::Transaction::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::Transaction &obj) {
    archive(ar, obj.sourceAccount, "sourceAccount");
    archive(ar, obj.fee, "fee");
    archive(ar, obj.seqNum, "seqNum");
    archive(ar, obj.cond, "cond");
    archive(ar, obj.memo, "memo");
    archive(ar, obj.operations, "operations");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::Transaction &obj) {
    archive(ar, obj.sourceAccount, "sourceAccount");
    archive(ar, obj.fee, "fee");
    archive(ar, obj.seqNum, "seqNum");
    archive(ar, obj.cond, "cond");
    archive(ar, obj.memo, "memo");
    archive(ar, obj.operations, "operations");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct TransactionV1Envelope {
  Transaction tx{};
  xdr::xvector<DecoratedSignature,20> signatures{};

  TransactionV1Envelope() = default;
  template<typename _tx_T,
           typename _signatures_T,
           typename = typename
           std::enable_if<std::is_constructible<Transaction, _tx_T>::value
                          && std::is_constructible<xdr::xvector<DecoratedSignature,20>, _signatures_T>::value
                         >::type>
  explicit TransactionV1Envelope(_tx_T &&_tx,
                                 _signatures_T &&_signatures)
    : tx(std::forward<_tx_T>(_tx)),
      signatures(std::forward<_signatures_T>(_signatures)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::TransactionV1Envelope>
  : xdr_struct_base<field_ptr<::stellar::TransactionV1Envelope,
                              decltype(::stellar::TransactionV1Envelope::tx),
                              &::stellar::TransactionV1Envelope::tx>,
                    field_ptr<::stellar::TransactionV1Envelope,
                              decltype(::stellar::TransactionV1Envelope::signatures),
                              &::stellar::TransactionV1Envelope::signatures>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::TransactionV1Envelope &obj) {
    archive(ar, obj.tx, "tx");
    archive(ar, obj.signatures, "signatures");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::TransactionV1Envelope &obj) {
    archive(ar, obj.tx, "tx");
    archive(ar, obj.signatures, "signatures");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct FeeBumpTransaction {
  struct _innerTx_t {
    using _xdr_case_type = xdr::xdr_traits<EnvelopeType>::case_type;
  private:
    _xdr_case_type type_;
    union {
      TransactionV1Envelope v1_;
    };

  public:
    static Constexpr const bool _xdr_has_default_case = false;
    static const std::vector<EnvelopeType> &_xdr_case_values() {
      static const std::vector<EnvelopeType> _xdr_disc_vec {
        ENVELOPE_TYPE_TX
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == ENVELOPE_TYPE_TX ? 1
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case ENVELOPE_TYPE_TX:
        _f(&_innerTx_t::v1_, std::forward<_A>(_a)...);
        return true;
      }
      return false;
    }

    _xdr_case_type _xdr_discriminant() const { return type_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of type in _innerTx_t");
      if (fnum != _xdr_field_number(type_)) {
        this->~_innerTx_t();
        type_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
      }
      else
        type_ = which;
    }
    explicit _innerTx_t(EnvelopeType which = EnvelopeType{}) : type_(which) {
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
    }
    _innerTx_t(const _innerTx_t &source) : type_(source.type_) {
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this, source);
    }
    _innerTx_t(_innerTx_t &&source) : type_(source.type_) {
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this,
                        std::move(source));
    }
    ~_innerTx_t() { _xdr_with_mem_ptr(xdr::field_destructor, type_, *this); }
    _innerTx_t &operator=(const _innerTx_t &source) {
      if (_xdr_field_number(type_)
          == _xdr_field_number(source.type_))
        _xdr_with_mem_ptr(xdr::field_assigner, type_, *this, source);
      else {
        this->~_innerTx_t();
        type_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this, source);
      }
      type_ = source.type_;
      return *this;
    }
    _innerTx_t &operator=(_innerTx_t &&source) {
      if (_xdr_field_number(type_)
           == _xdr_field_number(source.type_))
        _xdr_with_mem_ptr(xdr::field_assigner, type_, *this,
                          std::move(source));
      else {
        this->~_innerTx_t();
        type_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this,
                          std::move(source));
      }
      type_ = source.type_;
      return *this;
    }

    EnvelopeType type() const { return EnvelopeType(type_); }
    _innerTx_t &type(EnvelopeType _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant(_xdr_d, _xdr_validate);
      return *this;
    }

    TransactionV1Envelope &v1() {
      if (_xdr_field_number(type_) == 1)
        return v1_;
      throw xdr::xdr_wrong_union("_innerTx_t: v1 accessed when not selected");
    }
    const TransactionV1Envelope &v1() const {
      if (_xdr_field_number(type_) == 1)
        return v1_;
      throw xdr::xdr_wrong_union("_innerTx_t: v1 accessed when not selected");
    }
  };
  struct _ext_t {
    using _xdr_case_type = xdr::xdr_traits<int>::case_type;
  private:
    _xdr_case_type v_;
  public:
    static Constexpr const bool _xdr_has_default_case = false;
    static const std::vector<int> &_xdr_case_values() {
      static const std::vector<int> _xdr_disc_vec {
        0
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == 0 ? 0
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case 0:
        return true;
      }
      return false;
    }

    _xdr_case_type _xdr_discriminant() const { return v_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of v in _ext_t");
      if (fnum != _xdr_field_number(v_)) {
        this->~_ext_t();
        v_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
      }
      else
        v_ = which;
    }
    explicit _ext_t(std::int32_t which = std::int32_t{}) : v_(which) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
    }
    _ext_t(const _ext_t &source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this, source);
    }
    _ext_t(_ext_t &&source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this,
                        std::move(source));
    }
    ~_ext_t() { _xdr_with_mem_ptr(xdr::field_destructor, v_, *this); }
    _ext_t &operator=(const _ext_t &source) {
      if (_xdr_field_number(v_)
          == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this, source);
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this, source);
      }
      v_ = source.v_;
      return *this;
    }
    _ext_t &operator=(_ext_t &&source) {
      if (_xdr_field_number(v_)
           == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this,
                          std::move(source));
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this,
                          std::move(source));
      }
      v_ = source.v_;
      return *this;
    }

    std::int32_t v() const { return std::int32_t(v_); }
    _ext_t &v(int _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant(_xdr_d, _xdr_validate);
      return *this;
    }

  };

  MuxedAccount feeSource{};
  int64 fee{};
  _innerTx_t innerTx{};
  _ext_t ext{};

  FeeBumpTransaction() = default;
  template<typename _feeSource_T,
           typename _fee_T,
           typename _innerTx_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<MuxedAccount, _feeSource_T>::value
                          && std::is_constructible<int64, _fee_T>::value
                          && std::is_constructible<_innerTx_t, _innerTx_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit FeeBumpTransaction(_feeSource_T &&_feeSource,
                              _fee_T &&_fee,
                              _innerTx_T &&_innerTx,
                              _ext_T &&_ext)
    : feeSource(std::forward<_feeSource_T>(_feeSource)),
      fee(std::forward<_fee_T>(_fee)),
      innerTx(std::forward<_innerTx_T>(_innerTx)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::FeeBumpTransaction::_innerTx_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::FeeBumpTransaction::_innerTx_t;
  using case_type = ::stellar::FeeBumpTransaction::_innerTx_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().type());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "v1";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::FeeBumpTransaction::_innerTx_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of type in _innerTx_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::FeeBumpTransaction::_innerTx_t &obj) {
    xdr::archive(ar, obj.type(), "type");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of type in _innerTx_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::FeeBumpTransaction::_innerTx_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "type");
    obj.type(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::FeeBumpTransaction::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::FeeBumpTransaction::_ext_t;
  using case_type = ::stellar::FeeBumpTransaction::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::FeeBumpTransaction::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::FeeBumpTransaction::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::FeeBumpTransaction::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.v(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::FeeBumpTransaction>
  : xdr_struct_base<field_ptr<::stellar::FeeBumpTransaction,
                              decltype(::stellar::FeeBumpTransaction::feeSource),
                              &::stellar::FeeBumpTransaction::feeSource>,
                    field_ptr<::stellar::FeeBumpTransaction,
                              decltype(::stellar::FeeBumpTransaction::fee),
                              &::stellar::FeeBumpTransaction::fee>,
                    field_ptr<::stellar::FeeBumpTransaction,
                              decltype(::stellar::FeeBumpTransaction::innerTx),
                              &::stellar::FeeBumpTransaction::innerTx>,
                    field_ptr<::stellar::FeeBumpTransaction,
                              decltype(::stellar::FeeBumpTransaction::ext),
                              &::stellar::FeeBumpTransaction::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::FeeBumpTransaction &obj) {
    archive(ar, obj.feeSource, "feeSource");
    archive(ar, obj.fee, "fee");
    archive(ar, obj.innerTx, "innerTx");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::FeeBumpTransaction &obj) {
    archive(ar, obj.feeSource, "feeSource");
    archive(ar, obj.fee, "fee");
    archive(ar, obj.innerTx, "innerTx");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct FeeBumpTransactionEnvelope {
  FeeBumpTransaction tx{};
  xdr::xvector<DecoratedSignature,20> signatures{};

  FeeBumpTransactionEnvelope() = default;
  template<typename _tx_T,
           typename _signatures_T,
           typename = typename
           std::enable_if<std::is_constructible<FeeBumpTransaction, _tx_T>::value
                          && std::is_constructible<xdr::xvector<DecoratedSignature,20>, _signatures_T>::value
                         >::type>
  explicit FeeBumpTransactionEnvelope(_tx_T &&_tx,
                                      _signatures_T &&_signatures)
    : tx(std::forward<_tx_T>(_tx)),
      signatures(std::forward<_signatures_T>(_signatures)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::FeeBumpTransactionEnvelope>
  : xdr_struct_base<field_ptr<::stellar::FeeBumpTransactionEnvelope,
                              decltype(::stellar::FeeBumpTransactionEnvelope::tx),
                              &::stellar::FeeBumpTransactionEnvelope::tx>,
                    field_ptr<::stellar::FeeBumpTransactionEnvelope,
                              decltype(::stellar::FeeBumpTransactionEnvelope::signatures),
                              &::stellar::FeeBumpTransactionEnvelope::signatures>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::FeeBumpTransactionEnvelope &obj) {
    archive(ar, obj.tx, "tx");
    archive(ar, obj.signatures, "signatures");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::FeeBumpTransactionEnvelope &obj) {
    archive(ar, obj.tx, "tx");
    archive(ar, obj.signatures, "signatures");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct TransactionEnvelope {
  using _xdr_case_type = xdr::xdr_traits<EnvelopeType>::case_type;
private:
  _xdr_case_type type_;
  union {
    TransactionV0Envelope v0_;
    TransactionV1Envelope v1_;
    FeeBumpTransactionEnvelope feeBump_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<EnvelopeType> &_xdr_case_values() {
    static const std::vector<EnvelopeType> _xdr_disc_vec {
      ENVELOPE_TYPE_TX_V0,
      ENVELOPE_TYPE_TX,
      ENVELOPE_TYPE_TX_FEE_BUMP
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == ENVELOPE_TYPE_TX_V0 ? 1
      : which == ENVELOPE_TYPE_TX ? 2
      : which == ENVELOPE_TYPE_TX_FEE_BUMP ? 3
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case ENVELOPE_TYPE_TX_V0:
      _f(&TransactionEnvelope::v0_, std::forward<_A>(_a)...);
      return true;
    case ENVELOPE_TYPE_TX:
      _f(&TransactionEnvelope::v1_, std::forward<_A>(_a)...);
      return true;
    case ENVELOPE_TYPE_TX_FEE_BUMP:
      _f(&TransactionEnvelope::feeBump_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return type_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of type in TransactionEnvelope");
    if (fnum != _xdr_field_number(type_)) {
      this->~TransactionEnvelope();
      type_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
    }
    else
      type_ = which;
  }
  explicit TransactionEnvelope(EnvelopeType which = EnvelopeType{}) : type_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
  }
  TransactionEnvelope(const TransactionEnvelope &source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this, source);
  }
  TransactionEnvelope(TransactionEnvelope &&source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this,
                      std::move(source));
  }
  ~TransactionEnvelope() { _xdr_with_mem_ptr(xdr::field_destructor, type_, *this); }
  TransactionEnvelope &operator=(const TransactionEnvelope &source) {
    if (_xdr_field_number(type_)
        == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this, source);
    else {
      this->~TransactionEnvelope();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this, source);
    }
    type_ = source.type_;
    return *this;
  }
  TransactionEnvelope &operator=(TransactionEnvelope &&source) {
    if (_xdr_field_number(type_)
         == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this,
                        std::move(source));
    else {
      this->~TransactionEnvelope();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this,
                        std::move(source));
    }
    type_ = source.type_;
    return *this;
  }

  EnvelopeType type() const { return EnvelopeType(type_); }
  TransactionEnvelope &type(EnvelopeType _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  TransactionV0Envelope &v0() {
    if (_xdr_field_number(type_) == 1)
      return v0_;
    throw xdr::xdr_wrong_union("TransactionEnvelope: v0 accessed when not selected");
  }
  const TransactionV0Envelope &v0() const {
    if (_xdr_field_number(type_) == 1)
      return v0_;
    throw xdr::xdr_wrong_union("TransactionEnvelope: v0 accessed when not selected");
  }
  TransactionV1Envelope &v1() {
    if (_xdr_field_number(type_) == 2)
      return v1_;
    throw xdr::xdr_wrong_union("TransactionEnvelope: v1 accessed when not selected");
  }
  const TransactionV1Envelope &v1() const {
    if (_xdr_field_number(type_) == 2)
      return v1_;
    throw xdr::xdr_wrong_union("TransactionEnvelope: v1 accessed when not selected");
  }
  FeeBumpTransactionEnvelope &feeBump() {
    if (_xdr_field_number(type_) == 3)
      return feeBump_;
    throw xdr::xdr_wrong_union("TransactionEnvelope: feeBump accessed when not selected");
  }
  const FeeBumpTransactionEnvelope &feeBump() const {
    if (_xdr_field_number(type_) == 3)
      return feeBump_;
    throw xdr::xdr_wrong_union("TransactionEnvelope: feeBump accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::TransactionEnvelope> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::TransactionEnvelope;
  using case_type = ::stellar::TransactionEnvelope::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().type());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "v0";
    case 2:
      return "v1";
    case 3:
      return "feeBump";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::TransactionEnvelope &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of type in TransactionEnvelope");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::TransactionEnvelope &obj) {
    xdr::archive(ar, obj.type(), "type");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of type in TransactionEnvelope");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::TransactionEnvelope &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "type");
    obj.type(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

struct TransactionSignaturePayload {
  struct _taggedTransaction_t {
    using _xdr_case_type = xdr::xdr_traits<EnvelopeType>::case_type;
  private:
    _xdr_case_type type_;
    union {
      Transaction tx_;
      FeeBumpTransaction feeBump_;
    };

  public:
    static Constexpr const bool _xdr_has_default_case = false;
    static const std::vector<EnvelopeType> &_xdr_case_values() {
      static const std::vector<EnvelopeType> _xdr_disc_vec {
        ENVELOPE_TYPE_TX,
        ENVELOPE_TYPE_TX_FEE_BUMP
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == ENVELOPE_TYPE_TX ? 1
        : which == ENVELOPE_TYPE_TX_FEE_BUMP ? 2
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case ENVELOPE_TYPE_TX:
        _f(&_taggedTransaction_t::tx_, std::forward<_A>(_a)...);
        return true;
      case ENVELOPE_TYPE_TX_FEE_BUMP:
        _f(&_taggedTransaction_t::feeBump_, std::forward<_A>(_a)...);
        return true;
      }
      return false;
    }

    _xdr_case_type _xdr_discriminant() const { return type_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of type in _taggedTransaction_t");
      if (fnum != _xdr_field_number(type_)) {
        this->~_taggedTransaction_t();
        type_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
      }
      else
        type_ = which;
    }
    explicit _taggedTransaction_t(EnvelopeType which = EnvelopeType{}) : type_(which) {
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
    }
    _taggedTransaction_t(const _taggedTransaction_t &source) : type_(source.type_) {
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this, source);
    }
    _taggedTransaction_t(_taggedTransaction_t &&source) : type_(source.type_) {
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this,
                        std::move(source));
    }
    ~_taggedTransaction_t() { _xdr_with_mem_ptr(xdr::field_destructor, type_, *this); }
    _taggedTransaction_t &operator=(const _taggedTransaction_t &source) {
      if (_xdr_field_number(type_)
          == _xdr_field_number(source.type_))
        _xdr_with_mem_ptr(xdr::field_assigner, type_, *this, source);
      else {
        this->~_taggedTransaction_t();
        type_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this, source);
      }
      type_ = source.type_;
      return *this;
    }
    _taggedTransaction_t &operator=(_taggedTransaction_t &&source) {
      if (_xdr_field_number(type_)
           == _xdr_field_number(source.type_))
        _xdr_with_mem_ptr(xdr::field_assigner, type_, *this,
                          std::move(source));
      else {
        this->~_taggedTransaction_t();
        type_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this,
                          std::move(source));
      }
      type_ = source.type_;
      return *this;
    }

    EnvelopeType type() const { return EnvelopeType(type_); }
    _taggedTransaction_t &type(EnvelopeType _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant(_xdr_d, _xdr_validate);
      return *this;
    }

    Transaction &tx() {
      if (_xdr_field_number(type_) == 1)
        return tx_;
      throw xdr::xdr_wrong_union("_taggedTransaction_t: tx accessed when not selected");
    }
    const Transaction &tx() const {
      if (_xdr_field_number(type_) == 1)
        return tx_;
      throw xdr::xdr_wrong_union("_taggedTransaction_t: tx accessed when not selected");
    }
    FeeBumpTransaction &feeBump() {
      if (_xdr_field_number(type_) == 2)
        return feeBump_;
      throw xdr::xdr_wrong_union("_taggedTransaction_t: feeBump accessed when not selected");
    }
    const FeeBumpTransaction &feeBump() const {
      if (_xdr_field_number(type_) == 2)
        return feeBump_;
      throw xdr::xdr_wrong_union("_taggedTransaction_t: feeBump accessed when not selected");
    }
  };

  Hash networkId{};
  _taggedTransaction_t taggedTransaction{};

  TransactionSignaturePayload() = default;
  template<typename _networkId_T,
           typename _taggedTransaction_T,
           typename = typename
           std::enable_if<std::is_constructible<Hash, _networkId_T>::value
                          && std::is_constructible<_taggedTransaction_t, _taggedTransaction_T>::value
                         >::type>
  explicit TransactionSignaturePayload(_networkId_T &&_networkId,
                                       _taggedTransaction_T &&_taggedTransaction)
    : networkId(std::forward<_networkId_T>(_networkId)),
      taggedTransaction(std::forward<_taggedTransaction_T>(_taggedTransaction)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::TransactionSignaturePayload::_taggedTransaction_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::TransactionSignaturePayload::_taggedTransaction_t;
  using case_type = ::stellar::TransactionSignaturePayload::_taggedTransaction_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().type());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "tx";
    case 2:
      return "feeBump";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::TransactionSignaturePayload::_taggedTransaction_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of type in _taggedTransaction_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::TransactionSignaturePayload::_taggedTransaction_t &obj) {
    xdr::archive(ar, obj.type(), "type");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of type in _taggedTransaction_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::TransactionSignaturePayload::_taggedTransaction_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "type");
    obj.type(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::TransactionSignaturePayload>
  : xdr_struct_base<field_ptr<::stellar::TransactionSignaturePayload,
                              decltype(::stellar::TransactionSignaturePayload::networkId),
                              &::stellar::TransactionSignaturePayload::networkId>,
                    field_ptr<::stellar::TransactionSignaturePayload,
                              decltype(::stellar::TransactionSignaturePayload::taggedTransaction),
                              &::stellar::TransactionSignaturePayload::taggedTransaction>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::TransactionSignaturePayload &obj) {
    archive(ar, obj.networkId, "networkId");
    archive(ar, obj.taggedTransaction, "taggedTransaction");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::TransactionSignaturePayload &obj) {
    archive(ar, obj.networkId, "networkId");
    archive(ar, obj.taggedTransaction, "taggedTransaction");
    xdr::validate(obj);
  }
};
} namespace stellar {

enum ClaimAtomType : std::int32_t {
  CLAIM_ATOM_TYPE_V0 = 0,
  CLAIM_ATOM_TYPE_ORDER_BOOK = 1,
  CLAIM_ATOM_TYPE_LIQUIDITY_POOL = 2,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ClaimAtomType>
  : xdr_integral_base<::stellar::ClaimAtomType, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ClaimAtomType val) {
    switch (val) {
    case ::stellar::CLAIM_ATOM_TYPE_V0:
      return "CLAIM_ATOM_TYPE_V0";
    case ::stellar::CLAIM_ATOM_TYPE_ORDER_BOOK:
      return "CLAIM_ATOM_TYPE_ORDER_BOOK";
    case ::stellar::CLAIM_ATOM_TYPE_LIQUIDITY_POOL:
      return "CLAIM_ATOM_TYPE_LIQUIDITY_POOL";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::CLAIM_ATOM_TYPE_V0,
      ::stellar::CLAIM_ATOM_TYPE_ORDER_BOOK,
      ::stellar::CLAIM_ATOM_TYPE_LIQUIDITY_POOL
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct ClaimOfferAtomV0 {
  uint256 sellerEd25519{};
  int64 offerID{};
  Asset assetSold{};
  int64 amountSold{};
  Asset assetBought{};
  int64 amountBought{};

  ClaimOfferAtomV0() = default;
  template<typename _sellerEd25519_T,
           typename _offerID_T,
           typename _assetSold_T,
           typename _amountSold_T,
           typename _assetBought_T,
           typename _amountBought_T,
           typename = typename
           std::enable_if<std::is_constructible<uint256, _sellerEd25519_T>::value
                          && std::is_constructible<int64, _offerID_T>::value
                          && std::is_constructible<Asset, _assetSold_T>::value
                          && std::is_constructible<int64, _amountSold_T>::value
                          && std::is_constructible<Asset, _assetBought_T>::value
                          && std::is_constructible<int64, _amountBought_T>::value
                         >::type>
  explicit ClaimOfferAtomV0(_sellerEd25519_T &&_sellerEd25519,
                            _offerID_T &&_offerID,
                            _assetSold_T &&_assetSold,
                            _amountSold_T &&_amountSold,
                            _assetBought_T &&_assetBought,
                            _amountBought_T &&_amountBought)
    : sellerEd25519(std::forward<_sellerEd25519_T>(_sellerEd25519)),
      offerID(std::forward<_offerID_T>(_offerID)),
      assetSold(std::forward<_assetSold_T>(_assetSold)),
      amountSold(std::forward<_amountSold_T>(_amountSold)),
      assetBought(std::forward<_assetBought_T>(_assetBought)),
      amountBought(std::forward<_amountBought_T>(_amountBought)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ClaimOfferAtomV0>
  : xdr_struct_base<field_ptr<::stellar::ClaimOfferAtomV0,
                              decltype(::stellar::ClaimOfferAtomV0::sellerEd25519),
                              &::stellar::ClaimOfferAtomV0::sellerEd25519>,
                    field_ptr<::stellar::ClaimOfferAtomV0,
                              decltype(::stellar::ClaimOfferAtomV0::offerID),
                              &::stellar::ClaimOfferAtomV0::offerID>,
                    field_ptr<::stellar::ClaimOfferAtomV0,
                              decltype(::stellar::ClaimOfferAtomV0::assetSold),
                              &::stellar::ClaimOfferAtomV0::assetSold>,
                    field_ptr<::stellar::ClaimOfferAtomV0,
                              decltype(::stellar::ClaimOfferAtomV0::amountSold),
                              &::stellar::ClaimOfferAtomV0::amountSold>,
                    field_ptr<::stellar::ClaimOfferAtomV0,
                              decltype(::stellar::ClaimOfferAtomV0::assetBought),
                              &::stellar::ClaimOfferAtomV0::assetBought>,
                    field_ptr<::stellar::ClaimOfferAtomV0,
                              decltype(::stellar::ClaimOfferAtomV0::amountBought),
                              &::stellar::ClaimOfferAtomV0::amountBought>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ClaimOfferAtomV0 &obj) {
    archive(ar, obj.sellerEd25519, "sellerEd25519");
    archive(ar, obj.offerID, "offerID");
    archive(ar, obj.assetSold, "assetSold");
    archive(ar, obj.amountSold, "amountSold");
    archive(ar, obj.assetBought, "assetBought");
    archive(ar, obj.amountBought, "amountBought");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ClaimOfferAtomV0 &obj) {
    archive(ar, obj.sellerEd25519, "sellerEd25519");
    archive(ar, obj.offerID, "offerID");
    archive(ar, obj.assetSold, "assetSold");
    archive(ar, obj.amountSold, "amountSold");
    archive(ar, obj.assetBought, "assetBought");
    archive(ar, obj.amountBought, "amountBought");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ClaimOfferAtom {
  AccountID sellerID{};
  int64 offerID{};
  Asset assetSold{};
  int64 amountSold{};
  Asset assetBought{};
  int64 amountBought{};

  ClaimOfferAtom() = default;
  template<typename _sellerID_T,
           typename _offerID_T,
           typename _assetSold_T,
           typename _amountSold_T,
           typename _assetBought_T,
           typename _amountBought_T,
           typename = typename
           std::enable_if<std::is_constructible<AccountID, _sellerID_T>::value
                          && std::is_constructible<int64, _offerID_T>::value
                          && std::is_constructible<Asset, _assetSold_T>::value
                          && std::is_constructible<int64, _amountSold_T>::value
                          && std::is_constructible<Asset, _assetBought_T>::value
                          && std::is_constructible<int64, _amountBought_T>::value
                         >::type>
  explicit ClaimOfferAtom(_sellerID_T &&_sellerID,
                          _offerID_T &&_offerID,
                          _assetSold_T &&_assetSold,
                          _amountSold_T &&_amountSold,
                          _assetBought_T &&_assetBought,
                          _amountBought_T &&_amountBought)
    : sellerID(std::forward<_sellerID_T>(_sellerID)),
      offerID(std::forward<_offerID_T>(_offerID)),
      assetSold(std::forward<_assetSold_T>(_assetSold)),
      amountSold(std::forward<_amountSold_T>(_amountSold)),
      assetBought(std::forward<_assetBought_T>(_assetBought)),
      amountBought(std::forward<_amountBought_T>(_amountBought)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ClaimOfferAtom>
  : xdr_struct_base<field_ptr<::stellar::ClaimOfferAtom,
                              decltype(::stellar::ClaimOfferAtom::sellerID),
                              &::stellar::ClaimOfferAtom::sellerID>,
                    field_ptr<::stellar::ClaimOfferAtom,
                              decltype(::stellar::ClaimOfferAtom::offerID),
                              &::stellar::ClaimOfferAtom::offerID>,
                    field_ptr<::stellar::ClaimOfferAtom,
                              decltype(::stellar::ClaimOfferAtom::assetSold),
                              &::stellar::ClaimOfferAtom::assetSold>,
                    field_ptr<::stellar::ClaimOfferAtom,
                              decltype(::stellar::ClaimOfferAtom::amountSold),
                              &::stellar::ClaimOfferAtom::amountSold>,
                    field_ptr<::stellar::ClaimOfferAtom,
                              decltype(::stellar::ClaimOfferAtom::assetBought),
                              &::stellar::ClaimOfferAtom::assetBought>,
                    field_ptr<::stellar::ClaimOfferAtom,
                              decltype(::stellar::ClaimOfferAtom::amountBought),
                              &::stellar::ClaimOfferAtom::amountBought>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ClaimOfferAtom &obj) {
    archive(ar, obj.sellerID, "sellerID");
    archive(ar, obj.offerID, "offerID");
    archive(ar, obj.assetSold, "assetSold");
    archive(ar, obj.amountSold, "amountSold");
    archive(ar, obj.assetBought, "assetBought");
    archive(ar, obj.amountBought, "amountBought");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ClaimOfferAtom &obj) {
    archive(ar, obj.sellerID, "sellerID");
    archive(ar, obj.offerID, "offerID");
    archive(ar, obj.assetSold, "assetSold");
    archive(ar, obj.amountSold, "amountSold");
    archive(ar, obj.assetBought, "assetBought");
    archive(ar, obj.amountBought, "amountBought");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ClaimLiquidityAtom {
  PoolID liquidityPoolID{};
  Asset assetSold{};
  int64 amountSold{};
  Asset assetBought{};
  int64 amountBought{};

  ClaimLiquidityAtom() = default;
  template<typename _liquidityPoolID_T,
           typename _assetSold_T,
           typename _amountSold_T,
           typename _assetBought_T,
           typename _amountBought_T,
           typename = typename
           std::enable_if<std::is_constructible<PoolID, _liquidityPoolID_T>::value
                          && std::is_constructible<Asset, _assetSold_T>::value
                          && std::is_constructible<int64, _amountSold_T>::value
                          && std::is_constructible<Asset, _assetBought_T>::value
                          && std::is_constructible<int64, _amountBought_T>::value
                         >::type>
  explicit ClaimLiquidityAtom(_liquidityPoolID_T &&_liquidityPoolID,
                              _assetSold_T &&_assetSold,
                              _amountSold_T &&_amountSold,
                              _assetBought_T &&_assetBought,
                              _amountBought_T &&_amountBought)
    : liquidityPoolID(std::forward<_liquidityPoolID_T>(_liquidityPoolID)),
      assetSold(std::forward<_assetSold_T>(_assetSold)),
      amountSold(std::forward<_amountSold_T>(_amountSold)),
      assetBought(std::forward<_assetBought_T>(_assetBought)),
      amountBought(std::forward<_amountBought_T>(_amountBought)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ClaimLiquidityAtom>
  : xdr_struct_base<field_ptr<::stellar::ClaimLiquidityAtom,
                              decltype(::stellar::ClaimLiquidityAtom::liquidityPoolID),
                              &::stellar::ClaimLiquidityAtom::liquidityPoolID>,
                    field_ptr<::stellar::ClaimLiquidityAtom,
                              decltype(::stellar::ClaimLiquidityAtom::assetSold),
                              &::stellar::ClaimLiquidityAtom::assetSold>,
                    field_ptr<::stellar::ClaimLiquidityAtom,
                              decltype(::stellar::ClaimLiquidityAtom::amountSold),
                              &::stellar::ClaimLiquidityAtom::amountSold>,
                    field_ptr<::stellar::ClaimLiquidityAtom,
                              decltype(::stellar::ClaimLiquidityAtom::assetBought),
                              &::stellar::ClaimLiquidityAtom::assetBought>,
                    field_ptr<::stellar::ClaimLiquidityAtom,
                              decltype(::stellar::ClaimLiquidityAtom::amountBought),
                              &::stellar::ClaimLiquidityAtom::amountBought>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ClaimLiquidityAtom &obj) {
    archive(ar, obj.liquidityPoolID, "liquidityPoolID");
    archive(ar, obj.assetSold, "assetSold");
    archive(ar, obj.amountSold, "amountSold");
    archive(ar, obj.assetBought, "assetBought");
    archive(ar, obj.amountBought, "amountBought");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ClaimLiquidityAtom &obj) {
    archive(ar, obj.liquidityPoolID, "liquidityPoolID");
    archive(ar, obj.assetSold, "assetSold");
    archive(ar, obj.amountSold, "amountSold");
    archive(ar, obj.assetBought, "assetBought");
    archive(ar, obj.amountBought, "amountBought");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ClaimAtom {
  using _xdr_case_type = xdr::xdr_traits<ClaimAtomType>::case_type;
private:
  _xdr_case_type type_;
  union {
    ClaimOfferAtomV0 v0_;
    ClaimOfferAtom orderBook_;
    ClaimLiquidityAtom liquidityPool_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<ClaimAtomType> &_xdr_case_values() {
    static const std::vector<ClaimAtomType> _xdr_disc_vec {
      CLAIM_ATOM_TYPE_V0,
      CLAIM_ATOM_TYPE_ORDER_BOOK,
      CLAIM_ATOM_TYPE_LIQUIDITY_POOL
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == CLAIM_ATOM_TYPE_V0 ? 1
      : which == CLAIM_ATOM_TYPE_ORDER_BOOK ? 2
      : which == CLAIM_ATOM_TYPE_LIQUIDITY_POOL ? 3
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case CLAIM_ATOM_TYPE_V0:
      _f(&ClaimAtom::v0_, std::forward<_A>(_a)...);
      return true;
    case CLAIM_ATOM_TYPE_ORDER_BOOK:
      _f(&ClaimAtom::orderBook_, std::forward<_A>(_a)...);
      return true;
    case CLAIM_ATOM_TYPE_LIQUIDITY_POOL:
      _f(&ClaimAtom::liquidityPool_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return type_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of type in ClaimAtom");
    if (fnum != _xdr_field_number(type_)) {
      this->~ClaimAtom();
      type_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
    }
    else
      type_ = which;
  }
  explicit ClaimAtom(ClaimAtomType which = ClaimAtomType{}) : type_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
  }
  ClaimAtom(const ClaimAtom &source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this, source);
  }
  ClaimAtom(ClaimAtom &&source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this,
                      std::move(source));
  }
  ~ClaimAtom() { _xdr_with_mem_ptr(xdr::field_destructor, type_, *this); }
  ClaimAtom &operator=(const ClaimAtom &source) {
    if (_xdr_field_number(type_)
        == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this, source);
    else {
      this->~ClaimAtom();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this, source);
    }
    type_ = source.type_;
    return *this;
  }
  ClaimAtom &operator=(ClaimAtom &&source) {
    if (_xdr_field_number(type_)
         == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this,
                        std::move(source));
    else {
      this->~ClaimAtom();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this,
                        std::move(source));
    }
    type_ = source.type_;
    return *this;
  }

  ClaimAtomType type() const { return ClaimAtomType(type_); }
  ClaimAtom &type(ClaimAtomType _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  ClaimOfferAtomV0 &v0() {
    if (_xdr_field_number(type_) == 1)
      return v0_;
    throw xdr::xdr_wrong_union("ClaimAtom: v0 accessed when not selected");
  }
  const ClaimOfferAtomV0 &v0() const {
    if (_xdr_field_number(type_) == 1)
      return v0_;
    throw xdr::xdr_wrong_union("ClaimAtom: v0 accessed when not selected");
  }
  ClaimOfferAtom &orderBook() {
    if (_xdr_field_number(type_) == 2)
      return orderBook_;
    throw xdr::xdr_wrong_union("ClaimAtom: orderBook accessed when not selected");
  }
  const ClaimOfferAtom &orderBook() const {
    if (_xdr_field_number(type_) == 2)
      return orderBook_;
    throw xdr::xdr_wrong_union("ClaimAtom: orderBook accessed when not selected");
  }
  ClaimLiquidityAtom &liquidityPool() {
    if (_xdr_field_number(type_) == 3)
      return liquidityPool_;
    throw xdr::xdr_wrong_union("ClaimAtom: liquidityPool accessed when not selected");
  }
  const ClaimLiquidityAtom &liquidityPool() const {
    if (_xdr_field_number(type_) == 3)
      return liquidityPool_;
    throw xdr::xdr_wrong_union("ClaimAtom: liquidityPool accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ClaimAtom> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ClaimAtom;
  using case_type = ::stellar::ClaimAtom::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().type());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "v0";
    case 2:
      return "orderBook";
    case 3:
      return "liquidityPool";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ClaimAtom &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of type in ClaimAtom");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ClaimAtom &obj) {
    xdr::archive(ar, obj.type(), "type");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of type in ClaimAtom");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ClaimAtom &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "type");
    obj.type(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

enum CreateAccountResultCode : std::int32_t {
  CREATE_ACCOUNT_SUCCESS = 0,
  CREATE_ACCOUNT_MALFORMED = -1,
  CREATE_ACCOUNT_UNDERFUNDED = -2,
  CREATE_ACCOUNT_LOW_RESERVE = -3,
  CREATE_ACCOUNT_ALREADY_EXIST = -4,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateAccountResultCode>
  : xdr_integral_base<::stellar::CreateAccountResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::CreateAccountResultCode val) {
    switch (val) {
    case ::stellar::CREATE_ACCOUNT_SUCCESS:
      return "CREATE_ACCOUNT_SUCCESS";
    case ::stellar::CREATE_ACCOUNT_MALFORMED:
      return "CREATE_ACCOUNT_MALFORMED";
    case ::stellar::CREATE_ACCOUNT_UNDERFUNDED:
      return "CREATE_ACCOUNT_UNDERFUNDED";
    case ::stellar::CREATE_ACCOUNT_LOW_RESERVE:
      return "CREATE_ACCOUNT_LOW_RESERVE";
    case ::stellar::CREATE_ACCOUNT_ALREADY_EXIST:
      return "CREATE_ACCOUNT_ALREADY_EXIST";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::CREATE_ACCOUNT_SUCCESS,
      ::stellar::CREATE_ACCOUNT_MALFORMED,
      ::stellar::CREATE_ACCOUNT_UNDERFUNDED,
      ::stellar::CREATE_ACCOUNT_LOW_RESERVE,
      ::stellar::CREATE_ACCOUNT_ALREADY_EXIST
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct CreateAccountResult {
  using _xdr_case_type = xdr::xdr_traits<CreateAccountResultCode>::case_type;
private:
  _xdr_case_type code_;
public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<CreateAccountResultCode> &_xdr_case_values() {
    static const std::vector<CreateAccountResultCode> _xdr_disc_vec {
      CREATE_ACCOUNT_SUCCESS,
      CREATE_ACCOUNT_MALFORMED,
      CREATE_ACCOUNT_UNDERFUNDED,
      CREATE_ACCOUNT_LOW_RESERVE,
      CREATE_ACCOUNT_ALREADY_EXIST
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == CREATE_ACCOUNT_SUCCESS ? 0
      : which == CREATE_ACCOUNT_MALFORMED || which == CREATE_ACCOUNT_UNDERFUNDED || which == CREATE_ACCOUNT_LOW_RESERVE || which == CREATE_ACCOUNT_ALREADY_EXIST ? 0
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case CREATE_ACCOUNT_SUCCESS:
      return true;
    case CREATE_ACCOUNT_MALFORMED:
    case CREATE_ACCOUNT_UNDERFUNDED:
    case CREATE_ACCOUNT_LOW_RESERVE:
    case CREATE_ACCOUNT_ALREADY_EXIST:
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in CreateAccountResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~CreateAccountResult();
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit CreateAccountResult(CreateAccountResultCode which = CreateAccountResultCode{}) : code_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  CreateAccountResult(const CreateAccountResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  CreateAccountResult(CreateAccountResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~CreateAccountResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  CreateAccountResult &operator=(const CreateAccountResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~CreateAccountResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  CreateAccountResult &operator=(CreateAccountResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~CreateAccountResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
    return *this;
  }

  CreateAccountResultCode code() const { return CreateAccountResultCode(code_); }
  CreateAccountResult &code(CreateAccountResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateAccountResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::CreateAccountResult;
  using case_type = ::stellar::CreateAccountResult::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().code());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::CreateAccountResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in CreateAccountResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateAccountResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in CreateAccountResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateAccountResult &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "code");
    obj.code(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

enum PaymentResultCode : std::int32_t {
  PAYMENT_SUCCESS = 0,
  PAYMENT_MALFORMED = -1,
  PAYMENT_UNDERFUNDED = -2,
  PAYMENT_SRC_NO_TRUST = -3,
  PAYMENT_SRC_NOT_AUTHORIZED = -4,
  PAYMENT_NO_DESTINATION = -5,
  PAYMENT_NO_TRUST = -6,
  PAYMENT_NOT_AUTHORIZED = -7,
  PAYMENT_LINE_FULL = -8,
  PAYMENT_NO_ISSUER = -9,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::PaymentResultCode>
  : xdr_integral_base<::stellar::PaymentResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::PaymentResultCode val) {
    switch (val) {
    case ::stellar::PAYMENT_SUCCESS:
      return "PAYMENT_SUCCESS";
    case ::stellar::PAYMENT_MALFORMED:
      return "PAYMENT_MALFORMED";
    case ::stellar::PAYMENT_UNDERFUNDED:
      return "PAYMENT_UNDERFUNDED";
    case ::stellar::PAYMENT_SRC_NO_TRUST:
      return "PAYMENT_SRC_NO_TRUST";
    case ::stellar::PAYMENT_SRC_NOT_AUTHORIZED:
      return "PAYMENT_SRC_NOT_AUTHORIZED";
    case ::stellar::PAYMENT_NO_DESTINATION:
      return "PAYMENT_NO_DESTINATION";
    case ::stellar::PAYMENT_NO_TRUST:
      return "PAYMENT_NO_TRUST";
    case ::stellar::PAYMENT_NOT_AUTHORIZED:
      return "PAYMENT_NOT_AUTHORIZED";
    case ::stellar::PAYMENT_LINE_FULL:
      return "PAYMENT_LINE_FULL";
    case ::stellar::PAYMENT_NO_ISSUER:
      return "PAYMENT_NO_ISSUER";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::PAYMENT_SUCCESS,
      ::stellar::PAYMENT_MALFORMED,
      ::stellar::PAYMENT_UNDERFUNDED,
      ::stellar::PAYMENT_SRC_NO_TRUST,
      ::stellar::PAYMENT_SRC_NOT_AUTHORIZED,
      ::stellar::PAYMENT_NO_DESTINATION,
      ::stellar::PAYMENT_NO_TRUST,
      ::stellar::PAYMENT_NOT_AUTHORIZED,
      ::stellar::PAYMENT_LINE_FULL,
      ::stellar::PAYMENT_NO_ISSUER
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct PaymentResult {
  using _xdr_case_type = xdr::xdr_traits<PaymentResultCode>::case_type;
private:
  _xdr_case_type code_;
public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<PaymentResultCode> &_xdr_case_values() {
    static const std::vector<PaymentResultCode> _xdr_disc_vec {
      PAYMENT_SUCCESS,
      PAYMENT_MALFORMED,
      PAYMENT_UNDERFUNDED,
      PAYMENT_SRC_NO_TRUST,
      PAYMENT_SRC_NOT_AUTHORIZED,
      PAYMENT_NO_DESTINATION,
      PAYMENT_NO_TRUST,
      PAYMENT_NOT_AUTHORIZED,
      PAYMENT_LINE_FULL,
      PAYMENT_NO_ISSUER
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == PAYMENT_SUCCESS ? 0
      : which == PAYMENT_MALFORMED || which == PAYMENT_UNDERFUNDED || which == PAYMENT_SRC_NO_TRUST || which == PAYMENT_SRC_NOT_AUTHORIZED || which == PAYMENT_NO_DESTINATION || which == PAYMENT_NO_TRUST || which == PAYMENT_NOT_AUTHORIZED || which == PAYMENT_LINE_FULL || which == PAYMENT_NO_ISSUER ? 0
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case PAYMENT_SUCCESS:
      return true;
    case PAYMENT_MALFORMED:
    case PAYMENT_UNDERFUNDED:
    case PAYMENT_SRC_NO_TRUST:
    case PAYMENT_SRC_NOT_AUTHORIZED:
    case PAYMENT_NO_DESTINATION:
    case PAYMENT_NO_TRUST:
    case PAYMENT_NOT_AUTHORIZED:
    case PAYMENT_LINE_FULL:
    case PAYMENT_NO_ISSUER:
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in PaymentResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~PaymentResult();
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit PaymentResult(PaymentResultCode which = PaymentResultCode{}) : code_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  PaymentResult(const PaymentResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  PaymentResult(PaymentResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~PaymentResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  PaymentResult &operator=(const PaymentResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~PaymentResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  PaymentResult &operator=(PaymentResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~PaymentResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
    return *this;
  }

  PaymentResultCode code() const { return PaymentResultCode(code_); }
  PaymentResult &code(PaymentResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

};
} namespace xdr {
template<> struct xdr_traits<::stellar::PaymentResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::PaymentResult;
  using case_type = ::stellar::PaymentResult::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().code());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::PaymentResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in PaymentResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::PaymentResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in PaymentResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::PaymentResult &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "code");
    obj.code(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

enum PathPaymentStrictReceiveResultCode : std::int32_t {
  PATH_PAYMENT_STRICT_RECEIVE_SUCCESS = 0,
  PATH_PAYMENT_STRICT_RECEIVE_MALFORMED = -1,
  PATH_PAYMENT_STRICT_RECEIVE_UNDERFUNDED = -2,
  PATH_PAYMENT_STRICT_RECEIVE_SRC_NO_TRUST = -3,
  PATH_PAYMENT_STRICT_RECEIVE_SRC_NOT_AUTHORIZED = -4,
  PATH_PAYMENT_STRICT_RECEIVE_NO_DESTINATION = -5,
  PATH_PAYMENT_STRICT_RECEIVE_NO_TRUST = -6,
  PATH_PAYMENT_STRICT_RECEIVE_NOT_AUTHORIZED = -7,
  PATH_PAYMENT_STRICT_RECEIVE_LINE_FULL = -8,
  PATH_PAYMENT_STRICT_RECEIVE_NO_ISSUER = -9,
  PATH_PAYMENT_STRICT_RECEIVE_TOO_FEW_OFFERS = -10,
  PATH_PAYMENT_STRICT_RECEIVE_OFFER_CROSS_SELF = -11,
  PATH_PAYMENT_STRICT_RECEIVE_OVER_SENDMAX = -12,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::PathPaymentStrictReceiveResultCode>
  : xdr_integral_base<::stellar::PathPaymentStrictReceiveResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::PathPaymentStrictReceiveResultCode val) {
    switch (val) {
    case ::stellar::PATH_PAYMENT_STRICT_RECEIVE_SUCCESS:
      return "PATH_PAYMENT_STRICT_RECEIVE_SUCCESS";
    case ::stellar::PATH_PAYMENT_STRICT_RECEIVE_MALFORMED:
      return "PATH_PAYMENT_STRICT_RECEIVE_MALFORMED";
    case ::stellar::PATH_PAYMENT_STRICT_RECEIVE_UNDERFUNDED:
      return "PATH_PAYMENT_STRICT_RECEIVE_UNDERFUNDED";
    case ::stellar::PATH_PAYMENT_STRICT_RECEIVE_SRC_NO_TRUST:
      return "PATH_PAYMENT_STRICT_RECEIVE_SRC_NO_TRUST";
    case ::stellar::PATH_PAYMENT_STRICT_RECEIVE_SRC_NOT_AUTHORIZED:
      return "PATH_PAYMENT_STRICT_RECEIVE_SRC_NOT_AUTHORIZED";
    case ::stellar::PATH_PAYMENT_STRICT_RECEIVE_NO_DESTINATION:
      return "PATH_PAYMENT_STRICT_RECEIVE_NO_DESTINATION";
    case ::stellar::PATH_PAYMENT_STRICT_RECEIVE_NO_TRUST:
      return "PATH_PAYMENT_STRICT_RECEIVE_NO_TRUST";
    case ::stellar::PATH_PAYMENT_STRICT_RECEIVE_NOT_AUTHORIZED:
      return "PATH_PAYMENT_STRICT_RECEIVE_NOT_AUTHORIZED";
    case ::stellar::PATH_PAYMENT_STRICT_RECEIVE_LINE_FULL:
      return "PATH_PAYMENT_STRICT_RECEIVE_LINE_FULL";
    case ::stellar::PATH_PAYMENT_STRICT_RECEIVE_NO_ISSUER:
      return "PATH_PAYMENT_STRICT_RECEIVE_NO_ISSUER";
    case ::stellar::PATH_PAYMENT_STRICT_RECEIVE_TOO_FEW_OFFERS:
      return "PATH_PAYMENT_STRICT_RECEIVE_TOO_FEW_OFFERS";
    case ::stellar::PATH_PAYMENT_STRICT_RECEIVE_OFFER_CROSS_SELF:
      return "PATH_PAYMENT_STRICT_RECEIVE_OFFER_CROSS_SELF";
    case ::stellar::PATH_PAYMENT_STRICT_RECEIVE_OVER_SENDMAX:
      return "PATH_PAYMENT_STRICT_RECEIVE_OVER_SENDMAX";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::PATH_PAYMENT_STRICT_RECEIVE_SUCCESS,
      ::stellar::PATH_PAYMENT_STRICT_RECEIVE_MALFORMED,
      ::stellar::PATH_PAYMENT_STRICT_RECEIVE_UNDERFUNDED,
      ::stellar::PATH_PAYMENT_STRICT_RECEIVE_SRC_NO_TRUST,
      ::stellar::PATH_PAYMENT_STRICT_RECEIVE_SRC_NOT_AUTHORIZED,
      ::stellar::PATH_PAYMENT_STRICT_RECEIVE_NO_DESTINATION,
      ::stellar::PATH_PAYMENT_STRICT_RECEIVE_NO_TRUST,
      ::stellar::PATH_PAYMENT_STRICT_RECEIVE_NOT_AUTHORIZED,
      ::stellar::PATH_PAYMENT_STRICT_RECEIVE_LINE_FULL,
      ::stellar::PATH_PAYMENT_STRICT_RECEIVE_NO_ISSUER,
      ::stellar::PATH_PAYMENT_STRICT_RECEIVE_TOO_FEW_OFFERS,
      ::stellar::PATH_PAYMENT_STRICT_RECEIVE_OFFER_CROSS_SELF,
      ::stellar::PATH_PAYMENT_STRICT_RECEIVE_OVER_SENDMAX
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct SimplePaymentResult {
  AccountID destination{};
  Asset asset{};
  int64 amount{};

  SimplePaymentResult() = default;
  template<typename _destination_T,
           typename _asset_T,
           typename _amount_T,
           typename = typename
           std::enable_if<std::is_constructible<AccountID, _destination_T>::value
                          && std::is_constructible<Asset, _asset_T>::value
                          && std::is_constructible<int64, _amount_T>::value
                         >::type>
  explicit SimplePaymentResult(_destination_T &&_destination,
                               _asset_T &&_asset,
                               _amount_T &&_amount)
    : destination(std::forward<_destination_T>(_destination)),
      asset(std::forward<_asset_T>(_asset)),
      amount(std::forward<_amount_T>(_amount)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SimplePaymentResult>
  : xdr_struct_base<field_ptr<::stellar::SimplePaymentResult,
                              decltype(::stellar::SimplePaymentResult::destination),
                              &::stellar::SimplePaymentResult::destination>,
                    field_ptr<::stellar::SimplePaymentResult,
                              decltype(::stellar::SimplePaymentResult::asset),
                              &::stellar::SimplePaymentResult::asset>,
                    field_ptr<::stellar::SimplePaymentResult,
                              decltype(::stellar::SimplePaymentResult::amount),
                              &::stellar::SimplePaymentResult::amount>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SimplePaymentResult &obj) {
    archive(ar, obj.destination, "destination");
    archive(ar, obj.asset, "asset");
    archive(ar, obj.amount, "amount");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SimplePaymentResult &obj) {
    archive(ar, obj.destination, "destination");
    archive(ar, obj.asset, "asset");
    archive(ar, obj.amount, "amount");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct PathPaymentStrictReceiveResult {
  struct _success_t {
    xdr::xvector<ClaimAtom> offers{};
    SimplePaymentResult last{};

    _success_t() = default;
    template<typename _offers_T,
             typename _last_T,
             typename = typename
             std::enable_if<std::is_constructible<xdr::xvector<ClaimAtom>, _offers_T>::value
                            && std::is_constructible<SimplePaymentResult, _last_T>::value
                           >::type>
    explicit _success_t(_offers_T &&_offers,
                        _last_T &&_last)
      : offers(std::forward<_offers_T>(_offers)),
        last(std::forward<_last_T>(_last)) {}
  };

  using _xdr_case_type = xdr::xdr_traits<PathPaymentStrictReceiveResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    _success_t success_;
    Asset noIssuer_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<PathPaymentStrictReceiveResultCode> &_xdr_case_values() {
    static const std::vector<PathPaymentStrictReceiveResultCode> _xdr_disc_vec {
      PATH_PAYMENT_STRICT_RECEIVE_SUCCESS,
      PATH_PAYMENT_STRICT_RECEIVE_MALFORMED,
      PATH_PAYMENT_STRICT_RECEIVE_UNDERFUNDED,
      PATH_PAYMENT_STRICT_RECEIVE_SRC_NO_TRUST,
      PATH_PAYMENT_STRICT_RECEIVE_SRC_NOT_AUTHORIZED,
      PATH_PAYMENT_STRICT_RECEIVE_NO_DESTINATION,
      PATH_PAYMENT_STRICT_RECEIVE_NO_TRUST,
      PATH_PAYMENT_STRICT_RECEIVE_NOT_AUTHORIZED,
      PATH_PAYMENT_STRICT_RECEIVE_LINE_FULL,
      PATH_PAYMENT_STRICT_RECEIVE_NO_ISSUER,
      PATH_PAYMENT_STRICT_RECEIVE_TOO_FEW_OFFERS,
      PATH_PAYMENT_STRICT_RECEIVE_OFFER_CROSS_SELF,
      PATH_PAYMENT_STRICT_RECEIVE_OVER_SENDMAX
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == PATH_PAYMENT_STRICT_RECEIVE_SUCCESS ? 1
      : which == PATH_PAYMENT_STRICT_RECEIVE_MALFORMED || which == PATH_PAYMENT_STRICT_RECEIVE_UNDERFUNDED || which == PATH_PAYMENT_STRICT_RECEIVE_SRC_NO_TRUST || which == PATH_PAYMENT_STRICT_RECEIVE_SRC_NOT_AUTHORIZED || which == PATH_PAYMENT_STRICT_RECEIVE_NO_DESTINATION || which == PATH_PAYMENT_STRICT_RECEIVE_NO_TRUST || which == PATH_PAYMENT_STRICT_RECEIVE_NOT_AUTHORIZED || which == PATH_PAYMENT_STRICT_RECEIVE_LINE_FULL ? 0
      : which == PATH_PAYMENT_STRICT_RECEIVE_NO_ISSUER ? 2
      : which == PATH_PAYMENT_STRICT_RECEIVE_TOO_FEW_OFFERS || which == PATH_PAYMENT_STRICT_RECEIVE_OFFER_CROSS_SELF || which == PATH_PAYMENT_STRICT_RECEIVE_OVER_SENDMAX ? 0
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case PATH_PAYMENT_STRICT_RECEIVE_SUCCESS:
      _f(&PathPaymentStrictReceiveResult::success_, std::forward<_A>(_a)...);
      return true;
    case PATH_PAYMENT_STRICT_RECEIVE_MALFORMED:
    case PATH_PAYMENT_STRICT_RECEIVE_UNDERFUNDED:
    case PATH_PAYMENT_STRICT_RECEIVE_SRC_NO_TRUST:
    case PATH_PAYMENT_STRICT_RECEIVE_SRC_NOT_AUTHORIZED:
    case PATH_PAYMENT_STRICT_RECEIVE_NO_DESTINATION:
    case PATH_PAYMENT_STRICT_RECEIVE_NO_TRUST:
    case PATH_PAYMENT_STRICT_RECEIVE_NOT_AUTHORIZED:
    case PATH_PAYMENT_STRICT_RECEIVE_LINE_FULL:
      return true;
    case PATH_PAYMENT_STRICT_RECEIVE_NO_ISSUER:
      _f(&PathPaymentStrictReceiveResult::noIssuer_, std::forward<_A>(_a)...);
      return true;
    case PATH_PAYMENT_STRICT_RECEIVE_TOO_FEW_OFFERS:
    case PATH_PAYMENT_STRICT_RECEIVE_OFFER_CROSS_SELF:
    case PATH_PAYMENT_STRICT_RECEIVE_OVER_SENDMAX:
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in PathPaymentStrictReceiveResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~PathPaymentStrictReceiveResult();
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit PathPaymentStrictReceiveResult(PathPaymentStrictReceiveResultCode which = PathPaymentStrictReceiveResultCode{}) : code_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  PathPaymentStrictReceiveResult(const PathPaymentStrictReceiveResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  PathPaymentStrictReceiveResult(PathPaymentStrictReceiveResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~PathPaymentStrictReceiveResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  PathPaymentStrictReceiveResult &operator=(const PathPaymentStrictReceiveResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~PathPaymentStrictReceiveResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  PathPaymentStrictReceiveResult &operator=(PathPaymentStrictReceiveResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~PathPaymentStrictReceiveResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
    return *this;
  }

  PathPaymentStrictReceiveResultCode code() const { return PathPaymentStrictReceiveResultCode(code_); }
  PathPaymentStrictReceiveResult &code(PathPaymentStrictReceiveResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  _success_t &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("PathPaymentStrictReceiveResult: success accessed when not selected");
  }
  const _success_t &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("PathPaymentStrictReceiveResult: success accessed when not selected");
  }
  Asset &noIssuer() {
    if (_xdr_field_number(code_) == 2)
      return noIssuer_;
    throw xdr::xdr_wrong_union("PathPaymentStrictReceiveResult: noIssuer accessed when not selected");
  }
  const Asset &noIssuer() const {
    if (_xdr_field_number(code_) == 2)
      return noIssuer_;
    throw xdr::xdr_wrong_union("PathPaymentStrictReceiveResult: noIssuer accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::PathPaymentStrictReceiveResult::_success_t>
  : xdr_struct_base<field_ptr<::stellar::PathPaymentStrictReceiveResult::_success_t,
                              decltype(::stellar::PathPaymentStrictReceiveResult::_success_t::offers),
                              &::stellar::PathPaymentStrictReceiveResult::_success_t::offers>,
                    field_ptr<::stellar::PathPaymentStrictReceiveResult::_success_t,
                              decltype(::stellar::PathPaymentStrictReceiveResult::_success_t::last),
                              &::stellar::PathPaymentStrictReceiveResult::_success_t::last>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::PathPaymentStrictReceiveResult::_success_t &obj) {
    archive(ar, obj.offers, "offers");
    archive(ar, obj.last, "last");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::PathPaymentStrictReceiveResult::_success_t &obj) {
    archive(ar, obj.offers, "offers");
    archive(ar, obj.last, "last");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::PathPaymentStrictReceiveResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::PathPaymentStrictReceiveResult;
  using case_type = ::stellar::PathPaymentStrictReceiveResult::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().code());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "success";
    case 2:
      return "noIssuer";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::PathPaymentStrictReceiveResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in PathPaymentStrictReceiveResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::PathPaymentStrictReceiveResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in PathPaymentStrictReceiveResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::PathPaymentStrictReceiveResult &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "code");
    obj.code(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

enum PathPaymentStrictSendResultCode : std::int32_t {
  PATH_PAYMENT_STRICT_SEND_SUCCESS = 0,
  PATH_PAYMENT_STRICT_SEND_MALFORMED = -1,
  PATH_PAYMENT_STRICT_SEND_UNDERFUNDED = -2,
  PATH_PAYMENT_STRICT_SEND_SRC_NO_TRUST = -3,
  PATH_PAYMENT_STRICT_SEND_SRC_NOT_AUTHORIZED = -4,
  PATH_PAYMENT_STRICT_SEND_NO_DESTINATION = -5,
  PATH_PAYMENT_STRICT_SEND_NO_TRUST = -6,
  PATH_PAYMENT_STRICT_SEND_NOT_AUTHORIZED = -7,
  PATH_PAYMENT_STRICT_SEND_LINE_FULL = -8,
  PATH_PAYMENT_STRICT_SEND_NO_ISSUER = -9,
  PATH_PAYMENT_STRICT_SEND_TOO_FEW_OFFERS = -10,
  PATH_PAYMENT_STRICT_SEND_OFFER_CROSS_SELF = -11,
  PATH_PAYMENT_STRICT_SEND_UNDER_DESTMIN = -12,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::PathPaymentStrictSendResultCode>
  : xdr_integral_base<::stellar::PathPaymentStrictSendResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::PathPaymentStrictSendResultCode val) {
    switch (val) {
    case ::stellar::PATH_PAYMENT_STRICT_SEND_SUCCESS:
      return "PATH_PAYMENT_STRICT_SEND_SUCCESS";
    case ::stellar::PATH_PAYMENT_STRICT_SEND_MALFORMED:
      return "PATH_PAYMENT_STRICT_SEND_MALFORMED";
    case ::stellar::PATH_PAYMENT_STRICT_SEND_UNDERFUNDED:
      return "PATH_PAYMENT_STRICT_SEND_UNDERFUNDED";
    case ::stellar::PATH_PAYMENT_STRICT_SEND_SRC_NO_TRUST:
      return "PATH_PAYMENT_STRICT_SEND_SRC_NO_TRUST";
    case ::stellar::PATH_PAYMENT_STRICT_SEND_SRC_NOT_AUTHORIZED:
      return "PATH_PAYMENT_STRICT_SEND_SRC_NOT_AUTHORIZED";
    case ::stellar::PATH_PAYMENT_STRICT_SEND_NO_DESTINATION:
      return "PATH_PAYMENT_STRICT_SEND_NO_DESTINATION";
    case ::stellar::PATH_PAYMENT_STRICT_SEND_NO_TRUST:
      return "PATH_PAYMENT_STRICT_SEND_NO_TRUST";
    case ::stellar::PATH_PAYMENT_STRICT_SEND_NOT_AUTHORIZED:
      return "PATH_PAYMENT_STRICT_SEND_NOT_AUTHORIZED";
    case ::stellar::PATH_PAYMENT_STRICT_SEND_LINE_FULL:
      return "PATH_PAYMENT_STRICT_SEND_LINE_FULL";
    case ::stellar::PATH_PAYMENT_STRICT_SEND_NO_ISSUER:
      return "PATH_PAYMENT_STRICT_SEND_NO_ISSUER";
    case ::stellar::PATH_PAYMENT_STRICT_SEND_TOO_FEW_OFFERS:
      return "PATH_PAYMENT_STRICT_SEND_TOO_FEW_OFFERS";
    case ::stellar::PATH_PAYMENT_STRICT_SEND_OFFER_CROSS_SELF:
      return "PATH_PAYMENT_STRICT_SEND_OFFER_CROSS_SELF";
    case ::stellar::PATH_PAYMENT_STRICT_SEND_UNDER_DESTMIN:
      return "PATH_PAYMENT_STRICT_SEND_UNDER_DESTMIN";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::PATH_PAYMENT_STRICT_SEND_SUCCESS,
      ::stellar::PATH_PAYMENT_STRICT_SEND_MALFORMED,
      ::stellar::PATH_PAYMENT_STRICT_SEND_UNDERFUNDED,
      ::stellar::PATH_PAYMENT_STRICT_SEND_SRC_NO_TRUST,
      ::stellar::PATH_PAYMENT_STRICT_SEND_SRC_NOT_AUTHORIZED,
      ::stellar::PATH_PAYMENT_STRICT_SEND_NO_DESTINATION,
      ::stellar::PATH_PAYMENT_STRICT_SEND_NO_TRUST,
      ::stellar::PATH_PAYMENT_STRICT_SEND_NOT_AUTHORIZED,
      ::stellar::PATH_PAYMENT_STRICT_SEND_LINE_FULL,
      ::stellar::PATH_PAYMENT_STRICT_SEND_NO_ISSUER,
      ::stellar::PATH_PAYMENT_STRICT_SEND_TOO_FEW_OFFERS,
      ::stellar::PATH_PAYMENT_STRICT_SEND_OFFER_CROSS_SELF,
      ::stellar::PATH_PAYMENT_STRICT_SEND_UNDER_DESTMIN
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct PathPaymentStrictSendResult {
  struct _success_t {
    xdr::xvector<ClaimAtom> offers{};
    SimplePaymentResult last{};

    _success_t() = default;
    template<typename _offers_T,
             typename _last_T,
             typename = typename
             std::enable_if<std::is_constructible<xdr::xvector<ClaimAtom>, _offers_T>::value
                            && std::is_constructible<SimplePaymentResult, _last_T>::value
                           >::type>
    explicit _success_t(_offers_T &&_offers,
                        _last_T &&_last)
      : offers(std::forward<_offers_T>(_offers)),
        last(std::forward<_last_T>(_last)) {}
  };

  using _xdr_case_type = xdr::xdr_traits<PathPaymentStrictSendResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    _success_t success_;
    Asset noIssuer_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<PathPaymentStrictSendResultCode> &_xdr_case_values() {
    static const std::vector<PathPaymentStrictSendResultCode> _xdr_disc_vec {
      PATH_PAYMENT_STRICT_SEND_SUCCESS,
      PATH_PAYMENT_STRICT_SEND_MALFORMED,
      PATH_PAYMENT_STRICT_SEND_UNDERFUNDED,
      PATH_PAYMENT_STRICT_SEND_SRC_NO_TRUST,
      PATH_PAYMENT_STRICT_SEND_SRC_NOT_AUTHORIZED,
      PATH_PAYMENT_STRICT_SEND_NO_DESTINATION,
      PATH_PAYMENT_STRICT_SEND_NO_TRUST,
      PATH_PAYMENT_STRICT_SEND_NOT_AUTHORIZED,
      PATH_PAYMENT_STRICT_SEND_LINE_FULL,
      PATH_PAYMENT_STRICT_SEND_NO_ISSUER,
      PATH_PAYMENT_STRICT_SEND_TOO_FEW_OFFERS,
      PATH_PAYMENT_STRICT_SEND_OFFER_CROSS_SELF,
      PATH_PAYMENT_STRICT_SEND_UNDER_DESTMIN
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == PATH_PAYMENT_STRICT_SEND_SUCCESS ? 1
      : which == PATH_PAYMENT_STRICT_SEND_MALFORMED || which == PATH_PAYMENT_STRICT_SEND_UNDERFUNDED || which == PATH_PAYMENT_STRICT_SEND_SRC_NO_TRUST || which == PATH_PAYMENT_STRICT_SEND_SRC_NOT_AUTHORIZED || which == PATH_PAYMENT_STRICT_SEND_NO_DESTINATION || which == PATH_PAYMENT_STRICT_SEND_NO_TRUST || which == PATH_PAYMENT_STRICT_SEND_NOT_AUTHORIZED || which == PATH_PAYMENT_STRICT_SEND_LINE_FULL ? 0
      : which == PATH_PAYMENT_STRICT_SEND_NO_ISSUER ? 2
      : which == PATH_PAYMENT_STRICT_SEND_TOO_FEW_OFFERS || which == PATH_PAYMENT_STRICT_SEND_OFFER_CROSS_SELF || which == PATH_PAYMENT_STRICT_SEND_UNDER_DESTMIN ? 0
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case PATH_PAYMENT_STRICT_SEND_SUCCESS:
      _f(&PathPaymentStrictSendResult::success_, std::forward<_A>(_a)...);
      return true;
    case PATH_PAYMENT_STRICT_SEND_MALFORMED:
    case PATH_PAYMENT_STRICT_SEND_UNDERFUNDED:
    case PATH_PAYMENT_STRICT_SEND_SRC_NO_TRUST:
    case PATH_PAYMENT_STRICT_SEND_SRC_NOT_AUTHORIZED:
    case PATH_PAYMENT_STRICT_SEND_NO_DESTINATION:
    case PATH_PAYMENT_STRICT_SEND_NO_TRUST:
    case PATH_PAYMENT_STRICT_SEND_NOT_AUTHORIZED:
    case PATH_PAYMENT_STRICT_SEND_LINE_FULL:
      return true;
    case PATH_PAYMENT_STRICT_SEND_NO_ISSUER:
      _f(&PathPaymentStrictSendResult::noIssuer_, std::forward<_A>(_a)...);
      return true;
    case PATH_PAYMENT_STRICT_SEND_TOO_FEW_OFFERS:
    case PATH_PAYMENT_STRICT_SEND_OFFER_CROSS_SELF:
    case PATH_PAYMENT_STRICT_SEND_UNDER_DESTMIN:
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in PathPaymentStrictSendResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~PathPaymentStrictSendResult();
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit PathPaymentStrictSendResult(PathPaymentStrictSendResultCode which = PathPaymentStrictSendResultCode{}) : code_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  PathPaymentStrictSendResult(const PathPaymentStrictSendResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  PathPaymentStrictSendResult(PathPaymentStrictSendResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~PathPaymentStrictSendResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  PathPaymentStrictSendResult &operator=(const PathPaymentStrictSendResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~PathPaymentStrictSendResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  PathPaymentStrictSendResult &operator=(PathPaymentStrictSendResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~PathPaymentStrictSendResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
    return *this;
  }

  PathPaymentStrictSendResultCode code() const { return PathPaymentStrictSendResultCode(code_); }
  PathPaymentStrictSendResult &code(PathPaymentStrictSendResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  _success_t &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("PathPaymentStrictSendResult: success accessed when not selected");
  }
  const _success_t &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("PathPaymentStrictSendResult: success accessed when not selected");
  }
  Asset &noIssuer() {
    if (_xdr_field_number(code_) == 2)
      return noIssuer_;
    throw xdr::xdr_wrong_union("PathPaymentStrictSendResult: noIssuer accessed when not selected");
  }
  const Asset &noIssuer() const {
    if (_xdr_field_number(code_) == 2)
      return noIssuer_;
    throw xdr::xdr_wrong_union("PathPaymentStrictSendResult: noIssuer accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::PathPaymentStrictSendResult::_success_t>
  : xdr_struct_base<field_ptr<::stellar::PathPaymentStrictSendResult::_success_t,
                              decltype(::stellar::PathPaymentStrictSendResult::_success_t::offers),
                              &::stellar::PathPaymentStrictSendResult::_success_t::offers>,
                    field_ptr<::stellar::PathPaymentStrictSendResult::_success_t,
                              decltype(::stellar::PathPaymentStrictSendResult::_success_t::last),
                              &::stellar::PathPaymentStrictSendResult::_success_t::last>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::PathPaymentStrictSendResult::_success_t &obj) {
    archive(ar, obj.offers, "offers");
    archive(ar, obj.last, "last");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::PathPaymentStrictSendResult::_success_t &obj) {
    archive(ar, obj.offers, "offers");
    archive(ar, obj.last, "last");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::PathPaymentStrictSendResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::PathPaymentStrictSendResult;
  using case_type = ::stellar::PathPaymentStrictSendResult::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().code());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "success";
    case 2:
      return "noIssuer";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::PathPaymentStrictSendResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in PathPaymentStrictSendResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::PathPaymentStrictSendResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in PathPaymentStrictSendResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::PathPaymentStrictSendResult &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "code");
    obj.code(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

enum ManageSellOfferResultCode : std::int32_t {
  MANAGE_SELL_OFFER_SUCCESS = 0,
  MANAGE_SELL_OFFER_MALFORMED = -1,
  MANAGE_SELL_OFFER_SELL_NO_TRUST = -2,
  MANAGE_SELL_OFFER_BUY_NO_TRUST = -3,
  MANAGE_SELL_OFFER_SELL_NOT_AUTHORIZED = -4,
  MANAGE_SELL_OFFER_BUY_NOT_AUTHORIZED = -5,
  MANAGE_SELL_OFFER_LINE_FULL = -6,
  MANAGE_SELL_OFFER_UNDERFUNDED = -7,
  MANAGE_SELL_OFFER_CROSS_SELF = -8,
  MANAGE_SELL_OFFER_SELL_NO_ISSUER = -9,
  MANAGE_SELL_OFFER_BUY_NO_ISSUER = -10,
  MANAGE_SELL_OFFER_NOT_FOUND = -11,
  MANAGE_SELL_OFFER_LOW_RESERVE = -12,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageSellOfferResultCode>
  : xdr_integral_base<::stellar::ManageSellOfferResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageSellOfferResultCode val) {
    switch (val) {
    case ::stellar::MANAGE_SELL_OFFER_SUCCESS:
      return "MANAGE_SELL_OFFER_SUCCESS";
    case ::stellar::MANAGE_SELL_OFFER_MALFORMED:
      return "MANAGE_SELL_OFFER_MALFORMED";
    case ::stellar::MANAGE_SELL_OFFER_SELL_NO_TRUST:
      return "MANAGE_SELL_OFFER_SELL_NO_TRUST";
    case ::stellar::MANAGE_SELL_OFFER_BUY_NO_TRUST:
      return "MANAGE_SELL_OFFER_BUY_NO_TRUST";
    case ::stellar::MANAGE_SELL_OFFER_SELL_NOT_AUTHORIZED:
      return "MANAGE_SELL_OFFER_SELL_NOT_AUTHORIZED";
    case ::stellar::MANAGE_SELL_OFFER_BUY_NOT_AUTHORIZED:
      return "MANAGE_SELL_OFFER_BUY_NOT_AUTHORIZED";
    case ::stellar::MANAGE_SELL_OFFER_LINE_FULL:
      return "MANAGE_SELL_OFFER_LINE_FULL";
    case ::stellar::MANAGE_SELL_OFFER_UNDERFUNDED:
      return "MANAGE_SELL_OFFER_UNDERFUNDED";
    case ::stellar::MANAGE_SELL_OFFER_CROSS_SELF:
      return "MANAGE_SELL_OFFER_CROSS_SELF";
    case ::stellar::MANAGE_SELL_OFFER_SELL_NO_ISSUER:
      return "MANAGE_SELL_OFFER_SELL_NO_ISSUER";
    case ::stellar::MANAGE_SELL_OFFER_BUY_NO_ISSUER:
      return "MANAGE_SELL_OFFER_BUY_NO_ISSUER";
    case ::stellar::MANAGE_SELL_OFFER_NOT_FOUND:
      return "MANAGE_SELL_OFFER_NOT_FOUND";
    case ::stellar::MANAGE_SELL_OFFER_LOW_RESERVE:
      return "MANAGE_SELL_OFFER_LOW_RESERVE";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::MANAGE_SELL_OFFER_SUCCESS,
      ::stellar::MANAGE_SELL_OFFER_MALFORMED,
      ::stellar::MANAGE_SELL_OFFER_SELL_NO_TRUST,
      ::stellar::MANAGE_SELL_OFFER_BUY_NO_TRUST,
      ::stellar::MANAGE_SELL_OFFER_SELL_NOT_AUTHORIZED,
      ::stellar::MANAGE_SELL_OFFER_BUY_NOT_AUTHORIZED,
      ::stellar::MANAGE_SELL_OFFER_LINE_FULL,
      ::stellar::MANAGE_SELL_OFFER_UNDERFUNDED,
      ::stellar::MANAGE_SELL_OFFER_CROSS_SELF,
      ::stellar::MANAGE_SELL_OFFER_SELL_NO_ISSUER,
      ::stellar::MANAGE_SELL_OFFER_BUY_NO_ISSUER,
      ::stellar::MANAGE_SELL_OFFER_NOT_FOUND,
      ::stellar::MANAGE_SELL_OFFER_LOW_RESERVE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

enum ManageOfferEffect : std::int32_t {
  MANAGE_OFFER_CREATED = 0,
  MANAGE_OFFER_UPDATED = 1,
  MANAGE_OFFER_DELETED = 2,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageOfferEffect>
  : xdr_integral_base<::stellar::ManageOfferEffect, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageOfferEffect val) {
    switch (val) {
    case ::stellar::MANAGE_OFFER_CREATED:
      return "MANAGE_OFFER_CREATED";
    case ::stellar::MANAGE_OFFER_UPDATED:
      return "MANAGE_OFFER_UPDATED";
    case ::stellar::MANAGE_OFFER_DELETED:
      return "MANAGE_OFFER_DELETED";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::MANAGE_OFFER_CREATED,
      ::stellar::MANAGE_OFFER_UPDATED,
      ::stellar::MANAGE_OFFER_DELETED
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct ManageOfferSuccessResult {
  struct _offer_t {
    using _xdr_case_type = xdr::xdr_traits<ManageOfferEffect>::case_type;
  private:
    _xdr_case_type effect_;
    union {
      OfferEntry offer_;
    };

  public:
    static Constexpr const bool _xdr_has_default_case = false;
    static const std::vector<ManageOfferEffect> &_xdr_case_values() {
      static const std::vector<ManageOfferEffect> _xdr_disc_vec {
        MANAGE_OFFER_CREATED,
        MANAGE_OFFER_UPDATED,
        MANAGE_OFFER_DELETED
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == MANAGE_OFFER_CREATED || which == MANAGE_OFFER_UPDATED ? 1
        : which == MANAGE_OFFER_DELETED ? 0
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case MANAGE_OFFER_CREATED:
      case MANAGE_OFFER_UPDATED:
        _f(&_offer_t::offer_, std::forward<_A>(_a)...);
        return true;
      case MANAGE_OFFER_DELETED:
        return true;
      }
      return false;
    }

    _xdr_case_type _xdr_discriminant() const { return effect_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of effect in _offer_t");
      if (fnum != _xdr_field_number(effect_)) {
        this->~_offer_t();
        effect_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, effect_, *this);
      }
      else
        effect_ = which;
    }
    explicit _offer_t(ManageOfferEffect which = ManageOfferEffect{}) : effect_(which) {
      _xdr_with_mem_ptr(xdr::field_constructor, effect_, *this);
    }
    _offer_t(const _offer_t &source) : effect_(source.effect_) {
      _xdr_with_mem_ptr(xdr::field_constructor, effect_, *this, source);
    }
    _offer_t(_offer_t &&source) : effect_(source.effect_) {
      _xdr_with_mem_ptr(xdr::field_constructor, effect_, *this,
                        std::move(source));
    }
    ~_offer_t() { _xdr_with_mem_ptr(xdr::field_destructor, effect_, *this); }
    _offer_t &operator=(const _offer_t &source) {
      if (_xdr_field_number(effect_)
          == _xdr_field_number(source.effect_))
        _xdr_with_mem_ptr(xdr::field_assigner, effect_, *this, source);
      else {
        this->~_offer_t();
        effect_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.effect_, *this, source);
      }
      effect_ = source.effect_;
      return *this;
    }
    _offer_t &operator=(_offer_t &&source) {
      if (_xdr_field_number(effect_)
           == _xdr_field_number(source.effect_))
        _xdr_with_mem_ptr(xdr::field_assigner, effect_, *this,
                          std::move(source));
      else {
        this->~_offer_t();
        effect_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.effect_, *this,
                          std::move(source));
      }
      effect_ = source.effect_;
      return *this;
    }

    ManageOfferEffect effect() const { return ManageOfferEffect(effect_); }
    _offer_t &effect(ManageOfferEffect _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant(_xdr_d, _xdr_validate);
      return *this;
    }

    OfferEntry &offer() {
      if (_xdr_field_number(effect_) == 1)
        return offer_;
      throw xdr::xdr_wrong_union("_offer_t: offer accessed when not selected");
    }
    const OfferEntry &offer() const {
      if (_xdr_field_number(effect_) == 1)
        return offer_;
      throw xdr::xdr_wrong_union("_offer_t: offer accessed when not selected");
    }
  };

  xdr::xvector<ClaimAtom> offersClaimed{};
  _offer_t offer{};

  ManageOfferSuccessResult() = default;
  template<typename _offersClaimed_T,
           typename _offer_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::xvector<ClaimAtom>, _offersClaimed_T>::value
                          && std::is_constructible<_offer_t, _offer_T>::value
                         >::type>
  explicit ManageOfferSuccessResult(_offersClaimed_T &&_offersClaimed,
                                    _offer_T &&_offer)
    : offersClaimed(std::forward<_offersClaimed_T>(_offersClaimed)),
      offer(std::forward<_offer_T>(_offer)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageOfferSuccessResult::_offer_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageOfferSuccessResult::_offer_t;
  using case_type = ::stellar::ManageOfferSuccessResult::_offer_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().effect());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "offer";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageOfferSuccessResult::_offer_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of effect in _offer_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageOfferSuccessResult::_offer_t &obj) {
    xdr::archive(ar, obj.effect(), "effect");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.effect(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of effect in _offer_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageOfferSuccessResult::_offer_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "effect");
    obj.effect(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.effect(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ManageOfferSuccessResult>
  : xdr_struct_base<field_ptr<::stellar::ManageOfferSuccessResult,
                              decltype(::stellar::ManageOfferSuccessResult::offersClaimed),
                              &::stellar::ManageOfferSuccessResult::offersClaimed>,
                    field_ptr<::stellar::ManageOfferSuccessResult,
                              decltype(::stellar::ManageOfferSuccessResult::offer),
                              &::stellar::ManageOfferSuccessResult::offer>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageOfferSuccessResult &obj) {
    archive(ar, obj.offersClaimed, "offersClaimed");
    archive(ar, obj.offer, "offer");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageOfferSuccessResult &obj) {
    archive(ar, obj.offersClaimed, "offersClaimed");
    archive(ar, obj.offer, "offer");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ManageSellOfferResult {
  using _xdr_case_type = xdr::xdr_traits<ManageSellOfferResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    ManageOfferSuccessResult success_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<ManageSellOfferResultCode> &_xdr_case_values() {
    static const std::vector<ManageSellOfferResultCode> _xdr_disc_vec {
      MANAGE_SELL_OFFER_SUCCESS,
      MANAGE_SELL_OFFER_MALFORMED,
      MANAGE_SELL_OFFER_SELL_NO_TRUST,
      MANAGE_SELL_OFFER_BUY_NO_TRUST,
      MANAGE_SELL_OFFER_SELL_NOT_AUTHORIZED,
      MANAGE_SELL_OFFER_BUY_NOT_AUTHORIZED,
      MANAGE_SELL_OFFER_LINE_FULL,
      MANAGE_SELL_OFFER_UNDERFUNDED,
      MANAGE_SELL_OFFER_CROSS_SELF,
      MANAGE_SELL_OFFER_SELL_NO_ISSUER,
      MANAGE_SELL_OFFER_BUY_NO_ISSUER,
      MANAGE_SELL_OFFER_NOT_FOUND,
      MANAGE_SELL_OFFER_LOW_RESERVE
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == MANAGE_SELL_OFFER_SUCCESS ? 1
      : which == MANAGE_SELL_OFFER_MALFORMED || which == MANAGE_SELL_OFFER_SELL_NO_TRUST || which == MANAGE_SELL_OFFER_BUY_NO_TRUST || which == MANAGE_SELL_OFFER_SELL_NOT_AUTHORIZED || which == MANAGE_SELL_OFFER_BUY_NOT_AUTHORIZED || which == MANAGE_SELL_OFFER_LINE_FULL || which == MANAGE_SELL_OFFER_UNDERFUNDED || which == MANAGE_SELL_OFFER_CROSS_SELF || which == MANAGE_SELL_OFFER_SELL_NO_ISSUER || which == MANAGE_SELL_OFFER_BUY_NO_ISSUER || which == MANAGE_SELL_OFFER_NOT_FOUND || which == MANAGE_SELL_OFFER_LOW_RESERVE ? 0
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case MANAGE_SELL_OFFER_SUCCESS:
      _f(&ManageSellOfferResult::success_, std::forward<_A>(_a)...);
      return true;
    case MANAGE_SELL_OFFER_MALFORMED:
    case MANAGE_SELL_OFFER_SELL_NO_TRUST:
    case MANAGE_SELL_OFFER_BUY_NO_TRUST:
    case MANAGE_SELL_OFFER_SELL_NOT_AUTHORIZED:
    case MANAGE_SELL_OFFER_BUY_NOT_AUTHORIZED:
    case MANAGE_SELL_OFFER_LINE_FULL:
    case MANAGE_SELL_OFFER_UNDERFUNDED:
    case MANAGE_SELL_OFFER_CROSS_SELF:
    case MANAGE_SELL_OFFER_SELL_NO_ISSUER:
    case MANAGE_SELL_OFFER_BUY_NO_ISSUER:
    case MANAGE_SELL_OFFER_NOT_FOUND:
    case MANAGE_SELL_OFFER_LOW_RESERVE:
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in ManageSellOfferResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~ManageSellOfferResult();
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit ManageSellOfferResult(ManageSellOfferResultCode which = ManageSellOfferResultCode{}) : code_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  ManageSellOfferResult(const ManageSellOfferResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  ManageSellOfferResult(ManageSellOfferResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~ManageSellOfferResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  ManageSellOfferResult &operator=(const ManageSellOfferResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~ManageSellOfferResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  ManageSellOfferResult &operator=(ManageSellOfferResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~ManageSellOfferResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
    return *this;
  }

  ManageSellOfferResultCode code() const { return ManageSellOfferResultCode(code_); }
  ManageSellOfferResult &code(ManageSellOfferResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  ManageOfferSuccessResult &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("ManageSellOfferResult: success accessed when not selected");
  }
  const ManageOfferSuccessResult &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("ManageSellOfferResult: success accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageSellOfferResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageSellOfferResult;
  using case_type = ::stellar::ManageSellOfferResult::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().code());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "success";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageSellOfferResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in ManageSellOfferResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageSellOfferResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in ManageSellOfferResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageSellOfferResult &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "code");
    obj.code(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

enum ManageBuyOfferResultCode : std::int32_t {
  MANAGE_BUY_OFFER_SUCCESS = 0,
  MANAGE_BUY_OFFER_MALFORMED = -1,
  MANAGE_BUY_OFFER_SELL_NO_TRUST = -2,
  MANAGE_BUY_OFFER_BUY_NO_TRUST = -3,
  MANAGE_BUY_OFFER_SELL_NOT_AUTHORIZED = -4,
  MANAGE_BUY_OFFER_BUY_NOT_AUTHORIZED = -5,
  MANAGE_BUY_OFFER_LINE_FULL = -6,
  MANAGE_BUY_OFFER_UNDERFUNDED = -7,
  MANAGE_BUY_OFFER_CROSS_SELF = -8,
  MANAGE_BUY_OFFER_SELL_NO_ISSUER = -9,
  MANAGE_BUY_OFFER_BUY_NO_ISSUER = -10,
  MANAGE_BUY_OFFER_NOT_FOUND = -11,
  MANAGE_BUY_OFFER_LOW_RESERVE = -12,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageBuyOfferResultCode>
  : xdr_integral_base<::stellar::ManageBuyOfferResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageBuyOfferResultCode val) {
    switch (val) {
    case ::stellar::MANAGE_BUY_OFFER_SUCCESS:
      return "MANAGE_BUY_OFFER_SUCCESS";
    case ::stellar::MANAGE_BUY_OFFER_MALFORMED:
      return "MANAGE_BUY_OFFER_MALFORMED";
    case ::stellar::MANAGE_BUY_OFFER_SELL_NO_TRUST:
      return "MANAGE_BUY_OFFER_SELL_NO_TRUST";
    case ::stellar::MANAGE_BUY_OFFER_BUY_NO_TRUST:
      return "MANAGE_BUY_OFFER_BUY_NO_TRUST";
    case ::stellar::MANAGE_BUY_OFFER_SELL_NOT_AUTHORIZED:
      return "MANAGE_BUY_OFFER_SELL_NOT_AUTHORIZED";
    case ::stellar::MANAGE_BUY_OFFER_BUY_NOT_AUTHORIZED:
      return "MANAGE_BUY_OFFER_BUY_NOT_AUTHORIZED";
    case ::stellar::MANAGE_BUY_OFFER_LINE_FULL:
      return "MANAGE_BUY_OFFER_LINE_FULL";
    case ::stellar::MANAGE_BUY_OFFER_UNDERFUNDED:
      return "MANAGE_BUY_OFFER_UNDERFUNDED";
    case ::stellar::MANAGE_BUY_OFFER_CROSS_SELF:
      return "MANAGE_BUY_OFFER_CROSS_SELF";
    case ::stellar::MANAGE_BUY_OFFER_SELL_NO_ISSUER:
      return "MANAGE_BUY_OFFER_SELL_NO_ISSUER";
    case ::stellar::MANAGE_BUY_OFFER_BUY_NO_ISSUER:
      return "MANAGE_BUY_OFFER_BUY_NO_ISSUER";
    case ::stellar::MANAGE_BUY_OFFER_NOT_FOUND:
      return "MANAGE_BUY_OFFER_NOT_FOUND";
    case ::stellar::MANAGE_BUY_OFFER_LOW_RESERVE:
      return "MANAGE_BUY_OFFER_LOW_RESERVE";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::MANAGE_BUY_OFFER_SUCCESS,
      ::stellar::MANAGE_BUY_OFFER_MALFORMED,
      ::stellar::MANAGE_BUY_OFFER_SELL_NO_TRUST,
      ::stellar::MANAGE_BUY_OFFER_BUY_NO_TRUST,
      ::stellar::MANAGE_BUY_OFFER_SELL_NOT_AUTHORIZED,
      ::stellar::MANAGE_BUY_OFFER_BUY_NOT_AUTHORIZED,
      ::stellar::MANAGE_BUY_OFFER_LINE_FULL,
      ::stellar::MANAGE_BUY_OFFER_UNDERFUNDED,
      ::stellar::MANAGE_BUY_OFFER_CROSS_SELF,
      ::stellar::MANAGE_BUY_OFFER_SELL_NO_ISSUER,
      ::stellar::MANAGE_BUY_OFFER_BUY_NO_ISSUER,
      ::stellar::MANAGE_BUY_OFFER_NOT_FOUND,
      ::stellar::MANAGE_BUY_OFFER_LOW_RESERVE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct ManageBuyOfferResult {
  using _xdr_case_type = xdr::xdr_traits<ManageBuyOfferResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    ManageOfferSuccessResult success_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<ManageBuyOfferResultCode> &_xdr_case_values() {
    static const std::vector<ManageBuyOfferResultCode> _xdr_disc_vec {
      MANAGE_BUY_OFFER_SUCCESS,
      MANAGE_BUY_OFFER_MALFORMED,
      MANAGE_BUY_OFFER_SELL_NO_TRUST,
      MANAGE_BUY_OFFER_BUY_NO_TRUST,
      MANAGE_BUY_OFFER_SELL_NOT_AUTHORIZED,
      MANAGE_BUY_OFFER_BUY_NOT_AUTHORIZED,
      MANAGE_BUY_OFFER_LINE_FULL,
      MANAGE_BUY_OFFER_UNDERFUNDED,
      MANAGE_BUY_OFFER_CROSS_SELF,
      MANAGE_BUY_OFFER_SELL_NO_ISSUER,
      MANAGE_BUY_OFFER_BUY_NO_ISSUER,
      MANAGE_BUY_OFFER_NOT_FOUND,
      MANAGE_BUY_OFFER_LOW_RESERVE
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == MANAGE_BUY_OFFER_SUCCESS ? 1
      : which == MANAGE_BUY_OFFER_MALFORMED || which == MANAGE_BUY_OFFER_SELL_NO_TRUST || which == MANAGE_BUY_OFFER_BUY_NO_TRUST || which == MANAGE_BUY_OFFER_SELL_NOT_AUTHORIZED || which == MANAGE_BUY_OFFER_BUY_NOT_AUTHORIZED || which == MANAGE_BUY_OFFER_LINE_FULL || which == MANAGE_BUY_OFFER_UNDERFUNDED || which == MANAGE_BUY_OFFER_CROSS_SELF || which == MANAGE_BUY_OFFER_SELL_NO_ISSUER || which == MANAGE_BUY_OFFER_BUY_NO_ISSUER || which == MANAGE_BUY_OFFER_NOT_FOUND || which == MANAGE_BUY_OFFER_LOW_RESERVE ? 0
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case MANAGE_BUY_OFFER_SUCCESS:
      _f(&ManageBuyOfferResult::success_, std::forward<_A>(_a)...);
      return true;
    case MANAGE_BUY_OFFER_MALFORMED:
    case MANAGE_BUY_OFFER_SELL_NO_TRUST:
    case MANAGE_BUY_OFFER_BUY_NO_TRUST:
    case MANAGE_BUY_OFFER_SELL_NOT_AUTHORIZED:
    case MANAGE_BUY_OFFER_BUY_NOT_AUTHORIZED:
    case MANAGE_BUY_OFFER_LINE_FULL:
    case MANAGE_BUY_OFFER_UNDERFUNDED:
    case MANAGE_BUY_OFFER_CROSS_SELF:
    case MANAGE_BUY_OFFER_SELL_NO_ISSUER:
    case MANAGE_BUY_OFFER_BUY_NO_ISSUER:
    case MANAGE_BUY_OFFER_NOT_FOUND:
    case MANAGE_BUY_OFFER_LOW_RESERVE:
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in ManageBuyOfferResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~ManageBuyOfferResult();
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit ManageBuyOfferResult(ManageBuyOfferResultCode which = ManageBuyOfferResultCode{}) : code_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  ManageBuyOfferResult(const ManageBuyOfferResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  ManageBuyOfferResult(ManageBuyOfferResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~ManageBuyOfferResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  ManageBuyOfferResult &operator=(const ManageBuyOfferResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~ManageBuyOfferResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  ManageBuyOfferResult &operator=(ManageBuyOfferResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~ManageBuyOfferResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
    return *this;
  }

  ManageBuyOfferResultCode code() const { return ManageBuyOfferResultCode(code_); }
  ManageBuyOfferResult &code(ManageBuyOfferResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  ManageOfferSuccessResult &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("ManageBuyOfferResult: success accessed when not selected");
  }
  const ManageOfferSuccessResult &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("ManageBuyOfferResult: success accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageBuyOfferResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageBuyOfferResult;
  using case_type = ::stellar::ManageBuyOfferResult::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().code());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "success";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageBuyOfferResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in ManageBuyOfferResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageBuyOfferResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in ManageBuyOfferResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageBuyOfferResult &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "code");
    obj.code(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

enum SetOptionsResultCode : std::int32_t {
  SET_OPTIONS_SUCCESS = 0,
  SET_OPTIONS_LOW_RESERVE = -1,
  SET_OPTIONS_TOO_MANY_SIGNERS = -2,
  SET_OPTIONS_BAD_FLAGS = -3,
  SET_OPTIONS_INVALID_INFLATION = -4,
  SET_OPTIONS_CANT_CHANGE = -5,
  SET_OPTIONS_UNKNOWN_FLAG = -6,
  SET_OPTIONS_THRESHOLD_OUT_OF_RANGE = -7,
  SET_OPTIONS_BAD_SIGNER = -8,
  SET_OPTIONS_INVALID_HOME_DOMAIN = -9,
  SET_OPTIONS_AUTH_REVOCABLE_REQUIRED = -10,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SetOptionsResultCode>
  : xdr_integral_base<::stellar::SetOptionsResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::SetOptionsResultCode val) {
    switch (val) {
    case ::stellar::SET_OPTIONS_SUCCESS:
      return "SET_OPTIONS_SUCCESS";
    case ::stellar::SET_OPTIONS_LOW_RESERVE:
      return "SET_OPTIONS_LOW_RESERVE";
    case ::stellar::SET_OPTIONS_TOO_MANY_SIGNERS:
      return "SET_OPTIONS_TOO_MANY_SIGNERS";
    case ::stellar::SET_OPTIONS_BAD_FLAGS:
      return "SET_OPTIONS_BAD_FLAGS";
    case ::stellar::SET_OPTIONS_INVALID_INFLATION:
      return "SET_OPTIONS_INVALID_INFLATION";
    case ::stellar::SET_OPTIONS_CANT_CHANGE:
      return "SET_OPTIONS_CANT_CHANGE";
    case ::stellar::SET_OPTIONS_UNKNOWN_FLAG:
      return "SET_OPTIONS_UNKNOWN_FLAG";
    case ::stellar::SET_OPTIONS_THRESHOLD_OUT_OF_RANGE:
      return "SET_OPTIONS_THRESHOLD_OUT_OF_RANGE";
    case ::stellar::SET_OPTIONS_BAD_SIGNER:
      return "SET_OPTIONS_BAD_SIGNER";
    case ::stellar::SET_OPTIONS_INVALID_HOME_DOMAIN:
      return "SET_OPTIONS_INVALID_HOME_DOMAIN";
    case ::stellar::SET_OPTIONS_AUTH_REVOCABLE_REQUIRED:
      return "SET_OPTIONS_AUTH_REVOCABLE_REQUIRED";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::SET_OPTIONS_SUCCESS,
      ::stellar::SET_OPTIONS_LOW_RESERVE,
      ::stellar::SET_OPTIONS_TOO_MANY_SIGNERS,
      ::stellar::SET_OPTIONS_BAD_FLAGS,
      ::stellar::SET_OPTIONS_INVALID_INFLATION,
      ::stellar::SET_OPTIONS_CANT_CHANGE,
      ::stellar::SET_OPTIONS_UNKNOWN_FLAG,
      ::stellar::SET_OPTIONS_THRESHOLD_OUT_OF_RANGE,
      ::stellar::SET_OPTIONS_BAD_SIGNER,
      ::stellar::SET_OPTIONS_INVALID_HOME_DOMAIN,
      ::stellar::SET_OPTIONS_AUTH_REVOCABLE_REQUIRED
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct SetOptionsResult {
  using _xdr_case_type = xdr::xdr_traits<SetOptionsResultCode>::case_type;
private:
  _xdr_case_type code_;
public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<SetOptionsResultCode> &_xdr_case_values() {
    static const std::vector<SetOptionsResultCode> _xdr_disc_vec {
      SET_OPTIONS_SUCCESS,
      SET_OPTIONS_LOW_RESERVE,
      SET_OPTIONS_TOO_MANY_SIGNERS,
      SET_OPTIONS_BAD_FLAGS,
      SET_OPTIONS_INVALID_INFLATION,
      SET_OPTIONS_CANT_CHANGE,
      SET_OPTIONS_UNKNOWN_FLAG,
      SET_OPTIONS_THRESHOLD_OUT_OF_RANGE,
      SET_OPTIONS_BAD_SIGNER,
      SET_OPTIONS_INVALID_HOME_DOMAIN,
      SET_OPTIONS_AUTH_REVOCABLE_REQUIRED
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == SET_OPTIONS_SUCCESS ? 0
      : which == SET_OPTIONS_LOW_RESERVE || which == SET_OPTIONS_TOO_MANY_SIGNERS || which == SET_OPTIONS_BAD_FLAGS || which == SET_OPTIONS_INVALID_INFLATION || which == SET_OPTIONS_CANT_CHANGE || which == SET_OPTIONS_UNKNOWN_FLAG || which == SET_OPTIONS_THRESHOLD_OUT_OF_RANGE || which == SET_OPTIONS_BAD_SIGNER || which == SET_OPTIONS_INVALID_HOME_DOMAIN || which == SET_OPTIONS_AUTH_REVOCABLE_REQUIRED ? 0
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case SET_OPTIONS_SUCCESS:
      return true;
    case SET_OPTIONS_LOW_RESERVE:
    case SET_OPTIONS_TOO_MANY_SIGNERS:
    case SET_OPTIONS_BAD_FLAGS:
    case SET_OPTIONS_INVALID_INFLATION:
    case SET_OPTIONS_CANT_CHANGE:
    case SET_OPTIONS_UNKNOWN_FLAG:
    case SET_OPTIONS_THRESHOLD_OUT_OF_RANGE:
    case SET_OPTIONS_BAD_SIGNER:
    case SET_OPTIONS_INVALID_HOME_DOMAIN:
    case SET_OPTIONS_AUTH_REVOCABLE_REQUIRED:
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in SetOptionsResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~SetOptionsResult();
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit SetOptionsResult(SetOptionsResultCode which = SetOptionsResultCode{}) : code_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  SetOptionsResult(const SetOptionsResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  SetOptionsResult(SetOptionsResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~SetOptionsResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  SetOptionsResult &operator=(const SetOptionsResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~SetOptionsResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  SetOptionsResult &operator=(SetOptionsResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~SetOptionsResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
    return *this;
  }

  SetOptionsResultCode code() const { return SetOptionsResultCode(code_); }
  SetOptionsResult &code(SetOptionsResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

};
} namespace xdr {
template<> struct xdr_traits<::stellar::SetOptionsResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::SetOptionsResult;
  using case_type = ::stellar::SetOptionsResult::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().code());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::SetOptionsResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in SetOptionsResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SetOptionsResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in SetOptionsResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SetOptionsResult &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "code");
    obj.code(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

enum ChangeTrustResultCode : std::int32_t {
  CHANGE_TRUST_SUCCESS = 0,
  CHANGE_TRUST_MALFORMED = -1,
  CHANGE_TRUST_NO_ISSUER = -2,
  CHANGE_TRUST_INVALID_LIMIT = -3,
  CHANGE_TRUST_LOW_RESERVE = -4,
  CHANGE_TRUST_SELF_NOT_ALLOWED = -5,
  CHANGE_TRUST_TRUST_LINE_MISSING = -6,
  CHANGE_TRUST_CANNOT_DELETE = -7,
  CHANGE_TRUST_NOT_AUTH_MAINTAIN_LIABILITIES = -8,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ChangeTrustResultCode>
  : xdr_integral_base<::stellar::ChangeTrustResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ChangeTrustResultCode val) {
    switch (val) {
    case ::stellar::CHANGE_TRUST_SUCCESS:
      return "CHANGE_TRUST_SUCCESS";
    case ::stellar::CHANGE_TRUST_MALFORMED:
      return "CHANGE_TRUST_MALFORMED";
    case ::stellar::CHANGE_TRUST_NO_ISSUER:
      return "CHANGE_TRUST_NO_ISSUER";
    case ::stellar::CHANGE_TRUST_INVALID_LIMIT:
      return "CHANGE_TRUST_INVALID_LIMIT";
    case ::stellar::CHANGE_TRUST_LOW_RESERVE:
      return "CHANGE_TRUST_LOW_RESERVE";
    case ::stellar::CHANGE_TRUST_SELF_NOT_ALLOWED:
      return "CHANGE_TRUST_SELF_NOT_ALLOWED";
    case ::stellar::CHANGE_TRUST_TRUST_LINE_MISSING:
      return "CHANGE_TRUST_TRUST_LINE_MISSING";
    case ::stellar::CHANGE_TRUST_CANNOT_DELETE:
      return "CHANGE_TRUST_CANNOT_DELETE";
    case ::stellar::CHANGE_TRUST_NOT_AUTH_MAINTAIN_LIABILITIES:
      return "CHANGE_TRUST_NOT_AUTH_MAINTAIN_LIABILITIES";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::CHANGE_TRUST_SUCCESS,
      ::stellar::CHANGE_TRUST_MALFORMED,
      ::stellar::CHANGE_TRUST_NO_ISSUER,
      ::stellar::CHANGE_TRUST_INVALID_LIMIT,
      ::stellar::CHANGE_TRUST_LOW_RESERVE,
      ::stellar::CHANGE_TRUST_SELF_NOT_ALLOWED,
      ::stellar::CHANGE_TRUST_TRUST_LINE_MISSING,
      ::stellar::CHANGE_TRUST_CANNOT_DELETE,
      ::stellar::CHANGE_TRUST_NOT_AUTH_MAINTAIN_LIABILITIES
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct ChangeTrustResult {
  using _xdr_case_type = xdr::xdr_traits<ChangeTrustResultCode>::case_type;
private:
  _xdr_case_type code_;
public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<ChangeTrustResultCode> &_xdr_case_values() {
    static const std::vector<ChangeTrustResultCode> _xdr_disc_vec {
      CHANGE_TRUST_SUCCESS,
      CHANGE_TRUST_MALFORMED,
      CHANGE_TRUST_NO_ISSUER,
      CHANGE_TRUST_INVALID_LIMIT,
      CHANGE_TRUST_LOW_RESERVE,
      CHANGE_TRUST_SELF_NOT_ALLOWED,
      CHANGE_TRUST_TRUST_LINE_MISSING,
      CHANGE_TRUST_CANNOT_DELETE,
      CHANGE_TRUST_NOT_AUTH_MAINTAIN_LIABILITIES
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == CHANGE_TRUST_SUCCESS ? 0
      : which == CHANGE_TRUST_MALFORMED || which == CHANGE_TRUST_NO_ISSUER || which == CHANGE_TRUST_INVALID_LIMIT || which == CHANGE_TRUST_LOW_RESERVE || which == CHANGE_TRUST_SELF_NOT_ALLOWED || which == CHANGE_TRUST_TRUST_LINE_MISSING || which == CHANGE_TRUST_CANNOT_DELETE || which == CHANGE_TRUST_NOT_AUTH_MAINTAIN_LIABILITIES ? 0
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case CHANGE_TRUST_SUCCESS:
      return true;
    case CHANGE_TRUST_MALFORMED:
    case CHANGE_TRUST_NO_ISSUER:
    case CHANGE_TRUST_INVALID_LIMIT:
    case CHANGE_TRUST_LOW_RESERVE:
    case CHANGE_TRUST_SELF_NOT_ALLOWED:
    case CHANGE_TRUST_TRUST_LINE_MISSING:
    case CHANGE_TRUST_CANNOT_DELETE:
    case CHANGE_TRUST_NOT_AUTH_MAINTAIN_LIABILITIES:
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in ChangeTrustResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~ChangeTrustResult();
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit ChangeTrustResult(ChangeTrustResultCode which = ChangeTrustResultCode{}) : code_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  ChangeTrustResult(const ChangeTrustResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  ChangeTrustResult(ChangeTrustResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~ChangeTrustResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  ChangeTrustResult &operator=(const ChangeTrustResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~ChangeTrustResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  ChangeTrustResult &operator=(ChangeTrustResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~ChangeTrustResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
    return *this;
  }

  ChangeTrustResultCode code() const { return ChangeTrustResultCode(code_); }
  ChangeTrustResult &code(ChangeTrustResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

};
} namespace xdr {
template<> struct xdr_traits<::stellar::ChangeTrustResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ChangeTrustResult;
  using case_type = ::stellar::ChangeTrustResult::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().code());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ChangeTrustResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in ChangeTrustResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ChangeTrustResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in ChangeTrustResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ChangeTrustResult &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "code");
    obj.code(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

enum AllowTrustResultCode : std::int32_t {
  ALLOW_TRUST_SUCCESS = 0,
  ALLOW_TRUST_MALFORMED = -1,
  ALLOW_TRUST_NO_TRUST_LINE = -2,
  ALLOW_TRUST_TRUST_NOT_REQUIRED = -3,
  ALLOW_TRUST_CANT_REVOKE = -4,
  ALLOW_TRUST_SELF_NOT_ALLOWED = -5,
  ALLOW_TRUST_LOW_RESERVE = -6,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::AllowTrustResultCode>
  : xdr_integral_base<::stellar::AllowTrustResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::AllowTrustResultCode val) {
    switch (val) {
    case ::stellar::ALLOW_TRUST_SUCCESS:
      return "ALLOW_TRUST_SUCCESS";
    case ::stellar::ALLOW_TRUST_MALFORMED:
      return "ALLOW_TRUST_MALFORMED";
    case ::stellar::ALLOW_TRUST_NO_TRUST_LINE:
      return "ALLOW_TRUST_NO_TRUST_LINE";
    case ::stellar::ALLOW_TRUST_TRUST_NOT_REQUIRED:
      return "ALLOW_TRUST_TRUST_NOT_REQUIRED";
    case ::stellar::ALLOW_TRUST_CANT_REVOKE:
      return "ALLOW_TRUST_CANT_REVOKE";
    case ::stellar::ALLOW_TRUST_SELF_NOT_ALLOWED:
      return "ALLOW_TRUST_SELF_NOT_ALLOWED";
    case ::stellar::ALLOW_TRUST_LOW_RESERVE:
      return "ALLOW_TRUST_LOW_RESERVE";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::ALLOW_TRUST_SUCCESS,
      ::stellar::ALLOW_TRUST_MALFORMED,
      ::stellar::ALLOW_TRUST_NO_TRUST_LINE,
      ::stellar::ALLOW_TRUST_TRUST_NOT_REQUIRED,
      ::stellar::ALLOW_TRUST_CANT_REVOKE,
      ::stellar::ALLOW_TRUST_SELF_NOT_ALLOWED,
      ::stellar::ALLOW_TRUST_LOW_RESERVE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct AllowTrustResult {
  using _xdr_case_type = xdr::xdr_traits<AllowTrustResultCode>::case_type;
private:
  _xdr_case_type code_;
public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<AllowTrustResultCode> &_xdr_case_values() {
    static const std::vector<AllowTrustResultCode> _xdr_disc_vec {
      ALLOW_TRUST_SUCCESS,
      ALLOW_TRUST_MALFORMED,
      ALLOW_TRUST_NO_TRUST_LINE,
      ALLOW_TRUST_TRUST_NOT_REQUIRED,
      ALLOW_TRUST_CANT_REVOKE,
      ALLOW_TRUST_SELF_NOT_ALLOWED,
      ALLOW_TRUST_LOW_RESERVE
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == ALLOW_TRUST_SUCCESS ? 0
      : which == ALLOW_TRUST_MALFORMED || which == ALLOW_TRUST_NO_TRUST_LINE || which == ALLOW_TRUST_TRUST_NOT_REQUIRED || which == ALLOW_TRUST_CANT_REVOKE || which == ALLOW_TRUST_SELF_NOT_ALLOWED || which == ALLOW_TRUST_LOW_RESERVE ? 0
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case ALLOW_TRUST_SUCCESS:
      return true;
    case ALLOW_TRUST_MALFORMED:
    case ALLOW_TRUST_NO_TRUST_LINE:
    case ALLOW_TRUST_TRUST_NOT_REQUIRED:
    case ALLOW_TRUST_CANT_REVOKE:
    case ALLOW_TRUST_SELF_NOT_ALLOWED:
    case ALLOW_TRUST_LOW_RESERVE:
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in AllowTrustResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~AllowTrustResult();
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit AllowTrustResult(AllowTrustResultCode which = AllowTrustResultCode{}) : code_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  AllowTrustResult(const AllowTrustResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  AllowTrustResult(AllowTrustResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~AllowTrustResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  AllowTrustResult &operator=(const AllowTrustResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~AllowTrustResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  AllowTrustResult &operator=(AllowTrustResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~AllowTrustResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
    return *this;
  }

  AllowTrustResultCode code() const { return AllowTrustResultCode(code_); }
  AllowTrustResult &code(AllowTrustResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

};
} namespace xdr {
template<> struct xdr_traits<::stellar::AllowTrustResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::AllowTrustResult;
  using case_type = ::stellar::AllowTrustResult::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().code());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::AllowTrustResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in AllowTrustResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::AllowTrustResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in AllowTrustResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::AllowTrustResult &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "code");
    obj.code(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

enum AccountMergeResultCode : std::int32_t {
  ACCOUNT_MERGE_SUCCESS = 0,
  ACCOUNT_MERGE_MALFORMED = -1,
  ACCOUNT_MERGE_NO_ACCOUNT = -2,
  ACCOUNT_MERGE_IMMUTABLE_SET = -3,
  ACCOUNT_MERGE_HAS_SUB_ENTRIES = -4,
  ACCOUNT_MERGE_SEQNUM_TOO_FAR = -5,
  ACCOUNT_MERGE_DEST_FULL = -6,
  ACCOUNT_MERGE_IS_SPONSOR = -7,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::AccountMergeResultCode>
  : xdr_integral_base<::stellar::AccountMergeResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::AccountMergeResultCode val) {
    switch (val) {
    case ::stellar::ACCOUNT_MERGE_SUCCESS:
      return "ACCOUNT_MERGE_SUCCESS";
    case ::stellar::ACCOUNT_MERGE_MALFORMED:
      return "ACCOUNT_MERGE_MALFORMED";
    case ::stellar::ACCOUNT_MERGE_NO_ACCOUNT:
      return "ACCOUNT_MERGE_NO_ACCOUNT";
    case ::stellar::ACCOUNT_MERGE_IMMUTABLE_SET:
      return "ACCOUNT_MERGE_IMMUTABLE_SET";
    case ::stellar::ACCOUNT_MERGE_HAS_SUB_ENTRIES:
      return "ACCOUNT_MERGE_HAS_SUB_ENTRIES";
    case ::stellar::ACCOUNT_MERGE_SEQNUM_TOO_FAR:
      return "ACCOUNT_MERGE_SEQNUM_TOO_FAR";
    case ::stellar::ACCOUNT_MERGE_DEST_FULL:
      return "ACCOUNT_MERGE_DEST_FULL";
    case ::stellar::ACCOUNT_MERGE_IS_SPONSOR:
      return "ACCOUNT_MERGE_IS_SPONSOR";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::ACCOUNT_MERGE_SUCCESS,
      ::stellar::ACCOUNT_MERGE_MALFORMED,
      ::stellar::ACCOUNT_MERGE_NO_ACCOUNT,
      ::stellar::ACCOUNT_MERGE_IMMUTABLE_SET,
      ::stellar::ACCOUNT_MERGE_HAS_SUB_ENTRIES,
      ::stellar::ACCOUNT_MERGE_SEQNUM_TOO_FAR,
      ::stellar::ACCOUNT_MERGE_DEST_FULL,
      ::stellar::ACCOUNT_MERGE_IS_SPONSOR
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct AccountMergeResult {
  using _xdr_case_type = xdr::xdr_traits<AccountMergeResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    int64 sourceAccountBalance_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<AccountMergeResultCode> &_xdr_case_values() {
    static const std::vector<AccountMergeResultCode> _xdr_disc_vec {
      ACCOUNT_MERGE_SUCCESS,
      ACCOUNT_MERGE_MALFORMED,
      ACCOUNT_MERGE_NO_ACCOUNT,
      ACCOUNT_MERGE_IMMUTABLE_SET,
      ACCOUNT_MERGE_HAS_SUB_ENTRIES,
      ACCOUNT_MERGE_SEQNUM_TOO_FAR,
      ACCOUNT_MERGE_DEST_FULL,
      ACCOUNT_MERGE_IS_SPONSOR
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == ACCOUNT_MERGE_SUCCESS ? 1
      : which == ACCOUNT_MERGE_MALFORMED || which == ACCOUNT_MERGE_NO_ACCOUNT || which == ACCOUNT_MERGE_IMMUTABLE_SET || which == ACCOUNT_MERGE_HAS_SUB_ENTRIES || which == ACCOUNT_MERGE_SEQNUM_TOO_FAR || which == ACCOUNT_MERGE_DEST_FULL || which == ACCOUNT_MERGE_IS_SPONSOR ? 0
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case ACCOUNT_MERGE_SUCCESS:
      _f(&AccountMergeResult::sourceAccountBalance_, std::forward<_A>(_a)...);
      return true;
    case ACCOUNT_MERGE_MALFORMED:
    case ACCOUNT_MERGE_NO_ACCOUNT:
    case ACCOUNT_MERGE_IMMUTABLE_SET:
    case ACCOUNT_MERGE_HAS_SUB_ENTRIES:
    case ACCOUNT_MERGE_SEQNUM_TOO_FAR:
    case ACCOUNT_MERGE_DEST_FULL:
    case ACCOUNT_MERGE_IS_SPONSOR:
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in AccountMergeResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~AccountMergeResult();
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit AccountMergeResult(AccountMergeResultCode which = AccountMergeResultCode{}) : code_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  AccountMergeResult(const AccountMergeResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  AccountMergeResult(AccountMergeResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~AccountMergeResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  AccountMergeResult &operator=(const AccountMergeResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~AccountMergeResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  AccountMergeResult &operator=(AccountMergeResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~AccountMergeResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
    return *this;
  }

  AccountMergeResultCode code() const { return AccountMergeResultCode(code_); }
  AccountMergeResult &code(AccountMergeResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  int64 &sourceAccountBalance() {
    if (_xdr_field_number(code_) == 1)
      return sourceAccountBalance_;
    throw xdr::xdr_wrong_union("AccountMergeResult: sourceAccountBalance accessed when not selected");
  }
  const int64 &sourceAccountBalance() const {
    if (_xdr_field_number(code_) == 1)
      return sourceAccountBalance_;
    throw xdr::xdr_wrong_union("AccountMergeResult: sourceAccountBalance accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::AccountMergeResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::AccountMergeResult;
  using case_type = ::stellar::AccountMergeResult::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().code());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "sourceAccountBalance";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::AccountMergeResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in AccountMergeResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::AccountMergeResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in AccountMergeResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::AccountMergeResult &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "code");
    obj.code(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

enum InflationResultCode : std::int32_t {
  INFLATION_SUCCESS = 0,
  INFLATION_NOT_TIME = -1,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::InflationResultCode>
  : xdr_integral_base<::stellar::InflationResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::InflationResultCode val) {
    switch (val) {
    case ::stellar::INFLATION_SUCCESS:
      return "INFLATION_SUCCESS";
    case ::stellar::INFLATION_NOT_TIME:
      return "INFLATION_NOT_TIME";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::INFLATION_SUCCESS,
      ::stellar::INFLATION_NOT_TIME
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct InflationPayout {
  AccountID destination{};
  int64 amount{};

  InflationPayout() = default;
  template<typename _destination_T,
           typename _amount_T,
           typename = typename
           std::enable_if<std::is_constructible<AccountID, _destination_T>::value
                          && std::is_constructible<int64, _amount_T>::value
                         >::type>
  explicit InflationPayout(_destination_T &&_destination,
                           _amount_T &&_amount)
    : destination(std::forward<_destination_T>(_destination)),
      amount(std::forward<_amount_T>(_amount)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::InflationPayout>
  : xdr_struct_base<field_ptr<::stellar::InflationPayout,
                              decltype(::stellar::InflationPayout::destination),
                              &::stellar::InflationPayout::destination>,
                    field_ptr<::stellar::InflationPayout,
                              decltype(::stellar::InflationPayout::amount),
                              &::stellar::InflationPayout::amount>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::InflationPayout &obj) {
    archive(ar, obj.destination, "destination");
    archive(ar, obj.amount, "amount");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::InflationPayout &obj) {
    archive(ar, obj.destination, "destination");
    archive(ar, obj.amount, "amount");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct InflationResult {
  using _xdr_case_type = xdr::xdr_traits<InflationResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    xdr::xvector<InflationPayout> payouts_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<InflationResultCode> &_xdr_case_values() {
    static const std::vector<InflationResultCode> _xdr_disc_vec {
      INFLATION_SUCCESS,
      INFLATION_NOT_TIME
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == INFLATION_SUCCESS ? 1
      : which == INFLATION_NOT_TIME ? 0
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case INFLATION_SUCCESS:
      _f(&InflationResult::payouts_, std::forward<_A>(_a)...);
      return true;
    case INFLATION_NOT_TIME:
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in InflationResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~InflationResult();
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit InflationResult(InflationResultCode which = InflationResultCode{}) : code_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  InflationResult(const InflationResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  InflationResult(InflationResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~InflationResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  InflationResult &operator=(const InflationResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~InflationResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  InflationResult &operator=(InflationResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~InflationResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
    return *this;
  }

  InflationResultCode code() const { return InflationResultCode(code_); }
  InflationResult &code(InflationResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  xdr::xvector<InflationPayout> &payouts() {
    if (_xdr_field_number(code_) == 1)
      return payouts_;
    throw xdr::xdr_wrong_union("InflationResult: payouts accessed when not selected");
  }
  const xdr::xvector<InflationPayout> &payouts() const {
    if (_xdr_field_number(code_) == 1)
      return payouts_;
    throw xdr::xdr_wrong_union("InflationResult: payouts accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::InflationResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::InflationResult;
  using case_type = ::stellar::InflationResult::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().code());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "payouts";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::InflationResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in InflationResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::InflationResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in InflationResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::InflationResult &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "code");
    obj.code(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

enum ManageDataResultCode : std::int32_t {
  MANAGE_DATA_SUCCESS = 0,
  MANAGE_DATA_NOT_SUPPORTED_YET = -1,
  MANAGE_DATA_NAME_NOT_FOUND = -2,
  MANAGE_DATA_LOW_RESERVE = -3,
  MANAGE_DATA_INVALID_NAME = -4,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageDataResultCode>
  : xdr_integral_base<::stellar::ManageDataResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ManageDataResultCode val) {
    switch (val) {
    case ::stellar::MANAGE_DATA_SUCCESS:
      return "MANAGE_DATA_SUCCESS";
    case ::stellar::MANAGE_DATA_NOT_SUPPORTED_YET:
      return "MANAGE_DATA_NOT_SUPPORTED_YET";
    case ::stellar::MANAGE_DATA_NAME_NOT_FOUND:
      return "MANAGE_DATA_NAME_NOT_FOUND";
    case ::stellar::MANAGE_DATA_LOW_RESERVE:
      return "MANAGE_DATA_LOW_RESERVE";
    case ::stellar::MANAGE_DATA_INVALID_NAME:
      return "MANAGE_DATA_INVALID_NAME";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::MANAGE_DATA_SUCCESS,
      ::stellar::MANAGE_DATA_NOT_SUPPORTED_YET,
      ::stellar::MANAGE_DATA_NAME_NOT_FOUND,
      ::stellar::MANAGE_DATA_LOW_RESERVE,
      ::stellar::MANAGE_DATA_INVALID_NAME
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct ManageDataResult {
  using _xdr_case_type = xdr::xdr_traits<ManageDataResultCode>::case_type;
private:
  _xdr_case_type code_;
public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<ManageDataResultCode> &_xdr_case_values() {
    static const std::vector<ManageDataResultCode> _xdr_disc_vec {
      MANAGE_DATA_SUCCESS,
      MANAGE_DATA_NOT_SUPPORTED_YET,
      MANAGE_DATA_NAME_NOT_FOUND,
      MANAGE_DATA_LOW_RESERVE,
      MANAGE_DATA_INVALID_NAME
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == MANAGE_DATA_SUCCESS ? 0
      : which == MANAGE_DATA_NOT_SUPPORTED_YET || which == MANAGE_DATA_NAME_NOT_FOUND || which == MANAGE_DATA_LOW_RESERVE || which == MANAGE_DATA_INVALID_NAME ? 0
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case MANAGE_DATA_SUCCESS:
      return true;
    case MANAGE_DATA_NOT_SUPPORTED_YET:
    case MANAGE_DATA_NAME_NOT_FOUND:
    case MANAGE_DATA_LOW_RESERVE:
    case MANAGE_DATA_INVALID_NAME:
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in ManageDataResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~ManageDataResult();
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit ManageDataResult(ManageDataResultCode which = ManageDataResultCode{}) : code_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  ManageDataResult(const ManageDataResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  ManageDataResult(ManageDataResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~ManageDataResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  ManageDataResult &operator=(const ManageDataResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~ManageDataResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  ManageDataResult &operator=(ManageDataResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~ManageDataResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
    return *this;
  }

  ManageDataResultCode code() const { return ManageDataResultCode(code_); }
  ManageDataResult &code(ManageDataResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

};
} namespace xdr {
template<> struct xdr_traits<::stellar::ManageDataResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ManageDataResult;
  using case_type = ::stellar::ManageDataResult::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().code());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ManageDataResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in ManageDataResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ManageDataResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in ManageDataResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ManageDataResult &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "code");
    obj.code(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

enum BumpSequenceResultCode : std::int32_t {
  BUMP_SEQUENCE_SUCCESS = 0,
  BUMP_SEQUENCE_BAD_SEQ = -1,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::BumpSequenceResultCode>
  : xdr_integral_base<::stellar::BumpSequenceResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::BumpSequenceResultCode val) {
    switch (val) {
    case ::stellar::BUMP_SEQUENCE_SUCCESS:
      return "BUMP_SEQUENCE_SUCCESS";
    case ::stellar::BUMP_SEQUENCE_BAD_SEQ:
      return "BUMP_SEQUENCE_BAD_SEQ";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::BUMP_SEQUENCE_SUCCESS,
      ::stellar::BUMP_SEQUENCE_BAD_SEQ
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct BumpSequenceResult {
  using _xdr_case_type = xdr::xdr_traits<BumpSequenceResultCode>::case_type;
private:
  _xdr_case_type code_;
public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<BumpSequenceResultCode> &_xdr_case_values() {
    static const std::vector<BumpSequenceResultCode> _xdr_disc_vec {
      BUMP_SEQUENCE_SUCCESS,
      BUMP_SEQUENCE_BAD_SEQ
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == BUMP_SEQUENCE_SUCCESS ? 0
      : which == BUMP_SEQUENCE_BAD_SEQ ? 0
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case BUMP_SEQUENCE_SUCCESS:
      return true;
    case BUMP_SEQUENCE_BAD_SEQ:
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in BumpSequenceResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~BumpSequenceResult();
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit BumpSequenceResult(BumpSequenceResultCode which = BumpSequenceResultCode{}) : code_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  BumpSequenceResult(const BumpSequenceResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  BumpSequenceResult(BumpSequenceResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~BumpSequenceResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  BumpSequenceResult &operator=(const BumpSequenceResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~BumpSequenceResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  BumpSequenceResult &operator=(BumpSequenceResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~BumpSequenceResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
    return *this;
  }

  BumpSequenceResultCode code() const { return BumpSequenceResultCode(code_); }
  BumpSequenceResult &code(BumpSequenceResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

};
} namespace xdr {
template<> struct xdr_traits<::stellar::BumpSequenceResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::BumpSequenceResult;
  using case_type = ::stellar::BumpSequenceResult::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().code());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::BumpSequenceResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in BumpSequenceResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::BumpSequenceResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in BumpSequenceResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::BumpSequenceResult &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "code");
    obj.code(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

enum CreateClaimableBalanceResultCode : std::int32_t {
  CREATE_CLAIMABLE_BALANCE_SUCCESS = 0,
  CREATE_CLAIMABLE_BALANCE_MALFORMED = -1,
  CREATE_CLAIMABLE_BALANCE_LOW_RESERVE = -2,
  CREATE_CLAIMABLE_BALANCE_NO_TRUST = -3,
  CREATE_CLAIMABLE_BALANCE_NOT_AUTHORIZED = -4,
  CREATE_CLAIMABLE_BALANCE_UNDERFUNDED = -5,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateClaimableBalanceResultCode>
  : xdr_integral_base<::stellar::CreateClaimableBalanceResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::CreateClaimableBalanceResultCode val) {
    switch (val) {
    case ::stellar::CREATE_CLAIMABLE_BALANCE_SUCCESS:
      return "CREATE_CLAIMABLE_BALANCE_SUCCESS";
    case ::stellar::CREATE_CLAIMABLE_BALANCE_MALFORMED:
      return "CREATE_CLAIMABLE_BALANCE_MALFORMED";
    case ::stellar::CREATE_CLAIMABLE_BALANCE_LOW_RESERVE:
      return "CREATE_CLAIMABLE_BALANCE_LOW_RESERVE";
    case ::stellar::CREATE_CLAIMABLE_BALANCE_NO_TRUST:
      return "CREATE_CLAIMABLE_BALANCE_NO_TRUST";
    case ::stellar::CREATE_CLAIMABLE_BALANCE_NOT_AUTHORIZED:
      return "CREATE_CLAIMABLE_BALANCE_NOT_AUTHORIZED";
    case ::stellar::CREATE_CLAIMABLE_BALANCE_UNDERFUNDED:
      return "CREATE_CLAIMABLE_BALANCE_UNDERFUNDED";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::CREATE_CLAIMABLE_BALANCE_SUCCESS,
      ::stellar::CREATE_CLAIMABLE_BALANCE_MALFORMED,
      ::stellar::CREATE_CLAIMABLE_BALANCE_LOW_RESERVE,
      ::stellar::CREATE_CLAIMABLE_BALANCE_NO_TRUST,
      ::stellar::CREATE_CLAIMABLE_BALANCE_NOT_AUTHORIZED,
      ::stellar::CREATE_CLAIMABLE_BALANCE_UNDERFUNDED
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct CreateClaimableBalanceResult {
  using _xdr_case_type = xdr::xdr_traits<CreateClaimableBalanceResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    ClaimableBalanceID balanceID_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<CreateClaimableBalanceResultCode> &_xdr_case_values() {
    static const std::vector<CreateClaimableBalanceResultCode> _xdr_disc_vec {
      CREATE_CLAIMABLE_BALANCE_SUCCESS,
      CREATE_CLAIMABLE_BALANCE_MALFORMED,
      CREATE_CLAIMABLE_BALANCE_LOW_RESERVE,
      CREATE_CLAIMABLE_BALANCE_NO_TRUST,
      CREATE_CLAIMABLE_BALANCE_NOT_AUTHORIZED,
      CREATE_CLAIMABLE_BALANCE_UNDERFUNDED
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == CREATE_CLAIMABLE_BALANCE_SUCCESS ? 1
      : which == CREATE_CLAIMABLE_BALANCE_MALFORMED || which == CREATE_CLAIMABLE_BALANCE_LOW_RESERVE || which == CREATE_CLAIMABLE_BALANCE_NO_TRUST || which == CREATE_CLAIMABLE_BALANCE_NOT_AUTHORIZED || which == CREATE_CLAIMABLE_BALANCE_UNDERFUNDED ? 0
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case CREATE_CLAIMABLE_BALANCE_SUCCESS:
      _f(&CreateClaimableBalanceResult::balanceID_, std::forward<_A>(_a)...);
      return true;
    case CREATE_CLAIMABLE_BALANCE_MALFORMED:
    case CREATE_CLAIMABLE_BALANCE_LOW_RESERVE:
    case CREATE_CLAIMABLE_BALANCE_NO_TRUST:
    case CREATE_CLAIMABLE_BALANCE_NOT_AUTHORIZED:
    case CREATE_CLAIMABLE_BALANCE_UNDERFUNDED:
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in CreateClaimableBalanceResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~CreateClaimableBalanceResult();
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit CreateClaimableBalanceResult(CreateClaimableBalanceResultCode which = CreateClaimableBalanceResultCode{}) : code_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  CreateClaimableBalanceResult(const CreateClaimableBalanceResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  CreateClaimableBalanceResult(CreateClaimableBalanceResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~CreateClaimableBalanceResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  CreateClaimableBalanceResult &operator=(const CreateClaimableBalanceResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~CreateClaimableBalanceResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  CreateClaimableBalanceResult &operator=(CreateClaimableBalanceResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~CreateClaimableBalanceResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
    return *this;
  }

  CreateClaimableBalanceResultCode code() const { return CreateClaimableBalanceResultCode(code_); }
  CreateClaimableBalanceResult &code(CreateClaimableBalanceResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  ClaimableBalanceID &balanceID() {
    if (_xdr_field_number(code_) == 1)
      return balanceID_;
    throw xdr::xdr_wrong_union("CreateClaimableBalanceResult: balanceID accessed when not selected");
  }
  const ClaimableBalanceID &balanceID() const {
    if (_xdr_field_number(code_) == 1)
      return balanceID_;
    throw xdr::xdr_wrong_union("CreateClaimableBalanceResult: balanceID accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::CreateClaimableBalanceResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::CreateClaimableBalanceResult;
  using case_type = ::stellar::CreateClaimableBalanceResult::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().code());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "balanceID";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::CreateClaimableBalanceResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in CreateClaimableBalanceResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::CreateClaimableBalanceResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in CreateClaimableBalanceResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::CreateClaimableBalanceResult &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "code");
    obj.code(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

enum ClaimClaimableBalanceResultCode : std::int32_t {
  CLAIM_CLAIMABLE_BALANCE_SUCCESS = 0,
  CLAIM_CLAIMABLE_BALANCE_DOES_NOT_EXIST = -1,
  CLAIM_CLAIMABLE_BALANCE_CANNOT_CLAIM = -2,
  CLAIM_CLAIMABLE_BALANCE_LINE_FULL = -3,
  CLAIM_CLAIMABLE_BALANCE_NO_TRUST = -4,
  CLAIM_CLAIMABLE_BALANCE_NOT_AUTHORIZED = -5,
  CLAIM_CLAIMABLE_BALANCE_TRUSTLINE_FROZEN = -6,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ClaimClaimableBalanceResultCode>
  : xdr_integral_base<::stellar::ClaimClaimableBalanceResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ClaimClaimableBalanceResultCode val) {
    switch (val) {
    case ::stellar::CLAIM_CLAIMABLE_BALANCE_SUCCESS:
      return "CLAIM_CLAIMABLE_BALANCE_SUCCESS";
    case ::stellar::CLAIM_CLAIMABLE_BALANCE_DOES_NOT_EXIST:
      return "CLAIM_CLAIMABLE_BALANCE_DOES_NOT_EXIST";
    case ::stellar::CLAIM_CLAIMABLE_BALANCE_CANNOT_CLAIM:
      return "CLAIM_CLAIMABLE_BALANCE_CANNOT_CLAIM";
    case ::stellar::CLAIM_CLAIMABLE_BALANCE_LINE_FULL:
      return "CLAIM_CLAIMABLE_BALANCE_LINE_FULL";
    case ::stellar::CLAIM_CLAIMABLE_BALANCE_NO_TRUST:
      return "CLAIM_CLAIMABLE_BALANCE_NO_TRUST";
    case ::stellar::CLAIM_CLAIMABLE_BALANCE_NOT_AUTHORIZED:
      return "CLAIM_CLAIMABLE_BALANCE_NOT_AUTHORIZED";
    case ::stellar::CLAIM_CLAIMABLE_BALANCE_TRUSTLINE_FROZEN:
      return "CLAIM_CLAIMABLE_BALANCE_TRUSTLINE_FROZEN";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::CLAIM_CLAIMABLE_BALANCE_SUCCESS,
      ::stellar::CLAIM_CLAIMABLE_BALANCE_DOES_NOT_EXIST,
      ::stellar::CLAIM_CLAIMABLE_BALANCE_CANNOT_CLAIM,
      ::stellar::CLAIM_CLAIMABLE_BALANCE_LINE_FULL,
      ::stellar::CLAIM_CLAIMABLE_BALANCE_NO_TRUST,
      ::stellar::CLAIM_CLAIMABLE_BALANCE_NOT_AUTHORIZED,
      ::stellar::CLAIM_CLAIMABLE_BALANCE_TRUSTLINE_FROZEN
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct ClaimClaimableBalanceResult {
  using _xdr_case_type = xdr::xdr_traits<ClaimClaimableBalanceResultCode>::case_type;
private:
  _xdr_case_type code_;
public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<ClaimClaimableBalanceResultCode> &_xdr_case_values() {
    static const std::vector<ClaimClaimableBalanceResultCode> _xdr_disc_vec {
      CLAIM_CLAIMABLE_BALANCE_SUCCESS,
      CLAIM_CLAIMABLE_BALANCE_DOES_NOT_EXIST,
      CLAIM_CLAIMABLE_BALANCE_CANNOT_CLAIM,
      CLAIM_CLAIMABLE_BALANCE_LINE_FULL,
      CLAIM_CLAIMABLE_BALANCE_NO_TRUST,
      CLAIM_CLAIMABLE_BALANCE_NOT_AUTHORIZED,
      CLAIM_CLAIMABLE_BALANCE_TRUSTLINE_FROZEN
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == CLAIM_CLAIMABLE_BALANCE_SUCCESS ? 0
      : which == CLAIM_CLAIMABLE_BALANCE_DOES_NOT_EXIST || which == CLAIM_CLAIMABLE_BALANCE_CANNOT_CLAIM || which == CLAIM_CLAIMABLE_BALANCE_LINE_FULL || which == CLAIM_CLAIMABLE_BALANCE_NO_TRUST || which == CLAIM_CLAIMABLE_BALANCE_NOT_AUTHORIZED || which == CLAIM_CLAIMABLE_BALANCE_TRUSTLINE_FROZEN ? 0
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case CLAIM_CLAIMABLE_BALANCE_SUCCESS:
      return true;
    case CLAIM_CLAIMABLE_BALANCE_DOES_NOT_EXIST:
    case CLAIM_CLAIMABLE_BALANCE_CANNOT_CLAIM:
    case CLAIM_CLAIMABLE_BALANCE_LINE_FULL:
    case CLAIM_CLAIMABLE_BALANCE_NO_TRUST:
    case CLAIM_CLAIMABLE_BALANCE_NOT_AUTHORIZED:
    case CLAIM_CLAIMABLE_BALANCE_TRUSTLINE_FROZEN:
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in ClaimClaimableBalanceResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~ClaimClaimableBalanceResult();
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit ClaimClaimableBalanceResult(ClaimClaimableBalanceResultCode which = ClaimClaimableBalanceResultCode{}) : code_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  ClaimClaimableBalanceResult(const ClaimClaimableBalanceResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  ClaimClaimableBalanceResult(ClaimClaimableBalanceResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~ClaimClaimableBalanceResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  ClaimClaimableBalanceResult &operator=(const ClaimClaimableBalanceResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~ClaimClaimableBalanceResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  ClaimClaimableBalanceResult &operator=(ClaimClaimableBalanceResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~ClaimClaimableBalanceResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
    return *this;
  }

  ClaimClaimableBalanceResultCode code() const { return ClaimClaimableBalanceResultCode(code_); }
  ClaimClaimableBalanceResult &code(ClaimClaimableBalanceResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

};
} namespace xdr {
template<> struct xdr_traits<::stellar::ClaimClaimableBalanceResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ClaimClaimableBalanceResult;
  using case_type = ::stellar::ClaimClaimableBalanceResult::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().code());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ClaimClaimableBalanceResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in ClaimClaimableBalanceResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ClaimClaimableBalanceResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in ClaimClaimableBalanceResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ClaimClaimableBalanceResult &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "code");
    obj.code(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

enum BeginSponsoringFutureReservesResultCode : std::int32_t {
  BEGIN_SPONSORING_FUTURE_RESERVES_SUCCESS = 0,
  BEGIN_SPONSORING_FUTURE_RESERVES_MALFORMED = -1,
  BEGIN_SPONSORING_FUTURE_RESERVES_ALREADY_SPONSORED = -2,
  BEGIN_SPONSORING_FUTURE_RESERVES_RECURSIVE = -3,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::BeginSponsoringFutureReservesResultCode>
  : xdr_integral_base<::stellar::BeginSponsoringFutureReservesResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::BeginSponsoringFutureReservesResultCode val) {
    switch (val) {
    case ::stellar::BEGIN_SPONSORING_FUTURE_RESERVES_SUCCESS:
      return "BEGIN_SPONSORING_FUTURE_RESERVES_SUCCESS";
    case ::stellar::BEGIN_SPONSORING_FUTURE_RESERVES_MALFORMED:
      return "BEGIN_SPONSORING_FUTURE_RESERVES_MALFORMED";
    case ::stellar::BEGIN_SPONSORING_FUTURE_RESERVES_ALREADY_SPONSORED:
      return "BEGIN_SPONSORING_FUTURE_RESERVES_ALREADY_SPONSORED";
    case ::stellar::BEGIN_SPONSORING_FUTURE_RESERVES_RECURSIVE:
      return "BEGIN_SPONSORING_FUTURE_RESERVES_RECURSIVE";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::BEGIN_SPONSORING_FUTURE_RESERVES_SUCCESS,
      ::stellar::BEGIN_SPONSORING_FUTURE_RESERVES_MALFORMED,
      ::stellar::BEGIN_SPONSORING_FUTURE_RESERVES_ALREADY_SPONSORED,
      ::stellar::BEGIN_SPONSORING_FUTURE_RESERVES_RECURSIVE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct BeginSponsoringFutureReservesResult {
  using _xdr_case_type = xdr::xdr_traits<BeginSponsoringFutureReservesResultCode>::case_type;
private:
  _xdr_case_type code_;
public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<BeginSponsoringFutureReservesResultCode> &_xdr_case_values() {
    static const std::vector<BeginSponsoringFutureReservesResultCode> _xdr_disc_vec {
      BEGIN_SPONSORING_FUTURE_RESERVES_SUCCESS,
      BEGIN_SPONSORING_FUTURE_RESERVES_MALFORMED,
      BEGIN_SPONSORING_FUTURE_RESERVES_ALREADY_SPONSORED,
      BEGIN_SPONSORING_FUTURE_RESERVES_RECURSIVE
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == BEGIN_SPONSORING_FUTURE_RESERVES_SUCCESS ? 0
      : which == BEGIN_SPONSORING_FUTURE_RESERVES_MALFORMED || which == BEGIN_SPONSORING_FUTURE_RESERVES_ALREADY_SPONSORED || which == BEGIN_SPONSORING_FUTURE_RESERVES_RECURSIVE ? 0
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case BEGIN_SPONSORING_FUTURE_RESERVES_SUCCESS:
      return true;
    case BEGIN_SPONSORING_FUTURE_RESERVES_MALFORMED:
    case BEGIN_SPONSORING_FUTURE_RESERVES_ALREADY_SPONSORED:
    case BEGIN_SPONSORING_FUTURE_RESERVES_RECURSIVE:
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in BeginSponsoringFutureReservesResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~BeginSponsoringFutureReservesResult();
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit BeginSponsoringFutureReservesResult(BeginSponsoringFutureReservesResultCode which = BeginSponsoringFutureReservesResultCode{}) : code_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  BeginSponsoringFutureReservesResult(const BeginSponsoringFutureReservesResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  BeginSponsoringFutureReservesResult(BeginSponsoringFutureReservesResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~BeginSponsoringFutureReservesResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  BeginSponsoringFutureReservesResult &operator=(const BeginSponsoringFutureReservesResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~BeginSponsoringFutureReservesResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  BeginSponsoringFutureReservesResult &operator=(BeginSponsoringFutureReservesResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~BeginSponsoringFutureReservesResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
    return *this;
  }

  BeginSponsoringFutureReservesResultCode code() const { return BeginSponsoringFutureReservesResultCode(code_); }
  BeginSponsoringFutureReservesResult &code(BeginSponsoringFutureReservesResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

};
} namespace xdr {
template<> struct xdr_traits<::stellar::BeginSponsoringFutureReservesResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::BeginSponsoringFutureReservesResult;
  using case_type = ::stellar::BeginSponsoringFutureReservesResult::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().code());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::BeginSponsoringFutureReservesResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in BeginSponsoringFutureReservesResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::BeginSponsoringFutureReservesResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in BeginSponsoringFutureReservesResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::BeginSponsoringFutureReservesResult &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "code");
    obj.code(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

enum EndSponsoringFutureReservesResultCode : std::int32_t {
  END_SPONSORING_FUTURE_RESERVES_SUCCESS = 0,
  END_SPONSORING_FUTURE_RESERVES_NOT_SPONSORED = -1,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::EndSponsoringFutureReservesResultCode>
  : xdr_integral_base<::stellar::EndSponsoringFutureReservesResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::EndSponsoringFutureReservesResultCode val) {
    switch (val) {
    case ::stellar::END_SPONSORING_FUTURE_RESERVES_SUCCESS:
      return "END_SPONSORING_FUTURE_RESERVES_SUCCESS";
    case ::stellar::END_SPONSORING_FUTURE_RESERVES_NOT_SPONSORED:
      return "END_SPONSORING_FUTURE_RESERVES_NOT_SPONSORED";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::END_SPONSORING_FUTURE_RESERVES_SUCCESS,
      ::stellar::END_SPONSORING_FUTURE_RESERVES_NOT_SPONSORED
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct EndSponsoringFutureReservesResult {
  using _xdr_case_type = xdr::xdr_traits<EndSponsoringFutureReservesResultCode>::case_type;
private:
  _xdr_case_type code_;
public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<EndSponsoringFutureReservesResultCode> &_xdr_case_values() {
    static const std::vector<EndSponsoringFutureReservesResultCode> _xdr_disc_vec {
      END_SPONSORING_FUTURE_RESERVES_SUCCESS,
      END_SPONSORING_FUTURE_RESERVES_NOT_SPONSORED
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == END_SPONSORING_FUTURE_RESERVES_SUCCESS ? 0
      : which == END_SPONSORING_FUTURE_RESERVES_NOT_SPONSORED ? 0
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case END_SPONSORING_FUTURE_RESERVES_SUCCESS:
      return true;
    case END_SPONSORING_FUTURE_RESERVES_NOT_SPONSORED:
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in EndSponsoringFutureReservesResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~EndSponsoringFutureReservesResult();
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit EndSponsoringFutureReservesResult(EndSponsoringFutureReservesResultCode which = EndSponsoringFutureReservesResultCode{}) : code_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  EndSponsoringFutureReservesResult(const EndSponsoringFutureReservesResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  EndSponsoringFutureReservesResult(EndSponsoringFutureReservesResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~EndSponsoringFutureReservesResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  EndSponsoringFutureReservesResult &operator=(const EndSponsoringFutureReservesResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~EndSponsoringFutureReservesResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  EndSponsoringFutureReservesResult &operator=(EndSponsoringFutureReservesResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~EndSponsoringFutureReservesResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
    return *this;
  }

  EndSponsoringFutureReservesResultCode code() const { return EndSponsoringFutureReservesResultCode(code_); }
  EndSponsoringFutureReservesResult &code(EndSponsoringFutureReservesResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

};
} namespace xdr {
template<> struct xdr_traits<::stellar::EndSponsoringFutureReservesResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::EndSponsoringFutureReservesResult;
  using case_type = ::stellar::EndSponsoringFutureReservesResult::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().code());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::EndSponsoringFutureReservesResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in EndSponsoringFutureReservesResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::EndSponsoringFutureReservesResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in EndSponsoringFutureReservesResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::EndSponsoringFutureReservesResult &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "code");
    obj.code(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

enum RevokeSponsorshipResultCode : std::int32_t {
  REVOKE_SPONSORSHIP_SUCCESS = 0,
  REVOKE_SPONSORSHIP_DOES_NOT_EXIST = -1,
  REVOKE_SPONSORSHIP_NOT_SPONSOR = -2,
  REVOKE_SPONSORSHIP_LOW_RESERVE = -3,
  REVOKE_SPONSORSHIP_ONLY_TRANSFERABLE = -4,
  REVOKE_SPONSORSHIP_MALFORMED = -5,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::RevokeSponsorshipResultCode>
  : xdr_integral_base<::stellar::RevokeSponsorshipResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::RevokeSponsorshipResultCode val) {
    switch (val) {
    case ::stellar::REVOKE_SPONSORSHIP_SUCCESS:
      return "REVOKE_SPONSORSHIP_SUCCESS";
    case ::stellar::REVOKE_SPONSORSHIP_DOES_NOT_EXIST:
      return "REVOKE_SPONSORSHIP_DOES_NOT_EXIST";
    case ::stellar::REVOKE_SPONSORSHIP_NOT_SPONSOR:
      return "REVOKE_SPONSORSHIP_NOT_SPONSOR";
    case ::stellar::REVOKE_SPONSORSHIP_LOW_RESERVE:
      return "REVOKE_SPONSORSHIP_LOW_RESERVE";
    case ::stellar::REVOKE_SPONSORSHIP_ONLY_TRANSFERABLE:
      return "REVOKE_SPONSORSHIP_ONLY_TRANSFERABLE";
    case ::stellar::REVOKE_SPONSORSHIP_MALFORMED:
      return "REVOKE_SPONSORSHIP_MALFORMED";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::REVOKE_SPONSORSHIP_SUCCESS,
      ::stellar::REVOKE_SPONSORSHIP_DOES_NOT_EXIST,
      ::stellar::REVOKE_SPONSORSHIP_NOT_SPONSOR,
      ::stellar::REVOKE_SPONSORSHIP_LOW_RESERVE,
      ::stellar::REVOKE_SPONSORSHIP_ONLY_TRANSFERABLE,
      ::stellar::REVOKE_SPONSORSHIP_MALFORMED
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct RevokeSponsorshipResult {
  using _xdr_case_type = xdr::xdr_traits<RevokeSponsorshipResultCode>::case_type;
private:
  _xdr_case_type code_;
public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<RevokeSponsorshipResultCode> &_xdr_case_values() {
    static const std::vector<RevokeSponsorshipResultCode> _xdr_disc_vec {
      REVOKE_SPONSORSHIP_SUCCESS,
      REVOKE_SPONSORSHIP_DOES_NOT_EXIST,
      REVOKE_SPONSORSHIP_NOT_SPONSOR,
      REVOKE_SPONSORSHIP_LOW_RESERVE,
      REVOKE_SPONSORSHIP_ONLY_TRANSFERABLE,
      REVOKE_SPONSORSHIP_MALFORMED
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == REVOKE_SPONSORSHIP_SUCCESS ? 0
      : which == REVOKE_SPONSORSHIP_DOES_NOT_EXIST || which == REVOKE_SPONSORSHIP_NOT_SPONSOR || which == REVOKE_SPONSORSHIP_LOW_RESERVE || which == REVOKE_SPONSORSHIP_ONLY_TRANSFERABLE || which == REVOKE_SPONSORSHIP_MALFORMED ? 0
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case REVOKE_SPONSORSHIP_SUCCESS:
      return true;
    case REVOKE_SPONSORSHIP_DOES_NOT_EXIST:
    case REVOKE_SPONSORSHIP_NOT_SPONSOR:
    case REVOKE_SPONSORSHIP_LOW_RESERVE:
    case REVOKE_SPONSORSHIP_ONLY_TRANSFERABLE:
    case REVOKE_SPONSORSHIP_MALFORMED:
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in RevokeSponsorshipResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~RevokeSponsorshipResult();
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit RevokeSponsorshipResult(RevokeSponsorshipResultCode which = RevokeSponsorshipResultCode{}) : code_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  RevokeSponsorshipResult(const RevokeSponsorshipResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  RevokeSponsorshipResult(RevokeSponsorshipResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~RevokeSponsorshipResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  RevokeSponsorshipResult &operator=(const RevokeSponsorshipResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~RevokeSponsorshipResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  RevokeSponsorshipResult &operator=(RevokeSponsorshipResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~RevokeSponsorshipResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
    return *this;
  }

  RevokeSponsorshipResultCode code() const { return RevokeSponsorshipResultCode(code_); }
  RevokeSponsorshipResult &code(RevokeSponsorshipResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

};
} namespace xdr {
template<> struct xdr_traits<::stellar::RevokeSponsorshipResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::RevokeSponsorshipResult;
  using case_type = ::stellar::RevokeSponsorshipResult::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().code());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::RevokeSponsorshipResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in RevokeSponsorshipResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::RevokeSponsorshipResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in RevokeSponsorshipResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::RevokeSponsorshipResult &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "code");
    obj.code(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

enum ClawbackResultCode : std::int32_t {
  CLAWBACK_SUCCESS = 0,
  CLAWBACK_MALFORMED = -1,
  CLAWBACK_NOT_CLAWBACK_ENABLED = -2,
  CLAWBACK_NO_TRUST = -3,
  CLAWBACK_UNDERFUNDED = -4,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ClawbackResultCode>
  : xdr_integral_base<::stellar::ClawbackResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ClawbackResultCode val) {
    switch (val) {
    case ::stellar::CLAWBACK_SUCCESS:
      return "CLAWBACK_SUCCESS";
    case ::stellar::CLAWBACK_MALFORMED:
      return "CLAWBACK_MALFORMED";
    case ::stellar::CLAWBACK_NOT_CLAWBACK_ENABLED:
      return "CLAWBACK_NOT_CLAWBACK_ENABLED";
    case ::stellar::CLAWBACK_NO_TRUST:
      return "CLAWBACK_NO_TRUST";
    case ::stellar::CLAWBACK_UNDERFUNDED:
      return "CLAWBACK_UNDERFUNDED";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::CLAWBACK_SUCCESS,
      ::stellar::CLAWBACK_MALFORMED,
      ::stellar::CLAWBACK_NOT_CLAWBACK_ENABLED,
      ::stellar::CLAWBACK_NO_TRUST,
      ::stellar::CLAWBACK_UNDERFUNDED
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct ClawbackResult {
  using _xdr_case_type = xdr::xdr_traits<ClawbackResultCode>::case_type;
private:
  _xdr_case_type code_;
public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<ClawbackResultCode> &_xdr_case_values() {
    static const std::vector<ClawbackResultCode> _xdr_disc_vec {
      CLAWBACK_SUCCESS,
      CLAWBACK_MALFORMED,
      CLAWBACK_NOT_CLAWBACK_ENABLED,
      CLAWBACK_NO_TRUST,
      CLAWBACK_UNDERFUNDED
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == CLAWBACK_SUCCESS ? 0
      : which == CLAWBACK_MALFORMED || which == CLAWBACK_NOT_CLAWBACK_ENABLED || which == CLAWBACK_NO_TRUST || which == CLAWBACK_UNDERFUNDED ? 0
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case CLAWBACK_SUCCESS:
      return true;
    case CLAWBACK_MALFORMED:
    case CLAWBACK_NOT_CLAWBACK_ENABLED:
    case CLAWBACK_NO_TRUST:
    case CLAWBACK_UNDERFUNDED:
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in ClawbackResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~ClawbackResult();
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit ClawbackResult(ClawbackResultCode which = ClawbackResultCode{}) : code_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  ClawbackResult(const ClawbackResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  ClawbackResult(ClawbackResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~ClawbackResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  ClawbackResult &operator=(const ClawbackResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~ClawbackResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  ClawbackResult &operator=(ClawbackResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~ClawbackResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
    return *this;
  }

  ClawbackResultCode code() const { return ClawbackResultCode(code_); }
  ClawbackResult &code(ClawbackResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

};
} namespace xdr {
template<> struct xdr_traits<::stellar::ClawbackResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ClawbackResult;
  using case_type = ::stellar::ClawbackResult::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().code());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ClawbackResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in ClawbackResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ClawbackResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in ClawbackResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ClawbackResult &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "code");
    obj.code(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

enum ClawbackClaimableBalanceResultCode : std::int32_t {
  CLAWBACK_CLAIMABLE_BALANCE_SUCCESS = 0,
  CLAWBACK_CLAIMABLE_BALANCE_DOES_NOT_EXIST = -1,
  CLAWBACK_CLAIMABLE_BALANCE_NOT_ISSUER = -2,
  CLAWBACK_CLAIMABLE_BALANCE_NOT_CLAWBACK_ENABLED = -3,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ClawbackClaimableBalanceResultCode>
  : xdr_integral_base<::stellar::ClawbackClaimableBalanceResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ClawbackClaimableBalanceResultCode val) {
    switch (val) {
    case ::stellar::CLAWBACK_CLAIMABLE_BALANCE_SUCCESS:
      return "CLAWBACK_CLAIMABLE_BALANCE_SUCCESS";
    case ::stellar::CLAWBACK_CLAIMABLE_BALANCE_DOES_NOT_EXIST:
      return "CLAWBACK_CLAIMABLE_BALANCE_DOES_NOT_EXIST";
    case ::stellar::CLAWBACK_CLAIMABLE_BALANCE_NOT_ISSUER:
      return "CLAWBACK_CLAIMABLE_BALANCE_NOT_ISSUER";
    case ::stellar::CLAWBACK_CLAIMABLE_BALANCE_NOT_CLAWBACK_ENABLED:
      return "CLAWBACK_CLAIMABLE_BALANCE_NOT_CLAWBACK_ENABLED";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::CLAWBACK_CLAIMABLE_BALANCE_SUCCESS,
      ::stellar::CLAWBACK_CLAIMABLE_BALANCE_DOES_NOT_EXIST,
      ::stellar::CLAWBACK_CLAIMABLE_BALANCE_NOT_ISSUER,
      ::stellar::CLAWBACK_CLAIMABLE_BALANCE_NOT_CLAWBACK_ENABLED
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct ClawbackClaimableBalanceResult {
  using _xdr_case_type = xdr::xdr_traits<ClawbackClaimableBalanceResultCode>::case_type;
private:
  _xdr_case_type code_;
public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<ClawbackClaimableBalanceResultCode> &_xdr_case_values() {
    static const std::vector<ClawbackClaimableBalanceResultCode> _xdr_disc_vec {
      CLAWBACK_CLAIMABLE_BALANCE_SUCCESS,
      CLAWBACK_CLAIMABLE_BALANCE_DOES_NOT_EXIST,
      CLAWBACK_CLAIMABLE_BALANCE_NOT_ISSUER,
      CLAWBACK_CLAIMABLE_BALANCE_NOT_CLAWBACK_ENABLED
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == CLAWBACK_CLAIMABLE_BALANCE_SUCCESS ? 0
      : which == CLAWBACK_CLAIMABLE_BALANCE_DOES_NOT_EXIST || which == CLAWBACK_CLAIMABLE_BALANCE_NOT_ISSUER || which == CLAWBACK_CLAIMABLE_BALANCE_NOT_CLAWBACK_ENABLED ? 0
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case CLAWBACK_CLAIMABLE_BALANCE_SUCCESS:
      return true;
    case CLAWBACK_CLAIMABLE_BALANCE_DOES_NOT_EXIST:
    case CLAWBACK_CLAIMABLE_BALANCE_NOT_ISSUER:
    case CLAWBACK_CLAIMABLE_BALANCE_NOT_CLAWBACK_ENABLED:
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in ClawbackClaimableBalanceResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~ClawbackClaimableBalanceResult();
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit ClawbackClaimableBalanceResult(ClawbackClaimableBalanceResultCode which = ClawbackClaimableBalanceResultCode{}) : code_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  ClawbackClaimableBalanceResult(const ClawbackClaimableBalanceResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  ClawbackClaimableBalanceResult(ClawbackClaimableBalanceResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~ClawbackClaimableBalanceResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  ClawbackClaimableBalanceResult &operator=(const ClawbackClaimableBalanceResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~ClawbackClaimableBalanceResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  ClawbackClaimableBalanceResult &operator=(ClawbackClaimableBalanceResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~ClawbackClaimableBalanceResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
    return *this;
  }

  ClawbackClaimableBalanceResultCode code() const { return ClawbackClaimableBalanceResultCode(code_); }
  ClawbackClaimableBalanceResult &code(ClawbackClaimableBalanceResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

};
} namespace xdr {
template<> struct xdr_traits<::stellar::ClawbackClaimableBalanceResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ClawbackClaimableBalanceResult;
  using case_type = ::stellar::ClawbackClaimableBalanceResult::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().code());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ClawbackClaimableBalanceResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in ClawbackClaimableBalanceResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ClawbackClaimableBalanceResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in ClawbackClaimableBalanceResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ClawbackClaimableBalanceResult &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "code");
    obj.code(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

enum SetTrustLineFlagsResultCode : std::int32_t {
  SET_TRUST_LINE_FLAGS_SUCCESS = 0,
  SET_TRUST_LINE_FLAGS_MALFORMED = -1,
  SET_TRUST_LINE_FLAGS_NO_TRUST_LINE = -2,
  SET_TRUST_LINE_FLAGS_CANT_REVOKE = -3,
  SET_TRUST_LINE_FLAGS_INVALID_STATE = -4,
  SET_TRUST_LINE_FLAGS_LOW_RESERVE = -5,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SetTrustLineFlagsResultCode>
  : xdr_integral_base<::stellar::SetTrustLineFlagsResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::SetTrustLineFlagsResultCode val) {
    switch (val) {
    case ::stellar::SET_TRUST_LINE_FLAGS_SUCCESS:
      return "SET_TRUST_LINE_FLAGS_SUCCESS";
    case ::stellar::SET_TRUST_LINE_FLAGS_MALFORMED:
      return "SET_TRUST_LINE_FLAGS_MALFORMED";
    case ::stellar::SET_TRUST_LINE_FLAGS_NO_TRUST_LINE:
      return "SET_TRUST_LINE_FLAGS_NO_TRUST_LINE";
    case ::stellar::SET_TRUST_LINE_FLAGS_CANT_REVOKE:
      return "SET_TRUST_LINE_FLAGS_CANT_REVOKE";
    case ::stellar::SET_TRUST_LINE_FLAGS_INVALID_STATE:
      return "SET_TRUST_LINE_FLAGS_INVALID_STATE";
    case ::stellar::SET_TRUST_LINE_FLAGS_LOW_RESERVE:
      return "SET_TRUST_LINE_FLAGS_LOW_RESERVE";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::SET_TRUST_LINE_FLAGS_SUCCESS,
      ::stellar::SET_TRUST_LINE_FLAGS_MALFORMED,
      ::stellar::SET_TRUST_LINE_FLAGS_NO_TRUST_LINE,
      ::stellar::SET_TRUST_LINE_FLAGS_CANT_REVOKE,
      ::stellar::SET_TRUST_LINE_FLAGS_INVALID_STATE,
      ::stellar::SET_TRUST_LINE_FLAGS_LOW_RESERVE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct SetTrustLineFlagsResult {
  using _xdr_case_type = xdr::xdr_traits<SetTrustLineFlagsResultCode>::case_type;
private:
  _xdr_case_type code_;
public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<SetTrustLineFlagsResultCode> &_xdr_case_values() {
    static const std::vector<SetTrustLineFlagsResultCode> _xdr_disc_vec {
      SET_TRUST_LINE_FLAGS_SUCCESS,
      SET_TRUST_LINE_FLAGS_MALFORMED,
      SET_TRUST_LINE_FLAGS_NO_TRUST_LINE,
      SET_TRUST_LINE_FLAGS_CANT_REVOKE,
      SET_TRUST_LINE_FLAGS_INVALID_STATE,
      SET_TRUST_LINE_FLAGS_LOW_RESERVE
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == SET_TRUST_LINE_FLAGS_SUCCESS ? 0
      : which == SET_TRUST_LINE_FLAGS_MALFORMED || which == SET_TRUST_LINE_FLAGS_NO_TRUST_LINE || which == SET_TRUST_LINE_FLAGS_CANT_REVOKE || which == SET_TRUST_LINE_FLAGS_INVALID_STATE || which == SET_TRUST_LINE_FLAGS_LOW_RESERVE ? 0
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case SET_TRUST_LINE_FLAGS_SUCCESS:
      return true;
    case SET_TRUST_LINE_FLAGS_MALFORMED:
    case SET_TRUST_LINE_FLAGS_NO_TRUST_LINE:
    case SET_TRUST_LINE_FLAGS_CANT_REVOKE:
    case SET_TRUST_LINE_FLAGS_INVALID_STATE:
    case SET_TRUST_LINE_FLAGS_LOW_RESERVE:
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in SetTrustLineFlagsResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~SetTrustLineFlagsResult();
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit SetTrustLineFlagsResult(SetTrustLineFlagsResultCode which = SetTrustLineFlagsResultCode{}) : code_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  SetTrustLineFlagsResult(const SetTrustLineFlagsResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  SetTrustLineFlagsResult(SetTrustLineFlagsResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~SetTrustLineFlagsResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  SetTrustLineFlagsResult &operator=(const SetTrustLineFlagsResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~SetTrustLineFlagsResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  SetTrustLineFlagsResult &operator=(SetTrustLineFlagsResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~SetTrustLineFlagsResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
    return *this;
  }

  SetTrustLineFlagsResultCode code() const { return SetTrustLineFlagsResultCode(code_); }
  SetTrustLineFlagsResult &code(SetTrustLineFlagsResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

};
} namespace xdr {
template<> struct xdr_traits<::stellar::SetTrustLineFlagsResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::SetTrustLineFlagsResult;
  using case_type = ::stellar::SetTrustLineFlagsResult::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().code());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::SetTrustLineFlagsResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in SetTrustLineFlagsResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SetTrustLineFlagsResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in SetTrustLineFlagsResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SetTrustLineFlagsResult &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "code");
    obj.code(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

enum LiquidityPoolDepositResultCode : std::int32_t {
  LIQUIDITY_POOL_DEPOSIT_SUCCESS = 0,
  LIQUIDITY_POOL_DEPOSIT_MALFORMED = -1,
  LIQUIDITY_POOL_DEPOSIT_NO_TRUST = -2,
  LIQUIDITY_POOL_DEPOSIT_NOT_AUTHORIZED = -3,
  LIQUIDITY_POOL_DEPOSIT_UNDERFUNDED = -4,
  LIQUIDITY_POOL_DEPOSIT_LINE_FULL = -5,
  LIQUIDITY_POOL_DEPOSIT_BAD_PRICE = -6,
  LIQUIDITY_POOL_DEPOSIT_POOL_FULL = -7,
  LIQUIDITY_POOL_DEPOSIT_TRUSTLINE_FROZEN = -8,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::LiquidityPoolDepositResultCode>
  : xdr_integral_base<::stellar::LiquidityPoolDepositResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::LiquidityPoolDepositResultCode val) {
    switch (val) {
    case ::stellar::LIQUIDITY_POOL_DEPOSIT_SUCCESS:
      return "LIQUIDITY_POOL_DEPOSIT_SUCCESS";
    case ::stellar::LIQUIDITY_POOL_DEPOSIT_MALFORMED:
      return "LIQUIDITY_POOL_DEPOSIT_MALFORMED";
    case ::stellar::LIQUIDITY_POOL_DEPOSIT_NO_TRUST:
      return "LIQUIDITY_POOL_DEPOSIT_NO_TRUST";
    case ::stellar::LIQUIDITY_POOL_DEPOSIT_NOT_AUTHORIZED:
      return "LIQUIDITY_POOL_DEPOSIT_NOT_AUTHORIZED";
    case ::stellar::LIQUIDITY_POOL_DEPOSIT_UNDERFUNDED:
      return "LIQUIDITY_POOL_DEPOSIT_UNDERFUNDED";
    case ::stellar::LIQUIDITY_POOL_DEPOSIT_LINE_FULL:
      return "LIQUIDITY_POOL_DEPOSIT_LINE_FULL";
    case ::stellar::LIQUIDITY_POOL_DEPOSIT_BAD_PRICE:
      return "LIQUIDITY_POOL_DEPOSIT_BAD_PRICE";
    case ::stellar::LIQUIDITY_POOL_DEPOSIT_POOL_FULL:
      return "LIQUIDITY_POOL_DEPOSIT_POOL_FULL";
    case ::stellar::LIQUIDITY_POOL_DEPOSIT_TRUSTLINE_FROZEN:
      return "LIQUIDITY_POOL_DEPOSIT_TRUSTLINE_FROZEN";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::LIQUIDITY_POOL_DEPOSIT_SUCCESS,
      ::stellar::LIQUIDITY_POOL_DEPOSIT_MALFORMED,
      ::stellar::LIQUIDITY_POOL_DEPOSIT_NO_TRUST,
      ::stellar::LIQUIDITY_POOL_DEPOSIT_NOT_AUTHORIZED,
      ::stellar::LIQUIDITY_POOL_DEPOSIT_UNDERFUNDED,
      ::stellar::LIQUIDITY_POOL_DEPOSIT_LINE_FULL,
      ::stellar::LIQUIDITY_POOL_DEPOSIT_BAD_PRICE,
      ::stellar::LIQUIDITY_POOL_DEPOSIT_POOL_FULL,
      ::stellar::LIQUIDITY_POOL_DEPOSIT_TRUSTLINE_FROZEN
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct LiquidityPoolDepositResult {
  using _xdr_case_type = xdr::xdr_traits<LiquidityPoolDepositResultCode>::case_type;
private:
  _xdr_case_type code_;
public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<LiquidityPoolDepositResultCode> &_xdr_case_values() {
    static const std::vector<LiquidityPoolDepositResultCode> _xdr_disc_vec {
      LIQUIDITY_POOL_DEPOSIT_SUCCESS,
      LIQUIDITY_POOL_DEPOSIT_MALFORMED,
      LIQUIDITY_POOL_DEPOSIT_NO_TRUST,
      LIQUIDITY_POOL_DEPOSIT_NOT_AUTHORIZED,
      LIQUIDITY_POOL_DEPOSIT_UNDERFUNDED,
      LIQUIDITY_POOL_DEPOSIT_LINE_FULL,
      LIQUIDITY_POOL_DEPOSIT_BAD_PRICE,
      LIQUIDITY_POOL_DEPOSIT_POOL_FULL,
      LIQUIDITY_POOL_DEPOSIT_TRUSTLINE_FROZEN
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == LIQUIDITY_POOL_DEPOSIT_SUCCESS ? 0
      : which == LIQUIDITY_POOL_DEPOSIT_MALFORMED || which == LIQUIDITY_POOL_DEPOSIT_NO_TRUST || which == LIQUIDITY_POOL_DEPOSIT_NOT_AUTHORIZED || which == LIQUIDITY_POOL_DEPOSIT_UNDERFUNDED || which == LIQUIDITY_POOL_DEPOSIT_LINE_FULL || which == LIQUIDITY_POOL_DEPOSIT_BAD_PRICE || which == LIQUIDITY_POOL_DEPOSIT_POOL_FULL || which == LIQUIDITY_POOL_DEPOSIT_TRUSTLINE_FROZEN ? 0
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case LIQUIDITY_POOL_DEPOSIT_SUCCESS:
      return true;
    case LIQUIDITY_POOL_DEPOSIT_MALFORMED:
    case LIQUIDITY_POOL_DEPOSIT_NO_TRUST:
    case LIQUIDITY_POOL_DEPOSIT_NOT_AUTHORIZED:
    case LIQUIDITY_POOL_DEPOSIT_UNDERFUNDED:
    case LIQUIDITY_POOL_DEPOSIT_LINE_FULL:
    case LIQUIDITY_POOL_DEPOSIT_BAD_PRICE:
    case LIQUIDITY_POOL_DEPOSIT_POOL_FULL:
    case LIQUIDITY_POOL_DEPOSIT_TRUSTLINE_FROZEN:
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in LiquidityPoolDepositResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~LiquidityPoolDepositResult();
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit LiquidityPoolDepositResult(LiquidityPoolDepositResultCode which = LiquidityPoolDepositResultCode{}) : code_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  LiquidityPoolDepositResult(const LiquidityPoolDepositResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  LiquidityPoolDepositResult(LiquidityPoolDepositResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~LiquidityPoolDepositResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  LiquidityPoolDepositResult &operator=(const LiquidityPoolDepositResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~LiquidityPoolDepositResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  LiquidityPoolDepositResult &operator=(LiquidityPoolDepositResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~LiquidityPoolDepositResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
    return *this;
  }

  LiquidityPoolDepositResultCode code() const { return LiquidityPoolDepositResultCode(code_); }
  LiquidityPoolDepositResult &code(LiquidityPoolDepositResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

};
} namespace xdr {
template<> struct xdr_traits<::stellar::LiquidityPoolDepositResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::LiquidityPoolDepositResult;
  using case_type = ::stellar::LiquidityPoolDepositResult::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().code());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::LiquidityPoolDepositResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in LiquidityPoolDepositResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LiquidityPoolDepositResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in LiquidityPoolDepositResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LiquidityPoolDepositResult &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "code");
    obj.code(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

enum LiquidityPoolWithdrawResultCode : std::int32_t {
  LIQUIDITY_POOL_WITHDRAW_SUCCESS = 0,
  LIQUIDITY_POOL_WITHDRAW_MALFORMED = -1,
  LIQUIDITY_POOL_WITHDRAW_NO_TRUST = -2,
  LIQUIDITY_POOL_WITHDRAW_UNDERFUNDED = -3,
  LIQUIDITY_POOL_WITHDRAW_LINE_FULL = -4,
  LIQUIDITY_POOL_WITHDRAW_UNDER_MINIMUM = -5,
  LIQUIDITY_POOL_WITHDRAW_TRUSTLINE_FROZEN = -6,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::LiquidityPoolWithdrawResultCode>
  : xdr_integral_base<::stellar::LiquidityPoolWithdrawResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::LiquidityPoolWithdrawResultCode val) {
    switch (val) {
    case ::stellar::LIQUIDITY_POOL_WITHDRAW_SUCCESS:
      return "LIQUIDITY_POOL_WITHDRAW_SUCCESS";
    case ::stellar::LIQUIDITY_POOL_WITHDRAW_MALFORMED:
      return "LIQUIDITY_POOL_WITHDRAW_MALFORMED";
    case ::stellar::LIQUIDITY_POOL_WITHDRAW_NO_TRUST:
      return "LIQUIDITY_POOL_WITHDRAW_NO_TRUST";
    case ::stellar::LIQUIDITY_POOL_WITHDRAW_UNDERFUNDED:
      return "LIQUIDITY_POOL_WITHDRAW_UNDERFUNDED";
    case ::stellar::LIQUIDITY_POOL_WITHDRAW_LINE_FULL:
      return "LIQUIDITY_POOL_WITHDRAW_LINE_FULL";
    case ::stellar::LIQUIDITY_POOL_WITHDRAW_UNDER_MINIMUM:
      return "LIQUIDITY_POOL_WITHDRAW_UNDER_MINIMUM";
    case ::stellar::LIQUIDITY_POOL_WITHDRAW_TRUSTLINE_FROZEN:
      return "LIQUIDITY_POOL_WITHDRAW_TRUSTLINE_FROZEN";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::LIQUIDITY_POOL_WITHDRAW_SUCCESS,
      ::stellar::LIQUIDITY_POOL_WITHDRAW_MALFORMED,
      ::stellar::LIQUIDITY_POOL_WITHDRAW_NO_TRUST,
      ::stellar::LIQUIDITY_POOL_WITHDRAW_UNDERFUNDED,
      ::stellar::LIQUIDITY_POOL_WITHDRAW_LINE_FULL,
      ::stellar::LIQUIDITY_POOL_WITHDRAW_UNDER_MINIMUM,
      ::stellar::LIQUIDITY_POOL_WITHDRAW_TRUSTLINE_FROZEN
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct LiquidityPoolWithdrawResult {
  using _xdr_case_type = xdr::xdr_traits<LiquidityPoolWithdrawResultCode>::case_type;
private:
  _xdr_case_type code_;
public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<LiquidityPoolWithdrawResultCode> &_xdr_case_values() {
    static const std::vector<LiquidityPoolWithdrawResultCode> _xdr_disc_vec {
      LIQUIDITY_POOL_WITHDRAW_SUCCESS,
      LIQUIDITY_POOL_WITHDRAW_MALFORMED,
      LIQUIDITY_POOL_WITHDRAW_NO_TRUST,
      LIQUIDITY_POOL_WITHDRAW_UNDERFUNDED,
      LIQUIDITY_POOL_WITHDRAW_LINE_FULL,
      LIQUIDITY_POOL_WITHDRAW_UNDER_MINIMUM,
      LIQUIDITY_POOL_WITHDRAW_TRUSTLINE_FROZEN
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == LIQUIDITY_POOL_WITHDRAW_SUCCESS ? 0
      : which == LIQUIDITY_POOL_WITHDRAW_MALFORMED || which == LIQUIDITY_POOL_WITHDRAW_NO_TRUST || which == LIQUIDITY_POOL_WITHDRAW_UNDERFUNDED || which == LIQUIDITY_POOL_WITHDRAW_LINE_FULL || which == LIQUIDITY_POOL_WITHDRAW_UNDER_MINIMUM || which == LIQUIDITY_POOL_WITHDRAW_TRUSTLINE_FROZEN ? 0
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case LIQUIDITY_POOL_WITHDRAW_SUCCESS:
      return true;
    case LIQUIDITY_POOL_WITHDRAW_MALFORMED:
    case LIQUIDITY_POOL_WITHDRAW_NO_TRUST:
    case LIQUIDITY_POOL_WITHDRAW_UNDERFUNDED:
    case LIQUIDITY_POOL_WITHDRAW_LINE_FULL:
    case LIQUIDITY_POOL_WITHDRAW_UNDER_MINIMUM:
    case LIQUIDITY_POOL_WITHDRAW_TRUSTLINE_FROZEN:
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in LiquidityPoolWithdrawResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~LiquidityPoolWithdrawResult();
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit LiquidityPoolWithdrawResult(LiquidityPoolWithdrawResultCode which = LiquidityPoolWithdrawResultCode{}) : code_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  LiquidityPoolWithdrawResult(const LiquidityPoolWithdrawResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  LiquidityPoolWithdrawResult(LiquidityPoolWithdrawResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~LiquidityPoolWithdrawResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  LiquidityPoolWithdrawResult &operator=(const LiquidityPoolWithdrawResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~LiquidityPoolWithdrawResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  LiquidityPoolWithdrawResult &operator=(LiquidityPoolWithdrawResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~LiquidityPoolWithdrawResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
    return *this;
  }

  LiquidityPoolWithdrawResultCode code() const { return LiquidityPoolWithdrawResultCode(code_); }
  LiquidityPoolWithdrawResult &code(LiquidityPoolWithdrawResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

};
} namespace xdr {
template<> struct xdr_traits<::stellar::LiquidityPoolWithdrawResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::LiquidityPoolWithdrawResult;
  using case_type = ::stellar::LiquidityPoolWithdrawResult::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().code());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::LiquidityPoolWithdrawResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in LiquidityPoolWithdrawResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LiquidityPoolWithdrawResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in LiquidityPoolWithdrawResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LiquidityPoolWithdrawResult &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "code");
    obj.code(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

enum InvokeHostFunctionResultCode : std::int32_t {
  INVOKE_HOST_FUNCTION_SUCCESS = 0,
  INVOKE_HOST_FUNCTION_MALFORMED = -1,
  INVOKE_HOST_FUNCTION_TRAPPED = -2,
  INVOKE_HOST_FUNCTION_RESOURCE_LIMIT_EXCEEDED = -3,
  INVOKE_HOST_FUNCTION_ENTRY_ARCHIVED = -4,
  INVOKE_HOST_FUNCTION_INSUFFICIENT_REFUNDABLE_FEE = -5,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::InvokeHostFunctionResultCode>
  : xdr_integral_base<::stellar::InvokeHostFunctionResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::InvokeHostFunctionResultCode val) {
    switch (val) {
    case ::stellar::INVOKE_HOST_FUNCTION_SUCCESS:
      return "INVOKE_HOST_FUNCTION_SUCCESS";
    case ::stellar::INVOKE_HOST_FUNCTION_MALFORMED:
      return "INVOKE_HOST_FUNCTION_MALFORMED";
    case ::stellar::INVOKE_HOST_FUNCTION_TRAPPED:
      return "INVOKE_HOST_FUNCTION_TRAPPED";
    case ::stellar::INVOKE_HOST_FUNCTION_RESOURCE_LIMIT_EXCEEDED:
      return "INVOKE_HOST_FUNCTION_RESOURCE_LIMIT_EXCEEDED";
    case ::stellar::INVOKE_HOST_FUNCTION_ENTRY_ARCHIVED:
      return "INVOKE_HOST_FUNCTION_ENTRY_ARCHIVED";
    case ::stellar::INVOKE_HOST_FUNCTION_INSUFFICIENT_REFUNDABLE_FEE:
      return "INVOKE_HOST_FUNCTION_INSUFFICIENT_REFUNDABLE_FEE";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::INVOKE_HOST_FUNCTION_SUCCESS,
      ::stellar::INVOKE_HOST_FUNCTION_MALFORMED,
      ::stellar::INVOKE_HOST_FUNCTION_TRAPPED,
      ::stellar::INVOKE_HOST_FUNCTION_RESOURCE_LIMIT_EXCEEDED,
      ::stellar::INVOKE_HOST_FUNCTION_ENTRY_ARCHIVED,
      ::stellar::INVOKE_HOST_FUNCTION_INSUFFICIENT_REFUNDABLE_FEE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct InvokeHostFunctionResult {
  using _xdr_case_type = xdr::xdr_traits<InvokeHostFunctionResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    Hash success_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<InvokeHostFunctionResultCode> &_xdr_case_values() {
    static const std::vector<InvokeHostFunctionResultCode> _xdr_disc_vec {
      INVOKE_HOST_FUNCTION_SUCCESS,
      INVOKE_HOST_FUNCTION_MALFORMED,
      INVOKE_HOST_FUNCTION_TRAPPED,
      INVOKE_HOST_FUNCTION_RESOURCE_LIMIT_EXCEEDED,
      INVOKE_HOST_FUNCTION_ENTRY_ARCHIVED,
      INVOKE_HOST_FUNCTION_INSUFFICIENT_REFUNDABLE_FEE
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == INVOKE_HOST_FUNCTION_SUCCESS ? 1
      : which == INVOKE_HOST_FUNCTION_MALFORMED || which == INVOKE_HOST_FUNCTION_TRAPPED || which == INVOKE_HOST_FUNCTION_RESOURCE_LIMIT_EXCEEDED || which == INVOKE_HOST_FUNCTION_ENTRY_ARCHIVED || which == INVOKE_HOST_FUNCTION_INSUFFICIENT_REFUNDABLE_FEE ? 0
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case INVOKE_HOST_FUNCTION_SUCCESS:
      _f(&InvokeHostFunctionResult::success_, std::forward<_A>(_a)...);
      return true;
    case INVOKE_HOST_FUNCTION_MALFORMED:
    case INVOKE_HOST_FUNCTION_TRAPPED:
    case INVOKE_HOST_FUNCTION_RESOURCE_LIMIT_EXCEEDED:
    case INVOKE_HOST_FUNCTION_ENTRY_ARCHIVED:
    case INVOKE_HOST_FUNCTION_INSUFFICIENT_REFUNDABLE_FEE:
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in InvokeHostFunctionResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~InvokeHostFunctionResult();
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit InvokeHostFunctionResult(InvokeHostFunctionResultCode which = InvokeHostFunctionResultCode{}) : code_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  InvokeHostFunctionResult(const InvokeHostFunctionResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  InvokeHostFunctionResult(InvokeHostFunctionResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~InvokeHostFunctionResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  InvokeHostFunctionResult &operator=(const InvokeHostFunctionResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~InvokeHostFunctionResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  InvokeHostFunctionResult &operator=(InvokeHostFunctionResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~InvokeHostFunctionResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
    return *this;
  }

  InvokeHostFunctionResultCode code() const { return InvokeHostFunctionResultCode(code_); }
  InvokeHostFunctionResult &code(InvokeHostFunctionResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  Hash &success() {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("InvokeHostFunctionResult: success accessed when not selected");
  }
  const Hash &success() const {
    if (_xdr_field_number(code_) == 1)
      return success_;
    throw xdr::xdr_wrong_union("InvokeHostFunctionResult: success accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::InvokeHostFunctionResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::InvokeHostFunctionResult;
  using case_type = ::stellar::InvokeHostFunctionResult::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().code());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "success";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::InvokeHostFunctionResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in InvokeHostFunctionResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::InvokeHostFunctionResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in InvokeHostFunctionResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::InvokeHostFunctionResult &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "code");
    obj.code(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

enum ExtendFootprintTTLResultCode : std::int32_t {
  EXTEND_FOOTPRINT_TTL_SUCCESS = 0,
  EXTEND_FOOTPRINT_TTL_MALFORMED = -1,
  EXTEND_FOOTPRINT_TTL_RESOURCE_LIMIT_EXCEEDED = -2,
  EXTEND_FOOTPRINT_TTL_INSUFFICIENT_REFUNDABLE_FEE = -3,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ExtendFootprintTTLResultCode>
  : xdr_integral_base<::stellar::ExtendFootprintTTLResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ExtendFootprintTTLResultCode val) {
    switch (val) {
    case ::stellar::EXTEND_FOOTPRINT_TTL_SUCCESS:
      return "EXTEND_FOOTPRINT_TTL_SUCCESS";
    case ::stellar::EXTEND_FOOTPRINT_TTL_MALFORMED:
      return "EXTEND_FOOTPRINT_TTL_MALFORMED";
    case ::stellar::EXTEND_FOOTPRINT_TTL_RESOURCE_LIMIT_EXCEEDED:
      return "EXTEND_FOOTPRINT_TTL_RESOURCE_LIMIT_EXCEEDED";
    case ::stellar::EXTEND_FOOTPRINT_TTL_INSUFFICIENT_REFUNDABLE_FEE:
      return "EXTEND_FOOTPRINT_TTL_INSUFFICIENT_REFUNDABLE_FEE";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::EXTEND_FOOTPRINT_TTL_SUCCESS,
      ::stellar::EXTEND_FOOTPRINT_TTL_MALFORMED,
      ::stellar::EXTEND_FOOTPRINT_TTL_RESOURCE_LIMIT_EXCEEDED,
      ::stellar::EXTEND_FOOTPRINT_TTL_INSUFFICIENT_REFUNDABLE_FEE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct ExtendFootprintTTLResult {
  using _xdr_case_type = xdr::xdr_traits<ExtendFootprintTTLResultCode>::case_type;
private:
  _xdr_case_type code_;
public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<ExtendFootprintTTLResultCode> &_xdr_case_values() {
    static const std::vector<ExtendFootprintTTLResultCode> _xdr_disc_vec {
      EXTEND_FOOTPRINT_TTL_SUCCESS,
      EXTEND_FOOTPRINT_TTL_MALFORMED,
      EXTEND_FOOTPRINT_TTL_RESOURCE_LIMIT_EXCEEDED,
      EXTEND_FOOTPRINT_TTL_INSUFFICIENT_REFUNDABLE_FEE
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == EXTEND_FOOTPRINT_TTL_SUCCESS ? 0
      : which == EXTEND_FOOTPRINT_TTL_MALFORMED || which == EXTEND_FOOTPRINT_TTL_RESOURCE_LIMIT_EXCEEDED || which == EXTEND_FOOTPRINT_TTL_INSUFFICIENT_REFUNDABLE_FEE ? 0
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case EXTEND_FOOTPRINT_TTL_SUCCESS:
      return true;
    case EXTEND_FOOTPRINT_TTL_MALFORMED:
    case EXTEND_FOOTPRINT_TTL_RESOURCE_LIMIT_EXCEEDED:
    case EXTEND_FOOTPRINT_TTL_INSUFFICIENT_REFUNDABLE_FEE:
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in ExtendFootprintTTLResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~ExtendFootprintTTLResult();
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit ExtendFootprintTTLResult(ExtendFootprintTTLResultCode which = ExtendFootprintTTLResultCode{}) : code_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  ExtendFootprintTTLResult(const ExtendFootprintTTLResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  ExtendFootprintTTLResult(ExtendFootprintTTLResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~ExtendFootprintTTLResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  ExtendFootprintTTLResult &operator=(const ExtendFootprintTTLResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~ExtendFootprintTTLResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  ExtendFootprintTTLResult &operator=(ExtendFootprintTTLResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~ExtendFootprintTTLResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
    return *this;
  }

  ExtendFootprintTTLResultCode code() const { return ExtendFootprintTTLResultCode(code_); }
  ExtendFootprintTTLResult &code(ExtendFootprintTTLResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

};
} namespace xdr {
template<> struct xdr_traits<::stellar::ExtendFootprintTTLResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ExtendFootprintTTLResult;
  using case_type = ::stellar::ExtendFootprintTTLResult::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().code());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ExtendFootprintTTLResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in ExtendFootprintTTLResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ExtendFootprintTTLResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in ExtendFootprintTTLResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ExtendFootprintTTLResult &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "code");
    obj.code(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

enum RestoreFootprintResultCode : std::int32_t {
  RESTORE_FOOTPRINT_SUCCESS = 0,
  RESTORE_FOOTPRINT_MALFORMED = -1,
  RESTORE_FOOTPRINT_RESOURCE_LIMIT_EXCEEDED = -2,
  RESTORE_FOOTPRINT_INSUFFICIENT_REFUNDABLE_FEE = -3,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::RestoreFootprintResultCode>
  : xdr_integral_base<::stellar::RestoreFootprintResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::RestoreFootprintResultCode val) {
    switch (val) {
    case ::stellar::RESTORE_FOOTPRINT_SUCCESS:
      return "RESTORE_FOOTPRINT_SUCCESS";
    case ::stellar::RESTORE_FOOTPRINT_MALFORMED:
      return "RESTORE_FOOTPRINT_MALFORMED";
    case ::stellar::RESTORE_FOOTPRINT_RESOURCE_LIMIT_EXCEEDED:
      return "RESTORE_FOOTPRINT_RESOURCE_LIMIT_EXCEEDED";
    case ::stellar::RESTORE_FOOTPRINT_INSUFFICIENT_REFUNDABLE_FEE:
      return "RESTORE_FOOTPRINT_INSUFFICIENT_REFUNDABLE_FEE";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::RESTORE_FOOTPRINT_SUCCESS,
      ::stellar::RESTORE_FOOTPRINT_MALFORMED,
      ::stellar::RESTORE_FOOTPRINT_RESOURCE_LIMIT_EXCEEDED,
      ::stellar::RESTORE_FOOTPRINT_INSUFFICIENT_REFUNDABLE_FEE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct RestoreFootprintResult {
  using _xdr_case_type = xdr::xdr_traits<RestoreFootprintResultCode>::case_type;
private:
  _xdr_case_type code_;
public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<RestoreFootprintResultCode> &_xdr_case_values() {
    static const std::vector<RestoreFootprintResultCode> _xdr_disc_vec {
      RESTORE_FOOTPRINT_SUCCESS,
      RESTORE_FOOTPRINT_MALFORMED,
      RESTORE_FOOTPRINT_RESOURCE_LIMIT_EXCEEDED,
      RESTORE_FOOTPRINT_INSUFFICIENT_REFUNDABLE_FEE
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == RESTORE_FOOTPRINT_SUCCESS ? 0
      : which == RESTORE_FOOTPRINT_MALFORMED || which == RESTORE_FOOTPRINT_RESOURCE_LIMIT_EXCEEDED || which == RESTORE_FOOTPRINT_INSUFFICIENT_REFUNDABLE_FEE ? 0
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case RESTORE_FOOTPRINT_SUCCESS:
      return true;
    case RESTORE_FOOTPRINT_MALFORMED:
    case RESTORE_FOOTPRINT_RESOURCE_LIMIT_EXCEEDED:
    case RESTORE_FOOTPRINT_INSUFFICIENT_REFUNDABLE_FEE:
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in RestoreFootprintResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~RestoreFootprintResult();
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit RestoreFootprintResult(RestoreFootprintResultCode which = RestoreFootprintResultCode{}) : code_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  RestoreFootprintResult(const RestoreFootprintResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  RestoreFootprintResult(RestoreFootprintResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~RestoreFootprintResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  RestoreFootprintResult &operator=(const RestoreFootprintResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~RestoreFootprintResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  RestoreFootprintResult &operator=(RestoreFootprintResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~RestoreFootprintResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
    return *this;
  }

  RestoreFootprintResultCode code() const { return RestoreFootprintResultCode(code_); }
  RestoreFootprintResult &code(RestoreFootprintResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

};
} namespace xdr {
template<> struct xdr_traits<::stellar::RestoreFootprintResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::RestoreFootprintResult;
  using case_type = ::stellar::RestoreFootprintResult::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().code());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::RestoreFootprintResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in RestoreFootprintResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::RestoreFootprintResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in RestoreFootprintResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::RestoreFootprintResult &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "code");
    obj.code(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

enum OperationResultCode : std::int32_t {
  opINNER = 0,
  opBAD_AUTH = -1,
  opNO_ACCOUNT = -2,
  opNOT_SUPPORTED = -3,
  opTOO_MANY_SUBENTRIES = -4,
  opEXCEEDED_WORK_LIMIT = -5,
  opTOO_MANY_SPONSORING = -6,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::OperationResultCode>
  : xdr_integral_base<::stellar::OperationResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::OperationResultCode val) {
    switch (val) {
    case ::stellar::opINNER:
      return "opINNER";
    case ::stellar::opBAD_AUTH:
      return "opBAD_AUTH";
    case ::stellar::opNO_ACCOUNT:
      return "opNO_ACCOUNT";
    case ::stellar::opNOT_SUPPORTED:
      return "opNOT_SUPPORTED";
    case ::stellar::opTOO_MANY_SUBENTRIES:
      return "opTOO_MANY_SUBENTRIES";
    case ::stellar::opEXCEEDED_WORK_LIMIT:
      return "opEXCEEDED_WORK_LIMIT";
    case ::stellar::opTOO_MANY_SPONSORING:
      return "opTOO_MANY_SPONSORING";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::opINNER,
      ::stellar::opBAD_AUTH,
      ::stellar::opNO_ACCOUNT,
      ::stellar::opNOT_SUPPORTED,
      ::stellar::opTOO_MANY_SUBENTRIES,
      ::stellar::opEXCEEDED_WORK_LIMIT,
      ::stellar::opTOO_MANY_SPONSORING
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct OperationResult {
  struct _tr_t {
    using _xdr_case_type = xdr::xdr_traits<OperationType>::case_type;
  private:
    _xdr_case_type type_;
    union {
      CreateAccountResult createAccountResult_;
      PaymentResult paymentResult_;
      PathPaymentStrictReceiveResult pathPaymentStrictReceiveResult_;
      ManageSellOfferResult manageSellOfferResult_;
      ManageSellOfferResult createPassiveSellOfferResult_;
      SetOptionsResult setOptionsResult_;
      ChangeTrustResult changeTrustResult_;
      AllowTrustResult allowTrustResult_;
      AccountMergeResult accountMergeResult_;
      InflationResult inflationResult_;
      ManageDataResult manageDataResult_;
      BumpSequenceResult bumpSeqResult_;
      ManageBuyOfferResult manageBuyOfferResult_;
      PathPaymentStrictSendResult pathPaymentStrictSendResult_;
      CreateClaimableBalanceResult createClaimableBalanceResult_;
      ClaimClaimableBalanceResult claimClaimableBalanceResult_;
      BeginSponsoringFutureReservesResult beginSponsoringFutureReservesResult_;
      EndSponsoringFutureReservesResult endSponsoringFutureReservesResult_;
      RevokeSponsorshipResult revokeSponsorshipResult_;
      ClawbackResult clawbackResult_;
      ClawbackClaimableBalanceResult clawbackClaimableBalanceResult_;
      SetTrustLineFlagsResult setTrustLineFlagsResult_;
      LiquidityPoolDepositResult liquidityPoolDepositResult_;
      LiquidityPoolWithdrawResult liquidityPoolWithdrawResult_;
      InvokeHostFunctionResult invokeHostFunctionResult_;
      ExtendFootprintTTLResult extendFootprintTTLResult_;
      RestoreFootprintResult restoreFootprintResult_;
    };

  public:
    static Constexpr const bool _xdr_has_default_case = false;
    static const std::vector<OperationType> &_xdr_case_values() {
      static const std::vector<OperationType> _xdr_disc_vec {
        CREATE_ACCOUNT,
        PAYMENT,
        PATH_PAYMENT_STRICT_RECEIVE,
        MANAGE_SELL_OFFER,
        CREATE_PASSIVE_SELL_OFFER,
        SET_OPTIONS,
        CHANGE_TRUST,
        ALLOW_TRUST,
        ACCOUNT_MERGE,
        INFLATION,
        MANAGE_DATA,
        BUMP_SEQUENCE,
        MANAGE_BUY_OFFER,
        PATH_PAYMENT_STRICT_SEND,
        CREATE_CLAIMABLE_BALANCE,
        CLAIM_CLAIMABLE_BALANCE,
        BEGIN_SPONSORING_FUTURE_RESERVES,
        END_SPONSORING_FUTURE_RESERVES,
        REVOKE_SPONSORSHIP,
        CLAWBACK,
        CLAWBACK_CLAIMABLE_BALANCE,
        SET_TRUST_LINE_FLAGS,
        LIQUIDITY_POOL_DEPOSIT,
        LIQUIDITY_POOL_WITHDRAW,
        INVOKE_HOST_FUNCTION,
        EXTEND_FOOTPRINT_TTL,
        RESTORE_FOOTPRINT
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == CREATE_ACCOUNT ? 1
        : which == PAYMENT ? 2
        : which == PATH_PAYMENT_STRICT_RECEIVE ? 3
        : which == MANAGE_SELL_OFFER ? 4
        : which == CREATE_PASSIVE_SELL_OFFER ? 5
        : which == SET_OPTIONS ? 6
        : which == CHANGE_TRUST ? 7
        : which == ALLOW_TRUST ? 8
        : which == ACCOUNT_MERGE ? 9
        : which == INFLATION ? 10
        : which == MANAGE_DATA ? 11
        : which == BUMP_SEQUENCE ? 12
        : which == MANAGE_BUY_OFFER ? 13
        : which == PATH_PAYMENT_STRICT_SEND ? 14
        : which == CREATE_CLAIMABLE_BALANCE ? 15
        : which == CLAIM_CLAIMABLE_BALANCE ? 16
        : which == BEGIN_SPONSORING_FUTURE_RESERVES ? 17
        : which == END_SPONSORING_FUTURE_RESERVES ? 18
        : which == REVOKE_SPONSORSHIP ? 19
        : which == CLAWBACK ? 20
        : which == CLAWBACK_CLAIMABLE_BALANCE ? 21
        : which == SET_TRUST_LINE_FLAGS ? 22
        : which == LIQUIDITY_POOL_DEPOSIT ? 23
        : which == LIQUIDITY_POOL_WITHDRAW ? 24
        : which == INVOKE_HOST_FUNCTION ? 25
        : which == EXTEND_FOOTPRINT_TTL ? 26
        : which == RESTORE_FOOTPRINT ? 27
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case CREATE_ACCOUNT:
        _f(&_tr_t::createAccountResult_, std::forward<_A>(_a)...);
        return true;
      case PAYMENT:
        _f(&_tr_t::paymentResult_, std::forward<_A>(_a)...);
        return true;
      case PATH_PAYMENT_STRICT_RECEIVE:
        _f(&_tr_t::pathPaymentStrictReceiveResult_, std::forward<_A>(_a)...);
        return true;
      case MANAGE_SELL_OFFER:
        _f(&_tr_t::manageSellOfferResult_, std::forward<_A>(_a)...);
        return true;
      case CREATE_PASSIVE_SELL_OFFER:
        _f(&_tr_t::createPassiveSellOfferResult_, std::forward<_A>(_a)...);
        return true;
      case SET_OPTIONS:
        _f(&_tr_t::setOptionsResult_, std::forward<_A>(_a)...);
        return true;
      case CHANGE_TRUST:
        _f(&_tr_t::changeTrustResult_, std::forward<_A>(_a)...);
        return true;
      case ALLOW_TRUST:
        _f(&_tr_t::allowTrustResult_, std::forward<_A>(_a)...);
        return true;
      case ACCOUNT_MERGE:
        _f(&_tr_t::accountMergeResult_, std::forward<_A>(_a)...);
        return true;
      case INFLATION:
        _f(&_tr_t::inflationResult_, std::forward<_A>(_a)...);
        return true;
      case MANAGE_DATA:
        _f(&_tr_t::manageDataResult_, std::forward<_A>(_a)...);
        return true;
      case BUMP_SEQUENCE:
        _f(&_tr_t::bumpSeqResult_, std::forward<_A>(_a)...);
        return true;
      case MANAGE_BUY_OFFER:
        _f(&_tr_t::manageBuyOfferResult_, std::forward<_A>(_a)...);
        return true;
      case PATH_PAYMENT_STRICT_SEND:
        _f(&_tr_t::pathPaymentStrictSendResult_, std::forward<_A>(_a)...);
        return true;
      case CREATE_CLAIMABLE_BALANCE:
        _f(&_tr_t::createClaimableBalanceResult_, std::forward<_A>(_a)...);
        return true;
      case CLAIM_CLAIMABLE_BALANCE:
        _f(&_tr_t::claimClaimableBalanceResult_, std::forward<_A>(_a)...);
        return true;
      case BEGIN_SPONSORING_FUTURE_RESERVES:
        _f(&_tr_t::beginSponsoringFutureReservesResult_, std::forward<_A>(_a)...);
        return true;
      case END_SPONSORING_FUTURE_RESERVES:
        _f(&_tr_t::endSponsoringFutureReservesResult_, std::forward<_A>(_a)...);
        return true;
      case REVOKE_SPONSORSHIP:
        _f(&_tr_t::revokeSponsorshipResult_, std::forward<_A>(_a)...);
        return true;
      case CLAWBACK:
        _f(&_tr_t::clawbackResult_, std::forward<_A>(_a)...);
        return true;
      case CLAWBACK_CLAIMABLE_BALANCE:
        _f(&_tr_t::clawbackClaimableBalanceResult_, std::forward<_A>(_a)...);
        return true;
      case SET_TRUST_LINE_FLAGS:
        _f(&_tr_t::setTrustLineFlagsResult_, std::forward<_A>(_a)...);
        return true;
      case LIQUIDITY_POOL_DEPOSIT:
        _f(&_tr_t::liquidityPoolDepositResult_, std::forward<_A>(_a)...);
        return true;
      case LIQUIDITY_POOL_WITHDRAW:
        _f(&_tr_t::liquidityPoolWithdrawResult_, std::forward<_A>(_a)...);
        return true;
      case INVOKE_HOST_FUNCTION:
        _f(&_tr_t::invokeHostFunctionResult_, std::forward<_A>(_a)...);
        return true;
      case EXTEND_FOOTPRINT_TTL:
        _f(&_tr_t::extendFootprintTTLResult_, std::forward<_A>(_a)...);
        return true;
      case RESTORE_FOOTPRINT:
        _f(&_tr_t::restoreFootprintResult_, std::forward<_A>(_a)...);
        return true;
      }
      return false;
    }

    _xdr_case_type _xdr_discriminant() const { return type_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of type in _tr_t");
      if (fnum != _xdr_field_number(type_)) {
        this->~_tr_t();
        type_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
      }
      else
        type_ = which;
    }
    explicit _tr_t(OperationType which = OperationType{}) : type_(which) {
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
    }
    _tr_t(const _tr_t &source) : type_(source.type_) {
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this, source);
    }
    _tr_t(_tr_t &&source) : type_(source.type_) {
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this,
                        std::move(source));
    }
    ~_tr_t() { _xdr_with_mem_ptr(xdr::field_destructor, type_, *this); }
    _tr_t &operator=(const _tr_t &source) {
      if (_xdr_field_number(type_)
          == _xdr_field_number(source.type_))
        _xdr_with_mem_ptr(xdr::field_assigner, type_, *this, source);
      else {
        this->~_tr_t();
        type_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this, source);
      }
      type_ = source.type_;
      return *this;
    }
    _tr_t &operator=(_tr_t &&source) {
      if (_xdr_field_number(type_)
           == _xdr_field_number(source.type_))
        _xdr_with_mem_ptr(xdr::field_assigner, type_, *this,
                          std::move(source));
      else {
        this->~_tr_t();
        type_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this,
                          std::move(source));
      }
      type_ = source.type_;
      return *this;
    }

    OperationType type() const { return OperationType(type_); }
    _tr_t &type(OperationType _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant(_xdr_d, _xdr_validate);
      return *this;
    }

    CreateAccountResult &createAccountResult() {
      if (_xdr_field_number(type_) == 1)
        return createAccountResult_;
      throw xdr::xdr_wrong_union("_tr_t: createAccountResult accessed when not selected");
    }
    const CreateAccountResult &createAccountResult() const {
      if (_xdr_field_number(type_) == 1)
        return createAccountResult_;
      throw xdr::xdr_wrong_union("_tr_t: createAccountResult accessed when not selected");
    }
    PaymentResult &paymentResult() {
      if (_xdr_field_number(type_) == 2)
        return paymentResult_;
      throw xdr::xdr_wrong_union("_tr_t: paymentResult accessed when not selected");
    }
    const PaymentResult &paymentResult() const {
      if (_xdr_field_number(type_) == 2)
        return paymentResult_;
      throw xdr::xdr_wrong_union("_tr_t: paymentResult accessed when not selected");
    }
    PathPaymentStrictReceiveResult &pathPaymentStrictReceiveResult() {
      if (_xdr_field_number(type_) == 3)
        return pathPaymentStrictReceiveResult_;
      throw xdr::xdr_wrong_union("_tr_t: pathPaymentStrictReceiveResult accessed when not selected");
    }
    const PathPaymentStrictReceiveResult &pathPaymentStrictReceiveResult() const {
      if (_xdr_field_number(type_) == 3)
        return pathPaymentStrictReceiveResult_;
      throw xdr::xdr_wrong_union("_tr_t: pathPaymentStrictReceiveResult accessed when not selected");
    }
    ManageSellOfferResult &manageSellOfferResult() {
      if (_xdr_field_number(type_) == 4)
        return manageSellOfferResult_;
      throw xdr::xdr_wrong_union("_tr_t: manageSellOfferResult accessed when not selected");
    }
    const ManageSellOfferResult &manageSellOfferResult() const {
      if (_xdr_field_number(type_) == 4)
        return manageSellOfferResult_;
      throw xdr::xdr_wrong_union("_tr_t: manageSellOfferResult accessed when not selected");
    }
    ManageSellOfferResult &createPassiveSellOfferResult() {
      if (_xdr_field_number(type_) == 5)
        return createPassiveSellOfferResult_;
      throw xdr::xdr_wrong_union("_tr_t: createPassiveSellOfferResult accessed when not selected");
    }
    const ManageSellOfferResult &createPassiveSellOfferResult() const {
      if (_xdr_field_number(type_) == 5)
        return createPassiveSellOfferResult_;
      throw xdr::xdr_wrong_union("_tr_t: createPassiveSellOfferResult accessed when not selected");
    }
    SetOptionsResult &setOptionsResult() {
      if (_xdr_field_number(type_) == 6)
        return setOptionsResult_;
      throw xdr::xdr_wrong_union("_tr_t: setOptionsResult accessed when not selected");
    }
    const SetOptionsResult &setOptionsResult() const {
      if (_xdr_field_number(type_) == 6)
        return setOptionsResult_;
      throw xdr::xdr_wrong_union("_tr_t: setOptionsResult accessed when not selected");
    }
    ChangeTrustResult &changeTrustResult() {
      if (_xdr_field_number(type_) == 7)
        return changeTrustResult_;
      throw xdr::xdr_wrong_union("_tr_t: changeTrustResult accessed when not selected");
    }
    const ChangeTrustResult &changeTrustResult() const {
      if (_xdr_field_number(type_) == 7)
        return changeTrustResult_;
      throw xdr::xdr_wrong_union("_tr_t: changeTrustResult accessed when not selected");
    }
    AllowTrustResult &allowTrustResult() {
      if (_xdr_field_number(type_) == 8)
        return allowTrustResult_;
      throw xdr::xdr_wrong_union("_tr_t: allowTrustResult accessed when not selected");
    }
    const AllowTrustResult &allowTrustResult() const {
      if (_xdr_field_number(type_) == 8)
        return allowTrustResult_;
      throw xdr::xdr_wrong_union("_tr_t: allowTrustResult accessed when not selected");
    }
    AccountMergeResult &accountMergeResult() {
      if (_xdr_field_number(type_) == 9)
        return accountMergeResult_;
      throw xdr::xdr_wrong_union("_tr_t: accountMergeResult accessed when not selected");
    }
    const AccountMergeResult &accountMergeResult() const {
      if (_xdr_field_number(type_) == 9)
        return accountMergeResult_;
      throw xdr::xdr_wrong_union("_tr_t: accountMergeResult accessed when not selected");
    }
    InflationResult &inflationResult() {
      if (_xdr_field_number(type_) == 10)
        return inflationResult_;
      throw xdr::xdr_wrong_union("_tr_t: inflationResult accessed when not selected");
    }
    const InflationResult &inflationResult() const {
      if (_xdr_field_number(type_) == 10)
        return inflationResult_;
      throw xdr::xdr_wrong_union("_tr_t: inflationResult accessed when not selected");
    }
    ManageDataResult &manageDataResult() {
      if (_xdr_field_number(type_) == 11)
        return manageDataResult_;
      throw xdr::xdr_wrong_union("_tr_t: manageDataResult accessed when not selected");
    }
    const ManageDataResult &manageDataResult() const {
      if (_xdr_field_number(type_) == 11)
        return manageDataResult_;
      throw xdr::xdr_wrong_union("_tr_t: manageDataResult accessed when not selected");
    }
    BumpSequenceResult &bumpSeqResult() {
      if (_xdr_field_number(type_) == 12)
        return bumpSeqResult_;
      throw xdr::xdr_wrong_union("_tr_t: bumpSeqResult accessed when not selected");
    }
    const BumpSequenceResult &bumpSeqResult() const {
      if (_xdr_field_number(type_) == 12)
        return bumpSeqResult_;
      throw xdr::xdr_wrong_union("_tr_t: bumpSeqResult accessed when not selected");
    }
    ManageBuyOfferResult &manageBuyOfferResult() {
      if (_xdr_field_number(type_) == 13)
        return manageBuyOfferResult_;
      throw xdr::xdr_wrong_union("_tr_t: manageBuyOfferResult accessed when not selected");
    }
    const ManageBuyOfferResult &manageBuyOfferResult() const {
      if (_xdr_field_number(type_) == 13)
        return manageBuyOfferResult_;
      throw xdr::xdr_wrong_union("_tr_t: manageBuyOfferResult accessed when not selected");
    }
    PathPaymentStrictSendResult &pathPaymentStrictSendResult() {
      if (_xdr_field_number(type_) == 14)
        return pathPaymentStrictSendResult_;
      throw xdr::xdr_wrong_union("_tr_t: pathPaymentStrictSendResult accessed when not selected");
    }
    const PathPaymentStrictSendResult &pathPaymentStrictSendResult() const {
      if (_xdr_field_number(type_) == 14)
        return pathPaymentStrictSendResult_;
      throw xdr::xdr_wrong_union("_tr_t: pathPaymentStrictSendResult accessed when not selected");
    }
    CreateClaimableBalanceResult &createClaimableBalanceResult() {
      if (_xdr_field_number(type_) == 15)
        return createClaimableBalanceResult_;
      throw xdr::xdr_wrong_union("_tr_t: createClaimableBalanceResult accessed when not selected");
    }
    const CreateClaimableBalanceResult &createClaimableBalanceResult() const {
      if (_xdr_field_number(type_) == 15)
        return createClaimableBalanceResult_;
      throw xdr::xdr_wrong_union("_tr_t: createClaimableBalanceResult accessed when not selected");
    }
    ClaimClaimableBalanceResult &claimClaimableBalanceResult() {
      if (_xdr_field_number(type_) == 16)
        return claimClaimableBalanceResult_;
      throw xdr::xdr_wrong_union("_tr_t: claimClaimableBalanceResult accessed when not selected");
    }
    const ClaimClaimableBalanceResult &claimClaimableBalanceResult() const {
      if (_xdr_field_number(type_) == 16)
        return claimClaimableBalanceResult_;
      throw xdr::xdr_wrong_union("_tr_t: claimClaimableBalanceResult accessed when not selected");
    }
    BeginSponsoringFutureReservesResult &beginSponsoringFutureReservesResult() {
      if (_xdr_field_number(type_) == 17)
        return beginSponsoringFutureReservesResult_;
      throw xdr::xdr_wrong_union("_tr_t: beginSponsoringFutureReservesResult accessed when not selected");
    }
    const BeginSponsoringFutureReservesResult &beginSponsoringFutureReservesResult() const {
      if (_xdr_field_number(type_) == 17)
        return beginSponsoringFutureReservesResult_;
      throw xdr::xdr_wrong_union("_tr_t: beginSponsoringFutureReservesResult accessed when not selected");
    }
    EndSponsoringFutureReservesResult &endSponsoringFutureReservesResult() {
      if (_xdr_field_number(type_) == 18)
        return endSponsoringFutureReservesResult_;
      throw xdr::xdr_wrong_union("_tr_t: endSponsoringFutureReservesResult accessed when not selected");
    }
    const EndSponsoringFutureReservesResult &endSponsoringFutureReservesResult() const {
      if (_xdr_field_number(type_) == 18)
        return endSponsoringFutureReservesResult_;
      throw xdr::xdr_wrong_union("_tr_t: endSponsoringFutureReservesResult accessed when not selected");
    }
    RevokeSponsorshipResult &revokeSponsorshipResult() {
      if (_xdr_field_number(type_) == 19)
        return revokeSponsorshipResult_;
      throw xdr::xdr_wrong_union("_tr_t: revokeSponsorshipResult accessed when not selected");
    }
    const RevokeSponsorshipResult &revokeSponsorshipResult() const {
      if (_xdr_field_number(type_) == 19)
        return revokeSponsorshipResult_;
      throw xdr::xdr_wrong_union("_tr_t: revokeSponsorshipResult accessed when not selected");
    }
    ClawbackResult &clawbackResult() {
      if (_xdr_field_number(type_) == 20)
        return clawbackResult_;
      throw xdr::xdr_wrong_union("_tr_t: clawbackResult accessed when not selected");
    }
    const ClawbackResult &clawbackResult() const {
      if (_xdr_field_number(type_) == 20)
        return clawbackResult_;
      throw xdr::xdr_wrong_union("_tr_t: clawbackResult accessed when not selected");
    }
    ClawbackClaimableBalanceResult &clawbackClaimableBalanceResult() {
      if (_xdr_field_number(type_) == 21)
        return clawbackClaimableBalanceResult_;
      throw xdr::xdr_wrong_union("_tr_t: clawbackClaimableBalanceResult accessed when not selected");
    }
    const ClawbackClaimableBalanceResult &clawbackClaimableBalanceResult() const {
      if (_xdr_field_number(type_) == 21)
        return clawbackClaimableBalanceResult_;
      throw xdr::xdr_wrong_union("_tr_t: clawbackClaimableBalanceResult accessed when not selected");
    }
    SetTrustLineFlagsResult &setTrustLineFlagsResult() {
      if (_xdr_field_number(type_) == 22)
        return setTrustLineFlagsResult_;
      throw xdr::xdr_wrong_union("_tr_t: setTrustLineFlagsResult accessed when not selected");
    }
    const SetTrustLineFlagsResult &setTrustLineFlagsResult() const {
      if (_xdr_field_number(type_) == 22)
        return setTrustLineFlagsResult_;
      throw xdr::xdr_wrong_union("_tr_t: setTrustLineFlagsResult accessed when not selected");
    }
    LiquidityPoolDepositResult &liquidityPoolDepositResult() {
      if (_xdr_field_number(type_) == 23)
        return liquidityPoolDepositResult_;
      throw xdr::xdr_wrong_union("_tr_t: liquidityPoolDepositResult accessed when not selected");
    }
    const LiquidityPoolDepositResult &liquidityPoolDepositResult() const {
      if (_xdr_field_number(type_) == 23)
        return liquidityPoolDepositResult_;
      throw xdr::xdr_wrong_union("_tr_t: liquidityPoolDepositResult accessed when not selected");
    }
    LiquidityPoolWithdrawResult &liquidityPoolWithdrawResult() {
      if (_xdr_field_number(type_) == 24)
        return liquidityPoolWithdrawResult_;
      throw xdr::xdr_wrong_union("_tr_t: liquidityPoolWithdrawResult accessed when not selected");
    }
    const LiquidityPoolWithdrawResult &liquidityPoolWithdrawResult() const {
      if (_xdr_field_number(type_) == 24)
        return liquidityPoolWithdrawResult_;
      throw xdr::xdr_wrong_union("_tr_t: liquidityPoolWithdrawResult accessed when not selected");
    }
    InvokeHostFunctionResult &invokeHostFunctionResult() {
      if (_xdr_field_number(type_) == 25)
        return invokeHostFunctionResult_;
      throw xdr::xdr_wrong_union("_tr_t: invokeHostFunctionResult accessed when not selected");
    }
    const InvokeHostFunctionResult &invokeHostFunctionResult() const {
      if (_xdr_field_number(type_) == 25)
        return invokeHostFunctionResult_;
      throw xdr::xdr_wrong_union("_tr_t: invokeHostFunctionResult accessed when not selected");
    }
    ExtendFootprintTTLResult &extendFootprintTTLResult() {
      if (_xdr_field_number(type_) == 26)
        return extendFootprintTTLResult_;
      throw xdr::xdr_wrong_union("_tr_t: extendFootprintTTLResult accessed when not selected");
    }
    const ExtendFootprintTTLResult &extendFootprintTTLResult() const {
      if (_xdr_field_number(type_) == 26)
        return extendFootprintTTLResult_;
      throw xdr::xdr_wrong_union("_tr_t: extendFootprintTTLResult accessed when not selected");
    }
    RestoreFootprintResult &restoreFootprintResult() {
      if (_xdr_field_number(type_) == 27)
        return restoreFootprintResult_;
      throw xdr::xdr_wrong_union("_tr_t: restoreFootprintResult accessed when not selected");
    }
    const RestoreFootprintResult &restoreFootprintResult() const {
      if (_xdr_field_number(type_) == 27)
        return restoreFootprintResult_;
      throw xdr::xdr_wrong_union("_tr_t: restoreFootprintResult accessed when not selected");
    }
  };

  using _xdr_case_type = xdr::xdr_traits<OperationResultCode>::case_type;
private:
  _xdr_case_type code_;
  union {
    _tr_t tr_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<OperationResultCode> &_xdr_case_values() {
    static const std::vector<OperationResultCode> _xdr_disc_vec {
      opINNER,
      opBAD_AUTH,
      opNO_ACCOUNT,
      opNOT_SUPPORTED,
      opTOO_MANY_SUBENTRIES,
      opEXCEEDED_WORK_LIMIT,
      opTOO_MANY_SPONSORING
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == opINNER ? 1
      : which == opBAD_AUTH || which == opNO_ACCOUNT || which == opNOT_SUPPORTED || which == opTOO_MANY_SUBENTRIES || which == opEXCEEDED_WORK_LIMIT || which == opTOO_MANY_SPONSORING ? 0
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case opINNER:
      _f(&OperationResult::tr_, std::forward<_A>(_a)...);
      return true;
    case opBAD_AUTH:
    case opNO_ACCOUNT:
    case opNOT_SUPPORTED:
    case opTOO_MANY_SUBENTRIES:
    case opEXCEEDED_WORK_LIMIT:
    case opTOO_MANY_SPONSORING:
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return code_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of code in OperationResult");
    if (fnum != _xdr_field_number(code_)) {
      this->~OperationResult();
      code_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    else
      code_ = which;
  }
  explicit OperationResult(OperationResultCode which = OperationResultCode{}) : code_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
  }
  OperationResult(const OperationResult &source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
  }
  OperationResult(OperationResult &&source) : code_(source.code_) {
    _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                      std::move(source));
  }
  ~OperationResult() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
  OperationResult &operator=(const OperationResult &source) {
    if (_xdr_field_number(code_)
        == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
    else {
      this->~OperationResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
    }
    code_ = source.code_;
    return *this;
  }
  OperationResult &operator=(OperationResult &&source) {
    if (_xdr_field_number(code_)
         == _xdr_field_number(source.code_))
      _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                        std::move(source));
    else {
      this->~OperationResult();
      code_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                        std::move(source));
    }
    code_ = source.code_;
    return *this;
  }

  OperationResultCode code() const { return OperationResultCode(code_); }
  OperationResult &code(OperationResultCode _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  _tr_t &tr() {
    if (_xdr_field_number(code_) == 1)
      return tr_;
    throw xdr::xdr_wrong_union("OperationResult: tr accessed when not selected");
  }
  const _tr_t &tr() const {
    if (_xdr_field_number(code_) == 1)
      return tr_;
    throw xdr::xdr_wrong_union("OperationResult: tr accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::OperationResult::_tr_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::OperationResult::_tr_t;
  using case_type = ::stellar::OperationResult::_tr_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().type());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "createAccountResult";
    case 2:
      return "paymentResult";
    case 3:
      return "pathPaymentStrictReceiveResult";
    case 4:
      return "manageSellOfferResult";
    case 5:
      return "createPassiveSellOfferResult";
    case 6:
      return "setOptionsResult";
    case 7:
      return "changeTrustResult";
    case 8:
      return "allowTrustResult";
    case 9:
      return "accountMergeResult";
    case 10:
      return "inflationResult";
    case 11:
      return "manageDataResult";
    case 12:
      return "bumpSeqResult";
    case 13:
      return "manageBuyOfferResult";
    case 14:
      return "pathPaymentStrictSendResult";
    case 15:
      return "createClaimableBalanceResult";
    case 16:
      return "claimClaimableBalanceResult";
    case 17:
      return "beginSponsoringFutureReservesResult";
    case 18:
      return "endSponsoringFutureReservesResult";
    case 19:
      return "revokeSponsorshipResult";
    case 20:
      return "clawbackResult";
    case 21:
      return "clawbackClaimableBalanceResult";
    case 22:
      return "setTrustLineFlagsResult";
    case 23:
      return "liquidityPoolDepositResult";
    case 24:
      return "liquidityPoolWithdrawResult";
    case 25:
      return "invokeHostFunctionResult";
    case 26:
      return "extendFootprintTTLResult";
    case 27:
      return "restoreFootprintResult";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::OperationResult::_tr_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of type in _tr_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::OperationResult::_tr_t &obj) {
    xdr::archive(ar, obj.type(), "type");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of type in _tr_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::OperationResult::_tr_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "type");
    obj.type(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::OperationResult> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::OperationResult;
  using case_type = ::stellar::OperationResult::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().code());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "tr";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::OperationResult &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in OperationResult");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::OperationResult &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in OperationResult");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::OperationResult &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "code");
    obj.code(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

enum TransactionResultCode : std::int32_t {
  txFEE_BUMP_INNER_SUCCESS = 1,
  txSUCCESS = 0,
  txFAILED = -1,
  txTOO_EARLY = -2,
  txTOO_LATE = -3,
  txMISSING_OPERATION = -4,
  txBAD_SEQ = -5,
  txBAD_AUTH = -6,
  txINSUFFICIENT_BALANCE = -7,
  txNO_ACCOUNT = -8,
  txINSUFFICIENT_FEE = -9,
  txBAD_AUTH_EXTRA = -10,
  txINTERNAL_ERROR = -11,
  txNOT_SUPPORTED = -12,
  txFEE_BUMP_INNER_FAILED = -13,
  txBAD_SPONSORSHIP = -14,
  txBAD_MIN_SEQ_AGE_OR_GAP = -15,
  txMALFORMED = -16,
  txSOROBAN_INVALID = -17,
  txFROZEN_KEY_ACCESSED = -18,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::TransactionResultCode>
  : xdr_integral_base<::stellar::TransactionResultCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::TransactionResultCode val) {
    switch (val) {
    case ::stellar::txFEE_BUMP_INNER_SUCCESS:
      return "txFEE_BUMP_INNER_SUCCESS";
    case ::stellar::txSUCCESS:
      return "txSUCCESS";
    case ::stellar::txFAILED:
      return "txFAILED";
    case ::stellar::txTOO_EARLY:
      return "txTOO_EARLY";
    case ::stellar::txTOO_LATE:
      return "txTOO_LATE";
    case ::stellar::txMISSING_OPERATION:
      return "txMISSING_OPERATION";
    case ::stellar::txBAD_SEQ:
      return "txBAD_SEQ";
    case ::stellar::txBAD_AUTH:
      return "txBAD_AUTH";
    case ::stellar::txINSUFFICIENT_BALANCE:
      return "txINSUFFICIENT_BALANCE";
    case ::stellar::txNO_ACCOUNT:
      return "txNO_ACCOUNT";
    case ::stellar::txINSUFFICIENT_FEE:
      return "txINSUFFICIENT_FEE";
    case ::stellar::txBAD_AUTH_EXTRA:
      return "txBAD_AUTH_EXTRA";
    case ::stellar::txINTERNAL_ERROR:
      return "txINTERNAL_ERROR";
    case ::stellar::txNOT_SUPPORTED:
      return "txNOT_SUPPORTED";
    case ::stellar::txFEE_BUMP_INNER_FAILED:
      return "txFEE_BUMP_INNER_FAILED";
    case ::stellar::txBAD_SPONSORSHIP:
      return "txBAD_SPONSORSHIP";
    case ::stellar::txBAD_MIN_SEQ_AGE_OR_GAP:
      return "txBAD_MIN_SEQ_AGE_OR_GAP";
    case ::stellar::txMALFORMED:
      return "txMALFORMED";
    case ::stellar::txSOROBAN_INVALID:
      return "txSOROBAN_INVALID";
    case ::stellar::txFROZEN_KEY_ACCESSED:
      return "txFROZEN_KEY_ACCESSED";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::txFEE_BUMP_INNER_SUCCESS,
      ::stellar::txSUCCESS,
      ::stellar::txFAILED,
      ::stellar::txTOO_EARLY,
      ::stellar::txTOO_LATE,
      ::stellar::txMISSING_OPERATION,
      ::stellar::txBAD_SEQ,
      ::stellar::txBAD_AUTH,
      ::stellar::txINSUFFICIENT_BALANCE,
      ::stellar::txNO_ACCOUNT,
      ::stellar::txINSUFFICIENT_FEE,
      ::stellar::txBAD_AUTH_EXTRA,
      ::stellar::txINTERNAL_ERROR,
      ::stellar::txNOT_SUPPORTED,
      ::stellar::txFEE_BUMP_INNER_FAILED,
      ::stellar::txBAD_SPONSORSHIP,
      ::stellar::txBAD_MIN_SEQ_AGE_OR_GAP,
      ::stellar::txMALFORMED,
      ::stellar::txSOROBAN_INVALID,
      ::stellar::txFROZEN_KEY_ACCESSED
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct InnerTransactionResult {
  struct _result_t {
    using _xdr_case_type = xdr::xdr_traits<TransactionResultCode>::case_type;
  private:
    _xdr_case_type code_;
    union {
      xdr::xvector<OperationResult> results_;
    };

  public:
    static Constexpr const bool _xdr_has_default_case = false;
    static const std::vector<TransactionResultCode> &_xdr_case_values() {
      static const std::vector<TransactionResultCode> _xdr_disc_vec {
        txSUCCESS,
        txFAILED,
        txTOO_EARLY,
        txTOO_LATE,
        txMISSING_OPERATION,
        txBAD_SEQ,
        txBAD_AUTH,
        txINSUFFICIENT_BALANCE,
        txNO_ACCOUNT,
        txINSUFFICIENT_FEE,
        txBAD_AUTH_EXTRA,
        txINTERNAL_ERROR,
        txNOT_SUPPORTED,
        txBAD_SPONSORSHIP,
        txBAD_MIN_SEQ_AGE_OR_GAP,
        txMALFORMED,
        txSOROBAN_INVALID,
        txFROZEN_KEY_ACCESSED
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == txSUCCESS || which == txFAILED ? 1
        : which == txTOO_EARLY || which == txTOO_LATE || which == txMISSING_OPERATION || which == txBAD_SEQ || which == txBAD_AUTH || which == txINSUFFICIENT_BALANCE || which == txNO_ACCOUNT || which == txINSUFFICIENT_FEE || which == txBAD_AUTH_EXTRA || which == txINTERNAL_ERROR || which == txNOT_SUPPORTED || which == txBAD_SPONSORSHIP || which == txBAD_MIN_SEQ_AGE_OR_GAP || which == txMALFORMED || which == txSOROBAN_INVALID || which == txFROZEN_KEY_ACCESSED ? 0
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case txSUCCESS:
      case txFAILED:
        _f(&_result_t::results_, std::forward<_A>(_a)...);
        return true;
      case txTOO_EARLY:
      case txTOO_LATE:
      case txMISSING_OPERATION:
      case txBAD_SEQ:
      case txBAD_AUTH:
      case txINSUFFICIENT_BALANCE:
      case txNO_ACCOUNT:
      case txINSUFFICIENT_FEE:
      case txBAD_AUTH_EXTRA:
      case txINTERNAL_ERROR:
      case txNOT_SUPPORTED:
      case txBAD_SPONSORSHIP:
      case txBAD_MIN_SEQ_AGE_OR_GAP:
      case txMALFORMED:
      case txSOROBAN_INVALID:
      case txFROZEN_KEY_ACCESSED:
        return true;
      }
      return false;
    }

    _xdr_case_type _xdr_discriminant() const { return code_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of code in _result_t");
      if (fnum != _xdr_field_number(code_)) {
        this->~_result_t();
        code_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
      }
      else
        code_ = which;
    }
    explicit _result_t(TransactionResultCode which = TransactionResultCode{}) : code_(which) {
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    _result_t(const _result_t &source) : code_(source.code_) {
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
    }
    _result_t(_result_t &&source) : code_(source.code_) {
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                        std::move(source));
    }
    ~_result_t() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
    _result_t &operator=(const _result_t &source) {
      if (_xdr_field_number(code_)
          == _xdr_field_number(source.code_))
        _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
      else {
        this->~_result_t();
        code_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
      }
      code_ = source.code_;
      return *this;
    }
    _result_t &operator=(_result_t &&source) {
      if (_xdr_field_number(code_)
           == _xdr_field_number(source.code_))
        _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                          std::move(source));
      else {
        this->~_result_t();
        code_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                          std::move(source));
      }
      code_ = source.code_;
      return *this;
    }

    TransactionResultCode code() const { return TransactionResultCode(code_); }
    _result_t &code(TransactionResultCode _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant(_xdr_d, _xdr_validate);
      return *this;
    }

    xdr::xvector<OperationResult> &results() {
      if (_xdr_field_number(code_) == 1)
        return results_;
      throw xdr::xdr_wrong_union("_result_t: results accessed when not selected");
    }
    const xdr::xvector<OperationResult> &results() const {
      if (_xdr_field_number(code_) == 1)
        return results_;
      throw xdr::xdr_wrong_union("_result_t: results accessed when not selected");
    }
  };
  struct _ext_t {
    using _xdr_case_type = xdr::xdr_traits<int>::case_type;
  private:
    _xdr_case_type v_;
  public:
    static Constexpr const bool _xdr_has_default_case = false;
    static const std::vector<int> &_xdr_case_values() {
      static const std::vector<int> _xdr_disc_vec {
        0
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == 0 ? 0
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case 0:
        return true;
      }
      return false;
    }

    _xdr_case_type _xdr_discriminant() const { return v_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of v in _ext_t");
      if (fnum != _xdr_field_number(v_)) {
        this->~_ext_t();
        v_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
      }
      else
        v_ = which;
    }
    explicit _ext_t(std::int32_t which = std::int32_t{}) : v_(which) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
    }
    _ext_t(const _ext_t &source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this, source);
    }
    _ext_t(_ext_t &&source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this,
                        std::move(source));
    }
    ~_ext_t() { _xdr_with_mem_ptr(xdr::field_destructor, v_, *this); }
    _ext_t &operator=(const _ext_t &source) {
      if (_xdr_field_number(v_)
          == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this, source);
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this, source);
      }
      v_ = source.v_;
      return *this;
    }
    _ext_t &operator=(_ext_t &&source) {
      if (_xdr_field_number(v_)
           == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this,
                          std::move(source));
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this,
                          std::move(source));
      }
      v_ = source.v_;
      return *this;
    }

    std::int32_t v() const { return std::int32_t(v_); }
    _ext_t &v(int _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant(_xdr_d, _xdr_validate);
      return *this;
    }

  };

  int64 feeCharged{};
  _result_t result{};
  _ext_t ext{};

  InnerTransactionResult() = default;
  template<typename _feeCharged_T,
           typename _result_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<int64, _feeCharged_T>::value
                          && std::is_constructible<_result_t, _result_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit InnerTransactionResult(_feeCharged_T &&_feeCharged,
                                  _result_T &&_result,
                                  _ext_T &&_ext)
    : feeCharged(std::forward<_feeCharged_T>(_feeCharged)),
      result(std::forward<_result_T>(_result)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::InnerTransactionResult::_result_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::InnerTransactionResult::_result_t;
  using case_type = ::stellar::InnerTransactionResult::_result_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().code());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "results";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::InnerTransactionResult::_result_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in _result_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::InnerTransactionResult::_result_t &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in _result_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::InnerTransactionResult::_result_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "code");
    obj.code(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::InnerTransactionResult::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::InnerTransactionResult::_ext_t;
  using case_type = ::stellar::InnerTransactionResult::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::InnerTransactionResult::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::InnerTransactionResult::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::InnerTransactionResult::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.v(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::InnerTransactionResult>
  : xdr_struct_base<field_ptr<::stellar::InnerTransactionResult,
                              decltype(::stellar::InnerTransactionResult::feeCharged),
                              &::stellar::InnerTransactionResult::feeCharged>,
                    field_ptr<::stellar::InnerTransactionResult,
                              decltype(::stellar::InnerTransactionResult::result),
                              &::stellar::InnerTransactionResult::result>,
                    field_ptr<::stellar::InnerTransactionResult,
                              decltype(::stellar::InnerTransactionResult::ext),
                              &::stellar::InnerTransactionResult::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::InnerTransactionResult &obj) {
    archive(ar, obj.feeCharged, "feeCharged");
    archive(ar, obj.result, "result");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::InnerTransactionResult &obj) {
    archive(ar, obj.feeCharged, "feeCharged");
    archive(ar, obj.result, "result");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct InnerTransactionResultPair {
  Hash transactionHash{};
  InnerTransactionResult result{};

  InnerTransactionResultPair() = default;
  template<typename _transactionHash_T,
           typename _result_T,
           typename = typename
           std::enable_if<std::is_constructible<Hash, _transactionHash_T>::value
                          && std::is_constructible<InnerTransactionResult, _result_T>::value
                         >::type>
  explicit InnerTransactionResultPair(_transactionHash_T &&_transactionHash,
                                      _result_T &&_result)
    : transactionHash(std::forward<_transactionHash_T>(_transactionHash)),
      result(std::forward<_result_T>(_result)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::InnerTransactionResultPair>
  : xdr_struct_base<field_ptr<::stellar::InnerTransactionResultPair,
                              decltype(::stellar::InnerTransactionResultPair::transactionHash),
                              &::stellar::InnerTransactionResultPair::transactionHash>,
                    field_ptr<::stellar::InnerTransactionResultPair,
                              decltype(::stellar::InnerTransactionResultPair::result),
                              &::stellar::InnerTransactionResultPair::result>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::InnerTransactionResultPair &obj) {
    archive(ar, obj.transactionHash, "transactionHash");
    archive(ar, obj.result, "result");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::InnerTransactionResultPair &obj) {
    archive(ar, obj.transactionHash, "transactionHash");
    archive(ar, obj.result, "result");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct TransactionResult {
  struct _result_t {
    using _xdr_case_type = xdr::xdr_traits<TransactionResultCode>::case_type;
  private:
    _xdr_case_type code_;
    union {
      InnerTransactionResultPair innerResultPair_;
      xdr::xvector<OperationResult> results_;
    };

  public:
    static Constexpr const bool _xdr_has_default_case = false;
    static const std::vector<TransactionResultCode> &_xdr_case_values() {
      static const std::vector<TransactionResultCode> _xdr_disc_vec {
        txFEE_BUMP_INNER_SUCCESS,
        txFEE_BUMP_INNER_FAILED,
        txSUCCESS,
        txFAILED,
        txTOO_EARLY,
        txTOO_LATE,
        txMISSING_OPERATION,
        txBAD_SEQ,
        txBAD_AUTH,
        txINSUFFICIENT_BALANCE,
        txNO_ACCOUNT,
        txINSUFFICIENT_FEE,
        txBAD_AUTH_EXTRA,
        txINTERNAL_ERROR,
        txNOT_SUPPORTED,
        txBAD_SPONSORSHIP,
        txBAD_MIN_SEQ_AGE_OR_GAP,
        txMALFORMED,
        txSOROBAN_INVALID,
        txFROZEN_KEY_ACCESSED
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == txFEE_BUMP_INNER_SUCCESS || which == txFEE_BUMP_INNER_FAILED ? 1
        : which == txSUCCESS || which == txFAILED ? 2
        : which == txTOO_EARLY || which == txTOO_LATE || which == txMISSING_OPERATION || which == txBAD_SEQ || which == txBAD_AUTH || which == txINSUFFICIENT_BALANCE || which == txNO_ACCOUNT || which == txINSUFFICIENT_FEE || which == txBAD_AUTH_EXTRA || which == txINTERNAL_ERROR || which == txNOT_SUPPORTED || which == txBAD_SPONSORSHIP || which == txBAD_MIN_SEQ_AGE_OR_GAP || which == txMALFORMED || which == txSOROBAN_INVALID || which == txFROZEN_KEY_ACCESSED ? 0
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case txFEE_BUMP_INNER_SUCCESS:
      case txFEE_BUMP_INNER_FAILED:
        _f(&_result_t::innerResultPair_, std::forward<_A>(_a)...);
        return true;
      case txSUCCESS:
      case txFAILED:
        _f(&_result_t::results_, std::forward<_A>(_a)...);
        return true;
      case txTOO_EARLY:
      case txTOO_LATE:
      case txMISSING_OPERATION:
      case txBAD_SEQ:
      case txBAD_AUTH:
      case txINSUFFICIENT_BALANCE:
      case txNO_ACCOUNT:
      case txINSUFFICIENT_FEE:
      case txBAD_AUTH_EXTRA:
      case txINTERNAL_ERROR:
      case txNOT_SUPPORTED:
      case txBAD_SPONSORSHIP:
      case txBAD_MIN_SEQ_AGE_OR_GAP:
      case txMALFORMED:
      case txSOROBAN_INVALID:
      case txFROZEN_KEY_ACCESSED:
        return true;
      }
      return false;
    }

    _xdr_case_type _xdr_discriminant() const { return code_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of code in _result_t");
      if (fnum != _xdr_field_number(code_)) {
        this->~_result_t();
        code_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
      }
      else
        code_ = which;
    }
    explicit _result_t(TransactionResultCode which = TransactionResultCode{}) : code_(which) {
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this);
    }
    _result_t(const _result_t &source) : code_(source.code_) {
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this, source);
    }
    _result_t(_result_t &&source) : code_(source.code_) {
      _xdr_with_mem_ptr(xdr::field_constructor, code_, *this,
                        std::move(source));
    }
    ~_result_t() { _xdr_with_mem_ptr(xdr::field_destructor, code_, *this); }
    _result_t &operator=(const _result_t &source) {
      if (_xdr_field_number(code_)
          == _xdr_field_number(source.code_))
        _xdr_with_mem_ptr(xdr::field_assigner, code_, *this, source);
      else {
        this->~_result_t();
        code_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this, source);
      }
      code_ = source.code_;
      return *this;
    }
    _result_t &operator=(_result_t &&source) {
      if (_xdr_field_number(code_)
           == _xdr_field_number(source.code_))
        _xdr_with_mem_ptr(xdr::field_assigner, code_, *this,
                          std::move(source));
      else {
        this->~_result_t();
        code_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.code_, *this,
                          std::move(source));
      }
      code_ = source.code_;
      return *this;
    }

    TransactionResultCode code() const { return TransactionResultCode(code_); }
    _result_t &code(TransactionResultCode _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant(_xdr_d, _xdr_validate);
      return *this;
    }

    InnerTransactionResultPair &innerResultPair() {
      if (_xdr_field_number(code_) == 1)
        return innerResultPair_;
      throw xdr::xdr_wrong_union("_result_t: innerResultPair accessed when not selected");
    }
    const InnerTransactionResultPair &innerResultPair() const {
      if (_xdr_field_number(code_) == 1)
        return innerResultPair_;
      throw xdr::xdr_wrong_union("_result_t: innerResultPair accessed when not selected");
    }
    xdr::xvector<OperationResult> &results() {
      if (_xdr_field_number(code_) == 2)
        return results_;
      throw xdr::xdr_wrong_union("_result_t: results accessed when not selected");
    }
    const xdr::xvector<OperationResult> &results() const {
      if (_xdr_field_number(code_) == 2)
        return results_;
      throw xdr::xdr_wrong_union("_result_t: results accessed when not selected");
    }
  };
  struct _ext_t {
    using _xdr_case_type = xdr::xdr_traits<int>::case_type;
  private:
    _xdr_case_type v_;
  public:
    static Constexpr const bool _xdr_has_default_case = false;
    static const std::vector<int> &_xdr_case_values() {
      static const std::vector<int> _xdr_disc_vec {
        0
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == 0 ? 0
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case 0:
        return true;
      }
      return false;
    }

    _xdr_case_type _xdr_discriminant() const { return v_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of v in _ext_t");
      if (fnum != _xdr_field_number(v_)) {
        this->~_ext_t();
        v_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
      }
      else
        v_ = which;
    }
    explicit _ext_t(std::int32_t which = std::int32_t{}) : v_(which) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
    }
    _ext_t(const _ext_t &source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this, source);
    }
    _ext_t(_ext_t &&source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this,
                        std::move(source));
    }
    ~_ext_t() { _xdr_with_mem_ptr(xdr::field_destructor, v_, *this); }
    _ext_t &operator=(const _ext_t &source) {
      if (_xdr_field_number(v_)
          == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this, source);
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this, source);
      }
      v_ = source.v_;
      return *this;
    }
    _ext_t &operator=(_ext_t &&source) {
      if (_xdr_field_number(v_)
           == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this,
                          std::move(source));
      else {
        this->~_ext_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this,
                          std::move(source));
      }
      v_ = source.v_;
      return *this;
    }

    std::int32_t v() const { return std::int32_t(v_); }
    _ext_t &v(int _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant(_xdr_d, _xdr_validate);
      return *this;
    }

  };

  int64 feeCharged{};
  _result_t result{};
  _ext_t ext{};

  TransactionResult() = default;
  template<typename _feeCharged_T,
           typename _result_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<int64, _feeCharged_T>::value
                          && std::is_constructible<_result_t, _result_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit TransactionResult(_feeCharged_T &&_feeCharged,
                             _result_T &&_result,
                             _ext_T &&_ext)
    : feeCharged(std::forward<_feeCharged_T>(_feeCharged)),
      result(std::forward<_result_T>(_result)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::TransactionResult::_result_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::TransactionResult::_result_t;
  using case_type = ::stellar::TransactionResult::_result_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().code());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "innerResultPair";
    case 2:
      return "results";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::TransactionResult::_result_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of code in _result_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::TransactionResult::_result_t &obj) {
    xdr::archive(ar, obj.code(), "code");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of code in _result_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::TransactionResult::_result_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "code");
    obj.code(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.code(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::TransactionResult::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::TransactionResult::_ext_t;
  using case_type = ::stellar::TransactionResult::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::TransactionResult::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::TransactionResult::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::TransactionResult::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.v(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::TransactionResult>
  : xdr_struct_base<field_ptr<::stellar::TransactionResult,
                              decltype(::stellar::TransactionResult::feeCharged),
                              &::stellar::TransactionResult::feeCharged>,
                    field_ptr<::stellar::TransactionResult,
                              decltype(::stellar::TransactionResult::result),
                              &::stellar::TransactionResult::result>,
                    field_ptr<::stellar::TransactionResult,
                              decltype(::stellar::TransactionResult::ext),
                              &::stellar::TransactionResult::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::TransactionResult &obj) {
    archive(ar, obj.feeCharged, "feeCharged");
    archive(ar, obj.result, "result");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::TransactionResult &obj) {
    archive(ar, obj.feeCharged, "feeCharged");
    archive(ar, obj.result, "result");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

}

#endif // !__XDR_STELLAR_TRANSACTION_H_INCLUDED__
