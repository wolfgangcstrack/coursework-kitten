/*
Lab 5 - Overloading dynamic memory operators and using STL maps
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This header file contains the class definition for DynamicMemoryMap, which maps
addresses to number of bytes allocated when allocating dynamic memory with
the global, overrided dynamic memory operators in Global.h.

The DynamicMemoryMap is a map<void *, pair<bool, size_t>>. The void* key
is the address returned by malloc(). The pair<bool, size_t> is as follows:
	- the bool is there for lazy-deletion support and is a flag for whether
	  the map node is active
	- the size_t value is the number of bytes allocated to the void* key.
*/

#ifndef MEMORY_MAP_H_
#define MEMORY_MAP_H_

#include <memory>
#include <map>

class DynamicMemoryMap : public std::map < void *, std::pair< bool, size_t > >
{
private:
	static DynamicMemoryMap *mmInstance;
protected:
	// protected constructor because this is a singleton class
	DynamicMemoryMap() {}
public:
	// get instance and check if instance exists methods
	static DynamicMemoryMap * instance();
	static bool exists() { return (mmInstance != 0); }
};

// initialize static member instance later in instance()
DynamicMemoryMap * DynamicMemoryMap::mmInstance = 0;

DynamicMemoryMap * DynamicMemoryMap::instance()
{
	if (!mmInstance)
	{
		mmInstance = new DynamicMemoryMap();
	}

	return mmInstance;
}

#endif // MEMORY_MAP_