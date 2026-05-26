// -*- C++ -*-
// Automatically generated from Stellar-contract.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_CONTRACT_H_INCLUDED__
#define __XDR_STELLAR_CONTRACT_H_INCLUDED__ 1

#include <xdrpp/types.h>

 #include "xdr/Stellar-types.h"

namespace stellar {

enum SCValType : std::int32_t {
  SCV_BOOL = 0,
  SCV_VOID = 1,
  SCV_ERROR = 2,
  SCV_U32 = 3,
  SCV_I32 = 4,
  SCV_U64 = 5,
  SCV_I64 = 6,
  SCV_TIMEPOINT = 7,
  SCV_DURATION = 8,
  SCV_U128 = 9,
  SCV_I128 = 10,
  SCV_U256 = 11,
  SCV_I256 = 12,
  SCV_BYTES = 13,
  SCV_STRING = 14,
  SCV_SYMBOL = 15,
  SCV_VEC = 16,
  SCV_MAP = 17,
  SCV_ADDRESS = 18,
  SCV_CONTRACT_INSTANCE = 19,
  SCV_LEDGER_KEY_CONTRACT_INSTANCE = 20,
  SCV_LEDGER_KEY_NONCE = 21,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCValType>
  : xdr_integral_base<::stellar::SCValType, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::SCValType val) {
    switch (val) {
    case ::stellar::SCV_BOOL:
      return "SCV_BOOL";
    case ::stellar::SCV_VOID:
      return "SCV_VOID";
    case ::stellar::SCV_ERROR:
      return "SCV_ERROR";
    case ::stellar::SCV_U32:
      return "SCV_U32";
    case ::stellar::SCV_I32:
      return "SCV_I32";
    case ::stellar::SCV_U64:
      return "SCV_U64";
    case ::stellar::SCV_I64:
      return "SCV_I64";
    case ::stellar::SCV_TIMEPOINT:
      return "SCV_TIMEPOINT";
    case ::stellar::SCV_DURATION:
      return "SCV_DURATION";
    case ::stellar::SCV_U128:
      return "SCV_U128";
    case ::stellar::SCV_I128:
      return "SCV_I128";
    case ::stellar::SCV_U256:
      return "SCV_U256";
    case ::stellar::SCV_I256:
      return "SCV_I256";
    case ::stellar::SCV_BYTES:
      return "SCV_BYTES";
    case ::stellar::SCV_STRING:
      return "SCV_STRING";
    case ::stellar::SCV_SYMBOL:
      return "SCV_SYMBOL";
    case ::stellar::SCV_VEC:
      return "SCV_VEC";
    case ::stellar::SCV_MAP:
      return "SCV_MAP";
    case ::stellar::SCV_ADDRESS:
      return "SCV_ADDRESS";
    case ::stellar::SCV_CONTRACT_INSTANCE:
      return "SCV_CONTRACT_INSTANCE";
    case ::stellar::SCV_LEDGER_KEY_CONTRACT_INSTANCE:
      return "SCV_LEDGER_KEY_CONTRACT_INSTANCE";
    case ::stellar::SCV_LEDGER_KEY_NONCE:
      return "SCV_LEDGER_KEY_NONCE";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::SCV_BOOL,
      ::stellar::SCV_VOID,
      ::stellar::SCV_ERROR,
      ::stellar::SCV_U32,
      ::stellar::SCV_I32,
      ::stellar::SCV_U64,
      ::stellar::SCV_I64,
      ::stellar::SCV_TIMEPOINT,
      ::stellar::SCV_DURATION,
      ::stellar::SCV_U128,
      ::stellar::SCV_I128,
      ::stellar::SCV_U256,
      ::stellar::SCV_I256,
      ::stellar::SCV_BYTES,
      ::stellar::SCV_STRING,
      ::stellar::SCV_SYMBOL,
      ::stellar::SCV_VEC,
      ::stellar::SCV_MAP,
      ::stellar::SCV_ADDRESS,
      ::stellar::SCV_CONTRACT_INSTANCE,
      ::stellar::SCV_LEDGER_KEY_CONTRACT_INSTANCE,
      ::stellar::SCV_LEDGER_KEY_NONCE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

enum SCErrorType : std::int32_t {
  SCE_CONTRACT = 0,
  SCE_WASM_VM = 1,
  SCE_CONTEXT = 2,
  SCE_STORAGE = 3,
  SCE_OBJECT = 4,
  SCE_CRYPTO = 5,
  SCE_EVENTS = 6,
  SCE_BUDGET = 7,
  SCE_VALUE = 8,
  SCE_AUTH = 9,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCErrorType>
  : xdr_integral_base<::stellar::SCErrorType, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::SCErrorType val) {
    switch (val) {
    case ::stellar::SCE_CONTRACT:
      return "SCE_CONTRACT";
    case ::stellar::SCE_WASM_VM:
      return "SCE_WASM_VM";
    case ::stellar::SCE_CONTEXT:
      return "SCE_CONTEXT";
    case ::stellar::SCE_STORAGE:
      return "SCE_STORAGE";
    case ::stellar::SCE_OBJECT:
      return "SCE_OBJECT";
    case ::stellar::SCE_CRYPTO:
      return "SCE_CRYPTO";
    case ::stellar::SCE_EVENTS:
      return "SCE_EVENTS";
    case ::stellar::SCE_BUDGET:
      return "SCE_BUDGET";
    case ::stellar::SCE_VALUE:
      return "SCE_VALUE";
    case ::stellar::SCE_AUTH:
      return "SCE_AUTH";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::SCE_CONTRACT,
      ::stellar::SCE_WASM_VM,
      ::stellar::SCE_CONTEXT,
      ::stellar::SCE_STORAGE,
      ::stellar::SCE_OBJECT,
      ::stellar::SCE_CRYPTO,
      ::stellar::SCE_EVENTS,
      ::stellar::SCE_BUDGET,
      ::stellar::SCE_VALUE,
      ::stellar::SCE_AUTH
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

enum SCErrorCode : std::int32_t {
  SCEC_ARITH_DOMAIN = 0,
  SCEC_INDEX_BOUNDS = 1,
  SCEC_INVALID_INPUT = 2,
  SCEC_MISSING_VALUE = 3,
  SCEC_EXISTING_VALUE = 4,
  SCEC_EXCEEDED_LIMIT = 5,
  SCEC_INVALID_ACTION = 6,
  SCEC_INTERNAL_ERROR = 7,
  SCEC_UNEXPECTED_TYPE = 8,
  SCEC_UNEXPECTED_SIZE = 9,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCErrorCode>
  : xdr_integral_base<::stellar::SCErrorCode, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::SCErrorCode val) {
    switch (val) {
    case ::stellar::SCEC_ARITH_DOMAIN:
      return "SCEC_ARITH_DOMAIN";
    case ::stellar::SCEC_INDEX_BOUNDS:
      return "SCEC_INDEX_BOUNDS";
    case ::stellar::SCEC_INVALID_INPUT:
      return "SCEC_INVALID_INPUT";
    case ::stellar::SCEC_MISSING_VALUE:
      return "SCEC_MISSING_VALUE";
    case ::stellar::SCEC_EXISTING_VALUE:
      return "SCEC_EXISTING_VALUE";
    case ::stellar::SCEC_EXCEEDED_LIMIT:
      return "SCEC_EXCEEDED_LIMIT";
    case ::stellar::SCEC_INVALID_ACTION:
      return "SCEC_INVALID_ACTION";
    case ::stellar::SCEC_INTERNAL_ERROR:
      return "SCEC_INTERNAL_ERROR";
    case ::stellar::SCEC_UNEXPECTED_TYPE:
      return "SCEC_UNEXPECTED_TYPE";
    case ::stellar::SCEC_UNEXPECTED_SIZE:
      return "SCEC_UNEXPECTED_SIZE";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::SCEC_ARITH_DOMAIN,
      ::stellar::SCEC_INDEX_BOUNDS,
      ::stellar::SCEC_INVALID_INPUT,
      ::stellar::SCEC_MISSING_VALUE,
      ::stellar::SCEC_EXISTING_VALUE,
      ::stellar::SCEC_EXCEEDED_LIMIT,
      ::stellar::SCEC_INVALID_ACTION,
      ::stellar::SCEC_INTERNAL_ERROR,
      ::stellar::SCEC_UNEXPECTED_TYPE,
      ::stellar::SCEC_UNEXPECTED_SIZE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct SCError {
  using _xdr_case_type = xdr::xdr_traits<SCErrorType>::case_type;
private:
  _xdr_case_type type_;
  union {
    uint32 contractCode_;
    SCErrorCode code_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<SCErrorType> &_xdr_case_values() {
    static const std::vector<SCErrorType> _xdr_disc_vec {
      SCE_CONTRACT,
      SCE_WASM_VM,
      SCE_CONTEXT,
      SCE_STORAGE,
      SCE_OBJECT,
      SCE_CRYPTO,
      SCE_EVENTS,
      SCE_BUDGET,
      SCE_VALUE,
      SCE_AUTH
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == SCE_CONTRACT ? 1
      : which == SCE_WASM_VM || which == SCE_CONTEXT || which == SCE_STORAGE || which == SCE_OBJECT || which == SCE_CRYPTO || which == SCE_EVENTS || which == SCE_BUDGET || which == SCE_VALUE || which == SCE_AUTH ? 2
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case SCE_CONTRACT:
      _f(&SCError::contractCode_, std::forward<_A>(_a)...);
      return true;
    case SCE_WASM_VM:
    case SCE_CONTEXT:
    case SCE_STORAGE:
    case SCE_OBJECT:
    case SCE_CRYPTO:
    case SCE_EVENTS:
    case SCE_BUDGET:
    case SCE_VALUE:
    case SCE_AUTH:
      _f(&SCError::code_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return type_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of type in SCError");
    if (fnum != _xdr_field_number(type_)) {
      this->~SCError();
      type_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
    }
    else
      type_ = which;
  }
  explicit SCError(SCErrorType which = SCErrorType{}) : type_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
  }
  SCError(const SCError &source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this, source);
  }
  SCError(SCError &&source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this,
                      std::move(source));
  }
  ~SCError() { _xdr_with_mem_ptr(xdr::field_destructor, type_, *this); }
  SCError &operator=(const SCError &source) {
    if (_xdr_field_number(type_)
        == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this, source);
    else {
      this->~SCError();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this, source);
    }
    type_ = source.type_;
    return *this;
  }
  SCError &operator=(SCError &&source) {
    if (_xdr_field_number(type_)
         == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this,
                        std::move(source));
    else {
      this->~SCError();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this,
                        std::move(source));
    }
    type_ = source.type_;
    return *this;
  }

  SCErrorType type() const { return SCErrorType(type_); }
  SCError &type(SCErrorType _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  uint32 &contractCode() {
    if (_xdr_field_number(type_) == 1)
      return contractCode_;
    throw xdr::xdr_wrong_union("SCError: contractCode accessed when not selected");
  }
  const uint32 &contractCode() const {
    if (_xdr_field_number(type_) == 1)
      return contractCode_;
    throw xdr::xdr_wrong_union("SCError: contractCode accessed when not selected");
  }
  SCErrorCode &code() {
    if (_xdr_field_number(type_) == 2)
      return code_;
    throw xdr::xdr_wrong_union("SCError: code accessed when not selected");
  }
  const SCErrorCode &code() const {
    if (_xdr_field_number(type_) == 2)
      return code_;
    throw xdr::xdr_wrong_union("SCError: code accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCError> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::SCError;
  using case_type = ::stellar::SCError::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().type());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "contractCode";
    case 2:
      return "code";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::SCError &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of type in SCError");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SCError &obj) {
    xdr::archive(ar, obj.type(), "type");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of type in SCError");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SCError &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "type");
    obj.type(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

struct UInt128Parts {
  uint64 hi{};
  uint64 lo{};

  UInt128Parts() = default;
  template<typename _hi_T,
           typename _lo_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _hi_T>::value
                          && std::is_constructible<uint64, _lo_T>::value
                         >::type>
  explicit UInt128Parts(_hi_T &&_hi,
                        _lo_T &&_lo)
    : hi(std::forward<_hi_T>(_hi)),
      lo(std::forward<_lo_T>(_lo)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::UInt128Parts>
  : xdr_struct_base<field_ptr<::stellar::UInt128Parts,
                              decltype(::stellar::UInt128Parts::hi),
                              &::stellar::UInt128Parts::hi>,
                    field_ptr<::stellar::UInt128Parts,
                              decltype(::stellar::UInt128Parts::lo),
                              &::stellar::UInt128Parts::lo>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::UInt128Parts &obj) {
    archive(ar, obj.hi, "hi");
    archive(ar, obj.lo, "lo");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::UInt128Parts &obj) {
    archive(ar, obj.hi, "hi");
    archive(ar, obj.lo, "lo");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct Int128Parts {
  int64 hi{};
  uint64 lo{};

  Int128Parts() = default;
  template<typename _hi_T,
           typename _lo_T,
           typename = typename
           std::enable_if<std::is_constructible<int64, _hi_T>::value
                          && std::is_constructible<uint64, _lo_T>::value
                         >::type>
  explicit Int128Parts(_hi_T &&_hi,
                       _lo_T &&_lo)
    : hi(std::forward<_hi_T>(_hi)),
      lo(std::forward<_lo_T>(_lo)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::Int128Parts>
  : xdr_struct_base<field_ptr<::stellar::Int128Parts,
                              decltype(::stellar::Int128Parts::hi),
                              &::stellar::Int128Parts::hi>,
                    field_ptr<::stellar::Int128Parts,
                              decltype(::stellar::Int128Parts::lo),
                              &::stellar::Int128Parts::lo>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::Int128Parts &obj) {
    archive(ar, obj.hi, "hi");
    archive(ar, obj.lo, "lo");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::Int128Parts &obj) {
    archive(ar, obj.hi, "hi");
    archive(ar, obj.lo, "lo");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct UInt256Parts {
  uint64 hi_hi{};
  uint64 hi_lo{};
  uint64 lo_hi{};
  uint64 lo_lo{};

  UInt256Parts() = default;
  template<typename _hi_hi_T,
           typename _hi_lo_T,
           typename _lo_hi_T,
           typename _lo_lo_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _hi_hi_T>::value
                          && std::is_constructible<uint64, _hi_lo_T>::value
                          && std::is_constructible<uint64, _lo_hi_T>::value
                          && std::is_constructible<uint64, _lo_lo_T>::value
                         >::type>
  explicit UInt256Parts(_hi_hi_T &&_hi_hi,
                        _hi_lo_T &&_hi_lo,
                        _lo_hi_T &&_lo_hi,
                        _lo_lo_T &&_lo_lo)
    : hi_hi(std::forward<_hi_hi_T>(_hi_hi)),
      hi_lo(std::forward<_hi_lo_T>(_hi_lo)),
      lo_hi(std::forward<_lo_hi_T>(_lo_hi)),
      lo_lo(std::forward<_lo_lo_T>(_lo_lo)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::UInt256Parts>
  : xdr_struct_base<field_ptr<::stellar::UInt256Parts,
                              decltype(::stellar::UInt256Parts::hi_hi),
                              &::stellar::UInt256Parts::hi_hi>,
                    field_ptr<::stellar::UInt256Parts,
                              decltype(::stellar::UInt256Parts::hi_lo),
                              &::stellar::UInt256Parts::hi_lo>,
                    field_ptr<::stellar::UInt256Parts,
                              decltype(::stellar::UInt256Parts::lo_hi),
                              &::stellar::UInt256Parts::lo_hi>,
                    field_ptr<::stellar::UInt256Parts,
                              decltype(::stellar::UInt256Parts::lo_lo),
                              &::stellar::UInt256Parts::lo_lo>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::UInt256Parts &obj) {
    archive(ar, obj.hi_hi, "hi_hi");
    archive(ar, obj.hi_lo, "hi_lo");
    archive(ar, obj.lo_hi, "lo_hi");
    archive(ar, obj.lo_lo, "lo_lo");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::UInt256Parts &obj) {
    archive(ar, obj.hi_hi, "hi_hi");
    archive(ar, obj.hi_lo, "hi_lo");
    archive(ar, obj.lo_hi, "lo_hi");
    archive(ar, obj.lo_lo, "lo_lo");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct Int256Parts {
  int64 hi_hi{};
  uint64 hi_lo{};
  uint64 lo_hi{};
  uint64 lo_lo{};

  Int256Parts() = default;
  template<typename _hi_hi_T,
           typename _hi_lo_T,
           typename _lo_hi_T,
           typename _lo_lo_T,
           typename = typename
           std::enable_if<std::is_constructible<int64, _hi_hi_T>::value
                          && std::is_constructible<uint64, _hi_lo_T>::value
                          && std::is_constructible<uint64, _lo_hi_T>::value
                          && std::is_constructible<uint64, _lo_lo_T>::value
                         >::type>
  explicit Int256Parts(_hi_hi_T &&_hi_hi,
                       _hi_lo_T &&_hi_lo,
                       _lo_hi_T &&_lo_hi,
                       _lo_lo_T &&_lo_lo)
    : hi_hi(std::forward<_hi_hi_T>(_hi_hi)),
      hi_lo(std::forward<_hi_lo_T>(_hi_lo)),
      lo_hi(std::forward<_lo_hi_T>(_lo_hi)),
      lo_lo(std::forward<_lo_lo_T>(_lo_lo)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::Int256Parts>
  : xdr_struct_base<field_ptr<::stellar::Int256Parts,
                              decltype(::stellar::Int256Parts::hi_hi),
                              &::stellar::Int256Parts::hi_hi>,
                    field_ptr<::stellar::Int256Parts,
                              decltype(::stellar::Int256Parts::hi_lo),
                              &::stellar::Int256Parts::hi_lo>,
                    field_ptr<::stellar::Int256Parts,
                              decltype(::stellar::Int256Parts::lo_hi),
                              &::stellar::Int256Parts::lo_hi>,
                    field_ptr<::stellar::Int256Parts,
                              decltype(::stellar::Int256Parts::lo_lo),
                              &::stellar::Int256Parts::lo_lo>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::Int256Parts &obj) {
    archive(ar, obj.hi_hi, "hi_hi");
    archive(ar, obj.hi_lo, "hi_lo");
    archive(ar, obj.lo_hi, "lo_hi");
    archive(ar, obj.lo_lo, "lo_lo");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::Int256Parts &obj) {
    archive(ar, obj.hi_hi, "hi_hi");
    archive(ar, obj.hi_lo, "hi_lo");
    archive(ar, obj.lo_hi, "lo_hi");
    archive(ar, obj.lo_lo, "lo_lo");
    xdr::validate(obj);
  }
};
} namespace stellar {

enum ContractExecutableType : std::int32_t {
  CONTRACT_EXECUTABLE_WASM = 0,
  CONTRACT_EXECUTABLE_STELLAR_ASSET = 1,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ContractExecutableType>
  : xdr_integral_base<::stellar::ContractExecutableType, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ContractExecutableType val) {
    switch (val) {
    case ::stellar::CONTRACT_EXECUTABLE_WASM:
      return "CONTRACT_EXECUTABLE_WASM";
    case ::stellar::CONTRACT_EXECUTABLE_STELLAR_ASSET:
      return "CONTRACT_EXECUTABLE_STELLAR_ASSET";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::CONTRACT_EXECUTABLE_WASM,
      ::stellar::CONTRACT_EXECUTABLE_STELLAR_ASSET
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct ContractExecutable {
  using _xdr_case_type = xdr::xdr_traits<ContractExecutableType>::case_type;
private:
  _xdr_case_type type_;
  union {
    Hash wasm_hash_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<ContractExecutableType> &_xdr_case_values() {
    static const std::vector<ContractExecutableType> _xdr_disc_vec {
      CONTRACT_EXECUTABLE_WASM,
      CONTRACT_EXECUTABLE_STELLAR_ASSET
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == CONTRACT_EXECUTABLE_WASM ? 1
      : which == CONTRACT_EXECUTABLE_STELLAR_ASSET ? 0
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case CONTRACT_EXECUTABLE_WASM:
      _f(&ContractExecutable::wasm_hash_, std::forward<_A>(_a)...);
      return true;
    case CONTRACT_EXECUTABLE_STELLAR_ASSET:
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return type_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of type in ContractExecutable");
    if (fnum != _xdr_field_number(type_)) {
      this->~ContractExecutable();
      type_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
    }
    else
      type_ = which;
  }
  explicit ContractExecutable(ContractExecutableType which = ContractExecutableType{}) : type_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
  }
  ContractExecutable(const ContractExecutable &source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this, source);
  }
  ContractExecutable(ContractExecutable &&source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this,
                      std::move(source));
  }
  ~ContractExecutable() { _xdr_with_mem_ptr(xdr::field_destructor, type_, *this); }
  ContractExecutable &operator=(const ContractExecutable &source) {
    if (_xdr_field_number(type_)
        == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this, source);
    else {
      this->~ContractExecutable();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this, source);
    }
    type_ = source.type_;
    return *this;
  }
  ContractExecutable &operator=(ContractExecutable &&source) {
    if (_xdr_field_number(type_)
         == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this,
                        std::move(source));
    else {
      this->~ContractExecutable();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this,
                        std::move(source));
    }
    type_ = source.type_;
    return *this;
  }

  ContractExecutableType type() const { return ContractExecutableType(type_); }
  ContractExecutable &type(ContractExecutableType _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  Hash &wasm_hash() {
    if (_xdr_field_number(type_) == 1)
      return wasm_hash_;
    throw xdr::xdr_wrong_union("ContractExecutable: wasm_hash accessed when not selected");
  }
  const Hash &wasm_hash() const {
    if (_xdr_field_number(type_) == 1)
      return wasm_hash_;
    throw xdr::xdr_wrong_union("ContractExecutable: wasm_hash accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ContractExecutable> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ContractExecutable;
  using case_type = ::stellar::ContractExecutable::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().type());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "wasm_hash";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ContractExecutable &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of type in ContractExecutable");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ContractExecutable &obj) {
    xdr::archive(ar, obj.type(), "type");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of type in ContractExecutable");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ContractExecutable &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "type");
    obj.type(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

enum SCAddressType : std::int32_t {
  SC_ADDRESS_TYPE_ACCOUNT = 0,
  SC_ADDRESS_TYPE_CONTRACT = 1,
  SC_ADDRESS_TYPE_MUXED_ACCOUNT = 2,
  SC_ADDRESS_TYPE_CLAIMABLE_BALANCE = 3,
  SC_ADDRESS_TYPE_LIQUIDITY_POOL = 4,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCAddressType>
  : xdr_integral_base<::stellar::SCAddressType, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::SCAddressType val) {
    switch (val) {
    case ::stellar::SC_ADDRESS_TYPE_ACCOUNT:
      return "SC_ADDRESS_TYPE_ACCOUNT";
    case ::stellar::SC_ADDRESS_TYPE_CONTRACT:
      return "SC_ADDRESS_TYPE_CONTRACT";
    case ::stellar::SC_ADDRESS_TYPE_MUXED_ACCOUNT:
      return "SC_ADDRESS_TYPE_MUXED_ACCOUNT";
    case ::stellar::SC_ADDRESS_TYPE_CLAIMABLE_BALANCE:
      return "SC_ADDRESS_TYPE_CLAIMABLE_BALANCE";
    case ::stellar::SC_ADDRESS_TYPE_LIQUIDITY_POOL:
      return "SC_ADDRESS_TYPE_LIQUIDITY_POOL";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::SC_ADDRESS_TYPE_ACCOUNT,
      ::stellar::SC_ADDRESS_TYPE_CONTRACT,
      ::stellar::SC_ADDRESS_TYPE_MUXED_ACCOUNT,
      ::stellar::SC_ADDRESS_TYPE_CLAIMABLE_BALANCE,
      ::stellar::SC_ADDRESS_TYPE_LIQUIDITY_POOL
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct MuxedEd25519Account {
  uint64 id{};
  uint256 ed25519{};

  MuxedEd25519Account() = default;
  template<typename _id_T,
           typename _ed25519_T,
           typename = typename
           std::enable_if<std::is_constructible<uint64, _id_T>::value
                          && std::is_constructible<uint256, _ed25519_T>::value
                         >::type>
  explicit MuxedEd25519Account(_id_T &&_id,
                               _ed25519_T &&_ed25519)
    : id(std::forward<_id_T>(_id)),
      ed25519(std::forward<_ed25519_T>(_ed25519)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::MuxedEd25519Account>
  : xdr_struct_base<field_ptr<::stellar::MuxedEd25519Account,
                              decltype(::stellar::MuxedEd25519Account::id),
                              &::stellar::MuxedEd25519Account::id>,
                    field_ptr<::stellar::MuxedEd25519Account,
                              decltype(::stellar::MuxedEd25519Account::ed25519),
                              &::stellar::MuxedEd25519Account::ed25519>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::MuxedEd25519Account &obj) {
    archive(ar, obj.id, "id");
    archive(ar, obj.ed25519, "ed25519");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::MuxedEd25519Account &obj) {
    archive(ar, obj.id, "id");
    archive(ar, obj.ed25519, "ed25519");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct SCAddress {
  using _xdr_case_type = xdr::xdr_traits<SCAddressType>::case_type;
private:
  _xdr_case_type type_;
  union {
    AccountID accountId_;
    ContractID contractId_;
    MuxedEd25519Account muxedAccount_;
    ClaimableBalanceID claimableBalanceId_;
    PoolID liquidityPoolId_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<SCAddressType> &_xdr_case_values() {
    static const std::vector<SCAddressType> _xdr_disc_vec {
      SC_ADDRESS_TYPE_ACCOUNT,
      SC_ADDRESS_TYPE_CONTRACT,
      SC_ADDRESS_TYPE_MUXED_ACCOUNT,
      SC_ADDRESS_TYPE_CLAIMABLE_BALANCE,
      SC_ADDRESS_TYPE_LIQUIDITY_POOL
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == SC_ADDRESS_TYPE_ACCOUNT ? 1
      : which == SC_ADDRESS_TYPE_CONTRACT ? 2
      : which == SC_ADDRESS_TYPE_MUXED_ACCOUNT ? 3
      : which == SC_ADDRESS_TYPE_CLAIMABLE_BALANCE ? 4
      : which == SC_ADDRESS_TYPE_LIQUIDITY_POOL ? 5
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case SC_ADDRESS_TYPE_ACCOUNT:
      _f(&SCAddress::accountId_, std::forward<_A>(_a)...);
      return true;
    case SC_ADDRESS_TYPE_CONTRACT:
      _f(&SCAddress::contractId_, std::forward<_A>(_a)...);
      return true;
    case SC_ADDRESS_TYPE_MUXED_ACCOUNT:
      _f(&SCAddress::muxedAccount_, std::forward<_A>(_a)...);
      return true;
    case SC_ADDRESS_TYPE_CLAIMABLE_BALANCE:
      _f(&SCAddress::claimableBalanceId_, std::forward<_A>(_a)...);
      return true;
    case SC_ADDRESS_TYPE_LIQUIDITY_POOL:
      _f(&SCAddress::liquidityPoolId_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return type_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of type in SCAddress");
    if (fnum != _xdr_field_number(type_)) {
      this->~SCAddress();
      type_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
    }
    else
      type_ = which;
  }
  explicit SCAddress(SCAddressType which = SCAddressType{}) : type_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
  }
  SCAddress(const SCAddress &source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this, source);
  }
  SCAddress(SCAddress &&source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this,
                      std::move(source));
  }
  ~SCAddress() { _xdr_with_mem_ptr(xdr::field_destructor, type_, *this); }
  SCAddress &operator=(const SCAddress &source) {
    if (_xdr_field_number(type_)
        == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this, source);
    else {
      this->~SCAddress();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this, source);
    }
    type_ = source.type_;
    return *this;
  }
  SCAddress &operator=(SCAddress &&source) {
    if (_xdr_field_number(type_)
         == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this,
                        std::move(source));
    else {
      this->~SCAddress();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this,
                        std::move(source));
    }
    type_ = source.type_;
    return *this;
  }

  SCAddressType type() const { return SCAddressType(type_); }
  SCAddress &type(SCAddressType _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  AccountID &accountId() {
    if (_xdr_field_number(type_) == 1)
      return accountId_;
    throw xdr::xdr_wrong_union("SCAddress: accountId accessed when not selected");
  }
  const AccountID &accountId() const {
    if (_xdr_field_number(type_) == 1)
      return accountId_;
    throw xdr::xdr_wrong_union("SCAddress: accountId accessed when not selected");
  }
  ContractID &contractId() {
    if (_xdr_field_number(type_) == 2)
      return contractId_;
    throw xdr::xdr_wrong_union("SCAddress: contractId accessed when not selected");
  }
  const ContractID &contractId() const {
    if (_xdr_field_number(type_) == 2)
      return contractId_;
    throw xdr::xdr_wrong_union("SCAddress: contractId accessed when not selected");
  }
  MuxedEd25519Account &muxedAccount() {
    if (_xdr_field_number(type_) == 3)
      return muxedAccount_;
    throw xdr::xdr_wrong_union("SCAddress: muxedAccount accessed when not selected");
  }
  const MuxedEd25519Account &muxedAccount() const {
    if (_xdr_field_number(type_) == 3)
      return muxedAccount_;
    throw xdr::xdr_wrong_union("SCAddress: muxedAccount accessed when not selected");
  }
  ClaimableBalanceID &claimableBalanceId() {
    if (_xdr_field_number(type_) == 4)
      return claimableBalanceId_;
    throw xdr::xdr_wrong_union("SCAddress: claimableBalanceId accessed when not selected");
  }
  const ClaimableBalanceID &claimableBalanceId() const {
    if (_xdr_field_number(type_) == 4)
      return claimableBalanceId_;
    throw xdr::xdr_wrong_union("SCAddress: claimableBalanceId accessed when not selected");
  }
  PoolID &liquidityPoolId() {
    if (_xdr_field_number(type_) == 5)
      return liquidityPoolId_;
    throw xdr::xdr_wrong_union("SCAddress: liquidityPoolId accessed when not selected");
  }
  const PoolID &liquidityPoolId() const {
    if (_xdr_field_number(type_) == 5)
      return liquidityPoolId_;
    throw xdr::xdr_wrong_union("SCAddress: liquidityPoolId accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCAddress> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::SCAddress;
  using case_type = ::stellar::SCAddress::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().type());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "accountId";
    case 2:
      return "contractId";
    case 3:
      return "muxedAccount";
    case 4:
      return "claimableBalanceId";
    case 5:
      return "liquidityPoolId";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::SCAddress &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of type in SCAddress");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SCAddress &obj) {
    xdr::archive(ar, obj.type(), "type");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of type in SCAddress");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SCAddress &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "type");
    obj.type(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

struct SCVal;
struct SCMapEntry;

Constexpr const std::uint32_t SCSYMBOL_LIMIT = 32;

using SCVec = xdr::xvector<SCVal>;
using SCMap = xdr::xvector<SCMapEntry>;
using SCBytes = xdr::opaque_vec<>;
using SCString = xdr::xstring<>;
using SCSymbol = xdr::xstring<SCSYMBOL_LIMIT>;

struct SCNonceKey {
  int64 nonce{};

  SCNonceKey() = default;
  template<typename _nonce_T,
           typename = typename
           std::enable_if<std::is_constructible<int64, _nonce_T>::value
                         >::type>
  explicit SCNonceKey(_nonce_T &&_nonce)
    : nonce(std::forward<_nonce_T>(_nonce)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCNonceKey>
  : xdr_struct_base<field_ptr<::stellar::SCNonceKey,
                              decltype(::stellar::SCNonceKey::nonce),
                              &::stellar::SCNonceKey::nonce>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SCNonceKey &obj) {
    archive(ar, obj.nonce, "nonce");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SCNonceKey &obj) {
    archive(ar, obj.nonce, "nonce");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct SCContractInstance {
  ContractExecutable executable{};
  xdr::pointer<SCMap> storage{};

  SCContractInstance() = default;
  template<typename _executable_T,
           typename _storage_T,
           typename = typename
           std::enable_if<std::is_constructible<ContractExecutable, _executable_T>::value
                          && std::is_constructible<xdr::pointer<SCMap>, _storage_T>::value
                         >::type>
  explicit SCContractInstance(_executable_T &&_executable,
                              _storage_T &&_storage)
    : executable(std::forward<_executable_T>(_executable)),
      storage(std::forward<_storage_T>(_storage)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCContractInstance>
  : xdr_struct_base<field_ptr<::stellar::SCContractInstance,
                              decltype(::stellar::SCContractInstance::executable),
                              &::stellar::SCContractInstance::executable>,
                    field_ptr<::stellar::SCContractInstance,
                              decltype(::stellar::SCContractInstance::storage),
                              &::stellar::SCContractInstance::storage>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SCContractInstance &obj) {
    archive(ar, obj.executable, "executable");
    archive(ar, obj.storage, "storage");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SCContractInstance &obj) {
    archive(ar, obj.executable, "executable");
    archive(ar, obj.storage, "storage");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct SCVal {
  using _xdr_case_type = xdr::xdr_traits<SCValType>::case_type;
private:
  _xdr_case_type type_;
  union {
    bool b_;
    SCError error_;
    uint32 u32_;
    int32 i32_;
    uint64 u64_;
    int64 i64_;
    TimePoint timepoint_;
    Duration duration_;
    UInt128Parts u128_;
    Int128Parts i128_;
    UInt256Parts u256_;
    Int256Parts i256_;
    SCBytes bytes_;
    SCString str_;
    SCSymbol sym_;
    xdr::pointer<SCVec> vec_;
    xdr::pointer<SCMap> map_;
    SCAddress address_;
    SCContractInstance instance_;
    SCNonceKey nonce_key_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<SCValType> &_xdr_case_values() {
    static const std::vector<SCValType> _xdr_disc_vec {
      SCV_BOOL,
      SCV_VOID,
      SCV_ERROR,
      SCV_U32,
      SCV_I32,
      SCV_U64,
      SCV_I64,
      SCV_TIMEPOINT,
      SCV_DURATION,
      SCV_U128,
      SCV_I128,
      SCV_U256,
      SCV_I256,
      SCV_BYTES,
      SCV_STRING,
      SCV_SYMBOL,
      SCV_VEC,
      SCV_MAP,
      SCV_ADDRESS,
      SCV_CONTRACT_INSTANCE,
      SCV_LEDGER_KEY_CONTRACT_INSTANCE,
      SCV_LEDGER_KEY_NONCE
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == SCV_BOOL ? 1
      : which == SCV_VOID ? 0
      : which == SCV_ERROR ? 2
      : which == SCV_U32 ? 3
      : which == SCV_I32 ? 4
      : which == SCV_U64 ? 5
      : which == SCV_I64 ? 6
      : which == SCV_TIMEPOINT ? 7
      : which == SCV_DURATION ? 8
      : which == SCV_U128 ? 9
      : which == SCV_I128 ? 10
      : which == SCV_U256 ? 11
      : which == SCV_I256 ? 12
      : which == SCV_BYTES ? 13
      : which == SCV_STRING ? 14
      : which == SCV_SYMBOL ? 15
      : which == SCV_VEC ? 16
      : which == SCV_MAP ? 17
      : which == SCV_ADDRESS ? 18
      : which == SCV_CONTRACT_INSTANCE ? 19
      : which == SCV_LEDGER_KEY_CONTRACT_INSTANCE ? 0
      : which == SCV_LEDGER_KEY_NONCE ? 20
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case SCV_BOOL:
      _f(&SCVal::b_, std::forward<_A>(_a)...);
      return true;
    case SCV_VOID:
      return true;
    case SCV_ERROR:
      _f(&SCVal::error_, std::forward<_A>(_a)...);
      return true;
    case SCV_U32:
      _f(&SCVal::u32_, std::forward<_A>(_a)...);
      return true;
    case SCV_I32:
      _f(&SCVal::i32_, std::forward<_A>(_a)...);
      return true;
    case SCV_U64:
      _f(&SCVal::u64_, std::forward<_A>(_a)...);
      return true;
    case SCV_I64:
      _f(&SCVal::i64_, std::forward<_A>(_a)...);
      return true;
    case SCV_TIMEPOINT:
      _f(&SCVal::timepoint_, std::forward<_A>(_a)...);
      return true;
    case SCV_DURATION:
      _f(&SCVal::duration_, std::forward<_A>(_a)...);
      return true;
    case SCV_U128:
      _f(&SCVal::u128_, std::forward<_A>(_a)...);
      return true;
    case SCV_I128:
      _f(&SCVal::i128_, std::forward<_A>(_a)...);
      return true;
    case SCV_U256:
      _f(&SCVal::u256_, std::forward<_A>(_a)...);
      return true;
    case SCV_I256:
      _f(&SCVal::i256_, std::forward<_A>(_a)...);
      return true;
    case SCV_BYTES:
      _f(&SCVal::bytes_, std::forward<_A>(_a)...);
      return true;
    case SCV_STRING:
      _f(&SCVal::str_, std::forward<_A>(_a)...);
      return true;
    case SCV_SYMBOL:
      _f(&SCVal::sym_, std::forward<_A>(_a)...);
      return true;
    case SCV_VEC:
      _f(&SCVal::vec_, std::forward<_A>(_a)...);
      return true;
    case SCV_MAP:
      _f(&SCVal::map_, std::forward<_A>(_a)...);
      return true;
    case SCV_ADDRESS:
      _f(&SCVal::address_, std::forward<_A>(_a)...);
      return true;
    case SCV_CONTRACT_INSTANCE:
      _f(&SCVal::instance_, std::forward<_A>(_a)...);
      return true;
    case SCV_LEDGER_KEY_CONTRACT_INSTANCE:
      return true;
    case SCV_LEDGER_KEY_NONCE:
      _f(&SCVal::nonce_key_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return type_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of type in SCVal");
    if (fnum != _xdr_field_number(type_)) {
      this->~SCVal();
      type_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
    }
    else
      type_ = which;
  }
  explicit SCVal(SCValType which = SCValType{}) : type_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
  }
  SCVal(const SCVal &source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this, source);
  }
  SCVal(SCVal &&source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this,
                      std::move(source));
  }
  ~SCVal() { _xdr_with_mem_ptr(xdr::field_destructor, type_, *this); }
  SCVal &operator=(const SCVal &source) {
    if (_xdr_field_number(type_)
        == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this, source);
    else {
      this->~SCVal();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this, source);
    }
    type_ = source.type_;
    return *this;
  }
  SCVal &operator=(SCVal &&source) {
    if (_xdr_field_number(type_)
         == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this,
                        std::move(source));
    else {
      this->~SCVal();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this,
                        std::move(source));
    }
    type_ = source.type_;
    return *this;
  }

  SCValType type() const { return SCValType(type_); }
  SCVal &type(SCValType _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  bool &b() {
    if (_xdr_field_number(type_) == 1)
      return b_;
    throw xdr::xdr_wrong_union("SCVal: b accessed when not selected");
  }
  const bool &b() const {
    if (_xdr_field_number(type_) == 1)
      return b_;
    throw xdr::xdr_wrong_union("SCVal: b accessed when not selected");
  }
  SCError &error() {
    if (_xdr_field_number(type_) == 2)
      return error_;
    throw xdr::xdr_wrong_union("SCVal: error accessed when not selected");
  }
  const SCError &error() const {
    if (_xdr_field_number(type_) == 2)
      return error_;
    throw xdr::xdr_wrong_union("SCVal: error accessed when not selected");
  }
  uint32 &u32() {
    if (_xdr_field_number(type_) == 3)
      return u32_;
    throw xdr::xdr_wrong_union("SCVal: u32 accessed when not selected");
  }
  const uint32 &u32() const {
    if (_xdr_field_number(type_) == 3)
      return u32_;
    throw xdr::xdr_wrong_union("SCVal: u32 accessed when not selected");
  }
  int32 &i32() {
    if (_xdr_field_number(type_) == 4)
      return i32_;
    throw xdr::xdr_wrong_union("SCVal: i32 accessed when not selected");
  }
  const int32 &i32() const {
    if (_xdr_field_number(type_) == 4)
      return i32_;
    throw xdr::xdr_wrong_union("SCVal: i32 accessed when not selected");
  }
  uint64 &u64() {
    if (_xdr_field_number(type_) == 5)
      return u64_;
    throw xdr::xdr_wrong_union("SCVal: u64 accessed when not selected");
  }
  const uint64 &u64() const {
    if (_xdr_field_number(type_) == 5)
      return u64_;
    throw xdr::xdr_wrong_union("SCVal: u64 accessed when not selected");
  }
  int64 &i64() {
    if (_xdr_field_number(type_) == 6)
      return i64_;
    throw xdr::xdr_wrong_union("SCVal: i64 accessed when not selected");
  }
  const int64 &i64() const {
    if (_xdr_field_number(type_) == 6)
      return i64_;
    throw xdr::xdr_wrong_union("SCVal: i64 accessed when not selected");
  }
  TimePoint &timepoint() {
    if (_xdr_field_number(type_) == 7)
      return timepoint_;
    throw xdr::xdr_wrong_union("SCVal: timepoint accessed when not selected");
  }
  const TimePoint &timepoint() const {
    if (_xdr_field_number(type_) == 7)
      return timepoint_;
    throw xdr::xdr_wrong_union("SCVal: timepoint accessed when not selected");
  }
  Duration &duration() {
    if (_xdr_field_number(type_) == 8)
      return duration_;
    throw xdr::xdr_wrong_union("SCVal: duration accessed when not selected");
  }
  const Duration &duration() const {
    if (_xdr_field_number(type_) == 8)
      return duration_;
    throw xdr::xdr_wrong_union("SCVal: duration accessed when not selected");
  }
  UInt128Parts &u128() {
    if (_xdr_field_number(type_) == 9)
      return u128_;
    throw xdr::xdr_wrong_union("SCVal: u128 accessed when not selected");
  }
  const UInt128Parts &u128() const {
    if (_xdr_field_number(type_) == 9)
      return u128_;
    throw xdr::xdr_wrong_union("SCVal: u128 accessed when not selected");
  }
  Int128Parts &i128() {
    if (_xdr_field_number(type_) == 10)
      return i128_;
    throw xdr::xdr_wrong_union("SCVal: i128 accessed when not selected");
  }
  const Int128Parts &i128() const {
    if (_xdr_field_number(type_) == 10)
      return i128_;
    throw xdr::xdr_wrong_union("SCVal: i128 accessed when not selected");
  }
  UInt256Parts &u256() {
    if (_xdr_field_number(type_) == 11)
      return u256_;
    throw xdr::xdr_wrong_union("SCVal: u256 accessed when not selected");
  }
  const UInt256Parts &u256() const {
    if (_xdr_field_number(type_) == 11)
      return u256_;
    throw xdr::xdr_wrong_union("SCVal: u256 accessed when not selected");
  }
  Int256Parts &i256() {
    if (_xdr_field_number(type_) == 12)
      return i256_;
    throw xdr::xdr_wrong_union("SCVal: i256 accessed when not selected");
  }
  const Int256Parts &i256() const {
    if (_xdr_field_number(type_) == 12)
      return i256_;
    throw xdr::xdr_wrong_union("SCVal: i256 accessed when not selected");
  }
  SCBytes &bytes() {
    if (_xdr_field_number(type_) == 13)
      return bytes_;
    throw xdr::xdr_wrong_union("SCVal: bytes accessed when not selected");
  }
  const SCBytes &bytes() const {
    if (_xdr_field_number(type_) == 13)
      return bytes_;
    throw xdr::xdr_wrong_union("SCVal: bytes accessed when not selected");
  }
  SCString &str() {
    if (_xdr_field_number(type_) == 14)
      return str_;
    throw xdr::xdr_wrong_union("SCVal: str accessed when not selected");
  }
  const SCString &str() const {
    if (_xdr_field_number(type_) == 14)
      return str_;
    throw xdr::xdr_wrong_union("SCVal: str accessed when not selected");
  }
  SCSymbol &sym() {
    if (_xdr_field_number(type_) == 15)
      return sym_;
    throw xdr::xdr_wrong_union("SCVal: sym accessed when not selected");
  }
  const SCSymbol &sym() const {
    if (_xdr_field_number(type_) == 15)
      return sym_;
    throw xdr::xdr_wrong_union("SCVal: sym accessed when not selected");
  }
  xdr::pointer<SCVec> &vec() {
    if (_xdr_field_number(type_) == 16)
      return vec_;
    throw xdr::xdr_wrong_union("SCVal: vec accessed when not selected");
  }
  const xdr::pointer<SCVec> &vec() const {
    if (_xdr_field_number(type_) == 16)
      return vec_;
    throw xdr::xdr_wrong_union("SCVal: vec accessed when not selected");
  }
  xdr::pointer<SCMap> &map() {
    if (_xdr_field_number(type_) == 17)
      return map_;
    throw xdr::xdr_wrong_union("SCVal: map accessed when not selected");
  }
  const xdr::pointer<SCMap> &map() const {
    if (_xdr_field_number(type_) == 17)
      return map_;
    throw xdr::xdr_wrong_union("SCVal: map accessed when not selected");
  }
  SCAddress &address() {
    if (_xdr_field_number(type_) == 18)
      return address_;
    throw xdr::xdr_wrong_union("SCVal: address accessed when not selected");
  }
  const SCAddress &address() const {
    if (_xdr_field_number(type_) == 18)
      return address_;
    throw xdr::xdr_wrong_union("SCVal: address accessed when not selected");
  }
  SCContractInstance &instance() {
    if (_xdr_field_number(type_) == 19)
      return instance_;
    throw xdr::xdr_wrong_union("SCVal: instance accessed when not selected");
  }
  const SCContractInstance &instance() const {
    if (_xdr_field_number(type_) == 19)
      return instance_;
    throw xdr::xdr_wrong_union("SCVal: instance accessed when not selected");
  }
  SCNonceKey &nonce_key() {
    if (_xdr_field_number(type_) == 20)
      return nonce_key_;
    throw xdr::xdr_wrong_union("SCVal: nonce_key accessed when not selected");
  }
  const SCNonceKey &nonce_key() const {
    if (_xdr_field_number(type_) == 20)
      return nonce_key_;
    throw xdr::xdr_wrong_union("SCVal: nonce_key accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCVal> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::SCVal;
  using case_type = ::stellar::SCVal::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().type());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "b";
    case 2:
      return "error";
    case 3:
      return "u32";
    case 4:
      return "i32";
    case 5:
      return "u64";
    case 6:
      return "i64";
    case 7:
      return "timepoint";
    case 8:
      return "duration";
    case 9:
      return "u128";
    case 10:
      return "i128";
    case 11:
      return "u256";
    case 12:
      return "i256";
    case 13:
      return "bytes";
    case 14:
      return "str";
    case 15:
      return "sym";
    case 16:
      return "vec";
    case 17:
      return "map";
    case 18:
      return "address";
    case 19:
      return "instance";
    case 20:
      return "nonce_key";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::SCVal &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of type in SCVal");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SCVal &obj) {
    xdr::archive(ar, obj.type(), "type");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of type in SCVal");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SCVal &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "type");
    obj.type(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

struct SCMapEntry {
  SCVal key{};
  SCVal val{};

  SCMapEntry() = default;
  template<typename _key_T,
           typename _val_T,
           typename = typename
           std::enable_if<std::is_constructible<SCVal, _key_T>::value
                          && std::is_constructible<SCVal, _val_T>::value
                         >::type>
  explicit SCMapEntry(_key_T &&_key,
                      _val_T &&_val)
    : key(std::forward<_key_T>(_key)),
      val(std::forward<_val_T>(_val)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCMapEntry>
  : xdr_struct_base<field_ptr<::stellar::SCMapEntry,
                              decltype(::stellar::SCMapEntry::key),
                              &::stellar::SCMapEntry::key>,
                    field_ptr<::stellar::SCMapEntry,
                              decltype(::stellar::SCMapEntry::val),
                              &::stellar::SCMapEntry::val>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SCMapEntry &obj) {
    archive(ar, obj.key, "key");
    archive(ar, obj.val, "val");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SCMapEntry &obj) {
    archive(ar, obj.key, "key");
    archive(ar, obj.val, "val");
    xdr::validate(obj);
  }
};
} namespace stellar {

}

#endif // !__XDR_STELLAR_CONTRACT_H_INCLUDED__
