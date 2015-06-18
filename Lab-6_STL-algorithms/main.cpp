/*
Lab 6 - STL Containers and Algorithms
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This file includes the main application for this lab.
*/

#include "PatientDatabase.h"
#include "XmlRegexIO.h"
#include <iostream>
#include <vector>
using namespace std;

bool populateDatabase(PatientDatabase *pDB, XmlRegexIO &xrio, const vector<string> &tags);
void testDatabase(PatientDatabase *pDB);

int main()
{
	// Variable declarations ---------------------------------------------
	const std::string dataFile = "Patient.xml";
	const std::string barcodeFile = "Barcodes.txt";
	PatientDatabase *pDB = PatientDatabase::getInstance();
	XmlRegexIO xrio("[0-9]*\\n<patient>(.|\\n)*?</patient>");
	vector<string> tags;

	// Start program (and timer) -----------------------------------------
	cout << "Now reading tags from file...\n\n\n";
	if (!xrio.getAllMatches(dataFile, tags))
	{
		cout << "Error: something went wrong while reading XML tags from file!\n";
		return 1;
	}

	cout << "Now populating Patient database...\n\n\n";
	if (!populateDatabase(pDB, xrio, tags))
	{
		cout << "Error: something went wrong while populating the Patient DB!\n";
		return 2;
	}

	cout << "Now testing Patient database...\n\n\n";
	testDatabase(pDB);

	// End program (and timer) and display statistics --------------------


	PatientDatabase::resetInstance();
	return 0;
}

bool populateDatabase(PatientDatabase *pDB, XmlRegexIO &xrio, const vector<string> &tags)
{
	for (int i = 0; i < tags.size(); i++)
	{
		Patient patient;
		patient.setXMLTags(tags[i]);

		if (!xrio.getXmlDataFromString(tags[i], patient))
			return false;

		if (!pDB->addPatient(patient))
			return false;
	}

	return true;
}

void testDatabase(PatientDatabase *pDB)
{
	cout << "TEST DATABASE STUB" << endl;
}