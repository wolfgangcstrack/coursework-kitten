/*
Lab 1 - Bitsets and Vectors
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This is the implementation file for the Lab1Decryptor class.
*/

#include "Lab1Decryptor.h"

char Lab1Decryptor::getLetter(const MorseChar &mc)
{
	std::string morseLetter(mc.getCode());

	if (morseLetter.compare(".-") == 0)
		return 'A';
	else if (morseLetter.compare("-...") == 0)
		return 'B';
	else if (morseLetter.compare("-.-.") == 0)
		return 'C';
	else if (morseLetter.compare("-..") == 0)
		return 'D';
	else if (morseLetter.compare(".") == 0)
		return 'E';
	else if (morseLetter.compare("..-.") == 0)
		return 'F';
	else if (morseLetter.compare("--.") == 0)
		return 'G';
	else if (morseLetter.compare("....") == 0)
		return 'H';
	else if (morseLetter.compare("..") == 0)
		return 'I';
	else if (morseLetter.compare(".---") == 0)
		return 'J';
	else if (morseLetter.compare("-.-") == 0)
		return 'K';
	else if (morseLetter.compare(".-..") == 0)
		return 'L';
	else if (morseLetter.compare("--") == 0)
		return 'M';
	else if (morseLetter.compare("-.") == 0)
		return 'N';
	else if (morseLetter.compare("---") == 0)
		return 'O';
	else if (morseLetter.compare(".--.") == 0)
		return 'P';
	else if (morseLetter.compare("--.-") == 0)
		return 'Q';
	else if (morseLetter.compare(".-.") == 0)
		return 'R';
	else if (morseLetter.compare("...") == 0)
		return 'S';
	else if (morseLetter.compare("-") == 0)
		return 'T';
	else if (morseLetter.compare("..-") == 0)
		return 'U';
	else if (morseLetter.compare("...-") == 0)
		return 'V';
	else if (morseLetter.compare("--") == 0)
		return 'W';
	else if (morseLetter.compare("-..-") == 0)
		return 'X';
	else if (morseLetter.compare("-.--") == 0)
		return 'Y';
	else if (morseLetter.compare("--..") == 0)
		return 'Z';
	else if (morseLetter.compare("-----") == 0)
		return '0';
	else if (morseLetter.compare(".----") == 0)
		return '1';
	else if (morseLetter.compare("..---") == 0)
		return '2';
	else if (morseLetter.compare("...--") == 0)
		return '3';
	else if (morseLetter.compare("....-") == 0)
		return '4';
	else if (morseLetter.compare(".....") == 0)
		return '5';
	else if (morseLetter.compare("-....") == 0)
		return '6';
	else if (morseLetter.compare("--...") == 0)
		return '7';
	else if (morseLetter.compare("---..") == 0)
		return '8';
	else if (morseLetter.compare("----.") == 0)
		return '9';
	else if (morseLetter.compare(".---.") == 0)
		return '\'';
	else if (morseLetter.compare(".--.-.") == 0)
		return '@';
	else if (morseLetter.compare("---...") == 0)
		return ':';
	else if (morseLetter.compare("--..--") == 0)
		return ',';
	else if (morseLetter.compare("...-..-") == 0)
		return '$';
	else if (morseLetter.compare("-...-") == 0)
		return '=';
	else if (morseLetter.compare("-.-.--") == 0)
		return '!';
	else if (morseLetter.compare(".-.-.-") == 0)
		return '.';
	else if (morseLetter.compare("..--..") == 0)
		return '?';
	else if (morseLetter.compare(".-..-.") == 0)
		return '\"';
	else
		return ' ';
}

void Lab1Decryptor::decrypt(const std::vector<ANSIChar> &acv, std::vector<char> &result)
{
	result.clear();
	std::vector<MorseChar> morseChars(mac.convertANSIToMorse(acv));

	for (int i = 0; i < morseChars.size(); i++)
		result.push_back(getLetter(morseChars[i]));
}

void Lab1Decryptor::decrypt(const std::vector<ANSIChar> &acv, std::string &result)
{
	result = "";
	std::vector<char> vecTemp;
	decrypt(acv, vecTemp);

	for (int i = 0; i < vecTemp.size(); i++)
		result += vecTemp[i];
}