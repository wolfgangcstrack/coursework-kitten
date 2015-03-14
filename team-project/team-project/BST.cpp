/*
Manager: Andrew Wang

This file includes the implementation for:
BinaryTree class
BinarySearchTree class
*/

#include "Global.h"

// ---------------------- BinaryNode Class Implementation -----------------------------------------

class BinaryNode
{
private:
	void *             item;         // Data portion
	BinaryNode* leftPtr;		// Pointer to left child 
	BinaryNode* rightPtr;		// Pointer to right child

public:
	// constructors
	BinaryNode(void* anItem)			   { item = anItem; leftPtr = 0; rightPtr = 0; }
	BinaryNode(void* anItem, BinaryNode* left, BinaryNode* right)		 { item = anItem; leftPtr = left; rightPtr = right; }
	// accessors
	void setItem(void* anItem)		   { item = anItem; }
	void setLeftPtr(BinaryNode* left)	   { leftPtr = left; }
	void setRightPtr(BinaryNode* right)  { rightPtr = right; }
	// mutators
	void* getItem() const					   { return item; }
	BinaryNode* getLeftPtr() const	   { return leftPtr; }
	BinaryNode* getRightPtr() const	   { return rightPtr; }

	bool isLeaf() const							   { return (leftPtr == 0 && rightPtr == 0); }
};

// ---------------------- BinaryNode Class Implementation End -------------------------------------


// ---------------------- BinaryTree Class Implementation -----------------------------------------

class BinaryTree
{
protected:
	BinaryNode* rootPtr;		// ptr to root node
	int count;							// number of nodes in tree
	// copy from the tree rooted at nodePtr and returns a pointer to the copy
	BinaryNode* copyTree(const BinaryNode* nodePtr);

public:
	// "admin" functions
	BinaryTree()					{ rootPtr = 0; count = 0; }
	BinaryTree(const BinaryTree& tree) { if (this->rootPtr != 0) clear(); this->rootPtr = copyTree(tree.rootPtr); }// see assignment
	virtual ~BinaryTree()				{ clear(); }// CALL clear()		
	BinaryTree & operator=(const BinaryTree & sourceTree);

	// common functions for all binary trees
	bool isEmpty() const				{ return count == 0; }
	int size() const					{ return count; }
	void clear(){ destroyTree(rootPtr); rootPtr = 0; count = 0; }
	void inOrder(void visit(void*)) const		{ _inorder(visit, rootPtr); }

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
		void* newNodeValue;
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


int BinarySearchTree::compare(void* a, void* b) const
{

}

// ---------------------- BinarySearchTree Class Implementation End -------------------------------