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

	cout << "Now parsing Patients from \"Patient.xml\"...\n\n\n";
	if (!spp.specializedParse(*pDB))
	{
		cout << "Error: something went wrong while parsing the XML file!\n";
		return 1;
	}

	cout << "Now accessing Patient database with barcodes from \"Barcodes.txt\"...\n";
	cout << "NOTE: Output suppressed for speed\n\n\n";
	if (!testDatabase(barcodeFile, *pDB))
	{
		cout << "Error: something went wrong while accessing the patient database!\n";
		return 2;
	}
	cout << "Patient database access successful!\n\n\n";

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
	Patient nullPatient;
	while (getline(ifs, line))
	{
		Patient patient = *phash->find(bitset<15>(line))->second;
		if (patient == nullPatient)
		{
			cout << "ERROR: Patient with code " << line << " unable to be retrieved\n";
			return false;
		}

		/* NOTE:
		The following statement below is commented out because they increase the time it takes for the program
		to complete. An unsuccessful access will result in the error message above and the program will
		exit. In my opinion, using this system makes up for not printing out the actual patient data.
		
		However, if so desired, feel free to uncomment the statement below to see that the program does, in fact,
		parse the and capture the data correctly.
		*/
		//cout << "Patient with code " << line << ":\n" << patient << endl; // uncommenting this adds about 30 seconds on my test machine
	}

	return true;
}