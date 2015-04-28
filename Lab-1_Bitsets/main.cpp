/*
Lab 1 - Bitsets and Vectors
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This is the driver application for Lab 1.
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
	bitset<8> bs('Q');
	cout << bs << endl;
	
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