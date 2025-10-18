#ifndef SUPPERCHAIN_CONSENSUS_CONSENSUS_H
#define SUPPERCHAIN_CONSENSUS_CONSENSUS_H

#include <cstdint>
#include <cstdlib>

/** The maximum allowed size for a serialized block, in bytes (only for buffer size limits) */
static const unsigned int MAX_BLOCK_SERIALIZED_SIZE = 8000000; // doubled from Bitcoin

/** The maximum allowed weight for a block, see BIP 141 (network rule) */
static const unsigned int MAX_BLOCK_WEIGHT = 8000000;

/** The maximum allowed number of signature check operations in a block (network rule) */
static const int64_t MAX_BLOCK_SIGOPS_COST = 160000; // proportional increase

/** Coinbase transaction outputs can only be spent after this number of new blocks (network rule) */
static const int COINBASE_MATURITY = 50; // reduced from 100 for faster coin availability

static const int WITNESS_SCALE_FACTOR = 4;

static const size_t MIN_TRANSACTION_WEIGHT = WITNESS_SCALE_FACTOR * 60;
static const size_t MIN_SERIALIZABLE_TRANSACTION_WEIGHT = WITNESS_SCALE_FACTOR * 10;

/** Flags for nSequence and nLockTime locks */
/** Interpret sequence numbers as relative lock-time constraints. */
static constexpr unsigned int LOCKTIME_VERIFY_SEQUENCE = (1 << 0);

/**
 * Maximum number of seconds that the timestamp of the first
 * block of a difficulty adjustment period is allowed to
 * be earlier than the last block of the previous period (BIP94).
 */
static constexpr int64_t MAX_TIMEWARP = 600;

#endif // SUPPERCHAIN_CONSENSUS_CONSENSUS_H
