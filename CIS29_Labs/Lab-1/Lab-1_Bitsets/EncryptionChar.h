/*
Lab 1 - Bitsets and Vectors
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This is the header file for the EncryptionChar class. It is an abstract
base class for MorseChar and ANSIChar.
*/

#ifndef ENCRPYTION_CHAR_H
#define ENCRPYTION_CHAR_H

#include <bitset>

class EncryptionChar
{
protected:
	const static int bitsetSize = 8;
	std::bitset<bitsetSize> charBits;

	// method for setting bits based on type of EncryptedChar
	virtual void setBits() = 0;
public:
	// getters
	const std::bitset<bitsetSize> & getBits() { return charBits; }
};

#endif // ENCRPYTION_CHAR_H