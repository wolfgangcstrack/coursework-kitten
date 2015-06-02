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
	static std::shared_ptr<DynamicMemoryCounter> dmcInstance;
protected:
	int allocationCounter;

	// protected constructor because this is a singleton class
	DynamicMemoryCounter()                  { allocationCounter = 0; }
public:
	// get instance and check if instance exists methods
	static std::shared_ptr<DynamicMemoryCounter> instance();
	static bool exists()                    { return (dmcInstance != 0); }
	// get/set instance data
	virtual int getAllocationCount() const  { return allocationCounter; }
	virtual void incrementAllocationCount() { ++allocationCounter; }
	virtual void decrementAllocationCount() { --allocationCounter; }
};

// initialize static member instance later in instance()
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