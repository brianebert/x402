// -*- C++ -*-
// Automatically generated from Stellar-contract-spec.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_CONTRACT_SPEC_H_INCLUDED__
#define __XDR_STELLAR_CONTRACT_SPEC_H_INCLUDED__ 1

#include <xdrpp/types.h>

 #include "xdr/Stellar-types.h"
 #include "xdr/Stellar-contract.h"

namespace stellar {

Constexpr const std::uint32_t SC_SPEC_DOC_LIMIT = 1024;

enum SCSpecType : std::int32_t {
  SC_SPEC_TYPE_VAL = 0,
  SC_SPEC_TYPE_BOOL = 1,
  SC_SPEC_TYPE_VOID = 2,
  SC_SPEC_TYPE_ERROR = 3,
  SC_SPEC_TYPE_U32 = 4,
  SC_SPEC_TYPE_I32 = 5,
  SC_SPEC_TYPE_U64 = 6,
  SC_SPEC_TYPE_I64 = 7,
  SC_SPEC_TYPE_TIMEPOINT = 8,
  SC_SPEC_TYPE_DURATION = 9,
  SC_SPEC_TYPE_U128 = 10,
  SC_SPEC_TYPE_I128 = 11,
  SC_SPEC_TYPE_U256 = 12,
  SC_SPEC_TYPE_I256 = 13,
  SC_SPEC_TYPE_BYTES = 14,
  SC_SPEC_TYPE_STRING = 16,
  SC_SPEC_TYPE_SYMBOL = 17,
  SC_SPEC_TYPE_ADDRESS = 19,
  SC_SPEC_TYPE_MUXED_ADDRESS = 20,
  SC_SPEC_TYPE_OPTION = 1000,
  SC_SPEC_TYPE_RESULT = 1001,
  SC_SPEC_TYPE_VEC = 1002,
  SC_SPEC_TYPE_MAP = 1004,
  SC_SPEC_TYPE_TUPLE = 1005,
  SC_SPEC_TYPE_BYTES_N = 1006,
  SC_SPEC_TYPE_UDT = 2000,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCSpecType>
  : xdr_integral_base<::stellar::SCSpecType, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::SCSpecType val) {
    switch (val) {
    case ::stellar::SC_SPEC_TYPE_VAL:
      return "SC_SPEC_TYPE_VAL";
    case ::stellar::SC_SPEC_TYPE_BOOL:
      return "SC_SPEC_TYPE_BOOL";
    case ::stellar::SC_SPEC_TYPE_VOID:
      return "SC_SPEC_TYPE_VOID";
    case ::stellar::SC_SPEC_TYPE_ERROR:
      return "SC_SPEC_TYPE_ERROR";
    case ::stellar::SC_SPEC_TYPE_U32:
      return "SC_SPEC_TYPE_U32";
    case ::stellar::SC_SPEC_TYPE_I32:
      return "SC_SPEC_TYPE_I32";
    case ::stellar::SC_SPEC_TYPE_U64:
      return "SC_SPEC_TYPE_U64";
    case ::stellar::SC_SPEC_TYPE_I64:
      return "SC_SPEC_TYPE_I64";
    case ::stellar::SC_SPEC_TYPE_TIMEPOINT:
      return "SC_SPEC_TYPE_TIMEPOINT";
    case ::stellar::SC_SPEC_TYPE_DURATION:
      return "SC_SPEC_TYPE_DURATION";
    case ::stellar::SC_SPEC_TYPE_U128:
      return "SC_SPEC_TYPE_U128";
    case ::stellar::SC_SPEC_TYPE_I128:
      return "SC_SPEC_TYPE_I128";
    case ::stellar::SC_SPEC_TYPE_U256:
      return "SC_SPEC_TYPE_U256";
    case ::stellar::SC_SPEC_TYPE_I256:
      return "SC_SPEC_TYPE_I256";
    case ::stellar::SC_SPEC_TYPE_BYTES:
      return "SC_SPEC_TYPE_BYTES";
    case ::stellar::SC_SPEC_TYPE_STRING:
      return "SC_SPEC_TYPE_STRING";
    case ::stellar::SC_SPEC_TYPE_SYMBOL:
      return "SC_SPEC_TYPE_SYMBOL";
    case ::stellar::SC_SPEC_TYPE_ADDRESS:
      return "SC_SPEC_TYPE_ADDRESS";
    case ::stellar::SC_SPEC_TYPE_MUXED_ADDRESS:
      return "SC_SPEC_TYPE_MUXED_ADDRESS";
    case ::stellar::SC_SPEC_TYPE_OPTION:
      return "SC_SPEC_TYPE_OPTION";
    case ::stellar::SC_SPEC_TYPE_RESULT:
      return "SC_SPEC_TYPE_RESULT";
    case ::stellar::SC_SPEC_TYPE_VEC:
      return "SC_SPEC_TYPE_VEC";
    case ::stellar::SC_SPEC_TYPE_MAP:
      return "SC_SPEC_TYPE_MAP";
    case ::stellar::SC_SPEC_TYPE_TUPLE:
      return "SC_SPEC_TYPE_TUPLE";
    case ::stellar::SC_SPEC_TYPE_BYTES_N:
      return "SC_SPEC_TYPE_BYTES_N";
    case ::stellar::SC_SPEC_TYPE_UDT:
      return "SC_SPEC_TYPE_UDT";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::SC_SPEC_TYPE_VAL,
      ::stellar::SC_SPEC_TYPE_BOOL,
      ::stellar::SC_SPEC_TYPE_VOID,
      ::stellar::SC_SPEC_TYPE_ERROR,
      ::stellar::SC_SPEC_TYPE_U32,
      ::stellar::SC_SPEC_TYPE_I32,
      ::stellar::SC_SPEC_TYPE_U64,
      ::stellar::SC_SPEC_TYPE_I64,
      ::stellar::SC_SPEC_TYPE_TIMEPOINT,
      ::stellar::SC_SPEC_TYPE_DURATION,
      ::stellar::SC_SPEC_TYPE_U128,
      ::stellar::SC_SPEC_TYPE_I128,
      ::stellar::SC_SPEC_TYPE_U256,
      ::stellar::SC_SPEC_TYPE_I256,
      ::stellar::SC_SPEC_TYPE_BYTES,
      ::stellar::SC_SPEC_TYPE_STRING,
      ::stellar::SC_SPEC_TYPE_SYMBOL,
      ::stellar::SC_SPEC_TYPE_ADDRESS,
      ::stellar::SC_SPEC_TYPE_MUXED_ADDRESS,
      ::stellar::SC_SPEC_TYPE_OPTION,
      ::stellar::SC_SPEC_TYPE_RESULT,
      ::stellar::SC_SPEC_TYPE_VEC,
      ::stellar::SC_SPEC_TYPE_MAP,
      ::stellar::SC_SPEC_TYPE_TUPLE,
      ::stellar::SC_SPEC_TYPE_BYTES_N,
      ::stellar::SC_SPEC_TYPE_UDT
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct SCSpecTypeOption {
  SCSpecTypeDef valueType{};

  SCSpecTypeOption() = default;
  template<typename _valueType_T,
           typename = typename
           std::enable_if<std::is_constructible<SCSpecTypeDef, _valueType_T>::value
                         >::type>
  explicit SCSpecTypeOption(_valueType_T &&_valueType)
    : valueType(std::forward<_valueType_T>(_valueType)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCSpecTypeOption>
  : xdr_struct_base<field_ptr<::stellar::SCSpecTypeOption,
                              decltype(::stellar::SCSpecTypeOption::valueType),
                              &::stellar::SCSpecTypeOption::valueType>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SCSpecTypeOption &obj) {
    archive(ar, obj.valueType, "valueType");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SCSpecTypeOption &obj) {
    archive(ar, obj.valueType, "valueType");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct SCSpecTypeResult {
  SCSpecTypeDef okType{};
  SCSpecTypeDef errorType{};

  SCSpecTypeResult() = default;
  template<typename _okType_T,
           typename _errorType_T,
           typename = typename
           std::enable_if<std::is_constructible<SCSpecTypeDef, _okType_T>::value
                          && std::is_constructible<SCSpecTypeDef, _errorType_T>::value
                         >::type>
  explicit SCSpecTypeResult(_okType_T &&_okType,
                            _errorType_T &&_errorType)
    : okType(std::forward<_okType_T>(_okType)),
      errorType(std::forward<_errorType_T>(_errorType)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCSpecTypeResult>
  : xdr_struct_base<field_ptr<::stellar::SCSpecTypeResult,
                              decltype(::stellar::SCSpecTypeResult::okType),
                              &::stellar::SCSpecTypeResult::okType>,
                    field_ptr<::stellar::SCSpecTypeResult,
                              decltype(::stellar::SCSpecTypeResult::errorType),
                              &::stellar::SCSpecTypeResult::errorType>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SCSpecTypeResult &obj) {
    archive(ar, obj.okType, "okType");
    archive(ar, obj.errorType, "errorType");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SCSpecTypeResult &obj) {
    archive(ar, obj.okType, "okType");
    archive(ar, obj.errorType, "errorType");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct SCSpecTypeVec {
  SCSpecTypeDef elementType{};

  SCSpecTypeVec() = default;
  template<typename _elementType_T,
           typename = typename
           std::enable_if<std::is_constructible<SCSpecTypeDef, _elementType_T>::value
                         >::type>
  explicit SCSpecTypeVec(_elementType_T &&_elementType)
    : elementType(std::forward<_elementType_T>(_elementType)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCSpecTypeVec>
  : xdr_struct_base<field_ptr<::stellar::SCSpecTypeVec,
                              decltype(::stellar::SCSpecTypeVec::elementType),
                              &::stellar::SCSpecTypeVec::elementType>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SCSpecTypeVec &obj) {
    archive(ar, obj.elementType, "elementType");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SCSpecTypeVec &obj) {
    archive(ar, obj.elementType, "elementType");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct SCSpecTypeMap {
  SCSpecTypeDef keyType{};
  SCSpecTypeDef valueType{};

  SCSpecTypeMap() = default;
  template<typename _keyType_T,
           typename _valueType_T,
           typename = typename
           std::enable_if<std::is_constructible<SCSpecTypeDef, _keyType_T>::value
                          && std::is_constructible<SCSpecTypeDef, _valueType_T>::value
                         >::type>
  explicit SCSpecTypeMap(_keyType_T &&_keyType,
                         _valueType_T &&_valueType)
    : keyType(std::forward<_keyType_T>(_keyType)),
      valueType(std::forward<_valueType_T>(_valueType)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCSpecTypeMap>
  : xdr_struct_base<field_ptr<::stellar::SCSpecTypeMap,
                              decltype(::stellar::SCSpecTypeMap::keyType),
                              &::stellar::SCSpecTypeMap::keyType>,
                    field_ptr<::stellar::SCSpecTypeMap,
                              decltype(::stellar::SCSpecTypeMap::valueType),
                              &::stellar::SCSpecTypeMap::valueType>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SCSpecTypeMap &obj) {
    archive(ar, obj.keyType, "keyType");
    archive(ar, obj.valueType, "valueType");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SCSpecTypeMap &obj) {
    archive(ar, obj.keyType, "keyType");
    archive(ar, obj.valueType, "valueType");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct SCSpecTypeTuple {
  xdr::xvector<SCSpecTypeDef,12> valueTypes{};

  SCSpecTypeTuple() = default;
  template<typename _valueTypes_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::xvector<SCSpecTypeDef,12>, _valueTypes_T>::value
                         >::type>
  explicit SCSpecTypeTuple(_valueTypes_T &&_valueTypes)
    : valueTypes(std::forward<_valueTypes_T>(_valueTypes)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCSpecTypeTuple>
  : xdr_struct_base<field_ptr<::stellar::SCSpecTypeTuple,
                              decltype(::stellar::SCSpecTypeTuple::valueTypes),
                              &::stellar::SCSpecTypeTuple::valueTypes>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SCSpecTypeTuple &obj) {
    archive(ar, obj.valueTypes, "valueTypes");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SCSpecTypeTuple &obj) {
    archive(ar, obj.valueTypes, "valueTypes");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct SCSpecTypeBytesN {
  uint32 n{};

  SCSpecTypeBytesN() = default;
  template<typename _n_T,
           typename = typename
           std::enable_if<std::is_constructible<uint32, _n_T>::value
                         >::type>
  explicit SCSpecTypeBytesN(_n_T &&_n)
    : n(std::forward<_n_T>(_n)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCSpecTypeBytesN>
  : xdr_struct_base<field_ptr<::stellar::SCSpecTypeBytesN,
                              decltype(::stellar::SCSpecTypeBytesN::n),
                              &::stellar::SCSpecTypeBytesN::n>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SCSpecTypeBytesN &obj) {
    archive(ar, obj.n, "n");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SCSpecTypeBytesN &obj) {
    archive(ar, obj.n, "n");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct SCSpecTypeUDT {
  xdr::xstring<60> name{};

  SCSpecTypeUDT() = default;
  template<typename _name_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::xstring<60>, _name_T>::value
                         >::type>
  explicit SCSpecTypeUDT(_name_T &&_name)
    : name(std::forward<_name_T>(_name)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCSpecTypeUDT>
  : xdr_struct_base<field_ptr<::stellar::SCSpecTypeUDT,
                              decltype(::stellar::SCSpecTypeUDT::name),
                              &::stellar::SCSpecTypeUDT::name>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SCSpecTypeUDT &obj) {
    archive(ar, obj.name, "name");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SCSpecTypeUDT &obj) {
    archive(ar, obj.name, "name");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct SCSpecTypeDef {
  using _xdr_case_type = xdr::xdr_traits<SCSpecType>::case_type;
private:
  _xdr_case_type type_;
  union {
    SCSpecTypeOption option_;
    SCSpecTypeResult result_;
    SCSpecTypeVec vec_;
    SCSpecTypeMap map_;
    SCSpecTypeTuple tuple_;
    SCSpecTypeBytesN bytesN_;
    SCSpecTypeUDT udt_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<SCSpecType> &_xdr_case_values() {
    static const std::vector<SCSpecType> _xdr_disc_vec {
      SC_SPEC_TYPE_VAL,
      SC_SPEC_TYPE_BOOL,
      SC_SPEC_TYPE_VOID,
      SC_SPEC_TYPE_ERROR,
      SC_SPEC_TYPE_U32,
      SC_SPEC_TYPE_I32,
      SC_SPEC_TYPE_U64,
      SC_SPEC_TYPE_I64,
      SC_SPEC_TYPE_TIMEPOINT,
      SC_SPEC_TYPE_DURATION,
      SC_SPEC_TYPE_U128,
      SC_SPEC_TYPE_I128,
      SC_SPEC_TYPE_U256,
      SC_SPEC_TYPE_I256,
      SC_SPEC_TYPE_BYTES,
      SC_SPEC_TYPE_STRING,
      SC_SPEC_TYPE_SYMBOL,
      SC_SPEC_TYPE_ADDRESS,
      SC_SPEC_TYPE_MUXED_ADDRESS,
      SC_SPEC_TYPE_OPTION,
      SC_SPEC_TYPE_RESULT,
      SC_SPEC_TYPE_VEC,
      SC_SPEC_TYPE_MAP,
      SC_SPEC_TYPE_TUPLE,
      SC_SPEC_TYPE_BYTES_N,
      SC_SPEC_TYPE_UDT
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == SC_SPEC_TYPE_VAL || which == SC_SPEC_TYPE_BOOL || which == SC_SPEC_TYPE_VOID || which == SC_SPEC_TYPE_ERROR || which == SC_SPEC_TYPE_U32 || which == SC_SPEC_TYPE_I32 || which == SC_SPEC_TYPE_U64 || which == SC_SPEC_TYPE_I64 || which == SC_SPEC_TYPE_TIMEPOINT || which == SC_SPEC_TYPE_DURATION || which == SC_SPEC_TYPE_U128 || which == SC_SPEC_TYPE_I128 || which == SC_SPEC_TYPE_U256 || which == SC_SPEC_TYPE_I256 || which == SC_SPEC_TYPE_BYTES || which == SC_SPEC_TYPE_STRING || which == SC_SPEC_TYPE_SYMBOL || which == SC_SPEC_TYPE_ADDRESS || which == SC_SPEC_TYPE_MUXED_ADDRESS ? 0
      : which == SC_SPEC_TYPE_OPTION ? 1
      : which == SC_SPEC_TYPE_RESULT ? 2
      : which == SC_SPEC_TYPE_VEC ? 3
      : which == SC_SPEC_TYPE_MAP ? 4
      : which == SC_SPEC_TYPE_TUPLE ? 5
      : which == SC_SPEC_TYPE_BYTES_N ? 6
      : which == SC_SPEC_TYPE_UDT ? 7
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case SC_SPEC_TYPE_VAL:
    case SC_SPEC_TYPE_BOOL:
    case SC_SPEC_TYPE_VOID:
    case SC_SPEC_TYPE_ERROR:
    case SC_SPEC_TYPE_U32:
    case SC_SPEC_TYPE_I32:
    case SC_SPEC_TYPE_U64:
    case SC_SPEC_TYPE_I64:
    case SC_SPEC_TYPE_TIMEPOINT:
    case SC_SPEC_TYPE_DURATION:
    case SC_SPEC_TYPE_U128:
    case SC_SPEC_TYPE_I128:
    case SC_SPEC_TYPE_U256:
    case SC_SPEC_TYPE_I256:
    case SC_SPEC_TYPE_BYTES:
    case SC_SPEC_TYPE_STRING:
    case SC_SPEC_TYPE_SYMBOL:
    case SC_SPEC_TYPE_ADDRESS:
    case SC_SPEC_TYPE_MUXED_ADDRESS:
      return true;
    case SC_SPEC_TYPE_OPTION:
      _f(&SCSpecTypeDef::option_, std::forward<_A>(_a)...);
      return true;
    case SC_SPEC_TYPE_RESULT:
      _f(&SCSpecTypeDef::result_, std::forward<_A>(_a)...);
      return true;
    case SC_SPEC_TYPE_VEC:
      _f(&SCSpecTypeDef::vec_, std::forward<_A>(_a)...);
      return true;
    case SC_SPEC_TYPE_MAP:
      _f(&SCSpecTypeDef::map_, std::forward<_A>(_a)...);
      return true;
    case SC_SPEC_TYPE_TUPLE:
      _f(&SCSpecTypeDef::tuple_, std::forward<_A>(_a)...);
      return true;
    case SC_SPEC_TYPE_BYTES_N:
      _f(&SCSpecTypeDef::bytesN_, std::forward<_A>(_a)...);
      return true;
    case SC_SPEC_TYPE_UDT:
      _f(&SCSpecTypeDef::udt_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return type_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of type in SCSpecTypeDef");
    if (fnum != _xdr_field_number(type_)) {
      this->~SCSpecTypeDef();
      type_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
    }
    else
      type_ = which;
  }
  explicit SCSpecTypeDef(SCSpecType which = SCSpecType{}) : type_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
  }
  SCSpecTypeDef(const SCSpecTypeDef &source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this, source);
  }
  SCSpecTypeDef(SCSpecTypeDef &&source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this,
                      std::move(source));
  }
  ~SCSpecTypeDef() { _xdr_with_mem_ptr(xdr::field_destructor, type_, *this); }
  SCSpecTypeDef &operator=(const SCSpecTypeDef &source) {
    if (_xdr_field_number(type_)
        == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this, source);
    else {
      this->~SCSpecTypeDef();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this, source);
    }
    type_ = source.type_;
    return *this;
  }
  SCSpecTypeDef &operator=(SCSpecTypeDef &&source) {
    if (_xdr_field_number(type_)
         == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this,
                        std::move(source));
    else {
      this->~SCSpecTypeDef();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this,
                        std::move(source));
    }
    type_ = source.type_;
    return *this;
  }

  SCSpecType type() const { return SCSpecType(type_); }
  SCSpecTypeDef &type(SCSpecType _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  SCSpecTypeOption &option() {
    if (_xdr_field_number(type_) == 1)
      return option_;
    throw xdr::xdr_wrong_union("SCSpecTypeDef: option accessed when not selected");
  }
  const SCSpecTypeOption &option() const {
    if (_xdr_field_number(type_) == 1)
      return option_;
    throw xdr::xdr_wrong_union("SCSpecTypeDef: option accessed when not selected");
  }
  SCSpecTypeResult &result() {
    if (_xdr_field_number(type_) == 2)
      return result_;
    throw xdr::xdr_wrong_union("SCSpecTypeDef: result accessed when not selected");
  }
  const SCSpecTypeResult &result() const {
    if (_xdr_field_number(type_) == 2)
      return result_;
    throw xdr::xdr_wrong_union("SCSpecTypeDef: result accessed when not selected");
  }
  SCSpecTypeVec &vec() {
    if (_xdr_field_number(type_) == 3)
      return vec_;
    throw xdr::xdr_wrong_union("SCSpecTypeDef: vec accessed when not selected");
  }
  const SCSpecTypeVec &vec() const {
    if (_xdr_field_number(type_) == 3)
      return vec_;
    throw xdr::xdr_wrong_union("SCSpecTypeDef: vec accessed when not selected");
  }
  SCSpecTypeMap &map() {
    if (_xdr_field_number(type_) == 4)
      return map_;
    throw xdr::xdr_wrong_union("SCSpecTypeDef: map accessed when not selected");
  }
  const SCSpecTypeMap &map() const {
    if (_xdr_field_number(type_) == 4)
      return map_;
    throw xdr::xdr_wrong_union("SCSpecTypeDef: map accessed when not selected");
  }
  SCSpecTypeTuple &tuple() {
    if (_xdr_field_number(type_) == 5)
      return tuple_;
    throw xdr::xdr_wrong_union("SCSpecTypeDef: tuple accessed when not selected");
  }
  const SCSpecTypeTuple &tuple() const {
    if (_xdr_field_number(type_) == 5)
      return tuple_;
    throw xdr::xdr_wrong_union("SCSpecTypeDef: tuple accessed when not selected");
  }
  SCSpecTypeBytesN &bytesN() {
    if (_xdr_field_number(type_) == 6)
      return bytesN_;
    throw xdr::xdr_wrong_union("SCSpecTypeDef: bytesN accessed when not selected");
  }
  const SCSpecTypeBytesN &bytesN() const {
    if (_xdr_field_number(type_) == 6)
      return bytesN_;
    throw xdr::xdr_wrong_union("SCSpecTypeDef: bytesN accessed when not selected");
  }
  SCSpecTypeUDT &udt() {
    if (_xdr_field_number(type_) == 7)
      return udt_;
    throw xdr::xdr_wrong_union("SCSpecTypeDef: udt accessed when not selected");
  }
  const SCSpecTypeUDT &udt() const {
    if (_xdr_field_number(type_) == 7)
      return udt_;
    throw xdr::xdr_wrong_union("SCSpecTypeDef: udt accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCSpecTypeDef> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::SCSpecTypeDef;
  using case_type = ::stellar::SCSpecTypeDef::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().type());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "option";
    case 2:
      return "result";
    case 3:
      return "vec";
    case 4:
      return "map";
    case 5:
      return "tuple";
    case 6:
      return "bytesN";
    case 7:
      return "udt";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::SCSpecTypeDef &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of type in SCSpecTypeDef");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SCSpecTypeDef &obj) {
    xdr::archive(ar, obj.type(), "type");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of type in SCSpecTypeDef");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SCSpecTypeDef &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "type");
    obj.type(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

struct SCSpecUDTStructFieldV0 {
  xdr::xstring<SC_SPEC_DOC_LIMIT> doc{};
  xdr::xstring<30> name{};
  SCSpecTypeDef type{};

  SCSpecUDTStructFieldV0() = default;
  template<typename _doc_T,
           typename _name_T,
           typename _type_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::xstring<SC_SPEC_DOC_LIMIT>, _doc_T>::value
                          && std::is_constructible<xdr::xstring<30>, _name_T>::value
                          && std::is_constructible<SCSpecTypeDef, _type_T>::value
                         >::type>
  explicit SCSpecUDTStructFieldV0(_doc_T &&_doc,
                                  _name_T &&_name,
                                  _type_T &&_type)
    : doc(std::forward<_doc_T>(_doc)),
      name(std::forward<_name_T>(_name)),
      type(std::forward<_type_T>(_type)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCSpecUDTStructFieldV0>
  : xdr_struct_base<field_ptr<::stellar::SCSpecUDTStructFieldV0,
                              decltype(::stellar::SCSpecUDTStructFieldV0::doc),
                              &::stellar::SCSpecUDTStructFieldV0::doc>,
                    field_ptr<::stellar::SCSpecUDTStructFieldV0,
                              decltype(::stellar::SCSpecUDTStructFieldV0::name),
                              &::stellar::SCSpecUDTStructFieldV0::name>,
                    field_ptr<::stellar::SCSpecUDTStructFieldV0,
                              decltype(::stellar::SCSpecUDTStructFieldV0::type),
                              &::stellar::SCSpecUDTStructFieldV0::type>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SCSpecUDTStructFieldV0 &obj) {
    archive(ar, obj.doc, "doc");
    archive(ar, obj.name, "name");
    archive(ar, obj.type, "type");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SCSpecUDTStructFieldV0 &obj) {
    archive(ar, obj.doc, "doc");
    archive(ar, obj.name, "name");
    archive(ar, obj.type, "type");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct SCSpecUDTStructV0 {
  xdr::xstring<SC_SPEC_DOC_LIMIT> doc{};
  xdr::xstring<80> lib{};
  xdr::xstring<60> name{};
  xdr::xvector<SCSpecUDTStructFieldV0> fields{};

  SCSpecUDTStructV0() = default;
  template<typename _doc_T,
           typename _lib_T,
           typename _name_T,
           typename _fields_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::xstring<SC_SPEC_DOC_LIMIT>, _doc_T>::value
                          && std::is_constructible<xdr::xstring<80>, _lib_T>::value
                          && std::is_constructible<xdr::xstring<60>, _name_T>::value
                          && std::is_constructible<xdr::xvector<SCSpecUDTStructFieldV0>, _fields_T>::value
                         >::type>
  explicit SCSpecUDTStructV0(_doc_T &&_doc,
                             _lib_T &&_lib,
                             _name_T &&_name,
                             _fields_T &&_fields)
    : doc(std::forward<_doc_T>(_doc)),
      lib(std::forward<_lib_T>(_lib)),
      name(std::forward<_name_T>(_name)),
      fields(std::forward<_fields_T>(_fields)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCSpecUDTStructV0>
  : xdr_struct_base<field_ptr<::stellar::SCSpecUDTStructV0,
                              decltype(::stellar::SCSpecUDTStructV0::doc),
                              &::stellar::SCSpecUDTStructV0::doc>,
                    field_ptr<::stellar::SCSpecUDTStructV0,
                              decltype(::stellar::SCSpecUDTStructV0::lib),
                              &::stellar::SCSpecUDTStructV0::lib>,
                    field_ptr<::stellar::SCSpecUDTStructV0,
                              decltype(::stellar::SCSpecUDTStructV0::name),
                              &::stellar::SCSpecUDTStructV0::name>,
                    field_ptr<::stellar::SCSpecUDTStructV0,
                              decltype(::stellar::SCSpecUDTStructV0::fields),
                              &::stellar::SCSpecUDTStructV0::fields>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SCSpecUDTStructV0 &obj) {
    archive(ar, obj.doc, "doc");
    archive(ar, obj.lib, "lib");
    archive(ar, obj.name, "name");
    archive(ar, obj.fields, "fields");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SCSpecUDTStructV0 &obj) {
    archive(ar, obj.doc, "doc");
    archive(ar, obj.lib, "lib");
    archive(ar, obj.name, "name");
    archive(ar, obj.fields, "fields");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct SCSpecUDTUnionCaseVoidV0 {
  xdr::xstring<SC_SPEC_DOC_LIMIT> doc{};
  xdr::xstring<60> name{};

  SCSpecUDTUnionCaseVoidV0() = default;
  template<typename _doc_T,
           typename _name_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::xstring<SC_SPEC_DOC_LIMIT>, _doc_T>::value
                          && std::is_constructible<xdr::xstring<60>, _name_T>::value
                         >::type>
  explicit SCSpecUDTUnionCaseVoidV0(_doc_T &&_doc,
                                    _name_T &&_name)
    : doc(std::forward<_doc_T>(_doc)),
      name(std::forward<_name_T>(_name)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCSpecUDTUnionCaseVoidV0>
  : xdr_struct_base<field_ptr<::stellar::SCSpecUDTUnionCaseVoidV0,
                              decltype(::stellar::SCSpecUDTUnionCaseVoidV0::doc),
                              &::stellar::SCSpecUDTUnionCaseVoidV0::doc>,
                    field_ptr<::stellar::SCSpecUDTUnionCaseVoidV0,
                              decltype(::stellar::SCSpecUDTUnionCaseVoidV0::name),
                              &::stellar::SCSpecUDTUnionCaseVoidV0::name>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SCSpecUDTUnionCaseVoidV0 &obj) {
    archive(ar, obj.doc, "doc");
    archive(ar, obj.name, "name");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SCSpecUDTUnionCaseVoidV0 &obj) {
    archive(ar, obj.doc, "doc");
    archive(ar, obj.name, "name");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct SCSpecUDTUnionCaseTupleV0 {
  xdr::xstring<SC_SPEC_DOC_LIMIT> doc{};
  xdr::xstring<60> name{};
  xdr::xvector<SCSpecTypeDef> type{};

  SCSpecUDTUnionCaseTupleV0() = default;
  template<typename _doc_T,
           typename _name_T,
           typename _type_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::xstring<SC_SPEC_DOC_LIMIT>, _doc_T>::value
                          && std::is_constructible<xdr::xstring<60>, _name_T>::value
                          && std::is_constructible<xdr::xvector<SCSpecTypeDef>, _type_T>::value
                         >::type>
  explicit SCSpecUDTUnionCaseTupleV0(_doc_T &&_doc,
                                     _name_T &&_name,
                                     _type_T &&_type)
    : doc(std::forward<_doc_T>(_doc)),
      name(std::forward<_name_T>(_name)),
      type(std::forward<_type_T>(_type)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCSpecUDTUnionCaseTupleV0>
  : xdr_struct_base<field_ptr<::stellar::SCSpecUDTUnionCaseTupleV0,
                              decltype(::stellar::SCSpecUDTUnionCaseTupleV0::doc),
                              &::stellar::SCSpecUDTUnionCaseTupleV0::doc>,
                    field_ptr<::stellar::SCSpecUDTUnionCaseTupleV0,
                              decltype(::stellar::SCSpecUDTUnionCaseTupleV0::name),
                              &::stellar::SCSpecUDTUnionCaseTupleV0::name>,
                    field_ptr<::stellar::SCSpecUDTUnionCaseTupleV0,
                              decltype(::stellar::SCSpecUDTUnionCaseTupleV0::type),
                              &::stellar::SCSpecUDTUnionCaseTupleV0::type>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SCSpecUDTUnionCaseTupleV0 &obj) {
    archive(ar, obj.doc, "doc");
    archive(ar, obj.name, "name");
    archive(ar, obj.type, "type");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SCSpecUDTUnionCaseTupleV0 &obj) {
    archive(ar, obj.doc, "doc");
    archive(ar, obj.name, "name");
    archive(ar, obj.type, "type");
    xdr::validate(obj);
  }
};
} namespace stellar {

enum SCSpecUDTUnionCaseV0Kind : std::int32_t {
  SC_SPEC_UDT_UNION_CASE_VOID_V0 = 0,
  SC_SPEC_UDT_UNION_CASE_TUPLE_V0 = 1,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCSpecUDTUnionCaseV0Kind>
  : xdr_integral_base<::stellar::SCSpecUDTUnionCaseV0Kind, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::SCSpecUDTUnionCaseV0Kind val) {
    switch (val) {
    case ::stellar::SC_SPEC_UDT_UNION_CASE_VOID_V0:
      return "SC_SPEC_UDT_UNION_CASE_VOID_V0";
    case ::stellar::SC_SPEC_UDT_UNION_CASE_TUPLE_V0:
      return "SC_SPEC_UDT_UNION_CASE_TUPLE_V0";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::SC_SPEC_UDT_UNION_CASE_VOID_V0,
      ::stellar::SC_SPEC_UDT_UNION_CASE_TUPLE_V0
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct SCSpecUDTUnionCaseV0 {
  using _xdr_case_type = xdr::xdr_traits<SCSpecUDTUnionCaseV0Kind>::case_type;
private:
  _xdr_case_type kind_;
  union {
    SCSpecUDTUnionCaseVoidV0 voidCase_;
    SCSpecUDTUnionCaseTupleV0 tupleCase_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<SCSpecUDTUnionCaseV0Kind> &_xdr_case_values() {
    static const std::vector<SCSpecUDTUnionCaseV0Kind> _xdr_disc_vec {
      SC_SPEC_UDT_UNION_CASE_VOID_V0,
      SC_SPEC_UDT_UNION_CASE_TUPLE_V0
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == SC_SPEC_UDT_UNION_CASE_VOID_V0 ? 1
      : which == SC_SPEC_UDT_UNION_CASE_TUPLE_V0 ? 2
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case SC_SPEC_UDT_UNION_CASE_VOID_V0:
      _f(&SCSpecUDTUnionCaseV0::voidCase_, std::forward<_A>(_a)...);
      return true;
    case SC_SPEC_UDT_UNION_CASE_TUPLE_V0:
      _f(&SCSpecUDTUnionCaseV0::tupleCase_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return kind_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of kind in SCSpecUDTUnionCaseV0");
    if (fnum != _xdr_field_number(kind_)) {
      this->~SCSpecUDTUnionCaseV0();
      kind_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, kind_, *this);
    }
    else
      kind_ = which;
  }
  explicit SCSpecUDTUnionCaseV0(SCSpecUDTUnionCaseV0Kind which = SCSpecUDTUnionCaseV0Kind{}) : kind_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, kind_, *this);
  }
  SCSpecUDTUnionCaseV0(const SCSpecUDTUnionCaseV0 &source) : kind_(source.kind_) {
    _xdr_with_mem_ptr(xdr::field_constructor, kind_, *this, source);
  }
  SCSpecUDTUnionCaseV0(SCSpecUDTUnionCaseV0 &&source) : kind_(source.kind_) {
    _xdr_with_mem_ptr(xdr::field_constructor, kind_, *this,
                      std::move(source));
  }
  ~SCSpecUDTUnionCaseV0() { _xdr_with_mem_ptr(xdr::field_destructor, kind_, *this); }
  SCSpecUDTUnionCaseV0 &operator=(const SCSpecUDTUnionCaseV0 &source) {
    if (_xdr_field_number(kind_)
        == _xdr_field_number(source.kind_))
      _xdr_with_mem_ptr(xdr::field_assigner, kind_, *this, source);
    else {
      this->~SCSpecUDTUnionCaseV0();
      kind_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.kind_, *this, source);
    }
    kind_ = source.kind_;
    return *this;
  }
  SCSpecUDTUnionCaseV0 &operator=(SCSpecUDTUnionCaseV0 &&source) {
    if (_xdr_field_number(kind_)
         == _xdr_field_number(source.kind_))
      _xdr_with_mem_ptr(xdr::field_assigner, kind_, *this,
                        std::move(source));
    else {
      this->~SCSpecUDTUnionCaseV0();
      kind_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.kind_, *this,
                        std::move(source));
    }
    kind_ = source.kind_;
    return *this;
  }

  SCSpecUDTUnionCaseV0Kind kind() const { return SCSpecUDTUnionCaseV0Kind(kind_); }
  SCSpecUDTUnionCaseV0 &kind(SCSpecUDTUnionCaseV0Kind _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  SCSpecUDTUnionCaseVoidV0 &voidCase() {
    if (_xdr_field_number(kind_) == 1)
      return voidCase_;
    throw xdr::xdr_wrong_union("SCSpecUDTUnionCaseV0: voidCase accessed when not selected");
  }
  const SCSpecUDTUnionCaseVoidV0 &voidCase() const {
    if (_xdr_field_number(kind_) == 1)
      return voidCase_;
    throw xdr::xdr_wrong_union("SCSpecUDTUnionCaseV0: voidCase accessed when not selected");
  }
  SCSpecUDTUnionCaseTupleV0 &tupleCase() {
    if (_xdr_field_number(kind_) == 2)
      return tupleCase_;
    throw xdr::xdr_wrong_union("SCSpecUDTUnionCaseV0: tupleCase accessed when not selected");
  }
  const SCSpecUDTUnionCaseTupleV0 &tupleCase() const {
    if (_xdr_field_number(kind_) == 2)
      return tupleCase_;
    throw xdr::xdr_wrong_union("SCSpecUDTUnionCaseV0: tupleCase accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCSpecUDTUnionCaseV0> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::SCSpecUDTUnionCaseV0;
  using case_type = ::stellar::SCSpecUDTUnionCaseV0::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().kind());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "voidCase";
    case 2:
      return "tupleCase";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::SCSpecUDTUnionCaseV0 &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of kind in SCSpecUDTUnionCaseV0");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SCSpecUDTUnionCaseV0 &obj) {
    xdr::archive(ar, obj.kind(), "kind");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.kind(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of kind in SCSpecUDTUnionCaseV0");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SCSpecUDTUnionCaseV0 &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "kind");
    obj.kind(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.kind(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

struct SCSpecUDTUnionV0 {
  xdr::xstring<SC_SPEC_DOC_LIMIT> doc{};
  xdr::xstring<80> lib{};
  xdr::xstring<60> name{};
  xdr::xvector<SCSpecUDTUnionCaseV0> cases{};

  SCSpecUDTUnionV0() = default;
  template<typename _doc_T,
           typename _lib_T,
           typename _name_T,
           typename _cases_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::xstring<SC_SPEC_DOC_LIMIT>, _doc_T>::value
                          && std::is_constructible<xdr::xstring<80>, _lib_T>::value
                          && std::is_constructible<xdr::xstring<60>, _name_T>::value
                          && std::is_constructible<xdr::xvector<SCSpecUDTUnionCaseV0>, _cases_T>::value
                         >::type>
  explicit SCSpecUDTUnionV0(_doc_T &&_doc,
                            _lib_T &&_lib,
                            _name_T &&_name,
                            _cases_T &&_cases)
    : doc(std::forward<_doc_T>(_doc)),
      lib(std::forward<_lib_T>(_lib)),
      name(std::forward<_name_T>(_name)),
      cases(std::forward<_cases_T>(_cases)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCSpecUDTUnionV0>
  : xdr_struct_base<field_ptr<::stellar::SCSpecUDTUnionV0,
                              decltype(::stellar::SCSpecUDTUnionV0::doc),
                              &::stellar::SCSpecUDTUnionV0::doc>,
                    field_ptr<::stellar::SCSpecUDTUnionV0,
                              decltype(::stellar::SCSpecUDTUnionV0::lib),
                              &::stellar::SCSpecUDTUnionV0::lib>,
                    field_ptr<::stellar::SCSpecUDTUnionV0,
                              decltype(::stellar::SCSpecUDTUnionV0::name),
                              &::stellar::SCSpecUDTUnionV0::name>,
                    field_ptr<::stellar::SCSpecUDTUnionV0,
                              decltype(::stellar::SCSpecUDTUnionV0::cases),
                              &::stellar::SCSpecUDTUnionV0::cases>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SCSpecUDTUnionV0 &obj) {
    archive(ar, obj.doc, "doc");
    archive(ar, obj.lib, "lib");
    archive(ar, obj.name, "name");
    archive(ar, obj.cases, "cases");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SCSpecUDTUnionV0 &obj) {
    archive(ar, obj.doc, "doc");
    archive(ar, obj.lib, "lib");
    archive(ar, obj.name, "name");
    archive(ar, obj.cases, "cases");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct SCSpecUDTEnumCaseV0 {
  xdr::xstring<SC_SPEC_DOC_LIMIT> doc{};
  xdr::xstring<60> name{};
  uint32 value{};

  SCSpecUDTEnumCaseV0() = default;
  template<typename _doc_T,
           typename _name_T,
           typename _value_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::xstring<SC_SPEC_DOC_LIMIT>, _doc_T>::value
                          && std::is_constructible<xdr::xstring<60>, _name_T>::value
                          && std::is_constructible<uint32, _value_T>::value
                         >::type>
  explicit SCSpecUDTEnumCaseV0(_doc_T &&_doc,
                               _name_T &&_name,
                               _value_T &&_value)
    : doc(std::forward<_doc_T>(_doc)),
      name(std::forward<_name_T>(_name)),
      value(std::forward<_value_T>(_value)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCSpecUDTEnumCaseV0>
  : xdr_struct_base<field_ptr<::stellar::SCSpecUDTEnumCaseV0,
                              decltype(::stellar::SCSpecUDTEnumCaseV0::doc),
                              &::stellar::SCSpecUDTEnumCaseV0::doc>,
                    field_ptr<::stellar::SCSpecUDTEnumCaseV0,
                              decltype(::stellar::SCSpecUDTEnumCaseV0::name),
                              &::stellar::SCSpecUDTEnumCaseV0::name>,
                    field_ptr<::stellar::SCSpecUDTEnumCaseV0,
                              decltype(::stellar::SCSpecUDTEnumCaseV0::value),
                              &::stellar::SCSpecUDTEnumCaseV0::value>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SCSpecUDTEnumCaseV0 &obj) {
    archive(ar, obj.doc, "doc");
    archive(ar, obj.name, "name");
    archive(ar, obj.value, "value");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SCSpecUDTEnumCaseV0 &obj) {
    archive(ar, obj.doc, "doc");
    archive(ar, obj.name, "name");
    archive(ar, obj.value, "value");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct SCSpecUDTEnumV0 {
  xdr::xstring<SC_SPEC_DOC_LIMIT> doc{};
  xdr::xstring<80> lib{};
  xdr::xstring<60> name{};
  xdr::xvector<SCSpecUDTEnumCaseV0> cases{};

  SCSpecUDTEnumV0() = default;
  template<typename _doc_T,
           typename _lib_T,
           typename _name_T,
           typename _cases_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::xstring<SC_SPEC_DOC_LIMIT>, _doc_T>::value
                          && std::is_constructible<xdr::xstring<80>, _lib_T>::value
                          && std::is_constructible<xdr::xstring<60>, _name_T>::value
                          && std::is_constructible<xdr::xvector<SCSpecUDTEnumCaseV0>, _cases_T>::value
                         >::type>
  explicit SCSpecUDTEnumV0(_doc_T &&_doc,
                           _lib_T &&_lib,
                           _name_T &&_name,
                           _cases_T &&_cases)
    : doc(std::forward<_doc_T>(_doc)),
      lib(std::forward<_lib_T>(_lib)),
      name(std::forward<_name_T>(_name)),
      cases(std::forward<_cases_T>(_cases)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCSpecUDTEnumV0>
  : xdr_struct_base<field_ptr<::stellar::SCSpecUDTEnumV0,
                              decltype(::stellar::SCSpecUDTEnumV0::doc),
                              &::stellar::SCSpecUDTEnumV0::doc>,
                    field_ptr<::stellar::SCSpecUDTEnumV0,
                              decltype(::stellar::SCSpecUDTEnumV0::lib),
                              &::stellar::SCSpecUDTEnumV0::lib>,
                    field_ptr<::stellar::SCSpecUDTEnumV0,
                              decltype(::stellar::SCSpecUDTEnumV0::name),
                              &::stellar::SCSpecUDTEnumV0::name>,
                    field_ptr<::stellar::SCSpecUDTEnumV0,
                              decltype(::stellar::SCSpecUDTEnumV0::cases),
                              &::stellar::SCSpecUDTEnumV0::cases>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SCSpecUDTEnumV0 &obj) {
    archive(ar, obj.doc, "doc");
    archive(ar, obj.lib, "lib");
    archive(ar, obj.name, "name");
    archive(ar, obj.cases, "cases");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SCSpecUDTEnumV0 &obj) {
    archive(ar, obj.doc, "doc");
    archive(ar, obj.lib, "lib");
    archive(ar, obj.name, "name");
    archive(ar, obj.cases, "cases");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct SCSpecUDTErrorEnumCaseV0 {
  xdr::xstring<SC_SPEC_DOC_LIMIT> doc{};
  xdr::xstring<60> name{};
  uint32 value{};

  SCSpecUDTErrorEnumCaseV0() = default;
  template<typename _doc_T,
           typename _name_T,
           typename _value_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::xstring<SC_SPEC_DOC_LIMIT>, _doc_T>::value
                          && std::is_constructible<xdr::xstring<60>, _name_T>::value
                          && std::is_constructible<uint32, _value_T>::value
                         >::type>
  explicit SCSpecUDTErrorEnumCaseV0(_doc_T &&_doc,
                                    _name_T &&_name,
                                    _value_T &&_value)
    : doc(std::forward<_doc_T>(_doc)),
      name(std::forward<_name_T>(_name)),
      value(std::forward<_value_T>(_value)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCSpecUDTErrorEnumCaseV0>
  : xdr_struct_base<field_ptr<::stellar::SCSpecUDTErrorEnumCaseV0,
                              decltype(::stellar::SCSpecUDTErrorEnumCaseV0::doc),
                              &::stellar::SCSpecUDTErrorEnumCaseV0::doc>,
                    field_ptr<::stellar::SCSpecUDTErrorEnumCaseV0,
                              decltype(::stellar::SCSpecUDTErrorEnumCaseV0::name),
                              &::stellar::SCSpecUDTErrorEnumCaseV0::name>,
                    field_ptr<::stellar::SCSpecUDTErrorEnumCaseV0,
                              decltype(::stellar::SCSpecUDTErrorEnumCaseV0::value),
                              &::stellar::SCSpecUDTErrorEnumCaseV0::value>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SCSpecUDTErrorEnumCaseV0 &obj) {
    archive(ar, obj.doc, "doc");
    archive(ar, obj.name, "name");
    archive(ar, obj.value, "value");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SCSpecUDTErrorEnumCaseV0 &obj) {
    archive(ar, obj.doc, "doc");
    archive(ar, obj.name, "name");
    archive(ar, obj.value, "value");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct SCSpecUDTErrorEnumV0 {
  xdr::xstring<SC_SPEC_DOC_LIMIT> doc{};
  xdr::xstring<80> lib{};
  xdr::xstring<60> name{};
  xdr::xvector<SCSpecUDTErrorEnumCaseV0> cases{};

  SCSpecUDTErrorEnumV0() = default;
  template<typename _doc_T,
           typename _lib_T,
           typename _name_T,
           typename _cases_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::xstring<SC_SPEC_DOC_LIMIT>, _doc_T>::value
                          && std::is_constructible<xdr::xstring<80>, _lib_T>::value
                          && std::is_constructible<xdr::xstring<60>, _name_T>::value
                          && std::is_constructible<xdr::xvector<SCSpecUDTErrorEnumCaseV0>, _cases_T>::value
                         >::type>
  explicit SCSpecUDTErrorEnumV0(_doc_T &&_doc,
                                _lib_T &&_lib,
                                _name_T &&_name,
                                _cases_T &&_cases)
    : doc(std::forward<_doc_T>(_doc)),
      lib(std::forward<_lib_T>(_lib)),
      name(std::forward<_name_T>(_name)),
      cases(std::forward<_cases_T>(_cases)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCSpecUDTErrorEnumV0>
  : xdr_struct_base<field_ptr<::stellar::SCSpecUDTErrorEnumV0,
                              decltype(::stellar::SCSpecUDTErrorEnumV0::doc),
                              &::stellar::SCSpecUDTErrorEnumV0::doc>,
                    field_ptr<::stellar::SCSpecUDTErrorEnumV0,
                              decltype(::stellar::SCSpecUDTErrorEnumV0::lib),
                              &::stellar::SCSpecUDTErrorEnumV0::lib>,
                    field_ptr<::stellar::SCSpecUDTErrorEnumV0,
                              decltype(::stellar::SCSpecUDTErrorEnumV0::name),
                              &::stellar::SCSpecUDTErrorEnumV0::name>,
                    field_ptr<::stellar::SCSpecUDTErrorEnumV0,
                              decltype(::stellar::SCSpecUDTErrorEnumV0::cases),
                              &::stellar::SCSpecUDTErrorEnumV0::cases>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SCSpecUDTErrorEnumV0 &obj) {
    archive(ar, obj.doc, "doc");
    archive(ar, obj.lib, "lib");
    archive(ar, obj.name, "name");
    archive(ar, obj.cases, "cases");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SCSpecUDTErrorEnumV0 &obj) {
    archive(ar, obj.doc, "doc");
    archive(ar, obj.lib, "lib");
    archive(ar, obj.name, "name");
    archive(ar, obj.cases, "cases");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct SCSpecFunctionInputV0 {
  xdr::xstring<SC_SPEC_DOC_LIMIT> doc{};
  xdr::xstring<30> name{};
  SCSpecTypeDef type{};

  SCSpecFunctionInputV0() = default;
  template<typename _doc_T,
           typename _name_T,
           typename _type_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::xstring<SC_SPEC_DOC_LIMIT>, _doc_T>::value
                          && std::is_constructible<xdr::xstring<30>, _name_T>::value
                          && std::is_constructible<SCSpecTypeDef, _type_T>::value
                         >::type>
  explicit SCSpecFunctionInputV0(_doc_T &&_doc,
                                 _name_T &&_name,
                                 _type_T &&_type)
    : doc(std::forward<_doc_T>(_doc)),
      name(std::forward<_name_T>(_name)),
      type(std::forward<_type_T>(_type)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCSpecFunctionInputV0>
  : xdr_struct_base<field_ptr<::stellar::SCSpecFunctionInputV0,
                              decltype(::stellar::SCSpecFunctionInputV0::doc),
                              &::stellar::SCSpecFunctionInputV0::doc>,
                    field_ptr<::stellar::SCSpecFunctionInputV0,
                              decltype(::stellar::SCSpecFunctionInputV0::name),
                              &::stellar::SCSpecFunctionInputV0::name>,
                    field_ptr<::stellar::SCSpecFunctionInputV0,
                              decltype(::stellar::SCSpecFunctionInputV0::type),
                              &::stellar::SCSpecFunctionInputV0::type>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SCSpecFunctionInputV0 &obj) {
    archive(ar, obj.doc, "doc");
    archive(ar, obj.name, "name");
    archive(ar, obj.type, "type");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SCSpecFunctionInputV0 &obj) {
    archive(ar, obj.doc, "doc");
    archive(ar, obj.name, "name");
    archive(ar, obj.type, "type");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct SCSpecFunctionV0 {
  xdr::xstring<SC_SPEC_DOC_LIMIT> doc{};
  SCSymbol name{};
  xdr::xvector<SCSpecFunctionInputV0> inputs{};
  xdr::xvector<SCSpecTypeDef,1> outputs{};

  SCSpecFunctionV0() = default;
  template<typename _doc_T,
           typename _name_T,
           typename _inputs_T,
           typename _outputs_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::xstring<SC_SPEC_DOC_LIMIT>, _doc_T>::value
                          && std::is_constructible<SCSymbol, _name_T>::value
                          && std::is_constructible<xdr::xvector<SCSpecFunctionInputV0>, _inputs_T>::value
                          && std::is_constructible<xdr::xvector<SCSpecTypeDef,1>, _outputs_T>::value
                         >::type>
  explicit SCSpecFunctionV0(_doc_T &&_doc,
                            _name_T &&_name,
                            _inputs_T &&_inputs,
                            _outputs_T &&_outputs)
    : doc(std::forward<_doc_T>(_doc)),
      name(std::forward<_name_T>(_name)),
      inputs(std::forward<_inputs_T>(_inputs)),
      outputs(std::forward<_outputs_T>(_outputs)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCSpecFunctionV0>
  : xdr_struct_base<field_ptr<::stellar::SCSpecFunctionV0,
                              decltype(::stellar::SCSpecFunctionV0::doc),
                              &::stellar::SCSpecFunctionV0::doc>,
                    field_ptr<::stellar::SCSpecFunctionV0,
                              decltype(::stellar::SCSpecFunctionV0::name),
                              &::stellar::SCSpecFunctionV0::name>,
                    field_ptr<::stellar::SCSpecFunctionV0,
                              decltype(::stellar::SCSpecFunctionV0::inputs),
                              &::stellar::SCSpecFunctionV0::inputs>,
                    field_ptr<::stellar::SCSpecFunctionV0,
                              decltype(::stellar::SCSpecFunctionV0::outputs),
                              &::stellar::SCSpecFunctionV0::outputs>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SCSpecFunctionV0 &obj) {
    archive(ar, obj.doc, "doc");
    archive(ar, obj.name, "name");
    archive(ar, obj.inputs, "inputs");
    archive(ar, obj.outputs, "outputs");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SCSpecFunctionV0 &obj) {
    archive(ar, obj.doc, "doc");
    archive(ar, obj.name, "name");
    archive(ar, obj.inputs, "inputs");
    archive(ar, obj.outputs, "outputs");
    xdr::validate(obj);
  }
};
} namespace stellar {

enum SCSpecEventParamLocationV0 : std::int32_t {
  SC_SPEC_EVENT_PARAM_LOCATION_DATA = 0,
  SC_SPEC_EVENT_PARAM_LOCATION_TOPIC_LIST = 1,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCSpecEventParamLocationV0>
  : xdr_integral_base<::stellar::SCSpecEventParamLocationV0, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::SCSpecEventParamLocationV0 val) {
    switch (val) {
    case ::stellar::SC_SPEC_EVENT_PARAM_LOCATION_DATA:
      return "SC_SPEC_EVENT_PARAM_LOCATION_DATA";
    case ::stellar::SC_SPEC_EVENT_PARAM_LOCATION_TOPIC_LIST:
      return "SC_SPEC_EVENT_PARAM_LOCATION_TOPIC_LIST";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::SC_SPEC_EVENT_PARAM_LOCATION_DATA,
      ::stellar::SC_SPEC_EVENT_PARAM_LOCATION_TOPIC_LIST
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct SCSpecEventParamV0 {
  xdr::xstring<SC_SPEC_DOC_LIMIT> doc{};
  xdr::xstring<30> name{};
  SCSpecTypeDef type{};
  SCSpecEventParamLocationV0 location{};

  SCSpecEventParamV0() = default;
  template<typename _doc_T,
           typename _name_T,
           typename _type_T,
           typename _location_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::xstring<SC_SPEC_DOC_LIMIT>, _doc_T>::value
                          && std::is_constructible<xdr::xstring<30>, _name_T>::value
                          && std::is_constructible<SCSpecTypeDef, _type_T>::value
                          && std::is_constructible<SCSpecEventParamLocationV0, _location_T>::value
                         >::type>
  explicit SCSpecEventParamV0(_doc_T &&_doc,
                              _name_T &&_name,
                              _type_T &&_type,
                              _location_T &&_location)
    : doc(std::forward<_doc_T>(_doc)),
      name(std::forward<_name_T>(_name)),
      type(std::forward<_type_T>(_type)),
      location(std::forward<_location_T>(_location)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCSpecEventParamV0>
  : xdr_struct_base<field_ptr<::stellar::SCSpecEventParamV0,
                              decltype(::stellar::SCSpecEventParamV0::doc),
                              &::stellar::SCSpecEventParamV0::doc>,
                    field_ptr<::stellar::SCSpecEventParamV0,
                              decltype(::stellar::SCSpecEventParamV0::name),
                              &::stellar::SCSpecEventParamV0::name>,
                    field_ptr<::stellar::SCSpecEventParamV0,
                              decltype(::stellar::SCSpecEventParamV0::type),
                              &::stellar::SCSpecEventParamV0::type>,
                    field_ptr<::stellar::SCSpecEventParamV0,
                              decltype(::stellar::SCSpecEventParamV0::location),
                              &::stellar::SCSpecEventParamV0::location>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SCSpecEventParamV0 &obj) {
    archive(ar, obj.doc, "doc");
    archive(ar, obj.name, "name");
    archive(ar, obj.type, "type");
    archive(ar, obj.location, "location");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SCSpecEventParamV0 &obj) {
    archive(ar, obj.doc, "doc");
    archive(ar, obj.name, "name");
    archive(ar, obj.type, "type");
    archive(ar, obj.location, "location");
    xdr::validate(obj);
  }
};
} namespace stellar {

enum SCSpecEventDataFormat : std::int32_t {
  SC_SPEC_EVENT_DATA_FORMAT_SINGLE_VALUE = 0,
  SC_SPEC_EVENT_DATA_FORMAT_VEC = 1,
  SC_SPEC_EVENT_DATA_FORMAT_MAP = 2,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCSpecEventDataFormat>
  : xdr_integral_base<::stellar::SCSpecEventDataFormat, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::SCSpecEventDataFormat val) {
    switch (val) {
    case ::stellar::SC_SPEC_EVENT_DATA_FORMAT_SINGLE_VALUE:
      return "SC_SPEC_EVENT_DATA_FORMAT_SINGLE_VALUE";
    case ::stellar::SC_SPEC_EVENT_DATA_FORMAT_VEC:
      return "SC_SPEC_EVENT_DATA_FORMAT_VEC";
    case ::stellar::SC_SPEC_EVENT_DATA_FORMAT_MAP:
      return "SC_SPEC_EVENT_DATA_FORMAT_MAP";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::SC_SPEC_EVENT_DATA_FORMAT_SINGLE_VALUE,
      ::stellar::SC_SPEC_EVENT_DATA_FORMAT_VEC,
      ::stellar::SC_SPEC_EVENT_DATA_FORMAT_MAP
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct SCSpecEventV0 {
  xdr::xstring<SC_SPEC_DOC_LIMIT> doc{};
  xdr::xstring<80> lib{};
  SCSymbol name{};
  xdr::xvector<SCSymbol,2> prefixTopics{};
  xdr::xvector<SCSpecEventParamV0> params{};
  SCSpecEventDataFormat dataFormat{};

  SCSpecEventV0() = default;
  template<typename _doc_T,
           typename _lib_T,
           typename _name_T,
           typename _prefixTopics_T,
           typename _params_T,
           typename _dataFormat_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::xstring<SC_SPEC_DOC_LIMIT>, _doc_T>::value
                          && std::is_constructible<xdr::xstring<80>, _lib_T>::value
                          && std::is_constructible<SCSymbol, _name_T>::value
                          && std::is_constructible<xdr::xvector<SCSymbol,2>, _prefixTopics_T>::value
                          && std::is_constructible<xdr::xvector<SCSpecEventParamV0>, _params_T>::value
                          && std::is_constructible<SCSpecEventDataFormat, _dataFormat_T>::value
                         >::type>
  explicit SCSpecEventV0(_doc_T &&_doc,
                         _lib_T &&_lib,
                         _name_T &&_name,
                         _prefixTopics_T &&_prefixTopics,
                         _params_T &&_params,
                         _dataFormat_T &&_dataFormat)
    : doc(std::forward<_doc_T>(_doc)),
      lib(std::forward<_lib_T>(_lib)),
      name(std::forward<_name_T>(_name)),
      prefixTopics(std::forward<_prefixTopics_T>(_prefixTopics)),
      params(std::forward<_params_T>(_params)),
      dataFormat(std::forward<_dataFormat_T>(_dataFormat)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCSpecEventV0>
  : xdr_struct_base<field_ptr<::stellar::SCSpecEventV0,
                              decltype(::stellar::SCSpecEventV0::doc),
                              &::stellar::SCSpecEventV0::doc>,
                    field_ptr<::stellar::SCSpecEventV0,
                              decltype(::stellar::SCSpecEventV0::lib),
                              &::stellar::SCSpecEventV0::lib>,
                    field_ptr<::stellar::SCSpecEventV0,
                              decltype(::stellar::SCSpecEventV0::name),
                              &::stellar::SCSpecEventV0::name>,
                    field_ptr<::stellar::SCSpecEventV0,
                              decltype(::stellar::SCSpecEventV0::prefixTopics),
                              &::stellar::SCSpecEventV0::prefixTopics>,
                    field_ptr<::stellar::SCSpecEventV0,
                              decltype(::stellar::SCSpecEventV0::params),
                              &::stellar::SCSpecEventV0::params>,
                    field_ptr<::stellar::SCSpecEventV0,
                              decltype(::stellar::SCSpecEventV0::dataFormat),
                              &::stellar::SCSpecEventV0::dataFormat>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SCSpecEventV0 &obj) {
    archive(ar, obj.doc, "doc");
    archive(ar, obj.lib, "lib");
    archive(ar, obj.name, "name");
    archive(ar, obj.prefixTopics, "prefixTopics");
    archive(ar, obj.params, "params");
    archive(ar, obj.dataFormat, "dataFormat");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SCSpecEventV0 &obj) {
    archive(ar, obj.doc, "doc");
    archive(ar, obj.lib, "lib");
    archive(ar, obj.name, "name");
    archive(ar, obj.prefixTopics, "prefixTopics");
    archive(ar, obj.params, "params");
    archive(ar, obj.dataFormat, "dataFormat");
    xdr::validate(obj);
  }
};
} namespace stellar {

enum SCSpecEntryKind : std::int32_t {
  SC_SPEC_ENTRY_FUNCTION_V0 = 0,
  SC_SPEC_ENTRY_UDT_STRUCT_V0 = 1,
  SC_SPEC_ENTRY_UDT_UNION_V0 = 2,
  SC_SPEC_ENTRY_UDT_ENUM_V0 = 3,
  SC_SPEC_ENTRY_UDT_ERROR_ENUM_V0 = 4,
  SC_SPEC_ENTRY_EVENT_V0 = 5,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCSpecEntryKind>
  : xdr_integral_base<::stellar::SCSpecEntryKind, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::SCSpecEntryKind val) {
    switch (val) {
    case ::stellar::SC_SPEC_ENTRY_FUNCTION_V0:
      return "SC_SPEC_ENTRY_FUNCTION_V0";
    case ::stellar::SC_SPEC_ENTRY_UDT_STRUCT_V0:
      return "SC_SPEC_ENTRY_UDT_STRUCT_V0";
    case ::stellar::SC_SPEC_ENTRY_UDT_UNION_V0:
      return "SC_SPEC_ENTRY_UDT_UNION_V0";
    case ::stellar::SC_SPEC_ENTRY_UDT_ENUM_V0:
      return "SC_SPEC_ENTRY_UDT_ENUM_V0";
    case ::stellar::SC_SPEC_ENTRY_UDT_ERROR_ENUM_V0:
      return "SC_SPEC_ENTRY_UDT_ERROR_ENUM_V0";
    case ::stellar::SC_SPEC_ENTRY_EVENT_V0:
      return "SC_SPEC_ENTRY_EVENT_V0";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::SC_SPEC_ENTRY_FUNCTION_V0,
      ::stellar::SC_SPEC_ENTRY_UDT_STRUCT_V0,
      ::stellar::SC_SPEC_ENTRY_UDT_UNION_V0,
      ::stellar::SC_SPEC_ENTRY_UDT_ENUM_V0,
      ::stellar::SC_SPEC_ENTRY_UDT_ERROR_ENUM_V0,
      ::stellar::SC_SPEC_ENTRY_EVENT_V0
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct SCSpecEntry {
  using _xdr_case_type = xdr::xdr_traits<SCSpecEntryKind>::case_type;
private:
  _xdr_case_type kind_;
  union {
    SCSpecFunctionV0 functionV0_;
    SCSpecUDTStructV0 udtStructV0_;
    SCSpecUDTUnionV0 udtUnionV0_;
    SCSpecUDTEnumV0 udtEnumV0_;
    SCSpecUDTErrorEnumV0 udtErrorEnumV0_;
    SCSpecEventV0 eventV0_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<SCSpecEntryKind> &_xdr_case_values() {
    static const std::vector<SCSpecEntryKind> _xdr_disc_vec {
      SC_SPEC_ENTRY_FUNCTION_V0,
      SC_SPEC_ENTRY_UDT_STRUCT_V0,
      SC_SPEC_ENTRY_UDT_UNION_V0,
      SC_SPEC_ENTRY_UDT_ENUM_V0,
      SC_SPEC_ENTRY_UDT_ERROR_ENUM_V0,
      SC_SPEC_ENTRY_EVENT_V0
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == SC_SPEC_ENTRY_FUNCTION_V0 ? 1
      : which == SC_SPEC_ENTRY_UDT_STRUCT_V0 ? 2
      : which == SC_SPEC_ENTRY_UDT_UNION_V0 ? 3
      : which == SC_SPEC_ENTRY_UDT_ENUM_V0 ? 4
      : which == SC_SPEC_ENTRY_UDT_ERROR_ENUM_V0 ? 5
      : which == SC_SPEC_ENTRY_EVENT_V0 ? 6
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case SC_SPEC_ENTRY_FUNCTION_V0:
      _f(&SCSpecEntry::functionV0_, std::forward<_A>(_a)...);
      return true;
    case SC_SPEC_ENTRY_UDT_STRUCT_V0:
      _f(&SCSpecEntry::udtStructV0_, std::forward<_A>(_a)...);
      return true;
    case SC_SPEC_ENTRY_UDT_UNION_V0:
      _f(&SCSpecEntry::udtUnionV0_, std::forward<_A>(_a)...);
      return true;
    case SC_SPEC_ENTRY_UDT_ENUM_V0:
      _f(&SCSpecEntry::udtEnumV0_, std::forward<_A>(_a)...);
      return true;
    case SC_SPEC_ENTRY_UDT_ERROR_ENUM_V0:
      _f(&SCSpecEntry::udtErrorEnumV0_, std::forward<_A>(_a)...);
      return true;
    case SC_SPEC_ENTRY_EVENT_V0:
      _f(&SCSpecEntry::eventV0_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return kind_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of kind in SCSpecEntry");
    if (fnum != _xdr_field_number(kind_)) {
      this->~SCSpecEntry();
      kind_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, kind_, *this);
    }
    else
      kind_ = which;
  }
  explicit SCSpecEntry(SCSpecEntryKind which = SCSpecEntryKind{}) : kind_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, kind_, *this);
  }
  SCSpecEntry(const SCSpecEntry &source) : kind_(source.kind_) {
    _xdr_with_mem_ptr(xdr::field_constructor, kind_, *this, source);
  }
  SCSpecEntry(SCSpecEntry &&source) : kind_(source.kind_) {
    _xdr_with_mem_ptr(xdr::field_constructor, kind_, *this,
                      std::move(source));
  }
  ~SCSpecEntry() { _xdr_with_mem_ptr(xdr::field_destructor, kind_, *this); }
  SCSpecEntry &operator=(const SCSpecEntry &source) {
    if (_xdr_field_number(kind_)
        == _xdr_field_number(source.kind_))
      _xdr_with_mem_ptr(xdr::field_assigner, kind_, *this, source);
    else {
      this->~SCSpecEntry();
      kind_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.kind_, *this, source);
    }
    kind_ = source.kind_;
    return *this;
  }
  SCSpecEntry &operator=(SCSpecEntry &&source) {
    if (_xdr_field_number(kind_)
         == _xdr_field_number(source.kind_))
      _xdr_with_mem_ptr(xdr::field_assigner, kind_, *this,
                        std::move(source));
    else {
      this->~SCSpecEntry();
      kind_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.kind_, *this,
                        std::move(source));
    }
    kind_ = source.kind_;
    return *this;
  }

  SCSpecEntryKind kind() const { return SCSpecEntryKind(kind_); }
  SCSpecEntry &kind(SCSpecEntryKind _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  SCSpecFunctionV0 &functionV0() {
    if (_xdr_field_number(kind_) == 1)
      return functionV0_;
    throw xdr::xdr_wrong_union("SCSpecEntry: functionV0 accessed when not selected");
  }
  const SCSpecFunctionV0 &functionV0() const {
    if (_xdr_field_number(kind_) == 1)
      return functionV0_;
    throw xdr::xdr_wrong_union("SCSpecEntry: functionV0 accessed when not selected");
  }
  SCSpecUDTStructV0 &udtStructV0() {
    if (_xdr_field_number(kind_) == 2)
      return udtStructV0_;
    throw xdr::xdr_wrong_union("SCSpecEntry: udtStructV0 accessed when not selected");
  }
  const SCSpecUDTStructV0 &udtStructV0() const {
    if (_xdr_field_number(kind_) == 2)
      return udtStructV0_;
    throw xdr::xdr_wrong_union("SCSpecEntry: udtStructV0 accessed when not selected");
  }
  SCSpecUDTUnionV0 &udtUnionV0() {
    if (_xdr_field_number(kind_) == 3)
      return udtUnionV0_;
    throw xdr::xdr_wrong_union("SCSpecEntry: udtUnionV0 accessed when not selected");
  }
  const SCSpecUDTUnionV0 &udtUnionV0() const {
    if (_xdr_field_number(kind_) == 3)
      return udtUnionV0_;
    throw xdr::xdr_wrong_union("SCSpecEntry: udtUnionV0 accessed when not selected");
  }
  SCSpecUDTEnumV0 &udtEnumV0() {
    if (_xdr_field_number(kind_) == 4)
      return udtEnumV0_;
    throw xdr::xdr_wrong_union("SCSpecEntry: udtEnumV0 accessed when not selected");
  }
  const SCSpecUDTEnumV0 &udtEnumV0() const {
    if (_xdr_field_number(kind_) == 4)
      return udtEnumV0_;
    throw xdr::xdr_wrong_union("SCSpecEntry: udtEnumV0 accessed when not selected");
  }
  SCSpecUDTErrorEnumV0 &udtErrorEnumV0() {
    if (_xdr_field_number(kind_) == 5)
      return udtErrorEnumV0_;
    throw xdr::xdr_wrong_union("SCSpecEntry: udtErrorEnumV0 accessed when not selected");
  }
  const SCSpecUDTErrorEnumV0 &udtErrorEnumV0() const {
    if (_xdr_field_number(kind_) == 5)
      return udtErrorEnumV0_;
    throw xdr::xdr_wrong_union("SCSpecEntry: udtErrorEnumV0 accessed when not selected");
  }
  SCSpecEventV0 &eventV0() {
    if (_xdr_field_number(kind_) == 6)
      return eventV0_;
    throw xdr::xdr_wrong_union("SCSpecEntry: eventV0 accessed when not selected");
  }
  const SCSpecEventV0 &eventV0() const {
    if (_xdr_field_number(kind_) == 6)
      return eventV0_;
    throw xdr::xdr_wrong_union("SCSpecEntry: eventV0 accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCSpecEntry> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::SCSpecEntry;
  using case_type = ::stellar::SCSpecEntry::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().kind());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "functionV0";
    case 2:
      return "udtStructV0";
    case 3:
      return "udtUnionV0";
    case 4:
      return "udtEnumV0";
    case 5:
      return "udtErrorEnumV0";
    case 6:
      return "eventV0";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::SCSpecEntry &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of kind in SCSpecEntry");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SCSpecEntry &obj) {
    xdr::archive(ar, obj.kind(), "kind");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.kind(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of kind in SCSpecEntry");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SCSpecEntry &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "kind");
    obj.kind(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.kind(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

}

#endif // !__XDR_STELLAR_CONTRACT_SPEC_H_INCLUDED__
