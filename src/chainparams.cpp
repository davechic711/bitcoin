// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2022 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainparams.h>

#include <chainparamsbase.h>
#include <common/args.h>
#include <consensus/params.h>
#include <deploymentinfo.h>
#include <logging.h>
#include <tinyformat.h>
#include <util/chaintype.h>
#include <util/strencodings.h>
#include <util/string.h>

#include <cassert>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <vector>

using util::SplitString;

/**
 * David's Custom Blockchain - Main Network
 */
class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = CBaseChainParams::MAIN;
        
        // Consensus settings
        consensus.nSubsidyHalvingInterval = 210000;
        consensus.BIP16Height = 0;
        consensus.BIP34Height = 0;
        consensus.BIP34Hash = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000");
        consensus.BIP65Height = 0;
        consensus.BIP66Height = 0;
        consensus.CSVHeight = 0;
        consensus.SegwitHeight = 0;
        consensus.MinBIP9WarningHeight = 0;
        
        // Proof-of-work limits - MAKE THIS EASIER FOR TESTING!
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 14 * 24 * 60 * 60; // two weeks
        consensus.nPowTargetSpacing = 10 * 60; // 10 minutes
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1916; // 95% of 2016
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        
        // Deployment parameters
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        
        // Message start string - UNIQUE TO YOUR BLOCKCHAIN!
        pchMessageStart[0] = 0xda;
        pchMessageStart[1] = 0xvi;
        pchMessageStart[2] = 0xd0;
        pchMessageStart[3] = 0x01; // "david" custom bytes
        
        // Network ports - USE DIFFERENT PORTS THAN BITCOIN!
        nDefaultPort = 18833;  // Different from Bitcoin's 8333
        nPruneAfterHeight = 100000;
        m_assumed_blockchain_size = 1;
        m_assumed_chain_state_size = 1;
        
        // Genesis block - TEMPORARY - YOU'LL NEED TO GENERATE A REAL ONE!
        genesis = CreateGenesisBlock(1739721600, 2083236893, 0x1d00ffff, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        
        // Verify your genesis block (uncomment and update after generating real genesis)
        // assert(consensus.hashGenesisBlock == uint256S("0x000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f"));
        
        // No DNS seeds or fixed peers for your custom chain initially
        vSeeds.clear();
        vFixedSeeds.clear();
        
        // Address prefixes - CHANGE THESE FOR YOUR BLOCKCHAIN!
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,48); // Starts with 'D' instead of '1'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,50); // Starts with 'S' instead of '3'
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,176); // Different from Bitcoin
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x88, 0xB2, 0x1E};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x88, 0xAD, 0xE4};
        
        bech32_hrp = "dc"; // "davidcoin" instead of "bc" for bitcoin
        
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        m_is_test_chain = false;
        m_is_mockable_chain = false;
    }
};

/**
 * Testnet for your custom blockchain
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = CBaseChainParams::TESTNET;
        consensus.nSubsidyHalvingInterval = 210000;
        consensus.BIP16Height = 0;
        consensus.BIP34Height = 0;
        consensus.BIP34Hash = uint256();
        consensus.BIP65Height = 0;
        consensus.BIP66Height = 0;
        consensus.CSVHeight = 0;
        consensus.SegwitHeight = 0;
        consensus.MinBIP9WarningHeight = 0;
        
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 14 * 24 * 60 * 60;
        consensus.nPowTargetSpacing = 10 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1512;
        consensus.nMinerConfirmationWindow = 2016;
        
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        
        pchMessageStart[0] = 0xda;
        pchMessageStart[1] = 0xvi;
        pchMessageStart[2] = 0xd0;
        pchMessageStart[3] = 0x02; // Different from mainnet
        
        nDefaultPort = 18834; // Different from mainnet
        nPruneAfterHeight = 1000;
        m_assumed_blockchain_size = 1;
        m_assumed_chain_state_size = 1;
        
        genesis = CreateGenesisBlock(1739721600, 2083236893, 0x1d00ffff, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        
        vFixedSeeds.clear();
        vSeeds.clear();
        
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111); // Starts with 'm' or 'n'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196); // Starts with '2'
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239); // Starts with '9'
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};
        
        bech32_hrp = "td"; // testnet david
        
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        m_is_test_chain = true;
        m_is_mockable_chain = false;
    }
};

/**
 * Regression test for your custom blockchain
 */
class CRegTestParams : public CChainParams {
public:
    explicit CRegTestParams(const RegTestOptions& opts) {
        strNetworkID = CBaseChainParams::REGTEST;
        consensus.nSubsidyHalvingInterval = 150;
        consensus.BIP16Height = 0;
        consensus.BIP34Height = 0;
        consensus.BIP34Hash = uint256();
        consensus.BIP65Height = 0;
        consensus.BIP66Height = 0;
        consensus.CSVHeight = 0;
        consensus.SegwitHeight = 0;
        consensus.MinBIP9WarningHeight = 0;
        
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 14 * 24 * 60 * 60;
        consensus.nPowTargetSpacing = 10 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108;
        consensus.nMinerConfirmationWindow = 144;
        
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        
        pchMessageStart[0] = 0xda;
        pchMessageStart[1] = 0xvi;
        pchMessageStart[2] = 0xd0;
        pchMessageStart[3] = 0x03; // Different from mainnet and testnet
        
        nDefaultPort = 18835; // Different from mainnet and testnet
        nPruneAfterHeight = 1000;
        m_assumed_blockchain_size = 0;
        m_assumed_chain_state_size = 0;
        
        genesis = CreateGenesisBlock(1739721600, 2, 0x207fffff, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        
        vFixedSeeds.clear();
        vSeeds.clear();
        
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        m_is_test_chain = true;
        m_is_mockable_chain = true;
        
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};
        
        bech32_hrp = "dcrt"; // david regtest
    }
};

/**
 * Signet for your custom blockchain
 */
class CSigNetParams : public CChainParams {
public:
    explicit CSigNetParams(const SigNetOptions& options) {
        strNetworkID = CBaseChainParams::SIGNET;
        // ... (similar structure to above)
    }
};

// Static methods for creating chain params
std::unique_ptr<const CChainParams> CChainParams::Main() {
    return std::make_unique<CMainParams>();
}

std::unique_ptr<const CChainParams> CChainParams::TestNet() {
    return std::make_unique<CTestNetParams>();
}

std::unique_ptr<const CChainParams> CChainParams::TestNet4() {
    return std::make_unique<CTestNetParams>();
}

std::unique_ptr<const CChainParams> CChainParams::SigNet(const SigNetOptions& options) {
    return std::make_unique<CSigNetParams>(options);
}

std::unique_ptr<const CChainParams> CChainParams::RegTest(const RegTestOptions& opts) {
    return std::make_unique<CRegTestParams>(opts);
}

// Your existing helper functions continue here...
void ReadSigNetArgs(const ArgsManager& args, CChainParams::SigNetOptions& options)
{
    if (!args.GetArgs("-signetseednode").empty()) {
        options.seeds.emplace(args.GetArgs("-signetseednode"));
    }
    if (!args.GetArgs("-signetchallenge").empty()) {
        const auto signet_challenge = args.GetArgs("-signetchallenge");
        if (signet_challenge.size() != 1) {
            throw std::runtime_error("-signetchallenge cannot be multiple values.");
        }
        const auto val{TryParseHex<uint8_t>(signet_challenge[0])};
        if (!val) {
            throw std::runtime_error(strprintf("-signetchallenge must be hex, not '%s'.", signet_challenge[0]));
        }
        options.challenge.emplace(*val);
    }
}

void ReadRegTestArgs(const ArgsManager& args, CChainParams::RegTestOptions& options)
{
    if (auto value = args.GetBoolArg("-fastprune")) options.fastprune = *value;
    if (HasTestOption(args, "bip94")) options.enforce_bip94 = true;

    for (const std::string& arg : args.GetArgs("-testactivationheight")) {
        const auto found{arg.find('@')};
        if (found == std::string::npos) {
            throw std::runtime_error(strprintf("Invalid format (%s) for -testactivationheight=name@height.", arg));
        }

        const auto value{arg.substr(found + 1)};
        const auto height{ToIntegral<int32_t>(value)};
        if (!height || *height < 0 || *height >= std::numeric_limits<int>::max()) {
            throw std::runtime_error(strprintf("Invalid height value (%s) for -testactivationheight=name@height.", arg));
        }

        const auto deployment_name{arg.substr(0, found)};
        if (const auto buried_deployment = GetBuriedDeployment(deployment_name)) {
            options.activation_heights[*buried_deployment] = *height;
        } else {
            throw std::runtime_error(strprintf("Invalid name (%s) for -testactivationheight=name@height.", arg));
        }
    }

    for (const std::string& strDeployment : args.GetArgs("-vbparams")) {
        std::vector<std::string> vDeploymentParams = SplitString(strDeployment, ':');
        if (vDeploymentParams.size() < 3 || 4 < vDeploymentParams.size()) {
            throw std::runtime_error("Version bits parameters malformed, expecting deployment:start:end[:min_activation_height]");
        }
        CChainParams::VersionBitsParameters vbparams{};
        const auto start_time{ToIntegral<int64_t>(vDeploymentParams[1])};
        if (!start_time) {
            throw std::runtime_error(strprintf("Invalid nStartTime (%s)", vDeploymentParams[1]));
        }
        vbparams.start_time = *start_time;
        const auto timeout{ToIntegral<int64_t>(vDeploymentParams[2])};
        if (!timeout) {
            throw std::runtime_error(strprintf("Invalid nTimeout (%s)", vDeploymentParams[2]));
        }
        vbparams.timeout = *timeout;
        if (vDeploymentParams.size() >= 4) {
            const auto min_activation_height{ToIntegral<int64_t>(vDeploymentParams[3])};
            if (!min_activation_height) {
                throw std::runtime_error(strprintf("Invalid min_activation_height (%s)", vDeploymentParams[3]);
            }
            vbparams.min_activation_height = *min_activation_height;
        } else {
            vbparams.min_activation_height = 0;
        }
        bool found = false;
        for (int j=0; j < (int)Consensus::MAX_VERSION_BITS_DEPLOYMENTS; ++j) {
            if (vDeploymentParams[0] == VersionBitsDeploymentInfo[j].name) {
                options.version_bits_parameters[Consensus::DeploymentPos(j)] = vbparams;
                found = true;
                LogInfo("Setting version bits activation parameters for %s to start=%ld, timeout=%ld, min_activation_height=%d",
                        vDeploymentParams[0], vbparams.start_time, vbparams.timeout, vbparams.min_activation_height);
                break;
            }
        }
        if (!found) {
            throw std::runtime_error(strprintf("Invalid deployment (%s)", vDeploymentParams[0]));
        }
    }
}

static std::unique_ptr<const CChainParams> globalChainParams;

const CChainParams &Params() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<const CChainParams> CreateChainParams(const ArgsManager& args, const ChainType chain)
{
    switch (chain) {
    case ChainType::MAIN:
        return CChainParams::Main();
    case ChainType::TESTNET:
        return CChainParams::TestNet();
    case ChainType::TESTNET4:
        return CChainParams::TestNet4();
    case ChainType::SIGNET: {
        auto opts = CChainParams::SigNetOptions{};
        ReadSigNetArgs(args, opts);
        return CChainParams::SigNet(opts);
    }
    case ChainType::REGTEST: {
        auto opts = CChainParams::RegTestOptions{};
        ReadRegTestArgs(args, opts);
        return CChainParams::RegTest(opts);
    }
    }
    assert(false);
}

void SelectParams(const ChainType chain)
{
    SelectBaseParams(chain);
    globalChainParams = CreateChainParams(gArgs, chain);
}