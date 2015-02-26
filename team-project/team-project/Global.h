/*
This file is the global header file for the project and has common includes,
data structure prototypes/definitions, and all other code commonly shared by
files in the project.

Initial: Added class's Node, LinkedList, List, HashSC;
*/

#ifndef GLOBAL_H
#define GLOBAL_H



#include <cmath>
using namespace std;

template <class ItemType>
class Node;

template <class ItemType>
class LinkedList;

template <class ItemType>
class List;

template <class ItemType>
class HashSC;

// ---------------------- Node Class --------------------------------------------------------------
// Linkded List Node Class
// Created by Frank M. Carrano and Tim Henry.
// Modified by CNguyen

// Edit: getItem returns reference to ItemType
template<class ItemType>
class Node
{
private:
	ItemType        item;
	Node<ItemType>* next;

public:
	Node()										{ next = 0; }
	Node(const ItemType& anItem)				{ item = anItem; next = 0; }
	void setItem(const ItemType& anItem)		{ item = anItem; }
	void setNext(Node<ItemType>* nextNodePtr)	{ next = nextNodePtr; }
	ItemType& getItem() const					{ return item; }
	Node<ItemType>* getNext() const				{ return next; }
};
// ---------------------- Node Class End ----------------------------------------------------------

// ---------------------- LinkedList Class --------------------------------------------------------
// Linked List abstract base class
// By CNguyen
template<class ItemType>
class LinkedList
{
protected:
	Node<ItemType>* headPtr; // Pointer to first node in the list
	int itemCount;           // Current count of list items

public:
	// constructor
	LinkedList()			{ headPtr = 0; itemCount = 0; }
	// copy constructor
	LinkedList(const LinkedList<ItemType>& aList);
	// destructor
	virtual ~LinkedList()	{ clear(); }

	// check for empty list
	bool isEmpty() const	{ return itemCount == 0; }
	// get number of entries in the list
	int size() const		{ return itemCount; }
	// remove all entries from list
	void clear();
	// display list from front to end
	void display() const;
	// abstract insert function
	virtual bool insert(const ItemType& newEntry, int newPosition = 1) = 0;
};

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
// ---------------------- LinkedList Class End ----------------------------------------------------

// ---------------------- List Class --------------------------------------------------------------
// Linked List ADT 
// This list allows the user to insert and remove data at a specified position
// By CNguyen
template<class ItemType>
class List : public LinkedList<ItemType>  // derived from abstract LinkedList class
{
private:
	// Finds node at a specified position
	Node<ItemType>* getNodeAt(int position) const;

public:
	// Adds node at a specified position
	bool insert(const ItemType& newEntry, int newPosition = 1);
	// Removes node at a specified position
	bool remove(int position);
	// Passes back node at a specified position
	bool getEntry(int position, ItemType & anEntry) const;
};


template<class ItemType>
bool List<ItemType>::insert(const ItemType& newEntry, int newPosition)
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
	else  // insert new node in middle or end of list
	{
		Node<ItemType>* prevPtr = getNodeAt(newPosition - 1);  // go to position
		newNodePtr->setNext(prevPtr->getNext());
		prevPtr->setNext(newNodePtr);
	}
	itemCount++;
	return true;
}


template<class ItemType>
bool List<ItemType>::remove(int position)
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
	else   // remove from middle or end of list
	{
		Node<ItemType>* prevPtr = getNodeAt(position - 1); // get to position
		deletePtr = prevPtr->getNext();		// remove from list
		prevPtr->setNext(deletePtr->getNext());
	}
	delete deletePtr;
	itemCount--;
	return true;
}

template<class ItemType>
bool List<ItemType>::getEntry(int position, ItemType & anEntry) const
{
	if (position < 1 || position > itemCount)
		return false;

	Node<ItemType>* copyPtr = getNodeAt(position); // get to position
	anEntry = copyPtr->getItem();
	return true;
}


template<class ItemType>
Node<ItemType>* List<ItemType>::getNodeAt(int position) const
{
	Node<ItemType>* curPtr = headPtr;
	for (int i = 1; i < position; i++)
		curPtr = curPtr->getNext();
	return curPtr;
}
// ---------------------- List Class End ----------------------------------------------------------

// ---------------------- HashSC Class ------------------------------------------------------------
template <class Object>
class HashSC
{
	static const int INIT_TABLE_SIZE = 97;
	static const float INIT_MAX_LAMBDA;
private:
	List<Object> * mLists; // for array of linked lists
	int mSize;  // number of entries
	int mTableSize; // array size
	float mMaxLambda; // max. load factor

public:
	HashSC(int tableSize = INIT_TABLE_SIZE);
	~HashSC();
	bool contains(const Object & x) const;
	void makeEmpty();
	bool insert(const Object & x);
	bool remove(const Object & x);
	static long nextPrime(long n);
	int size() const { return mSize; }
	bool setMaxLambda(float lm);

private:
	void rehash();
	int myHash(const Object & x) const;
};

template <class Object>
const float HashSC<Object>::INIT_MAX_LAMBDA = 1.5;

// HashSC method definitions -------------------
template <class Object>
HashSC<Object>::HashSC(int tableSize) : mSize(0)
{
	if (tableSize < INIT_TABLE_SIZE)
		mTableSize = INIT_TABLE_SIZE;
	else
		mTableSize = nextPrime(tableSize);

	mLists = new List<Object>[mTableSize];
	mMaxLambda = INIT_MAX_LAMBDA;
}

template <class Object>
HashSC<Object>::~HashSC()
{
	//    for( int i=0; i < mTableSize; ++i )//FIXED******************
	//        delete mLists[i];//FIXED******************
	delete[] mLists;
}

template <class Object>
int HashSC<Object>::myHash(const Object & x) const
{
	int hashVal;

	hashVal = Hash(x) % mTableSize;
	if (hashVal < 0)
		hashVal += mTableSize;

	return hashVal;
}

template <class Object>
void HashSC<Object>::makeEmpty()
{
	int k;

	for (k = 0; k < mTableSize; k++)
		mLists[k].clear();
	mSize = 0;
}

template <class Object>
bool HashSC<Object>::contains(const Object & x) const
{
	const List<Object> & theList = mLists[myHash(x)];
	Object tempObj;					// ADDED**********************

	for (int i = 0; i < theList.size(); i++)
	{
		theList.getEntry((i + 1), tempObj);//FIXED******************
		if (tempObj == x)		//FIXED******************
			return true;
	}

	// not found
	return false;
}

template <class Object>
bool HashSC<Object>::remove(const Object & x)
{
	List<Object> &theList = mLists[myHash(x)];
	Object tempObj;					// ADDED**********************

	for (int i = 0; i < theList.size(); i++)
	{
		theList.getEntry((i + 1), tempObj);//FIXED******************
		if (tempObj == x)		//FIXED******************
		{
			theList.remove(i + 1);
			mSize--;
			return true;
		}
	}
	// not found
	return false;
}

template <class Object>
bool HashSC<Object>::insert(const Object & x)
{
	List<Object> &theList = mLists[myHash(x)];
	int listSize = theList.size();
	Object tempObj;					// ADDED**********************

	for (int i = 0; i < listSize; i++)
	{
		theList.getEntry((i + 1), tempObj);//FIXED******************
		if (tempObj == x)		//FIXED******************
			return false;
	}
	// not found so we insert at the beginning
	theList.insert(x);

	// check load factor
	if (++mSize > mMaxLambda * mTableSize)
		rehash();

	return true;
}

template <class Object>
void HashSC<Object>::rehash()
{
	List<Object> *oldLists = mLists;
	int k, oldTableSize = mTableSize;
	List<Object> *currList;           // CHANGED********************
	Object tempObj;

	mTableSize = nextPrime(2 * oldTableSize);
	mLists = new List<Object>[mTableSize];

	mSize = 0;
	for (k = 0; k < oldTableSize; k++)
	{
		currList = &oldLists[k];
		for (int i = 0; i < currList->size(); ++i)//updated***************
		{
			currList->getEntry((i + 1), tempObj);//updated***************
			insert(tempObj);
		}

	}
	delete[] oldLists;
}

template <class Object>
bool HashSC<Object>::setMaxLambda(float lam)
{
	if (lam < .1 || lam > 100)
		return false;
	mMaxLambda = lam;
	return true;
}

template <class Object>
long HashSC<Object>::nextPrime(long n)
{
	long k, candidate, loopLim;

	// loop doesn't work for 2 or 3
	if (n <= 2)
		return 2;
	else if (n == 3)
		return 3;

	for (candidate = (n % 2 == 0) ? n + 1 : n; true; candidate += 2)
	{
		// all primes > 3 are of the form 6k +/- 1
		loopLim = (long)((sqrt((float)candidate) + 1) / 6);

		// we know it is odd.  check for divisibility by 3
		if (candidate % 3 == 0)
			continue;

		// now we can check for divisibility of 6k +/- 1 up to sqrt
		for (k = 1; k <= loopLim; k++)
		{
			if (candidate % (6 * k - 1) == 0)
				break;
			if (candidate % (6 * k + 1) == 0)
				break;
		}
		if (k > loopLim)
			return candidate;
	}
}
// ---------------------- HashSC Class End --------------------------------------------------------


#endif