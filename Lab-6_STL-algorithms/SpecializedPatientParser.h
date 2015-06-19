/*
Lab 6 - STL Containers and Algorithms
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This header file contains the parser specialized for Lab 6 to parse Patients
more quickly and automatically insert to the PatientDatabase. It extends the
XmlRegexIO parser built from the previous lab and adds multithreading
functionality to improve speed. It also works in conjunction with the
singleton PatientDatabase used in this lab for insertion efficiency.
*/

#ifndef SPECIALIZED_PATIENT_PARSER_H_
#define SPECIALIZED_PATIENT_PARSER_H_

#include "PatientDatabase.h"
#include "XmlRegexIO.h"
#include "Patient.h"
#include <thread>
#include <mutex>
#include <list>

class SpecializedPatientParser : public XmlRegexIO
{
private:
	int NUM_OF_LOGICAL_PROCESSORS;
	int PATIENT_COUNT_SPLITTER;

	std::string fileToParse;

	std::list<std::thread> parserThreads;

	// private method used by threads
	static void parseAndInsertData(std::string data, PatientDatabase *&pDB);
public:
	// constructors and destructor
	SpecializedPatientParser()  {}
	SpecializedPatientParser(const std::string &filename, size_t numberOfLinesInFile, bool limitCPUusage = false);
	~SpecializedPatientParser() {}
	// other methods
	bool specializedParse(PatientDatabase &pDB);
};

SpecializedPatientParser::SpecializedPatientParser(
	const std::string &filename,
	size_t numberOfLinesInFile,
	bool limitCPUusage)
	: NUM_OF_LOGICAL_PROCESSORS(std::thread::hardware_concurrency()),
	fileToParse(filename)
{
	if (numberOfLinesInFile % NUM_OF_LOGICAL_PROCESSORS == 0)
		PATIENT_COUNT_SPLITTER = numberOfLinesInFile / NUM_OF_LOGICAL_PROCESSORS;
	else if (NUM_OF_LOGICAL_PROCESSORS == 0)
		// this default was based on tests using an average CPU
		PATIENT_COUNT_SPLITTER = numberOfLinesInFile / 4;
	else
	{
		if (NUM_OF_LOGICAL_PROCESSORS < 4)
			PATIENT_COUNT_SPLITTER = numberOfLinesInFile / 2;
		else
		{
			do { --NUM_OF_LOGICAL_PROCESSORS; } while (NUM_OF_LOGICAL_PROCESSORS % 4 != 0);
			PATIENT_COUNT_SPLITTER = numberOfLinesInFile / NUM_OF_LOGICAL_PROCESSORS;
		}
	}
}

// private method used by threads
void SpecializedPatientParser::parseAndInsertData(std::string data, PatientDatabase *&pDB)
{
	std::string pattern("</patient>");
	size_t bpos = 0; // "beginning position" of substring
	size_t epos = data.find(pattern); // "end position" of substring

	while (epos != std::string::npos)
	{
		std::string temp = data.substr(bpos, (epos += pattern.length()) - bpos); // get a single patient node
		// parse data, create Patient and insert Patient into database
		Patient newPatient;
		newPatient.readData(temp);
		pDB->addPatient(Patient(newPatient));

		// sets epos so string::find looks for next occurrence instead of previous one
		bpos = epos; // also sets bpos to one index past the last occurrence of </patient>
		epos = data.find(pattern, bpos);
	}
}

bool SpecializedPatientParser::specializedParse(PatientDatabase &pDB)
{
	// check if file opens
	std::ifstream ifs;
	ifs.open(fileToParse);
	if (!ifs.is_open())
		return false;

	// split file and parse all pieces concurrently
	int count = 0;
	std::string line;
	std::string chunk;

	while (!ifs.eof()) // read until end of file
	{
		// Fill "chunk" string with a certain number of lines from file
		// where number of lines is specified by PATIENT_COUNT_SPLITTER
		while (++count <= PATIENT_COUNT_SPLITTER)
		{
			std::getline(ifs, line);
			chunk.append(line);
		}
		
		// start a new thread that runs the member function parseAndInsertData,
		// using std::bind to bind the "this" pointer to the function call
		parserThreads.push_back(
			std::thread(&SpecializedPatientParser::parseAndInsertData, chunk, &pDB)
		);

		// reset loop/temporary variables
		count = 0;
		chunk.clear();
	}

	// join all parser threads
	std::for_each(
		parserThreads.begin(),
		parserThreads.end(),
		[](std::thread &pthread) { pthread.join(); }
	);

	return true;
}

#endif // SPECIALIZED_PATIENT_PARSER_H_