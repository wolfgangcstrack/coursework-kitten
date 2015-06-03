/*
Lab 5 - Overloading dynamic memory operators and using STL maps
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This header file contains the class definition of Falsegrind, the complete
dynamic memory manager for this lab. The name "Falsegrind" was chosen as a
play on the name "Valgrind," which is a legitimate, well-known programming
tool for memory debugging, leak detection, and profiling.
*/

#ifndef FALSEGRIND_H_
#define FALSEGRIND_H_

#include "DynamicMemoryCounter.h"
#include "DynamicMemoryMap.h"
#include <memory>

class Falsegrind
{
private:
	static std::shared_ptr<Falsegrind> fgInstance;
protected:
	std::shared_ptr<DynamicMemoryCounter> dm_count;
	std::shared_ptr<DynamicMemoryMap> dm_map;

	// protected constructor because this is a singleton class
	Falsegrind();
public:
	// get instance and check if instance exists methods
	static std::shared_ptr<Falsegrind> instance();
	static bool exists() { return (fgInstance != 0); }
	// DynamicMemoryCounter methods
	virtual int getAllocationCount() const  { return dm_count->getAllocationCount(); }
	virtual void incrementAllocationCount() { dm_count->incrementAllocationCount(); }
	virtual void decrementAllocationCount() { dm_count->decrementAllocationCount(); }
	// DynamicMemoryMap methods
	virtual size_t & getByteSize(void *address) { return (*dm_map)[address]; }
	virtual void addMemoryMapping(void *address, size_t byteSize);
	virtual void deleteMemoryMapping(void *address);

	//// friend methods
	//friend void * operator new(size_t);
	//friend void * operator new[](size_t);
	//friend void operator delete(void *);
	//friend void operator delete[](void *);
	// get/set instance data
	/*const std::map<void *, size_t> & get_memory_map() const { return memory_map; }
	bool insertAddressBytePairToMemoryMap(std::pair<void *, size_t> abPair);
	bool removeAddressBytePairFromMemoryMap(void *address);*/
};

// initialize static member instance later in instance()
std::shared_ptr<Falsegrind> Falsegrind::fgInstance = 0;

Falsegrind::Falsegrind()
{
	dm_count = DynamicMemoryCounter::instance();
	dm_map = DynamicMemoryMap::instance();
}

std::shared_ptr<Falsegrind> Falsegrind::instance()
{
	if (!fgInstance)
	{
		fgInstance = std::shared_ptr<Falsegrind>(new Falsegrind());
	}

	return fgInstance;
}

#endif // FALSEGRIND_H_