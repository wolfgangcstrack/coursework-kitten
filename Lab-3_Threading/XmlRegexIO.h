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
	bool getXmlData(const string &dataFilename, XmlNode &store);
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

bool XmlRegexIO::getXmlData(const string &dataFilename, XmlNode &store)
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

#endif // _XML_REGEX_IO_H