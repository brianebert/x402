// -*- C++ -*-
// Automatically generated from Stellar-ledger.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_LEDGER_H_INCLUDED__
#define __XDR_STELLAR_LEDGER_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-SCP.h"
#include "xdr/Stellar-transaction.h"

namespace stellar {

using UpgradeType = xdr::opaque_vec<128>;

enum StellarValueType : std::int32_t {
  STELLAR_VALUE_BASIC = 0,
  STELLAR_VALUE_SIGNED = 1,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::StellarValueType>
  : xdr_integral_base<::stellar::StellarValueType, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::StellarValueType val) {
    switch (val) {
    case ::stellar::STELLAR_VALUE_BASIC:
      return "STELLAR_VALUE_BASIC";
    case ::stellar::STELLAR_VALUE_SIGNED:
      return "STELLAR_VALUE_SIGNED";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::STELLAR_VALUE_BASIC,
      ::stellar::STELLAR_VALUE_SIGNED
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct LedgerCloseValueSignature {
  NodeID nodeID{};
  Signature signature{};

  LedgerCloseValueSignature() = default;
  template<typename _nodeID_T,
           typename _signature_T,
           typename = typename
           std::enable_if<std::is_constructible<NodeID, _nodeID_T>::value
                          && std::is_constructible<Signature, _signature_T>::value
                         >::type>
  explicit LedgerCloseValueSignature(_nodeID_T &&_nodeID,
                                     _signature_T &&_signature)
    : nodeID(std::forward<_nodeID_T>(_nodeID)),
      signature(std::forward<_signature_T>(_signature)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::LedgerCloseValueSignature>
  : xdr_struct_base<field_ptr<::stellar::LedgerCloseValueSignature,
                              decltype(::stellar::LedgerCloseValueSignature::nodeID),
                              &::stellar::LedgerCloseValueSignature::nodeID>,
                    field_ptr<::stellar::LedgerCloseValueSignature,
                              decltype(::stellar::LedgerCloseValueSignature::signature),
                              &::stellar::LedgerCloseValueSignature::signature>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerCloseValueSignature &obj) {
    archive(ar, obj.nodeID, "nodeID");
    archive(ar, obj.signature, "signature");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerCloseValueSignature &obj) {
    archive(ar, obj.nodeID, "nodeID");
    archive(ar, obj.signature, "signature");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct StellarValue {
  struct _ext_t {
    using _xdr_case_type = xdr::xdr_traits<StellarValueType>::case_type;
  private:
    _xdr_case_type v_;
    union {
      LedgerCloseValueSignature lcValueSignature_;
    };

  public:
    static Constexpr const bool _xdr_has_default_case = false;
    static const std::vector<StellarValueType> &_xdr_case_values() {
      static const std::vector<StellarValueType> _xdr_disc_vec {
        STELLAR_VALUE_BASIC,
        STELLAR_VALUE_SIGNED
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == STELLAR_VALUE_BASIC ? 0
        : which == STELLAR_VALUE_SIGNED ? 1
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case STELLAR_VALUE_BASIC:
        return true;
      case STELLAR_VALUE_SIGNED:
        _f(&_ext_t::lcValueSignature_, std::forward<_A>(_a)...);
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
    explicit _ext_t(StellarValueType which = StellarValueType{}) : v_(which) {
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

    StellarValueType v() const { return StellarValueType(v_); }
    _ext_t &v(StellarValueType _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant(_xdr_d, _xdr_validate);
      return *this;
    }

    LedgerCloseValueSignature &lcValueSignature() {
      if (_xdr_field_number(v_) == 1)
        return lcValueSignature_;
      throw xdr::xdr_wrong_union("_ext_t: lcValueSignature accessed when not selected");
    }
    const LedgerCloseValueSignature &lcValueSignature() const {
      if (_xdr_field_number(v_) == 1)
        return lcValueSignature_;
      throw xdr::xdr_wrong_union("_ext_t: lcValueSignature accessed when not selected");
    }
  };

  Hash txSetHash{};
  TimePoint closeTime{};
  xdr::xvector<UpgradeType,6> upgrades{};
  _ext_t ext{};

  StellarValue() = default;
  template<typename _txSetHash_T,
           typename _closeTime_T,
           typename _upgrades_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<Hash, _txSetHash_T>::value
                          && std::is_constructible<TimePoint, _closeTime_T>::value
                          && std::is_constructible<xdr::xvector<UpgradeType,6>, _upgrades_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit StellarValue(_txSetHash_T &&_txSetHash,
                        _closeTime_T &&_closeTime,
                        _upgrades_T &&_upgrades,
                        _ext_T &&_ext)
    : txSetHash(std::forward<_txSetHash_T>(_txSetHash)),
      closeTime(std::forward<_closeTime_T>(_closeTime)),
      upgrades(std::forward<_upgrades_T>(_upgrades)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::StellarValue::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::StellarValue::_ext_t;
  using case_type = ::stellar::StellarValue::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "lcValueSignature";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::StellarValue::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::StellarValue::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::StellarValue::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.v(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::StellarValue>
  : xdr_struct_base<field_ptr<::stellar::StellarValue,
                              decltype(::stellar::StellarValue::txSetHash),
                              &::stellar::StellarValue::txSetHash>,
                    field_ptr<::stellar::StellarValue,
                              decltype(::stellar::StellarValue::closeTime),
                              &::stellar::StellarValue::closeTime>,
                    field_ptr<::stellar::StellarValue,
                              decltype(::stellar::StellarValue::upgrades),
                              &::stellar::StellarValue::upgrades>,
                    field_ptr<::stellar::StellarValue,
                              decltype(::stellar::StellarValue::ext),
                              &::stellar::StellarValue::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::StellarValue &obj) {
    archive(ar, obj.txSetHash, "txSetHash");
    archive(ar, obj.closeTime, "closeTime");
    archive(ar, obj.upgrades, "upgrades");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::StellarValue &obj) {
    archive(ar, obj.txSetHash, "txSetHash");
    archive(ar, obj.closeTime, "closeTime");
    archive(ar, obj.upgrades, "upgrades");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

Constexpr const std::uint32_t MASK_LEDGER_HEADER_FLAGS = 0x7;

enum LedgerHeaderFlags : std::int32_t {
  DISABLE_LIQUIDITY_POOL_TRADING_FLAG = 0x1,
  DISABLE_LIQUIDITY_POOL_DEPOSIT_FLAG = 0x2,
  DISABLE_LIQUIDITY_POOL_WITHDRAWAL_FLAG = 0x4,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::LedgerHeaderFlags>
  : xdr_integral_base<::stellar::LedgerHeaderFlags, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::LedgerHeaderFlags val) {
    switch (val) {
    case ::stellar::DISABLE_LIQUIDITY_POOL_TRADING_FLAG:
      return "DISABLE_LIQUIDITY_POOL_TRADING_FLAG";
    case ::stellar::DISABLE_LIQUIDITY_POOL_DEPOSIT_FLAG:
      return "DISABLE_LIQUIDITY_POOL_DEPOSIT_FLAG";
    case ::stellar::DISABLE_LIQUIDITY_POOL_WITHDRAWAL_FLAG:
      return "DISABLE_LIQUIDITY_POOL_WITHDRAWAL_FLAG";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::DISABLE_LIQUIDITY_POOL_TRADING_FLAG,
      ::stellar::DISABLE_LIQUIDITY_POOL_DEPOSIT_FLAG,
      ::stellar::DISABLE_LIQUIDITY_POOL_WITHDRAWAL_FLAG
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct LedgerHeaderExtensionV1 {
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

  uint32 flags{};
  _ext_t ext{};

  LedgerHeaderExtensionV1() = default;
  template<typename _flags_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint32, _flags_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit LedgerHeaderExtensionV1(_flags_T &&_flags,
                                   _ext_T &&_ext)
    : flags(std::forward<_flags_T>(_flags)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::LedgerHeaderExtensionV1::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::LedgerHeaderExtensionV1::_ext_t;
  using case_type = ::stellar::LedgerHeaderExtensionV1::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::LedgerHeaderExtensionV1::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerHeaderExtensionV1::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerHeaderExtensionV1::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.v(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerHeaderExtensionV1>
  : xdr_struct_base<field_ptr<::stellar::LedgerHeaderExtensionV1,
                              decltype(::stellar::LedgerHeaderExtensionV1::flags),
                              &::stellar::LedgerHeaderExtensionV1::flags>,
                    field_ptr<::stellar::LedgerHeaderExtensionV1,
                              decltype(::stellar::LedgerHeaderExtensionV1::ext),
                              &::stellar::LedgerHeaderExtensionV1::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerHeaderExtensionV1 &obj) {
    archive(ar, obj.flags, "flags");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerHeaderExtensionV1 &obj) {
    archive(ar, obj.flags, "flags");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct LedgerHeader {
  struct _ext_t {
    using _xdr_case_type = xdr::xdr_traits<int>::case_type;
  private:
    _xdr_case_type v_;
    union {
      LedgerHeaderExtensionV1 v1_;
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
        _f(&_ext_t::v1_, std::forward<_A>(_a)...);
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

    LedgerHeaderExtensionV1 &v1() {
      if (_xdr_field_number(v_) == 1)
        return v1_;
      throw xdr::xdr_wrong_union("_ext_t: v1 accessed when not selected");
    }
    const LedgerHeaderExtensionV1 &v1() const {
      if (_xdr_field_number(v_) == 1)
        return v1_;
      throw xdr::xdr_wrong_union("_ext_t: v1 accessed when not selected");
    }
  };

  uint32 ledgerVersion{};
  Hash previousLedgerHash{};
  StellarValue scpValue{};
  Hash txSetResultHash{};
  Hash bucketListHash{};
  uint32 ledgerSeq{};
  int64 totalCoins{};
  int64 feePool{};
  uint32 inflationSeq{};
  uint64 idPool{};
  uint32 baseFee{};
  uint32 baseReserve{};
  uint32 maxTxSetSize{};
  xdr::xarray<Hash,4> skipList{};
  _ext_t ext{};

  LedgerHeader() = default;
  template<typename _ledgerVersion_T,
           typename _previousLedgerHash_T,
           typename _scpValue_T,
           typename _txSetResultHash_T,
           typename _bucketListHash_T,
           typename _ledgerSeq_T,
           typename _totalCoins_T,
           typename _feePool_T,
           typename _inflationSeq_T,
           typename _idPool_T,
           typename _baseFee_T,
           typename _baseReserve_T,
           typename _maxTxSetSize_T,
           typename _skipList_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint32, _ledgerVersion_T>::value
                          && std::is_constructible<Hash, _previousLedgerHash_T>::value
                          && std::is_constructible<StellarValue, _scpValue_T>::value
                          && std::is_constructible<Hash, _txSetResultHash_T>::value
                          && std::is_constructible<Hash, _bucketListHash_T>::value
                          && std::is_constructible<uint32, _ledgerSeq_T>::value
                          && std::is_constructible<int64, _totalCoins_T>::value
                          && std::is_constructible<int64, _feePool_T>::value
                          && std::is_constructible<uint32, _inflationSeq_T>::value
                          && std::is_constructible<uint64, _idPool_T>::value
                          && std::is_constructible<uint32, _baseFee_T>::value
                          && std::is_constructible<uint32, _baseReserve_T>::value
                          && std::is_constructible<uint32, _maxTxSetSize_T>::value
                          && std::is_constructible<xdr::xarray<Hash,4>, _skipList_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit LedgerHeader(_ledgerVersion_T &&_ledgerVersion,
                        _previousLedgerHash_T &&_previousLedgerHash,
                        _scpValue_T &&_scpValue,
                        _txSetResultHash_T &&_txSetResultHash,
                        _bucketListHash_T &&_bucketListHash,
                        _ledgerSeq_T &&_ledgerSeq,
                        _totalCoins_T &&_totalCoins,
                        _feePool_T &&_feePool,
                        _inflationSeq_T &&_inflationSeq,
                        _idPool_T &&_idPool,
                        _baseFee_T &&_baseFee,
                        _baseReserve_T &&_baseReserve,
                        _maxTxSetSize_T &&_maxTxSetSize,
                        _skipList_T &&_skipList,
                        _ext_T &&_ext)
    : ledgerVersion(std::forward<_ledgerVersion_T>(_ledgerVersion)),
      previousLedgerHash(std::forward<_previousLedgerHash_T>(_previousLedgerHash)),
      scpValue(std::forward<_scpValue_T>(_scpValue)),
      txSetResultHash(std::forward<_txSetResultHash_T>(_txSetResultHash)),
      bucketListHash(std::forward<_bucketListHash_T>(_bucketListHash)),
      ledgerSeq(std::forward<_ledgerSeq_T>(_ledgerSeq)),
      totalCoins(std::forward<_totalCoins_T>(_totalCoins)),
      feePool(std::forward<_feePool_T>(_feePool)),
      inflationSeq(std::forward<_inflationSeq_T>(_inflationSeq)),
      idPool(std::forward<_idPool_T>(_idPool)),
      baseFee(std::forward<_baseFee_T>(_baseFee)),
      baseReserve(std::forward<_baseReserve_T>(_baseReserve)),
      maxTxSetSize(std::forward<_maxTxSetSize_T>(_maxTxSetSize)),
      skipList(std::forward<_skipList_T>(_skipList)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::LedgerHeader::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::LedgerHeader::_ext_t;
  using case_type = ::stellar::LedgerHeader::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

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

  static std::size_t serial_size(const ::stellar::LedgerHeader::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerHeader::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerHeader::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.v(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerHeader>
  : xdr_struct_base<field_ptr<::stellar::LedgerHeader,
                              decltype(::stellar::LedgerHeader::ledgerVersion),
                              &::stellar::LedgerHeader::ledgerVersion>,
                    field_ptr<::stellar::LedgerHeader,
                              decltype(::stellar::LedgerHeader::previousLedgerHash),
                              &::stellar::LedgerHeader::previousLedgerHash>,
                    field_ptr<::stellar::LedgerHeader,
                              decltype(::stellar::LedgerHeader::scpValue),
                              &::stellar::LedgerHeader::scpValue>,
                    field_ptr<::stellar::LedgerHeader,
                              decltype(::stellar::LedgerHeader::txSetResultHash),
                              &::stellar::LedgerHeader::txSetResultHash>,
                    field_ptr<::stellar::LedgerHeader,
                              decltype(::stellar::LedgerHeader::bucketListHash),
                              &::stellar::LedgerHeader::bucketListHash>,
                    field_ptr<::stellar::LedgerHeader,
                              decltype(::stellar::LedgerHeader::ledgerSeq),
                              &::stellar::LedgerHeader::ledgerSeq>,
                    field_ptr<::stellar::LedgerHeader,
                              decltype(::stellar::LedgerHeader::totalCoins),
                              &::stellar::LedgerHeader::totalCoins>,
                    field_ptr<::stellar::LedgerHeader,
                              decltype(::stellar::LedgerHeader::feePool),
                              &::stellar::LedgerHeader::feePool>,
                    field_ptr<::stellar::LedgerHeader,
                              decltype(::stellar::LedgerHeader::inflationSeq),
                              &::stellar::LedgerHeader::inflationSeq>,
                    field_ptr<::stellar::LedgerHeader,
                              decltype(::stellar::LedgerHeader::idPool),
                              &::stellar::LedgerHeader::idPool>,
                    field_ptr<::stellar::LedgerHeader,
                              decltype(::stellar::LedgerHeader::baseFee),
                              &::stellar::LedgerHeader::baseFee>,
                    field_ptr<::stellar::LedgerHeader,
                              decltype(::stellar::LedgerHeader::baseReserve),
                              &::stellar::LedgerHeader::baseReserve>,
                    field_ptr<::stellar::LedgerHeader,
                              decltype(::stellar::LedgerHeader::maxTxSetSize),
                              &::stellar::LedgerHeader::maxTxSetSize>,
                    field_ptr<::stellar::LedgerHeader,
                              decltype(::stellar::LedgerHeader::skipList),
                              &::stellar::LedgerHeader::skipList>,
                    field_ptr<::stellar::LedgerHeader,
                              decltype(::stellar::LedgerHeader::ext),
                              &::stellar::LedgerHeader::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerHeader &obj) {
    archive(ar, obj.ledgerVersion, "ledgerVersion");
    archive(ar, obj.previousLedgerHash, "previousLedgerHash");
    archive(ar, obj.scpValue, "scpValue");
    archive(ar, obj.txSetResultHash, "txSetResultHash");
    archive(ar, obj.bucketListHash, "bucketListHash");
    archive(ar, obj.ledgerSeq, "ledgerSeq");
    archive(ar, obj.totalCoins, "totalCoins");
    archive(ar, obj.feePool, "feePool");
    archive(ar, obj.inflationSeq, "inflationSeq");
    archive(ar, obj.idPool, "idPool");
    archive(ar, obj.baseFee, "baseFee");
    archive(ar, obj.baseReserve, "baseReserve");
    archive(ar, obj.maxTxSetSize, "maxTxSetSize");
    archive(ar, obj.skipList, "skipList");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerHeader &obj) {
    archive(ar, obj.ledgerVersion, "ledgerVersion");
    archive(ar, obj.previousLedgerHash, "previousLedgerHash");
    archive(ar, obj.scpValue, "scpValue");
    archive(ar, obj.txSetResultHash, "txSetResultHash");
    archive(ar, obj.bucketListHash, "bucketListHash");
    archive(ar, obj.ledgerSeq, "ledgerSeq");
    archive(ar, obj.totalCoins, "totalCoins");
    archive(ar, obj.feePool, "feePool");
    archive(ar, obj.inflationSeq, "inflationSeq");
    archive(ar, obj.idPool, "idPool");
    archive(ar, obj.baseFee, "baseFee");
    archive(ar, obj.baseReserve, "baseReserve");
    archive(ar, obj.maxTxSetSize, "maxTxSetSize");
    archive(ar, obj.skipList, "skipList");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

enum LedgerUpgradeType : std::int32_t {
  LEDGER_UPGRADE_VERSION = 1,
  LEDGER_UPGRADE_BASE_FEE = 2,
  LEDGER_UPGRADE_MAX_TX_SET_SIZE = 3,
  LEDGER_UPGRADE_BASE_RESERVE = 4,
  LEDGER_UPGRADE_FLAGS = 5,
  LEDGER_UPGRADE_CONFIG = 6,
  LEDGER_UPGRADE_MAX_SOROBAN_TX_SET_SIZE = 7,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::LedgerUpgradeType>
  : xdr_integral_base<::stellar::LedgerUpgradeType, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::LedgerUpgradeType val) {
    switch (val) {
    case ::stellar::LEDGER_UPGRADE_VERSION:
      return "LEDGER_UPGRADE_VERSION";
    case ::stellar::LEDGER_UPGRADE_BASE_FEE:
      return "LEDGER_UPGRADE_BASE_FEE";
    case ::stellar::LEDGER_UPGRADE_MAX_TX_SET_SIZE:
      return "LEDGER_UPGRADE_MAX_TX_SET_SIZE";
    case ::stellar::LEDGER_UPGRADE_BASE_RESERVE:
      return "LEDGER_UPGRADE_BASE_RESERVE";
    case ::stellar::LEDGER_UPGRADE_FLAGS:
      return "LEDGER_UPGRADE_FLAGS";
    case ::stellar::LEDGER_UPGRADE_CONFIG:
      return "LEDGER_UPGRADE_CONFIG";
    case ::stellar::LEDGER_UPGRADE_MAX_SOROBAN_TX_SET_SIZE:
      return "LEDGER_UPGRADE_MAX_SOROBAN_TX_SET_SIZE";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::LEDGER_UPGRADE_VERSION,
      ::stellar::LEDGER_UPGRADE_BASE_FEE,
      ::stellar::LEDGER_UPGRADE_MAX_TX_SET_SIZE,
      ::stellar::LEDGER_UPGRADE_BASE_RESERVE,
      ::stellar::LEDGER_UPGRADE_FLAGS,
      ::stellar::LEDGER_UPGRADE_CONFIG,
      ::stellar::LEDGER_UPGRADE_MAX_SOROBAN_TX_SET_SIZE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct ConfigUpgradeSetKey {
  ContractID contractID{};
  Hash contentHash{};

  ConfigUpgradeSetKey() = default;
  template<typename _contractID_T,
           typename _contentHash_T,
           typename = typename
           std::enable_if<std::is_constructible<ContractID, _contractID_T>::value
                          && std::is_constructible<Hash, _contentHash_T>::value
                         >::type>
  explicit ConfigUpgradeSetKey(_contractID_T &&_contractID,
                               _contentHash_T &&_contentHash)
    : contractID(std::forward<_contractID_T>(_contractID)),
      contentHash(std::forward<_contentHash_T>(_contentHash)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ConfigUpgradeSetKey>
  : xdr_struct_base<field_ptr<::stellar::ConfigUpgradeSetKey,
                              decltype(::stellar::ConfigUpgradeSetKey::contractID),
                              &::stellar::ConfigUpgradeSetKey::contractID>,
                    field_ptr<::stellar::ConfigUpgradeSetKey,
                              decltype(::stellar::ConfigUpgradeSetKey::contentHash),
                              &::stellar::ConfigUpgradeSetKey::contentHash>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ConfigUpgradeSetKey &obj) {
    archive(ar, obj.contractID, "contractID");
    archive(ar, obj.contentHash, "contentHash");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ConfigUpgradeSetKey &obj) {
    archive(ar, obj.contractID, "contractID");
    archive(ar, obj.contentHash, "contentHash");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct LedgerUpgrade {
  using _xdr_case_type = xdr::xdr_traits<LedgerUpgradeType>::case_type;
private:
  _xdr_case_type type_;
  union {
    uint32 newLedgerVersion_;
    uint32 newBaseFee_;
    uint32 newMaxTxSetSize_;
    uint32 newBaseReserve_;
    uint32 newFlags_;
    ConfigUpgradeSetKey newConfig_;
    uint32 newMaxSorobanTxSetSize_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<LedgerUpgradeType> &_xdr_case_values() {
    static const std::vector<LedgerUpgradeType> _xdr_disc_vec {
      LEDGER_UPGRADE_VERSION,
      LEDGER_UPGRADE_BASE_FEE,
      LEDGER_UPGRADE_MAX_TX_SET_SIZE,
      LEDGER_UPGRADE_BASE_RESERVE,
      LEDGER_UPGRADE_FLAGS,
      LEDGER_UPGRADE_CONFIG,
      LEDGER_UPGRADE_MAX_SOROBAN_TX_SET_SIZE
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == LEDGER_UPGRADE_VERSION ? 1
      : which == LEDGER_UPGRADE_BASE_FEE ? 2
      : which == LEDGER_UPGRADE_MAX_TX_SET_SIZE ? 3
      : which == LEDGER_UPGRADE_BASE_RESERVE ? 4
      : which == LEDGER_UPGRADE_FLAGS ? 5
      : which == LEDGER_UPGRADE_CONFIG ? 6
      : which == LEDGER_UPGRADE_MAX_SOROBAN_TX_SET_SIZE ? 7
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case LEDGER_UPGRADE_VERSION:
      _f(&LedgerUpgrade::newLedgerVersion_, std::forward<_A>(_a)...);
      return true;
    case LEDGER_UPGRADE_BASE_FEE:
      _f(&LedgerUpgrade::newBaseFee_, std::forward<_A>(_a)...);
      return true;
    case LEDGER_UPGRADE_MAX_TX_SET_SIZE:
      _f(&LedgerUpgrade::newMaxTxSetSize_, std::forward<_A>(_a)...);
      return true;
    case LEDGER_UPGRADE_BASE_RESERVE:
      _f(&LedgerUpgrade::newBaseReserve_, std::forward<_A>(_a)...);
      return true;
    case LEDGER_UPGRADE_FLAGS:
      _f(&LedgerUpgrade::newFlags_, std::forward<_A>(_a)...);
      return true;
    case LEDGER_UPGRADE_CONFIG:
      _f(&LedgerUpgrade::newConfig_, std::forward<_A>(_a)...);
      return true;
    case LEDGER_UPGRADE_MAX_SOROBAN_TX_SET_SIZE:
      _f(&LedgerUpgrade::newMaxSorobanTxSetSize_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return type_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of type in LedgerUpgrade");
    if (fnum != _xdr_field_number(type_)) {
      this->~LedgerUpgrade();
      type_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
    }
    else
      type_ = which;
  }
  explicit LedgerUpgrade(LedgerUpgradeType which = LedgerUpgradeType{}) : type_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
  }
  LedgerUpgrade(const LedgerUpgrade &source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this, source);
  }
  LedgerUpgrade(LedgerUpgrade &&source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this,
                      std::move(source));
  }
  ~LedgerUpgrade() { _xdr_with_mem_ptr(xdr::field_destructor, type_, *this); }
  LedgerUpgrade &operator=(const LedgerUpgrade &source) {
    if (_xdr_field_number(type_)
        == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this, source);
    else {
      this->~LedgerUpgrade();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this, source);
    }
    type_ = source.type_;
    return *this;
  }
  LedgerUpgrade &operator=(LedgerUpgrade &&source) {
    if (_xdr_field_number(type_)
         == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this,
                        std::move(source));
    else {
      this->~LedgerUpgrade();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this,
                        std::move(source));
    }
    type_ = source.type_;
    return *this;
  }

  LedgerUpgradeType type() const { return LedgerUpgradeType(type_); }
  LedgerUpgrade &type(LedgerUpgradeType _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  uint32 &newLedgerVersion() {
    if (_xdr_field_number(type_) == 1)
      return newLedgerVersion_;
    throw xdr::xdr_wrong_union("LedgerUpgrade: newLedgerVersion accessed when not selected");
  }
  const uint32 &newLedgerVersion() const {
    if (_xdr_field_number(type_) == 1)
      return newLedgerVersion_;
    throw xdr::xdr_wrong_union("LedgerUpgrade: newLedgerVersion accessed when not selected");
  }
  uint32 &newBaseFee() {
    if (_xdr_field_number(type_) == 2)
      return newBaseFee_;
    throw xdr::xdr_wrong_union("LedgerUpgrade: newBaseFee accessed when not selected");
  }
  const uint32 &newBaseFee() const {
    if (_xdr_field_number(type_) == 2)
      return newBaseFee_;
    throw xdr::xdr_wrong_union("LedgerUpgrade: newBaseFee accessed when not selected");
  }
  uint32 &newMaxTxSetSize() {
    if (_xdr_field_number(type_) == 3)
      return newMaxTxSetSize_;
    throw xdr::xdr_wrong_union("LedgerUpgrade: newMaxTxSetSize accessed when not selected");
  }
  const uint32 &newMaxTxSetSize() const {
    if (_xdr_field_number(type_) == 3)
      return newMaxTxSetSize_;
    throw xdr::xdr_wrong_union("LedgerUpgrade: newMaxTxSetSize accessed when not selected");
  }
  uint32 &newBaseReserve() {
    if (_xdr_field_number(type_) == 4)
      return newBaseReserve_;
    throw xdr::xdr_wrong_union("LedgerUpgrade: newBaseReserve accessed when not selected");
  }
  const uint32 &newBaseReserve() const {
    if (_xdr_field_number(type_) == 4)
      return newBaseReserve_;
    throw xdr::xdr_wrong_union("LedgerUpgrade: newBaseReserve accessed when not selected");
  }
  uint32 &newFlags() {
    if (_xdr_field_number(type_) == 5)
      return newFlags_;
    throw xdr::xdr_wrong_union("LedgerUpgrade: newFlags accessed when not selected");
  }
  const uint32 &newFlags() const {
    if (_xdr_field_number(type_) == 5)
      return newFlags_;
    throw xdr::xdr_wrong_union("LedgerUpgrade: newFlags accessed when not selected");
  }
  ConfigUpgradeSetKey &newConfig() {
    if (_xdr_field_number(type_) == 6)
      return newConfig_;
    throw xdr::xdr_wrong_union("LedgerUpgrade: newConfig accessed when not selected");
  }
  const ConfigUpgradeSetKey &newConfig() const {
    if (_xdr_field_number(type_) == 6)
      return newConfig_;
    throw xdr::xdr_wrong_union("LedgerUpgrade: newConfig accessed when not selected");
  }
  uint32 &newMaxSorobanTxSetSize() {
    if (_xdr_field_number(type_) == 7)
      return newMaxSorobanTxSetSize_;
    throw xdr::xdr_wrong_union("LedgerUpgrade: newMaxSorobanTxSetSize accessed when not selected");
  }
  const uint32 &newMaxSorobanTxSetSize() const {
    if (_xdr_field_number(type_) == 7)
      return newMaxSorobanTxSetSize_;
    throw xdr::xdr_wrong_union("LedgerUpgrade: newMaxSorobanTxSetSize accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::LedgerUpgrade> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::LedgerUpgrade;
  using case_type = ::stellar::LedgerUpgrade::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().type());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "newLedgerVersion";
    case 2:
      return "newBaseFee";
    case 3:
      return "newMaxTxSetSize";
    case 4:
      return "newBaseReserve";
    case 5:
      return "newFlags";
    case 6:
      return "newConfig";
    case 7:
      return "newMaxSorobanTxSetSize";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::LedgerUpgrade &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of type in LedgerUpgrade");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerUpgrade &obj) {
    xdr::archive(ar, obj.type(), "type");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of type in LedgerUpgrade");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerUpgrade &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "type");
    obj.type(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ConfigUpgradeSet {
  xdr::xvector<ConfigSettingEntry> updatedEntry{};

  ConfigUpgradeSet() = default;
  template<typename _updatedEntry_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::xvector<ConfigSettingEntry>, _updatedEntry_T>::value
                         >::type>
  explicit ConfigUpgradeSet(_updatedEntry_T &&_updatedEntry)
    : updatedEntry(std::forward<_updatedEntry_T>(_updatedEntry)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ConfigUpgradeSet>
  : xdr_struct_base<field_ptr<::stellar::ConfigUpgradeSet,
                              decltype(::stellar::ConfigUpgradeSet::updatedEntry),
                              &::stellar::ConfigUpgradeSet::updatedEntry>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ConfigUpgradeSet &obj) {
    archive(ar, obj.updatedEntry, "updatedEntry");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ConfigUpgradeSet &obj) {
    archive(ar, obj.updatedEntry, "updatedEntry");
    xdr::validate(obj);
  }
};
} namespace stellar {

enum TxSetComponentType : std::int32_t {
  TXSET_COMP_TXS_MAYBE_DISCOUNTED_FEE = 0,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::TxSetComponentType>
  : xdr_integral_base<::stellar::TxSetComponentType, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::TxSetComponentType val) {
    switch (val) {
    case ::stellar::TXSET_COMP_TXS_MAYBE_DISCOUNTED_FEE:
      return "TXSET_COMP_TXS_MAYBE_DISCOUNTED_FEE";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::TXSET_COMP_TXS_MAYBE_DISCOUNTED_FEE
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

using DependentTxCluster = xdr::xvector<TransactionEnvelope>;
using ParallelTxExecutionStage = xdr::xvector<DependentTxCluster>;

struct ParallelTxsComponent {
  xdr::pointer<int64> baseFee{};
  xdr::xvector<ParallelTxExecutionStage> executionStages{};

  ParallelTxsComponent() = default;
  template<typename _baseFee_T,
           typename _executionStages_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::pointer<int64>, _baseFee_T>::value
                          && std::is_constructible<xdr::xvector<ParallelTxExecutionStage>, _executionStages_T>::value
                         >::type>
  explicit ParallelTxsComponent(_baseFee_T &&_baseFee,
                                _executionStages_T &&_executionStages)
    : baseFee(std::forward<_baseFee_T>(_baseFee)),
      executionStages(std::forward<_executionStages_T>(_executionStages)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ParallelTxsComponent>
  : xdr_struct_base<field_ptr<::stellar::ParallelTxsComponent,
                              decltype(::stellar::ParallelTxsComponent::baseFee),
                              &::stellar::ParallelTxsComponent::baseFee>,
                    field_ptr<::stellar::ParallelTxsComponent,
                              decltype(::stellar::ParallelTxsComponent::executionStages),
                              &::stellar::ParallelTxsComponent::executionStages>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ParallelTxsComponent &obj) {
    archive(ar, obj.baseFee, "baseFee");
    archive(ar, obj.executionStages, "executionStages");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ParallelTxsComponent &obj) {
    archive(ar, obj.baseFee, "baseFee");
    archive(ar, obj.executionStages, "executionStages");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct TxSetComponent {
  struct _txsMaybeDiscountedFee_t {
    xdr::pointer<int64> baseFee{};
    xdr::xvector<TransactionEnvelope> txs{};

    _txsMaybeDiscountedFee_t() = default;
    template<typename _baseFee_T,
             typename _txs_T,
             typename = typename
             std::enable_if<std::is_constructible<xdr::pointer<int64>, _baseFee_T>::value
                            && std::is_constructible<xdr::xvector<TransactionEnvelope>, _txs_T>::value
                           >::type>
    explicit _txsMaybeDiscountedFee_t(_baseFee_T &&_baseFee,
                                      _txs_T &&_txs)
      : baseFee(std::forward<_baseFee_T>(_baseFee)),
        txs(std::forward<_txs_T>(_txs)) {}
  };

  using _xdr_case_type = xdr::xdr_traits<TxSetComponentType>::case_type;
private:
  _xdr_case_type type_;
  union {
    _txsMaybeDiscountedFee_t txsMaybeDiscountedFee_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<TxSetComponentType> &_xdr_case_values() {
    static const std::vector<TxSetComponentType> _xdr_disc_vec {
      TXSET_COMP_TXS_MAYBE_DISCOUNTED_FEE
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == TXSET_COMP_TXS_MAYBE_DISCOUNTED_FEE ? 1
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case TXSET_COMP_TXS_MAYBE_DISCOUNTED_FEE:
      _f(&TxSetComponent::txsMaybeDiscountedFee_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return type_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of type in TxSetComponent");
    if (fnum != _xdr_field_number(type_)) {
      this->~TxSetComponent();
      type_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
    }
    else
      type_ = which;
  }
  explicit TxSetComponent(TxSetComponentType which = TxSetComponentType{}) : type_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
  }
  TxSetComponent(const TxSetComponent &source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this, source);
  }
  TxSetComponent(TxSetComponent &&source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this,
                      std::move(source));
  }
  ~TxSetComponent() { _xdr_with_mem_ptr(xdr::field_destructor, type_, *this); }
  TxSetComponent &operator=(const TxSetComponent &source) {
    if (_xdr_field_number(type_)
        == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this, source);
    else {
      this->~TxSetComponent();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this, source);
    }
    type_ = source.type_;
    return *this;
  }
  TxSetComponent &operator=(TxSetComponent &&source) {
    if (_xdr_field_number(type_)
         == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this,
                        std::move(source));
    else {
      this->~TxSetComponent();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this,
                        std::move(source));
    }
    type_ = source.type_;
    return *this;
  }

  TxSetComponentType type() const { return TxSetComponentType(type_); }
  TxSetComponent &type(TxSetComponentType _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  _txsMaybeDiscountedFee_t &txsMaybeDiscountedFee() {
    if (_xdr_field_number(type_) == 1)
      return txsMaybeDiscountedFee_;
    throw xdr::xdr_wrong_union("TxSetComponent: txsMaybeDiscountedFee accessed when not selected");
  }
  const _txsMaybeDiscountedFee_t &txsMaybeDiscountedFee() const {
    if (_xdr_field_number(type_) == 1)
      return txsMaybeDiscountedFee_;
    throw xdr::xdr_wrong_union("TxSetComponent: txsMaybeDiscountedFee accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::TxSetComponent::_txsMaybeDiscountedFee_t>
  : xdr_struct_base<field_ptr<::stellar::TxSetComponent::_txsMaybeDiscountedFee_t,
                              decltype(::stellar::TxSetComponent::_txsMaybeDiscountedFee_t::baseFee),
                              &::stellar::TxSetComponent::_txsMaybeDiscountedFee_t::baseFee>,
                    field_ptr<::stellar::TxSetComponent::_txsMaybeDiscountedFee_t,
                              decltype(::stellar::TxSetComponent::_txsMaybeDiscountedFee_t::txs),
                              &::stellar::TxSetComponent::_txsMaybeDiscountedFee_t::txs>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::TxSetComponent::_txsMaybeDiscountedFee_t &obj) {
    archive(ar, obj.baseFee, "baseFee");
    archive(ar, obj.txs, "txs");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::TxSetComponent::_txsMaybeDiscountedFee_t &obj) {
    archive(ar, obj.baseFee, "baseFee");
    archive(ar, obj.txs, "txs");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::TxSetComponent> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::TxSetComponent;
  using case_type = ::stellar::TxSetComponent::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().type());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "txsMaybeDiscountedFee";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::TxSetComponent &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of type in TxSetComponent");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::TxSetComponent &obj) {
    xdr::archive(ar, obj.type(), "type");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of type in TxSetComponent");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::TxSetComponent &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "type");
    obj.type(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

struct TransactionPhase {
  using _xdr_case_type = xdr::xdr_traits<int>::case_type;
private:
  _xdr_case_type v_;
  union {
    xdr::xvector<TxSetComponent> v0Components_;
    ParallelTxsComponent parallelTxsComponent_;
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
    return which == 0 ? 1
      : which == 1 ? 2
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case 0:
      _f(&TransactionPhase::v0Components_, std::forward<_A>(_a)...);
      return true;
    case 1:
      _f(&TransactionPhase::parallelTxsComponent_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return v_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of v in TransactionPhase");
    if (fnum != _xdr_field_number(v_)) {
      this->~TransactionPhase();
      v_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
    }
    else
      v_ = which;
  }
  explicit TransactionPhase(std::int32_t which = std::int32_t{}) : v_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
  }
  TransactionPhase(const TransactionPhase &source) : v_(source.v_) {
    _xdr_with_mem_ptr(xdr::field_constructor, v_, *this, source);
  }
  TransactionPhase(TransactionPhase &&source) : v_(source.v_) {
    _xdr_with_mem_ptr(xdr::field_constructor, v_, *this,
                      std::move(source));
  }
  ~TransactionPhase() { _xdr_with_mem_ptr(xdr::field_destructor, v_, *this); }
  TransactionPhase &operator=(const TransactionPhase &source) {
    if (_xdr_field_number(v_)
        == _xdr_field_number(source.v_))
      _xdr_with_mem_ptr(xdr::field_assigner, v_, *this, source);
    else {
      this->~TransactionPhase();
      v_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this, source);
    }
    v_ = source.v_;
    return *this;
  }
  TransactionPhase &operator=(TransactionPhase &&source) {
    if (_xdr_field_number(v_)
         == _xdr_field_number(source.v_))
      _xdr_with_mem_ptr(xdr::field_assigner, v_, *this,
                        std::move(source));
    else {
      this->~TransactionPhase();
      v_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this,
                        std::move(source));
    }
    v_ = source.v_;
    return *this;
  }

  std::int32_t v() const { return std::int32_t(v_); }
  TransactionPhase &v(int _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  xdr::xvector<TxSetComponent> &v0Components() {
    if (_xdr_field_number(v_) == 1)
      return v0Components_;
    throw xdr::xdr_wrong_union("TransactionPhase: v0Components accessed when not selected");
  }
  const xdr::xvector<TxSetComponent> &v0Components() const {
    if (_xdr_field_number(v_) == 1)
      return v0Components_;
    throw xdr::xdr_wrong_union("TransactionPhase: v0Components accessed when not selected");
  }
  ParallelTxsComponent &parallelTxsComponent() {
    if (_xdr_field_number(v_) == 2)
      return parallelTxsComponent_;
    throw xdr::xdr_wrong_union("TransactionPhase: parallelTxsComponent accessed when not selected");
  }
  const ParallelTxsComponent &parallelTxsComponent() const {
    if (_xdr_field_number(v_) == 2)
      return parallelTxsComponent_;
    throw xdr::xdr_wrong_union("TransactionPhase: parallelTxsComponent accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::TransactionPhase> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::TransactionPhase;
  using case_type = ::stellar::TransactionPhase::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "v0Components";
    case 2:
      return "parallelTxsComponent";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::TransactionPhase &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in TransactionPhase");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::TransactionPhase &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in TransactionPhase");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::TransactionPhase &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.v(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

struct TransactionSet {
  Hash previousLedgerHash{};
  xdr::xvector<TransactionEnvelope> txs{};

  TransactionSet() = default;
  template<typename _previousLedgerHash_T,
           typename _txs_T,
           typename = typename
           std::enable_if<std::is_constructible<Hash, _previousLedgerHash_T>::value
                          && std::is_constructible<xdr::xvector<TransactionEnvelope>, _txs_T>::value
                         >::type>
  explicit TransactionSet(_previousLedgerHash_T &&_previousLedgerHash,
                          _txs_T &&_txs)
    : previousLedgerHash(std::forward<_previousLedgerHash_T>(_previousLedgerHash)),
      txs(std::forward<_txs_T>(_txs)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::TransactionSet>
  : xdr_struct_base<field_ptr<::stellar::TransactionSet,
                              decltype(::stellar::TransactionSet::previousLedgerHash),
                              &::stellar::TransactionSet::previousLedgerHash>,
                    field_ptr<::stellar::TransactionSet,
                              decltype(::stellar::TransactionSet::txs),
                              &::stellar::TransactionSet::txs>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::TransactionSet &obj) {
    archive(ar, obj.previousLedgerHash, "previousLedgerHash");
    archive(ar, obj.txs, "txs");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::TransactionSet &obj) {
    archive(ar, obj.previousLedgerHash, "previousLedgerHash");
    archive(ar, obj.txs, "txs");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct TransactionSetV1 {
  Hash previousLedgerHash{};
  xdr::xvector<TransactionPhase> phases{};

  TransactionSetV1() = default;
  template<typename _previousLedgerHash_T,
           typename _phases_T,
           typename = typename
           std::enable_if<std::is_constructible<Hash, _previousLedgerHash_T>::value
                          && std::is_constructible<xdr::xvector<TransactionPhase>, _phases_T>::value
                         >::type>
  explicit TransactionSetV1(_previousLedgerHash_T &&_previousLedgerHash,
                            _phases_T &&_phases)
    : previousLedgerHash(std::forward<_previousLedgerHash_T>(_previousLedgerHash)),
      phases(std::forward<_phases_T>(_phases)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::TransactionSetV1>
  : xdr_struct_base<field_ptr<::stellar::TransactionSetV1,
                              decltype(::stellar::TransactionSetV1::previousLedgerHash),
                              &::stellar::TransactionSetV1::previousLedgerHash>,
                    field_ptr<::stellar::TransactionSetV1,
                              decltype(::stellar::TransactionSetV1::phases),
                              &::stellar::TransactionSetV1::phases>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::TransactionSetV1 &obj) {
    archive(ar, obj.previousLedgerHash, "previousLedgerHash");
    archive(ar, obj.phases, "phases");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::TransactionSetV1 &obj) {
    archive(ar, obj.previousLedgerHash, "previousLedgerHash");
    archive(ar, obj.phases, "phases");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct GeneralizedTransactionSet {
  using _xdr_case_type = xdr::xdr_traits<int>::case_type;
private:
  _xdr_case_type v_;
  union {
    TransactionSetV1 v1TxSet_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<int> &_xdr_case_values() {
    static const std::vector<int> _xdr_disc_vec {
      1
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == 1 ? 1
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case 1:
      _f(&GeneralizedTransactionSet::v1TxSet_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return v_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of v in GeneralizedTransactionSet");
    if (fnum != _xdr_field_number(v_)) {
      this->~GeneralizedTransactionSet();
      v_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
    }
    else
      v_ = which;
  }
  explicit GeneralizedTransactionSet(std::int32_t which = std::int32_t{}) : v_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
  }
  GeneralizedTransactionSet(const GeneralizedTransactionSet &source) : v_(source.v_) {
    _xdr_with_mem_ptr(xdr::field_constructor, v_, *this, source);
  }
  GeneralizedTransactionSet(GeneralizedTransactionSet &&source) : v_(source.v_) {
    _xdr_with_mem_ptr(xdr::field_constructor, v_, *this,
                      std::move(source));
  }
  ~GeneralizedTransactionSet() { _xdr_with_mem_ptr(xdr::field_destructor, v_, *this); }
  GeneralizedTransactionSet &operator=(const GeneralizedTransactionSet &source) {
    if (_xdr_field_number(v_)
        == _xdr_field_number(source.v_))
      _xdr_with_mem_ptr(xdr::field_assigner, v_, *this, source);
    else {
      this->~GeneralizedTransactionSet();
      v_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this, source);
    }
    v_ = source.v_;
    return *this;
  }
  GeneralizedTransactionSet &operator=(GeneralizedTransactionSet &&source) {
    if (_xdr_field_number(v_)
         == _xdr_field_number(source.v_))
      _xdr_with_mem_ptr(xdr::field_assigner, v_, *this,
                        std::move(source));
    else {
      this->~GeneralizedTransactionSet();
      v_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this,
                        std::move(source));
    }
    v_ = source.v_;
    return *this;
  }

  std::int32_t v() const { return std::int32_t(v_); }
  GeneralizedTransactionSet &v(int _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  TransactionSetV1 &v1TxSet() {
    if (_xdr_field_number(v_) == 1)
      return v1TxSet_;
    throw xdr::xdr_wrong_union("GeneralizedTransactionSet: v1TxSet accessed when not selected");
  }
  const TransactionSetV1 &v1TxSet() const {
    if (_xdr_field_number(v_) == 1)
      return v1TxSet_;
    throw xdr::xdr_wrong_union("GeneralizedTransactionSet: v1TxSet accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::GeneralizedTransactionSet> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::GeneralizedTransactionSet;
  using case_type = ::stellar::GeneralizedTransactionSet::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "v1TxSet";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::GeneralizedTransactionSet &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in GeneralizedTransactionSet");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::GeneralizedTransactionSet &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in GeneralizedTransactionSet");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::GeneralizedTransactionSet &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.v(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

struct TransactionResultPair {
  Hash transactionHash{};
  TransactionResult result{};

  TransactionResultPair() = default;
  template<typename _transactionHash_T,
           typename _result_T,
           typename = typename
           std::enable_if<std::is_constructible<Hash, _transactionHash_T>::value
                          && std::is_constructible<TransactionResult, _result_T>::value
                         >::type>
  explicit TransactionResultPair(_transactionHash_T &&_transactionHash,
                                 _result_T &&_result)
    : transactionHash(std::forward<_transactionHash_T>(_transactionHash)),
      result(std::forward<_result_T>(_result)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::TransactionResultPair>
  : xdr_struct_base<field_ptr<::stellar::TransactionResultPair,
                              decltype(::stellar::TransactionResultPair::transactionHash),
                              &::stellar::TransactionResultPair::transactionHash>,
                    field_ptr<::stellar::TransactionResultPair,
                              decltype(::stellar::TransactionResultPair::result),
                              &::stellar::TransactionResultPair::result>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::TransactionResultPair &obj) {
    archive(ar, obj.transactionHash, "transactionHash");
    archive(ar, obj.result, "result");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::TransactionResultPair &obj) {
    archive(ar, obj.transactionHash, "transactionHash");
    archive(ar, obj.result, "result");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct TransactionResultSet {
  xdr::xvector<TransactionResultPair> results{};

  TransactionResultSet() = default;
  template<typename _results_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::xvector<TransactionResultPair>, _results_T>::value
                         >::type>
  explicit TransactionResultSet(_results_T &&_results)
    : results(std::forward<_results_T>(_results)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::TransactionResultSet>
  : xdr_struct_base<field_ptr<::stellar::TransactionResultSet,
                              decltype(::stellar::TransactionResultSet::results),
                              &::stellar::TransactionResultSet::results>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::TransactionResultSet &obj) {
    archive(ar, obj.results, "results");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::TransactionResultSet &obj) {
    archive(ar, obj.results, "results");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct TransactionHistoryEntry {
  struct _ext_t {
    using _xdr_case_type = xdr::xdr_traits<int>::case_type;
  private:
    _xdr_case_type v_;
    union {
      GeneralizedTransactionSet generalizedTxSet_;
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
        _f(&_ext_t::generalizedTxSet_, std::forward<_A>(_a)...);
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

    GeneralizedTransactionSet &generalizedTxSet() {
      if (_xdr_field_number(v_) == 1)
        return generalizedTxSet_;
      throw xdr::xdr_wrong_union("_ext_t: generalizedTxSet accessed when not selected");
    }
    const GeneralizedTransactionSet &generalizedTxSet() const {
      if (_xdr_field_number(v_) == 1)
        return generalizedTxSet_;
      throw xdr::xdr_wrong_union("_ext_t: generalizedTxSet accessed when not selected");
    }
  };

  uint32 ledgerSeq{};
  TransactionSet txSet{};
  _ext_t ext{};

  TransactionHistoryEntry() = default;
  template<typename _ledgerSeq_T,
           typename _txSet_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint32, _ledgerSeq_T>::value
                          && std::is_constructible<TransactionSet, _txSet_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit TransactionHistoryEntry(_ledgerSeq_T &&_ledgerSeq,
                                   _txSet_T &&_txSet,
                                   _ext_T &&_ext)
    : ledgerSeq(std::forward<_ledgerSeq_T>(_ledgerSeq)),
      txSet(std::forward<_txSet_T>(_txSet)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::TransactionHistoryEntry::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::TransactionHistoryEntry::_ext_t;
  using case_type = ::stellar::TransactionHistoryEntry::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "generalizedTxSet";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::TransactionHistoryEntry::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::TransactionHistoryEntry::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::TransactionHistoryEntry::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.v(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::TransactionHistoryEntry>
  : xdr_struct_base<field_ptr<::stellar::TransactionHistoryEntry,
                              decltype(::stellar::TransactionHistoryEntry::ledgerSeq),
                              &::stellar::TransactionHistoryEntry::ledgerSeq>,
                    field_ptr<::stellar::TransactionHistoryEntry,
                              decltype(::stellar::TransactionHistoryEntry::txSet),
                              &::stellar::TransactionHistoryEntry::txSet>,
                    field_ptr<::stellar::TransactionHistoryEntry,
                              decltype(::stellar::TransactionHistoryEntry::ext),
                              &::stellar::TransactionHistoryEntry::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::TransactionHistoryEntry &obj) {
    archive(ar, obj.ledgerSeq, "ledgerSeq");
    archive(ar, obj.txSet, "txSet");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::TransactionHistoryEntry &obj) {
    archive(ar, obj.ledgerSeq, "ledgerSeq");
    archive(ar, obj.txSet, "txSet");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct TransactionHistoryResultEntry {
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

  uint32 ledgerSeq{};
  TransactionResultSet txResultSet{};
  _ext_t ext{};

  TransactionHistoryResultEntry() = default;
  template<typename _ledgerSeq_T,
           typename _txResultSet_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<uint32, _ledgerSeq_T>::value
                          && std::is_constructible<TransactionResultSet, _txResultSet_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit TransactionHistoryResultEntry(_ledgerSeq_T &&_ledgerSeq,
                                         _txResultSet_T &&_txResultSet,
                                         _ext_T &&_ext)
    : ledgerSeq(std::forward<_ledgerSeq_T>(_ledgerSeq)),
      txResultSet(std::forward<_txResultSet_T>(_txResultSet)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::TransactionHistoryResultEntry::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::TransactionHistoryResultEntry::_ext_t;
  using case_type = ::stellar::TransactionHistoryResultEntry::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::TransactionHistoryResultEntry::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::TransactionHistoryResultEntry::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::TransactionHistoryResultEntry::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.v(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::TransactionHistoryResultEntry>
  : xdr_struct_base<field_ptr<::stellar::TransactionHistoryResultEntry,
                              decltype(::stellar::TransactionHistoryResultEntry::ledgerSeq),
                              &::stellar::TransactionHistoryResultEntry::ledgerSeq>,
                    field_ptr<::stellar::TransactionHistoryResultEntry,
                              decltype(::stellar::TransactionHistoryResultEntry::txResultSet),
                              &::stellar::TransactionHistoryResultEntry::txResultSet>,
                    field_ptr<::stellar::TransactionHistoryResultEntry,
                              decltype(::stellar::TransactionHistoryResultEntry::ext),
                              &::stellar::TransactionHistoryResultEntry::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::TransactionHistoryResultEntry &obj) {
    archive(ar, obj.ledgerSeq, "ledgerSeq");
    archive(ar, obj.txResultSet, "txResultSet");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::TransactionHistoryResultEntry &obj) {
    archive(ar, obj.ledgerSeq, "ledgerSeq");
    archive(ar, obj.txResultSet, "txResultSet");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct LedgerHeaderHistoryEntry {
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

  Hash hash{};
  LedgerHeader header{};
  _ext_t ext{};

  LedgerHeaderHistoryEntry() = default;
  template<typename _hash_T,
           typename _header_T,
           typename _ext_T,
           typename = typename
           std::enable_if<std::is_constructible<Hash, _hash_T>::value
                          && std::is_constructible<LedgerHeader, _header_T>::value
                          && std::is_constructible<_ext_t, _ext_T>::value
                         >::type>
  explicit LedgerHeaderHistoryEntry(_hash_T &&_hash,
                                    _header_T &&_header,
                                    _ext_T &&_ext)
    : hash(std::forward<_hash_T>(_hash)),
      header(std::forward<_header_T>(_header)),
      ext(std::forward<_ext_T>(_ext)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::LedgerHeaderHistoryEntry::_ext_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::LedgerHeaderHistoryEntry::_ext_t;
  using case_type = ::stellar::LedgerHeaderHistoryEntry::_ext_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::LedgerHeaderHistoryEntry::_ext_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerHeaderHistoryEntry::_ext_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _ext_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerHeaderHistoryEntry::_ext_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.v(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::LedgerHeaderHistoryEntry>
  : xdr_struct_base<field_ptr<::stellar::LedgerHeaderHistoryEntry,
                              decltype(::stellar::LedgerHeaderHistoryEntry::hash),
                              &::stellar::LedgerHeaderHistoryEntry::hash>,
                    field_ptr<::stellar::LedgerHeaderHistoryEntry,
                              decltype(::stellar::LedgerHeaderHistoryEntry::header),
                              &::stellar::LedgerHeaderHistoryEntry::header>,
                    field_ptr<::stellar::LedgerHeaderHistoryEntry,
                              decltype(::stellar::LedgerHeaderHistoryEntry::ext),
                              &::stellar::LedgerHeaderHistoryEntry::ext>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerHeaderHistoryEntry &obj) {
    archive(ar, obj.hash, "hash");
    archive(ar, obj.header, "header");
    archive(ar, obj.ext, "ext");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerHeaderHistoryEntry &obj) {
    archive(ar, obj.hash, "hash");
    archive(ar, obj.header, "header");
    archive(ar, obj.ext, "ext");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct LedgerSCPMessages {
  uint32 ledgerSeq{};
  xdr::xvector<SCPEnvelope> messages{};

  LedgerSCPMessages() = default;
  template<typename _ledgerSeq_T,
           typename _messages_T,
           typename = typename
           std::enable_if<std::is_constructible<uint32, _ledgerSeq_T>::value
                          && std::is_constructible<xdr::xvector<SCPEnvelope>, _messages_T>::value
                         >::type>
  explicit LedgerSCPMessages(_ledgerSeq_T &&_ledgerSeq,
                             _messages_T &&_messages)
    : ledgerSeq(std::forward<_ledgerSeq_T>(_ledgerSeq)),
      messages(std::forward<_messages_T>(_messages)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::LedgerSCPMessages>
  : xdr_struct_base<field_ptr<::stellar::LedgerSCPMessages,
                              decltype(::stellar::LedgerSCPMessages::ledgerSeq),
                              &::stellar::LedgerSCPMessages::ledgerSeq>,
                    field_ptr<::stellar::LedgerSCPMessages,
                              decltype(::stellar::LedgerSCPMessages::messages),
                              &::stellar::LedgerSCPMessages::messages>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerSCPMessages &obj) {
    archive(ar, obj.ledgerSeq, "ledgerSeq");
    archive(ar, obj.messages, "messages");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerSCPMessages &obj) {
    archive(ar, obj.ledgerSeq, "ledgerSeq");
    archive(ar, obj.messages, "messages");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct SCPHistoryEntryV0 {
  xdr::xvector<SCPQuorumSet> quorumSets{};
  LedgerSCPMessages ledgerMessages{};

  SCPHistoryEntryV0() = default;
  template<typename _quorumSets_T,
           typename _ledgerMessages_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::xvector<SCPQuorumSet>, _quorumSets_T>::value
                          && std::is_constructible<LedgerSCPMessages, _ledgerMessages_T>::value
                         >::type>
  explicit SCPHistoryEntryV0(_quorumSets_T &&_quorumSets,
                             _ledgerMessages_T &&_ledgerMessages)
    : quorumSets(std::forward<_quorumSets_T>(_quorumSets)),
      ledgerMessages(std::forward<_ledgerMessages_T>(_ledgerMessages)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCPHistoryEntryV0>
  : xdr_struct_base<field_ptr<::stellar::SCPHistoryEntryV0,
                              decltype(::stellar::SCPHistoryEntryV0::quorumSets),
                              &::stellar::SCPHistoryEntryV0::quorumSets>,
                    field_ptr<::stellar::SCPHistoryEntryV0,
                              decltype(::stellar::SCPHistoryEntryV0::ledgerMessages),
                              &::stellar::SCPHistoryEntryV0::ledgerMessages>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SCPHistoryEntryV0 &obj) {
    archive(ar, obj.quorumSets, "quorumSets");
    archive(ar, obj.ledgerMessages, "ledgerMessages");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SCPHistoryEntryV0 &obj) {
    archive(ar, obj.quorumSets, "quorumSets");
    archive(ar, obj.ledgerMessages, "ledgerMessages");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct SCPHistoryEntry {
  using _xdr_case_type = xdr::xdr_traits<int>::case_type;
private:
  _xdr_case_type v_;
  union {
    SCPHistoryEntryV0 v0_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<int> &_xdr_case_values() {
    static const std::vector<int> _xdr_disc_vec {
      0
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == 0 ? 1
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case 0:
      _f(&SCPHistoryEntry::v0_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return v_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of v in SCPHistoryEntry");
    if (fnum != _xdr_field_number(v_)) {
      this->~SCPHistoryEntry();
      v_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
    }
    else
      v_ = which;
  }
  explicit SCPHistoryEntry(std::int32_t which = std::int32_t{}) : v_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
  }
  SCPHistoryEntry(const SCPHistoryEntry &source) : v_(source.v_) {
    _xdr_with_mem_ptr(xdr::field_constructor, v_, *this, source);
  }
  SCPHistoryEntry(SCPHistoryEntry &&source) : v_(source.v_) {
    _xdr_with_mem_ptr(xdr::field_constructor, v_, *this,
                      std::move(source));
  }
  ~SCPHistoryEntry() { _xdr_with_mem_ptr(xdr::field_destructor, v_, *this); }
  SCPHistoryEntry &operator=(const SCPHistoryEntry &source) {
    if (_xdr_field_number(v_)
        == _xdr_field_number(source.v_))
      _xdr_with_mem_ptr(xdr::field_assigner, v_, *this, source);
    else {
      this->~SCPHistoryEntry();
      v_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this, source);
    }
    v_ = source.v_;
    return *this;
  }
  SCPHistoryEntry &operator=(SCPHistoryEntry &&source) {
    if (_xdr_field_number(v_)
         == _xdr_field_number(source.v_))
      _xdr_with_mem_ptr(xdr::field_assigner, v_, *this,
                        std::move(source));
    else {
      this->~SCPHistoryEntry();
      v_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this,
                        std::move(source));
    }
    v_ = source.v_;
    return *this;
  }

  std::int32_t v() const { return std::int32_t(v_); }
  SCPHistoryEntry &v(int _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  SCPHistoryEntryV0 &v0() {
    if (_xdr_field_number(v_) == 1)
      return v0_;
    throw xdr::xdr_wrong_union("SCPHistoryEntry: v0 accessed when not selected");
  }
  const SCPHistoryEntryV0 &v0() const {
    if (_xdr_field_number(v_) == 1)
      return v0_;
    throw xdr::xdr_wrong_union("SCPHistoryEntry: v0 accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SCPHistoryEntry> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::SCPHistoryEntry;
  using case_type = ::stellar::SCPHistoryEntry::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

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

  static std::size_t serial_size(const ::stellar::SCPHistoryEntry &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in SCPHistoryEntry");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SCPHistoryEntry &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in SCPHistoryEntry");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SCPHistoryEntry &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.v(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

enum LedgerEntryChangeType : std::int32_t {
  LEDGER_ENTRY_CREATED = 0,
  LEDGER_ENTRY_UPDATED = 1,
  LEDGER_ENTRY_REMOVED = 2,
  LEDGER_ENTRY_STATE = 3,
  LEDGER_ENTRY_RESTORED = 4,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::LedgerEntryChangeType>
  : xdr_integral_base<::stellar::LedgerEntryChangeType, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::LedgerEntryChangeType val) {
    switch (val) {
    case ::stellar::LEDGER_ENTRY_CREATED:
      return "LEDGER_ENTRY_CREATED";
    case ::stellar::LEDGER_ENTRY_UPDATED:
      return "LEDGER_ENTRY_UPDATED";
    case ::stellar::LEDGER_ENTRY_REMOVED:
      return "LEDGER_ENTRY_REMOVED";
    case ::stellar::LEDGER_ENTRY_STATE:
      return "LEDGER_ENTRY_STATE";
    case ::stellar::LEDGER_ENTRY_RESTORED:
      return "LEDGER_ENTRY_RESTORED";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::LEDGER_ENTRY_CREATED,
      ::stellar::LEDGER_ENTRY_UPDATED,
      ::stellar::LEDGER_ENTRY_REMOVED,
      ::stellar::LEDGER_ENTRY_STATE,
      ::stellar::LEDGER_ENTRY_RESTORED
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct LedgerEntryChange {
  using _xdr_case_type = xdr::xdr_traits<LedgerEntryChangeType>::case_type;
private:
  _xdr_case_type type_;
  union {
    LedgerEntry created_;
    LedgerEntry updated_;
    LedgerKey removed_;
    LedgerEntry state_;
    LedgerEntry restored_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<LedgerEntryChangeType> &_xdr_case_values() {
    static const std::vector<LedgerEntryChangeType> _xdr_disc_vec {
      LEDGER_ENTRY_CREATED,
      LEDGER_ENTRY_UPDATED,
      LEDGER_ENTRY_REMOVED,
      LEDGER_ENTRY_STATE,
      LEDGER_ENTRY_RESTORED
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == LEDGER_ENTRY_CREATED ? 1
      : which == LEDGER_ENTRY_UPDATED ? 2
      : which == LEDGER_ENTRY_REMOVED ? 3
      : which == LEDGER_ENTRY_STATE ? 4
      : which == LEDGER_ENTRY_RESTORED ? 5
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case LEDGER_ENTRY_CREATED:
      _f(&LedgerEntryChange::created_, std::forward<_A>(_a)...);
      return true;
    case LEDGER_ENTRY_UPDATED:
      _f(&LedgerEntryChange::updated_, std::forward<_A>(_a)...);
      return true;
    case LEDGER_ENTRY_REMOVED:
      _f(&LedgerEntryChange::removed_, std::forward<_A>(_a)...);
      return true;
    case LEDGER_ENTRY_STATE:
      _f(&LedgerEntryChange::state_, std::forward<_A>(_a)...);
      return true;
    case LEDGER_ENTRY_RESTORED:
      _f(&LedgerEntryChange::restored_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return type_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of type in LedgerEntryChange");
    if (fnum != _xdr_field_number(type_)) {
      this->~LedgerEntryChange();
      type_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
    }
    else
      type_ = which;
  }
  explicit LedgerEntryChange(LedgerEntryChangeType which = LedgerEntryChangeType{}) : type_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this);
  }
  LedgerEntryChange(const LedgerEntryChange &source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this, source);
  }
  LedgerEntryChange(LedgerEntryChange &&source) : type_(source.type_) {
    _xdr_with_mem_ptr(xdr::field_constructor, type_, *this,
                      std::move(source));
  }
  ~LedgerEntryChange() { _xdr_with_mem_ptr(xdr::field_destructor, type_, *this); }
  LedgerEntryChange &operator=(const LedgerEntryChange &source) {
    if (_xdr_field_number(type_)
        == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this, source);
    else {
      this->~LedgerEntryChange();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this, source);
    }
    type_ = source.type_;
    return *this;
  }
  LedgerEntryChange &operator=(LedgerEntryChange &&source) {
    if (_xdr_field_number(type_)
         == _xdr_field_number(source.type_))
      _xdr_with_mem_ptr(xdr::field_assigner, type_, *this,
                        std::move(source));
    else {
      this->~LedgerEntryChange();
      type_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.type_, *this,
                        std::move(source));
    }
    type_ = source.type_;
    return *this;
  }

  LedgerEntryChangeType type() const { return LedgerEntryChangeType(type_); }
  LedgerEntryChange &type(LedgerEntryChangeType _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  LedgerEntry &created() {
    if (_xdr_field_number(type_) == 1)
      return created_;
    throw xdr::xdr_wrong_union("LedgerEntryChange: created accessed when not selected");
  }
  const LedgerEntry &created() const {
    if (_xdr_field_number(type_) == 1)
      return created_;
    throw xdr::xdr_wrong_union("LedgerEntryChange: created accessed when not selected");
  }
  LedgerEntry &updated() {
    if (_xdr_field_number(type_) == 2)
      return updated_;
    throw xdr::xdr_wrong_union("LedgerEntryChange: updated accessed when not selected");
  }
  const LedgerEntry &updated() const {
    if (_xdr_field_number(type_) == 2)
      return updated_;
    throw xdr::xdr_wrong_union("LedgerEntryChange: updated accessed when not selected");
  }
  LedgerKey &removed() {
    if (_xdr_field_number(type_) == 3)
      return removed_;
    throw xdr::xdr_wrong_union("LedgerEntryChange: removed accessed when not selected");
  }
  const LedgerKey &removed() const {
    if (_xdr_field_number(type_) == 3)
      return removed_;
    throw xdr::xdr_wrong_union("LedgerEntryChange: removed accessed when not selected");
  }
  LedgerEntry &state() {
    if (_xdr_field_number(type_) == 4)
      return state_;
    throw xdr::xdr_wrong_union("LedgerEntryChange: state accessed when not selected");
  }
  const LedgerEntry &state() const {
    if (_xdr_field_number(type_) == 4)
      return state_;
    throw xdr::xdr_wrong_union("LedgerEntryChange: state accessed when not selected");
  }
  LedgerEntry &restored() {
    if (_xdr_field_number(type_) == 5)
      return restored_;
    throw xdr::xdr_wrong_union("LedgerEntryChange: restored accessed when not selected");
  }
  const LedgerEntry &restored() const {
    if (_xdr_field_number(type_) == 5)
      return restored_;
    throw xdr::xdr_wrong_union("LedgerEntryChange: restored accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::LedgerEntryChange> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::LedgerEntryChange;
  using case_type = ::stellar::LedgerEntryChange::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().type());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "created";
    case 2:
      return "updated";
    case 3:
      return "removed";
    case 4:
      return "state";
    case 5:
      return "restored";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::LedgerEntryChange &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of type in LedgerEntryChange");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerEntryChange &obj) {
    xdr::archive(ar, obj.type(), "type");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of type in LedgerEntryChange");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerEntryChange &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "type");
    obj.type(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.type(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

using LedgerEntryChanges = xdr::xvector<LedgerEntryChange>;

struct OperationMeta {
  LedgerEntryChanges changes{};

  OperationMeta() = default;
  template<typename _changes_T,
           typename = typename
           std::enable_if<std::is_constructible<LedgerEntryChanges, _changes_T>::value
                         >::type>
  explicit OperationMeta(_changes_T &&_changes)
    : changes(std::forward<_changes_T>(_changes)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::OperationMeta>
  : xdr_struct_base<field_ptr<::stellar::OperationMeta,
                              decltype(::stellar::OperationMeta::changes),
                              &::stellar::OperationMeta::changes>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::OperationMeta &obj) {
    archive(ar, obj.changes, "changes");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::OperationMeta &obj) {
    archive(ar, obj.changes, "changes");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct TransactionMetaV1 {
  LedgerEntryChanges txChanges{};
  xdr::xvector<OperationMeta> operations{};

  TransactionMetaV1() = default;
  template<typename _txChanges_T,
           typename _operations_T,
           typename = typename
           std::enable_if<std::is_constructible<LedgerEntryChanges, _txChanges_T>::value
                          && std::is_constructible<xdr::xvector<OperationMeta>, _operations_T>::value
                         >::type>
  explicit TransactionMetaV1(_txChanges_T &&_txChanges,
                             _operations_T &&_operations)
    : txChanges(std::forward<_txChanges_T>(_txChanges)),
      operations(std::forward<_operations_T>(_operations)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::TransactionMetaV1>
  : xdr_struct_base<field_ptr<::stellar::TransactionMetaV1,
                              decltype(::stellar::TransactionMetaV1::txChanges),
                              &::stellar::TransactionMetaV1::txChanges>,
                    field_ptr<::stellar::TransactionMetaV1,
                              decltype(::stellar::TransactionMetaV1::operations),
                              &::stellar::TransactionMetaV1::operations>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::TransactionMetaV1 &obj) {
    archive(ar, obj.txChanges, "txChanges");
    archive(ar, obj.operations, "operations");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::TransactionMetaV1 &obj) {
    archive(ar, obj.txChanges, "txChanges");
    archive(ar, obj.operations, "operations");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct TransactionMetaV2 {
  LedgerEntryChanges txChangesBefore{};
  xdr::xvector<OperationMeta> operations{};
  LedgerEntryChanges txChangesAfter{};

  TransactionMetaV2() = default;
  template<typename _txChangesBefore_T,
           typename _operations_T,
           typename _txChangesAfter_T,
           typename = typename
           std::enable_if<std::is_constructible<LedgerEntryChanges, _txChangesBefore_T>::value
                          && std::is_constructible<xdr::xvector<OperationMeta>, _operations_T>::value
                          && std::is_constructible<LedgerEntryChanges, _txChangesAfter_T>::value
                         >::type>
  explicit TransactionMetaV2(_txChangesBefore_T &&_txChangesBefore,
                             _operations_T &&_operations,
                             _txChangesAfter_T &&_txChangesAfter)
    : txChangesBefore(std::forward<_txChangesBefore_T>(_txChangesBefore)),
      operations(std::forward<_operations_T>(_operations)),
      txChangesAfter(std::forward<_txChangesAfter_T>(_txChangesAfter)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::TransactionMetaV2>
  : xdr_struct_base<field_ptr<::stellar::TransactionMetaV2,
                              decltype(::stellar::TransactionMetaV2::txChangesBefore),
                              &::stellar::TransactionMetaV2::txChangesBefore>,
                    field_ptr<::stellar::TransactionMetaV2,
                              decltype(::stellar::TransactionMetaV2::operations),
                              &::stellar::TransactionMetaV2::operations>,
                    field_ptr<::stellar::TransactionMetaV2,
                              decltype(::stellar::TransactionMetaV2::txChangesAfter),
                              &::stellar::TransactionMetaV2::txChangesAfter>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::TransactionMetaV2 &obj) {
    archive(ar, obj.txChangesBefore, "txChangesBefore");
    archive(ar, obj.operations, "operations");
    archive(ar, obj.txChangesAfter, "txChangesAfter");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::TransactionMetaV2 &obj) {
    archive(ar, obj.txChangesBefore, "txChangesBefore");
    archive(ar, obj.operations, "operations");
    archive(ar, obj.txChangesAfter, "txChangesAfter");
    xdr::validate(obj);
  }
};
} namespace stellar {

enum ContractEventType : std::int32_t {
  SYSTEM = 0,
  CONTRACT = 1,
  DIAGNOSTIC = 2,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ContractEventType>
  : xdr_integral_base<::stellar::ContractEventType, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ContractEventType val) {
    switch (val) {
    case ::stellar::SYSTEM:
      return "SYSTEM";
    case ::stellar::CONTRACT:
      return "CONTRACT";
    case ::stellar::DIAGNOSTIC:
      return "DIAGNOSTIC";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::SYSTEM,
      ::stellar::CONTRACT,
      ::stellar::DIAGNOSTIC
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct ContractEvent {
  struct _body_t {
    struct _v0_t {
      xdr::xvector<SCVal> topics{};
      SCVal data{};

      _v0_t() = default;
      template<typename _topics_T,
               typename _data_T,
               typename = typename
               std::enable_if<std::is_constructible<xdr::xvector<SCVal>, _topics_T>::value
                              && std::is_constructible<SCVal, _data_T>::value
                             >::type>
      explicit _v0_t(_topics_T &&_topics,
                     _data_T &&_data)
        : topics(std::forward<_topics_T>(_topics)),
          data(std::forward<_data_T>(_data)) {}
    };

    using _xdr_case_type = xdr::xdr_traits<int>::case_type;
  private:
    _xdr_case_type v_;
    union {
      _v0_t v0_;
    };

  public:
    static Constexpr const bool _xdr_has_default_case = false;
    static const std::vector<int> &_xdr_case_values() {
      static const std::vector<int> _xdr_disc_vec {
        0
      };
      return _xdr_disc_vec;
    }
    static Constexpr int _xdr_field_number(_xdr_case_type which) {
      return which == 0 ? 1
        : -1;
    }
    template<typename _F, typename..._A> static bool
    _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
      switch (_which) {
      case 0:
        _f(&_body_t::v0_, std::forward<_A>(_a)...);
        return true;
      }
      return false;
    }

    _xdr_case_type _xdr_discriminant() const { return v_; }
    void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
      int fnum = _xdr_field_number(which);
      if (fnum < 0 && validate)
        throw xdr::xdr_bad_discriminant("bad value of v in _body_t");
      if (fnum != _xdr_field_number(v_)) {
        this->~_body_t();
        v_ = which;
        _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
      }
      else
        v_ = which;
    }
    explicit _body_t(std::int32_t which = std::int32_t{}) : v_(which) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
    }
    _body_t(const _body_t &source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this, source);
    }
    _body_t(_body_t &&source) : v_(source.v_) {
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this,
                        std::move(source));
    }
    ~_body_t() { _xdr_with_mem_ptr(xdr::field_destructor, v_, *this); }
    _body_t &operator=(const _body_t &source) {
      if (_xdr_field_number(v_)
          == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this, source);
      else {
        this->~_body_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this, source);
      }
      v_ = source.v_;
      return *this;
    }
    _body_t &operator=(_body_t &&source) {
      if (_xdr_field_number(v_)
           == _xdr_field_number(source.v_))
        _xdr_with_mem_ptr(xdr::field_assigner, v_, *this,
                          std::move(source));
      else {
        this->~_body_t();
        v_ = std::numeric_limits<_xdr_case_type>::max();
        _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this,
                          std::move(source));
      }
      v_ = source.v_;
      return *this;
    }

    std::int32_t v() const { return std::int32_t(v_); }
    _body_t &v(int _xdr_d, bool _xdr_validate = true) {
      _xdr_discriminant(_xdr_d, _xdr_validate);
      return *this;
    }

    _v0_t &v0() {
      if (_xdr_field_number(v_) == 1)
        return v0_;
      throw xdr::xdr_wrong_union("_body_t: v0 accessed when not selected");
    }
    const _v0_t &v0() const {
      if (_xdr_field_number(v_) == 1)
        return v0_;
      throw xdr::xdr_wrong_union("_body_t: v0 accessed when not selected");
    }
  };

  ExtensionPoint ext{};
  xdr::pointer<ContractID> contractID{};
  ContractEventType type{};
  _body_t body{};

  ContractEvent() = default;
  template<typename _ext_T,
           typename _contractID_T,
           typename _type_T,
           typename _body_T,
           typename = typename
           std::enable_if<std::is_constructible<ExtensionPoint, _ext_T>::value
                          && std::is_constructible<xdr::pointer<ContractID>, _contractID_T>::value
                          && std::is_constructible<ContractEventType, _type_T>::value
                          && std::is_constructible<_body_t, _body_T>::value
                         >::type>
  explicit ContractEvent(_ext_T &&_ext,
                         _contractID_T &&_contractID,
                         _type_T &&_type,
                         _body_T &&_body)
    : ext(std::forward<_ext_T>(_ext)),
      contractID(std::forward<_contractID_T>(_contractID)),
      type(std::forward<_type_T>(_type)),
      body(std::forward<_body_T>(_body)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ContractEvent::_body_t::_v0_t>
  : xdr_struct_base<field_ptr<::stellar::ContractEvent::_body_t::_v0_t,
                              decltype(::stellar::ContractEvent::_body_t::_v0_t::topics),
                              &::stellar::ContractEvent::_body_t::_v0_t::topics>,
                    field_ptr<::stellar::ContractEvent::_body_t::_v0_t,
                              decltype(::stellar::ContractEvent::_body_t::_v0_t::data),
                              &::stellar::ContractEvent::_body_t::_v0_t::data>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ContractEvent::_body_t::_v0_t &obj) {
    archive(ar, obj.topics, "topics");
    archive(ar, obj.data, "data");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ContractEvent::_body_t::_v0_t &obj) {
    archive(ar, obj.topics, "topics");
    archive(ar, obj.data, "data");
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ContractEvent::_body_t> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ContractEvent::_body_t;
  using case_type = ::stellar::ContractEvent::_body_t::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

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

  static std::size_t serial_size(const ::stellar::ContractEvent::_body_t &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in _body_t");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ContractEvent::_body_t &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in _body_t");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ContractEvent::_body_t &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.v(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
template<> struct xdr_traits<::stellar::ContractEvent>
  : xdr_struct_base<field_ptr<::stellar::ContractEvent,
                              decltype(::stellar::ContractEvent::ext),
                              &::stellar::ContractEvent::ext>,
                    field_ptr<::stellar::ContractEvent,
                              decltype(::stellar::ContractEvent::contractID),
                              &::stellar::ContractEvent::contractID>,
                    field_ptr<::stellar::ContractEvent,
                              decltype(::stellar::ContractEvent::type),
                              &::stellar::ContractEvent::type>,
                    field_ptr<::stellar::ContractEvent,
                              decltype(::stellar::ContractEvent::body),
                              &::stellar::ContractEvent::body>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ContractEvent &obj) {
    archive(ar, obj.ext, "ext");
    archive(ar, obj.contractID, "contractID");
    archive(ar, obj.type, "type");
    archive(ar, obj.body, "body");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ContractEvent &obj) {
    archive(ar, obj.ext, "ext");
    archive(ar, obj.contractID, "contractID");
    archive(ar, obj.type, "type");
    archive(ar, obj.body, "body");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct DiagnosticEvent {
  bool inSuccessfulContractCall{};
  ContractEvent event{};

  DiagnosticEvent() = default;
  template<typename _inSuccessfulContractCall_T,
           typename _event_T,
           typename = typename
           std::enable_if<std::is_constructible<bool, _inSuccessfulContractCall_T>::value
                          && std::is_constructible<ContractEvent, _event_T>::value
                         >::type>
  explicit DiagnosticEvent(_inSuccessfulContractCall_T &&_inSuccessfulContractCall,
                           _event_T &&_event)
    : inSuccessfulContractCall(std::forward<_inSuccessfulContractCall_T>(_inSuccessfulContractCall)),
      event(std::forward<_event_T>(_event)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::DiagnosticEvent>
  : xdr_struct_base<field_ptr<::stellar::DiagnosticEvent,
                              decltype(::stellar::DiagnosticEvent::inSuccessfulContractCall),
                              &::stellar::DiagnosticEvent::inSuccessfulContractCall>,
                    field_ptr<::stellar::DiagnosticEvent,
                              decltype(::stellar::DiagnosticEvent::event),
                              &::stellar::DiagnosticEvent::event>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::DiagnosticEvent &obj) {
    archive(ar, obj.inSuccessfulContractCall, "inSuccessfulContractCall");
    archive(ar, obj.event, "event");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::DiagnosticEvent &obj) {
    archive(ar, obj.inSuccessfulContractCall, "inSuccessfulContractCall");
    archive(ar, obj.event, "event");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct SorobanTransactionMetaExtV1 {
  ExtensionPoint ext{};
  int64 totalNonRefundableResourceFeeCharged{};
  int64 totalRefundableResourceFeeCharged{};
  int64 rentFeeCharged{};

  SorobanTransactionMetaExtV1() = default;
  template<typename _ext_T,
           typename _totalNonRefundableResourceFeeCharged_T,
           typename _totalRefundableResourceFeeCharged_T,
           typename _rentFeeCharged_T,
           typename = typename
           std::enable_if<std::is_constructible<ExtensionPoint, _ext_T>::value
                          && std::is_constructible<int64, _totalNonRefundableResourceFeeCharged_T>::value
                          && std::is_constructible<int64, _totalRefundableResourceFeeCharged_T>::value
                          && std::is_constructible<int64, _rentFeeCharged_T>::value
                         >::type>
  explicit SorobanTransactionMetaExtV1(_ext_T &&_ext,
                                       _totalNonRefundableResourceFeeCharged_T &&_totalNonRefundableResourceFeeCharged,
                                       _totalRefundableResourceFeeCharged_T &&_totalRefundableResourceFeeCharged,
                                       _rentFeeCharged_T &&_rentFeeCharged)
    : ext(std::forward<_ext_T>(_ext)),
      totalNonRefundableResourceFeeCharged(std::forward<_totalNonRefundableResourceFeeCharged_T>(_totalNonRefundableResourceFeeCharged)),
      totalRefundableResourceFeeCharged(std::forward<_totalRefundableResourceFeeCharged_T>(_totalRefundableResourceFeeCharged)),
      rentFeeCharged(std::forward<_rentFeeCharged_T>(_rentFeeCharged)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SorobanTransactionMetaExtV1>
  : xdr_struct_base<field_ptr<::stellar::SorobanTransactionMetaExtV1,
                              decltype(::stellar::SorobanTransactionMetaExtV1::ext),
                              &::stellar::SorobanTransactionMetaExtV1::ext>,
                    field_ptr<::stellar::SorobanTransactionMetaExtV1,
                              decltype(::stellar::SorobanTransactionMetaExtV1::totalNonRefundableResourceFeeCharged),
                              &::stellar::SorobanTransactionMetaExtV1::totalNonRefundableResourceFeeCharged>,
                    field_ptr<::stellar::SorobanTransactionMetaExtV1,
                              decltype(::stellar::SorobanTransactionMetaExtV1::totalRefundableResourceFeeCharged),
                              &::stellar::SorobanTransactionMetaExtV1::totalRefundableResourceFeeCharged>,
                    field_ptr<::stellar::SorobanTransactionMetaExtV1,
                              decltype(::stellar::SorobanTransactionMetaExtV1::rentFeeCharged),
                              &::stellar::SorobanTransactionMetaExtV1::rentFeeCharged>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SorobanTransactionMetaExtV1 &obj) {
    archive(ar, obj.ext, "ext");
    archive(ar, obj.totalNonRefundableResourceFeeCharged, "totalNonRefundableResourceFeeCharged");
    archive(ar, obj.totalRefundableResourceFeeCharged, "totalRefundableResourceFeeCharged");
    archive(ar, obj.rentFeeCharged, "rentFeeCharged");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SorobanTransactionMetaExtV1 &obj) {
    archive(ar, obj.ext, "ext");
    archive(ar, obj.totalNonRefundableResourceFeeCharged, "totalNonRefundableResourceFeeCharged");
    archive(ar, obj.totalRefundableResourceFeeCharged, "totalRefundableResourceFeeCharged");
    archive(ar, obj.rentFeeCharged, "rentFeeCharged");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct SorobanTransactionMetaExt {
  using _xdr_case_type = xdr::xdr_traits<int>::case_type;
private:
  _xdr_case_type v_;
  union {
    SorobanTransactionMetaExtV1 v1_;
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
      _f(&SorobanTransactionMetaExt::v1_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return v_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of v in SorobanTransactionMetaExt");
    if (fnum != _xdr_field_number(v_)) {
      this->~SorobanTransactionMetaExt();
      v_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
    }
    else
      v_ = which;
  }
  explicit SorobanTransactionMetaExt(std::int32_t which = std::int32_t{}) : v_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
  }
  SorobanTransactionMetaExt(const SorobanTransactionMetaExt &source) : v_(source.v_) {
    _xdr_with_mem_ptr(xdr::field_constructor, v_, *this, source);
  }
  SorobanTransactionMetaExt(SorobanTransactionMetaExt &&source) : v_(source.v_) {
    _xdr_with_mem_ptr(xdr::field_constructor, v_, *this,
                      std::move(source));
  }
  ~SorobanTransactionMetaExt() { _xdr_with_mem_ptr(xdr::field_destructor, v_, *this); }
  SorobanTransactionMetaExt &operator=(const SorobanTransactionMetaExt &source) {
    if (_xdr_field_number(v_)
        == _xdr_field_number(source.v_))
      _xdr_with_mem_ptr(xdr::field_assigner, v_, *this, source);
    else {
      this->~SorobanTransactionMetaExt();
      v_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this, source);
    }
    v_ = source.v_;
    return *this;
  }
  SorobanTransactionMetaExt &operator=(SorobanTransactionMetaExt &&source) {
    if (_xdr_field_number(v_)
         == _xdr_field_number(source.v_))
      _xdr_with_mem_ptr(xdr::field_assigner, v_, *this,
                        std::move(source));
    else {
      this->~SorobanTransactionMetaExt();
      v_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this,
                        std::move(source));
    }
    v_ = source.v_;
    return *this;
  }

  std::int32_t v() const { return std::int32_t(v_); }
  SorobanTransactionMetaExt &v(int _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  SorobanTransactionMetaExtV1 &v1() {
    if (_xdr_field_number(v_) == 1)
      return v1_;
    throw xdr::xdr_wrong_union("SorobanTransactionMetaExt: v1 accessed when not selected");
  }
  const SorobanTransactionMetaExtV1 &v1() const {
    if (_xdr_field_number(v_) == 1)
      return v1_;
    throw xdr::xdr_wrong_union("SorobanTransactionMetaExt: v1 accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SorobanTransactionMetaExt> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::SorobanTransactionMetaExt;
  using case_type = ::stellar::SorobanTransactionMetaExt::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

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

  static std::size_t serial_size(const ::stellar::SorobanTransactionMetaExt &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in SorobanTransactionMetaExt");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SorobanTransactionMetaExt &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in SorobanTransactionMetaExt");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SorobanTransactionMetaExt &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.v(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

struct SorobanTransactionMeta {
  SorobanTransactionMetaExt ext{};
  xdr::xvector<ContractEvent> events{};
  SCVal returnValue{};
  xdr::xvector<DiagnosticEvent> diagnosticEvents{};

  SorobanTransactionMeta() = default;
  template<typename _ext_T,
           typename _events_T,
           typename _returnValue_T,
           typename _diagnosticEvents_T,
           typename = typename
           std::enable_if<std::is_constructible<SorobanTransactionMetaExt, _ext_T>::value
                          && std::is_constructible<xdr::xvector<ContractEvent>, _events_T>::value
                          && std::is_constructible<SCVal, _returnValue_T>::value
                          && std::is_constructible<xdr::xvector<DiagnosticEvent>, _diagnosticEvents_T>::value
                         >::type>
  explicit SorobanTransactionMeta(_ext_T &&_ext,
                                  _events_T &&_events,
                                  _returnValue_T &&_returnValue,
                                  _diagnosticEvents_T &&_diagnosticEvents)
    : ext(std::forward<_ext_T>(_ext)),
      events(std::forward<_events_T>(_events)),
      returnValue(std::forward<_returnValue_T>(_returnValue)),
      diagnosticEvents(std::forward<_diagnosticEvents_T>(_diagnosticEvents)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SorobanTransactionMeta>
  : xdr_struct_base<field_ptr<::stellar::SorobanTransactionMeta,
                              decltype(::stellar::SorobanTransactionMeta::ext),
                              &::stellar::SorobanTransactionMeta::ext>,
                    field_ptr<::stellar::SorobanTransactionMeta,
                              decltype(::stellar::SorobanTransactionMeta::events),
                              &::stellar::SorobanTransactionMeta::events>,
                    field_ptr<::stellar::SorobanTransactionMeta,
                              decltype(::stellar::SorobanTransactionMeta::returnValue),
                              &::stellar::SorobanTransactionMeta::returnValue>,
                    field_ptr<::stellar::SorobanTransactionMeta,
                              decltype(::stellar::SorobanTransactionMeta::diagnosticEvents),
                              &::stellar::SorobanTransactionMeta::diagnosticEvents>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SorobanTransactionMeta &obj) {
    archive(ar, obj.ext, "ext");
    archive(ar, obj.events, "events");
    archive(ar, obj.returnValue, "returnValue");
    archive(ar, obj.diagnosticEvents, "diagnosticEvents");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SorobanTransactionMeta &obj) {
    archive(ar, obj.ext, "ext");
    archive(ar, obj.events, "events");
    archive(ar, obj.returnValue, "returnValue");
    archive(ar, obj.diagnosticEvents, "diagnosticEvents");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct TransactionMetaV3 {
  ExtensionPoint ext{};
  LedgerEntryChanges txChangesBefore{};
  xdr::xvector<OperationMeta> operations{};
  LedgerEntryChanges txChangesAfter{};
  xdr::pointer<SorobanTransactionMeta> sorobanMeta{};

  TransactionMetaV3() = default;
  template<typename _ext_T,
           typename _txChangesBefore_T,
           typename _operations_T,
           typename _txChangesAfter_T,
           typename _sorobanMeta_T,
           typename = typename
           std::enable_if<std::is_constructible<ExtensionPoint, _ext_T>::value
                          && std::is_constructible<LedgerEntryChanges, _txChangesBefore_T>::value
                          && std::is_constructible<xdr::xvector<OperationMeta>, _operations_T>::value
                          && std::is_constructible<LedgerEntryChanges, _txChangesAfter_T>::value
                          && std::is_constructible<xdr::pointer<SorobanTransactionMeta>, _sorobanMeta_T>::value
                         >::type>
  explicit TransactionMetaV3(_ext_T &&_ext,
                             _txChangesBefore_T &&_txChangesBefore,
                             _operations_T &&_operations,
                             _txChangesAfter_T &&_txChangesAfter,
                             _sorobanMeta_T &&_sorobanMeta)
    : ext(std::forward<_ext_T>(_ext)),
      txChangesBefore(std::forward<_txChangesBefore_T>(_txChangesBefore)),
      operations(std::forward<_operations_T>(_operations)),
      txChangesAfter(std::forward<_txChangesAfter_T>(_txChangesAfter)),
      sorobanMeta(std::forward<_sorobanMeta_T>(_sorobanMeta)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::TransactionMetaV3>
  : xdr_struct_base<field_ptr<::stellar::TransactionMetaV3,
                              decltype(::stellar::TransactionMetaV3::ext),
                              &::stellar::TransactionMetaV3::ext>,
                    field_ptr<::stellar::TransactionMetaV3,
                              decltype(::stellar::TransactionMetaV3::txChangesBefore),
                              &::stellar::TransactionMetaV3::txChangesBefore>,
                    field_ptr<::stellar::TransactionMetaV3,
                              decltype(::stellar::TransactionMetaV3::operations),
                              &::stellar::TransactionMetaV3::operations>,
                    field_ptr<::stellar::TransactionMetaV3,
                              decltype(::stellar::TransactionMetaV3::txChangesAfter),
                              &::stellar::TransactionMetaV3::txChangesAfter>,
                    field_ptr<::stellar::TransactionMetaV3,
                              decltype(::stellar::TransactionMetaV3::sorobanMeta),
                              &::stellar::TransactionMetaV3::sorobanMeta>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::TransactionMetaV3 &obj) {
    archive(ar, obj.ext, "ext");
    archive(ar, obj.txChangesBefore, "txChangesBefore");
    archive(ar, obj.operations, "operations");
    archive(ar, obj.txChangesAfter, "txChangesAfter");
    archive(ar, obj.sorobanMeta, "sorobanMeta");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::TransactionMetaV3 &obj) {
    archive(ar, obj.ext, "ext");
    archive(ar, obj.txChangesBefore, "txChangesBefore");
    archive(ar, obj.operations, "operations");
    archive(ar, obj.txChangesAfter, "txChangesAfter");
    archive(ar, obj.sorobanMeta, "sorobanMeta");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct OperationMetaV2 {
  ExtensionPoint ext{};
  LedgerEntryChanges changes{};
  xdr::xvector<ContractEvent> events{};

  OperationMetaV2() = default;
  template<typename _ext_T,
           typename _changes_T,
           typename _events_T,
           typename = typename
           std::enable_if<std::is_constructible<ExtensionPoint, _ext_T>::value
                          && std::is_constructible<LedgerEntryChanges, _changes_T>::value
                          && std::is_constructible<xdr::xvector<ContractEvent>, _events_T>::value
                         >::type>
  explicit OperationMetaV2(_ext_T &&_ext,
                           _changes_T &&_changes,
                           _events_T &&_events)
    : ext(std::forward<_ext_T>(_ext)),
      changes(std::forward<_changes_T>(_changes)),
      events(std::forward<_events_T>(_events)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::OperationMetaV2>
  : xdr_struct_base<field_ptr<::stellar::OperationMetaV2,
                              decltype(::stellar::OperationMetaV2::ext),
                              &::stellar::OperationMetaV2::ext>,
                    field_ptr<::stellar::OperationMetaV2,
                              decltype(::stellar::OperationMetaV2::changes),
                              &::stellar::OperationMetaV2::changes>,
                    field_ptr<::stellar::OperationMetaV2,
                              decltype(::stellar::OperationMetaV2::events),
                              &::stellar::OperationMetaV2::events>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::OperationMetaV2 &obj) {
    archive(ar, obj.ext, "ext");
    archive(ar, obj.changes, "changes");
    archive(ar, obj.events, "events");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::OperationMetaV2 &obj) {
    archive(ar, obj.ext, "ext");
    archive(ar, obj.changes, "changes");
    archive(ar, obj.events, "events");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct SorobanTransactionMetaV2 {
  SorobanTransactionMetaExt ext{};
  xdr::pointer<SCVal> returnValue{};

  SorobanTransactionMetaV2() = default;
  template<typename _ext_T,
           typename _returnValue_T,
           typename = typename
           std::enable_if<std::is_constructible<SorobanTransactionMetaExt, _ext_T>::value
                          && std::is_constructible<xdr::pointer<SCVal>, _returnValue_T>::value
                         >::type>
  explicit SorobanTransactionMetaV2(_ext_T &&_ext,
                                    _returnValue_T &&_returnValue)
    : ext(std::forward<_ext_T>(_ext)),
      returnValue(std::forward<_returnValue_T>(_returnValue)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::SorobanTransactionMetaV2>
  : xdr_struct_base<field_ptr<::stellar::SorobanTransactionMetaV2,
                              decltype(::stellar::SorobanTransactionMetaV2::ext),
                              &::stellar::SorobanTransactionMetaV2::ext>,
                    field_ptr<::stellar::SorobanTransactionMetaV2,
                              decltype(::stellar::SorobanTransactionMetaV2::returnValue),
                              &::stellar::SorobanTransactionMetaV2::returnValue>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::SorobanTransactionMetaV2 &obj) {
    archive(ar, obj.ext, "ext");
    archive(ar, obj.returnValue, "returnValue");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::SorobanTransactionMetaV2 &obj) {
    archive(ar, obj.ext, "ext");
    archive(ar, obj.returnValue, "returnValue");
    xdr::validate(obj);
  }
};
} namespace stellar {

enum TransactionEventStage : std::int32_t {
  TRANSACTION_EVENT_STAGE_BEFORE_ALL_TXS = 0,
  TRANSACTION_EVENT_STAGE_AFTER_TX = 1,
  TRANSACTION_EVENT_STAGE_AFTER_ALL_TXS = 2,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::TransactionEventStage>
  : xdr_integral_base<::stellar::TransactionEventStage, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::TransactionEventStage val) {
    switch (val) {
    case ::stellar::TRANSACTION_EVENT_STAGE_BEFORE_ALL_TXS:
      return "TRANSACTION_EVENT_STAGE_BEFORE_ALL_TXS";
    case ::stellar::TRANSACTION_EVENT_STAGE_AFTER_TX:
      return "TRANSACTION_EVENT_STAGE_AFTER_TX";
    case ::stellar::TRANSACTION_EVENT_STAGE_AFTER_ALL_TXS:
      return "TRANSACTION_EVENT_STAGE_AFTER_ALL_TXS";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::TRANSACTION_EVENT_STAGE_BEFORE_ALL_TXS,
      ::stellar::TRANSACTION_EVENT_STAGE_AFTER_TX,
      ::stellar::TRANSACTION_EVENT_STAGE_AFTER_ALL_TXS
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct TransactionEvent {
  TransactionEventStage stage{};
  ContractEvent event{};

  TransactionEvent() = default;
  template<typename _stage_T,
           typename _event_T,
           typename = typename
           std::enable_if<std::is_constructible<TransactionEventStage, _stage_T>::value
                          && std::is_constructible<ContractEvent, _event_T>::value
                         >::type>
  explicit TransactionEvent(_stage_T &&_stage,
                            _event_T &&_event)
    : stage(std::forward<_stage_T>(_stage)),
      event(std::forward<_event_T>(_event)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::TransactionEvent>
  : xdr_struct_base<field_ptr<::stellar::TransactionEvent,
                              decltype(::stellar::TransactionEvent::stage),
                              &::stellar::TransactionEvent::stage>,
                    field_ptr<::stellar::TransactionEvent,
                              decltype(::stellar::TransactionEvent::event),
                              &::stellar::TransactionEvent::event>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::TransactionEvent &obj) {
    archive(ar, obj.stage, "stage");
    archive(ar, obj.event, "event");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::TransactionEvent &obj) {
    archive(ar, obj.stage, "stage");
    archive(ar, obj.event, "event");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct TransactionMetaV4 {
  ExtensionPoint ext{};
  LedgerEntryChanges txChangesBefore{};
  xdr::xvector<OperationMetaV2> operations{};
  LedgerEntryChanges txChangesAfter{};
  xdr::pointer<SorobanTransactionMetaV2> sorobanMeta{};
  xdr::xvector<TransactionEvent> events{};
  xdr::xvector<DiagnosticEvent> diagnosticEvents{};

  TransactionMetaV4() = default;
  template<typename _ext_T,
           typename _txChangesBefore_T,
           typename _operations_T,
           typename _txChangesAfter_T,
           typename _sorobanMeta_T,
           typename _events_T,
           typename _diagnosticEvents_T,
           typename = typename
           std::enable_if<std::is_constructible<ExtensionPoint, _ext_T>::value
                          && std::is_constructible<LedgerEntryChanges, _txChangesBefore_T>::value
                          && std::is_constructible<xdr::xvector<OperationMetaV2>, _operations_T>::value
                          && std::is_constructible<LedgerEntryChanges, _txChangesAfter_T>::value
                          && std::is_constructible<xdr::pointer<SorobanTransactionMetaV2>, _sorobanMeta_T>::value
                          && std::is_constructible<xdr::xvector<TransactionEvent>, _events_T>::value
                          && std::is_constructible<xdr::xvector<DiagnosticEvent>, _diagnosticEvents_T>::value
                         >::type>
  explicit TransactionMetaV4(_ext_T &&_ext,
                             _txChangesBefore_T &&_txChangesBefore,
                             _operations_T &&_operations,
                             _txChangesAfter_T &&_txChangesAfter,
                             _sorobanMeta_T &&_sorobanMeta,
                             _events_T &&_events,
                             _diagnosticEvents_T &&_diagnosticEvents)
    : ext(std::forward<_ext_T>(_ext)),
      txChangesBefore(std::forward<_txChangesBefore_T>(_txChangesBefore)),
      operations(std::forward<_operations_T>(_operations)),
      txChangesAfter(std::forward<_txChangesAfter_T>(_txChangesAfter)),
      sorobanMeta(std::forward<_sorobanMeta_T>(_sorobanMeta)),
      events(std::forward<_events_T>(_events)),
      diagnosticEvents(std::forward<_diagnosticEvents_T>(_diagnosticEvents)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::TransactionMetaV4>
  : xdr_struct_base<field_ptr<::stellar::TransactionMetaV4,
                              decltype(::stellar::TransactionMetaV4::ext),
                              &::stellar::TransactionMetaV4::ext>,
                    field_ptr<::stellar::TransactionMetaV4,
                              decltype(::stellar::TransactionMetaV4::txChangesBefore),
                              &::stellar::TransactionMetaV4::txChangesBefore>,
                    field_ptr<::stellar::TransactionMetaV4,
                              decltype(::stellar::TransactionMetaV4::operations),
                              &::stellar::TransactionMetaV4::operations>,
                    field_ptr<::stellar::TransactionMetaV4,
                              decltype(::stellar::TransactionMetaV4::txChangesAfter),
                              &::stellar::TransactionMetaV4::txChangesAfter>,
                    field_ptr<::stellar::TransactionMetaV4,
                              decltype(::stellar::TransactionMetaV4::sorobanMeta),
                              &::stellar::TransactionMetaV4::sorobanMeta>,
                    field_ptr<::stellar::TransactionMetaV4,
                              decltype(::stellar::TransactionMetaV4::events),
                              &::stellar::TransactionMetaV4::events>,
                    field_ptr<::stellar::TransactionMetaV4,
                              decltype(::stellar::TransactionMetaV4::diagnosticEvents),
                              &::stellar::TransactionMetaV4::diagnosticEvents>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::TransactionMetaV4 &obj) {
    archive(ar, obj.ext, "ext");
    archive(ar, obj.txChangesBefore, "txChangesBefore");
    archive(ar, obj.operations, "operations");
    archive(ar, obj.txChangesAfter, "txChangesAfter");
    archive(ar, obj.sorobanMeta, "sorobanMeta");
    archive(ar, obj.events, "events");
    archive(ar, obj.diagnosticEvents, "diagnosticEvents");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::TransactionMetaV4 &obj) {
    archive(ar, obj.ext, "ext");
    archive(ar, obj.txChangesBefore, "txChangesBefore");
    archive(ar, obj.operations, "operations");
    archive(ar, obj.txChangesAfter, "txChangesAfter");
    archive(ar, obj.sorobanMeta, "sorobanMeta");
    archive(ar, obj.events, "events");
    archive(ar, obj.diagnosticEvents, "diagnosticEvents");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct InvokeHostFunctionSuccessPreImage {
  SCVal returnValue{};
  xdr::xvector<ContractEvent> events{};

  InvokeHostFunctionSuccessPreImage() = default;
  template<typename _returnValue_T,
           typename _events_T,
           typename = typename
           std::enable_if<std::is_constructible<SCVal, _returnValue_T>::value
                          && std::is_constructible<xdr::xvector<ContractEvent>, _events_T>::value
                         >::type>
  explicit InvokeHostFunctionSuccessPreImage(_returnValue_T &&_returnValue,
                                             _events_T &&_events)
    : returnValue(std::forward<_returnValue_T>(_returnValue)),
      events(std::forward<_events_T>(_events)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::InvokeHostFunctionSuccessPreImage>
  : xdr_struct_base<field_ptr<::stellar::InvokeHostFunctionSuccessPreImage,
                              decltype(::stellar::InvokeHostFunctionSuccessPreImage::returnValue),
                              &::stellar::InvokeHostFunctionSuccessPreImage::returnValue>,
                    field_ptr<::stellar::InvokeHostFunctionSuccessPreImage,
                              decltype(::stellar::InvokeHostFunctionSuccessPreImage::events),
                              &::stellar::InvokeHostFunctionSuccessPreImage::events>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::InvokeHostFunctionSuccessPreImage &obj) {
    archive(ar, obj.returnValue, "returnValue");
    archive(ar, obj.events, "events");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::InvokeHostFunctionSuccessPreImage &obj) {
    archive(ar, obj.returnValue, "returnValue");
    archive(ar, obj.events, "events");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct TransactionMeta {
  using _xdr_case_type = xdr::xdr_traits<int>::case_type;
private:
  _xdr_case_type v_;
  union {
    xdr::xvector<OperationMeta> operations_;
    TransactionMetaV1 v1_;
    TransactionMetaV2 v2_;
    TransactionMetaV3 v3_;
    TransactionMetaV4 v4_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<int> &_xdr_case_values() {
    static const std::vector<int> _xdr_disc_vec {
      0,
      1,
      2,
      3,
      4
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == 0 ? 1
      : which == 1 ? 2
      : which == 2 ? 3
      : which == 3 ? 4
      : which == 4 ? 5
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case 0:
      _f(&TransactionMeta::operations_, std::forward<_A>(_a)...);
      return true;
    case 1:
      _f(&TransactionMeta::v1_, std::forward<_A>(_a)...);
      return true;
    case 2:
      _f(&TransactionMeta::v2_, std::forward<_A>(_a)...);
      return true;
    case 3:
      _f(&TransactionMeta::v3_, std::forward<_A>(_a)...);
      return true;
    case 4:
      _f(&TransactionMeta::v4_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return v_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of v in TransactionMeta");
    if (fnum != _xdr_field_number(v_)) {
      this->~TransactionMeta();
      v_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
    }
    else
      v_ = which;
  }
  explicit TransactionMeta(std::int32_t which = std::int32_t{}) : v_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
  }
  TransactionMeta(const TransactionMeta &source) : v_(source.v_) {
    _xdr_with_mem_ptr(xdr::field_constructor, v_, *this, source);
  }
  TransactionMeta(TransactionMeta &&source) : v_(source.v_) {
    _xdr_with_mem_ptr(xdr::field_constructor, v_, *this,
                      std::move(source));
  }
  ~TransactionMeta() { _xdr_with_mem_ptr(xdr::field_destructor, v_, *this); }
  TransactionMeta &operator=(const TransactionMeta &source) {
    if (_xdr_field_number(v_)
        == _xdr_field_number(source.v_))
      _xdr_with_mem_ptr(xdr::field_assigner, v_, *this, source);
    else {
      this->~TransactionMeta();
      v_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this, source);
    }
    v_ = source.v_;
    return *this;
  }
  TransactionMeta &operator=(TransactionMeta &&source) {
    if (_xdr_field_number(v_)
         == _xdr_field_number(source.v_))
      _xdr_with_mem_ptr(xdr::field_assigner, v_, *this,
                        std::move(source));
    else {
      this->~TransactionMeta();
      v_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this,
                        std::move(source));
    }
    v_ = source.v_;
    return *this;
  }

  std::int32_t v() const { return std::int32_t(v_); }
  TransactionMeta &v(int _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  xdr::xvector<OperationMeta> &operations() {
    if (_xdr_field_number(v_) == 1)
      return operations_;
    throw xdr::xdr_wrong_union("TransactionMeta: operations accessed when not selected");
  }
  const xdr::xvector<OperationMeta> &operations() const {
    if (_xdr_field_number(v_) == 1)
      return operations_;
    throw xdr::xdr_wrong_union("TransactionMeta: operations accessed when not selected");
  }
  TransactionMetaV1 &v1() {
    if (_xdr_field_number(v_) == 2)
      return v1_;
    throw xdr::xdr_wrong_union("TransactionMeta: v1 accessed when not selected");
  }
  const TransactionMetaV1 &v1() const {
    if (_xdr_field_number(v_) == 2)
      return v1_;
    throw xdr::xdr_wrong_union("TransactionMeta: v1 accessed when not selected");
  }
  TransactionMetaV2 &v2() {
    if (_xdr_field_number(v_) == 3)
      return v2_;
    throw xdr::xdr_wrong_union("TransactionMeta: v2 accessed when not selected");
  }
  const TransactionMetaV2 &v2() const {
    if (_xdr_field_number(v_) == 3)
      return v2_;
    throw xdr::xdr_wrong_union("TransactionMeta: v2 accessed when not selected");
  }
  TransactionMetaV3 &v3() {
    if (_xdr_field_number(v_) == 4)
      return v3_;
    throw xdr::xdr_wrong_union("TransactionMeta: v3 accessed when not selected");
  }
  const TransactionMetaV3 &v3() const {
    if (_xdr_field_number(v_) == 4)
      return v3_;
    throw xdr::xdr_wrong_union("TransactionMeta: v3 accessed when not selected");
  }
  TransactionMetaV4 &v4() {
    if (_xdr_field_number(v_) == 5)
      return v4_;
    throw xdr::xdr_wrong_union("TransactionMeta: v4 accessed when not selected");
  }
  const TransactionMetaV4 &v4() const {
    if (_xdr_field_number(v_) == 5)
      return v4_;
    throw xdr::xdr_wrong_union("TransactionMeta: v4 accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::TransactionMeta> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::TransactionMeta;
  using case_type = ::stellar::TransactionMeta::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "operations";
    case 2:
      return "v1";
    case 3:
      return "v2";
    case 4:
      return "v3";
    case 5:
      return "v4";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::TransactionMeta &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in TransactionMeta");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::TransactionMeta &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in TransactionMeta");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::TransactionMeta &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.v(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

struct TransactionResultMeta {
  TransactionResultPair result{};
  LedgerEntryChanges feeProcessing{};
  TransactionMeta txApplyProcessing{};

  TransactionResultMeta() = default;
  template<typename _result_T,
           typename _feeProcessing_T,
           typename _txApplyProcessing_T,
           typename = typename
           std::enable_if<std::is_constructible<TransactionResultPair, _result_T>::value
                          && std::is_constructible<LedgerEntryChanges, _feeProcessing_T>::value
                          && std::is_constructible<TransactionMeta, _txApplyProcessing_T>::value
                         >::type>
  explicit TransactionResultMeta(_result_T &&_result,
                                 _feeProcessing_T &&_feeProcessing,
                                 _txApplyProcessing_T &&_txApplyProcessing)
    : result(std::forward<_result_T>(_result)),
      feeProcessing(std::forward<_feeProcessing_T>(_feeProcessing)),
      txApplyProcessing(std::forward<_txApplyProcessing_T>(_txApplyProcessing)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::TransactionResultMeta>
  : xdr_struct_base<field_ptr<::stellar::TransactionResultMeta,
                              decltype(::stellar::TransactionResultMeta::result),
                              &::stellar::TransactionResultMeta::result>,
                    field_ptr<::stellar::TransactionResultMeta,
                              decltype(::stellar::TransactionResultMeta::feeProcessing),
                              &::stellar::TransactionResultMeta::feeProcessing>,
                    field_ptr<::stellar::TransactionResultMeta,
                              decltype(::stellar::TransactionResultMeta::txApplyProcessing),
                              &::stellar::TransactionResultMeta::txApplyProcessing>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::TransactionResultMeta &obj) {
    archive(ar, obj.result, "result");
    archive(ar, obj.feeProcessing, "feeProcessing");
    archive(ar, obj.txApplyProcessing, "txApplyProcessing");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::TransactionResultMeta &obj) {
    archive(ar, obj.result, "result");
    archive(ar, obj.feeProcessing, "feeProcessing");
    archive(ar, obj.txApplyProcessing, "txApplyProcessing");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct TransactionResultMetaV1 {
  ExtensionPoint ext{};
  TransactionResultPair result{};
  LedgerEntryChanges feeProcessing{};
  TransactionMeta txApplyProcessing{};
  LedgerEntryChanges postTxApplyFeeProcessing{};

  TransactionResultMetaV1() = default;
  template<typename _ext_T,
           typename _result_T,
           typename _feeProcessing_T,
           typename _txApplyProcessing_T,
           typename _postTxApplyFeeProcessing_T,
           typename = typename
           std::enable_if<std::is_constructible<ExtensionPoint, _ext_T>::value
                          && std::is_constructible<TransactionResultPair, _result_T>::value
                          && std::is_constructible<LedgerEntryChanges, _feeProcessing_T>::value
                          && std::is_constructible<TransactionMeta, _txApplyProcessing_T>::value
                          && std::is_constructible<LedgerEntryChanges, _postTxApplyFeeProcessing_T>::value
                         >::type>
  explicit TransactionResultMetaV1(_ext_T &&_ext,
                                   _result_T &&_result,
                                   _feeProcessing_T &&_feeProcessing,
                                   _txApplyProcessing_T &&_txApplyProcessing,
                                   _postTxApplyFeeProcessing_T &&_postTxApplyFeeProcessing)
    : ext(std::forward<_ext_T>(_ext)),
      result(std::forward<_result_T>(_result)),
      feeProcessing(std::forward<_feeProcessing_T>(_feeProcessing)),
      txApplyProcessing(std::forward<_txApplyProcessing_T>(_txApplyProcessing)),
      postTxApplyFeeProcessing(std::forward<_postTxApplyFeeProcessing_T>(_postTxApplyFeeProcessing)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::TransactionResultMetaV1>
  : xdr_struct_base<field_ptr<::stellar::TransactionResultMetaV1,
                              decltype(::stellar::TransactionResultMetaV1::ext),
                              &::stellar::TransactionResultMetaV1::ext>,
                    field_ptr<::stellar::TransactionResultMetaV1,
                              decltype(::stellar::TransactionResultMetaV1::result),
                              &::stellar::TransactionResultMetaV1::result>,
                    field_ptr<::stellar::TransactionResultMetaV1,
                              decltype(::stellar::TransactionResultMetaV1::feeProcessing),
                              &::stellar::TransactionResultMetaV1::feeProcessing>,
                    field_ptr<::stellar::TransactionResultMetaV1,
                              decltype(::stellar::TransactionResultMetaV1::txApplyProcessing),
                              &::stellar::TransactionResultMetaV1::txApplyProcessing>,
                    field_ptr<::stellar::TransactionResultMetaV1,
                              decltype(::stellar::TransactionResultMetaV1::postTxApplyFeeProcessing),
                              &::stellar::TransactionResultMetaV1::postTxApplyFeeProcessing>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::TransactionResultMetaV1 &obj) {
    archive(ar, obj.ext, "ext");
    archive(ar, obj.result, "result");
    archive(ar, obj.feeProcessing, "feeProcessing");
    archive(ar, obj.txApplyProcessing, "txApplyProcessing");
    archive(ar, obj.postTxApplyFeeProcessing, "postTxApplyFeeProcessing");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::TransactionResultMetaV1 &obj) {
    archive(ar, obj.ext, "ext");
    archive(ar, obj.result, "result");
    archive(ar, obj.feeProcessing, "feeProcessing");
    archive(ar, obj.txApplyProcessing, "txApplyProcessing");
    archive(ar, obj.postTxApplyFeeProcessing, "postTxApplyFeeProcessing");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct UpgradeEntryMeta {
  LedgerUpgrade upgrade{};
  LedgerEntryChanges changes{};

  UpgradeEntryMeta() = default;
  template<typename _upgrade_T,
           typename _changes_T,
           typename = typename
           std::enable_if<std::is_constructible<LedgerUpgrade, _upgrade_T>::value
                          && std::is_constructible<LedgerEntryChanges, _changes_T>::value
                         >::type>
  explicit UpgradeEntryMeta(_upgrade_T &&_upgrade,
                            _changes_T &&_changes)
    : upgrade(std::forward<_upgrade_T>(_upgrade)),
      changes(std::forward<_changes_T>(_changes)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::UpgradeEntryMeta>
  : xdr_struct_base<field_ptr<::stellar::UpgradeEntryMeta,
                              decltype(::stellar::UpgradeEntryMeta::upgrade),
                              &::stellar::UpgradeEntryMeta::upgrade>,
                    field_ptr<::stellar::UpgradeEntryMeta,
                              decltype(::stellar::UpgradeEntryMeta::changes),
                              &::stellar::UpgradeEntryMeta::changes>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::UpgradeEntryMeta &obj) {
    archive(ar, obj.upgrade, "upgrade");
    archive(ar, obj.changes, "changes");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::UpgradeEntryMeta &obj) {
    archive(ar, obj.upgrade, "upgrade");
    archive(ar, obj.changes, "changes");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct LedgerCloseMetaV0 {
  LedgerHeaderHistoryEntry ledgerHeader{};
  TransactionSet txSet{};
  xdr::xvector<TransactionResultMeta> txProcessing{};
  xdr::xvector<UpgradeEntryMeta> upgradesProcessing{};
  xdr::xvector<SCPHistoryEntry> scpInfo{};

  LedgerCloseMetaV0() = default;
  template<typename _ledgerHeader_T,
           typename _txSet_T,
           typename _txProcessing_T,
           typename _upgradesProcessing_T,
           typename _scpInfo_T,
           typename = typename
           std::enable_if<std::is_constructible<LedgerHeaderHistoryEntry, _ledgerHeader_T>::value
                          && std::is_constructible<TransactionSet, _txSet_T>::value
                          && std::is_constructible<xdr::xvector<TransactionResultMeta>, _txProcessing_T>::value
                          && std::is_constructible<xdr::xvector<UpgradeEntryMeta>, _upgradesProcessing_T>::value
                          && std::is_constructible<xdr::xvector<SCPHistoryEntry>, _scpInfo_T>::value
                         >::type>
  explicit LedgerCloseMetaV0(_ledgerHeader_T &&_ledgerHeader,
                             _txSet_T &&_txSet,
                             _txProcessing_T &&_txProcessing,
                             _upgradesProcessing_T &&_upgradesProcessing,
                             _scpInfo_T &&_scpInfo)
    : ledgerHeader(std::forward<_ledgerHeader_T>(_ledgerHeader)),
      txSet(std::forward<_txSet_T>(_txSet)),
      txProcessing(std::forward<_txProcessing_T>(_txProcessing)),
      upgradesProcessing(std::forward<_upgradesProcessing_T>(_upgradesProcessing)),
      scpInfo(std::forward<_scpInfo_T>(_scpInfo)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::LedgerCloseMetaV0>
  : xdr_struct_base<field_ptr<::stellar::LedgerCloseMetaV0,
                              decltype(::stellar::LedgerCloseMetaV0::ledgerHeader),
                              &::stellar::LedgerCloseMetaV0::ledgerHeader>,
                    field_ptr<::stellar::LedgerCloseMetaV0,
                              decltype(::stellar::LedgerCloseMetaV0::txSet),
                              &::stellar::LedgerCloseMetaV0::txSet>,
                    field_ptr<::stellar::LedgerCloseMetaV0,
                              decltype(::stellar::LedgerCloseMetaV0::txProcessing),
                              &::stellar::LedgerCloseMetaV0::txProcessing>,
                    field_ptr<::stellar::LedgerCloseMetaV0,
                              decltype(::stellar::LedgerCloseMetaV0::upgradesProcessing),
                              &::stellar::LedgerCloseMetaV0::upgradesProcessing>,
                    field_ptr<::stellar::LedgerCloseMetaV0,
                              decltype(::stellar::LedgerCloseMetaV0::scpInfo),
                              &::stellar::LedgerCloseMetaV0::scpInfo>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerCloseMetaV0 &obj) {
    archive(ar, obj.ledgerHeader, "ledgerHeader");
    archive(ar, obj.txSet, "txSet");
    archive(ar, obj.txProcessing, "txProcessing");
    archive(ar, obj.upgradesProcessing, "upgradesProcessing");
    archive(ar, obj.scpInfo, "scpInfo");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerCloseMetaV0 &obj) {
    archive(ar, obj.ledgerHeader, "ledgerHeader");
    archive(ar, obj.txSet, "txSet");
    archive(ar, obj.txProcessing, "txProcessing");
    archive(ar, obj.upgradesProcessing, "upgradesProcessing");
    archive(ar, obj.scpInfo, "scpInfo");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct LedgerCloseMetaExtV1 {
  ExtensionPoint ext{};
  int64 sorobanFeeWrite1KB{};

  LedgerCloseMetaExtV1() = default;
  template<typename _ext_T,
           typename _sorobanFeeWrite1KB_T,
           typename = typename
           std::enable_if<std::is_constructible<ExtensionPoint, _ext_T>::value
                          && std::is_constructible<int64, _sorobanFeeWrite1KB_T>::value
                         >::type>
  explicit LedgerCloseMetaExtV1(_ext_T &&_ext,
                                _sorobanFeeWrite1KB_T &&_sorobanFeeWrite1KB)
    : ext(std::forward<_ext_T>(_ext)),
      sorobanFeeWrite1KB(std::forward<_sorobanFeeWrite1KB_T>(_sorobanFeeWrite1KB)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::LedgerCloseMetaExtV1>
  : xdr_struct_base<field_ptr<::stellar::LedgerCloseMetaExtV1,
                              decltype(::stellar::LedgerCloseMetaExtV1::ext),
                              &::stellar::LedgerCloseMetaExtV1::ext>,
                    field_ptr<::stellar::LedgerCloseMetaExtV1,
                              decltype(::stellar::LedgerCloseMetaExtV1::sorobanFeeWrite1KB),
                              &::stellar::LedgerCloseMetaExtV1::sorobanFeeWrite1KB>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerCloseMetaExtV1 &obj) {
    archive(ar, obj.ext, "ext");
    archive(ar, obj.sorobanFeeWrite1KB, "sorobanFeeWrite1KB");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerCloseMetaExtV1 &obj) {
    archive(ar, obj.ext, "ext");
    archive(ar, obj.sorobanFeeWrite1KB, "sorobanFeeWrite1KB");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct LedgerCloseMetaExt {
  using _xdr_case_type = xdr::xdr_traits<int>::case_type;
private:
  _xdr_case_type v_;
  union {
    LedgerCloseMetaExtV1 v1_;
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
      _f(&LedgerCloseMetaExt::v1_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return v_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of v in LedgerCloseMetaExt");
    if (fnum != _xdr_field_number(v_)) {
      this->~LedgerCloseMetaExt();
      v_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
    }
    else
      v_ = which;
  }
  explicit LedgerCloseMetaExt(std::int32_t which = std::int32_t{}) : v_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
  }
  LedgerCloseMetaExt(const LedgerCloseMetaExt &source) : v_(source.v_) {
    _xdr_with_mem_ptr(xdr::field_constructor, v_, *this, source);
  }
  LedgerCloseMetaExt(LedgerCloseMetaExt &&source) : v_(source.v_) {
    _xdr_with_mem_ptr(xdr::field_constructor, v_, *this,
                      std::move(source));
  }
  ~LedgerCloseMetaExt() { _xdr_with_mem_ptr(xdr::field_destructor, v_, *this); }
  LedgerCloseMetaExt &operator=(const LedgerCloseMetaExt &source) {
    if (_xdr_field_number(v_)
        == _xdr_field_number(source.v_))
      _xdr_with_mem_ptr(xdr::field_assigner, v_, *this, source);
    else {
      this->~LedgerCloseMetaExt();
      v_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this, source);
    }
    v_ = source.v_;
    return *this;
  }
  LedgerCloseMetaExt &operator=(LedgerCloseMetaExt &&source) {
    if (_xdr_field_number(v_)
         == _xdr_field_number(source.v_))
      _xdr_with_mem_ptr(xdr::field_assigner, v_, *this,
                        std::move(source));
    else {
      this->~LedgerCloseMetaExt();
      v_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this,
                        std::move(source));
    }
    v_ = source.v_;
    return *this;
  }

  std::int32_t v() const { return std::int32_t(v_); }
  LedgerCloseMetaExt &v(int _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  LedgerCloseMetaExtV1 &v1() {
    if (_xdr_field_number(v_) == 1)
      return v1_;
    throw xdr::xdr_wrong_union("LedgerCloseMetaExt: v1 accessed when not selected");
  }
  const LedgerCloseMetaExtV1 &v1() const {
    if (_xdr_field_number(v_) == 1)
      return v1_;
    throw xdr::xdr_wrong_union("LedgerCloseMetaExt: v1 accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::LedgerCloseMetaExt> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::LedgerCloseMetaExt;
  using case_type = ::stellar::LedgerCloseMetaExt::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

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

  static std::size_t serial_size(const ::stellar::LedgerCloseMetaExt &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in LedgerCloseMetaExt");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerCloseMetaExt &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in LedgerCloseMetaExt");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerCloseMetaExt &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.v(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

struct LedgerCloseMetaV1 {
  LedgerCloseMetaExt ext{};
  LedgerHeaderHistoryEntry ledgerHeader{};
  GeneralizedTransactionSet txSet{};
  xdr::xvector<TransactionResultMeta> txProcessing{};
  xdr::xvector<UpgradeEntryMeta> upgradesProcessing{};
  xdr::xvector<SCPHistoryEntry> scpInfo{};
  uint64 totalByteSizeOfLiveSorobanState{};
  xdr::xvector<LedgerKey> evictedKeys{};
  xdr::xvector<LedgerEntry> unused{};

  LedgerCloseMetaV1() = default;
  template<typename _ext_T,
           typename _ledgerHeader_T,
           typename _txSet_T,
           typename _txProcessing_T,
           typename _upgradesProcessing_T,
           typename _scpInfo_T,
           typename _totalByteSizeOfLiveSorobanState_T,
           typename _evictedKeys_T,
           typename _unused_T,
           typename = typename
           std::enable_if<std::is_constructible<LedgerCloseMetaExt, _ext_T>::value
                          && std::is_constructible<LedgerHeaderHistoryEntry, _ledgerHeader_T>::value
                          && std::is_constructible<GeneralizedTransactionSet, _txSet_T>::value
                          && std::is_constructible<xdr::xvector<TransactionResultMeta>, _txProcessing_T>::value
                          && std::is_constructible<xdr::xvector<UpgradeEntryMeta>, _upgradesProcessing_T>::value
                          && std::is_constructible<xdr::xvector<SCPHistoryEntry>, _scpInfo_T>::value
                          && std::is_constructible<uint64, _totalByteSizeOfLiveSorobanState_T>::value
                          && std::is_constructible<xdr::xvector<LedgerKey>, _evictedKeys_T>::value
                          && std::is_constructible<xdr::xvector<LedgerEntry>, _unused_T>::value
                         >::type>
  explicit LedgerCloseMetaV1(_ext_T &&_ext,
                             _ledgerHeader_T &&_ledgerHeader,
                             _txSet_T &&_txSet,
                             _txProcessing_T &&_txProcessing,
                             _upgradesProcessing_T &&_upgradesProcessing,
                             _scpInfo_T &&_scpInfo,
                             _totalByteSizeOfLiveSorobanState_T &&_totalByteSizeOfLiveSorobanState,
                             _evictedKeys_T &&_evictedKeys,
                             _unused_T &&_unused)
    : ext(std::forward<_ext_T>(_ext)),
      ledgerHeader(std::forward<_ledgerHeader_T>(_ledgerHeader)),
      txSet(std::forward<_txSet_T>(_txSet)),
      txProcessing(std::forward<_txProcessing_T>(_txProcessing)),
      upgradesProcessing(std::forward<_upgradesProcessing_T>(_upgradesProcessing)),
      scpInfo(std::forward<_scpInfo_T>(_scpInfo)),
      totalByteSizeOfLiveSorobanState(std::forward<_totalByteSizeOfLiveSorobanState_T>(_totalByteSizeOfLiveSorobanState)),
      evictedKeys(std::forward<_evictedKeys_T>(_evictedKeys)),
      unused(std::forward<_unused_T>(_unused)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::LedgerCloseMetaV1>
  : xdr_struct_base<field_ptr<::stellar::LedgerCloseMetaV1,
                              decltype(::stellar::LedgerCloseMetaV1::ext),
                              &::stellar::LedgerCloseMetaV1::ext>,
                    field_ptr<::stellar::LedgerCloseMetaV1,
                              decltype(::stellar::LedgerCloseMetaV1::ledgerHeader),
                              &::stellar::LedgerCloseMetaV1::ledgerHeader>,
                    field_ptr<::stellar::LedgerCloseMetaV1,
                              decltype(::stellar::LedgerCloseMetaV1::txSet),
                              &::stellar::LedgerCloseMetaV1::txSet>,
                    field_ptr<::stellar::LedgerCloseMetaV1,
                              decltype(::stellar::LedgerCloseMetaV1::txProcessing),
                              &::stellar::LedgerCloseMetaV1::txProcessing>,
                    field_ptr<::stellar::LedgerCloseMetaV1,
                              decltype(::stellar::LedgerCloseMetaV1::upgradesProcessing),
                              &::stellar::LedgerCloseMetaV1::upgradesProcessing>,
                    field_ptr<::stellar::LedgerCloseMetaV1,
                              decltype(::stellar::LedgerCloseMetaV1::scpInfo),
                              &::stellar::LedgerCloseMetaV1::scpInfo>,
                    field_ptr<::stellar::LedgerCloseMetaV1,
                              decltype(::stellar::LedgerCloseMetaV1::totalByteSizeOfLiveSorobanState),
                              &::stellar::LedgerCloseMetaV1::totalByteSizeOfLiveSorobanState>,
                    field_ptr<::stellar::LedgerCloseMetaV1,
                              decltype(::stellar::LedgerCloseMetaV1::evictedKeys),
                              &::stellar::LedgerCloseMetaV1::evictedKeys>,
                    field_ptr<::stellar::LedgerCloseMetaV1,
                              decltype(::stellar::LedgerCloseMetaV1::unused),
                              &::stellar::LedgerCloseMetaV1::unused>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerCloseMetaV1 &obj) {
    archive(ar, obj.ext, "ext");
    archive(ar, obj.ledgerHeader, "ledgerHeader");
    archive(ar, obj.txSet, "txSet");
    archive(ar, obj.txProcessing, "txProcessing");
    archive(ar, obj.upgradesProcessing, "upgradesProcessing");
    archive(ar, obj.scpInfo, "scpInfo");
    archive(ar, obj.totalByteSizeOfLiveSorobanState, "totalByteSizeOfLiveSorobanState");
    archive(ar, obj.evictedKeys, "evictedKeys");
    archive(ar, obj.unused, "unused");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerCloseMetaV1 &obj) {
    archive(ar, obj.ext, "ext");
    archive(ar, obj.ledgerHeader, "ledgerHeader");
    archive(ar, obj.txSet, "txSet");
    archive(ar, obj.txProcessing, "txProcessing");
    archive(ar, obj.upgradesProcessing, "upgradesProcessing");
    archive(ar, obj.scpInfo, "scpInfo");
    archive(ar, obj.totalByteSizeOfLiveSorobanState, "totalByteSizeOfLiveSorobanState");
    archive(ar, obj.evictedKeys, "evictedKeys");
    archive(ar, obj.unused, "unused");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct LedgerCloseMetaV2 {
  LedgerCloseMetaExt ext{};
  LedgerHeaderHistoryEntry ledgerHeader{};
  GeneralizedTransactionSet txSet{};
  xdr::xvector<TransactionResultMetaV1> txProcessing{};
  xdr::xvector<UpgradeEntryMeta> upgradesProcessing{};
  xdr::xvector<SCPHistoryEntry> scpInfo{};
  uint64 totalByteSizeOfLiveSorobanState{};
  xdr::xvector<LedgerKey> evictedKeys{};

  LedgerCloseMetaV2() = default;
  template<typename _ext_T,
           typename _ledgerHeader_T,
           typename _txSet_T,
           typename _txProcessing_T,
           typename _upgradesProcessing_T,
           typename _scpInfo_T,
           typename _totalByteSizeOfLiveSorobanState_T,
           typename _evictedKeys_T,
           typename = typename
           std::enable_if<std::is_constructible<LedgerCloseMetaExt, _ext_T>::value
                          && std::is_constructible<LedgerHeaderHistoryEntry, _ledgerHeader_T>::value
                          && std::is_constructible<GeneralizedTransactionSet, _txSet_T>::value
                          && std::is_constructible<xdr::xvector<TransactionResultMetaV1>, _txProcessing_T>::value
                          && std::is_constructible<xdr::xvector<UpgradeEntryMeta>, _upgradesProcessing_T>::value
                          && std::is_constructible<xdr::xvector<SCPHistoryEntry>, _scpInfo_T>::value
                          && std::is_constructible<uint64, _totalByteSizeOfLiveSorobanState_T>::value
                          && std::is_constructible<xdr::xvector<LedgerKey>, _evictedKeys_T>::value
                         >::type>
  explicit LedgerCloseMetaV2(_ext_T &&_ext,
                             _ledgerHeader_T &&_ledgerHeader,
                             _txSet_T &&_txSet,
                             _txProcessing_T &&_txProcessing,
                             _upgradesProcessing_T &&_upgradesProcessing,
                             _scpInfo_T &&_scpInfo,
                             _totalByteSizeOfLiveSorobanState_T &&_totalByteSizeOfLiveSorobanState,
                             _evictedKeys_T &&_evictedKeys)
    : ext(std::forward<_ext_T>(_ext)),
      ledgerHeader(std::forward<_ledgerHeader_T>(_ledgerHeader)),
      txSet(std::forward<_txSet_T>(_txSet)),
      txProcessing(std::forward<_txProcessing_T>(_txProcessing)),
      upgradesProcessing(std::forward<_upgradesProcessing_T>(_upgradesProcessing)),
      scpInfo(std::forward<_scpInfo_T>(_scpInfo)),
      totalByteSizeOfLiveSorobanState(std::forward<_totalByteSizeOfLiveSorobanState_T>(_totalByteSizeOfLiveSorobanState)),
      evictedKeys(std::forward<_evictedKeys_T>(_evictedKeys)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::LedgerCloseMetaV2>
  : xdr_struct_base<field_ptr<::stellar::LedgerCloseMetaV2,
                              decltype(::stellar::LedgerCloseMetaV2::ext),
                              &::stellar::LedgerCloseMetaV2::ext>,
                    field_ptr<::stellar::LedgerCloseMetaV2,
                              decltype(::stellar::LedgerCloseMetaV2::ledgerHeader),
                              &::stellar::LedgerCloseMetaV2::ledgerHeader>,
                    field_ptr<::stellar::LedgerCloseMetaV2,
                              decltype(::stellar::LedgerCloseMetaV2::txSet),
                              &::stellar::LedgerCloseMetaV2::txSet>,
                    field_ptr<::stellar::LedgerCloseMetaV2,
                              decltype(::stellar::LedgerCloseMetaV2::txProcessing),
                              &::stellar::LedgerCloseMetaV2::txProcessing>,
                    field_ptr<::stellar::LedgerCloseMetaV2,
                              decltype(::stellar::LedgerCloseMetaV2::upgradesProcessing),
                              &::stellar::LedgerCloseMetaV2::upgradesProcessing>,
                    field_ptr<::stellar::LedgerCloseMetaV2,
                              decltype(::stellar::LedgerCloseMetaV2::scpInfo),
                              &::stellar::LedgerCloseMetaV2::scpInfo>,
                    field_ptr<::stellar::LedgerCloseMetaV2,
                              decltype(::stellar::LedgerCloseMetaV2::totalByteSizeOfLiveSorobanState),
                              &::stellar::LedgerCloseMetaV2::totalByteSizeOfLiveSorobanState>,
                    field_ptr<::stellar::LedgerCloseMetaV2,
                              decltype(::stellar::LedgerCloseMetaV2::evictedKeys),
                              &::stellar::LedgerCloseMetaV2::evictedKeys>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerCloseMetaV2 &obj) {
    archive(ar, obj.ext, "ext");
    archive(ar, obj.ledgerHeader, "ledgerHeader");
    archive(ar, obj.txSet, "txSet");
    archive(ar, obj.txProcessing, "txProcessing");
    archive(ar, obj.upgradesProcessing, "upgradesProcessing");
    archive(ar, obj.scpInfo, "scpInfo");
    archive(ar, obj.totalByteSizeOfLiveSorobanState, "totalByteSizeOfLiveSorobanState");
    archive(ar, obj.evictedKeys, "evictedKeys");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerCloseMetaV2 &obj) {
    archive(ar, obj.ext, "ext");
    archive(ar, obj.ledgerHeader, "ledgerHeader");
    archive(ar, obj.txSet, "txSet");
    archive(ar, obj.txProcessing, "txProcessing");
    archive(ar, obj.upgradesProcessing, "upgradesProcessing");
    archive(ar, obj.scpInfo, "scpInfo");
    archive(ar, obj.totalByteSizeOfLiveSorobanState, "totalByteSizeOfLiveSorobanState");
    archive(ar, obj.evictedKeys, "evictedKeys");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct LedgerCloseMeta {
  using _xdr_case_type = xdr::xdr_traits<int>::case_type;
private:
  _xdr_case_type v_;
  union {
    LedgerCloseMetaV0 v0_;
    LedgerCloseMetaV1 v1_;
    LedgerCloseMetaV2 v2_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<int> &_xdr_case_values() {
    static const std::vector<int> _xdr_disc_vec {
      0,
      1,
      2
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == 0 ? 1
      : which == 1 ? 2
      : which == 2 ? 3
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case 0:
      _f(&LedgerCloseMeta::v0_, std::forward<_A>(_a)...);
      return true;
    case 1:
      _f(&LedgerCloseMeta::v1_, std::forward<_A>(_a)...);
      return true;
    case 2:
      _f(&LedgerCloseMeta::v2_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return v_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of v in LedgerCloseMeta");
    if (fnum != _xdr_field_number(v_)) {
      this->~LedgerCloseMeta();
      v_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
    }
    else
      v_ = which;
  }
  explicit LedgerCloseMeta(std::int32_t which = std::int32_t{}) : v_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
  }
  LedgerCloseMeta(const LedgerCloseMeta &source) : v_(source.v_) {
    _xdr_with_mem_ptr(xdr::field_constructor, v_, *this, source);
  }
  LedgerCloseMeta(LedgerCloseMeta &&source) : v_(source.v_) {
    _xdr_with_mem_ptr(xdr::field_constructor, v_, *this,
                      std::move(source));
  }
  ~LedgerCloseMeta() { _xdr_with_mem_ptr(xdr::field_destructor, v_, *this); }
  LedgerCloseMeta &operator=(const LedgerCloseMeta &source) {
    if (_xdr_field_number(v_)
        == _xdr_field_number(source.v_))
      _xdr_with_mem_ptr(xdr::field_assigner, v_, *this, source);
    else {
      this->~LedgerCloseMeta();
      v_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this, source);
    }
    v_ = source.v_;
    return *this;
  }
  LedgerCloseMeta &operator=(LedgerCloseMeta &&source) {
    if (_xdr_field_number(v_)
         == _xdr_field_number(source.v_))
      _xdr_with_mem_ptr(xdr::field_assigner, v_, *this,
                        std::move(source));
    else {
      this->~LedgerCloseMeta();
      v_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this,
                        std::move(source));
    }
    v_ = source.v_;
    return *this;
  }

  std::int32_t v() const { return std::int32_t(v_); }
  LedgerCloseMeta &v(int _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  LedgerCloseMetaV0 &v0() {
    if (_xdr_field_number(v_) == 1)
      return v0_;
    throw xdr::xdr_wrong_union("LedgerCloseMeta: v0 accessed when not selected");
  }
  const LedgerCloseMetaV0 &v0() const {
    if (_xdr_field_number(v_) == 1)
      return v0_;
    throw xdr::xdr_wrong_union("LedgerCloseMeta: v0 accessed when not selected");
  }
  LedgerCloseMetaV1 &v1() {
    if (_xdr_field_number(v_) == 2)
      return v1_;
    throw xdr::xdr_wrong_union("LedgerCloseMeta: v1 accessed when not selected");
  }
  const LedgerCloseMetaV1 &v1() const {
    if (_xdr_field_number(v_) == 2)
      return v1_;
    throw xdr::xdr_wrong_union("LedgerCloseMeta: v1 accessed when not selected");
  }
  LedgerCloseMetaV2 &v2() {
    if (_xdr_field_number(v_) == 3)
      return v2_;
    throw xdr::xdr_wrong_union("LedgerCloseMeta: v2 accessed when not selected");
  }
  const LedgerCloseMetaV2 &v2() const {
    if (_xdr_field_number(v_) == 3)
      return v2_;
    throw xdr::xdr_wrong_union("LedgerCloseMeta: v2 accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::LedgerCloseMeta> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::LedgerCloseMeta;
  using case_type = ::stellar::LedgerCloseMeta::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "v0";
    case 2:
      return "v1";
    case 3:
      return "v2";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::LedgerCloseMeta &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in LedgerCloseMeta");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerCloseMeta &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in LedgerCloseMeta");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerCloseMeta &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.v(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

}

#endif // !__XDR_STELLAR_LEDGER_H_INCLUDED__
