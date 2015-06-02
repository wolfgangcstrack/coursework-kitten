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
#include <memory>
#include <map>

class Falsegrind : public DynamicMemoryCounter
{
protected:
	std::map<void *, size_t> memory_map;

	static std::shared_ptr<Falsegrind> fgInstance;

	// protected constructor because this is a singleton class
	Falsegrind();
public:
	static std::shared_ptr<Falsegrind> instance();
	static bool exists() { return (fgInstance != 0); }
	// getters/setters
	const std::map<void *, size_t> & get_memory_map() const { return memory_map; }
	bool insertAddressBytePairToMemoryMap(std::pair<void *, size_t> abPair);
	bool removeAddressBytePairFromMemoryMap(void *address);
	void incrementAllocationCount();
};

#endif // FALSEGRIND_H_