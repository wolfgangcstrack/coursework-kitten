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
	static DynamicMemoryCounter *dmcInstance;
protected:
	long allocationCounter;

	// protected constructor because this is a singleton class
	DynamicMemoryCounter()                  { allocationCounter = 0; }
	// protected destructor forces user to call resetInstance(),
	// the proper way of deleting this class
	~DynamicMemoryCounter()                 {}
public:
	// get/reset instance and check if instance exists methods
	static DynamicMemoryCounter * instance();
	static void resetInstance()             { delete dmcInstance; dmcInstance = 0; }
	static bool exists()                    { return (dmcInstance != 0); }
	// get/set instance data
	virtual long getAllocationCount() const { return allocationCounter; }
	virtual void incrementAllocationCount() { ++allocationCounter; }
	virtual void decrementAllocationCount() { --allocationCounter; }
};

// initialize static member instance later in instance()
DynamicMemoryCounter * DynamicMemoryCounter::dmcInstance = 0;

DynamicMemoryCounter * DynamicMemoryCounter::instance()
{
	if (!dmcInstance)
	{
		dmcInstance = new DynamicMemoryCounter();
	}

	return dmcInstance;
}

#endif // DYNAMIC_MEMORY_COUNTER_H_