/*
Lab 6 - STL Containers and Algorithms
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This header file contains the utility class for extracting XML nodes and
XML node data from given files. The methods store the build XML node in a
parameter and return booleans.
*/

#ifndef _XML_REGEX_IO_H
#define _XML_REGEX_IO_H

#include "XmlNode.h"
#include <fstream>
#include <string>
#include <vector>
#include <regex>

class XmlRegexIO
{
private:
	std::string pattern;
	std::regex rex;
public:
	// constructors and destructor
	XmlRegexIO() {}
	XmlRegexIO(const std::string &patt) { pattern = patt; rex = std::regex(pattern); }
	~XmlRegexIO() {}
	// getters
	const std::string & getPattern() { return pattern; }
	const std::regex & getRegex() { return rex; }
	// setters
	void setPattern(const std::string &patt) { pattern = patt; rex = std::regex(pattern); }
	// other methods
	virtual bool getXmlTags(const std::string &filename, XmlNode &store);
	virtual bool getXmlDataFromFile(const std::string &dataFilename, XmlNode &store);
	virtual bool getXmlDataFromString(const std::string &data, XmlNode &store);
	virtual bool getAllMatches(const std::string &dataFilename, std::vector<std::string> &store);
};

bool XmlRegexIO::getXmlTags(const std::string &filename, XmlNode &store)
{
	// check if file exists/can be read from
	std::ifstream ifs;
	ifs.open(filename);
	if (!ifs.is_open())
		return false;

	// store entire file in content
	std::string content((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));

	if (!std::regex_search(content, rex)) // check if pattern returns true
		return false;

	int positionOfOpeningTag = content.find("<element name=\"" + store.getClassName());
	if (positionOfOpeningTag < 0) // validate std::string position
		return false;

	int lengthTillClosingTag;
	for (int i = positionOfOpeningTag; i < content.length(); i++)
	{
		if (content[i] == '<') // find closing tag of element
		{
			if (regex_match(content.substr(i, 10), std::regex("</element>")))
			{
				lengthTillClosingTag = (i + 10) - positionOfOpeningTag;
				store.setXMLTags(content.substr(positionOfOpeningTag, lengthTillClosingTag));
				break; // out of loop
			}
		}
	}

	return true;
}

bool XmlRegexIO::getXmlDataFromFile(const std::string &dataFilename, XmlNode &store)
{
	// check if file exists/can be read from
	std::ifstream ifs;
	ifs.open(dataFilename);
	if (!ifs.is_open())
		return false;

	// store entire file in content
	std::string content((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));

	if (!std::regex_search(content, rex)) // check if pattern returns true
		return false;

	int positionOfOpeningTag = content.find("<" + store.getClassName());
	if (positionOfOpeningTag < 0) // validate std::string position
		return false;

	int lengthTillClosingTag;
	for (int i = positionOfOpeningTag; i < content.length(); i++)
	{
		if (content[i] == '<') // find closing tag of element
		{
			if (std::regex_search(content.substr(i, pattern.length()), std::regex("</" + store.getClassName() + ">")))
			{
				lengthTillClosingTag = (i + store.getClassName().length() + 3) - positionOfOpeningTag;
				store.readData(content.substr(positionOfOpeningTag, lengthTillClosingTag));
				break; // out of loop
			}
		}
	}

	return true;
}

bool XmlRegexIO::getXmlDataFromString(const std::string &data, XmlNode &store)
{
	if (!std::regex_search(data, rex)) // check if pattern returns true
		return false;

	int positionOfOpeningTag = data.find("<" + store.getClassName());
	if (positionOfOpeningTag < 0) // validate std::string position
		return false;

	int lengthTillClosingTag;
	store.readData(data);

	return true;
}

bool XmlRegexIO::getAllMatches(const std::string &dataFilename, std::vector<std::string> &store)
{
	// check if file exists/can be read from
	std::ifstream ifs;
	ifs.open(dataFilename);
	if (!ifs.is_open())
		return false;

	// store entire file in content
	std::string content((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));

	std::sregex_iterator rIterBegin = std::sregex_iterator(content.begin(), content.end(), rex);
	std::sregex_iterator rIterEnd = std::sregex_iterator();

	// if there were no matches, return false
	if (std::distance(rIterBegin, rIterEnd) == 0)
		return false;

	for (std::sregex_iterator i = rIterBegin; i != rIterEnd; ++i)
	{
		store.push_back((*i).str());
	}

	return true;
}

#endif // _XML_REGEX_IO_H