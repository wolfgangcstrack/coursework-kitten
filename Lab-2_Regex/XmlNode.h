/*
Lab 2 - Regular Expressions
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This header file has the class definitions for the XML nodes arbitrarily
chosen for this lab.
*/

#ifndef _XML_NODE_H
#define _XML_NODE_H

#include <string>
#include <vector>
using namespace std;

class XmlNode
{
protected:
	vector<string> xmlTags;
public:
	XmlNode() {}
	const vector<string> & getXMLTags() const { return xmlTags; }
	virtual ~XmlNode() {}
};

#endif // _XML_NODE_H