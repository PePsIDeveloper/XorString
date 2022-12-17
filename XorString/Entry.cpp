#include "Utils/XorUtils.hpp"
int main() {
	XorString xor_string("Hello, world!", "1234567890qwertyuiopasdfghjklzxcvbnm");
	std::string encrypted = xor_string.Encrypt("pepsi_was_never_here");
	std::cout << "Encrypted: " << encrypted << std::endl;
	std::cout << "Decrypted: " << xor_string.Decrypt("pepsi_was_never_here") << std::endl;
	return 0;
}