/*
Lab 1 - Bitsets and Vectors
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This is the header file for the MorseChar class. Implementation included.
*/

#ifndef MORSE_CHAR_H_
#define MORSE_CHAR_H_

#include "EncryptionChar.h"
#include <string>

class MorseChar : public EncryptionChar
{
private:
	std::string code; // holds the Morse code representation

	void setBits()
	{
		for (int i = 0; i < code.length(); i++)
		{
			switch (code[i])
			{
			case ' ':
				charBits << 2;
				break;
			case '-':
				charBits << 2;
				charBits = std::bitset<bitsetSize>(charBits.to_ulong() + 1);
				break;
			case '.':
				charBits << 2;
				charBits = std::bitset<bitsetSize>(charBits.to_ulong() + 2);
				break;
			case '_' :
				charBits << 2;
				charBits = std::bitset<bitsetSize>(charBits.to_ulong() + 3);
				break;
			default:; // do nothing
			}
		}
	}
public:
	// constructors and destructor
	MorseChar() {}
	MorseChar(const MorseChar &mc) { code = mc.code; setBits(); }
	MorseChar(std::string morsecode) { code = morsecode; setBits(); }
	~MorseChar() {}
	// getters
	const std::string & getCode() const { return code; }
	// setters
	void setCode(const std::string &morsecode) { code = morsecode; setBits(); }
};

#endif // MORSE_CHAR_H_