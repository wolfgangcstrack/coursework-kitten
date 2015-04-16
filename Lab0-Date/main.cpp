/*
Lab 0 - Variant #3 (Date arithmetic)
Wolfgang C. Strack
16 April 2015
Windows 8 Visual C++ 2013

This is the driver application for Lab 0.
This is also where file IO is handled in order for the correct
value to be used when operating on a Date object. This is 
because the Date::operator(+=, -=, ++, -, etc.) takes a
parameter of type long which can only represent number of days.
*/

#include "Date.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

bool openInputFile(ifstream &ifs);
bool readOperands(vector<long> operands);

int main()
{
	cout << "This is a demonstration of the Date class.\n";

	return 0;
}