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
	cout << "Initializing vector...\n\n";
	vector<pair<long, long>> *randomLongs = new vector<pair<long, long>>();
	Falsegrind::printAllocationCount(cout);

	cout << "Seeding random number generator...\n\n";
	srand(time(0));
	Falsegrind::printAllocationCount(cout);

	cout << "Inserting 100 pair pointers of random longs to the vector...\n\n";
	for (int i = 0; i < 100; i++)
	{
		pair<long, long> randPair(rand() % aReallyBigNumber + 1, rand() % aReallyBigNumber + 1);
		cout << "Inserting " << randPair.first << " and " << randPair.second << endl;
		randomLongs->push_back(randPair);
		Falsegrind::printAllocationCount(cout);
	}

	Falsegrind::printAllocationCount(cout);

	randomLongs->clear();
	delete randomLongs;
	Falsegrind::printAllocationCount(cout);
	Falsegrind::closeFalsegrind();
	return 0;
}