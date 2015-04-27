/*
Lab 1 - Bitsets and Vectors
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This is the header file for the ANSIChar class. Implementation, besides
getter methods, are in ANSIChar.cpp.
*/

#ifndef ANSI_CHAR_H_
#define ANSI_CHAR_H_

#include "EncryptionChar.h"

class ANSIChar : public EncryptionChar
{
private:
	char letter; // stores the ANSI character
	// also technically stores ANSI code
public:
	// constructors and destructor
	ANSIChar();
	ANSIChar(const ANSIChar &ac);
	ANSIChar(char ansi);
	//ANSIChar(std::bitset<8> ansiBits);
	~ANSIChar() {}
	// getters
	char getLetter() const { return letter; }
	int getANSICode() const { return letter; }
	//const std::bitset<8> & getBits() { return ansiBits; }
	// setters
	void setLetter(char ansi);
};

#endif // ANSI_CHAR_H_