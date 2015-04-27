/*
Lab 1 - Bitsets and Vectors
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This is the header file for the MorseANSIConverter class.
*/

#ifndef MORSE_ANSI_DECRYPTOR_H_
#define MORSE_ANSI_DECRYPTOR_H_

#include "MorseChar.h"
#include "ANSIChar.h"
#include <vector>

class MorseANSIConverter
{
private:
	// stores the 4 different types of Morse codes: space, dash, dot, and word separator
	static std::vector<char> morseCodes;
	short morseHash(std::bitset<2> ansi2Bit) { return static_cast<short>(ansi2Bit.to_ulong()); }

	// used for converting 2 bits to a Morse code at a time
	std::bitset<2> morseCache;
	std::bitset<16> ansiCache;
public:
	// constructors and destructor
	MorseANSIConverter() {}
	~MorseANSIConverter() {}
	// getters - checkCache methods are mainly for debugging purposes
	const std::bitset<2> & checkMorseCache() const { return morseCache; }
	const std::bitset<16> & checkANSICache() const { return ansiCache; }
	
	// conversion functions
	std::vector<MorseChar> convertANSIToMorse(const std::vector<ANSIChar> &acv);
	//std::vector<ANSIChar> convertMorseToANSI(const std::vector<MorseChar> &mcv);
};

#endif // MORSE_ANSI_DECRYPTOR_H_