/*
Manager: Wolfgang C. Strack

This file includes the interace and implementation for:
- SAList class
*/

#pragma once

#include "Global.h"
#include "DoublyLinkedList.h"

// ---------------------- SAList Class Interface --------------------------------------------------
/* Modifications from List class:
- changed all functions to work with DoublyLinkedList
- insertions are only performed at the front of the list
- added adjust(int) - adjusts List so that nodes with greatest accessTimes are near the front
*/

template<class ItemType>
class SAList : public DoublyLinkedList<ItemType>  // derived from abstract DoublyLinkedList class
{
private:
	const int ACCESS_REQ = 5; // for determining if adjust() is needed
	// adjust will only be called every ACCESS_REQ times an element is adjusted

	// Finds node at a specified position
	Node<ItemType>* getNodeAt(int position);
public:
	// Adds node at FRONT of list
	bool insert(const ItemType & newEntry, int position = 1);
	// Removes node at a specified position
	bool remove(int position);
	// Passes back node at a specified position
	bool getEntry(int position, ItemType & anEntry);

	// adjusts node based on how many times it was accessed
	void adjust(int adjPosition);

	void write(ostream& os);
};
// ---------------------- SAList Class Interface End ----------------------------------------------

// ---------------------- SAList Class Implementation -----------------------------------------------
template<class ItemType>
bool SAList<ItemType>::insert(const ItemType & newEntry, int position = 1)
{
	// since insertion will always be performed at the front (fixed position parameter),
	// insert only returns true; "false" situation depends on HashTable load factor

	// create new node for newEntry
	Node<ItemType>* newNodePtr;
	newNodePtr = new Node<ItemType>(newEntry);
	if (itemCount == 0) // insert into empty list
	{
		headPtr->setNext(newNodePtr);		// double-link headPtr and newNodePtr
		newNodePtr->setPrev(headPtr);
		newNodePtr->setNext(tailPtr);		// double-link tailPtr and newNodePtr
		tailPtr->setPrev(newNodePtr);
	}
	else
	{
		Node<ItemType>* newNextPtr = headPtr->getNext();

		newNodePtr->setNext(newNextPtr);	// double-link newNextPtr and newNodePtr
		newNextPtr->setPrev(newNodePtr);
		headPtr->setNext(newNodePtr);		// double-link headPtr and newNodePtr
		newNodePtr->setPrev(headPtr);
	}
	itemCount++;

	return true;
}

template<class ItemType>
bool SAList<ItemType>::remove(int position)
{
	if (position < 1 || position > itemCount)		// validate position
		return false;

	Node<ItemType>* deletePtr = getNodeAt(position);

	Node<ItemType>* prevPtr = deletePtr->getPrev();
	Node<ItemType>* nextPtr = deletePtr->getNext();

	prevPtr->setNext(nextPtr);						// double-link deletePtr's previous and next nodes together
	nextPtr->setPrev(prevPtr);

	delete deletePtr;
	itemCount--;

	return true;
}

template<class ItemType>
bool SAList<ItemType>::getEntry(int position, ItemType & anEntry)
{
	if (position < 1 || position > itemCount)		// validate position
		return false;

	Node<ItemType>* copyPtr = getNodeAt(position);	// get to position
	anEntry = copyPtr->getItem();

	return true;
}

template<class ItemType>
Node<ItemType>* SAList<ItemType>::getNodeAt(int position)
{
	Node<ItemType>* curPtr;

	if (position <= itemCount / 2)					// node is in first half of list
	{												// start traversal from headPtr
		curPtr = headPtr->getNext();
		for (int i = 1; i < position; i++)
			curPtr = curPtr->getNext();
	}
	else											// node is in second half of list
	{												// start traversal from tailPtr
		curPtr = tailPtr->getPrev();
		for (int i = itemCount; i > position; i--)
			curPtr = curPtr->getPrev();
	}

	return curPtr;
}

template<class ItemType>
void SAList<ItemType>::adjust(int adjPosition)			// uses a variant of the counting method of node adjustment
{
	Node<ItemType>* adjustPtr = getNodeAt(adjPosition);	// save access times for multiple comparisons
	adjustPtr->incrementAccessTimes();
	int accessTimes = adjustPtr->getAccessTimes();

	// adjust only after entry is accessed ACCESS_REQ more times
	if (accessTimes % ACCESS_REQ != 0 && accessTimes != 0)
		return;

	int moves = 0;
	Node<ItemType>* newPrevPtr = 0;	// previous pointer for adjustPtr's new position IF new position is further up
	Node<ItemType>* newNextPtr = 0;	// next pointer for adjustPtr's new position IF new position is further down

	// find newPrevPtr or newNextPtr by comparing access times
	if (accessTimes > newPrevPtr->getAccessTimes() && newPrevPtr != headPtr)
	{
		newPrevPtr = adjustPtr->getPrev();
		while (accessTimes > newPrevPtr->getAccessTimes() && newPrevPtr != headPtr)
		{
			newPrevPtr = newPrevPtr->getPrev();
			moves++;
		}
	}
	else if (accessTimes < newNextPtr->getAccessTimes() && newNextPtr != tailPtr)
	{
		newNextPtr = adjustPtr->getNext();
		while (accessTimes < newNextPtr->getAccessTimes() && newNextPtr != tailPtr)
		{
			newNextPtr = newNextPtr->getNext();
			moves++;
		}
	}

	if (moves == 0) // if adjustPtr does not need to be adjusted
		return;		// do nothing
	else
	{
		Node<ItemType>* prevPtr = adjustPtr->getPrev();
		Node<ItemType>* nextPtr = adjustPtr->getNext();

		prevPtr->setNext(nextPtr);			// double-link adjustPtr's old previous/next pointers
		nextPtr->setPrev(prevPtr);

		newPrevPtr->setNext(adjustPtr);		// double-link adjustPtr with its new previous pointer
		adjustPtr->setPrev(newPrevPtr);
		adjustPtr->setNext(newNextPtr);		// double-link adjustPtr with its new next pointer
		newNextPtr->setPrev(adjustPtr);
	}
}

template <class ItemType>
void SAList<ItemType>::write(ostream& os)
{
	Node<ItemType>* currPtr = headPtr->getNext();
	while (currPtr != tailPtr)
	{
		currPtr->getItem()->output(os);			// display data
		currPtr = currPtr->getNext();			// go to next node
	}
}
// ---------------------- SAList Class Implementation End -------------------------------------------