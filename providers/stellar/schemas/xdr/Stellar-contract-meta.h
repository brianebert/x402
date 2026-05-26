// -*- C++ -*-
// Automatically generated from Stellar-contract-meta.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_CONTRACT_META_H_INCLUDED__
#define __XDR_STELLAR_CONTRACT_META_H_INCLUDED__ 1

#include <xdrpp/types.h>

 #include "xdr/Stellar-types.h"

namespace stellar {

struct SCMetaV0 {
  xdr::xstring<> key{};
  xdr::xstring<> val{};

  SCMetaV0() = default;
  template<typename _key_T,
           typename _val_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::xstring<>, _key_T>::value
                          && std::is_constructible<xdr::xstring<>, _val_T>::value
                         >::type>
  explicit SCMetaV0(_key_T &&_key,
                    _val_T &&_val)
    : key(std::forward<_key_T>(_key)),
      val(std::forward<_val_T>(_val)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCMetaV0>
  : xdr_struct_base<field_ptr<::stellar::SCMetaV0,
                              decltype(::stellar::SCMetaV0::key),
                              &::stellar::SCMetaV0::key>,
                    field_ptr<::stellar::SCMetaV0,
                              decltype(::stellar::SCMetaV0::val),
                              &::stellar::SCMetaV0::val>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SCMetaV0 &obj) {
    archive(ar, obj.key, "key");
    archive(ar, obj.val, "val");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SCMetaV0 &obj) {
    archive(ar, obj.key, "key");
    archive(ar, obj.val, "val");
    xdr::validate(obj);
  }
};
} namespace stellar {

enum SCMetaKind : std::int32_t {
  SC_META_V0 = 0,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCMetaKind>
  : xdr_integral_base<::stellar::SCMetaKind, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::SCMetaKind val) {
    switch (val) {
    case ::stellar::SC_META_V0:
      return "SC_META_V0";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::SC_META_V0
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct SCMetaEntry {
  using _xdr_case_type = xdr::xdr_traits<SCMetaKind>::case_type;
private:
  _xdr_case_type kind_;
  union {
    SCMetaV0 v0_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<SCMetaKind> &_xdr_case_values() {
    static const std::vector<SCMetaKind> _xdr_disc_vec {
      SC_META_V0
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == SC_META_V0 ? 1
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case SC_META_V0:
      _f(&SCMetaEntry::v0_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return kind_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of kind in SCMetaEntry");
    if (fnum != _xdr_field_number(kind_)) {
      this->~SCMetaEntry();
      kind_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, kind_, *this);
    }
    else
      kind_ = which;
  }
  explicit SCMetaEntry(SCMetaKind which = SCMetaKind{}) : kind_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, kind_, *this);
  }
  SCMetaEntry(const SCMetaEntry &source) : kind_(source.kind_) {
    _xdr_with_mem_ptr(xdr::field_constructor, kind_, *this, source);
  }
  SCMetaEntry(SCMetaEntry &&source) : kind_(source.kind_) {
    _xdr_with_mem_ptr(xdr::field_constructor, kind_, *this,
                      std::move(source));
  }
  ~SCMetaEntry() { _xdr_with_mem_ptr(xdr::field_destructor, kind_, *this); }
  SCMetaEntry &operator=(const SCMetaEntry &source) {
    if (_xdr_field_number(kind_)
        == _xdr_field_number(source.kind_))
      _xdr_with_mem_ptr(xdr::field_assigner, kind_, *this, source);
    else {
      this->~SCMetaEntry();
      kind_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.kind_, *this, source);
    }
    kind_ = source.kind_;
    return *this;
  }
  SCMetaEntry &operator=(SCMetaEntry &&source) {
    if (_xdr_field_number(kind_)
         == _xdr_field_number(source.kind_))
      _xdr_with_mem_ptr(xdr::field_assigner, kind_, *this,
                        std::move(source));
    else {
      this->~SCMetaEntry();
      kind_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.kind_, *this,
                        std::move(source));
    }
    kind_ = source.kind_;
    return *this;
  }

  SCMetaKind kind() const { return SCMetaKind(kind_); }
  SCMetaEntry &kind(SCMetaKind _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  SCMetaV0 &v0() {
    if (_xdr_field_number(kind_) == 1)
      return v0_;
    throw xdr::xdr_wrong_union("SCMetaEntry: v0 accessed when not selected");
  }
  const SCMetaV0 &v0() const {
    if (_xdr_field_number(kind_) == 1)
      return v0_;
    throw xdr::xdr_wrong_union("SCMetaEntry: v0 accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCMetaEntry> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::SCMetaEntry;
  using case_type = ::stellar::SCMetaEntry::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().kind());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "v0";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::SCMetaEntry &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of kind in SCMetaEntry");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SCMetaEntry &obj) {
    xdr::archive(ar, obj.kind(), "kind");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.kind(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of kind in SCMetaEntry");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SCMetaEntry &obj) {
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

#endif // !__XDR_STELLAR_CONTRACT_META_H_INCLUDED__
