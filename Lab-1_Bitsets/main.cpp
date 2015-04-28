/*
Lab 1 - Bitsets and Vectors
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This is the driver application for Lab 1.

NOTE: Execution results included at the end of this file.
*/

#include "Lab1Decryptor.h"
#include "ANSIChar.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// opens input file for reading, returns false if file does not open correctly
bool openInputFile(ifstream &ifs);
void readANSI(ifstream &ifs, vector<ANSIChar> &acv);

int main()
{
	cout << "This is a demonstration of the Lab1Decryptor." << endl;
	Lab1Decryptor decryptor;
	vector<ANSIChar> acv;
	string decodedResult;

	ifstream ifs;
	if (!openInputFile(ifs))
	{
		cout << "Error, file not found" << endl;
		return -1;
	}

	readANSI(ifs, acv);
	decryptor.decrypt(acv, decodedResult);

	cout << "The decoded string is:\n\n";
	cout << decodedResult << endl;
	
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

void readANSI(ifstream &ifs, vector<ANSIChar> &acv)
{
	string temp = "";
	while (getline(ifs, temp))
	{
		
		for (int i = 0; i < temp.length(); i++)
		{
			acv.push_back(ANSIChar(temp[i]));
		}
	}
}

/* EXECUTION RESULTS
This is a demonstration of the Lab1Decryptor.
Please enter filename to read from: Morse.bin
The decoded string is:

M O R S E   C O D E   W A S   I N V E N T E D   B Y   S A M U E L   M O R S E   I N   1 8 4 3 .   T H E   L I N E   R A N   F R O M   W A S H I N G T O N   D . C .
T O   B A L T I M O R E ,   M A R Y L A
Press any key to continue . . .
*/