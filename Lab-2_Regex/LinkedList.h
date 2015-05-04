/*
Lab 2 - Regular Expressions
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This is the header file for the LinkedList class. It will be the container
that mainly holds XML nodes in this project and is a circular linked list.
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

template<class T>
LinkedList::LinkedList(const LinkedList<T> &list)
{
	/*
	listSize = list.listSize;

	headPtr = new LinkedNode<T>(*(list.headPtr)); // copy headPtr
	std::unique_ptr<LinkedNode<T>> nodePtr = list.headPtr->getNext();

	while ()
	*/
}

#endif // LINKED_LIST_H_