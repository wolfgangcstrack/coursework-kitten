/*
Lab 2 - Regular Expressions
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This is the header file for the abstract List class. It will serve as the
base class for XmlNodeList and LinkedList.
*/

#ifndef LINKED_NODE_H_
#define LINKED_NODE_H_

#include <memory>

template<class T>
class LinkedNode
{
private:
	std::unique_ptr<T> data;
	std::unique_ptr<LinkedNode<T>> next;
public:
	// constructors and destructor
	LinkedNode() { *data = 0; next = 0; }
	LinkedNode(const T &pData) { *data = pData; next = 0; }
	// getters
	const T & getData() const { return (*data); }
	std::unique_ptr<LinkedNode<T>> getNext() const { return next; }
	// setters
	void setData(const T &pData) { *data = pData; }
	void setNext(std::unique_ptr<LinkedNode<T>> newNext) { next = newNext; }
};

#endif // LINKED_NODE_H_