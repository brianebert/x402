// -*- C++ -*-
// Automatically generated from Stellar-exporter.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_EXPORTER_H_INCLUDED__
#define __XDR_STELLAR_EXPORTER_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-ledger.h"

namespace stellar {

struct LedgerCloseMetaBatch {
  uint32 startSequence{};
  uint32 endSequence{};
  xdr::xvector<LedgerCloseMeta> ledgerCloseMetas{};

  LedgerCloseMetaBatch() = default;
  template<typename _startSequence_T,
           typename _endSequence_T,
           typename _ledgerCloseMetas_T,
           typename = typename
           std::enable_if<std::is_constructible<uint32, _startSequence_T>::value
                          && std::is_constructible<uint32, _endSequence_T>::value
                          && std::is_constructible<xdr::xvector<LedgerCloseMeta>, _ledgerCloseMetas_T>::value
                         >::type>
  explicit LedgerCloseMetaBatch(_startSequence_T &&_startSequence,
                                _endSequence_T &&_endSequence,
                                _ledgerCloseMetas_T &&_ledgerCloseMetas)
    : startSequence(std::forward<_startSequence_T>(_startSequence)),
      endSequence(std::forward<_endSequence_T>(_endSequence)),
      ledgerCloseMetas(std::forward<_ledgerCloseMetas_T>(_ledgerCloseMetas)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::LedgerCloseMetaBatch>
  : xdr_struct_base<field_ptr<::stellar::LedgerCloseMetaBatch,
                              decltype(::stellar::LedgerCloseMetaBatch::startSequence),
                              &::stellar::LedgerCloseMetaBatch::startSequence>,
                    field_ptr<::stellar::LedgerCloseMetaBatch,
                              decltype(::stellar::LedgerCloseMetaBatch::endSequence),
                              &::stellar::LedgerCloseMetaBatch::endSequence>,
                    field_ptr<::stellar::LedgerCloseMetaBatch,
                              decltype(::stellar::LedgerCloseMetaBatch::ledgerCloseMetas),
                              &::stellar::LedgerCloseMetaBatch::ledgerCloseMetas>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::LedgerCloseMetaBatch &obj) {
    archive(ar, obj.startSequence, "startSequence");
    archive(ar, obj.endSequence, "endSequence");
    archive(ar, obj.ledgerCloseMetas, "ledgerCloseMetas");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::LedgerCloseMetaBatch &obj) {
    archive(ar, obj.startSequence, "startSequence");
    archive(ar, obj.endSequence, "endSequence");
    archive(ar, obj.ledgerCloseMetas, "ledgerCloseMetas");
    xdr::validate(obj);
  }
};
} namespace stellar {

}

#endif // !__XDR_STELLAR_EXPORTER_H_INCLUDED__
