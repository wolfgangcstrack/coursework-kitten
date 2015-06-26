/*
Lab 1 - Bitsets and Vectors
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This is the header file for the Lab1Decryptor class. It wraps a
MorseANSIConverter for decrypting the Morse.bin file from ANSI to Morse to
decrypted letters.
*/

#ifndef LAB_1_DECRYPTOR_H_
#define LAB_1_DECRYPTOR_H_

#include "MorseANSIConverter.h"

class Lab1Decryptor
{
private:
	MorseANSIConverter mac;

	char getLetter(const MorseChar &mc);
public:
	// constructors and destructor
	Lab1Decryptor() {}
	~Lab1Decryptor() {}
	// getters
	const std::bitset<2> & checkMorseCache() { return mac.checkMorseCache(); }
	const std::bitset<8> & checkANSICache() { return mac.checkANSICache(); }

	// decryption function
	void decrypt(const std::vector<ANSIChar> &acv, std::vector<char> &result); // stores decrypted result in vector<char>
	void decrypt(const std::vector<ANSIChar> &acv, std::string &result); // stores decrypted result in string
};

#endif // LAB_1_DECRYPTOR_H_