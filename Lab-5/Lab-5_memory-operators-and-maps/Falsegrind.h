/*
Lab 5 - Overloading dynamic memory operators and using STL maps
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This header file is a pseudo-application of Falsegrind and has an instance
of Falsegrind, an API for accessing that instance, and finally the global
project definitions for the dynamic memory operator overloads.
*/

#ifndef FALSEGRIND_H_
#define FALSEGRIND_H_

#include "DynamicMemoryCounter.h"
#include "DynamicMemoryMap.h"
#include "FalsegrindClass.h"

/* This class serves as a basic API for the FalsegrindClass application,
encapsulating the FalsegrindClass so that it is used properly. Only the
dynamic memory operator overloads should have access to the FalsegrindClass
methods due to the nature of the application. */
class Falsegrind
{
private:
	static FalsegrindClass *fgrind;

	Falsegrind()  {} // private constructor/destructor because
	~Falsegrind() {} // this class only functions as an API

	friend void * operator new(size_t);   // these overloads are declared friends so that they can
	friend void * operator new[](size_t); // access the FalsegrindClass instance in this class
	friend void operator delete(void*);   // since no getter method is provided due to encapsulation
	friend void operator delete[](void*);
public:
	static void startFalsegrind()                  { fgrind = FalsegrindClass::instance(); }
	static void closeFalsegrind()                  { FalsegrindClass::resetInstance(); }
	static unsigned long getTotalAllocationCount() { return fgrind->getAllocationCount(); }
	static size_t getTotalBytesMapped()            { return fgrind->getTotalBytesMapped(); }
};

// static FalsegrindClass * instance is initialized only when startFalsegrind() is called
FalsegrindClass * Falsegrind::fgrind = 0;

void * operator new(size_t size)
{
	void *newPtr = malloc(size);

	if (FalsegrindClass::exists() &&                                      // check if fgrind instance exists
		(DynamicMemoryCounter::exists() && DynamicMemoryMap::exists()) && // check if fgrind components exist
		!Falsegrind::fgrind->isLockedForModification())                   // check if fgrind is not locked
	{
		Falsegrind::fgrind->addMappingAndIncrementAllocationCount(newPtr, size);
	}

	return newPtr;
}

void * operator new[](size_t size)
{
	void *newPtr = malloc(size);

	if (FalsegrindClass::exists() &&                                      // check if fgrind instance exists
		(DynamicMemoryCounter::exists() && DynamicMemoryMap::exists()) && // check if fgrind components exist
		!Falsegrind::fgrind->isLockedForModification())                   // check if fgrind is not locked
	{
		Falsegrind::fgrind->addMappingAndIncrementAllocationCount(newPtr, size);
	}

	return newPtr;
}

void operator delete(void *ptr)
{
	free(ptr);

	if (FalsegrindClass::exists() &&                                      // check if fgrind instance exists
		(DynamicMemoryCounter::exists() && DynamicMemoryMap::exists()) && // check if fgrind components exist
		!Falsegrind::fgrind->isLockedForModification())                   // check if fgrind is not locked
	{
		Falsegrind::fgrind->markMappingForDeleteAndDecrementAllocationCount(ptr);
	}
}

void operator delete[](void *ptr)
{
	free(ptr);

	if (FalsegrindClass::exists() &&                                      // check if fgrind instance exists
		(DynamicMemoryCounter::exists() && DynamicMemoryMap::exists()) && // check if fgrind components exist
		!Falsegrind::fgrind->isLockedForModification())                   // check if fgrind is not locked
	{
		Falsegrind::fgrind->markMappingForDeleteAndDecrementAllocationCount(ptr);
	}
}

#endif // FALSEGRIND_H_