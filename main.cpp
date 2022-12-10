#include <iostream>
#include <string>
#include <ctime>

#include "blowfish.h"

void usage() {
	std::cout << "Usage: ./blowfish <mode> <block> <key>\n";
	std::cout << "\t <mode>:   -e -> encrypt block\n\t\t   -d -> decrypt block\n";
	std::cout << "\t <block>:  the input block for encryption/decryption [block length: 8 bytes]\n";
	std::cout << "\t <key>:    the input key for encryption/decryption [key length: 8 bytes]\n";
}

int main(int argc, char* argv[]) {
	srand(time(0));

	uint64_t key = random();
	uint64_t block = 0;
	char mode = 0;	
	
	if (argc == 4) {
		mode = argv[1][1];
		if (mode != 'e' && mode != 'd') {
			std::cout << "Invalid mode\n";
			usage();
			return -1;
		}

		try {
			block = std::stoull(argv[2]);
		} catch (std::invalid_argument& e) {
			std::cout << "Invalid block. Your block will be set by default: " << block << "\n";
		}

		try {
			key = std::stoull(argv[3]);
		} catch (std::invalid_argument& e) {
			std::cout << "Invalid key. Your block will be set by default: " << key << "\n";
		}

		Cipher::Blowfish blowfish(key);
		block = blowfish.encrypt(block, mode);

		std::cout << (mode == 'e' ? "Encrypted: " : "Decrypted: ") << block << "\n";
	} else {
		std::cout << "Wrong arguments\n";
		usage();
	}

	return 0;
}
