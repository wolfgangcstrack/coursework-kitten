/*
Lab 2 - Regular Expressions
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This is the header file for the LinkedList class. It will be the container
that mainly holds XML nodes in this project.
*/

#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include "List_OLD.h"
#include "LinkedNode_OLD.h"

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
	void push_front(const T &newEntry) { this.insert(newEntry, 1); }
	void push_back(const T &newEntry) { this.insert(newEntry, listSize + 1); }
	void pop_front() { this.remove(1); }
	void pop_back() { this.remove(listSize); }
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
		while (origChainPtr != 0)
		{
			std::unique_ptr<LinkedNode<T>> newNodePtr = new LinkedNode<T>(origChainPtr->getData());
			newChainPtr->setNext(newNodePtr);
			newChainPtr = newChainPtr->getNext();
			origChainPtr = origChainPtr->getNext();
		}
	}
}

template<class T>
const T & LinkedList<T>::getItemAt(int position)
{
	return getNodeAt(position)->getData();
}

template<class T>
bool LinkedList<T>::insert(const T &newEntry, int position = 1)
{
	// check if position is valid
	if (position < 1 || position > listSize + 1)
		return false;

	// create new node for new entry
	std::unique_ptr<LinkedNode<T>> newNodePtr = new LinkedNode<T>(newEntry);
	if (newPosition == 1) // insert at head
	{
		newNodePtr->setNext(headPtr);
		headPtr = newNodePtr;
	}
	else // insert at middle or at end of list
	{
		std::unique_ptr<LinkedNode<T>> prevPtr = getNodeAt(position - 1);
		newNodePtr->setNext(prevPtr->getNext());
		prevPtr->setNext(newNodePtr);
	}
	listSize++;

	return true;
}

template<class T>
bool LinkedList<T>::remove(int position)
{
	// check if position is valid
	if (position < 1 || position > listSize)
		return false;

	std::unique_ptr<LinkedNode<T>> deletePtr = 0;
	if (position == 1) // remove head node
	{
		deletePtr = headPtr;
		headPtr = headPtr->getNext();
	}
	else // remove node in middle or at end of list
	{
		std::unique_ptr<LinkedNode<T>> prevPtr = getNodeAt(position - 1);
		deletePtr = prevPtr->getNext();
		prevPtr->setNext(deletePtr->getNext());
	}

	delete deletePtr;
	listSize--;

	return true;
}

template<class T>
void LinkedList<T>::clear()
{
	std::unique_ptr<LinkedNode<T>> deletePtr;

	for (int i = 0; i < listSize; i++)
	{
		deletePtr = headPtr;
		headPtr = headPtr->getNext();
		delete deletePtr;
	}

	itemCount = 0;
}

// private member function getNodeAt
template<class T>
std::unique_ptr<LinkedNode<T>> LinkedList<T>::getNodeAt(int position) const
{
	std::unique_ptr<LinkedNode<T>> resultPtr = headPtr;

	for (int i = 1; i < position; i++) // iterate until node at position is reached
		resultPtr = resultPtr->getNext();

	return resultPtr;
}
#endif // LINKED_LIST_H_