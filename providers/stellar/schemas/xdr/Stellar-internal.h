// -*- C++ -*-
// Automatically generated from Stellar-internal.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_INTERNAL_H_INCLUDED__
#define __XDR_STELLAR_INTERNAL_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-ledger.h"
#include "xdr/Stellar-SCP.h"

namespace stellar {

struct StoredTransactionSet {
  using _xdr_case_type = xdr::xdr_traits<int>::case_type;
private:
  _xdr_case_type v_;
  union {
    TransactionSet txSet_;
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
    return which == 0 ? 1
      : which == 1 ? 2
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case 0:
      _f(&StoredTransactionSet::txSet_, std::forward<_A>(_a)...);
      return true;
    case 1:
      _f(&StoredTransactionSet::generalizedTxSet_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return v_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of v in StoredTransactionSet");
    if (fnum != _xdr_field_number(v_)) {
      this->~StoredTransactionSet();
      v_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
    }
    else
      v_ = which;
  }
  explicit StoredTransactionSet(std::int32_t which = std::int32_t{}) : v_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
  }
  StoredTransactionSet(const StoredTransactionSet &source) : v_(source.v_) {
    _xdr_with_mem_ptr(xdr::field_constructor, v_, *this, source);
  }
  StoredTransactionSet(StoredTransactionSet &&source) : v_(source.v_) {
    _xdr_with_mem_ptr(xdr::field_constructor, v_, *this,
                      std::move(source));
  }
  ~StoredTransactionSet() { _xdr_with_mem_ptr(xdr::field_destructor, v_, *this); }
  StoredTransactionSet &operator=(const StoredTransactionSet &source) {
    if (_xdr_field_number(v_)
        == _xdr_field_number(source.v_))
      _xdr_with_mem_ptr(xdr::field_assigner, v_, *this, source);
    else {
      this->~StoredTransactionSet();
      v_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this, source);
    }
    v_ = source.v_;
    return *this;
  }
  StoredTransactionSet &operator=(StoredTransactionSet &&source) {
    if (_xdr_field_number(v_)
         == _xdr_field_number(source.v_))
      _xdr_with_mem_ptr(xdr::field_assigner, v_, *this,
                        std::move(source));
    else {
      this->~StoredTransactionSet();
      v_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this,
                        std::move(source));
    }
    v_ = source.v_;
    return *this;
  }

  std::int32_t v() const { return std::int32_t(v_); }
  StoredTransactionSet &v(int _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  TransactionSet &txSet() {
    if (_xdr_field_number(v_) == 1)
      return txSet_;
    throw xdr::xdr_wrong_union("StoredTransactionSet: txSet accessed when not selected");
  }
  const TransactionSet &txSet() const {
    if (_xdr_field_number(v_) == 1)
      return txSet_;
    throw xdr::xdr_wrong_union("StoredTransactionSet: txSet accessed when not selected");
  }
  GeneralizedTransactionSet &generalizedTxSet() {
    if (_xdr_field_number(v_) == 2)
      return generalizedTxSet_;
    throw xdr::xdr_wrong_union("StoredTransactionSet: generalizedTxSet accessed when not selected");
  }
  const GeneralizedTransactionSet &generalizedTxSet() const {
    if (_xdr_field_number(v_) == 2)
      return generalizedTxSet_;
    throw xdr::xdr_wrong_union("StoredTransactionSet: generalizedTxSet accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::StoredTransactionSet> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::StoredTransactionSet;
  using case_type = ::stellar::StoredTransactionSet::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "txSet";
    case 2:
      return "generalizedTxSet";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::StoredTransactionSet &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in StoredTransactionSet");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::StoredTransactionSet &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in StoredTransactionSet");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::StoredTransactionSet &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "v");
    obj.v(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.v(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

struct StoredDebugTransactionSet {
  StoredTransactionSet txSet{};
  uint32 ledgerSeq{};
  StellarValue scpValue{};

  StoredDebugTransactionSet() = default;
  template<typename _txSet_T,
           typename _ledgerSeq_T,
           typename _scpValue_T,
           typename = typename
           std::enable_if<std::is_constructible<StoredTransactionSet, _txSet_T>::value
                          && std::is_constructible<uint32, _ledgerSeq_T>::value
                          && std::is_constructible<StellarValue, _scpValue_T>::value
                         >::type>
  explicit StoredDebugTransactionSet(_txSet_T &&_txSet,
                                     _ledgerSeq_T &&_ledgerSeq,
                                     _scpValue_T &&_scpValue)
    : txSet(std::forward<_txSet_T>(_txSet)),
      ledgerSeq(std::forward<_ledgerSeq_T>(_ledgerSeq)),
      scpValue(std::forward<_scpValue_T>(_scpValue)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::StoredDebugTransactionSet>
  : xdr_struct_base<field_ptr<::stellar::StoredDebugTransactionSet,
                              decltype(::stellar::StoredDebugTransactionSet::txSet),
                              &::stellar::StoredDebugTransactionSet::txSet>,
                    field_ptr<::stellar::StoredDebugTransactionSet,
                              decltype(::stellar::StoredDebugTransactionSet::ledgerSeq),
                              &::stellar::StoredDebugTransactionSet::ledgerSeq>,
                    field_ptr<::stellar::StoredDebugTransactionSet,
                              decltype(::stellar::StoredDebugTransactionSet::scpValue),
                              &::stellar::StoredDebugTransactionSet::scpValue>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::StoredDebugTransactionSet &obj) {
    archive(ar, obj.txSet, "txSet");
    archive(ar, obj.ledgerSeq, "ledgerSeq");
    archive(ar, obj.scpValue, "scpValue");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::StoredDebugTransactionSet &obj) {
    archive(ar, obj.txSet, "txSet");
    archive(ar, obj.ledgerSeq, "ledgerSeq");
    archive(ar, obj.scpValue, "scpValue");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct PersistedSCPStateV0 {
  xdr::xvector<SCPEnvelope> scpEnvelopes{};
  xdr::xvector<SCPQuorumSet> quorumSets{};
  xdr::xvector<StoredTransactionSet> txSets{};

  PersistedSCPStateV0() = default;
  template<typename _scpEnvelopes_T,
           typename _quorumSets_T,
           typename _txSets_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::xvector<SCPEnvelope>, _scpEnvelopes_T>::value
                          && std::is_constructible<xdr::xvector<SCPQuorumSet>, _quorumSets_T>::value
                          && std::is_constructible<xdr::xvector<StoredTransactionSet>, _txSets_T>::value
                         >::type>
  explicit PersistedSCPStateV0(_scpEnvelopes_T &&_scpEnvelopes,
                               _quorumSets_T &&_quorumSets,
                               _txSets_T &&_txSets)
    : scpEnvelopes(std::forward<_scpEnvelopes_T>(_scpEnvelopes)),
      quorumSets(std::forward<_quorumSets_T>(_quorumSets)),
      txSets(std::forward<_txSets_T>(_txSets)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::PersistedSCPStateV0>
  : xdr_struct_base<field_ptr<::stellar::PersistedSCPStateV0,
                              decltype(::stellar::PersistedSCPStateV0::scpEnvelopes),
                              &::stellar::PersistedSCPStateV0::scpEnvelopes>,
                    field_ptr<::stellar::PersistedSCPStateV0,
                              decltype(::stellar::PersistedSCPStateV0::quorumSets),
                              &::stellar::PersistedSCPStateV0::quorumSets>,
                    field_ptr<::stellar::PersistedSCPStateV0,
                              decltype(::stellar::PersistedSCPStateV0::txSets),
                              &::stellar::PersistedSCPStateV0::txSets>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::PersistedSCPStateV0 &obj) {
    archive(ar, obj.scpEnvelopes, "scpEnvelopes");
    archive(ar, obj.quorumSets, "quorumSets");
    archive(ar, obj.txSets, "txSets");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::PersistedSCPStateV0 &obj) {
    archive(ar, obj.scpEnvelopes, "scpEnvelopes");
    archive(ar, obj.quorumSets, "quorumSets");
    archive(ar, obj.txSets, "txSets");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct PersistedSCPStateV1 {
  xdr::xvector<SCPEnvelope> scpEnvelopes{};
  xdr::xvector<SCPQuorumSet> quorumSets{};

  PersistedSCPStateV1() = default;
  template<typename _scpEnvelopes_T,
           typename _quorumSets_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::xvector<SCPEnvelope>, _scpEnvelopes_T>::value
                          && std::is_constructible<xdr::xvector<SCPQuorumSet>, _quorumSets_T>::value
                         >::type>
  explicit PersistedSCPStateV1(_scpEnvelopes_T &&_scpEnvelopes,
                               _quorumSets_T &&_quorumSets)
    : scpEnvelopes(std::forward<_scpEnvelopes_T>(_scpEnvelopes)),
      quorumSets(std::forward<_quorumSets_T>(_quorumSets)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::PersistedSCPStateV1>
  : xdr_struct_base<field_ptr<::stellar::PersistedSCPStateV1,
                              decltype(::stellar::PersistedSCPStateV1::scpEnvelopes),
                              &::stellar::PersistedSCPStateV1::scpEnvelopes>,
                    field_ptr<::stellar::PersistedSCPStateV1,
                              decltype(::stellar::PersistedSCPStateV1::quorumSets),
                              &::stellar::PersistedSCPStateV1::quorumSets>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::PersistedSCPStateV1 &obj) {
    archive(ar, obj.scpEnvelopes, "scpEnvelopes");
    archive(ar, obj.quorumSets, "quorumSets");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::PersistedSCPStateV1 &obj) {
    archive(ar, obj.scpEnvelopes, "scpEnvelopes");
    archive(ar, obj.quorumSets, "quorumSets");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct PersistedSCPState {
  using _xdr_case_type = xdr::xdr_traits<int>::case_type;
private:
  _xdr_case_type v_;
  union {
    PersistedSCPStateV0 v0_;
    PersistedSCPStateV1 v1_;
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
      _f(&PersistedSCPState::v0_, std::forward<_A>(_a)...);
      return true;
    case 1:
      _f(&PersistedSCPState::v1_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return v_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of v in PersistedSCPState");
    if (fnum != _xdr_field_number(v_)) {
      this->~PersistedSCPState();
      v_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
    }
    else
      v_ = which;
  }
  explicit PersistedSCPState(std::int32_t which = std::int32_t{}) : v_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, v_, *this);
  }
  PersistedSCPState(const PersistedSCPState &source) : v_(source.v_) {
    _xdr_with_mem_ptr(xdr::field_constructor, v_, *this, source);
  }
  PersistedSCPState(PersistedSCPState &&source) : v_(source.v_) {
    _xdr_with_mem_ptr(xdr::field_constructor, v_, *this,
                      std::move(source));
  }
  ~PersistedSCPState() { _xdr_with_mem_ptr(xdr::field_destructor, v_, *this); }
  PersistedSCPState &operator=(const PersistedSCPState &source) {
    if (_xdr_field_number(v_)
        == _xdr_field_number(source.v_))
      _xdr_with_mem_ptr(xdr::field_assigner, v_, *this, source);
    else {
      this->~PersistedSCPState();
      v_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this, source);
    }
    v_ = source.v_;
    return *this;
  }
  PersistedSCPState &operator=(PersistedSCPState &&source) {
    if (_xdr_field_number(v_)
         == _xdr_field_number(source.v_))
      _xdr_with_mem_ptr(xdr::field_assigner, v_, *this,
                        std::move(source));
    else {
      this->~PersistedSCPState();
      v_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.v_, *this,
                        std::move(source));
    }
    v_ = source.v_;
    return *this;
  }

  std::int32_t v() const { return std::int32_t(v_); }
  PersistedSCPState &v(int _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  PersistedSCPStateV0 &v0() {
    if (_xdr_field_number(v_) == 1)
      return v0_;
    throw xdr::xdr_wrong_union("PersistedSCPState: v0 accessed when not selected");
  }
  const PersistedSCPStateV0 &v0() const {
    if (_xdr_field_number(v_) == 1)
      return v0_;
    throw xdr::xdr_wrong_union("PersistedSCPState: v0 accessed when not selected");
  }
  PersistedSCPStateV1 &v1() {
    if (_xdr_field_number(v_) == 2)
      return v1_;
    throw xdr::xdr_wrong_union("PersistedSCPState: v1 accessed when not selected");
  }
  const PersistedSCPStateV1 &v1() const {
    if (_xdr_field_number(v_) == 2)
      return v1_;
    throw xdr::xdr_wrong_union("PersistedSCPState: v1 accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::PersistedSCPState> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::PersistedSCPState;
  using case_type = ::stellar::PersistedSCPState::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().v());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "v0";
    case 2:
      return "v1";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::PersistedSCPState &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of v in PersistedSCPState");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::PersistedSCPState &obj) {
    xdr::archive(ar, obj.v(), "v");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.v(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of v in PersistedSCPState");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::PersistedSCPState &obj) {
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

#endif // !__XDR_STELLAR_INTERNAL_H_INCLUDED__
