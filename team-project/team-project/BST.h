/*
Manager: Andrew Wang

This file includes the implementation for:
- BinaryTree class
- BinarySearchTree class
*/

#pragma once

#include "Global.h"

// ---------------------- BinaryTree Class Implementation -----------------------------------------
BinaryNode* BinaryTree::copyTree(const BinaryNode* nodePtr)
{
	BinaryNode* newNodePtr = 0;

	if (nodePtr == 0)  //return 0 if nodeptr doesnt exist
		return 0;

	newNodePtr = new BinaryNode(nodePtr->getItem()); //assign a new node and put nodeptr in it
	newNodePtr->setLeftPtr(copyTree(nodePtr->getLeftPtr())); //recursive call to copy left nodes
	newNodePtr->setRightPtr(copyTree(nodePtr->getRightPtr())); //recursive call for right nodes
	count++; //increment count

	return newNodePtr; //return the rootptr
}

void BinaryTree::destroyTree(BinaryNode* nodePtr)
{
	if (nodePtr == 0) //end if nodeptr is null
		return;

	destroyTree(nodePtr->getLeftPtr()); //recursive call to delete left node
	destroyTree(nodePtr->getRightPtr());//recursive call to delete right node
	delete nodePtr; //delete
}

void BinaryTree::_inorder(void visit(void*), BinaryNode* nodePtr) const
{
	if (nodePtr != 0) //continue if pointer is pointing to a node
	{
		void* item = nodePtr->getItem();
		_inorder(visit, nodePtr->getLeftPtr());
		visit(item); //print after leftptr recursive call so that print will be in order
		_inorder(visit, nodePtr->getRightPtr());

	}
}

BinaryTree& BinaryTree::operator=(const BinaryTree& sourceTree)
{
	// CALL copyTree and return *this
	if (rootPtr != 0) // already filled tree?
		clear(); // clear old tree
	rootPtr = copyTree(sourceTree.rootPtr);
	return *this;
}
// ---------------------- BinaryTree Class Implementation End -------------------------------------

// ---------------------- BinarySearchTree Class Implementation -----------------------------------
BinarySearchTree::BinarySearchTree(const BinarySearchTree& tree)
{
	//this->compare = tree.compare;
	this->rootPtr = copyTree(tree.rootPtr);
}

bool BinarySearchTree::insert(void* newEntry)
{
	BinaryNode* newNodePtr = new BinaryNode(newEntry);
	rootPtr = _insert(rootPtr, newNodePtr);
	return true;
}

bool BinarySearchTree::remove(void* target)
{
	bool isSuccessful = false;
	rootPtr = _remove(rootPtr, target, isSuccessful);
	return isSuccessful;
}

bool BinarySearchTree::getEntry(void* anEntry, void* returnedItem) const
{
	BinaryNode* ptr = findNode(rootPtr, anEntry); //find the node

	if (ptr != 0) //if node is not pointing to null, a node with anentry is found
	{
		returnedItem = ptr->getItem(); //replace anentry with returneditem
		return true;
	}
	else
		return false;
}

BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree & sourceTree)
{
	//compare() = sourceTree.compare();
	this->BinaryTree::operator=(sourceTree);
	return *this;
}

BinaryNode* BinarySearchTree::_insert(BinaryNode* nodePtr, BinaryNode* newNodePtr)
{
	if (nodePtr == 0)
		return newNodePtr;
	if (compare(newNodePtr->getItem(), nodePtr->getItem()) == -1)
		nodePtr->setLeftPtr(_insert(nodePtr->getLeftPtr(), newNodePtr));
	else
		nodePtr->setRightPtr(_insert(nodePtr->getRightPtr(), newNodePtr));
	return nodePtr;
}

BinaryNode* BinarySearchTree::_remove(BinaryNode* nodePtr, void* target, bool & success)
{
	if (nodePtr == 0)
	{
		success = false;
		return 0;
	}
	if (compare(nodePtr->getItem(), target) == 1) //compare function
		nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
	else if (compare(nodePtr->getItem(), target) == -1) //compare function
		nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
	else	// found the node
	{
		nodePtr = deleteNode(nodePtr);
		success = true;
	}
	return nodePtr;
}

BinaryNode* BinarySearchTree::deleteNode(BinaryNode* nodePtr)
{
	if (nodePtr->isLeaf())
	{
		delete nodePtr;
		nodePtr = 0;
		return nodePtr;
	}
	else if (nodePtr->getLeftPtr() == 0)
	{
		BinaryNode* nodeToConnectPtr = nodePtr->getRightPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else if (nodePtr->getRightPtr() == 0)
	{
		BinaryNode* nodeToConnectPtr = nodePtr->getLeftPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else
	{
		void* newNodeValue = 0;
		nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
		nodePtr->setItem(newNodeValue);
		return nodePtr;
	}
}

BinaryNode* BinarySearchTree::removeLeftmostNode(BinaryNode* nodePtr, void* successor)
{
	if (nodePtr->getLeftPtr() == 0)
	{
		successor = nodePtr->getItem();
		return deleteNode(nodePtr);
	}
	else
	{
		nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
		return nodePtr;
	}
}

BinaryNode* BinarySearchTree::findNode(BinaryNode* nodePtr, void* target) const
{
	if (nodePtr == 0) //returns 0 when either tree is empty or target is not found
		return 0;
	else if (compare(nodePtr->getItem(), target) == -1) //recursive call to look for greater value
	{
		return findNode(nodePtr->getRightPtr(), target);
	}
	else if (compare(nodePtr->getItem(), target) == 1) //recursive call to look for smaller value
	{
		return findNode(nodePtr->getLeftPtr(), target);
	}
	else
		return nodePtr; //return ptr if found
}

// ---------------------- BinarySearchTree Class Implementation End -------------------------------