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

#define aNumber int(1 << 3)
#define aBigNumber int(1 << 5)
#define aReallyBigNumber long(1 << 20)
#define RANDOM_LONG rand() % aReallyBigNumber + 1

void useNewAtLeastTenTimes(list <pair<long, long>**> &reallyLongList);
void useDeleteAtLeastTenTimes(list <pair<long, long>**> &reallyLongList);

int main()
{
	Falsegrind::startFalsegrind();            // start memory monitor application

	cout << "Creating a new list of type <pair<long, long>**>... ";
	list <pair<long, long>**> *reallyLongList = new list<pair<long, long>**>();
	cout << "Total dynamic memory allocations: " << Falsegrind::getTotalAllocationCount() << endl;

	useNewAtLeastTenTimes(*reallyLongList);
	useDeleteAtLeastTenTimes(*reallyLongList);

	cout << "Deleting list of type <pair<long, long>**>... ";
	delete reallyLongList;
	cout << "Total dynamic memory allocations: " << Falsegrind::getTotalAllocationCount() << endl << endl;

	cout << "Checking for memory leaks... " << (Falsegrind::getTotalAllocationCount() == 0 ? "No leak!" : "Memory leak.") << endl << endl;

	Falsegrind::closeFalsegrind();            // close memory monitor application

	return 0;
}

/* This method involves an unnecessarily complicated setup that eventually
 results in the new operator being used (aNumber * aBigNumber) times (see
 macros defined above). Why is the setup unnescessarily complicated, one
 might ask? Because I was bored, of course! */
void useNewAtLeastTenTimes(list<pair<long, long>**> &reallyLongList)
{
	cout << "Total number of dynamic memory allocations: " << Falsegrind::getTotalAllocationCount() << endl;
	cout << "Now starting test method for use of overloaded new/new[] operators ten or more times.\n\n";

	srand(time(0)); // seed RNG for random pairs of longs

	cout << "Inserting " << aNumber << " pair arrays of " << aBigNumber << " random pair<long, long> pointers each.\n\n";
	for (int i = 0; i < aNumber; i++)
	{
		cout << "Creating new pair array... ";
		pair<long, long> **newPair = new pair<long, long>*[aBigNumber]; // uses operator new[]
		cout << "Total number of dynamic memory allocations: " << Falsegrind::getTotalAllocationCount() << endl;
		for (int j = 0; j < aBigNumber; j++)
		{
			long rlong1, rlong2;
			cout << "Creating new random pair<long, long> pointer that holds " << (rlong1 = RANDOM_LONG) << " and " << (rlong2 = RANDOM_LONG);
			newPair[j] = new pair<long, long>(rlong1, rlong2);          // uses operator new
			cout << "... Total dynamic memory allocations: " << Falsegrind::getTotalAllocationCount() << endl;
		}
		reallyLongList.push_back(newPair);
		cout << endl;
	}

	cout << "\n\n\n\n";
}

/* See method description for useNewAtLeastTenTimes()
 but replace "new" with "delete". */
void useDeleteAtLeastTenTimes(list <pair<long, long>**> &reallyLongList)
{
	cout << "Total number of dynamic memory allocations: " << Falsegrind::getTotalAllocationCount() << endl;
	cout << "Now starting test method for use of overloaded delete/delete[] operators ten or more times.\n\n";

	cout << "Deleting " << aNumber << " pair arrays of " << aBigNumber << " random pair<long, long> pointers each.\n\n";
	for (auto i = reallyLongList.begin(); i != reallyLongList.end(); i++)
	{
		cout << "Deleting individual pair<long, long> pointers in pair array...\n";
		for (int j = 0; j < aBigNumber; j++)
		{
			delete (*i)[j]; // uses operator delete
			cout << "Deleted a pair<long, long> pointer. Total dynamic memory allocations: " << Falsegrind::getTotalAllocationCount() << endl;
		}
		delete[] (*i);      // uses operator delete[]
		cout << "Deleted a pair array from the list. Total dynamic memory allocations: " << Falsegrind::getTotalAllocationCount() << endl << endl;
	}

	cout << "\n\n\n\n";
}