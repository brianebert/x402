// -*- C++ -*-
// Automatically generated from Stellar-contract-config-setting.x.
// DO NOT EDIT or your changes may be overwritten

#ifndef __XDR_STELLAR_CONTRACT_CONFIG_SETTING_H_INCLUDED__
#define __XDR_STELLAR_CONTRACT_CONFIG_SETTING_H_INCLUDED__ 1

#include <xdrpp/types.h>

#include "xdr/Stellar-types.h"

namespace stellar {

using EncodedLedgerKey = xdr::opaque_vec<>;

struct ConfigSettingContractExecutionLanesV0 {
  uint32 ledgerMaxTxCount{};

  ConfigSettingContractExecutionLanesV0() = default;
  template<typename _ledgerMaxTxCount_T,
           typename = typename
           std::enable_if<std::is_constructible<uint32, _ledgerMaxTxCount_T>::value
                         >::type>
  explicit ConfigSettingContractExecutionLanesV0(_ledgerMaxTxCount_T &&_ledgerMaxTxCount)
    : ledgerMaxTxCount(std::forward<_ledgerMaxTxCount_T>(_ledgerMaxTxCount)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ConfigSettingContractExecutionLanesV0>
  : xdr_struct_base<field_ptr<::stellar::ConfigSettingContractExecutionLanesV0,
                              decltype(::stellar::ConfigSettingContractExecutionLanesV0::ledgerMaxTxCount),
                              &::stellar::ConfigSettingContractExecutionLanesV0::ledgerMaxTxCount>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ConfigSettingContractExecutionLanesV0 &obj) {
    archive(ar, obj.ledgerMaxTxCount, "ledgerMaxTxCount");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ConfigSettingContractExecutionLanesV0 &obj) {
    archive(ar, obj.ledgerMaxTxCount, "ledgerMaxTxCount");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ConfigSettingContractComputeV0 {
  int64 ledgerMaxInstructions{};
  int64 txMaxInstructions{};
  int64 feeRatePerInstructionsIncrement{};
  uint32 txMemoryLimit{};

  ConfigSettingContractComputeV0() = default;
  template<typename _ledgerMaxInstructions_T,
           typename _txMaxInstructions_T,
           typename _feeRatePerInstructionsIncrement_T,
           typename _txMemoryLimit_T,
           typename = typename
           std::enable_if<std::is_constructible<int64, _ledgerMaxInstructions_T>::value
                          && std::is_constructible<int64, _txMaxInstructions_T>::value
                          && std::is_constructible<int64, _feeRatePerInstructionsIncrement_T>::value
                          && std::is_constructible<uint32, _txMemoryLimit_T>::value
                         >::type>
  explicit ConfigSettingContractComputeV0(_ledgerMaxInstructions_T &&_ledgerMaxInstructions,
                                          _txMaxInstructions_T &&_txMaxInstructions,
                                          _feeRatePerInstructionsIncrement_T &&_feeRatePerInstructionsIncrement,
                                          _txMemoryLimit_T &&_txMemoryLimit)
    : ledgerMaxInstructions(std::forward<_ledgerMaxInstructions_T>(_ledgerMaxInstructions)),
      txMaxInstructions(std::forward<_txMaxInstructions_T>(_txMaxInstructions)),
      feeRatePerInstructionsIncrement(std::forward<_feeRatePerInstructionsIncrement_T>(_feeRatePerInstructionsIncrement)),
      txMemoryLimit(std::forward<_txMemoryLimit_T>(_txMemoryLimit)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ConfigSettingContractComputeV0>
  : xdr_struct_base<field_ptr<::stellar::ConfigSettingContractComputeV0,
                              decltype(::stellar::ConfigSettingContractComputeV0::ledgerMaxInstructions),
                              &::stellar::ConfigSettingContractComputeV0::ledgerMaxInstructions>,
                    field_ptr<::stellar::ConfigSettingContractComputeV0,
                              decltype(::stellar::ConfigSettingContractComputeV0::txMaxInstructions),
                              &::stellar::ConfigSettingContractComputeV0::txMaxInstructions>,
                    field_ptr<::stellar::ConfigSettingContractComputeV0,
                              decltype(::stellar::ConfigSettingContractComputeV0::feeRatePerInstructionsIncrement),
                              &::stellar::ConfigSettingContractComputeV0::feeRatePerInstructionsIncrement>,
                    field_ptr<::stellar::ConfigSettingContractComputeV0,
                              decltype(::stellar::ConfigSettingContractComputeV0::txMemoryLimit),
                              &::stellar::ConfigSettingContractComputeV0::txMemoryLimit>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ConfigSettingContractComputeV0 &obj) {
    archive(ar, obj.ledgerMaxInstructions, "ledgerMaxInstructions");
    archive(ar, obj.txMaxInstructions, "txMaxInstructions");
    archive(ar, obj.feeRatePerInstructionsIncrement, "feeRatePerInstructionsIncrement");
    archive(ar, obj.txMemoryLimit, "txMemoryLimit");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ConfigSettingContractComputeV0 &obj) {
    archive(ar, obj.ledgerMaxInstructions, "ledgerMaxInstructions");
    archive(ar, obj.txMaxInstructions, "txMaxInstructions");
    archive(ar, obj.feeRatePerInstructionsIncrement, "feeRatePerInstructionsIncrement");
    archive(ar, obj.txMemoryLimit, "txMemoryLimit");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ConfigSettingContractParallelComputeV0 {
  uint32 ledgerMaxDependentTxClusters{};

  ConfigSettingContractParallelComputeV0() = default;
  template<typename _ledgerMaxDependentTxClusters_T,
           typename = typename
           std::enable_if<std::is_constructible<uint32, _ledgerMaxDependentTxClusters_T>::value
                         >::type>
  explicit ConfigSettingContractParallelComputeV0(_ledgerMaxDependentTxClusters_T &&_ledgerMaxDependentTxClusters)
    : ledgerMaxDependentTxClusters(std::forward<_ledgerMaxDependentTxClusters_T>(_ledgerMaxDependentTxClusters)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ConfigSettingContractParallelComputeV0>
  : xdr_struct_base<field_ptr<::stellar::ConfigSettingContractParallelComputeV0,
                              decltype(::stellar::ConfigSettingContractParallelComputeV0::ledgerMaxDependentTxClusters),
                              &::stellar::ConfigSettingContractParallelComputeV0::ledgerMaxDependentTxClusters>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ConfigSettingContractParallelComputeV0 &obj) {
    archive(ar, obj.ledgerMaxDependentTxClusters, "ledgerMaxDependentTxClusters");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ConfigSettingContractParallelComputeV0 &obj) {
    archive(ar, obj.ledgerMaxDependentTxClusters, "ledgerMaxDependentTxClusters");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ConfigSettingContractLedgerCostV0 {
  uint32 ledgerMaxDiskReadEntries{};
  uint32 ledgerMaxDiskReadBytes{};
  uint32 ledgerMaxWriteLedgerEntries{};
  uint32 ledgerMaxWriteBytes{};
  uint32 txMaxDiskReadEntries{};
  uint32 txMaxDiskReadBytes{};
  uint32 txMaxWriteLedgerEntries{};
  uint32 txMaxWriteBytes{};
  int64 feeDiskReadLedgerEntry{};
  int64 feeWriteLedgerEntry{};
  int64 feeDiskRead1KB{};
  int64 sorobanStateTargetSizeBytes{};
  int64 rentFee1KBSorobanStateSizeLow{};
  int64 rentFee1KBSorobanStateSizeHigh{};
  uint32 sorobanStateRentFeeGrowthFactor{};

  ConfigSettingContractLedgerCostV0() = default;
  template<typename _ledgerMaxDiskReadEntries_T,
           typename _ledgerMaxDiskReadBytes_T,
           typename _ledgerMaxWriteLedgerEntries_T,
           typename _ledgerMaxWriteBytes_T,
           typename _txMaxDiskReadEntries_T,
           typename _txMaxDiskReadBytes_T,
           typename _txMaxWriteLedgerEntries_T,
           typename _txMaxWriteBytes_T,
           typename _feeDiskReadLedgerEntry_T,
           typename _feeWriteLedgerEntry_T,
           typename _feeDiskRead1KB_T,
           typename _sorobanStateTargetSizeBytes_T,
           typename _rentFee1KBSorobanStateSizeLow_T,
           typename _rentFee1KBSorobanStateSizeHigh_T,
           typename _sorobanStateRentFeeGrowthFactor_T,
           typename = typename
           std::enable_if<std::is_constructible<uint32, _ledgerMaxDiskReadEntries_T>::value
                          && std::is_constructible<uint32, _ledgerMaxDiskReadBytes_T>::value
                          && std::is_constructible<uint32, _ledgerMaxWriteLedgerEntries_T>::value
                          && std::is_constructible<uint32, _ledgerMaxWriteBytes_T>::value
                          && std::is_constructible<uint32, _txMaxDiskReadEntries_T>::value
                          && std::is_constructible<uint32, _txMaxDiskReadBytes_T>::value
                          && std::is_constructible<uint32, _txMaxWriteLedgerEntries_T>::value
                          && std::is_constructible<uint32, _txMaxWriteBytes_T>::value
                          && std::is_constructible<int64, _feeDiskReadLedgerEntry_T>::value
                          && std::is_constructible<int64, _feeWriteLedgerEntry_T>::value
                          && std::is_constructible<int64, _feeDiskRead1KB_T>::value
                          && std::is_constructible<int64, _sorobanStateTargetSizeBytes_T>::value
                          && std::is_constructible<int64, _rentFee1KBSorobanStateSizeLow_T>::value
                          && std::is_constructible<int64, _rentFee1KBSorobanStateSizeHigh_T>::value
                          && std::is_constructible<uint32, _sorobanStateRentFeeGrowthFactor_T>::value
                         >::type>
  explicit ConfigSettingContractLedgerCostV0(_ledgerMaxDiskReadEntries_T &&_ledgerMaxDiskReadEntries,
                                             _ledgerMaxDiskReadBytes_T &&_ledgerMaxDiskReadBytes,
                                             _ledgerMaxWriteLedgerEntries_T &&_ledgerMaxWriteLedgerEntries,
                                             _ledgerMaxWriteBytes_T &&_ledgerMaxWriteBytes,
                                             _txMaxDiskReadEntries_T &&_txMaxDiskReadEntries,
                                             _txMaxDiskReadBytes_T &&_txMaxDiskReadBytes,
                                             _txMaxWriteLedgerEntries_T &&_txMaxWriteLedgerEntries,
                                             _txMaxWriteBytes_T &&_txMaxWriteBytes,
                                             _feeDiskReadLedgerEntry_T &&_feeDiskReadLedgerEntry,
                                             _feeWriteLedgerEntry_T &&_feeWriteLedgerEntry,
                                             _feeDiskRead1KB_T &&_feeDiskRead1KB,
                                             _sorobanStateTargetSizeBytes_T &&_sorobanStateTargetSizeBytes,
                                             _rentFee1KBSorobanStateSizeLow_T &&_rentFee1KBSorobanStateSizeLow,
                                             _rentFee1KBSorobanStateSizeHigh_T &&_rentFee1KBSorobanStateSizeHigh,
                                             _sorobanStateRentFeeGrowthFactor_T &&_sorobanStateRentFeeGrowthFactor)
    : ledgerMaxDiskReadEntries(std::forward<_ledgerMaxDiskReadEntries_T>(_ledgerMaxDiskReadEntries)),
      ledgerMaxDiskReadBytes(std::forward<_ledgerMaxDiskReadBytes_T>(_ledgerMaxDiskReadBytes)),
      ledgerMaxWriteLedgerEntries(std::forward<_ledgerMaxWriteLedgerEntries_T>(_ledgerMaxWriteLedgerEntries)),
      ledgerMaxWriteBytes(std::forward<_ledgerMaxWriteBytes_T>(_ledgerMaxWriteBytes)),
      txMaxDiskReadEntries(std::forward<_txMaxDiskReadEntries_T>(_txMaxDiskReadEntries)),
      txMaxDiskReadBytes(std::forward<_txMaxDiskReadBytes_T>(_txMaxDiskReadBytes)),
      txMaxWriteLedgerEntries(std::forward<_txMaxWriteLedgerEntries_T>(_txMaxWriteLedgerEntries)),
      txMaxWriteBytes(std::forward<_txMaxWriteBytes_T>(_txMaxWriteBytes)),
      feeDiskReadLedgerEntry(std::forward<_feeDiskReadLedgerEntry_T>(_feeDiskReadLedgerEntry)),
      feeWriteLedgerEntry(std::forward<_feeWriteLedgerEntry_T>(_feeWriteLedgerEntry)),
      feeDiskRead1KB(std::forward<_feeDiskRead1KB_T>(_feeDiskRead1KB)),
      sorobanStateTargetSizeBytes(std::forward<_sorobanStateTargetSizeBytes_T>(_sorobanStateTargetSizeBytes)),
      rentFee1KBSorobanStateSizeLow(std::forward<_rentFee1KBSorobanStateSizeLow_T>(_rentFee1KBSorobanStateSizeLow)),
      rentFee1KBSorobanStateSizeHigh(std::forward<_rentFee1KBSorobanStateSizeHigh_T>(_rentFee1KBSorobanStateSizeHigh)),
      sorobanStateRentFeeGrowthFactor(std::forward<_sorobanStateRentFeeGrowthFactor_T>(_sorobanStateRentFeeGrowthFactor)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ConfigSettingContractLedgerCostV0>
  : xdr_struct_base<field_ptr<::stellar::ConfigSettingContractLedgerCostV0,
                              decltype(::stellar::ConfigSettingContractLedgerCostV0::ledgerMaxDiskReadEntries),
                              &::stellar::ConfigSettingContractLedgerCostV0::ledgerMaxDiskReadEntries>,
                    field_ptr<::stellar::ConfigSettingContractLedgerCostV0,
                              decltype(::stellar::ConfigSettingContractLedgerCostV0::ledgerMaxDiskReadBytes),
                              &::stellar::ConfigSettingContractLedgerCostV0::ledgerMaxDiskReadBytes>,
                    field_ptr<::stellar::ConfigSettingContractLedgerCostV0,
                              decltype(::stellar::ConfigSettingContractLedgerCostV0::ledgerMaxWriteLedgerEntries),
                              &::stellar::ConfigSettingContractLedgerCostV0::ledgerMaxWriteLedgerEntries>,
                    field_ptr<::stellar::ConfigSettingContractLedgerCostV0,
                              decltype(::stellar::ConfigSettingContractLedgerCostV0::ledgerMaxWriteBytes),
                              &::stellar::ConfigSettingContractLedgerCostV0::ledgerMaxWriteBytes>,
                    field_ptr<::stellar::ConfigSettingContractLedgerCostV0,
                              decltype(::stellar::ConfigSettingContractLedgerCostV0::txMaxDiskReadEntries),
                              &::stellar::ConfigSettingContractLedgerCostV0::txMaxDiskReadEntries>,
                    field_ptr<::stellar::ConfigSettingContractLedgerCostV0,
                              decltype(::stellar::ConfigSettingContractLedgerCostV0::txMaxDiskReadBytes),
                              &::stellar::ConfigSettingContractLedgerCostV0::txMaxDiskReadBytes>,
                    field_ptr<::stellar::ConfigSettingContractLedgerCostV0,
                              decltype(::stellar::ConfigSettingContractLedgerCostV0::txMaxWriteLedgerEntries),
                              &::stellar::ConfigSettingContractLedgerCostV0::txMaxWriteLedgerEntries>,
                    field_ptr<::stellar::ConfigSettingContractLedgerCostV0,
                              decltype(::stellar::ConfigSettingContractLedgerCostV0::txMaxWriteBytes),
                              &::stellar::ConfigSettingContractLedgerCostV0::txMaxWriteBytes>,
                    field_ptr<::stellar::ConfigSettingContractLedgerCostV0,
                              decltype(::stellar::ConfigSettingContractLedgerCostV0::feeDiskReadLedgerEntry),
                              &::stellar::ConfigSettingContractLedgerCostV0::feeDiskReadLedgerEntry>,
                    field_ptr<::stellar::ConfigSettingContractLedgerCostV0,
                              decltype(::stellar::ConfigSettingContractLedgerCostV0::feeWriteLedgerEntry),
                              &::stellar::ConfigSettingContractLedgerCostV0::feeWriteLedgerEntry>,
                    field_ptr<::stellar::ConfigSettingContractLedgerCostV0,
                              decltype(::stellar::ConfigSettingContractLedgerCostV0::feeDiskRead1KB),
                              &::stellar::ConfigSettingContractLedgerCostV0::feeDiskRead1KB>,
                    field_ptr<::stellar::ConfigSettingContractLedgerCostV0,
                              decltype(::stellar::ConfigSettingContractLedgerCostV0::sorobanStateTargetSizeBytes),
                              &::stellar::ConfigSettingContractLedgerCostV0::sorobanStateTargetSizeBytes>,
                    field_ptr<::stellar::ConfigSettingContractLedgerCostV0,
                              decltype(::stellar::ConfigSettingContractLedgerCostV0::rentFee1KBSorobanStateSizeLow),
                              &::stellar::ConfigSettingContractLedgerCostV0::rentFee1KBSorobanStateSizeLow>,
                    field_ptr<::stellar::ConfigSettingContractLedgerCostV0,
                              decltype(::stellar::ConfigSettingContractLedgerCostV0::rentFee1KBSorobanStateSizeHigh),
                              &::stellar::ConfigSettingContractLedgerCostV0::rentFee1KBSorobanStateSizeHigh>,
                    field_ptr<::stellar::ConfigSettingContractLedgerCostV0,
                              decltype(::stellar::ConfigSettingContractLedgerCostV0::sorobanStateRentFeeGrowthFactor),
                              &::stellar::ConfigSettingContractLedgerCostV0::sorobanStateRentFeeGrowthFactor>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ConfigSettingContractLedgerCostV0 &obj) {
    archive(ar, obj.ledgerMaxDiskReadEntries, "ledgerMaxDiskReadEntries");
    archive(ar, obj.ledgerMaxDiskReadBytes, "ledgerMaxDiskReadBytes");
    archive(ar, obj.ledgerMaxWriteLedgerEntries, "ledgerMaxWriteLedgerEntries");
    archive(ar, obj.ledgerMaxWriteBytes, "ledgerMaxWriteBytes");
    archive(ar, obj.txMaxDiskReadEntries, "txMaxDiskReadEntries");
    archive(ar, obj.txMaxDiskReadBytes, "txMaxDiskReadBytes");
    archive(ar, obj.txMaxWriteLedgerEntries, "txMaxWriteLedgerEntries");
    archive(ar, obj.txMaxWriteBytes, "txMaxWriteBytes");
    archive(ar, obj.feeDiskReadLedgerEntry, "feeDiskReadLedgerEntry");
    archive(ar, obj.feeWriteLedgerEntry, "feeWriteLedgerEntry");
    archive(ar, obj.feeDiskRead1KB, "feeDiskRead1KB");
    archive(ar, obj.sorobanStateTargetSizeBytes, "sorobanStateTargetSizeBytes");
    archive(ar, obj.rentFee1KBSorobanStateSizeLow, "rentFee1KBSorobanStateSizeLow");
    archive(ar, obj.rentFee1KBSorobanStateSizeHigh, "rentFee1KBSorobanStateSizeHigh");
    archive(ar, obj.sorobanStateRentFeeGrowthFactor, "sorobanStateRentFeeGrowthFactor");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ConfigSettingContractLedgerCostV0 &obj) {
    archive(ar, obj.ledgerMaxDiskReadEntries, "ledgerMaxDiskReadEntries");
    archive(ar, obj.ledgerMaxDiskReadBytes, "ledgerMaxDiskReadBytes");
    archive(ar, obj.ledgerMaxWriteLedgerEntries, "ledgerMaxWriteLedgerEntries");
    archive(ar, obj.ledgerMaxWriteBytes, "ledgerMaxWriteBytes");
    archive(ar, obj.txMaxDiskReadEntries, "txMaxDiskReadEntries");
    archive(ar, obj.txMaxDiskReadBytes, "txMaxDiskReadBytes");
    archive(ar, obj.txMaxWriteLedgerEntries, "txMaxWriteLedgerEntries");
    archive(ar, obj.txMaxWriteBytes, "txMaxWriteBytes");
    archive(ar, obj.feeDiskReadLedgerEntry, "feeDiskReadLedgerEntry");
    archive(ar, obj.feeWriteLedgerEntry, "feeWriteLedgerEntry");
    archive(ar, obj.feeDiskRead1KB, "feeDiskRead1KB");
    archive(ar, obj.sorobanStateTargetSizeBytes, "sorobanStateTargetSizeBytes");
    archive(ar, obj.rentFee1KBSorobanStateSizeLow, "rentFee1KBSorobanStateSizeLow");
    archive(ar, obj.rentFee1KBSorobanStateSizeHigh, "rentFee1KBSorobanStateSizeHigh");
    archive(ar, obj.sorobanStateRentFeeGrowthFactor, "sorobanStateRentFeeGrowthFactor");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ConfigSettingContractLedgerCostExtV0 {
  uint32 txMaxFootprintEntries{};
  int64 feeWrite1KB{};

  ConfigSettingContractLedgerCostExtV0() = default;
  template<typename _txMaxFootprintEntries_T,
           typename _feeWrite1KB_T,
           typename = typename
           std::enable_if<std::is_constructible<uint32, _txMaxFootprintEntries_T>::value
                          && std::is_constructible<int64, _feeWrite1KB_T>::value
                         >::type>
  explicit ConfigSettingContractLedgerCostExtV0(_txMaxFootprintEntries_T &&_txMaxFootprintEntries,
                                                _feeWrite1KB_T &&_feeWrite1KB)
    : txMaxFootprintEntries(std::forward<_txMaxFootprintEntries_T>(_txMaxFootprintEntries)),
      feeWrite1KB(std::forward<_feeWrite1KB_T>(_feeWrite1KB)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ConfigSettingContractLedgerCostExtV0>
  : xdr_struct_base<field_ptr<::stellar::ConfigSettingContractLedgerCostExtV0,
                              decltype(::stellar::ConfigSettingContractLedgerCostExtV0::txMaxFootprintEntries),
                              &::stellar::ConfigSettingContractLedgerCostExtV0::txMaxFootprintEntries>,
                    field_ptr<::stellar::ConfigSettingContractLedgerCostExtV0,
                              decltype(::stellar::ConfigSettingContractLedgerCostExtV0::feeWrite1KB),
                              &::stellar::ConfigSettingContractLedgerCostExtV0::feeWrite1KB>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ConfigSettingContractLedgerCostExtV0 &obj) {
    archive(ar, obj.txMaxFootprintEntries, "txMaxFootprintEntries");
    archive(ar, obj.feeWrite1KB, "feeWrite1KB");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ConfigSettingContractLedgerCostExtV0 &obj) {
    archive(ar, obj.txMaxFootprintEntries, "txMaxFootprintEntries");
    archive(ar, obj.feeWrite1KB, "feeWrite1KB");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ConfigSettingContractHistoricalDataV0 {
  int64 feeHistorical1KB{};

  ConfigSettingContractHistoricalDataV0() = default;
  template<typename _feeHistorical1KB_T,
           typename = typename
           std::enable_if<std::is_constructible<int64, _feeHistorical1KB_T>::value
                         >::type>
  explicit ConfigSettingContractHistoricalDataV0(_feeHistorical1KB_T &&_feeHistorical1KB)
    : feeHistorical1KB(std::forward<_feeHistorical1KB_T>(_feeHistorical1KB)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ConfigSettingContractHistoricalDataV0>
  : xdr_struct_base<field_ptr<::stellar::ConfigSettingContractHistoricalDataV0,
                              decltype(::stellar::ConfigSettingContractHistoricalDataV0::feeHistorical1KB),
                              &::stellar::ConfigSettingContractHistoricalDataV0::feeHistorical1KB>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ConfigSettingContractHistoricalDataV0 &obj) {
    archive(ar, obj.feeHistorical1KB, "feeHistorical1KB");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ConfigSettingContractHistoricalDataV0 &obj) {
    archive(ar, obj.feeHistorical1KB, "feeHistorical1KB");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ConfigSettingContractEventsV0 {
  uint32 txMaxContractEventsSizeBytes{};
  int64 feeContractEvents1KB{};

  ConfigSettingContractEventsV0() = default;
  template<typename _txMaxContractEventsSizeBytes_T,
           typename _feeContractEvents1KB_T,
           typename = typename
           std::enable_if<std::is_constructible<uint32, _txMaxContractEventsSizeBytes_T>::value
                          && std::is_constructible<int64, _feeContractEvents1KB_T>::value
                         >::type>
  explicit ConfigSettingContractEventsV0(_txMaxContractEventsSizeBytes_T &&_txMaxContractEventsSizeBytes,
                                         _feeContractEvents1KB_T &&_feeContractEvents1KB)
    : txMaxContractEventsSizeBytes(std::forward<_txMaxContractEventsSizeBytes_T>(_txMaxContractEventsSizeBytes)),
      feeContractEvents1KB(std::forward<_feeContractEvents1KB_T>(_feeContractEvents1KB)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ConfigSettingContractEventsV0>
  : xdr_struct_base<field_ptr<::stellar::ConfigSettingContractEventsV0,
                              decltype(::stellar::ConfigSettingContractEventsV0::txMaxContractEventsSizeBytes),
                              &::stellar::ConfigSettingContractEventsV0::txMaxContractEventsSizeBytes>,
                    field_ptr<::stellar::ConfigSettingContractEventsV0,
                              decltype(::stellar::ConfigSettingContractEventsV0::feeContractEvents1KB),
                              &::stellar::ConfigSettingContractEventsV0::feeContractEvents1KB>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ConfigSettingContractEventsV0 &obj) {
    archive(ar, obj.txMaxContractEventsSizeBytes, "txMaxContractEventsSizeBytes");
    archive(ar, obj.feeContractEvents1KB, "feeContractEvents1KB");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ConfigSettingContractEventsV0 &obj) {
    archive(ar, obj.txMaxContractEventsSizeBytes, "txMaxContractEventsSizeBytes");
    archive(ar, obj.feeContractEvents1KB, "feeContractEvents1KB");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ConfigSettingContractBandwidthV0 {
  uint32 ledgerMaxTxsSizeBytes{};
  uint32 txMaxSizeBytes{};
  int64 feeTxSize1KB{};

  ConfigSettingContractBandwidthV0() = default;
  template<typename _ledgerMaxTxsSizeBytes_T,
           typename _txMaxSizeBytes_T,
           typename _feeTxSize1KB_T,
           typename = typename
           std::enable_if<std::is_constructible<uint32, _ledgerMaxTxsSizeBytes_T>::value
                          && std::is_constructible<uint32, _txMaxSizeBytes_T>::value
                          && std::is_constructible<int64, _feeTxSize1KB_T>::value
                         >::type>
  explicit ConfigSettingContractBandwidthV0(_ledgerMaxTxsSizeBytes_T &&_ledgerMaxTxsSizeBytes,
                                            _txMaxSizeBytes_T &&_txMaxSizeBytes,
                                            _feeTxSize1KB_T &&_feeTxSize1KB)
    : ledgerMaxTxsSizeBytes(std::forward<_ledgerMaxTxsSizeBytes_T>(_ledgerMaxTxsSizeBytes)),
      txMaxSizeBytes(std::forward<_txMaxSizeBytes_T>(_txMaxSizeBytes)),
      feeTxSize1KB(std::forward<_feeTxSize1KB_T>(_feeTxSize1KB)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ConfigSettingContractBandwidthV0>
  : xdr_struct_base<field_ptr<::stellar::ConfigSettingContractBandwidthV0,
                              decltype(::stellar::ConfigSettingContractBandwidthV0::ledgerMaxTxsSizeBytes),
                              &::stellar::ConfigSettingContractBandwidthV0::ledgerMaxTxsSizeBytes>,
                    field_ptr<::stellar::ConfigSettingContractBandwidthV0,
                              decltype(::stellar::ConfigSettingContractBandwidthV0::txMaxSizeBytes),
                              &::stellar::ConfigSettingContractBandwidthV0::txMaxSizeBytes>,
                    field_ptr<::stellar::ConfigSettingContractBandwidthV0,
                              decltype(::stellar::ConfigSettingContractBandwidthV0::feeTxSize1KB),
                              &::stellar::ConfigSettingContractBandwidthV0::feeTxSize1KB>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ConfigSettingContractBandwidthV0 &obj) {
    archive(ar, obj.ledgerMaxTxsSizeBytes, "ledgerMaxTxsSizeBytes");
    archive(ar, obj.txMaxSizeBytes, "txMaxSizeBytes");
    archive(ar, obj.feeTxSize1KB, "feeTxSize1KB");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ConfigSettingContractBandwidthV0 &obj) {
    archive(ar, obj.ledgerMaxTxsSizeBytes, "ledgerMaxTxsSizeBytes");
    archive(ar, obj.txMaxSizeBytes, "txMaxSizeBytes");
    archive(ar, obj.feeTxSize1KB, "feeTxSize1KB");
    xdr::validate(obj);
  }
};
} namespace stellar {

enum ContractCostType : std::int32_t {
  WasmInsnExec = 0,
  MemAlloc = 1,
  MemCpy = 2,
  MemCmp = 3,
  DispatchHostFunction = 4,
  VisitObject = 5,
  ValSer = 6,
  ValDeser = 7,
  ComputeSha256Hash = 8,
  ComputeEd25519PubKey = 9,
  VerifyEd25519Sig = 10,
  VmInstantiation = 11,
  VmCachedInstantiation = 12,
  InvokeVmFunction = 13,
  ComputeKeccak256Hash = 14,
  DecodeEcdsaCurve256Sig = 15,
  RecoverEcdsaSecp256k1Key = 16,
  Int256AddSub = 17,
  Int256Mul = 18,
  Int256Div = 19,
  Int256Pow = 20,
  Int256Shift = 21,
  ChaCha20DrawBytes = 22,
  ParseWasmInstructions = 23,
  ParseWasmFunctions = 24,
  ParseWasmGlobals = 25,
  ParseWasmTableEntries = 26,
  ParseWasmTypes = 27,
  ParseWasmDataSegments = 28,
  ParseWasmElemSegments = 29,
  ParseWasmImports = 30,
  ParseWasmExports = 31,
  ParseWasmDataSegmentBytes = 32,
  InstantiateWasmInstructions = 33,
  InstantiateWasmFunctions = 34,
  InstantiateWasmGlobals = 35,
  InstantiateWasmTableEntries = 36,
  InstantiateWasmTypes = 37,
  InstantiateWasmDataSegments = 38,
  InstantiateWasmElemSegments = 39,
  InstantiateWasmImports = 40,
  InstantiateWasmExports = 41,
  InstantiateWasmDataSegmentBytes = 42,
  Sec1DecodePointUncompressed = 43,
  VerifyEcdsaSecp256r1Sig = 44,
  Bls12381EncodeFp = 45,
  Bls12381DecodeFp = 46,
  Bls12381G1CheckPointOnCurve = 47,
  Bls12381G1CheckPointInSubgroup = 48,
  Bls12381G2CheckPointOnCurve = 49,
  Bls12381G2CheckPointInSubgroup = 50,
  Bls12381G1ProjectiveToAffine = 51,
  Bls12381G2ProjectiveToAffine = 52,
  Bls12381G1Add = 53,
  Bls12381G1Mul = 54,
  Bls12381G1Msm = 55,
  Bls12381MapFpToG1 = 56,
  Bls12381HashToG1 = 57,
  Bls12381G2Add = 58,
  Bls12381G2Mul = 59,
  Bls12381G2Msm = 60,
  Bls12381MapFp2ToG2 = 61,
  Bls12381HashToG2 = 62,
  Bls12381Pairing = 63,
  Bls12381FrFromU256 = 64,
  Bls12381FrToU256 = 65,
  Bls12381FrAddSub = 66,
  Bls12381FrMul = 67,
  Bls12381FrPow = 68,
  Bls12381FrInv = 69,
  Bn254EncodeFp = 70,
  Bn254DecodeFp = 71,
  Bn254G1CheckPointOnCurve = 72,
  Bn254G2CheckPointOnCurve = 73,
  Bn254G2CheckPointInSubgroup = 74,
  Bn254G1ProjectiveToAffine = 75,
  Bn254G1Add = 76,
  Bn254G1Mul = 77,
  Bn254Pairing = 78,
  Bn254FrFromU256 = 79,
  Bn254FrToU256 = 80,
  Bn254FrAddSub = 81,
  Bn254FrMul = 82,
  Bn254FrPow = 83,
  Bn254FrInv = 84,
  Bn254G1Msm = 85,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ContractCostType>
  : xdr_integral_base<::stellar::ContractCostType, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ContractCostType val) {
    switch (val) {
    case ::stellar::WasmInsnExec:
      return "WasmInsnExec";
    case ::stellar::MemAlloc:
      return "MemAlloc";
    case ::stellar::MemCpy:
      return "MemCpy";
    case ::stellar::MemCmp:
      return "MemCmp";
    case ::stellar::DispatchHostFunction:
      return "DispatchHostFunction";
    case ::stellar::VisitObject:
      return "VisitObject";
    case ::stellar::ValSer:
      return "ValSer";
    case ::stellar::ValDeser:
      return "ValDeser";
    case ::stellar::ComputeSha256Hash:
      return "ComputeSha256Hash";
    case ::stellar::ComputeEd25519PubKey:
      return "ComputeEd25519PubKey";
    case ::stellar::VerifyEd25519Sig:
      return "VerifyEd25519Sig";
    case ::stellar::VmInstantiation:
      return "VmInstantiation";
    case ::stellar::VmCachedInstantiation:
      return "VmCachedInstantiation";
    case ::stellar::InvokeVmFunction:
      return "InvokeVmFunction";
    case ::stellar::ComputeKeccak256Hash:
      return "ComputeKeccak256Hash";
    case ::stellar::DecodeEcdsaCurve256Sig:
      return "DecodeEcdsaCurve256Sig";
    case ::stellar::RecoverEcdsaSecp256k1Key:
      return "RecoverEcdsaSecp256k1Key";
    case ::stellar::Int256AddSub:
      return "Int256AddSub";
    case ::stellar::Int256Mul:
      return "Int256Mul";
    case ::stellar::Int256Div:
      return "Int256Div";
    case ::stellar::Int256Pow:
      return "Int256Pow";
    case ::stellar::Int256Shift:
      return "Int256Shift";
    case ::stellar::ChaCha20DrawBytes:
      return "ChaCha20DrawBytes";
    case ::stellar::ParseWasmInstructions:
      return "ParseWasmInstructions";
    case ::stellar::ParseWasmFunctions:
      return "ParseWasmFunctions";
    case ::stellar::ParseWasmGlobals:
      return "ParseWasmGlobals";
    case ::stellar::ParseWasmTableEntries:
      return "ParseWasmTableEntries";
    case ::stellar::ParseWasmTypes:
      return "ParseWasmTypes";
    case ::stellar::ParseWasmDataSegments:
      return "ParseWasmDataSegments";
    case ::stellar::ParseWasmElemSegments:
      return "ParseWasmElemSegments";
    case ::stellar::ParseWasmImports:
      return "ParseWasmImports";
    case ::stellar::ParseWasmExports:
      return "ParseWasmExports";
    case ::stellar::ParseWasmDataSegmentBytes:
      return "ParseWasmDataSegmentBytes";
    case ::stellar::InstantiateWasmInstructions:
      return "InstantiateWasmInstructions";
    case ::stellar::InstantiateWasmFunctions:
      return "InstantiateWasmFunctions";
    case ::stellar::InstantiateWasmGlobals:
      return "InstantiateWasmGlobals";
    case ::stellar::InstantiateWasmTableEntries:
      return "InstantiateWasmTableEntries";
    case ::stellar::InstantiateWasmTypes:
      return "InstantiateWasmTypes";
    case ::stellar::InstantiateWasmDataSegments:
      return "InstantiateWasmDataSegments";
    case ::stellar::InstantiateWasmElemSegments:
      return "InstantiateWasmElemSegments";
    case ::stellar::InstantiateWasmImports:
      return "InstantiateWasmImports";
    case ::stellar::InstantiateWasmExports:
      return "InstantiateWasmExports";
    case ::stellar::InstantiateWasmDataSegmentBytes:
      return "InstantiateWasmDataSegmentBytes";
    case ::stellar::Sec1DecodePointUncompressed:
      return "Sec1DecodePointUncompressed";
    case ::stellar::VerifyEcdsaSecp256r1Sig:
      return "VerifyEcdsaSecp256r1Sig";
    case ::stellar::Bls12381EncodeFp:
      return "Bls12381EncodeFp";
    case ::stellar::Bls12381DecodeFp:
      return "Bls12381DecodeFp";
    case ::stellar::Bls12381G1CheckPointOnCurve:
      return "Bls12381G1CheckPointOnCurve";
    case ::stellar::Bls12381G1CheckPointInSubgroup:
      return "Bls12381G1CheckPointInSubgroup";
    case ::stellar::Bls12381G2CheckPointOnCurve:
      return "Bls12381G2CheckPointOnCurve";
    case ::stellar::Bls12381G2CheckPointInSubgroup:
      return "Bls12381G2CheckPointInSubgroup";
    case ::stellar::Bls12381G1ProjectiveToAffine:
      return "Bls12381G1ProjectiveToAffine";
    case ::stellar::Bls12381G2ProjectiveToAffine:
      return "Bls12381G2ProjectiveToAffine";
    case ::stellar::Bls12381G1Add:
      return "Bls12381G1Add";
    case ::stellar::Bls12381G1Mul:
      return "Bls12381G1Mul";
    case ::stellar::Bls12381G1Msm:
      return "Bls12381G1Msm";
    case ::stellar::Bls12381MapFpToG1:
      return "Bls12381MapFpToG1";
    case ::stellar::Bls12381HashToG1:
      return "Bls12381HashToG1";
    case ::stellar::Bls12381G2Add:
      return "Bls12381G2Add";
    case ::stellar::Bls12381G2Mul:
      return "Bls12381G2Mul";
    case ::stellar::Bls12381G2Msm:
      return "Bls12381G2Msm";
    case ::stellar::Bls12381MapFp2ToG2:
      return "Bls12381MapFp2ToG2";
    case ::stellar::Bls12381HashToG2:
      return "Bls12381HashToG2";
    case ::stellar::Bls12381Pairing:
      return "Bls12381Pairing";
    case ::stellar::Bls12381FrFromU256:
      return "Bls12381FrFromU256";
    case ::stellar::Bls12381FrToU256:
      return "Bls12381FrToU256";
    case ::stellar::Bls12381FrAddSub:
      return "Bls12381FrAddSub";
    case ::stellar::Bls12381FrMul:
      return "Bls12381FrMul";
    case ::stellar::Bls12381FrPow:
      return "Bls12381FrPow";
    case ::stellar::Bls12381FrInv:
      return "Bls12381FrInv";
    case ::stellar::Bn254EncodeFp:
      return "Bn254EncodeFp";
    case ::stellar::Bn254DecodeFp:
      return "Bn254DecodeFp";
    case ::stellar::Bn254G1CheckPointOnCurve:
      return "Bn254G1CheckPointOnCurve";
    case ::stellar::Bn254G2CheckPointOnCurve:
      return "Bn254G2CheckPointOnCurve";
    case ::stellar::Bn254G2CheckPointInSubgroup:
      return "Bn254G2CheckPointInSubgroup";
    case ::stellar::Bn254G1ProjectiveToAffine:
      return "Bn254G1ProjectiveToAffine";
    case ::stellar::Bn254G1Add:
      return "Bn254G1Add";
    case ::stellar::Bn254G1Mul:
      return "Bn254G1Mul";
    case ::stellar::Bn254Pairing:
      return "Bn254Pairing";
    case ::stellar::Bn254FrFromU256:
      return "Bn254FrFromU256";
    case ::stellar::Bn254FrToU256:
      return "Bn254FrToU256";
    case ::stellar::Bn254FrAddSub:
      return "Bn254FrAddSub";
    case ::stellar::Bn254FrMul:
      return "Bn254FrMul";
    case ::stellar::Bn254FrPow:
      return "Bn254FrPow";
    case ::stellar::Bn254FrInv:
      return "Bn254FrInv";
    case ::stellar::Bn254G1Msm:
      return "Bn254G1Msm";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::WasmInsnExec,
      ::stellar::MemAlloc,
      ::stellar::MemCpy,
      ::stellar::MemCmp,
      ::stellar::DispatchHostFunction,
      ::stellar::VisitObject,
      ::stellar::ValSer,
      ::stellar::ValDeser,
      ::stellar::ComputeSha256Hash,
      ::stellar::ComputeEd25519PubKey,
      ::stellar::VerifyEd25519Sig,
      ::stellar::VmInstantiation,
      ::stellar::VmCachedInstantiation,
      ::stellar::InvokeVmFunction,
      ::stellar::ComputeKeccak256Hash,
      ::stellar::DecodeEcdsaCurve256Sig,
      ::stellar::RecoverEcdsaSecp256k1Key,
      ::stellar::Int256AddSub,
      ::stellar::Int256Mul,
      ::stellar::Int256Div,
      ::stellar::Int256Pow,
      ::stellar::Int256Shift,
      ::stellar::ChaCha20DrawBytes,
      ::stellar::ParseWasmInstructions,
      ::stellar::ParseWasmFunctions,
      ::stellar::ParseWasmGlobals,
      ::stellar::ParseWasmTableEntries,
      ::stellar::ParseWasmTypes,
      ::stellar::ParseWasmDataSegments,
      ::stellar::ParseWasmElemSegments,
      ::stellar::ParseWasmImports,
      ::stellar::ParseWasmExports,
      ::stellar::ParseWasmDataSegmentBytes,
      ::stellar::InstantiateWasmInstructions,
      ::stellar::InstantiateWasmFunctions,
      ::stellar::InstantiateWasmGlobals,
      ::stellar::InstantiateWasmTableEntries,
      ::stellar::InstantiateWasmTypes,
      ::stellar::InstantiateWasmDataSegments,
      ::stellar::InstantiateWasmElemSegments,
      ::stellar::InstantiateWasmImports,
      ::stellar::InstantiateWasmExports,
      ::stellar::InstantiateWasmDataSegmentBytes,
      ::stellar::Sec1DecodePointUncompressed,
      ::stellar::VerifyEcdsaSecp256r1Sig,
      ::stellar::Bls12381EncodeFp,
      ::stellar::Bls12381DecodeFp,
      ::stellar::Bls12381G1CheckPointOnCurve,
      ::stellar::Bls12381G1CheckPointInSubgroup,
      ::stellar::Bls12381G2CheckPointOnCurve,
      ::stellar::Bls12381G2CheckPointInSubgroup,
      ::stellar::Bls12381G1ProjectiveToAffine,
      ::stellar::Bls12381G2ProjectiveToAffine,
      ::stellar::Bls12381G1Add,
      ::stellar::Bls12381G1Mul,
      ::stellar::Bls12381G1Msm,
      ::stellar::Bls12381MapFpToG1,
      ::stellar::Bls12381HashToG1,
      ::stellar::Bls12381G2Add,
      ::stellar::Bls12381G2Mul,
      ::stellar::Bls12381G2Msm,
      ::stellar::Bls12381MapFp2ToG2,
      ::stellar::Bls12381HashToG2,
      ::stellar::Bls12381Pairing,
      ::stellar::Bls12381FrFromU256,
      ::stellar::Bls12381FrToU256,
      ::stellar::Bls12381FrAddSub,
      ::stellar::Bls12381FrMul,
      ::stellar::Bls12381FrPow,
      ::stellar::Bls12381FrInv,
      ::stellar::Bn254EncodeFp,
      ::stellar::Bn254DecodeFp,
      ::stellar::Bn254G1CheckPointOnCurve,
      ::stellar::Bn254G2CheckPointOnCurve,
      ::stellar::Bn254G2CheckPointInSubgroup,
      ::stellar::Bn254G1ProjectiveToAffine,
      ::stellar::Bn254G1Add,
      ::stellar::Bn254G1Mul,
      ::stellar::Bn254Pairing,
      ::stellar::Bn254FrFromU256,
      ::stellar::Bn254FrToU256,
      ::stellar::Bn254FrAddSub,
      ::stellar::Bn254FrMul,
      ::stellar::Bn254FrPow,
      ::stellar::Bn254FrInv,
      ::stellar::Bn254G1Msm
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct ContractCostParamEntry {
  ExtensionPoint ext{};
  int64 constTerm{};
  int64 linearTerm{};

  ContractCostParamEntry() = default;
  template<typename _ext_T,
           typename _constTerm_T,
           typename _linearTerm_T,
           typename = typename
           std::enable_if<std::is_constructible<ExtensionPoint, _ext_T>::value
                          && std::is_constructible<int64, _constTerm_T>::value
                          && std::is_constructible<int64, _linearTerm_T>::value
                         >::type>
  explicit ContractCostParamEntry(_ext_T &&_ext,
                                  _constTerm_T &&_constTerm,
                                  _linearTerm_T &&_linearTerm)
    : ext(std::forward<_ext_T>(_ext)),
      constTerm(std::forward<_constTerm_T>(_constTerm)),
      linearTerm(std::forward<_linearTerm_T>(_linearTerm)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ContractCostParamEntry>
  : xdr_struct_base<field_ptr<::stellar::ContractCostParamEntry,
                              decltype(::stellar::ContractCostParamEntry::ext),
                              &::stellar::ContractCostParamEntry::ext>,
                    field_ptr<::stellar::ContractCostParamEntry,
                              decltype(::stellar::ContractCostParamEntry::constTerm),
                              &::stellar::ContractCostParamEntry::constTerm>,
                    field_ptr<::stellar::ContractCostParamEntry,
                              decltype(::stellar::ContractCostParamEntry::linearTerm),
                              &::stellar::ContractCostParamEntry::linearTerm>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ContractCostParamEntry &obj) {
    archive(ar, obj.ext, "ext");
    archive(ar, obj.constTerm, "constTerm");
    archive(ar, obj.linearTerm, "linearTerm");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ContractCostParamEntry &obj) {
    archive(ar, obj.ext, "ext");
    archive(ar, obj.constTerm, "constTerm");
    archive(ar, obj.linearTerm, "linearTerm");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct StateArchivalSettings {
  uint32 maxEntryTTL{};
  uint32 minTemporaryTTL{};
  uint32 minPersistentTTL{};
  int64 persistentRentRateDenominator{};
  int64 tempRentRateDenominator{};
  uint32 maxEntriesToArchive{};
  uint32 liveSorobanStateSizeWindowSampleSize{};
  uint32 liveSorobanStateSizeWindowSamplePeriod{};
  uint32 evictionScanSize{};
  uint32 startingEvictionScanLevel{};

  StateArchivalSettings() = default;
  template<typename _maxEntryTTL_T,
           typename _minTemporaryTTL_T,
           typename _minPersistentTTL_T,
           typename _persistentRentRateDenominator_T,
           typename _tempRentRateDenominator_T,
           typename _maxEntriesToArchive_T,
           typename _liveSorobanStateSizeWindowSampleSize_T,
           typename _liveSorobanStateSizeWindowSamplePeriod_T,
           typename _evictionScanSize_T,
           typename _startingEvictionScanLevel_T,
           typename = typename
           std::enable_if<std::is_constructible<uint32, _maxEntryTTL_T>::value
                          && std::is_constructible<uint32, _minTemporaryTTL_T>::value
                          && std::is_constructible<uint32, _minPersistentTTL_T>::value
                          && std::is_constructible<int64, _persistentRentRateDenominator_T>::value
                          && std::is_constructible<int64, _tempRentRateDenominator_T>::value
                          && std::is_constructible<uint32, _maxEntriesToArchive_T>::value
                          && std::is_constructible<uint32, _liveSorobanStateSizeWindowSampleSize_T>::value
                          && std::is_constructible<uint32, _liveSorobanStateSizeWindowSamplePeriod_T>::value
                          && std::is_constructible<uint32, _evictionScanSize_T>::value
                          && std::is_constructible<uint32, _startingEvictionScanLevel_T>::value
                         >::type>
  explicit StateArchivalSettings(_maxEntryTTL_T &&_maxEntryTTL,
                                 _minTemporaryTTL_T &&_minTemporaryTTL,
                                 _minPersistentTTL_T &&_minPersistentTTL,
                                 _persistentRentRateDenominator_T &&_persistentRentRateDenominator,
                                 _tempRentRateDenominator_T &&_tempRentRateDenominator,
                                 _maxEntriesToArchive_T &&_maxEntriesToArchive,
                                 _liveSorobanStateSizeWindowSampleSize_T &&_liveSorobanStateSizeWindowSampleSize,
                                 _liveSorobanStateSizeWindowSamplePeriod_T &&_liveSorobanStateSizeWindowSamplePeriod,
                                 _evictionScanSize_T &&_evictionScanSize,
                                 _startingEvictionScanLevel_T &&_startingEvictionScanLevel)
    : maxEntryTTL(std::forward<_maxEntryTTL_T>(_maxEntryTTL)),
      minTemporaryTTL(std::forward<_minTemporaryTTL_T>(_minTemporaryTTL)),
      minPersistentTTL(std::forward<_minPersistentTTL_T>(_minPersistentTTL)),
      persistentRentRateDenominator(std::forward<_persistentRentRateDenominator_T>(_persistentRentRateDenominator)),
      tempRentRateDenominator(std::forward<_tempRentRateDenominator_T>(_tempRentRateDenominator)),
      maxEntriesToArchive(std::forward<_maxEntriesToArchive_T>(_maxEntriesToArchive)),
      liveSorobanStateSizeWindowSampleSize(std::forward<_liveSorobanStateSizeWindowSampleSize_T>(_liveSorobanStateSizeWindowSampleSize)),
      liveSorobanStateSizeWindowSamplePeriod(std::forward<_liveSorobanStateSizeWindowSamplePeriod_T>(_liveSorobanStateSizeWindowSamplePeriod)),
      evictionScanSize(std::forward<_evictionScanSize_T>(_evictionScanSize)),
      startingEvictionScanLevel(std::forward<_startingEvictionScanLevel_T>(_startingEvictionScanLevel)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::StateArchivalSettings>
  : xdr_struct_base<field_ptr<::stellar::StateArchivalSettings,
                              decltype(::stellar::StateArchivalSettings::maxEntryTTL),
                              &::stellar::StateArchivalSettings::maxEntryTTL>,
                    field_ptr<::stellar::StateArchivalSettings,
                              decltype(::stellar::StateArchivalSettings::minTemporaryTTL),
                              &::stellar::StateArchivalSettings::minTemporaryTTL>,
                    field_ptr<::stellar::StateArchivalSettings,
                              decltype(::stellar::StateArchivalSettings::minPersistentTTL),
                              &::stellar::StateArchivalSettings::minPersistentTTL>,
                    field_ptr<::stellar::StateArchivalSettings,
                              decltype(::stellar::StateArchivalSettings::persistentRentRateDenominator),
                              &::stellar::StateArchivalSettings::persistentRentRateDenominator>,
                    field_ptr<::stellar::StateArchivalSettings,
                              decltype(::stellar::StateArchivalSettings::tempRentRateDenominator),
                              &::stellar::StateArchivalSettings::tempRentRateDenominator>,
                    field_ptr<::stellar::StateArchivalSettings,
                              decltype(::stellar::StateArchivalSettings::maxEntriesToArchive),
                              &::stellar::StateArchivalSettings::maxEntriesToArchive>,
                    field_ptr<::stellar::StateArchivalSettings,
                              decltype(::stellar::StateArchivalSettings::liveSorobanStateSizeWindowSampleSize),
                              &::stellar::StateArchivalSettings::liveSorobanStateSizeWindowSampleSize>,
                    field_ptr<::stellar::StateArchivalSettings,
                              decltype(::stellar::StateArchivalSettings::liveSorobanStateSizeWindowSamplePeriod),
                              &::stellar::StateArchivalSettings::liveSorobanStateSizeWindowSamplePeriod>,
                    field_ptr<::stellar::StateArchivalSettings,
                              decltype(::stellar::StateArchivalSettings::evictionScanSize),
                              &::stellar::StateArchivalSettings::evictionScanSize>,
                    field_ptr<::stellar::StateArchivalSettings,
                              decltype(::stellar::StateArchivalSettings::startingEvictionScanLevel),
                              &::stellar::StateArchivalSettings::startingEvictionScanLevel>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::StateArchivalSettings &obj) {
    archive(ar, obj.maxEntryTTL, "maxEntryTTL");
    archive(ar, obj.minTemporaryTTL, "minTemporaryTTL");
    archive(ar, obj.minPersistentTTL, "minPersistentTTL");
    archive(ar, obj.persistentRentRateDenominator, "persistentRentRateDenominator");
    archive(ar, obj.tempRentRateDenominator, "tempRentRateDenominator");
    archive(ar, obj.maxEntriesToArchive, "maxEntriesToArchive");
    archive(ar, obj.liveSorobanStateSizeWindowSampleSize, "liveSorobanStateSizeWindowSampleSize");
    archive(ar, obj.liveSorobanStateSizeWindowSamplePeriod, "liveSorobanStateSizeWindowSamplePeriod");
    archive(ar, obj.evictionScanSize, "evictionScanSize");
    archive(ar, obj.startingEvictionScanLevel, "startingEvictionScanLevel");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::StateArchivalSettings &obj) {
    archive(ar, obj.maxEntryTTL, "maxEntryTTL");
    archive(ar, obj.minTemporaryTTL, "minTemporaryTTL");
    archive(ar, obj.minPersistentTTL, "minPersistentTTL");
    archive(ar, obj.persistentRentRateDenominator, "persistentRentRateDenominator");
    archive(ar, obj.tempRentRateDenominator, "tempRentRateDenominator");
    archive(ar, obj.maxEntriesToArchive, "maxEntriesToArchive");
    archive(ar, obj.liveSorobanStateSizeWindowSampleSize, "liveSorobanStateSizeWindowSampleSize");
    archive(ar, obj.liveSorobanStateSizeWindowSamplePeriod, "liveSorobanStateSizeWindowSamplePeriod");
    archive(ar, obj.evictionScanSize, "evictionScanSize");
    archive(ar, obj.startingEvictionScanLevel, "startingEvictionScanLevel");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct EvictionIterator {
  uint32 bucketListLevel{};
  bool isCurrBucket{};
  uint64 bucketFileOffset{};

  EvictionIterator() = default;
  template<typename _bucketListLevel_T,
           typename _isCurrBucket_T,
           typename _bucketFileOffset_T,
           typename = typename
           std::enable_if<std::is_constructible<uint32, _bucketListLevel_T>::value
                          && std::is_constructible<bool, _isCurrBucket_T>::value
                          && std::is_constructible<uint64, _bucketFileOffset_T>::value
                         >::type>
  explicit EvictionIterator(_bucketListLevel_T &&_bucketListLevel,
                            _isCurrBucket_T &&_isCurrBucket,
                            _bucketFileOffset_T &&_bucketFileOffset)
    : bucketListLevel(std::forward<_bucketListLevel_T>(_bucketListLevel)),
      isCurrBucket(std::forward<_isCurrBucket_T>(_isCurrBucket)),
      bucketFileOffset(std::forward<_bucketFileOffset_T>(_bucketFileOffset)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::EvictionIterator>
  : xdr_struct_base<field_ptr<::stellar::EvictionIterator,
                              decltype(::stellar::EvictionIterator::bucketListLevel),
                              &::stellar::EvictionIterator::bucketListLevel>,
                    field_ptr<::stellar::EvictionIterator,
                              decltype(::stellar::EvictionIterator::isCurrBucket),
                              &::stellar::EvictionIterator::isCurrBucket>,
                    field_ptr<::stellar::EvictionIterator,
                              decltype(::stellar::EvictionIterator::bucketFileOffset),
                              &::stellar::EvictionIterator::bucketFileOffset>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::EvictionIterator &obj) {
    archive(ar, obj.bucketListLevel, "bucketListLevel");
    archive(ar, obj.isCurrBucket, "isCurrBucket");
    archive(ar, obj.bucketFileOffset, "bucketFileOffset");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::EvictionIterator &obj) {
    archive(ar, obj.bucketListLevel, "bucketListLevel");
    archive(ar, obj.isCurrBucket, "isCurrBucket");
    archive(ar, obj.bucketFileOffset, "bucketFileOffset");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct ConfigSettingSCPTiming {
  uint32 ledgerTargetCloseTimeMilliseconds{};
  uint32 nominationTimeoutInitialMilliseconds{};
  uint32 nominationTimeoutIncrementMilliseconds{};
  uint32 ballotTimeoutInitialMilliseconds{};
  uint32 ballotTimeoutIncrementMilliseconds{};

  ConfigSettingSCPTiming() = default;
  template<typename _ledgerTargetCloseTimeMilliseconds_T,
           typename _nominationTimeoutInitialMilliseconds_T,
           typename _nominationTimeoutIncrementMilliseconds_T,
           typename _ballotTimeoutInitialMilliseconds_T,
           typename _ballotTimeoutIncrementMilliseconds_T,
           typename = typename
           std::enable_if<std::is_constructible<uint32, _ledgerTargetCloseTimeMilliseconds_T>::value
                          && std::is_constructible<uint32, _nominationTimeoutInitialMilliseconds_T>::value
                          && std::is_constructible<uint32, _nominationTimeoutIncrementMilliseconds_T>::value
                          && std::is_constructible<uint32, _ballotTimeoutInitialMilliseconds_T>::value
                          && std::is_constructible<uint32, _ballotTimeoutIncrementMilliseconds_T>::value
                         >::type>
  explicit ConfigSettingSCPTiming(_ledgerTargetCloseTimeMilliseconds_T &&_ledgerTargetCloseTimeMilliseconds,
                                  _nominationTimeoutInitialMilliseconds_T &&_nominationTimeoutInitialMilliseconds,
                                  _nominationTimeoutIncrementMilliseconds_T &&_nominationTimeoutIncrementMilliseconds,
                                  _ballotTimeoutInitialMilliseconds_T &&_ballotTimeoutInitialMilliseconds,
                                  _ballotTimeoutIncrementMilliseconds_T &&_ballotTimeoutIncrementMilliseconds)
    : ledgerTargetCloseTimeMilliseconds(std::forward<_ledgerTargetCloseTimeMilliseconds_T>(_ledgerTargetCloseTimeMilliseconds)),
      nominationTimeoutInitialMilliseconds(std::forward<_nominationTimeoutInitialMilliseconds_T>(_nominationTimeoutInitialMilliseconds)),
      nominationTimeoutIncrementMilliseconds(std::forward<_nominationTimeoutIncrementMilliseconds_T>(_nominationTimeoutIncrementMilliseconds)),
      ballotTimeoutInitialMilliseconds(std::forward<_ballotTimeoutInitialMilliseconds_T>(_ballotTimeoutInitialMilliseconds)),
      ballotTimeoutIncrementMilliseconds(std::forward<_ballotTimeoutIncrementMilliseconds_T>(_ballotTimeoutIncrementMilliseconds)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ConfigSettingSCPTiming>
  : xdr_struct_base<field_ptr<::stellar::ConfigSettingSCPTiming,
                              decltype(::stellar::ConfigSettingSCPTiming::ledgerTargetCloseTimeMilliseconds),
                              &::stellar::ConfigSettingSCPTiming::ledgerTargetCloseTimeMilliseconds>,
                    field_ptr<::stellar::ConfigSettingSCPTiming,
                              decltype(::stellar::ConfigSettingSCPTiming::nominationTimeoutInitialMilliseconds),
                              &::stellar::ConfigSettingSCPTiming::nominationTimeoutInitialMilliseconds>,
                    field_ptr<::stellar::ConfigSettingSCPTiming,
                              decltype(::stellar::ConfigSettingSCPTiming::nominationTimeoutIncrementMilliseconds),
                              &::stellar::ConfigSettingSCPTiming::nominationTimeoutIncrementMilliseconds>,
                    field_ptr<::stellar::ConfigSettingSCPTiming,
                              decltype(::stellar::ConfigSettingSCPTiming::ballotTimeoutInitialMilliseconds),
                              &::stellar::ConfigSettingSCPTiming::ballotTimeoutInitialMilliseconds>,
                    field_ptr<::stellar::ConfigSettingSCPTiming,
                              decltype(::stellar::ConfigSettingSCPTiming::ballotTimeoutIncrementMilliseconds),
                              &::stellar::ConfigSettingSCPTiming::ballotTimeoutIncrementMilliseconds>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ConfigSettingSCPTiming &obj) {
    archive(ar, obj.ledgerTargetCloseTimeMilliseconds, "ledgerTargetCloseTimeMilliseconds");
    archive(ar, obj.nominationTimeoutInitialMilliseconds, "nominationTimeoutInitialMilliseconds");
    archive(ar, obj.nominationTimeoutIncrementMilliseconds, "nominationTimeoutIncrementMilliseconds");
    archive(ar, obj.ballotTimeoutInitialMilliseconds, "ballotTimeoutInitialMilliseconds");
    archive(ar, obj.ballotTimeoutIncrementMilliseconds, "ballotTimeoutIncrementMilliseconds");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ConfigSettingSCPTiming &obj) {
    archive(ar, obj.ledgerTargetCloseTimeMilliseconds, "ledgerTargetCloseTimeMilliseconds");
    archive(ar, obj.nominationTimeoutInitialMilliseconds, "nominationTimeoutInitialMilliseconds");
    archive(ar, obj.nominationTimeoutIncrementMilliseconds, "nominationTimeoutIncrementMilliseconds");
    archive(ar, obj.ballotTimeoutInitialMilliseconds, "ballotTimeoutInitialMilliseconds");
    archive(ar, obj.ballotTimeoutIncrementMilliseconds, "ballotTimeoutIncrementMilliseconds");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct FrozenLedgerKeys {
  xdr::xvector<EncodedLedgerKey> keys{};

  FrozenLedgerKeys() = default;
  template<typename _keys_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::xvector<EncodedLedgerKey>, _keys_T>::value
                         >::type>
  explicit FrozenLedgerKeys(_keys_T &&_keys)
    : keys(std::forward<_keys_T>(_keys)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::FrozenLedgerKeys>
  : xdr_struct_base<field_ptr<::stellar::FrozenLedgerKeys,
                              decltype(::stellar::FrozenLedgerKeys::keys),
                              &::stellar::FrozenLedgerKeys::keys>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::FrozenLedgerKeys &obj) {
    archive(ar, obj.keys, "keys");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::FrozenLedgerKeys &obj) {
    archive(ar, obj.keys, "keys");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct FrozenLedgerKeysDelta {
  xdr::xvector<EncodedLedgerKey> keysToFreeze{};
  xdr::xvector<EncodedLedgerKey> keysToUnfreeze{};

  FrozenLedgerKeysDelta() = default;
  template<typename _keysToFreeze_T,
           typename _keysToUnfreeze_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::xvector<EncodedLedgerKey>, _keysToFreeze_T>::value
                          && std::is_constructible<xdr::xvector<EncodedLedgerKey>, _keysToUnfreeze_T>::value
                         >::type>
  explicit FrozenLedgerKeysDelta(_keysToFreeze_T &&_keysToFreeze,
                                 _keysToUnfreeze_T &&_keysToUnfreeze)
    : keysToFreeze(std::forward<_keysToFreeze_T>(_keysToFreeze)),
      keysToUnfreeze(std::forward<_keysToUnfreeze_T>(_keysToUnfreeze)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::FrozenLedgerKeysDelta>
  : xdr_struct_base<field_ptr<::stellar::FrozenLedgerKeysDelta,
                              decltype(::stellar::FrozenLedgerKeysDelta::keysToFreeze),
                              &::stellar::FrozenLedgerKeysDelta::keysToFreeze>,
                    field_ptr<::stellar::FrozenLedgerKeysDelta,
                              decltype(::stellar::FrozenLedgerKeysDelta::keysToUnfreeze),
                              &::stellar::FrozenLedgerKeysDelta::keysToUnfreeze>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::FrozenLedgerKeysDelta &obj) {
    archive(ar, obj.keysToFreeze, "keysToFreeze");
    archive(ar, obj.keysToUnfreeze, "keysToUnfreeze");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::FrozenLedgerKeysDelta &obj) {
    archive(ar, obj.keysToFreeze, "keysToFreeze");
    archive(ar, obj.keysToUnfreeze, "keysToUnfreeze");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct FreezeBypassTxs {
  xdr::xvector<Hash> txHashes{};

  FreezeBypassTxs() = default;
  template<typename _txHashes_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::xvector<Hash>, _txHashes_T>::value
                         >::type>
  explicit FreezeBypassTxs(_txHashes_T &&_txHashes)
    : txHashes(std::forward<_txHashes_T>(_txHashes)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::FreezeBypassTxs>
  : xdr_struct_base<field_ptr<::stellar::FreezeBypassTxs,
                              decltype(::stellar::FreezeBypassTxs::txHashes),
                              &::stellar::FreezeBypassTxs::txHashes>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::FreezeBypassTxs &obj) {
    archive(ar, obj.txHashes, "txHashes");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::FreezeBypassTxs &obj) {
    archive(ar, obj.txHashes, "txHashes");
    xdr::validate(obj);
  }
};
} namespace stellar {

struct FreezeBypassTxsDelta {
  xdr::xvector<Hash> addTxs{};
  xdr::xvector<Hash> removeTxs{};

  FreezeBypassTxsDelta() = default;
  template<typename _addTxs_T,
           typename _removeTxs_T,
           typename = typename
           std::enable_if<std::is_constructible<xdr::xvector<Hash>, _addTxs_T>::value
                          && std::is_constructible<xdr::xvector<Hash>, _removeTxs_T>::value
                         >::type>
  explicit FreezeBypassTxsDelta(_addTxs_T &&_addTxs,
                                _removeTxs_T &&_removeTxs)
    : addTxs(std::forward<_addTxs_T>(_addTxs)),
      removeTxs(std::forward<_removeTxs_T>(_removeTxs)) {}
};
} namespace xdr {
template<> struct xdr_traits<::stellar::FreezeBypassTxsDelta>
  : xdr_struct_base<field_ptr<::stellar::FreezeBypassTxsDelta,
                              decltype(::stellar::FreezeBypassTxsDelta::addTxs),
                              &::stellar::FreezeBypassTxsDelta::addTxs>,
                    field_ptr<::stellar::FreezeBypassTxsDelta,
                              decltype(::stellar::FreezeBypassTxsDelta::removeTxs),
                              &::stellar::FreezeBypassTxsDelta::removeTxs>> {
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::FreezeBypassTxsDelta &obj) {
    archive(ar, obj.addTxs, "addTxs");
    archive(ar, obj.removeTxs, "removeTxs");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::FreezeBypassTxsDelta &obj) {
    archive(ar, obj.addTxs, "addTxs");
    archive(ar, obj.removeTxs, "removeTxs");
    xdr::validate(obj);
  }
};
} namespace stellar {

Constexpr const std::uint32_t CONTRACT_COST_COUNT_LIMIT = 1024;

using ContractCostParams = xdr::xvector<ContractCostParamEntry,CONTRACT_COST_COUNT_LIMIT>;

enum ConfigSettingID : std::int32_t {
  CONFIG_SETTING_CONTRACT_MAX_SIZE_BYTES = 0,
  CONFIG_SETTING_CONTRACT_COMPUTE_V0 = 1,
  CONFIG_SETTING_CONTRACT_LEDGER_COST_V0 = 2,
  CONFIG_SETTING_CONTRACT_HISTORICAL_DATA_V0 = 3,
  CONFIG_SETTING_CONTRACT_EVENTS_V0 = 4,
  CONFIG_SETTING_CONTRACT_BANDWIDTH_V0 = 5,
  CONFIG_SETTING_CONTRACT_COST_PARAMS_CPU_INSTRUCTIONS = 6,
  CONFIG_SETTING_CONTRACT_COST_PARAMS_MEMORY_BYTES = 7,
  CONFIG_SETTING_CONTRACT_DATA_KEY_SIZE_BYTES = 8,
  CONFIG_SETTING_CONTRACT_DATA_ENTRY_SIZE_BYTES = 9,
  CONFIG_SETTING_STATE_ARCHIVAL = 10,
  CONFIG_SETTING_CONTRACT_EXECUTION_LANES = 11,
  CONFIG_SETTING_LIVE_SOROBAN_STATE_SIZE_WINDOW = 12,
  CONFIG_SETTING_EVICTION_ITERATOR = 13,
  CONFIG_SETTING_CONTRACT_PARALLEL_COMPUTE_V0 = 14,
  CONFIG_SETTING_CONTRACT_LEDGER_COST_EXT_V0 = 15,
  CONFIG_SETTING_SCP_TIMING = 16,
  CONFIG_SETTING_FROZEN_LEDGER_KEYS = 17,
  CONFIG_SETTING_FROZEN_LEDGER_KEYS_DELTA = 18,
  CONFIG_SETTING_FREEZE_BYPASS_TXS = 19,
  CONFIG_SETTING_FREEZE_BYPASS_TXS_DELTA = 20,
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ConfigSettingID>
  : xdr_integral_base<::stellar::ConfigSettingID, std::uint32_t> {
  using case_type = std::int32_t;
  static Constexpr const bool is_enum = true;
  static Constexpr const bool is_numeric = false;
  static const char *enum_name(::stellar::ConfigSettingID val) {
    switch (val) {
    case ::stellar::CONFIG_SETTING_CONTRACT_MAX_SIZE_BYTES:
      return "CONFIG_SETTING_CONTRACT_MAX_SIZE_BYTES";
    case ::stellar::CONFIG_SETTING_CONTRACT_COMPUTE_V0:
      return "CONFIG_SETTING_CONTRACT_COMPUTE_V0";
    case ::stellar::CONFIG_SETTING_CONTRACT_LEDGER_COST_V0:
      return "CONFIG_SETTING_CONTRACT_LEDGER_COST_V0";
    case ::stellar::CONFIG_SETTING_CONTRACT_HISTORICAL_DATA_V0:
      return "CONFIG_SETTING_CONTRACT_HISTORICAL_DATA_V0";
    case ::stellar::CONFIG_SETTING_CONTRACT_EVENTS_V0:
      return "CONFIG_SETTING_CONTRACT_EVENTS_V0";
    case ::stellar::CONFIG_SETTING_CONTRACT_BANDWIDTH_V0:
      return "CONFIG_SETTING_CONTRACT_BANDWIDTH_V0";
    case ::stellar::CONFIG_SETTING_CONTRACT_COST_PARAMS_CPU_INSTRUCTIONS:
      return "CONFIG_SETTING_CONTRACT_COST_PARAMS_CPU_INSTRUCTIONS";
    case ::stellar::CONFIG_SETTING_CONTRACT_COST_PARAMS_MEMORY_BYTES:
      return "CONFIG_SETTING_CONTRACT_COST_PARAMS_MEMORY_BYTES";
    case ::stellar::CONFIG_SETTING_CONTRACT_DATA_KEY_SIZE_BYTES:
      return "CONFIG_SETTING_CONTRACT_DATA_KEY_SIZE_BYTES";
    case ::stellar::CONFIG_SETTING_CONTRACT_DATA_ENTRY_SIZE_BYTES:
      return "CONFIG_SETTING_CONTRACT_DATA_ENTRY_SIZE_BYTES";
    case ::stellar::CONFIG_SETTING_STATE_ARCHIVAL:
      return "CONFIG_SETTING_STATE_ARCHIVAL";
    case ::stellar::CONFIG_SETTING_CONTRACT_EXECUTION_LANES:
      return "CONFIG_SETTING_CONTRACT_EXECUTION_LANES";
    case ::stellar::CONFIG_SETTING_LIVE_SOROBAN_STATE_SIZE_WINDOW:
      return "CONFIG_SETTING_LIVE_SOROBAN_STATE_SIZE_WINDOW";
    case ::stellar::CONFIG_SETTING_EVICTION_ITERATOR:
      return "CONFIG_SETTING_EVICTION_ITERATOR";
    case ::stellar::CONFIG_SETTING_CONTRACT_PARALLEL_COMPUTE_V0:
      return "CONFIG_SETTING_CONTRACT_PARALLEL_COMPUTE_V0";
    case ::stellar::CONFIG_SETTING_CONTRACT_LEDGER_COST_EXT_V0:
      return "CONFIG_SETTING_CONTRACT_LEDGER_COST_EXT_V0";
    case ::stellar::CONFIG_SETTING_SCP_TIMING:
      return "CONFIG_SETTING_SCP_TIMING";
    case ::stellar::CONFIG_SETTING_FROZEN_LEDGER_KEYS:
      return "CONFIG_SETTING_FROZEN_LEDGER_KEYS";
    case ::stellar::CONFIG_SETTING_FROZEN_LEDGER_KEYS_DELTA:
      return "CONFIG_SETTING_FROZEN_LEDGER_KEYS_DELTA";
    case ::stellar::CONFIG_SETTING_FREEZE_BYPASS_TXS:
      return "CONFIG_SETTING_FREEZE_BYPASS_TXS";
    case ::stellar::CONFIG_SETTING_FREEZE_BYPASS_TXS_DELTA:
      return "CONFIG_SETTING_FREEZE_BYPASS_TXS_DELTA";
    default:
      return nullptr;
    }
  }
  static const std::vector<int32_t> &enum_values() {
    static const std::vector<int32_t> _xdr_enum_vec = {
      ::stellar::CONFIG_SETTING_CONTRACT_MAX_SIZE_BYTES,
      ::stellar::CONFIG_SETTING_CONTRACT_COMPUTE_V0,
      ::stellar::CONFIG_SETTING_CONTRACT_LEDGER_COST_V0,
      ::stellar::CONFIG_SETTING_CONTRACT_HISTORICAL_DATA_V0,
      ::stellar::CONFIG_SETTING_CONTRACT_EVENTS_V0,
      ::stellar::CONFIG_SETTING_CONTRACT_BANDWIDTH_V0,
      ::stellar::CONFIG_SETTING_CONTRACT_COST_PARAMS_CPU_INSTRUCTIONS,
      ::stellar::CONFIG_SETTING_CONTRACT_COST_PARAMS_MEMORY_BYTES,
      ::stellar::CONFIG_SETTING_CONTRACT_DATA_KEY_SIZE_BYTES,
      ::stellar::CONFIG_SETTING_CONTRACT_DATA_ENTRY_SIZE_BYTES,
      ::stellar::CONFIG_SETTING_STATE_ARCHIVAL,
      ::stellar::CONFIG_SETTING_CONTRACT_EXECUTION_LANES,
      ::stellar::CONFIG_SETTING_LIVE_SOROBAN_STATE_SIZE_WINDOW,
      ::stellar::CONFIG_SETTING_EVICTION_ITERATOR,
      ::stellar::CONFIG_SETTING_CONTRACT_PARALLEL_COMPUTE_V0,
      ::stellar::CONFIG_SETTING_CONTRACT_LEDGER_COST_EXT_V0,
      ::stellar::CONFIG_SETTING_SCP_TIMING,
      ::stellar::CONFIG_SETTING_FROZEN_LEDGER_KEYS,
      ::stellar::CONFIG_SETTING_FROZEN_LEDGER_KEYS_DELTA,
      ::stellar::CONFIG_SETTING_FREEZE_BYPASS_TXS,
      ::stellar::CONFIG_SETTING_FREEZE_BYPASS_TXS_DELTA
    };
    return _xdr_enum_vec;
  }
};
} namespace stellar {

struct ConfigSettingEntry {
  using _xdr_case_type = xdr::xdr_traits<ConfigSettingID>::case_type;
private:
  _xdr_case_type configSettingID_;
  union {
    uint32 contractMaxSizeBytes_;
    ConfigSettingContractComputeV0 contractCompute_;
    ConfigSettingContractLedgerCostV0 contractLedgerCost_;
    ConfigSettingContractHistoricalDataV0 contractHistoricalData_;
    ConfigSettingContractEventsV0 contractEvents_;
    ConfigSettingContractBandwidthV0 contractBandwidth_;
    ContractCostParams contractCostParamsCpuInsns_;
    ContractCostParams contractCostParamsMemBytes_;
    uint32 contractDataKeySizeBytes_;
    uint32 contractDataEntrySizeBytes_;
    StateArchivalSettings stateArchivalSettings_;
    ConfigSettingContractExecutionLanesV0 contractExecutionLanes_;
    xdr::xvector<uint64> liveSorobanStateSizeWindow_;
    EvictionIterator evictionIterator_;
    ConfigSettingContractParallelComputeV0 contractParallelCompute_;
    ConfigSettingContractLedgerCostExtV0 contractLedgerCostExt_;
    ConfigSettingSCPTiming contractSCPTiming_;
    FrozenLedgerKeys frozenLedgerKeys_;
    FrozenLedgerKeysDelta frozenLedgerKeysDelta_;
    FreezeBypassTxs freezeBypassTxs_;
    FreezeBypassTxsDelta freezeBypassTxsDelta_;
  };

public:
  static Constexpr const bool _xdr_has_default_case = false;
  static const std::vector<ConfigSettingID> &_xdr_case_values() {
    static const std::vector<ConfigSettingID> _xdr_disc_vec {
      CONFIG_SETTING_CONTRACT_MAX_SIZE_BYTES,
      CONFIG_SETTING_CONTRACT_COMPUTE_V0,
      CONFIG_SETTING_CONTRACT_LEDGER_COST_V0,
      CONFIG_SETTING_CONTRACT_HISTORICAL_DATA_V0,
      CONFIG_SETTING_CONTRACT_EVENTS_V0,
      CONFIG_SETTING_CONTRACT_BANDWIDTH_V0,
      CONFIG_SETTING_CONTRACT_COST_PARAMS_CPU_INSTRUCTIONS,
      CONFIG_SETTING_CONTRACT_COST_PARAMS_MEMORY_BYTES,
      CONFIG_SETTING_CONTRACT_DATA_KEY_SIZE_BYTES,
      CONFIG_SETTING_CONTRACT_DATA_ENTRY_SIZE_BYTES,
      CONFIG_SETTING_STATE_ARCHIVAL,
      CONFIG_SETTING_CONTRACT_EXECUTION_LANES,
      CONFIG_SETTING_LIVE_SOROBAN_STATE_SIZE_WINDOW,
      CONFIG_SETTING_EVICTION_ITERATOR,
      CONFIG_SETTING_CONTRACT_PARALLEL_COMPUTE_V0,
      CONFIG_SETTING_CONTRACT_LEDGER_COST_EXT_V0,
      CONFIG_SETTING_SCP_TIMING,
      CONFIG_SETTING_FROZEN_LEDGER_KEYS,
      CONFIG_SETTING_FROZEN_LEDGER_KEYS_DELTA,
      CONFIG_SETTING_FREEZE_BYPASS_TXS,
      CONFIG_SETTING_FREEZE_BYPASS_TXS_DELTA
    };
    return _xdr_disc_vec;
  }
  static Constexpr int _xdr_field_number(_xdr_case_type which) {
    return which == CONFIG_SETTING_CONTRACT_MAX_SIZE_BYTES ? 1
      : which == CONFIG_SETTING_CONTRACT_COMPUTE_V0 ? 2
      : which == CONFIG_SETTING_CONTRACT_LEDGER_COST_V0 ? 3
      : which == CONFIG_SETTING_CONTRACT_HISTORICAL_DATA_V0 ? 4
      : which == CONFIG_SETTING_CONTRACT_EVENTS_V0 ? 5
      : which == CONFIG_SETTING_CONTRACT_BANDWIDTH_V0 ? 6
      : which == CONFIG_SETTING_CONTRACT_COST_PARAMS_CPU_INSTRUCTIONS ? 7
      : which == CONFIG_SETTING_CONTRACT_COST_PARAMS_MEMORY_BYTES ? 8
      : which == CONFIG_SETTING_CONTRACT_DATA_KEY_SIZE_BYTES ? 9
      : which == CONFIG_SETTING_CONTRACT_DATA_ENTRY_SIZE_BYTES ? 10
      : which == CONFIG_SETTING_STATE_ARCHIVAL ? 11
      : which == CONFIG_SETTING_CONTRACT_EXECUTION_LANES ? 12
      : which == CONFIG_SETTING_LIVE_SOROBAN_STATE_SIZE_WINDOW ? 13
      : which == CONFIG_SETTING_EVICTION_ITERATOR ? 14
      : which == CONFIG_SETTING_CONTRACT_PARALLEL_COMPUTE_V0 ? 15
      : which == CONFIG_SETTING_CONTRACT_LEDGER_COST_EXT_V0 ? 16
      : which == CONFIG_SETTING_SCP_TIMING ? 17
      : which == CONFIG_SETTING_FROZEN_LEDGER_KEYS ? 18
      : which == CONFIG_SETTING_FROZEN_LEDGER_KEYS_DELTA ? 19
      : which == CONFIG_SETTING_FREEZE_BYPASS_TXS ? 20
      : which == CONFIG_SETTING_FREEZE_BYPASS_TXS_DELTA ? 21
      : -1;
  }
  template<typename _F, typename..._A> static bool
  _xdr_with_mem_ptr(_F &_f, _xdr_case_type _which, _A&&..._a) {
    switch (_which) {
    case CONFIG_SETTING_CONTRACT_MAX_SIZE_BYTES:
      _f(&ConfigSettingEntry::contractMaxSizeBytes_, std::forward<_A>(_a)...);
      return true;
    case CONFIG_SETTING_CONTRACT_COMPUTE_V0:
      _f(&ConfigSettingEntry::contractCompute_, std::forward<_A>(_a)...);
      return true;
    case CONFIG_SETTING_CONTRACT_LEDGER_COST_V0:
      _f(&ConfigSettingEntry::contractLedgerCost_, std::forward<_A>(_a)...);
      return true;
    case CONFIG_SETTING_CONTRACT_HISTORICAL_DATA_V0:
      _f(&ConfigSettingEntry::contractHistoricalData_, std::forward<_A>(_a)...);
      return true;
    case CONFIG_SETTING_CONTRACT_EVENTS_V0:
      _f(&ConfigSettingEntry::contractEvents_, std::forward<_A>(_a)...);
      return true;
    case CONFIG_SETTING_CONTRACT_BANDWIDTH_V0:
      _f(&ConfigSettingEntry::contractBandwidth_, std::forward<_A>(_a)...);
      return true;
    case CONFIG_SETTING_CONTRACT_COST_PARAMS_CPU_INSTRUCTIONS:
      _f(&ConfigSettingEntry::contractCostParamsCpuInsns_, std::forward<_A>(_a)...);
      return true;
    case CONFIG_SETTING_CONTRACT_COST_PARAMS_MEMORY_BYTES:
      _f(&ConfigSettingEntry::contractCostParamsMemBytes_, std::forward<_A>(_a)...);
      return true;
    case CONFIG_SETTING_CONTRACT_DATA_KEY_SIZE_BYTES:
      _f(&ConfigSettingEntry::contractDataKeySizeBytes_, std::forward<_A>(_a)...);
      return true;
    case CONFIG_SETTING_CONTRACT_DATA_ENTRY_SIZE_BYTES:
      _f(&ConfigSettingEntry::contractDataEntrySizeBytes_, std::forward<_A>(_a)...);
      return true;
    case CONFIG_SETTING_STATE_ARCHIVAL:
      _f(&ConfigSettingEntry::stateArchivalSettings_, std::forward<_A>(_a)...);
      return true;
    case CONFIG_SETTING_CONTRACT_EXECUTION_LANES:
      _f(&ConfigSettingEntry::contractExecutionLanes_, std::forward<_A>(_a)...);
      return true;
    case CONFIG_SETTING_LIVE_SOROBAN_STATE_SIZE_WINDOW:
      _f(&ConfigSettingEntry::liveSorobanStateSizeWindow_, std::forward<_A>(_a)...);
      return true;
    case CONFIG_SETTING_EVICTION_ITERATOR:
      _f(&ConfigSettingEntry::evictionIterator_, std::forward<_A>(_a)...);
      return true;
    case CONFIG_SETTING_CONTRACT_PARALLEL_COMPUTE_V0:
      _f(&ConfigSettingEntry::contractParallelCompute_, std::forward<_A>(_a)...);
      return true;
    case CONFIG_SETTING_CONTRACT_LEDGER_COST_EXT_V0:
      _f(&ConfigSettingEntry::contractLedgerCostExt_, std::forward<_A>(_a)...);
      return true;
    case CONFIG_SETTING_SCP_TIMING:
      _f(&ConfigSettingEntry::contractSCPTiming_, std::forward<_A>(_a)...);
      return true;
    case CONFIG_SETTING_FROZEN_LEDGER_KEYS:
      _f(&ConfigSettingEntry::frozenLedgerKeys_, std::forward<_A>(_a)...);
      return true;
    case CONFIG_SETTING_FROZEN_LEDGER_KEYS_DELTA:
      _f(&ConfigSettingEntry::frozenLedgerKeysDelta_, std::forward<_A>(_a)...);
      return true;
    case CONFIG_SETTING_FREEZE_BYPASS_TXS:
      _f(&ConfigSettingEntry::freezeBypassTxs_, std::forward<_A>(_a)...);
      return true;
    case CONFIG_SETTING_FREEZE_BYPASS_TXS_DELTA:
      _f(&ConfigSettingEntry::freezeBypassTxsDelta_, std::forward<_A>(_a)...);
      return true;
    }
    return false;
  }

  _xdr_case_type _xdr_discriminant() const { return configSettingID_; }
  void _xdr_discriminant(_xdr_case_type which, bool validate = true) {
    int fnum = _xdr_field_number(which);
    if (fnum < 0 && validate)
      throw xdr::xdr_bad_discriminant("bad value of configSettingID in ConfigSettingEntry");
    if (fnum != _xdr_field_number(configSettingID_)) {
      this->~ConfigSettingEntry();
      configSettingID_ = which;
      _xdr_with_mem_ptr(xdr::field_constructor, configSettingID_, *this);
    }
    else
      configSettingID_ = which;
  }
  explicit ConfigSettingEntry(ConfigSettingID which = ConfigSettingID{}) : configSettingID_(which) {
    _xdr_with_mem_ptr(xdr::field_constructor, configSettingID_, *this);
  }
  ConfigSettingEntry(const ConfigSettingEntry &source) : configSettingID_(source.configSettingID_) {
    _xdr_with_mem_ptr(xdr::field_constructor, configSettingID_, *this, source);
  }
  ConfigSettingEntry(ConfigSettingEntry &&source) : configSettingID_(source.configSettingID_) {
    _xdr_with_mem_ptr(xdr::field_constructor, configSettingID_, *this,
                      std::move(source));
  }
  ~ConfigSettingEntry() { _xdr_with_mem_ptr(xdr::field_destructor, configSettingID_, *this); }
  ConfigSettingEntry &operator=(const ConfigSettingEntry &source) {
    if (_xdr_field_number(configSettingID_)
        == _xdr_field_number(source.configSettingID_))
      _xdr_with_mem_ptr(xdr::field_assigner, configSettingID_, *this, source);
    else {
      this->~ConfigSettingEntry();
      configSettingID_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.configSettingID_, *this, source);
    }
    configSettingID_ = source.configSettingID_;
    return *this;
  }
  ConfigSettingEntry &operator=(ConfigSettingEntry &&source) {
    if (_xdr_field_number(configSettingID_)
         == _xdr_field_number(source.configSettingID_))
      _xdr_with_mem_ptr(xdr::field_assigner, configSettingID_, *this,
                        std::move(source));
    else {
      this->~ConfigSettingEntry();
      configSettingID_ = std::numeric_limits<_xdr_case_type>::max();
      _xdr_with_mem_ptr(xdr::field_constructor, source.configSettingID_, *this,
                        std::move(source));
    }
    configSettingID_ = source.configSettingID_;
    return *this;
  }

  ConfigSettingID configSettingID() const { return ConfigSettingID(configSettingID_); }
  ConfigSettingEntry &configSettingID(ConfigSettingID _xdr_d, bool _xdr_validate = true) {
    _xdr_discriminant(_xdr_d, _xdr_validate);
    return *this;
  }

  uint32 &contractMaxSizeBytes() {
    if (_xdr_field_number(configSettingID_) == 1)
      return contractMaxSizeBytes_;
    throw xdr::xdr_wrong_union("ConfigSettingEntry: contractMaxSizeBytes accessed when not selected");
  }
  const uint32 &contractMaxSizeBytes() const {
    if (_xdr_field_number(configSettingID_) == 1)
      return contractMaxSizeBytes_;
    throw xdr::xdr_wrong_union("ConfigSettingEntry: contractMaxSizeBytes accessed when not selected");
  }
  ConfigSettingContractComputeV0 &contractCompute() {
    if (_xdr_field_number(configSettingID_) == 2)
      return contractCompute_;
    throw xdr::xdr_wrong_union("ConfigSettingEntry: contractCompute accessed when not selected");
  }
  const ConfigSettingContractComputeV0 &contractCompute() const {
    if (_xdr_field_number(configSettingID_) == 2)
      return contractCompute_;
    throw xdr::xdr_wrong_union("ConfigSettingEntry: contractCompute accessed when not selected");
  }
  ConfigSettingContractLedgerCostV0 &contractLedgerCost() {
    if (_xdr_field_number(configSettingID_) == 3)
      return contractLedgerCost_;
    throw xdr::xdr_wrong_union("ConfigSettingEntry: contractLedgerCost accessed when not selected");
  }
  const ConfigSettingContractLedgerCostV0 &contractLedgerCost() const {
    if (_xdr_field_number(configSettingID_) == 3)
      return contractLedgerCost_;
    throw xdr::xdr_wrong_union("ConfigSettingEntry: contractLedgerCost accessed when not selected");
  }
  ConfigSettingContractHistoricalDataV0 &contractHistoricalData() {
    if (_xdr_field_number(configSettingID_) == 4)
      return contractHistoricalData_;
    throw xdr::xdr_wrong_union("ConfigSettingEntry: contractHistoricalData accessed when not selected");
  }
  const ConfigSettingContractHistoricalDataV0 &contractHistoricalData() const {
    if (_xdr_field_number(configSettingID_) == 4)
      return contractHistoricalData_;
    throw xdr::xdr_wrong_union("ConfigSettingEntry: contractHistoricalData accessed when not selected");
  }
  ConfigSettingContractEventsV0 &contractEvents() {
    if (_xdr_field_number(configSettingID_) == 5)
      return contractEvents_;
    throw xdr::xdr_wrong_union("ConfigSettingEntry: contractEvents accessed when not selected");
  }
  const ConfigSettingContractEventsV0 &contractEvents() const {
    if (_xdr_field_number(configSettingID_) == 5)
      return contractEvents_;
    throw xdr::xdr_wrong_union("ConfigSettingEntry: contractEvents accessed when not selected");
  }
  ConfigSettingContractBandwidthV0 &contractBandwidth() {
    if (_xdr_field_number(configSettingID_) == 6)
      return contractBandwidth_;
    throw xdr::xdr_wrong_union("ConfigSettingEntry: contractBandwidth accessed when not selected");
  }
  const ConfigSettingContractBandwidthV0 &contractBandwidth() const {
    if (_xdr_field_number(configSettingID_) == 6)
      return contractBandwidth_;
    throw xdr::xdr_wrong_union("ConfigSettingEntry: contractBandwidth accessed when not selected");
  }
  ContractCostParams &contractCostParamsCpuInsns() {
    if (_xdr_field_number(configSettingID_) == 7)
      return contractCostParamsCpuInsns_;
    throw xdr::xdr_wrong_union("ConfigSettingEntry: contractCostParamsCpuInsns accessed when not selected");
  }
  const ContractCostParams &contractCostParamsCpuInsns() const {
    if (_xdr_field_number(configSettingID_) == 7)
      return contractCostParamsCpuInsns_;
    throw xdr::xdr_wrong_union("ConfigSettingEntry: contractCostParamsCpuInsns accessed when not selected");
  }
  ContractCostParams &contractCostParamsMemBytes() {
    if (_xdr_field_number(configSettingID_) == 8)
      return contractCostParamsMemBytes_;
    throw xdr::xdr_wrong_union("ConfigSettingEntry: contractCostParamsMemBytes accessed when not selected");
  }
  const ContractCostParams &contractCostParamsMemBytes() const {
    if (_xdr_field_number(configSettingID_) == 8)
      return contractCostParamsMemBytes_;
    throw xdr::xdr_wrong_union("ConfigSettingEntry: contractCostParamsMemBytes accessed when not selected");
  }
  uint32 &contractDataKeySizeBytes() {
    if (_xdr_field_number(configSettingID_) == 9)
      return contractDataKeySizeBytes_;
    throw xdr::xdr_wrong_union("ConfigSettingEntry: contractDataKeySizeBytes accessed when not selected");
  }
  const uint32 &contractDataKeySizeBytes() const {
    if (_xdr_field_number(configSettingID_) == 9)
      return contractDataKeySizeBytes_;
    throw xdr::xdr_wrong_union("ConfigSettingEntry: contractDataKeySizeBytes accessed when not selected");
  }
  uint32 &contractDataEntrySizeBytes() {
    if (_xdr_field_number(configSettingID_) == 10)
      return contractDataEntrySizeBytes_;
    throw xdr::xdr_wrong_union("ConfigSettingEntry: contractDataEntrySizeBytes accessed when not selected");
  }
  const uint32 &contractDataEntrySizeBytes() const {
    if (_xdr_field_number(configSettingID_) == 10)
      return contractDataEntrySizeBytes_;
    throw xdr::xdr_wrong_union("ConfigSettingEntry: contractDataEntrySizeBytes accessed when not selected");
  }
  StateArchivalSettings &stateArchivalSettings() {
    if (_xdr_field_number(configSettingID_) == 11)
      return stateArchivalSettings_;
    throw xdr::xdr_wrong_union("ConfigSettingEntry: stateArchivalSettings accessed when not selected");
  }
  const StateArchivalSettings &stateArchivalSettings() const {
    if (_xdr_field_number(configSettingID_) == 11)
      return stateArchivalSettings_;
    throw xdr::xdr_wrong_union("ConfigSettingEntry: stateArchivalSettings accessed when not selected");
  }
  ConfigSettingContractExecutionLanesV0 &contractExecutionLanes() {
    if (_xdr_field_number(configSettingID_) == 12)
      return contractExecutionLanes_;
    throw xdr::xdr_wrong_union("ConfigSettingEntry: contractExecutionLanes accessed when not selected");
  }
  const ConfigSettingContractExecutionLanesV0 &contractExecutionLanes() const {
    if (_xdr_field_number(configSettingID_) == 12)
      return contractExecutionLanes_;
    throw xdr::xdr_wrong_union("ConfigSettingEntry: contractExecutionLanes accessed when not selected");
  }
  xdr::xvector<uint64> &liveSorobanStateSizeWindow() {
    if (_xdr_field_number(configSettingID_) == 13)
      return liveSorobanStateSizeWindow_;
    throw xdr::xdr_wrong_union("ConfigSettingEntry: liveSorobanStateSizeWindow accessed when not selected");
  }
  const xdr::xvector<uint64> &liveSorobanStateSizeWindow() const {
    if (_xdr_field_number(configSettingID_) == 13)
      return liveSorobanStateSizeWindow_;
    throw xdr::xdr_wrong_union("ConfigSettingEntry: liveSorobanStateSizeWindow accessed when not selected");
  }
  EvictionIterator &evictionIterator() {
    if (_xdr_field_number(configSettingID_) == 14)
      return evictionIterator_;
    throw xdr::xdr_wrong_union("ConfigSettingEntry: evictionIterator accessed when not selected");
  }
  const EvictionIterator &evictionIterator() const {
    if (_xdr_field_number(configSettingID_) == 14)
      return evictionIterator_;
    throw xdr::xdr_wrong_union("ConfigSettingEntry: evictionIterator accessed when not selected");
  }
  ConfigSettingContractParallelComputeV0 &contractParallelCompute() {
    if (_xdr_field_number(configSettingID_) == 15)
      return contractParallelCompute_;
    throw xdr::xdr_wrong_union("ConfigSettingEntry: contractParallelCompute accessed when not selected");
  }
  const ConfigSettingContractParallelComputeV0 &contractParallelCompute() const {
    if (_xdr_field_number(configSettingID_) == 15)
      return contractParallelCompute_;
    throw xdr::xdr_wrong_union("ConfigSettingEntry: contractParallelCompute accessed when not selected");
  }
  ConfigSettingContractLedgerCostExtV0 &contractLedgerCostExt() {
    if (_xdr_field_number(configSettingID_) == 16)
      return contractLedgerCostExt_;
    throw xdr::xdr_wrong_union("ConfigSettingEntry: contractLedgerCostExt accessed when not selected");
  }
  const ConfigSettingContractLedgerCostExtV0 &contractLedgerCostExt() const {
    if (_xdr_field_number(configSettingID_) == 16)
      return contractLedgerCostExt_;
    throw xdr::xdr_wrong_union("ConfigSettingEntry: contractLedgerCostExt accessed when not selected");
  }
  ConfigSettingSCPTiming &contractSCPTiming() {
    if (_xdr_field_number(configSettingID_) == 17)
      return contractSCPTiming_;
    throw xdr::xdr_wrong_union("ConfigSettingEntry: contractSCPTiming accessed when not selected");
  }
  const ConfigSettingSCPTiming &contractSCPTiming() const {
    if (_xdr_field_number(configSettingID_) == 17)
      return contractSCPTiming_;
    throw xdr::xdr_wrong_union("ConfigSettingEntry: contractSCPTiming accessed when not selected");
  }
  FrozenLedgerKeys &frozenLedgerKeys() {
    if (_xdr_field_number(configSettingID_) == 18)
      return frozenLedgerKeys_;
    throw xdr::xdr_wrong_union("ConfigSettingEntry: frozenLedgerKeys accessed when not selected");
  }
  const FrozenLedgerKeys &frozenLedgerKeys() const {
    if (_xdr_field_number(configSettingID_) == 18)
      return frozenLedgerKeys_;
    throw xdr::xdr_wrong_union("ConfigSettingEntry: frozenLedgerKeys accessed when not selected");
  }
  FrozenLedgerKeysDelta &frozenLedgerKeysDelta() {
    if (_xdr_field_number(configSettingID_) == 19)
      return frozenLedgerKeysDelta_;
    throw xdr::xdr_wrong_union("ConfigSettingEntry: frozenLedgerKeysDelta accessed when not selected");
  }
  const FrozenLedgerKeysDelta &frozenLedgerKeysDelta() const {
    if (_xdr_field_number(configSettingID_) == 19)
      return frozenLedgerKeysDelta_;
    throw xdr::xdr_wrong_union("ConfigSettingEntry: frozenLedgerKeysDelta accessed when not selected");
  }
  FreezeBypassTxs &freezeBypassTxs() {
    if (_xdr_field_number(configSettingID_) == 20)
      return freezeBypassTxs_;
    throw xdr::xdr_wrong_union("ConfigSettingEntry: freezeBypassTxs accessed when not selected");
  }
  const FreezeBypassTxs &freezeBypassTxs() const {
    if (_xdr_field_number(configSettingID_) == 20)
      return freezeBypassTxs_;
    throw xdr::xdr_wrong_union("ConfigSettingEntry: freezeBypassTxs accessed when not selected");
  }
  FreezeBypassTxsDelta &freezeBypassTxsDelta() {
    if (_xdr_field_number(configSettingID_) == 21)
      return freezeBypassTxsDelta_;
    throw xdr::xdr_wrong_union("ConfigSettingEntry: freezeBypassTxsDelta accessed when not selected");
  }
  const FreezeBypassTxsDelta &freezeBypassTxsDelta() const {
    if (_xdr_field_number(configSettingID_) == 21)
      return freezeBypassTxsDelta_;
    throw xdr::xdr_wrong_union("ConfigSettingEntry: freezeBypassTxsDelta accessed when not selected");
  }
};
} namespace xdr {
template<> struct xdr_traits<::stellar::ConfigSettingEntry> : xdr_traits_base {
  static Constexpr const bool is_class = true;
  static Constexpr const bool is_union = true;
  static Constexpr const bool has_fixed_size = false;

  using union_type = ::stellar::ConfigSettingEntry;
  using case_type = ::stellar::ConfigSettingEntry::_xdr_case_type;
  using discriminant_type = decltype(std::declval<union_type>().configSettingID());

  static const char *union_field_name(case_type which) {
    switch (union_type::_xdr_field_number(which)) {
    case 1:
      return "contractMaxSizeBytes";
    case 2:
      return "contractCompute";
    case 3:
      return "contractLedgerCost";
    case 4:
      return "contractHistoricalData";
    case 5:
      return "contractEvents";
    case 6:
      return "contractBandwidth";
    case 7:
      return "contractCostParamsCpuInsns";
    case 8:
      return "contractCostParamsMemBytes";
    case 9:
      return "contractDataKeySizeBytes";
    case 10:
      return "contractDataEntrySizeBytes";
    case 11:
      return "stateArchivalSettings";
    case 12:
      return "contractExecutionLanes";
    case 13:
      return "liveSorobanStateSizeWindow";
    case 14:
      return "evictionIterator";
    case 15:
      return "contractParallelCompute";
    case 16:
      return "contractLedgerCostExt";
    case 17:
      return "contractSCPTiming";
    case 18:
      return "frozenLedgerKeys";
    case 19:
      return "frozenLedgerKeysDelta";
    case 20:
      return "freezeBypassTxs";
    case 21:
      return "freezeBypassTxsDelta";
    }
    return nullptr;
  }
  static const char *union_field_name(const union_type &u) {
    return union_field_name(u._xdr_discriminant());
  }

  static std::size_t serial_size(const ::stellar::ConfigSettingEntry &obj) {
    std::size_t size = 0;
    if (!obj._xdr_with_mem_ptr(field_size, obj._xdr_discriminant(), obj, size))
      throw xdr_bad_discriminant("bad value of configSettingID in ConfigSettingEntry");
    return size + 4;
  }
  template<typename Archive> static void
  save(Archive &ar, const ::stellar::ConfigSettingEntry &obj) {
    xdr::archive(ar, obj.configSettingID(), "configSettingID");
    if (!obj._xdr_with_mem_ptr(field_archiver, obj.configSettingID(), ar, obj,
                               union_field_name(obj)))
      throw xdr_bad_discriminant("bad value of configSettingID in ConfigSettingEntry");
  }
  template<typename Archive> static void
  load(Archive &ar, ::stellar::ConfigSettingEntry &obj) {
    discriminant_type which;
    xdr::archive(ar, which, "configSettingID");
    obj.configSettingID(which);
    obj._xdr_with_mem_ptr(field_archiver, obj.configSettingID(), ar, obj,
                          union_field_name(which));
    xdr::validate(obj);
  }
};
} namespace stellar {

}

#endif // !__XDR_STELLAR_CONTRACT_CONFIG_SETTING_H_INCLUDED__
