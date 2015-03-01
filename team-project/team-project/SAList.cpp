/*
Manager: Wolfgang C. Strack

This file includes the implementation for:
LinkedList class
SAList class
*/

#include "Global.h"

// ---------------------- LinkedList Class Implementation -----------------------------------------
template<class ItemType>
LinkedList<ItemType>::LinkedList(const LinkedList<ItemType>& aList)
{
	itemCount = aList.itemCount;
	Node<ItemType>* origChainPtr = aList.headPtr;  // Points to nodes in original list

	if (origChainPtr == 0)
		headPtr = 0;  // Original list is empty
	else
	{
		headPtr = new Node<ItemType>();		// copy first node
		headPtr->setItem(origChainPtr->getItem());

		// Copy remaining nodes
		Node<ItemType>* newChainPtr = headPtr;
		origChainPtr = origChainPtr->getNext();
		while (origChainPtr->getNext() != headPtr)
		{
			ItemType nextItem = origChainPtr->getItem();
			Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);
			newChainPtr->setNext(newNodePtr);
			newChainPtr = newChainPtr->getNext();
			origChainPtr = origChainPtr->getNext();
		}
	}
}


template<class ItemType>
void LinkedList<ItemType>::display() const
{
	Node<ItemType>* currPtr = headPtr;		// start at front of list
	while (currPtr != 0)					// walk until end of list
	{
		cout << currPtr->getItem() << " ";	// display data
		currPtr = currPtr->getNext();		// go to next node
	}
	cout << endl << endl;
}


template<class ItemType>
void LinkedList<ItemType>::clear()
{
	Node<ItemType> * deletePtr;
	for (int i = 0; i < itemCount; i++) // walk each node
	{
		deletePtr = headPtr;			// remove each node
		headPtr = headPtr->getNext();
		delete deletePtr;
	}
	itemCount = 0;
}
// ---------------------- LinkedList Class Implementation End -------------------------------------

// ---------------------- SAList Class Implementation -----------------------------------------------
template<class ItemType>
bool SASAList<ItemType>::insert(const ItemType& newEntry, int newPosition)
{
	// check valid position
	if (newPosition < 1 || newPosition > itemCount + 1)
		return false;

	// create new node for newEntry
	Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);
	if (newPosition == 1)   // insert new node at beginning 
	{
		newNodePtr->setNext(headPtr);
		headPtr = newNodePtr;
	}
	else  // insert new node in middle or end of SAList
	{
		Node<ItemType>* prevPtr = getNodeAt(newPosition - 1);  // go to position
		newNodePtr->setNext(prevPtr->getNext());
		prevPtr->setNext(newNodePtr);
	}
	itemCount++;
	return true;
}


template<class ItemType>
bool SAList<ItemType>::remove(int position)
{
	// check for valid position
	if (position < 1 || position > itemCount)
		return false;

	Node<ItemType>* deletePtr = 0;
	if (position == 1)   // remove first node 
	{
		deletePtr = headPtr;
		headPtr = headPtr->getNext();
	}
	else   // remove from middle or end of SAList
	{
		Node<ItemType>* prevPtr = getNodeAt(position - 1); // get to position
		deletePtr = prevPtr->getNext();		// remove from SAList
		prevPtr->setNext(deletePtr->getNext());
	}
	delete deletePtr;
	itemCount--;
	return true;
}

template<class ItemType>
bool SAList<ItemType>::getEntry(int position, ItemType & anEntry) const
{
	if (position < 1 || position > itemCount)
		return false;

	Node<ItemType>* copyPtr = getNodeAt(position); // get to position
	anEntry = copyPtr->getItem();
	return true;
}


template<class ItemType>
Node<ItemType>* SAList<ItemType>::getNodeAt(int position) const
{
	Node<ItemType>* curPtr = headPtr;
	for (int i = 1; i < position; i++)
		curPtr = curPtr->getNext();
	return curPtr;
}
// ---------------------- SAList Class Implementation End -------------------------------------------