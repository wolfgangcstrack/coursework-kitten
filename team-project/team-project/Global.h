/*
Manager: Wolfgang C. Strack

This file is the global header file for the project and has common includes,
data structure prototypes/definitions, and all other code commonly shared by
files in the project.

*/

#pragma once

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

class Item;					// Data class, implementation included

template <class ItemType>	// implementation included
class Node;

template <class ItemType>
class HashTable;

class BinaryNode;

// ---------------------- Item Class --------------------------------------------------------------
class Item
{
private:
	string name;
	string productID; // not final

	double weight;
	double dimensions[3];
	double price;

	string seller;
	string category;
public:
	// constructors and destructor
	Item() {}
	Item::Item(string pID, string nm, double w, double dims[3], double p, string sell, string categ)
	{
		productID = pID;
		name = nm;
		weight = w;
		for (int i = 0; i < 3; i++)
			dimensions[i] = dims[i];
		price = p;
		seller = sell;
		category = categ;
	}
	~Item() {}

	// accessors
	const string& getProductID() const	{ return productID; }
	const string& getName() const		{ return name; }
	const double& getWeight() const		{ return weight; }
	const double* getDimensions() const { return dimensions; }
	const double& getPrice() const		{ return price; }
	const string& getSeller() const		{ return seller; }
	const string& getCategory() const	{ return category; }
	// mutators
	void setProductID(string pID)		{ productID = pID; }
	void setName(string nm)				{ name = nm; }
	void setWeight(double w)			{ weight = w; }
	void setDimensions(double dims[3])	{ for (int i = 0; i < 3; i++) dimensions[i] = dims[i]; }
	void setPrice(double p)				{ price = p; }
	void setSeller(string sell)			{ seller = sell; }
	void setCategory(string categ)		{ category = categ; }

	ostream& write(ostream &os)
	{
		os << setw(10)
			<< (name.length() < 10 ? name : name.substr(0, 7) + "...")
			<< ":" << productID;
		return os;
	}
};
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

	int (*compare)(void*, void*);

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
	BinarySearchTree(int comp(void* left, void* right)) { compare = comp; }

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