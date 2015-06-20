/*
Lab 6 - STL Containers and Algorithms
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This file includes the main application for this lab.

WARNING: Using the SpecializedPatientParser default initialization list
constructor results in use of a large percentage of the CPU. This is
intended in order to maximize speed by running a separate thread on each
logical processor. If this is undesirable for any reason, pass the
SpecializedPatientParser constructor "true" i.e.:

SpecializedPatientParser spp(dataFilename, numOfLinesInDataFile, true);

to halve the CPU usage of the multi-threaded parser.
*/

#include "SpecializedPatientParser.h"
#include "PatientDatabase.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

bool testDatabase(const string &barcodeFile, PatientDatabase &pDB);

int main()
{
	// Variable declarations ---------------------------------------------
	const string dataFileName = "Patient.xml";
	const int numberOfLinesInDataFile = 100000;
	const string barcodeFile = "Barcodes.txt";
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
	if (!testDatabase(barcodeFile, *pDB))
	{
		cout << "Error: something went wrong while testing the patient database!\n";
		return 2;
	}

	// End program (and timer) and display statistics --------------------
	PatientDatabase::resetInstance(); // turn off patient database
	clock_t end = clock();
	cout << "\nElapsed time:\t" << double(end - begin) / CLOCKS_PER_SEC << endl;

	return 0;
}

bool testDatabase(const string &barcodeFile, PatientDatabase &pDB)
{
	ifstream ifs;
	ifs.open(barcodeFile);
	if (!ifs.is_open())
		return false;

	const PatientHash *phash = pDB.getPatientHash();

	string line;
	while (getline(ifs, line))
	{
		Patient nullPatient;
		Patient patient = *phash->find(bitset<15>(line))->second;
		if (patient == nullPatient)
			cout << "Patient with code " << line << " could not be retrieved." << endl;
		//cout << "Patient code: " << line << ", Name: " << p.getName() << endl;
		//cout << *phash->find(bitset<15>(line))->second << endl << endl;
		//cout << *pDB.getPatient(bitset<15>(line)) << endl << endl;
	}

	return true;
}