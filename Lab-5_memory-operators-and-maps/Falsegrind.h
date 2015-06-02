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

class Falsegrind
{
private:
	typedef DynamicMemoryCounter DMcount;

	std::map<void *, size_t> memory_map;
	std::shared_ptr<DMcount> dmcount;
	//DMcount *dmcount;
protected:
	Falsegrind();
	virtual ~Falsegrind();
	static std::shared_ptr<Falsegrind> fgInstance;
public:
	static std::shared_ptr<Falsegrind> instance();
	static bool exists();
	// getters/setters
	const std::map<void *, size_t> & get_memory_map() const { return memory_map; }
	int getAllocationCount() const;
	bool insertAddressBytePairToMemoryMap(std::pair<void *, size_t> abPair);
	bool removeAddressBytePairFromMemoryMap(void *address);
	void incrementAllocationCount();
};

#endif // FALSEGRIND_H_