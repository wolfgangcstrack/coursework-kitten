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

namespace Lab5Global
{
	std::shared_ptr<DynamicMemoryCounter> dmc = DynamicMemoryCounter::instance();
}

void * operator new(size_t size)
{
	if (Lab5Global::dmc) // increment only if dmc exists
	{
		Lab5Global::dmc->incrementAllocationCount();
	}

	return malloc(size);
}

void * operator new[](size_t size)
{
	if (Lab5Global::dmc) // increment only if dmc exists
	{
		Lab5Global::dmc->incrementAllocationCount();
	}

	return malloc(size);
}

void operator delete(void *ptr)
{
	if (Lab5Global::dmc) // decrement only if dmc exists
	{
		Lab5Global::dmc->decrementAllocationCount();
	}

	free(ptr);
}

void operator delete[](void *ptr)
{
	if (Lab5Global::dmc) // decrement only if dmc exists
	{
		Lab5Global::dmc->decrementAllocationCount();
	}

	free(ptr);
}

#endif // GLOBAL_DEFS_H_