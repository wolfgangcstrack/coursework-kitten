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
class LinkedList : public List<T>
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
	const T & getItemAt(int position) const;
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
LinkedList<T>::LinkedList(const LinkedList<T> &list)
{
	listSize = list.listSize;
	std::unique_ptr<LinkedNode<T>> origChainPtr = list.headPtr;

	if (origChainPtr == 0) // copy empty list
		headPtr = 0;
	else
	{
		// copy first node
		headPtr = new LinkedNode<T>();
		headPtr->setData(origChainPtr->getData());

		// copy the remaining nodes
		std::unique_ptr<LinkedNode<T>> newChainPtr = headPtr;
		origChainPtr = origChainPtr->getNext();
		while (origChainPtr != list.headPtr)
		{
			std::unique_ptr<LinkedNode<T>> newNodePtr = new LinkedNode<T>(origChainPtr->getData());
			newChainPtr->setNext(newNodePtr);
			newChainPtr = newChainPtr->getNext();
			origChainPtr = origChainPtr->getNext();
		}

		// set the last node's next pointer to head (circular list implementation)
		newChainPtr->setNext(headPtr);
	}
}

template<class T>
const T & LinkedList<T>::getItemAt(int position)
{
	return getNodeAt(position)->getData();
}

template<class T>
std::unique_ptr<LinkedNode<T>> LinkedList<T>::getNodeAt(int position) const
{
	std::unique_ptr<LinkedNode<T>> resultPtr = headPtr;

	for (int i = 1; i < position; i++) // iterate until node at position is reached
		resultPtr = resultPtr->getNext();

	return resultPtr;
}
#endif // LINKED_LIST_H_