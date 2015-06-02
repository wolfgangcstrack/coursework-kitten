/*
Lab 5 - Overloading dynamic memory operators and using STL maps
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This header file contains the class definition for MemoryMap, which maps
addresses to number of bytes allocated when allocating dynamic memory with
the global, overrided dynamic memory operators in Global.h.
*/

#ifndef MEMORY_MAP_H_
#define MEMORY_MAP_H_

#include <memory>
#include <map>

class MemoryMap : std::map < void *, size_t >
{
private:
	static std::shared_ptr<MemoryMap> mmInstance;
protected:
	MemoryMap() {}
public:
	// get instance and check if instance exists methods
	static std::shared_ptr<MemoryMap> instance();
	static bool exists() { return (mmInstance != 0); }
};

std::shared_ptr<MemoryMap> MemoryMap::mmInstance = 0;

std::shared_ptr<MemoryMap> MemoryMap::instance()
{
	if (!mmInstance)
	{
		mmInstance = std::shared_ptr<MemoryMap>(new MemoryMap());
	}

	return mmInstance;
}

#endif // MEMORY_MAP_