/*
Lab 5 - Overloading dynamic memory operators and using STL maps
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This header file contains the class definition of the base class that will
monitor dynamic memory allocation in the project.
*/

#ifndef DYNAMIC_MEMORY_COUNTER_H_
#define DYNAMIC_MEMORY_COUNTER_H_

#include <memory>

class DynamicMemoryCounter
{
private:
	int allocationCounter;
protected:
	DynamicMemoryCounter()          { allocationCounter = 0; }
	//virtual ~DynamicMemoryCounter() {}
	static std::shared_ptr<DynamicMemoryCounter> dmcInstance;
	//static DynamicMemoryCounter *dmcInstance;
public:
	static std::shared_ptr<DynamicMemoryCounter> instance();
	static bool exists()            { return (dmcInstance != 0); }
	int getAllocationCount() const  { return allocationCounter; }
	void incrementAllocationCount() { ++allocationCounter; }
	void decrementAllocationCount() { --allocationCounter; }

	// overload the overloaded global dynamic memory operators
	inline void * operator new(size_t dmc_size){ return malloc(dmc_size); };
	inline void operator delete(void *dmc_ptr) { free(dmc_ptr); }
};

std::shared_ptr<DynamicMemoryCounter> DynamicMemoryCounter::dmcInstance = 0;

std::shared_ptr<DynamicMemoryCounter> DynamicMemoryCounter::instance()
{
	if (!dmcInstance)
	{
		dmcInstance = std::shared_ptr<DynamicMemoryCounter>(new DynamicMemoryCounter());
	}

	return dmcInstance;
}

#endif // DYNAMIC_MEMORY_COUNTER_H_