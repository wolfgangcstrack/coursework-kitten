/*
Lab 2 - Regular Expressions
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This is the header file for the XmlRegexIO class. This class extends the
RegexIO class and can instantiate XmlNodes.
*/

#ifndef XML_REGEX_IO_H_
#define XML_REGEX_IO_H_

#include "RegexIO.h"

class XmlRegexIO : public RegexIO
{
public:
	// constructors and destructor
	XmlRegexIO();
	XmlRegexIO(const XmlRegexIO &rIO);
	XmlRegexIO(const std::string &patt);
	~XmlRegexIO();
	// other methods
	bool getXmlNode(std::string filename, std::string className);
};

#endif // XML_REGEX_IO_H_