// Copyright (c) 2009-present The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_SUPPERCHAIN_PARAMS_H
#define BITCOIN_SUPPERCHAIN_PARAMS_H

class CChainParams;
class Consensus::Params;

#include <consensus/amount.h>
#include <cstdint>

/**
 * Supperchain-specific parameters and helper functions
 */

// Supperchain network magic bytes
namespace SupperchainMagic {
    static constexpr unsigned char MAINNET[4] = {0xFA, 0xBF, 0xB5, 0xDA}; // "SUPP" in hex
    static constexpr unsigned char TESTNET[4] = {0x0F, 0x0A, 0x0B, 0x05}; // Testnet magic
    static constexpr unsigned char REGTEST[4] = {0xDA, 0xB5, 0xBF, 0xFA}; // Regtest magic
}

// Supperchain consensus parameters
namespace SupperchainConsensus {
    // Block time in seconds
    static constexpr int64_t TARGET_SPACING = 60; // 1 minute blocks
    
    // Difficulty adjustment period
    static constexpr int64_t DIFFICULTY_ADJUSTMENT_INTERVAL = 2016; // Same as Bitcoin
    
    // Coinbase maturity
    static constexpr int COINBASE_MATURITY = 100;
    
    // Maximum money supply (use literal instead of COIN macro)
    static constexpr int64_t MAX_MONEY = 21000000 * 100000000; // 21 million coins
    
    // Block reward (use literal)
    static constexpr int64_t INITIAL_BLOCK_REWARD = 50 * 100000000; // 50 coins
    
    // Halving interval
    static constexpr int64_t SUBSIDY_HALVING_INTERVAL = 210000; // Same as Bitcoin
}

// Supperchain policy parameters
namespace SupperchainPolicy {
    // Maximum block size/weight
    static constexpr unsigned int MAX_BLOCK_WEIGHT = 4000000; // 4M weight units
    
    // Maximum standard transaction weight
    static constexpr unsigned int MAX_STANDARD_TX_WEIGHT = 400000;
    
    // Minimum relay fee rate
    static constexpr int64_t MIN_RELAY_TX_FEE = 1000; // 1000 satoshis per kB
    
    // Dust relay fee rate
    static constexpr int64_t DUST_RELAY_TX_FEE = 3000; // 3000 satoshis per kB
}

/**
 * Check if the current network is Supperchain
 */
bool IsSupperchain();

#endif // BITCOIN_SUPPERCHAIN_PARAMS_H