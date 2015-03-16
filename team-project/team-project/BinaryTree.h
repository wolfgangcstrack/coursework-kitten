/*
Manager: Andrew Wang

This file includes the implementation for:
- BinaryTree class
*/

#pragma once

#include "Global.h"

// ---------------------- BinaryTree Class Interface ----------------------------------------------
template<class ItemType>
class BinaryTree
{
protected:
	BinaryNode<ItemType>* rootPtr;		// ptr to root node
	int count;							// number of nodes in tree

	BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* nodePtr);
public:
	// "admin" functions
	BinaryTree()					{ rootPtr = 0; count = 0; }
	BinaryTree(const BinaryTree<ItemType> & tree) { clear(); rootPtr = copyTree(tree.rootPtr); }
	virtual ~BinaryTree()			{ clear(); }
	BinaryTree & operator=(const BinaryTree & sourceTree);

	// common functions for all binary trees
	bool isEmpty() const				{ return count == 0; }
	int size() const					{ return count; }
	void clear(){ destroyTree(rootPtr); rootPtr = 0; count = 0; }
	void preOrder(void visit(ItemType &)) const		{ _preorder(visit, rootPtr); }
	void inOrder(void visit(ItemType &)) const		{ _inorder(visit, rootPtr); }
	void postOrder(void visit(ItemType &)) const	{ _postorder(visit, rootPtr); }

	void printIndentedTree(void visit(ItemType &, string &)) const
	{ string start = ""; _indentorder(visit, rootPtr, start); }

	// abstract functions to be implemented by derived class
	virtual bool insert(const ItemType & newData) = 0;
	virtual bool remove(const ItemType & data) = 0;
	virtual bool getEntry(const ItemType & anEntry, ItemType & returnedItem) const = 0;

private:
	// delete all nodes from the tree
	void destroyTree(BinaryNode<ItemType>* nodePtr);

	// internal traverse
	void _preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;

	void _indentorder(void visit(ItemType &, string &), BinaryNode<ItemType>* nodePtr, string &tabs) const;
};

//////////////////////////////////////////////////////////////////////////

template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::copyTree(const BinaryNode<ItemType>* nodePtr)
{
	BinaryNode<ItemType>* newNodePtr = 0;

	if (nodePtr == 0)
		return 0;

	newNodePtr = new BinaryNode<ItemType>(nodePtr->getItem());

	newNodePtr->setLeftPtr(copyTree(nodePtr->getLeftPtr()));
	newNodePtr->setRightPtr(copyTree(nodePtr->getRightPtr()));
	count++;

	return newNodePtr;
}

template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr == 0)
		return;

	destroyTree(nodePtr->getLeftPtr());
	destroyTree(nodePtr->getRightPtr());

	delete nodePtr;
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
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		_inorder(visit, nodePtr->getLeftPtr());
		visit(item);
		_inorder(visit, nodePtr->getRightPtr());
	}
}

template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		_postorder(visit, nodePtr->getLeftPtr());
		_postorder(visit, nodePtr->getRightPtr());
		visit(item);
	}
}

template<class ItemType>
void BinaryTree<ItemType>::_indentorder(void visit(ItemType &, string &), BinaryNode<ItemType>* nodePtr, string &tabs) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		_indentorder(visit, nodePtr->getRightPtr(), tabs + "\t");
		visit(item, tabs);
		_indentorder(visit, nodePtr->getLeftPtr(), tabs + "\t");
	}
}

template<class ItemType>
BinaryTree<ItemType> & BinaryTree<ItemType>::operator=(const BinaryTree<ItemType> & sourceTree)
{
	if (rootPtr != 0)	// if already filled
		clear();		// clear old tree
	rootPtr = copyTree(sourceTree.rootPtr);
	return *this;
}
// ---------------------- BinaryTree Class Implementation End -------------------------------------