/*
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This header file has the class definitions for the XML nodes arbitrarily
chosen for this lab.
*/

#ifndef _XML_NODE_H
#define _XML_NODE_H

#include <string>
#include <vector>
#include <regex>

class XmlNode
{
protected:
	typedef unsigned short ushort;
	typedef unsigned long ulong;

	std::string className;
	std::string xmlTags;

	// private helper methods that XmlRegexIO uses for parsing
	long get_ulong(const std::string &data, const std::string &tagName);
	long get_ulong(const std::string &data, std::regex rx);
	std::string getString(const std::string &data, const std::string &tagName);
	std::string getString(const std::string &data, std::regex rx);
	bool getBoolean(const std::string &data, std::regex rx);
public:
	// constructors and destructor
	XmlNode() {}
	XmlNode(const std::string &tags) { xmlTags = tags; }
	virtual ~XmlNode() {}
	// getter
	const std::string & getXMLTags() const   { return xmlTags; }
	const std::string & getClassName() const { return className; }
	// setter
	void setXMLTags(const std::string &newTags) { xmlTags = newTags; }
	// other methods
	virtual void readData(const std::string &data) = 0;
};

long XmlNode::get_ulong(const std::string &data, const std::string &tagName)
{
	return get_ulong(data, std::regex("<" + tagName + ">[0-9]*"));
}

long XmlNode::get_ulong(const std::string &data, std::regex rx)
{
	auto match = std::sregex_iterator(data.begin(), data.end(), rx);
	std::string temp = match->str();
	return stol((std::sregex_iterator(temp.begin(), temp.end(), std::regex("[0-9]+"))->str()));
}

std::string XmlNode::getString(const std::string &data, const std::string &tagName)
{
	return getString(data, std::regex("<" + tagName + ">.*?</" + tagName + ">"));
}

std::string XmlNode::getString(const std::string &data, std::regex rx)
{
	auto match = std::sregex_iterator(data.begin(), data.end(), rx);
	std::string temp = match->str();
	std::string pTemp = "";
	for (int i = temp.find('>') + 1; i < temp.length(); i++)
	{
		if (temp[i] == '<')
			break;
		pTemp += temp[i];
	}

	return pTemp;
}

bool XmlNode::getBoolean(const std::string &data, std::regex rx)
{
	auto match = std::sregex_iterator(data.begin(), data.end(), rx);
	std::string temp = match->str();
	return (temp.find("true") > -1 ? true : false);
}

#endif // _XML_NODE_H