/*
Manager: Louis Christopher

This file includes the implementation for:
- HashSC class
*/

#pragma once

#include "Global.h"
#include "SAList.h"

// ---------------------- HashSC Class Interface --------------------------------------------------
// HashSC class
// Derived class of abstract HashTable
/* Modifications (besides assignment specifications):
- uses SAList (self-adjusting list) instead of List
- mLists is now a pointer to an array of SAList pointers
- all SALists in mLists are now dynamically allocated pointers
- all functions change accordingly to work with pointers to SAList
- wrote display() and write() functions
*/

template<class Object>
class HashSC : public HashTable<Object>
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
		int(*comp)(const Object &left, const Object &right),
		int tableSize = INIT_TABLE_SIZE);
	// destructor
	~HashSC();

	bool find(const string & hashkey);
	bool contains(const Object & x) const;								// calls SAList adjust() function
	bool getEntry(const Object & target, Object & returnedItem) const;	// calls SAList adjust() function
	void makeEmpty();
	bool insert(const Object & x);
	bool remove(const Object & x);
	static long nextPrime(long n);
	int size() const { return mSize; }
	bool setMaxLambda(float lm);

	void displayStatistics() const;
	void display(ostream& os);
	void write(ostream& os);
private:
	void rehash();
	int myHash(const Object & x) const;
};
// ---------------------- HashSC Class Interface End ----------------------------------------------

// ---------------------- HashSC Class Implementation -----------------------------------------
// - Initialize Static Variables ----------------
template<class Object>
const float HashSC<Object>::INIT_MAX_LAMBDA = 1.5;

template<class Object>
int HashSC<Object>::longestList = 0;

template<class Object>
long HashSC<Object>::numCollisions = 0;
// - Initialize Static Variables End ------------

// - HashSC Method Definitions ------------------
template<class Object>
bool find(const string & hashkey)
{
	int hashVal = Hash(x) % mTableSize;
	if (hashVal < 0)
		hashVal += mTableSize;

	SAList<Object>* theList = mLists[hashVal];
}

template<class Object>
HashSC<Object>::HashSC(int(*hashFcn)(const Object &obj),
	int(*comp)(const Object &left, const Object &right),
	int tableSize)
	: HashTable(hashFcn, comp), mSize(0)
{
	if (tableSize < INIT_TABLE_SIZE)
		mTableSize = INIT_TABLE_SIZE;
	else
		mTableSize = nextPrime(tableSize);

	mLists = new SAList<Object>*[mTableSize];
	for (int i = 0; i < mTableSize; i++)
		mLists[i] = new SAList<Object>();

	mMaxLambda = INIT_MAX_LAMBDA;
}

template<class Object>
HashSC<Object>::~HashSC()
{
	for (int i = 0; i < mTableSize; ++i)
		delete mLists[i];
	delete[] mLists;
}

template<class Object>
void HashSC<Object>::displayStatistics() const
{
	SAList<Object>* list;
	int nonempty_lists = 0;

	cout << "Load Factor = " << (double)mSize / mTableSize
		<< "\nLongest Linked List = " << longestList
		<< "\nAverage number of nodes in each non-empty list = ";

	for (int i = 0; i < mTableSize; i++)
	{
		list = mLists[i];
		if (!list->isEmpty())
			nonempty_lists++;
	}

	cout << (double)mSize / nonempty_lists << endl;
}

template<class Object>
void HashSC<Object>::display(ostream& os)
{
	for (int i = 0; i < mTableSize; i++)
	{
		if (mLists[i]->size() > 0)
			mLists[i]->display(os);
		else
			os << "<EMPTY LIST>";
		os << endl;
	}
}

template<class Object>
void HashSC<Object>::write(ostream& os)
{
	for (int i = 0; i < mTableSize; i++)
	{
		if (mLists[i]->size() > 0)
			mLists[i]->write(os);
	}
}

template<class Object>
int HashSC<Object>::myHash(const Object & x) const
{
	int hashVal;

	hashVal = Hash(x) % mTableSize;
	if (hashVal < 0)
		hashVal += mTableSize;

	return hashVal;
}

template<class Object>
void HashSC<Object>::makeEmpty()
{
	int k;

	for (k = 0; k < mTableSize; k++)
		mLists[k]->clear();
	mSize = 0;
}

template<class Object>
bool HashSC<Object>::contains(const Object & x) const
{
	SAList<Object> * theList = mLists[myHash(x)];
	Object tempObj;

	for (int i = 0; i < theList->size(); i++)
	{
		// if getEntry() is successful and tempObj equals x by arbitrary Compare()
		if (theList->getEntry((i + 1), tempObj) && this->Compare(tempObj, x) == 0)
		{
			theList->adjust(i + 1); // element has been accessed, adjust list accordingly
			return true;
		}
	}

	// not found
	return false;
}

template<class Object>
bool HashSC<Object>::getEntry(const Object & target, Object & returnedItem) const
{
	SAList<Object> *theList = mLists[myHash(target)];
	Object tempObj;

	for (int i = 0; i < theList->size(); i++)
	{
		// if getEntry() is successful and tempObj equals target by arbitrary Compare()
		if (theList->getEntry((i + 1), tempObj) && this->Compare(tempObj, target) == 0)
		{
			theList->adjust(i + 1);
			returnedItem = tempObj;
			return true;
		}
	}

	// not found
	return false;
}

template<class Object>
bool HashSC<Object>::remove(const Object & x)
{
	SAList<Object> *theList = mLists[myHash(x)];
	Object tempObj;

	for (int i = 0; i < theList->size(); i++)
	{
		// if getEntry() is successful and tempObj equals x by arbitrary Compare()
		if (theList->getEntry((i + 1), tempObj) && this->Compare(tempObj, x) == 0)
		{
			theList->remove(i + 1);
			mSize--;
			return true;
		}
	}

	// not found
	return false;
}

template<class Object>
bool HashSC<Object>::insert(const Object & x)
{
	SAList<Object> *theList = mLists[myHash(x)];
	int listSize = theList->size();
	Object tempObj;

	for (int i = 0; i < listSize; i++)
	{
		// if getEntry() is successful and tempObj equals x by arbitrary Compare()
		if (theList->getEntry((i + 1), tempObj) && this->Compare(tempObj, x) == 0)
			return false;
	}

	// not found so we insert at the beginning
	theList->insert(x);

	// update statistics
	if (++listSize > 1)
		numCollisions++;
	if (listSize > longestList)
		longestList++;

	// check load factor
	if (++mSize > mMaxLambda * mTableSize)
		rehash();

	return true;
}

template<class Object>
void HashSC<Object>::rehash()
{
	SAList<Object> **oldLists = mLists;
	int k, oldTableSize = mTableSize;
	SAList<Object> *currList;
	Object tempObj;

	mTableSize = nextPrime(2 * oldTableSize);
	mLists = new SAList<Object>*[mTableSize];
	for (int i = 0; i < mTableSize; i++)
		mLists[i] = new SAList<Object>();

	mSize = 0;
	for (k = 0; k < oldTableSize; k++)
	{
		currList = &*(oldLists[k]);
		for (int i = 0; i < currList->size(); ++i)
		{
			currList->getEntry((i + 1), tempObj);
			insert(tempObj);
		}

	}

	for (int i = 0; i < oldTableSize; ++i)
		delete oldLists[i];
	delete[] oldLists;
}

template<class Object>
bool HashSC<Object>::setMaxLambda(float lam)
{
	if (lam < .1 || lam > 100)
		return false;
	mMaxLambda = lam;
	return true;
}

template<class Object>
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
// - HashSC Method Definitions End --------------
// ---------------------- HashSC Class Implementation End -------------------------------------