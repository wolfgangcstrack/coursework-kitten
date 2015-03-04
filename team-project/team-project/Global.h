/*
Manager: Wolfgang C. Strack

This file is the global header file for the project and has common includes,
data structure prototypes/definitions, and all other code commonly shared by
files in the project.

*/

#ifndef _GLOBAL_H
#define _GLOBAL_H


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
class HashSC;

template <class ItemType>	// implementation included
class BinaryNode;

template <class ItemType>
class BinaryTree;

template <class ItemType>
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

	ostream& write(ostream &os); // To include here or as separate static function
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
/* Modifications
item stores a POINTER to the data, NOT THE ACTUAL DATA
getItem() : returns pointer to item
added accessTimes member variable and mutator/accessor function
*/

template<class ItemType>
class Node
{
private:
	ItemType*       item;
	Node<ItemType>* next;
	Node<ItemType>* prev;

	int accessTimes;

public:
	Node()										{ next = 0; prev = 0; accessTimes = 0; }
	Node(const ItemType* anItem)				{ item = anItem; next = 0; prev = 0; accessTimes = 0; }
	~Node()										{ delete item; delete next; delete prev; }

	void setItem(const ItemType* anItem)		{ item = anItem; }
	void setNext(Node<ItemType>* nextNodePtr)	{ next = nextNodePtr; }
	void setPrev(Node<ItemType>* prevNodePtr)	{ prev = prevNodePtr; }
	void incrementAccessTimes(int increment=1)	{ accessTimes += increment; }
	ItemType* getItem() const					{ return item; }
	Node<ItemType>* getNext() const				{ return next; }
	Node<ItemType>* getPrev() const				{ return prev; }
	const int& getAccessTimes() const			{ return accessTimes; }
};
// ---------------------- Node Class End ----------------------------------------------------------

// ---------------------- DoublyLinkedList Class Interface ----------------------------------------
// Doubly Linked List abstract base class
// By C. Lee-Klawender

// Modified by: Wolfgang C. Strack

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
	virtual ~DoublyLinkedList()	{ clear(); }

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
// ---------------------- DoublyLinkedList Class Interface End ------------------------------------

// ---------------------- SAList Class Interface --------------------------------------------------
// Linked List ADT 
// This list allows the user to insert and remove data at a specified position
// By CNguyen

// Modification: From List to SAList (Self-Adjusting)
// Modified by: Wolfgang C. Strack

// Implementation: SAList.cpp

template<class ItemType>
class SAList : public DoublyLinkedList<ItemType>  // derived from abstract DoublyLinkedList class
{
private:
	// Finds node at a specified position
	Node<ItemType>* getNodeAt(int position) const; // calls adjust()

	const int MAX_LENGTH = 5; // not final

	void adjust(Node<ItemType>* adjustPtr);
public:
	// Adds node at FRONT of list
	bool insert(const ItemType& newEntry);
	// Removes node at a specified position
	bool remove(int position);
	// Passes back node at a specified position
	bool getEntry(int position, ItemType & anEntry) const;
};
// ---------------------- SAList Class Interface End ------------------------------------------------

// ---------------------- HashSC Class Interface --------------------------------------------------
// Modified by: Louis Christopher

// Implementation: HashSC.cpp

template <class Object>
class HashSC
{
	static const int INIT_TABLE_SIZE = 97;
	static const float INIT_MAX_LAMBDA;
private:
	SAList<Object> * mLists; // for array of linked SALists
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

// Modified by: Wolfgang C. Strack
/* Modifications
item stores a POINTER to the data, NOT THE ACTUAL DATA
getItem() : returns pointer to item
*/

template<class ItemType>
class BinaryNode
{
private:
	ItemType*             item;         // Data portion
	BinaryNode<ItemType>* leftPtr;		// Pointer to left child
	BinaryNode<ItemType>* rightPtr;		// Pointer to right child

public:
	// constructors
	BinaryNode(const ItemType * anItem)			   { item = anItem; leftPtr = 0; rightPtr = 0; }
	BinaryNode(const ItemType * anItem,
		BinaryNode<ItemType>* left,
		BinaryNode<ItemType>* right)			   { item = anItem; leftPtr = left; rightPtr = right; }
	// accessors
	void setItem(const ItemType * anItem)		   { item = anItem; }
	void setLeftPtr(BinaryNode<ItemType>* left)	   { leftPtr = left; }
	void setRightPtr(BinaryNode<ItemType>* right)  { rightPtr = right; }
	// mutators
	ItemType* getItem() const					   { return item; }
	BinaryNode<ItemType>* getLeftPtr() const	   { return leftPtr; }
	BinaryNode<ItemType>* getRightPtr() const	   { return rightPtr; }

	bool isLeaf() const							   { return (leftPtr == 0 && rightPtr == 0); }
};
// ---------------------- BinaryNode Class End ----------------------------------------------------

// ---------------------- BinaryTree Class Interface ----------------------------------------------
// Binary tree abstract base class
// Created by Frank M. Carrano and Tim Henry.

// Modified by: Andrew Wang

// Implementation: BST.cpp

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
// ---------------------- BinaryTree Class Interface End ------------------------------------------

// ---------------------- BinarySearchTree Class Interface ----------------------------------------
// Binary Search Tree ADT
// Created by Frank M. Carrano and Tim Henry.

// Modified by: Andrew Wang

// Implementation: BST.cpp

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