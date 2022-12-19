#pragma once

#include <array>
#include <cstddef>
#include <string>
#include <functional>

template <std::size_t Len>
class XorString
{
private:
    std::array<char, Len> encrypted;
    std::function<std::string(const std::string&)> decryptFunc;

public:
    XorString(const char* data, const std::string& key)
    {
        for (std::size_t i = 0; i < Len; ++i) {
            encrypted[i] = data[i] ^ key[i % key.length()];
        }

        decryptFunc = [&](const std::string& decryptionKey) {
            std::array<char, Len> plain;
            for (std::size_t i = 0; i < Len; ++i) {
                plain[i] = encrypted[i] ^ decryptionKey[i % decryptionKey.length()];
            }
            return std::string(plain.data());
        };
    }

    std::string decrypt(const std::string& key) const
    {
        return decryptFunc(key);
    }
};

#define ENCRYPTED_STRING(string, key) \
    []() -> std::string { \
        constexpr std::size_t len = sizeof(string) / sizeof(string[0]); \
        static auto enc = XorString<len>(string, key); \
        return enc.decrypt(key); \
    }()
