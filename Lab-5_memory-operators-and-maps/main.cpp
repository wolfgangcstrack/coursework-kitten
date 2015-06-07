/*
Lab 5 - Overloading dynamic memory operators and using STL maps
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This file contains the main application for this lab.
*/

#include "Falsegrind.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
using namespace std;

#define aReallyBigNumber long(1 << 20)

int main()
{
	Falsegrind::startFalsegrind();
	Falsegrind::printAllocationCount(cout);
	int *doge = new int(7);
	Falsegrind::printAllocationCount(cout);
	delete doge;
	Falsegrind::printAllocationCount(cout);
	Falsegrind::closeFalsegrind();
	return 0;
}