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
	list <pair<long, long>**> reallyLongList;

	Falsegrind::startFalsegrind();            // start memory monitor application

	useNewAtLeastTenTimes(reallyLongList);
	useDeleteAtLeastTenTimes(reallyLongList);

	Falsegrind::closeFalsegrind();            // close memory monitor application

	return 0;
}

void useNewAtLeastTenTimes(list<pair<long, long>**> &reallyLongList)
{
	cout << "Total number of dynamic memory allocations: " << Falsegrind::getTotalAllocationCount() << "\n\n";

	srand(time(0));

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
			newPair[j] = new pair<long, long>(rlong1, rlong2);
			cout << "... Total dynamic memory allocations: " << Falsegrind::getTotalAllocationCount() << endl;
		}
		reallyLongList.push_back(newPair);
		cout << endl;
	}
}