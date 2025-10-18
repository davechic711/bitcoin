#pragma once
#include <string>
#include <stdexcept>  // Add this for std::runtime_error

enum class ChainType {
    MAIN,
    TESTNET,
    SIGNET,
    REGTEST,
    SUPPERCHAIN
};

inline std::string ChainTypeToString(ChainType c) {
    switch (c) {
        case ChainType::MAIN:        return "main";
        case ChainType::TESTNET:     return "test";
        case ChainType::SIGNET:      return "signet";
        case ChainType::REGTEST:     return "regtest";
        case ChainType::SUPPERCHAIN: return "supperchain";
    }
    return "main";
}

inline ChainType ChainTypeFromString(const std::string& s) {
    if (s == "main")        return ChainType::MAIN;
    if (s == "test")        return ChainType::TESTNET;
    if (s == "signet")      return ChainType::SIGNET;
    if (s == "regtest")     return ChainType::REGTEST;
    if (s == "supperchain") return ChainType::SUPPERCHAIN;
    throw std::runtime_error("Unknown chain \"" + s + "\"");
}
