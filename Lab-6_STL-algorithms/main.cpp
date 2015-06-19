/*
Lab 6 - STL Containers and Algorithms
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This file includes the main application for this lab.
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
	const std::string dataFile = "Patient.xml";
	const std::string barcodeFile = "Barcodes.txt";
	PatientDatabase *pDB = PatientDatabase::getInstance(); // turn on patient database
	SpecializedPatientParser spp;

	// Start program (and timer) -----------------------------------------
	clock_t begin = clock();

	cout << "Now parsing Patients from file...\n\n\n";
	if (!spp.specializedParse(dataFile, *pDB))
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
	while (pcount++ < 10)
	{
		if (iter == end)
			break;

		cout << *iter->second << endl;
		++iter;
	}
}