#include <iostream>
#include <random>
#include <string>

class XorString {
public:
    XorString(const std::string& str, const std::string& key) : str_(str), key_(key) {} /*Initialize Constructor Declaration*/

    std::string Encrypt(const std::string& watermark) {
        std::string result;
        std::mt19937 rng;
        rng.seed(std::random_device()());
        std::uniform_int_distribution<std::mt19937::result_type> dist(1, 10);
        for (size_t i = 0; i < str_.size(); i++) {
            result += (str_[i] ^ key_[i % key_.size()]) ^ dist(rng);
        }
        return watermark + result;
    }

	std::string Decrypt(const std::string& watermark) {
        std::string result;
        std::mt19937 rng;
        rng.seed(std::random_device()());
        std::uniform_int_distribution<std::mt19937::result_type> dist(1, 10);
        for (size_t i = watermark.size(); i < str_.size(); i++) {
            result += (str_[i] ^ dist(rng)) ^ key_[(i - watermark.size()) % key_.size()];
        }
        return result;
    }

private:
	std::string str_; /*Encrypted -> pepsi_was_never_here}]ZRR↕‼I\C¶↓C*/
	std::string key_; /*Key -> 1234567890*/
};
