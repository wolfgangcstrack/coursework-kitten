/*
Lab 1 - Bitsets and Vectors
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This is the header file for the MorseANSIConverter.
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
	const static std::vector<char> morseCodes;
	short morseHash(std::bitset<2> ansi2Bit);

	// used for converting 2 bits to a Morse code at a time
	std::bitset<2> morseCache;
	std::bitset<16> ansiCache;
public:
	// constructors and destructor
	MorseANSIConverter();
	MorseANSIConverter(const MorseANSIConverter &mad);
	~MorseANSIConverter() {}
	// getters - checkCache methods are mainly for debugging purposes
	const std::bitset<2> & checkMorseCache() { return morseCache; }
	const std::bitset<16> & checkANSICache() { return ansiCache; }
	
	// conversion functions
	std::vector<MorseChar> convertANSIToMorse(std::vector<ANSIChar> acv);
	std::vector<ANSIChar> convertMorseToANSI(std::vector<MorseChar> mcv);
};

#endif // MORSE_ANSI_DECRYPTOR_H_