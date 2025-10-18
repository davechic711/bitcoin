// Copyright (c) 2009-present The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_POLICY_TRUC_POLICY_H
#define BITCOIN_POLICY_TRUC_POLICY_H

#include <primitives/transaction.h>
#include <txmempool.h>

#include <optional>
#include <string>
#include <utility>

class CFeeRate;
class CTransaction;
class CTxMemPool;

/** The Right to Unconfirmed Children (TRUC) transaction version */
static constexpr int32_t TRUC_VERSION = 3;

/** Check TRUC rules for a single transaction */
std::optional<std::pair<std::string, const CTransaction*>> SingleTRUCChecks(
    const CTransactionRef& ptx,
    const CTxMemPool::setEntries& ancestors,
    const std::set<uint256>& conflicts,
    int64_t vsize);

/** Check TRUC rules for package transactions */
std::optional<std::string> PackageTRUCChecks(
    const CTransactionRef& ptx,
    int64_t vsize,
    const std::vector<CTransactionRef>& package,
    const CTxMemPool::setEntries& ancestors);

/** Check if entries and txids are disjoint */
std::optional<std::string> EntriesAndTxidsDisjoint(
    const CTxMemPool::setEntries& entries,
    const std::set<uint256>& txids,
    const uint256& hash);

/** Check if replacement pays more than conflicts */
std::optional<std::string> PaysMoreThanConflicts(
    const CTxMemPool::setEntries& iters_conflicting,
    const CFeeRate& newFeeRate,
    const uint256& hash);

/** Get entries for conflicts */
std::optional<std::string> GetEntriesForConflicts(
    const CTransaction& tx,
    const CTxMemPool& pool,
    const CTxMemPool::setEntries& iters_conflicting,
    CTxMemPool::setEntries& all_conflicts);

/** Check if transaction has no new unconfirmed inputs */
std::optional<std::string> HasNoNewUnconfirmed(
    const CTransaction& tx,
    const CTxMemPool& pool,
    const CTxMemPool::setEntries& all_conflicts);

/** Check if replacement pays for RBF */
std::optional<std::string> PaysForRBF(
    CAmount original_fees,
    CAmount replacement_fees,
    int64_t replacement_vsize,
    CFeeRate relay_fee,
    const uint256& hash);

/** Check if replacement improves fee rate diagram */
std::optional<std::pair<bool, std::string>> ImprovesFeerateDiagram(
    class CTxMemPool::ChangeSet& changeset);

#endif // BITCOIN_POLICY_TRUC_POLICY_H