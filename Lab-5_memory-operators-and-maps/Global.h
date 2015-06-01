/*
Lab 5 - Overloading dynamic memory operators and using STL maps
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This header file has global project definitions for the dynamic memory
operator overloads.
*/

#ifndef GLOBAL_DEFS_H_
#define GLOBAL_DEFS_H_

namespace Lab5Global
{
	void * operator new(size_t);
	void * operator new[](size_t);
	void operator delete(void *);
	void operator delete[](void *);
}

#endif // GLOBAL_DEFS_H_