/*
Lab 5 - Overloading dynamic memory operators and using STL maps
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This header file is a pseudo-application of Falsegrind and has an instance
of Falsegrind, an API for accessing that instance, and finally the global
project definitions for the dynamic memory operator overloads.
*/

/* NOTES
- have at least 10 new/delete statements
- report number of bytes leaking
- delete map nodes after program to avoid rebalancing inefficiency
*/

#ifndef FALSEGRIND_H_
#define FALSEGRIND_H_

#include "DynamicMemoryCounter.h"
#include "DynamicMemoryMap.h"
#include "FalsegrindClass.h"
#include <iostream>
#include <string>
#include <memory>

namespace Falsegrind
{
	FalsegrindClass *fgrind = 0;

	void startFalsegrind()                      { fgrind = FalsegrindClass::instance(); }
	void closeFalsegrind()                      { FalsegrindClass::resetInstance(); }
	unsigned long getTotalAllocationCount()     { return fgrind->getAllocationCount(); }
	unsigned long getTotalBytesMapped()         { return fgrind->getTotalBytesMapped(); }
}

void * operator new(size_t size)
{
	void *newPtr = malloc(size);

	if (FalsegrindClass::exists() &&                                      // check if fgrind instance exists
		(DynamicMemoryCounter::exists() && DynamicMemoryMap::exists()) && // check if fgrind components exist
		!Falsegrind::fgrind->isLockedForModification())                   // check if fgrind is not locked
	{
		Falsegrind::fgrind->incrementAllocationCount();
		Falsegrind::fgrind->addMemoryMapping(newPtr, size);
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
		Falsegrind::fgrind->incrementAllocationCount();
		Falsegrind::fgrind->addMemoryMapping(newPtr, size);
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
		Falsegrind::fgrind->decrementAllocationCount();
		Falsegrind::fgrind->markMappingForDelete(ptr);
	}
}

void operator delete[](void *ptr)
{
	free(ptr);

	if (FalsegrindClass::exists() &&                                      // check if fgrind instance exists
		(DynamicMemoryCounter::exists() && DynamicMemoryMap::exists()) && // check if fgrind components exist
		!Falsegrind::fgrind->isLockedForModification())                   // check if fgrind is not locked
	{
		Falsegrind::fgrind->decrementAllocationCount();
		Falsegrind::fgrind->markMappingForDelete(ptr);
	}
}

#endif // FALSEGRIND_H_