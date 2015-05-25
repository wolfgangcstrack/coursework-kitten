/*
Lab 4 - Graphs and Lambda Expressions
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This header file has the class definitions for the XML nodes arbitrarily
chosen for this lab.
*/

#ifndef _XML_NODE_H
#define _XML_NODE_H

#include <regex>
#include <string>
#include <vector>
using namespace std;

typedef unsigned short ushort;
typedef unsigned long ulong;

class XmlNode
{
protected:
	string className;
	string xmlTags;

	long get_ulong(const string &data, const string &tagName) 
	{
		return get_ulong(data, regex("<" + tagName + ">[0-9]*"));
	}
	long get_ulong(const string &data, regex rx)
	{
		auto match = sregex_iterator(data.begin(), data.end(), rx);
		string temp = match->str();
		return stol((sregex_iterator(temp.begin(), temp.end(), regex("[0-9]+"))->str()));
	}

	string getString(const string &data, const string &tagName)
	{
		return getString(data, regex("<" + tagName + ">.*?<" + tagName + ">"));
	}
	string getString(const string &data, regex rx)
	{
		auto match = sregex_iterator(data.begin(), data.end(), rx);
		string temp = match->str();
		string pTemp = "";
		for (int i = temp.find('>') + 1; i < temp.length(); i++)
		{
			if (temp[i] == '<')
				break;
			pTemp += temp[i];
		}

		return pTemp;
	}

	bool getBoolean(const string &data, regex rx)
	{
		auto match = sregex_iterator(data.begin(), data.end(), rx);
		string temp = match->str();
		return (temp.find("true") > -1 ? true : false);
	}
public:
	// constructors and destructor
	XmlNode() {}
	XmlNode(const string &tags) { xmlTags = tags; }
	virtual ~XmlNode() {}
	// getter
	const string & getXMLTags() const { return xmlTags; }
	const string & getClassName() const { return className; }
	// setter
	void setXMLTags(const string &newTags) { xmlTags = newTags; }
	// other methods
	virtual void readData(const string &data) = 0;
};

#endif // _XML_NODE_H