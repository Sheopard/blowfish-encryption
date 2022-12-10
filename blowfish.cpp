#include "blowfish.h"

Cipher::Blowfish::Blowfish(uint64_t key) {
	key_schedule(key);
}

uint64_t Cipher::Blowfish::encrypt(uint64_t block, char mode) {
	return feistel_network((block >> 32) & 0xffffffff, block & 0xffffffff, mode);
}

uint64_t Cipher::Blowfish::feistel_network(uint32_t left, uint32_t right, char mode) {
	uint32_t temp = 0;
	if (mode == 'e') {
		for (uint8_t i = 0; i < 16; i++) {
			left ^= P[i];
			temp = f(left);
			temp ^= right;
			right = left;
			left = temp;
		}

		std::swap(left, right);

		right ^= P[16];
		left ^= P[17];
	}
	else if (mode == 'd') {
		for (uint8_t i = 0; i < 16; i++) {
			left ^= P[17 - i];
			temp = f(left);
			temp ^= right;
			right = left;
			left = temp;
		}

		std::swap(left, right);

		right ^= P[1];
		left ^= P[0];
	}

	return ((uint64_t)left << 32) | right;
}

void Cipher::Blowfish::key_schedule(uint64_t key) {
	for (uint8_t i = 0; i < 18; i++) {
		P[i] ^= (key & 0xffffffff);
		P[++i] ^= ((key >> 32) & 0xffffffff);
	}

	uint64_t temp = 0;
	for (uint8_t i = 0; i < 18; i++) {
		temp = feistel_network((temp >> 32) & 0xffffffff, temp & 0xffffffff, 'e');
		P[i] = (temp & 0xffffffff);
		P[++i] = ((temp >> 32) & 0xffffffff);
	}

	for (uint8_t i = 0; i < 4; i++) {
		for (uint16_t j = 0; j < 256; j++) {
			temp = feistel_network((temp >> 32) & 0xffffffff, temp & 0xffffffff, 'e');
			S[i][j] = (temp & 0xffffffff);
			S[i][++j] = ((temp >> 32) & 0xffffffff);
		}
	}
}

uint32_t Cipher::Blowfish::f(uint32_t block) {
	return ((S[0][(block >> 24) & 0xff] + S[1][(block >> 16) & 0xff]) ^ S[2][(block >> 8) & 0xff]) + S[3][block & 0xff];
}
