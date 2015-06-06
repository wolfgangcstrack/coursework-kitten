/*
Lab 5 - Overloading dynamic memory operators and using STL maps
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This header file has global project definitions for the dynamic memory
operator overloads.
*/

/* NOTES
- have at least 10 new/delete statements
- report number of bytes leaking
- delete map nodes after program to avoid rebalancing inefficiency
*/

#ifndef GLOBAL_DEFS_H_
#define GLOBAL_DEFS_H_

#include "DynamicMemoryCounter.h"
#include "DynamicMemoryMap.h"
#include "Falsegrind.h"
#include <iostream>
#include <memory>

Falsegrind *fgrind = Falsegrind::instance();

void * operator new(size_t size)
{
	void *newPtr = malloc(size);

	if (fgrind && fgrind->componentsExist() && !fgrind->isLockedForModification()) // increment only if fgrind exists
	{
		fgrind->incrementAllocationCount();
		fgrind->addMemoryMapping(newPtr, size);
	}

	return newPtr;
}

void * operator new[](size_t size)
{
	void *newPtr = malloc(size);

	if (fgrind && fgrind->componentsExist() && !fgrind->isLockedForModification()) // increment only if fgrind exists
	{
		fgrind->incrementAllocationCount();
		fgrind->addMemoryMapping(newPtr, size);
	}

	return newPtr;
}

void operator delete(void *ptr)
{
	if (fgrind && fgrind->componentsExist() && !fgrind->isLockedForModification()) // decrement only if fgrind exists
	{
		fgrind->decrementAllocationCount();
		fgrind->markMappingForDelete(ptr);
	}

	free(ptr);
}

void operator delete[](void *ptr)
{
	if (fgrind && fgrind->componentsExist() && !fgrind->isLockedForModification()) // decrement only if fgrind exists
	{
		fgrind->decrementAllocationCount();
		fgrind->markMappingForDelete(ptr);
	}

	free(ptr);
}

#endif // GLOBAL_DEFS_H_