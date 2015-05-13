/*
Lab 3 - Threading
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This header file contains the NodeList implementation for this lab. This
class is effectively a wrapper of the stl vector.
*/

#ifndef _NODE_LIST_H
#define _NODE_LIST_H

#include "XmlNode.h"
#include <vector>
using namespace std;

class NodeList
{
private:
	vector<XmlNode*> nodeList;
public:
	// constructors and destructor
	NodeList() {}
	~NodeList() {}
	// wrapped methods
	int size() const { return nodeList.size(); }
	XmlNode *& operator[](unsigned int index) { return nodeList[index]; }
	void push_back(XmlNode *&xmlNode) { nodeList.push_back(xmlNode); }
	void pop_back() { nodeList.pop_back(); }
};

#endif // _NODE_LIST_H