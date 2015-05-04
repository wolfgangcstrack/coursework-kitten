/*
Lab 2 - Regular Expressions
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This is the header file for the RegexIO class.
*/

#ifndef REGEX_IO_H_
#define REGEX_IO_H_

#include <fstream>
#include <string>
#include <regex>

class RegexIO
{
protected:
	std::string pattern;
	std::regex rex;
public:
	// constructors and destructor
	RegexIO() {}
	RegexIO(const RegexIO &rIO);
	RegexIO(const std::string &patt);
	~RegexIO() {}
	// getters
	const std::string & getPattern() { return pattern; }
	// setters
	void setPattern(const std::string &patt);
	// other methods
	bool stringMatch(const std::string &text) { return std::regex_match(text, rex); }
	bool searchStringForMatch(const std::string &text) { return std::regex_search(text, rex); }
	bool searchFileForMatch(const std::string &filename);
	std::string findMatchInFile(const std::string &filename, unsigned int matchNum);
};

RegexIO::RegexIO(const RegexIO &rIO)
{
	pattern = rIO.pattern;
	rex = rIO.rex;
}

RegexIO::RegexIO(const std::string &patt)
{
	pattern = patt;
	rex = regex(pattern);
}

void RegexIO::setPattern(const std::string &patt)
{
	pattern = patt;
	rex = regex(pattern);
}

bool RegexIO::searchFileForMatch(const std::string &filename)
{
	std::ifstream ifs;
	
	ifs.open(filename);
	if (!ifs.is_open()) // if file was not opened
		return false;

	std::string line;
	while (getline(ifs, line))
	{
		if (std::regex_search(line, rex))
			return true;
	}
}

std::string RegexIO::findMatchInFile(const std::string &filename, unsigned int matchNum)
{
	std::ifstream ifs;

	ifs.open(filename);
	if (!ifs.is_open() || matchNum == 0)
		return "";

	std::string line;
	std::string match;
	unsigned int matchCount = 0;
	while (getline(ifs, line) && matchCount != matchNum)
	{
		if (std::regex_search(line, rex))
		{
			match = line;
			matchCount++;
		}
	}

	// if the match number wanted is greater than the total number of matches
	// return an empty string, otherwise return the nth match (n = matchNum)
	return (matchCount != matchNum ? "" : match);
}

#endif // REGEX_IO_H_