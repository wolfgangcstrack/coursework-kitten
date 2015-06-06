/*
Lab 5 - Overloading dynamic memory operators and using STL maps
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This file contains the main application for this lab.
*/

#include "Global.h"
#include "Falsegrind.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
using namespace std;

#define aReallyBigNumber long(1 << 20)

int main()
{
	cout << "Initializing vector...\n\n";
	vector<pair<long, long>> *randomLongs = new vector<pair<long, long>>();
	cout << "Allocation count: " << fgrind->getAllocationCount() << "\n\n";

	cout << "Seeding random number generator...\n\n";
	srand(time(0));
	cout << "Allocation count: " << fgrind->getAllocationCount() << "\n\n";

	cout << "Inserting 100 pair pointers of random longs to the vector...\n\n";
	for (int i = 0; i < 100; i++)
	{
		pair<long, long> randPair(rand() % aReallyBigNumber + 1, rand() % aReallyBigNumber + 1);
		cout << "Inserting " << randPair.first << " and " << randPair.second << endl;
		randomLongs->push_back(randPair);
		cout << "Allocation count: " << fgrind->getAllocationCount() << endl;
	}

	cout << "\nTotal allocation count: " << fgrind->getAllocationCount() << "\n\n";

	randomLongs->clear();
	delete randomLongs;
	cout << "\nTotal allocation count: " << fgrind->getAllocationCount() << "\n\n";

	return 0;
}