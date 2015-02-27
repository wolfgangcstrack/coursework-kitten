/*
Manager: Wolfgang

This file is the global header file for the project and has common includes,
data structure prototypes/definitions, and all other code commonly shared by
files in the project.

This file includes the implementation of the Node, LinkedList, and List classes.
All other implementations are in their respective files.
*/

#ifndef _GLOBAL_H
#define _GLOBAL_H


#include <iostream>
#include <string>
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

template <class ItemType>
class BinaryNode;

template <class ItemType>
class BinaryTree;

template <class ItemType>
class BinarySearchTree;

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

// ---------------------- HashSC Class Interface --------------------------------------------------
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
// ---------------------- HashSC Class Interface End ----------------------------------------------

// ---------------------- BinaryNode Class --------------------------------------------------------
// Node for a binary tree
// Created by Frank M. Carrano and Tim Henry.
// Modified by CNguyen
template<class ItemType>
class BinaryNode
{
private:
	ItemType              item;         // Data portion
	BinaryNode<ItemType>* leftPtr;		// Pointer to left child
	BinaryNode<ItemType>* rightPtr;		// Pointer to right child

public:
	// constructors
	BinaryNode(const ItemType & anItem)			   { item = anItem; leftPtr = 0; rightPtr = 0; }
	BinaryNode(const ItemType & anItem,
		BinaryNode<ItemType>* left,
		BinaryNode<ItemType>* right)		   {
		item = anItem; leftPtr = left; rightPtr = right;
	}
	// accessors
	void setItem(const ItemType & anItem)		   { item = anItem; }
	void setLeftPtr(BinaryNode<ItemType>* left)	   { leftPtr = left; }
	void setRightPtr(BinaryNode<ItemType>* right)  { rightPtr = right; }
	// mutators
	ItemType getItem() const					   { return item; }
	BinaryNode<ItemType>* getLeftPtr() const	   { return leftPtr; }
	BinaryNode<ItemType>* getRightPtr() const	   { return rightPtr; }

	bool isLeaf() const							   { return (leftPtr == 0 && rightPtr == 0); }
};
// ---------------------- BinaryNode Class End ----------------------------------------------------

// ---------------------- BinaryTree Class --------------------------------------------------------
// Binary tree abstract base class
// Created by Frank M. Carrano and Tim Henry.
// Modified by:
template<class ItemType>
class BinaryTree
{
protected:
	BinaryNode<ItemType>* rootPtr;		// ptr to root node
	int count;							// number of nodes in tree

public:
	// "admin" functions
	BinaryTree()						{ rootPtr = 0; count = 0; }
	BinaryTree(const BinaryTree<ItemType> & tree)	{ }
	virtual ~BinaryTree()				{ }
	BinaryTree & operator=(const BinaryTree & sourceTree);

	// common functions for all binary trees
	bool isEmpty() const				{ return count == 0; }
	int size() const					{ return count; }
	void clear()						{ destroyTree(rootPtr); rootPtr = 0; count = 0; }
	void preOrder(void visit(ItemType &)) const		{ _preorder(visit, rootPtr); }
	void inOrder(void visit(ItemType &)) const		{ _inorder(visit, rootPtr); }
	void postOrder(void visit(ItemType &)) const	{ _postorder(visit, rootPtr); }

	// abstract functions to be implemented by derived class
	virtual bool insert(const ItemType & newData) = 0;
	virtual bool remove(const ItemType & data) = 0;
	virtual bool getEntry(const ItemType & anEntry, ItemType & returnedItem) const = 0;

private:
	// delete all nodes from the tree
	void destroyTree(BinaryNode<ItemType>* nodePtr);

	// copy from the tree rooted at nodePtr and returns a pointer to the copy
	BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* nodePtr);

	// internal traverse
	void _preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;

};

//////////////////////////////////////////////////////////////////////////

template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::copyTree(const BinaryNode<ItemType>* nodePtr)
{
	BinaryNode<ItemType>* newNodePtr = 0;

	return newNodePtr;
}

template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{

}

template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		visit(item);
		_preorder(visit, nodePtr->getLeftPtr());
		_preorder(visit, nodePtr->getRightPtr());
	}
}

template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{

}

template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{

}

template<class ItemType>
BinaryTree<ItemType> & BinaryTree<ItemType>::operator=(const BinaryTree<ItemType> & sourceTree)
{

}
// ---------------------- BinaryTree Class End ----------------------------------------------------

// ---------------------- BinarySearchTree Class Interface ----------------------------------------
// Binary Search Tree ADT
// Created by Frank M. Carrano and Tim Henry.
// Modified by:
template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{
private:
	// internal insert node: insert newNode in nodePtr subtree
	BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);

	// internal remove node: locate and delete target node under nodePtr subtree
	BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool & success);

	// delete target node from tree, called by internal remove node
	BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);

	// remove the leftmost node in the left subtree of nodePtr
	BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType & successor);

	// search for target node
	BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, const ItemType & target) const;

public:
	// insert a node at the correct location
	bool insert(const ItemType & newEntry);
	// remove a node if found
	bool remove(const ItemType & anEntry);
	// find a target node
	bool getEntry(const ItemType & target, ItemType & returnedItem) const;

};
// ---------------------- BinarySearchTree Class Interface End ------------------------------------

#endif