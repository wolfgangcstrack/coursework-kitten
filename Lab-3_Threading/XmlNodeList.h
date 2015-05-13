/*
Lab 3 - Threading
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This header file contains the XmlNodeList implementation for this lab.
This class is essentially a wrapper of the stl vector.
*/

#ifndef _XML_NODE_LIST_H
#define _XML_NODE_LIST_H

#include "XmlNode.h"
#include <vector>
using namespace std;

class XmlNodeList
{
private:
	vector<XmlNode*> nodeList;
public:
	// constructors and destructor
	XmlNodeList() {}
	~XmlNodeList() {}
	// wrapped methods
	int size() const { return nodeList.size(); }
	XmlNode *& operator[](unsigned int index) { return nodeList[index]; }
	void push_back(XmlNode *&xmlNode) { nodeList.push_back(xmlNode); }
	void pop_back() { nodeList.pop_back(); }
};

#endif // _XML_NODE_LIST_H