/*
Lab 6 - STL Containers and Algorithms
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This file includes the main application for this lab.

WARNING: Using the SpecializedPatientParser default initialization list
constructor results in near-100% use of the CPU. This is intended in order
to maximize speed by running a separate thread on each logical processor.
If this is undesirable for any reason, pass the SpecializedPatientParser
constructor "true" i.e.:

SpecializedPatientParser spp(dataFilename, numOfLinesInDataFile, true);

to halve the CPU usage of the multi-threaded parser.
*/

#include "SpecializedPatientParser.h"
#include "PatientDatabase.h"
#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

void testDatabase(PatientDatabase &pDB);

int main()
{
	// Variable declarations ---------------------------------------------
	const std::string dataFileName = "Patient.xml";
	const int numberOfLinesInDataFile = 100000;
	const std::string barcodeFile = "Barcodes.txt";
	PatientDatabase *pDB = PatientDatabase::getInstance(); // turn on patient database
	SpecializedPatientParser spp(dataFileName, numberOfLinesInDataFile);

	// Start program (and timer) -----------------------------------------
	clock_t begin = clock();

	cout << "Now parsing Patients from file...\n\n\n";
	if (!spp.specializedParse(*pDB))
	{
		cout << "Error: something went wrong while parsing the XML file!\n";
		return 1;
	}

	cout << "Now testing Patient database...\n\n\n";
	testDatabase(*pDB);

	// End program (and timer) and display statistics --------------------
	PatientDatabase::resetInstance(); // turn off patient database
	clock_t end = clock();
	cout << "\nElapsed time:\t" << double(end - begin) / CLOCKS_PER_SEC << endl;

	return 0;
}

void testDatabase(PatientDatabase &pDB)
{
	PatientHash *ph = pDB.getPatientHash();

	int pcount = 0;
	auto iter = ph->begin();
	auto end = ph->end();
	while (pcount++ < 5)
	{
		if (iter == end)
			break;

		cout << *iter->second << endl;
		++iter;
	}
}