/*
Lab 6 - STL Containers and Algorithms
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This header file contains the XmlNodeList implementation for this lab.
This class is essentially a wrapper of the stl vector.
*/

#ifndef _XML_NODE_LIST_H
#define _XML_NODE_LIST_H

#include "XmlNode.h"
#include <vector>
#include <memory>

class XmlNodeList
{
private:
	std::vector<std::shared_ptr<XmlNode>> nodeList;
public:
	// constructors and destructor
	XmlNodeList() {}
	~XmlNodeList() {}
	// wrapped methods
	int size() const { return nodeList.size(); }
	bool empty() const { return nodeList.empty(); }
	std::shared_ptr<XmlNode> operator[](unsigned int index) const { return nodeList[index]; }
	std::shared_ptr<XmlNode> front() const { return nodeList[0]; }
	void push_front(std::shared_ptr<XmlNode> &xmlNode) { nodeList.insert(nodeList.begin(), xmlNode); }
	void push_back(std::shared_ptr<XmlNode> &xmlNode) { nodeList.push_back(xmlNode); }
	void pop_front() { nodeList.erase(nodeList.begin()); }
	void pop_back() { nodeList.pop_back(); }
};

#endif // _XML_NODE_LIST_H