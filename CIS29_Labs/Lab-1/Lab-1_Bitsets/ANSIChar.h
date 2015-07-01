/*
Lab 1 - Bitsets and Vectors
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This is the header file for the ANSIChar class. This is mainly a wrapper
class for characters read from Morse.bin. Implementation included.
*/

#ifndef ANSI_CHAR_H_
#define ANSI_CHAR_H_

#include "EncryptionChar.h"

class ANSIChar : public EncryptionChar
{
private:
	char letter; // stores the ANSI character
	// also technically stores ANSI code

	void setBits() { charBits = std::bitset<bitsetSize>(letter); }
public:
	// constructors and destructor
	ANSIChar() { letter = 0; setBits(); }
	ANSIChar(const ANSIChar &ac) { letter = ac.letter; setBits(); }
	ANSIChar(char ansi) { letter = ansi; setBits(); }
	~ANSIChar() {}
	// getters
	char getLetter() const { return letter; }
	int getANSICode() const { return letter; }
	// setters
	void setLetter(char ansi) { letter = ansi; setBits(); }
};

#endif // ANSI_CHAR_H_