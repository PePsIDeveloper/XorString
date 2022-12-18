#pragma once

#include <array>
#include <cstddef>
#include <string>

template <std::size_t Len>
class XorString
{
private:
    std::array<char, Len> encrypted;

public:
    XorString(const char* data, const std::string& key)
    {
        for (std::size_t i = 0; i < Len; ++i) {
            encrypted[i] = data[i] ^ key[i % key.length()];
        }
    }

    std::string decrypt(const std::string& key) const
    {
        std::array<char, Len> plain;
        for (std::size_t i = 0; i < Len; ++i) {
            plain[i] = encrypted[i] ^ key[i % key.length()];
        }
        return std::string(plain.data());
    }
};

#define ENCRYPTED_STRING(string, key) \
    []() -> std::string { \
        constexpr std::size_t len = sizeof(string) / sizeof(string[0]); \
        static auto enc = XorString<len>(string, key); \
        return enc.decrypt(key); \
    }()
