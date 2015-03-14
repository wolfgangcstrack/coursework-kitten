/*
Manager: Wolfgang C. Strack

This file is the global header file for the project and has common includes,
data structure prototypes/definitions, and all other code commonly shared by
files in the project.

*/

#pragma once

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Item;					// Data class, implementation included

template <class ItemType>	// implementation included
class Node;

template <class ItemType>
class DoublyLinkedList;

template <class ItemType>
class SAList;

template <class ItemType>
class HashTable;

template <class ItemType>
class HashSC;

class BinaryNode;

class BinaryTree;

class BinarySearchTree;

// ---------------------- Item Class --------------------------------------------------------------
class Item
{
private:
	string name;
	string productID; // not final

	double weight;
	double *dimensions;
	double price;

	string seller;
	string category;
public:
	// constructors
	Item() {}
	Item(string nm, string pID, double w, double *dims, double p, string sell, string categ);
	~Item() { delete[] dimensions; }

	// accessors
	const string& getName() const		{ return name; }
	const string& getProductID() const	{ return productID; }
	const double& getWeight() const		{ return weight; }
	const double* getDimensions() const { return dimensions; }
	const double& getPrice() const		{ return price; }
	const string& getSeller() const		{ return seller; }
	const string& getCategory() const	{ return category; }

	void setName(string nm)				{ name = nm; }
	void setProductID(string pID)		{ productID = pID; }
	void setWeight(double w)			{ weight = w; }
	void setDimensions(double dims[3])	{ for (int i = 0; i < 3; i++) dimensions[i] = dims[i]; }
	void setPrice(double p)				{ price = p; }
	void setSeller(string sell)			{ seller = sell; }
	void setCategory(string categ)		{ category = categ; }

	//ostream& write(ostream &os); // To include here or as separate static function
};

Item::Item(string nm, string pID, double w, double dims[3], double p, string sell, string categ)
{
	name = nm;
	productID = pID;
	weight = w;
	for (int i = 0; i < 3; i++)
		dimensions[i] = dims[i];
	price = p;
	seller = sell;
	category = categ;
}
// ---------------------- Item Class End ----------------------------------------------------------

// ---------------------- Node Class --------------------------------------------------------------
// Linkded List Node Class
// Created by Frank M. Carrano and Tim Henry.
// Modified by CNguyen
// Doubly Linked Version

// Modified by: Wolfgang C. Strack
/* Modifications:
- added accessTimes member variable and mutator/accessor
	function for SAList adjustment
*/

template<class ItemType>
class Node
{
private:
	ItemType       item;
	Node<ItemType>* next;
	Node<ItemType>* prev;

	int accessTimes; // used for adjustment in self-adjusting list

public:
	// constructors
	Node()										{ next = 0; prev = 0; accessTimes = 0; }
	Node(const ItemType& anItem)				{ item = anItem; next = 0; prev = 0; accessTimes = 0; }
	// mutators
	void setItem(const ItemType* anItem)		{ item = anItem; }
	void setNext(Node<ItemType>* nextNodePtr)	{ next = nextNodePtr; }
	void setPrev(Node<ItemType>* prevNodePtr)	{ prev = prevNodePtr; }
	void incrementAccessTimes(int increment = 1){ accessTimes += increment; }
	// accessors
	ItemType getItem() const					{ return item; }
	Node<ItemType>* getNext() const				{ return next; }
	Node<ItemType>* getPrev() const				{ return prev; }
	const int& getAccessTimes() const			{ return accessTimes; }
};
// ---------------------- Node Class End ----------------------------------------------------------

// ---------------------- DoublyLinkedList Class Interface ----------------------------------------
// Doubly Linked List abstract base class
// By C. Lee-Klawender

// Modified by: Wolfgang C. Strack
/* Modifications:
- completed Destructor
- clear() uses a while loop instead of a for loop
*/

// Implementation: SAList.cpp

template<class ItemType>
class DoublyLinkedList
{
protected:
	Node<ItemType>* headPtr; // Pointer to (dummy) first node in the list
	Node<ItemType>* tailPtr; // Pointer to (dummy) last node in the list
	int itemCount;           // Current count of list items
public:
	// constructor
	DoublyLinkedList();
	// copy constructor
	DoublyLinkedList(const DoublyLinkedList<ItemType>& aList);
	// destructor
	virtual ~DoublyLinkedList()	{ clear(); delete headPtr; delete tailPtr; }

	// check for empty list
	bool isEmpty() const	{ return (itemCount == 0); }
	// get number of entries in the list
	int size() const		{ return itemCount; }
	// remove all entries from list
	void clear();
	// display list from front to end
	void display() const;
	// abstract insert function
	virtual bool insert(const ItemType& newEntry, int newPosition = 1) = 0;
};
// ---------------------- DoublyLinkedList Class Interface End ------------------------------------

// ---------------------- SAList Class Interface --------------------------------------------------
// Linked List ADT 
// This list allows the user to insert and remove data at a specified position
// By CNguyen

// Modified by: Wolfgang C. Strack
/* Modifications from List class:
- changed all functions to work with DoublyLinkedList
- insertions are only performed at the front of the list
- added adjust(int) - adjusts List so that nodes with greatest accessTimes are near the front
*/

// Implementation: SAList.cpp

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
};
// ---------------------- SAList Class Interface End ----------------------------------------------

// ---------------------- HashTable Class Interface -----------------------------------------------
// Modified by: Louis Christopher

// Implementation is as Base Class of HashSC which is kept in HashSC.cpp

template <class Object>
class HashTable
{
protected:
	int(*Hash)(const Object&obj);
	int(*Compare)(const Object&left, const Object&right);
public:
	HashTable(int(*hashFcn)(const Object &obj),
		int(*comp)(const Object&left, const Object&right)){
		Hash = hashFcn; Compare = comp;
	}
	virtual ~HashTable(){}
	virtual bool contains(const Object & x) const = 0;
	virtual void makeEmpty() = 0;
	virtual bool insert(const Object & x) = 0;
	virtual bool remove(const Object & x) = 0;
	virtual int size() const = 0;
	virtual void displayStatistics() const = 0;
	virtual bool getEntry(const Object & target, Object & returnedItem) const = 0;
};
// ---------------------- HashTable Class Interface End -------------------------------------------

// ---------------------- HashSC Class Interface --------------------------------------------------
// HashSC class
// Derived class of abstract HashTable

// Modified by: Louis Christopher
/* Modifications (besides assignment specifications):
- uses SAList (self-adjusting list) instead of List
- mLists is now a pointer to an array of SAList pointers
- all SALists in mLists are now dynamically allocated pointers
	- all functions change accordingly to work with pointers to SAList
*/

// Implementation: HashSC.cpp

template<class Object>
class HashSC : public HashTable<Object> // FIX HERE TO BE A DERIVED CLASS OF HashTable
{
	static const int INIT_TABLE_SIZE = 97;
	static const float INIT_MAX_LAMBDA;
private:
	SAList<Object> ** mLists;	// for array of linked lists
	int mSize;					// number of entries
	int mTableSize;				// array size
	float mMaxLambda;			// max. load factor

	// statistics variables
	static int longestList;
	static long numCollisions;

public:
	// constructor
	HashSC(int(*hashFcn)(const Object &obj),
		int(*comp)(const Object&left, const Object&right),
		int tableSize = INIT_TABLE_SIZE);
	// destructor
	~HashSC();

	bool contains(const Object & x) const;						// calls SAList adjust() function
	bool getEntry(const Object & target, Object & returnedItem) const;// calls SAList adjust() function
	void makeEmpty();
	bool insert(const Object & x);
	bool remove(const Object & x);
	static long nextPrime(long n);
	int size() const { return mSize; }
	bool setMaxLambda(float lm);

	void displayStatistics() const;
private:
	void rehash();
	int myHash(const Object & x) const;
};
// ---------------------- HashSC Class Interface End ----------------------------------------------

// ---------------------- BinaryNode Class --------------------------------------------------------
// Node for a binary tree
// Created by Frank M. Carrano and Tim Henry.
// Modified by CNguyen

// Modified by: Wolfgang C. Strack
/* Modifications:

*/

class BinaryNode
{
private:
	void*		item;			// Data portion
	BinaryNode* leftPtr;		// Pointer to left child 
	BinaryNode* rightPtr;		// Pointer to right child

public:
	// constructors
	BinaryNode(void* anItem)			{ item = anItem; leftPtr = 0; rightPtr = 0; }
	BinaryNode(void* anItem, BinaryNode* left, BinaryNode* right) { item = anItem; leftPtr = left; rightPtr = right; }
	// accessors
	void setItem(void* anItem)			{ item = anItem; }
	void setLeftPtr(BinaryNode* left)	{ leftPtr = left; }
	void setRightPtr(BinaryNode* right)	{ rightPtr = right; }
	// mutators
	void* getItem() const				{ return item; }
	BinaryNode* getLeftPtr() const		{ return leftPtr; }
	BinaryNode* getRightPtr() const		{ return rightPtr; }

	bool isLeaf() const					{ return (leftPtr == 0 && rightPtr == 0); }
};
// ---------------------- BinaryNode Class End ----------------------------------------------------

// ---------------------- BinaryTree Class Interface ----------------------------------------------
// Binary tree abstract base class
// Created by Frank M. Carrano and Tim Henry.

// Modified by: Andrew Wang

// Implementation: BST.cpp

class BinaryTree
{
protected:
	BinaryNode* rootPtr;		// ptr to root node
	int count;					// number of nodes in tree

	// copy from the tree rooted at nodePtr and returns a pointer to the copy
	BinaryNode* copyTree(const BinaryNode* nodePtr);
public:
	// "admin" functions
	BinaryTree()							{ rootPtr = 0; count = 0; }
	BinaryTree(const BinaryTree& tree)		{ if (this->rootPtr != 0) clear(); this->rootPtr = copyTree(tree.rootPtr); }
	virtual ~BinaryTree()					{ clear(); }// CALL clear()
	BinaryTree & operator=(const BinaryTree & sourceTree);

	// common functions for all binary trees
	bool isEmpty() const					{ return count == 0; }
	int size() const						{ return count; }
	void clear()							{ destroyTree(rootPtr); rootPtr = 0; count = 0; }
	void inOrder(void visit(void*)) const	{ _inorder(visit, rootPtr); }

	// abstract functions to be implemented by derived class
	virtual bool insert(void* newData) = 0;
	virtual bool remove(void* data) = 0;
	virtual bool getEntry(void* anEntry, void* returnedItem) const = 0;
private:
	// delete all nodes from the tree
	void destroyTree(BinaryNode* nodePtr);

	// internal traverse
	void _inorder(void visit(void*), BinaryNode* nodePtr) const;
};
// ---------------------- BinaryTree Class Interface End ------------------------------------------

// ---------------------- BinarySearchTree Class Interface ----------------------------------------
// Binary Search Tree ADT
// Created by Frank M. Carrano and Tim Henry.

// Modified by: Andrew Wang

// Implementation: BST.cpp

class BinarySearchTree : public BinaryTree
{
private:

	int compare(void*, void*) const;

	// internal insert node: insert newNode in nodePtr subtree
	BinaryNode* _insert(BinaryNode* nodePtr, BinaryNode* newNode);

	// internal remove node: locate and delete target node under nodePtr subtree
	BinaryNode* _remove(BinaryNode* nodePtr, void* target, bool& success);

	// delete target node from tree, called by internal remove node
	BinaryNode* deleteNode(BinaryNode* targetNodePtr);

	// remove the leftmost node in the left subtree of nodePtr
	BinaryNode* removeLeftmostNode(BinaryNode* nodePtr, void* successor);

	// search for target node
	BinaryNode* findNode(BinaryNode* treePtr, void* target) const;


public:
	BinarySearchTree() {}

	BinarySearchTree(const BinarySearchTree& tree);

	// insert a node at the correct location
	bool insert(void* newEntry);
	// remove a node if found
	bool remove(void* anEntry);
	// find a target node
	bool getEntry(void* target, void* returnedItem) const;
	// NOT IN THE Tree Code Files on Catalyst, use for HW#4:
	BinarySearchTree & operator=(const BinarySearchTree & sourceTree);
};
// ---------------------- BinarySearchTree Class Interface End ------------------------------------