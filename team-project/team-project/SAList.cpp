/*
Manager: Wolfgang C. Strack

This file includes the implementation for:
DoublyLinkedList class
SAList class
*/

#include "Global.h"

// ---------------------- DoublyLinkedList Class Implementation -----------------------------------
/*
This is the DoublyLinkedList class. My team project and I
decided on using DoublyLinkedLists for implementing Self-Adjusting
List because it would make adjustments much easier and more efficient.

Modifications:
- completed Destructor
- clear() uses a while loop instead of a for loop
*/
template<class ItemType>
DoublyLinkedList<ItemType>::DoublyLinkedList()
{
	itemCount = 0;
	headPtr = new Node<ItemType>();
	tailPtr = new Node<ItemType>();
	headPtr->setNext(tailPtr);
	tailPtr->setPrev(headPtr);
}

template<class ItemType>
DoublyLinkedList<ItemType>::DoublyLinkedList(const DoublyLinkedList<ItemType>& aList)
{
	itemCount = aList.itemCount;
	Node<ItemType>  *origChainPtr;

	origChainPtr = aList.headPtr;

	headPtr = new Node<ItemType>();				// copy dummy head node

	// Copy remaining nodes BEFORE tailPtr
	Node<ItemType>* newChainPtr = headPtr;		// ignore data
	origChainPtr = origChainPtr->getNext();
	while (origChainPtr != aList.tailPtr)
	{
		ItemType *nextItem = origChainPtr->getItem();
		Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);
		newChainPtr->setNext(newNodePtr);		// link prev to current
		newNodePtr->setPrev(newChainPtr);		// link current to prev

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
		cout << currPtr->getItem() << " ";		// display data
		currPtr = currPtr->getNext();			// go to next node
	}
	cout << endl << endl;
}


template<class ItemType>
void DoublyLinkedList<ItemType>::clear()
{
	Node<ItemType> * deletePtr, *nodePtr;
	deletePtr = headPtr->getNext();
	nodePtr = deletePtr;
	while (nodePtr != tailPtr)					// walk each node
	{
		nodePtr = deletePtr->getNext();
		delete deletePtr;
		deletePtr = nodePtr;
	}

	itemCount = 0;
}
// ---------------------- DoublyLinkedList Class Implementation End -------------------------------

// ---------------------- SAList Class Implementation -----------------------------------------------
/*
This is the SAList(Self - Adjusting List) class.I based the implementation
off of the regular List class and the DoublyLinkedList abstract class.
The adjust method implementation is not final for our Team Project implementation.

Modifications from List class :
-changed all functions to work with DoublyLinkedList
- insertions are only performed at the front of the list
- added adjust(int) - adjusts List so that nodes with greatest accessTimes are near the front
*/
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
// ---------------------- SAList Class Implementation End -------------------------------------------