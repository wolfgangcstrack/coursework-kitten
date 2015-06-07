/*
Lab 5 - Overloading dynamic memory operators and using STL maps
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This file contains the main application for this lab.
*/

#include "Falsegrind.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <list>
using namespace std;

#define aNumber int(1 << 5)
#define aBigNumber int(1 << 10)
#define aReallyBigNumber long(1 << 20)

//void useNewAtLeastTenTimes(list<list<pair<long, long>*>*> &reallyLongList);
//void useDeleteAtLeastTenTimes(list<list<pair<long, long>*>*> &reallyLongList);

int main()
{
	//list <list<pair<long, long>*>*> reallyLongList;

	//Falsegrind::startFalsegrind();            // start memory monitor application

	//useNewAtLeastTenTimes(reallyLongList);
	//useDeleteAtLeastTenTimes(reallyLongList);

	//Falsegrind::closeFalsegrind();            // close memory monitor application

	//return 0;
}

void useNewAtLeastTenTimes(list<list<pair<long, long>>> &reallyLongList)
{
	/*Falsegrind::printAllocationCount(cout);
	cout << "Inserting " << aNumber << " list pointers of " << aBigNumber << " random pair<long, long> pointers each.\n\n"
	for (int i = 0; i < )*/
}