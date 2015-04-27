/*
Lab 1 - Bitsets and Vectors
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This is the header file for the MorseChar class.
*/

#ifndef MORSE_CHAR_H_
#define MORSE_CHAR_H_

#include "EncryptionChar.h"
#include <string>

class MorseChar : public EncryptionChar
{
private:
	std::string code; // holds the Morse code representation
public:
	// constructors and destructor
	MorseChar();
	MorseChar(const MorseChar &mc);
	MorseChar(std::string morsecode);
	~MorseChar() {}
	// getters
	const std::string & getCode() { return code; }
	// setters
	void setCode(std::string morsecode);
};

#endif // MORSE_CHAR_H_