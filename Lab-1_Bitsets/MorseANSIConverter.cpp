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
		ansiCache = std::bitset<16>(acv[i].getANSICode());
		for (int i = 0; i < ansiCache.size(); i += 2)
		{
			morseCache = std::bitset<2>(ansiCache[i] + "" + ansiCache[i + 1]);
			temp = morseCodes[morseHash(morseCache)];
			std::cout << temp;
			if (temp == '_')
			{
				result.push_back(MorseChar(morseString));
				result.push_back(MorseChar("_"));
				morseString = "";
			}
			else if (temp == ' ')
				; // do nothing
			else
				morseString += temp;
		}
	}

	return result;
}