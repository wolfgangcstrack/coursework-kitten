/*
Lab 1 - Bitsets and Vectors
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This is the implementation file for the MorseANSIConverter class.
*/

#include "MorseANSIConverter.h"

// initialize static vector
std::vector<char> MorseANSIConverter::morseCodes = std::vector<char>({
	' ',
	'-',
	'.',
	'_'
});

std::vector<MorseChar> MorseANSIConverter::convertANSIToMorse(const std::vector<ANSIChar> &acv)
{
	std::vector<MorseChar> result;
	std::bitset<2> morseWS("11");
	std::string morseString = "";
	char temp; // used for adding 2-bit converted value to a MorseChar

	for (int i = 0; i < acv.size(); i++)
	{
		ansiCache = std::bitset<8>(acv[i].getANSICode());
		for (int i = ansiCache.size() - 1; i > 0; i -= 2)
		{
			morseCache[1] = ansiCache[i];
			morseCache[0] = ansiCache[i - 1];
			temp = morseCodes[morseHash(morseCache)];
			if (temp == '_' || temp == ' ')
			{
				result.push_back(MorseChar(morseString));
				result.push_back(MorseChar(" "));
				morseString = "";
			}
			else
				morseString += temp;
		}
	}

	return result;
}