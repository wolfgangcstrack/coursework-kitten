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
	RegexIO();
	RegexIO(const RegexIO &rIO);
	RegexIO(const std::string &patt);
	~RegexIO();
	// getters
	const std::string & getPattern() { return pattern; }
	// setters
	void setPattern(const std::string &patt);
	// other methods
	bool stringMatch(std::string text);
	bool searchStringForMatch(std::string text);
	bool searchFileForMatch(std::string filename);
	std::string findMatchInFile(std::string filename, unsigned int matchNum);
};

#endif // REGEX_IO_H_