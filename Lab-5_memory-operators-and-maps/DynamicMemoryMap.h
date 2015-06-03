/*
Lab 5 - Overloading dynamic memory operators and using STL maps
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This header file contains the class definition for DynamicMemoryMap, which maps
addresses to number of bytes allocated when allocating dynamic memory with
the global, overrided dynamic memory operators in Global.h.
*/

#ifndef MEMORY_MAP_H_
#define MEMORY_MAP_H_

#include <memory>
#include <map>

class DynamicMemoryMap : public std::map < void *, size_t >
{
private:
	static std::shared_ptr<DynamicMemoryMap> mmInstance;
protected:
	// protected constructor because this is a singleton class
	DynamicMemoryMap() {}
public:
	// get instance and check if instance exists methods
	static std::shared_ptr<DynamicMemoryMap> instance();
	static bool exists() { return (mmInstance != 0); }
};

// initialize static member instance later in instance()
std::shared_ptr<DynamicMemoryMap> DynamicMemoryMap::mmInstance = 0;

std::shared_ptr<DynamicMemoryMap> DynamicMemoryMap::instance()
{
	if (!mmInstance)
	{
		mmInstance = std::shared_ptr<DynamicMemoryMap>(new DynamicMemoryMap());
	}

	return mmInstance;
}

#endif // MEMORY_MAP_