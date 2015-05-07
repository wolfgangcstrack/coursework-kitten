/*
Lab 2 - Regular Expressions
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This is the header file for the XmlNode class, the wrapper for the data
used in this lab. This class is then put in a LinkedNode when stored in a
LinkedList.
*/

#ifndef XML_NODE_H_
#define XML_NODE_H_

#include "LinkedList_OLD.h"
#include <string>
#include <vector>

class XmlNode
{
private:
	struct XmlNodeData;

	std::string className;
	std::vector<XmlNodeData> data;
	LinkedList<XmlNode> children;
public:
	// constructors and destructor
	XmlNode() {}
	XmlNode(const XmlNode &xmlNode);
	XmlNode(const std::string &name) { className = name; }
	~XmlNode() {}
	// getters
	const std::string & getClassName() const { return className; }
	const std::vector<XmlNodeData> & getAllData() const { return data; }
	const LinkedList<XmlNode> & getAllChildNodes() const { return children; }
	// setters
	void setClassName(const std::string &name) { className = name; }
	// other methods
	bool addData(const std::string name, const std::string type, const std::string value);
	bool addChildNode(const XmlNode &xmlNode);
	// operator overloads
	XmlNode & operator=(const XmlNode &right);
};

// private struct XmlNodeData in XmlNode
// used as a wrapper for data
struct XmlNode::XmlNodeData
{
	std::string _name;
	std::string _type;
	std::string _value;
	
	XmlNodeData(const std::string name, const std::string type, const std::string value)
	{
		_name = name; _type = type; _value = value;
	}

	XmlNodeData(const XmlNodeData &toCopy) { *this = toCopy; }

	XmlNodeData & operator=(const XmlNodeData &right)
	{
		_name = right._name;
		_type = right._type;
		_value = right._value;
	}
};

bool XmlNode::addData(const std::string name, const std::string type, const std::string value)
{
	data.push_back(XmlNodeData(name, type, value));
}

bool XmlNode::addChildNode(const XmlNode &xmlNode)
{
	children.push_back(xmlNode);
}

XmlNode & XmlNode::operator=(const XmlNode &right)
{
	className = right.className;
	data = right.data;
	children = right.children;
}

#endif // XML_NODE_H_