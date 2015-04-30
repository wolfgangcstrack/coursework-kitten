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

#include <string>
#include <vector>

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
	std::vector<XmlNodeData> data;
	std::vector<XmlNode> children;
public:
	// constructors and destructor
	XmlNode();
	XmlNode(std::string name);
	XmlNode(const XmlNode & xmlNode);
	~XmlNode();
	// getters
	const std::string & getClassName() const { return className; }
	const std::vector<XmlNodeData> & getAllData() const { return data; }
	const std::vector<XmlNode> getAllChildNodes() const { return children; }
	// setters
	void setClassName(std::string name) { className = name; }
};

#endif // XML_NODE_H_