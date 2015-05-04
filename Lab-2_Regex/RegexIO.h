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
	bool stringMatch(const std::string &text);
	bool searchStringForMatch(const std::string &text);
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

#endif // REGEX_IO_H_