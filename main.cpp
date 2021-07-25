#include <iostream>
#include <string>
#include "blowfish.h"

int main(int argc, char** argv) {
	uint64_t key = 0;
	uint64_t block = 0;
	char mode = 0;	
	
	if (argc == 4) {
		mode = argv[1][1];
		block = std::stoull(argv[2]);		
		key = std::stoull(argv[3]);
		Blowfish blowfish(key);
		block =	blowfish.encrypt(block, mode);	

		if (mode == 'e') {
			std::cout << "Encrypted: ";
		} else if (mode == 'd') {
			std::cout << "Decrypted: ";
		}
		std::cout << block << "\n";
		
	} else {
		std::cout << "Wrong arguments\n";
		return -1;
	}

	return 0;
}
