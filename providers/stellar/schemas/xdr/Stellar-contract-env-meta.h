// -*- C++ -*-
// Automatically generated from Stellar-contract-env-meta.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_CONTRACT_ENV_META_H_INCLUDED__
#define __XDR_STELLAR_CONTRACT_ENV_META_H_INCLUDED__ 1

#include <xdrpp/types.h>

 #include "xdr/Stellar-types.h"

namespace stellar {

enum SCEnvMetaKind : std::int32_t {
  SC_ENV_META_KIND_INTERFACE_VERSION = 0,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCEnvMetaKind>
  : xdr_integral_base<::stellar::SCEnvMetaKind, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::SCEnvMetaKind val) {
    switch (val) {
    case ::stellar::SC_ENV_META_KIND_INTERFACE_VERSION:
      return "SC_ENV_META_KIND_INTERFACE_VERSION";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::SC_ENV_META_KIND_INTERFACE_VERSION
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct SCEnvMetaEntry {
  struct _interfaceVersion_t {
    uint32 protocol{};
    uint32 preRelease{};

    _interfaceVersion_t() = default;
    template<typename _protocol_T,
             typename _preRelease_T,
             typename = typename
             std::enable_if<std::is_constructible<uint32, _protocol_T>::value
                            && std::is_constructible<uint32, _preRelease_T>::value
                           >::type>
    explicit _interfaceVersion_t(_protocol_T &&_protocol,
                                 _preRelease_T &&_preRelease)
      : protocol(std::forward<_protocol_T>(_protocol)),
        preRelease(std::forward<_preRelease_T>(_preRelease)) {}
  };

  using _xdr_case_type = xdr::xdr_traits<SCEnvMetaKind>::case_type;
private:
  _xdr_case_type kind_;
  union {
    _interfaceVersion_t interfaceVersion_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<SCEnvMetaKind> &_xdr_case_values() {
    static const std::vector<SCEnvMetaKind> _xdr_disc_vec {
      SC_ENV_META_KIND_INTERFACE_VERSION
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == SC_ENV_META_KIND_INTERFACE_VERSION ? 1
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case SC_ENV_META_KIND_INTERFACE_VERSION:
      _f(&SCEnvMetaEntry::interfaceVersion_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return kind_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of kind in SCEnvMetaEntry");
    if (fnum != _xdr_field_number(kind_)) {
      this->~SCEnvMetaEntry();
      kind_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, kind_, *this);
    }
    else
      kind_ = which;
  }
  explicit SCEnvMetaEntry(SCEnvMetaKind which = SCEnvMetaKind{}) : kind_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, kind_, *this);
  }
  SCEnvMetaEntry(const SCEnvMetaEntry &source) : kind_(source.kind_) {
    _xdr_with_mem_ptr(xdr::field_constructor, kind_, *this, source);
  }
  SCEnvMetaEntry(SCEnvMetaEntry &&source) : kind_(source.kind_) {
    _xdr_with_mem_ptr(xdr::field_constructor, kind_, *this,
                      std::move(source));
  }
  ~SCEnvMetaEntry() { _xdr_with_mem_ptr(xdr::field_destructor, kind_, *this); }
  SCEnvMetaEntry &operator=(const SCEnvMetaEntry &source) {
    if (_xdr_field_number(kind_)
        == _xdr_field_number(source.kind_))
      _xdr_with_mem_ptr(xdr::field_assigner, kind_, *this, source);
    else {
      this->~SCEnvMetaEntry();
      kind_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.kind_, *this, source);
    }
    kind_ = source.kind_;
    return *this;
  }
  SCEnvMetaEntry &operator=(SCEnvMetaEntry &&source) {
    if (_xdr_field_number(kind_)
         == _xdr_field_number(source.kind_))
      _xdr_with_mem_ptr(xdr::field_assigner, kind_, *this,
                        std::move(source));
    else {
      this->~SCEnvMetaEntry();
      kind_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.kind_, *this,
                        std::move(source));
    }
    kind_ = source.kind_;
    return *this;
  }

  SCEnvMetaKind kind() const { return SCEnvMetaKind(kind_); }
  SCEnvMetaEntry &kind(SCEnvMetaKind _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  _interfaceVersion_t &interfaceVersion() {
    if (_xdr_field_number(kind_) == 1)
      return interfaceVersion_;
    throw xdr::xdr_wrong_union("SCEnvMetaEntry: interfaceVersion accessed when not selected");
  }
  const _interfaceVersion_t &interfaceVersion() const {
    if (_xdr_field_number(kind_) == 1)
      return interfaceVersion_;
    throw xdr::xdr_wrong_union("SCEnvMetaEntry: interfaceVersion accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCEnvMetaEntry::_interfaceVersion_t>
  : xdr_struct_base<field_ptr<::stellar::SCEnvMetaEntry::_interfaceVersion_t,
                              decltype(::stellar::SCEnvMetaEntry::_interfaceVersion_t::protocol),
                              &::stellar::SCEnvMetaEntry::_interfaceVersion_t::protocol>,
                    field_ptr<::stellar::SCEnvMetaEntry::_interfaceVersion_t,
                              decltype(::stellar::SCEnvMetaEntry::_interfaceVersion_t::preRelease),
                              &::stellar::SCEnvMetaEntry::_interfaceVersion_t::preRelease>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SCEnvMetaEntry::_interfaceVersion_t &obj) {
    archive(ar, obj.protocol, "protocol");
    archive(ar, obj.preRelease, "preRelease");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SCEnvMetaEntry::_interfaceVersion_t &obj) {
    archive(ar, obj.protocol, "protocol");
    archive(ar, obj.preRelease, "preRelease");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::SCEnvMetaEntry> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::SCEnvMetaEntry;
  using case_type = ::stellar::SCEnvMetaEntry::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().kind());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "interfaceVersion";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::SCEnvMetaEntry &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of kind in SCEnvMetaEntry");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SCEnvMetaEntry &obj) {
    xdr::archive(ar, obj.kind(), "kind");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.kind(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of kind in SCEnvMetaEntry");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SCEnvMetaEntry &obj) {
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

#endif // !__XDR_STELLAR_CONTRACT_ENV_META_H_INCLUDED__
