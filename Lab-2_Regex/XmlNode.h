/*
Lab 2 - Regular Expressions
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This is the header file for the XmlNode class, the wrapper for the data
used in this lab. This class is then wrapped in a LinkedNode when stored
in a LinkedList.
*/

#ifndef XML_NODE_H_
#define XML_NODE_H_

#include "LinkedList.h"
#include <string>

class XmlNodeData
{
private:
	std::string _name;
	std::string _type;
	std::string _value;

	friend class XmlNode;
public:
	XmlNodeData(std::string name, std::string type, std::string value)
	{
		_name = name; _type = type; _value = value;
	}
};

class XmlNode
{
private:

	std::string className;
	LinkedList<XmlNodeData> data;
	LinkedList<XmlNode> children;
public:
	// constructors and destructor
	XmlNode();
	XmlNode(std::string name);
	XmlNode(const XmlNode & xmlNode);
	~XmlNode();
	// getters
	const std::string & getClassName() const { return className; }
	const LinkedList<XmlNodeData> & getAllData() const { return data; }
	const LinkedList<XmlNode> getAllChildNodes() const { return children; }
	// setters
	void setClassName(std::string name) { className = name; }
};

#endif // XML_NODE_H_