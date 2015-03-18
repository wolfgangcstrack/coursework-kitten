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
#include <string>
using namespace std;

class Item;					// Data class, implementation included

template <class ItemType>	// implementation included
class Node;

template <class ItemType>
class HashTable;

template <class ItemType>
class BinaryNode;

// ---------------------- Item Class --------------------------------------------------------------
class Item
{
private:
	string name;
	string productID;

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

	// "partial" display because Item has many fields, used for mass listing of Items
	friend ostream& operator<<(ostream &os, const Item & item)
	{
		os << setw(30) << left
			<< (item.name.length() <= 30 ? item.name : item.name.substr(0, 27) + "...")
			<< right << ":" << item.productID;
		return os;
	}

	// "full" display
	void display(ostream &os)
	{
		os << "Name: " << name << endl
			<< "Product ID: " << productID << endl
			<< "Weight: " << weight << endl
			<< "Dimensions: " << dimensions[0] << " x " << dimensions[1] << " x " << dimensions[2] << endl
			<< "Price: " << setprecision(2) << fixed << price << endl
			<< "Seller: " << seller << endl
			<< "Category: " << category << endl;
	}
	// for outputting to file

	void write(ostream &os)
	{
		os << productID << ":" << name << ":" << weight << ":"
			<< dimensions[0] << " " << dimensions[1] << " " << dimensions[2]
			<< ":" << price << ":" << seller << ":" << category << endl;
	}
};
// ---------------------- Item Class End ----------------------------------------------------------

// ---------------------- Node Class --------------------------------------------------------------
// Doubly Linked Version of Node
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
	const int getAccessTimes() const			{ return accessTimes; }
};
// ---------------------- Node Class End ----------------------------------------------------------

// ---------------------- HashTable Class Interface -----------------------------------------------
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