/*
Lab 2 - Regular Expressions
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This is the header file for the LinkedList class. It will be the container
that mainly holds XML nodes in this project.
*/

#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include "List.h"
#include "LinkedNode.h"

template<class T>
class LinkedList : public List
{
private:
	std::unique_ptr<LinkedNode<T>> headPtr;

	std::unique_ptr<LinkedNode<T>> getNodeAt(int position) const;
public:
	// constructors and destructor
	LinkedList() : List() { headPtr = 0; }
	LinkedList(const LinkedList<T> &list);
	~LinkedList() { clear(); }
	// overridden methods from List class
	bool insert(const T &newEntry, int position = 1);
	bool remove(int position);
	// other methods
	void push_front(const T &newEntry);
	void push_back(const T &newEntry);
	void pop_front();
	void pop_back();
	void clear();
};

#endif // LINKED_LIST_H_