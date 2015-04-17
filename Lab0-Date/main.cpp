/*
Lab 0 - Variant #3 (Date arithmetic)
Wolfgang C. Strack
16 April 2015
Windows 8 Visual C++ 2013

This is the driver application for Lab 0. It tests
the Date class with assignment, addition, subtraction,
and relational operations.

Note: Sample execution results appended to the end of this file.
*/

#include "Date.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// opens input file for reading, returns false if file does not open correctly
bool openInputFile(ifstream &ifs);
// reads from file and thoroughly tests the date class
void testDate(ifstream &ifs, vector<string> &operands, Date &date);

int main()
{
	cout << "This is a demonstration of the Date class.\n" << endl;
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
	int num = 0; // holds the number of days/months/years that the input file gives

	while (getline(ifs, temp))
		operands.push_back(temp);
	temp.clear();

	cout << "\n\nTesting assignment operation of Date class..." << endl;
	cout << "\nThe date is " << date << endl << endl;
	cout << "Now assigning that date to a storage copy: Date copy = date" << endl;
	Date copy = date;
	cout << "The storage copy date is " << copy << endl;

	cout << "\n\nTesting addition operations of Date class..." << endl;
	cout << "\nNow adding to the date " << date << endl << endl;
	for (int i = 0; i < operands.size(); i++)
	{
		copy = date; // reset for next operand/test
		temp = operands[i];
		num = stoi(temp.substr(0, temp.length() - 1));
		switch (temp.back())
		{
		case 'Y':
			copy.addYears(num);
			break;
		case 'M':
			copy.addMonths(num);
			break;
		case 'D':
			copy.addDays(num);
			break;
		default:
			cout << "Error in input file at line " << i + 1 << endl;
			return;
		}
		cout << date << " + " << temp << " = " << copy << endl;
	}
	temp.clear(); // reset for next test
	num = 0;

	cout << "\n\nTesting subtraction operations of Date class..." << endl;
	cout << "\nNow subtracting from the date " << date << endl << endl;
	for (int i = 0; i < operands.size(); i++)
	{
		copy = date; // reset for next operand/test
		temp = operands[i];
		num = -stoi(temp.substr(0, temp.length() - 1)); // makes num negative when adding to the date
		switch (temp.back())
		{
		case 'Y':
			copy.addYears(num);
			break;
		case 'M':
			copy.addMonths(num);
			break;
		case 'D':
			copy.addDays(num);
			break;
		default:
			cout << "Error in input file at line " << i + 1 << endl;
			return;
		}
		cout << date << " - " << temp << " = " << copy << endl;
	}

	cout << "\n\nTesting relational operators of Date class..." << endl;
	cout << "\nDate 1 is " << date << " and date 2 is " << copy << endl << endl;
	cout << "Is " << date << " == " << copy << " ? Answer: " << (date == copy ? "true" : "false") << endl;
	cout << "Is " << date << " != " << copy << " ? Answer: " << (date != copy ? "true" : "false") << endl;
	cout << "Is " << date << " >= " << copy << " ? Answer: " << (date >= copy ? "true" : "false") << endl;
	cout << "Is " << date << " <= " << copy << " ? Answer: " << (date <= copy ? "true" : "false") << endl;
	cout << "Is " << date << " > " << copy << " ? Answer: " << (date > copy ? "true" : "false") << endl;
	cout << "Is " << date << " < " << copy << " ? Answer: " << (date < copy ? "true" : "false") << endl;

	cout << "\n\nThis concludes the demonstration of the Date class.\n" << endl;
}

/* EXECUTION RESULTS
This is a demonstration of the Date class.

Please enter filename to read from: input.txt


Testing assignment operation of Date class...

The date is 2015/04/03

Now assigning that date to a storage copy: Date copy = date
The storage copy date is 2015/04/03


Testing addition operations of Date class...

Now adding to the date 2015/04/03

2015/04/03 + 1Y = 2016/04/03
2015/04/03 + 12M = 2016/04/03
2015/04/03 + 365D = 2016/04/02
2015/04/03 + 366D = 2016/04/03
2015/04/03 + 5Y = 2020/04/03
2015/04/03 + 6M = 2015/10/03
2015/04/03 + 7D = 2015/04/10
2015/04/03 + 2000Y = 4015/04/03
2015/04/03 + 1M = 2015/05/03
2015/04/03 + 30D = 2015/05/03
2015/04/03 + 31D = 2015/05/04


Testing subtraction operations of Date class...

Now subtracting from the date 2015/04/03

2015/04/03 - 1Y = 2014/04/03
2015/04/03 - 12M = 2014/04/03
2015/04/03 - 365D = 2014/04/03
2015/04/03 - 366D = 2014/04/02
2015/04/03 - 5Y = 2010/04/03
2015/04/03 - 6M = 2014/10/03
2015/04/03 - 7D = 2015/03/27
2015/04/03 - 2000Y = 15/04/03
2015/04/03 - 1M = 2015/03/03
2015/04/03 - 30D = 2015/03/04
2015/04/03 - 31D = 2015/03/03


Testing relational operators of Date class...

Date 1 is 2015/04/03 and date 2 is 2015/03/03

Is 2015/04/03 == 2015/03/03 ? Answer: false
Is 2015/04/03 != 2015/03/03 ? Answer: true
Is 2015/04/03 >= 2015/03/03 ? Answer: true
Is 2015/04/03 <= 2015/03/03 ? Answer: false
Is 2015/04/03 > 2015/03/03 ? Answer: true
Is 2015/04/03 < 2015/03/03 ? Answer: false


This concludes the demonstration of the Date class.

Press any key to continue . . .
*/