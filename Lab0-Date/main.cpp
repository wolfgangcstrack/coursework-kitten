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
#include <string>
using namespace std;

// opens input file for reading, returns false if file does not open correctly
bool openInputFile(ifstream &ifs);
// reads from file and tests all overloaded operators of Date
void testDate(ifstream &ifs, vector<string> &operands, Date &date);

int main()
{
	cout << "This is a demonstration of the Date class.\n";
	vector<string> operands;
	Date date(2015, 4, 3); // date chosen matches assignment instructions


	ifstream ifs;
	if (!openInputFile(ifs))
	{
		cout << "Error, file not found" << endl;
		return -1;
	}

	testDate(ifs, operands, date);

	return 0;
}

bool openInputFile(ifstream &ifs)
{
	string filename;
	cout << "Please enter filename to read from: ";
	getline(cin, filename);
	ifs.open(filename);
	return ifs.is_open();
}

void testDate(ifstream &ifs, vector<string> &operands, Date &date)
{
	string temp; // used for retrieving input and converting operands
	int offset = 0, multiplier = 0;
	long operand = 0;

	while (getline(ifs, temp))
		operands.push_back(temp);

	cout << "\nTesting operator= overload of Date class..." << endl;
	cout << "The date is " << date << endl;
	cout << "Now assigning that date to a storage copy...Storage copy date is ";
	Date copy = date;
	cout << copy << endl;

	cout << "\nTesting operator overloads += and + of Date class..." << endl;
	cout << "Now adding to the date " << date << " and the second date (storage copy) " << copy << endl;
	for (int i = 0; i < operands.size(); i++)
	{
		temp = operands[i];
		multiplier = stoi(temp.substr(0, temp.length() - 1));
		/*
		switch (temp.back())
		{
		case 'Y':
			for (int j = 0; j < multiplier; j++)
			{
				if ()
			}
			copy += offset;
			break;
		case 'M':
			for (int j = 0; j < multiplier; j++)
			{
				offset = Date::getDaysOfMonth(copy.getYear(), copy.getMonth());
				operand += offset;
				copy += offset;
			}
			break;
		case 'D':
			operand += multiplier;
			break;
		}
		*/
	}
}