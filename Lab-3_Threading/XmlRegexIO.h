/*
Lab 3 - Threading
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This header file contains the utility class for extracting XML nodes and
XML node data from given files. The methods store the build XML node in a
parameter and return booleans.
*/

#ifndef _XML_REGEX_IO_H
#define _XML_REGEX_IO_H

#include "XmlNode.h"
#include <string>
#include <regex>
using namespace std;

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class XmlRegexIO
{
private:
	string pattern;
	regex rex;
public:
	// constructors and destructor
	XmlRegexIO() {}
	XmlRegexIO(const string &patt) { pattern = patt; rex = regex(pattern); }
	~XmlRegexIO() {}
	// getters
	const string & getPattern() { return pattern; }
	const regex & getRegex() { return rex; }
	// setters
	void setPattern(const string &patt) { pattern = patt; rex = regex(pattern); }
	// other methods
	bool getXmlTags(const string &filename, XmlNode &store);
	bool getXmlDataFromFile(const string &dataFilename, XmlNode &store);
	bool getXmlDataFromString(const string &data, XmlNode &store);
	bool getAllMatches(const string &dataFilename, vector<string> &store);
};

bool XmlRegexIO::getXmlTags(const string &filename, XmlNode &store)
{
	// check if file exists/can be read from
	std::ifstream ifs;
	ifs.open(filename);
	if (!ifs.is_open())
		return false;

	// store entire file in content
	std::string content((istreambuf_iterator<char>(ifs)),
		(istreambuf_iterator<char>()));

	if (!regex_search(content, rex)) // check if pattern returns true
		return false;

	int positionOfOpeningTag = content.find("<element name=\"" + store.getClassName());
	if (positionOfOpeningTag < 0) // validate string position
		return false;

	int lengthTillClosingTag;
	for (int i = positionOfOpeningTag; i < content.length(); i++)
	{
		if (content[i] == '<') // find closing tag of element
		{
			if (regex_match(content.substr(i, 10), regex("</element>")))
			{
				lengthTillClosingTag = (i + 10) - positionOfOpeningTag;
				store.setXMLTags(content.substr(positionOfOpeningTag, lengthTillClosingTag));
				break; // out of loop
			}
		}
	}

	return true;
}

bool XmlRegexIO::getXmlDataFromFile(const string &dataFilename, XmlNode &store)
{
	// check if file exists/can be read from
	std::ifstream ifs;
	ifs.open(dataFilename);
	if (!ifs.is_open())
		return false;

	// store entire file in content
	std::string content((istreambuf_iterator<char>(ifs)),
		(istreambuf_iterator<char>()));

	if (!regex_search(content, rex)) // check if pattern returns true
		return false;

	int positionOfOpeningTag = content.find("<" + store.getClassName());
	if (positionOfOpeningTag < 0) // validate string position
		return false;

	int lengthTillClosingTag;
	for (int i = positionOfOpeningTag; i < content.length(); i++)
	{
		if (content[i] == '<') // find closing tag of element
		{
			if (regex_search(content.substr(i, pattern.length()), regex("</" + store.getClassName() + ">")))
			{
				lengthTillClosingTag = (i + store.getClassName().length() + 3) - positionOfOpeningTag;
				store.readData(content.substr(positionOfOpeningTag, lengthTillClosingTag));
				break; // out of loop
			}
		}
	}

	return true;
}

bool XmlRegexIO::getXmlDataFromString(const string &data, XmlNode &store)
{
	if (!regex_search(data, rex)) // check if pattern returns true
		return false;

	int positionOfOpeningTag = data.find("<" + store.getClassName());
	if (positionOfOpeningTag < 0) // validate string position
		return false;

	int lengthTillClosingTag;
	store.readData(data);

	return true;
}

bool XmlRegexIO::getAllMatches(const string &dataFilename, vector<string> &store)
{
	// check if file exists/can be read from
	std::ifstream ifs;
	ifs.open(dataFilename);
	if (!ifs.is_open())
		return false;

	// store entire file in content
	std::string content((istreambuf_iterator<char>(ifs)),
		(istreambuf_iterator<char>()));

	sregex_iterator rIterBegin = sregex_iterator(content.begin(), content.end(), rex);
	sregex_iterator rIterEnd = sregex_iterator();

	// if there were no matches, return false
	if (distance(rIterBegin, rIterEnd) == 0)
		return false;

	for (sregex_iterator i = rIterBegin; i != rIterEnd; ++i)
	{
		store.push_back((*i).str());
	}

	return true;
}

#endif // _XML_REGEX_IO_H