/*
Manager: Wolfgang C. Strack

This file includes the implementation for:
DoublyLinkedList class
SAList class
*/

#include "Global.h"

// ---------------------- DoublyLinkedList Class Implementation -----------------------------------
template<class ItemType>
DoublyLinkedList<ItemType>::DoublyLinkedList()
{
	itemCount = 0;
	headPtr = new Node<ItemType>();
	tailPtr = new Node<ItemType>();
	headPtr.setNext(tailPtr);
	tailPtr.setPrev(headPtr);
}

template<class ItemType>
DoublyLinkedList<ItemType>::DoublyLinkedList(const DoublyLinkedList<ItemType>& aList)
{
	itemCount = aList.itemCount;
	Node<ItemType>  *origChainPtr;

	origChainPtr = aList.headPtr;

	headPtr = new Node<ItemType>();		// copy dummy head node

	// Copy remaining nodes BEFORE tailPtr
	Node<ItemType>* newChainPtr = headPtr; // ignore data
	origChainPtr = origChainPtr->getNext();
	while (origChainPtr != aList.tailPtr)
	{
		ItemType *nextItem = origChainPtr->getItem();
		Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);
		newChainPtr->setNext(newNodePtr); // link prev to current
		newNodePtr->setPrev(newChainPtr); // link current to prev

		newChainPtr = newChainPtr->getNext();
		origChainPtr = origChainPtr->getNext();
	}
	// Create tail and init. prev
	tailPtr = new Node<ItemType>();
	tailPtr.setPrev(newChainPtr);
	newChainPtr->setNext(tailPtr);
}



template<class ItemType>
void DoublyLinkedList<ItemType>::display() const
{
	Node<ItemType>* currPtr = headPtr->getNext();
	while (currPtr != tailPtr)
	{
		cout << *(currPtr->getItem()) << " ";	// display data
		currPtr = currPtr->getNext();			// go to next node
	}
	cout << endl << endl;
}


template<class ItemType>
void DoublyLinkedList<ItemType>::clear()
{
	Node<ItemType> * deletePtr, *nodePtr;

	deletePtr = headPtr->getNext();
	for (int i = 0; i < itemCount; i++) // walk each node
	{
		nodePtr = deletePtr->getNext();
		delete deletePtr;
		deletePtr = nodePtr;
	}
	itemCount = 0;
}
// ---------------------- DoublyLinkedList Class Implementation End -------------------------------

// ---------------------- SAList Class Implementation -----------------------------------------------
/* Modifications from List class
changed ALL functions to work with DoublyLinkedList
insert() - inserts ONLY to front
added adjust() - adjusts List so that nodes with greatest accessTimes are near the front
*/
template<class ItemType>
bool SAList<ItemType>::insert(const ItemType& newEntry)
{
	// create new node for newEntry
	Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);
	if (itemCount < MAX_LENGTH)   // check if list can insert another value
	{
		if (itemCount == 0) // insert into empty list
		{
			headPtr->setNext(newNodePtr);
			newNodePtr->setPrev(headPtr);
			newNodePtr->setNext(tailPtr);
			tailPtr->setPrev(newNodePtr);
		}
		else
		{
			Node<ItemType>* prevFirstPtr = headPtr->getNext();

			newNodePtr->setNext(prevFirstPtr);
			prevFirstPtr->setPrev(newNodePtr);
			headPtr->setNext(newNodePtr);
			newNodePtr->setPrev(headPtr);
		}

		itemCount++;
		return true;
	}
	else
	{
		// ADD
		// HASH
		// TABLE
		// FUNCTIONALITY
		// HERE
		return false;
	}
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
		deletePtr = headPtr->getNext();
		headPtr->setNext(tailPtr);
		tailPtr->setPrev(headPtr);
	}
	else   // remove from middle or end of SAList
	{
		deletePtr = getNodeAt(position);
		Node<ItemType>* prevPtr = deletePtr->getPrev();
		Node<ItemType>* nextPtr = deletePtr->getNext();

		prevPtr->setNext(nextPtr);
		nextPtr->setPrev(prevPtr);
	}

	delete deletePtr;
	itemCount--;
	return true;
}

template<class ItemType>
bool SAList<ItemType>::getEntry(int position, ItemType * anEntry) const
{
	if (position < 1 || position > itemCount) // validate position
		return false;

	Node<ItemType>* copyPtr = getNodeAt(position); // get to position
	anEntry = copyPtr->getItem();
	return true;
}


template<class ItemType>
Node<ItemType>* SAList<ItemType>::getNodeAt(int position) const
{
	Node<ItemType>* curPtr;
	
	if (position <= itemCount/2) // node is in first half of list
	{
		curPtr = headPtr->getNext();
		for (int i = 1; i < position; i++)
			curPtr = curPtr->getNext();
	}
	else // node is in second half of list
	{
		curPtr = tailPtr->getPrev();
		for (int i = itemCount; i > position; i--)
			curPtr = curPtr->getPrev();
	}
	
	curPtr->incrementAccessTimes();
	adjust(curPtr);
	return curPtr;
}

template<class ItemType>
void SAList<ItemType>::adjust(Node<ItemType>* adjustPtr)
{
	int moves = 0;
	int accessTimes = adjustPtr->getAccessTimes();		// save access times for multiple comparisons
	Node<ItemType>* newPrevPtr = adjustPtr->getPrev();	// previous pointer for adjustPtr's new position

	// find newPrevPtr by comparing access times
	while (accessTimes > newPrevPtr->getAccessTimes() && newPrevPtr != headPtr)
	{
		newPrevPtr = newPrevPtr->getPrev();
		moves++;
	}

	if (moves == 0) // if adjustPtr does not need to be adjusted
		return;		// do nothing
	else
	{
		Node<ItemType>* prevPtr = adjustPtr->getPrev();
		Node<ItemType>* nextPtr = adjustPtr->getNext();
		Node<ItemType>* newNextPtr = newPrevPtr->getNext();

		prevPtr->setNext(nextPtr);
		nextPtr->setPrev(prevPtr);

		newPrevPtr->setNext(adjustPtr);
		adjustPtr->setPrev(newPrevPtr);
		adjustPtr->setNext(newNextPtr);
		newNextPtr->setPrev(adjustPtr);
	}
}
// ---------------------- SAList Class Implementation End -------------------------------------------