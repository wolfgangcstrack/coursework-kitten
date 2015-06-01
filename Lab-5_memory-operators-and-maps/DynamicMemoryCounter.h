/*
Lab 5 - Overloading dynamic memory operators and using STL maps
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This header file contains the class definition of the base class that will
monitor dynamic memory allocation in the project.
*/

#ifndef DYNAMIC_MEMORY_COUNTER_H_
#define DYNAMIC_MEMORY_COUNTER_H_

class DynamicMemoryCounter
{
private:
	int allocationCounter;
protected:
	DynamicMemoryCounter();
	virtual ~DynamicMemoryCounter();
	static DynamicMemoryCounter *dmcInstance;
public:
	static DynamicMemoryCounter * instance();
	static bool exists();
	int getAllocationCount() const  { return allocationCounter; }
	void incrementAllocationCount() { ++allocationCounter; }
};

#endif // DYNAMIC_MEMORY_COUNTER_H_