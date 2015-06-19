/*
Lab 6 - STL Containers and Algorithms
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This header file contains the parser specialized for Lab 6 to parse Patients
more quickly and automatically insert to the PatientDatabase. It extends the
XmlRegexIO parser built from the previous lab and adds multithreading
functionality to improve speed.
*/

#ifndef SPECIALIZED_PATIENT_PARSER_H_
#define SPECIALIZED_PATIENT_PARSER_H_

#include "PatientDatabase.h"
#include "XmlRegexIO.h"
#include "Patient.h"
#include <thread>
#include <mutex>
#include <list>

#include <iostream>

class SpecializedPatientParser : public XmlRegexIO
{
private:
	static const int PATIENT_COUNT_SPLITTER = 100;
	static const std::regex splitterRegex;
	static const std::regex patientRegex;

	std::list<std::thread> parserThreads;

	// private method used by threads
public:
	// constructors and destructor
	SpecializedPatientParser()  {}
	~SpecializedPatientParser() {}
	// other methods
	bool specializedParse(const std::string &fileName, PatientDatabase &pDB);
	static void parseAndInsertData(std::string data, PatientDatabase &pDB);
};

// static variable initializers
const std::regex SpecializedPatientParser::splitterRegex(
	std::string("([0-9]*\\n<patient>[\\s\\S]*?</patient>\\n*?){") +
	std::to_string(PATIENT_COUNT_SPLITTER) + 
	std::string("}"));
const std::regex SpecializedPatientParser::patientRegex("[0-9]*\\n<patient>(.|\\n)*?</patient>");

// private method used by threads
void SpecializedPatientParser::parseAndInsertData(std::string data, PatientDatabase &pDB)
{
	std::string temp;
	std::string pattern("</patient>");
	size_t bpos = 0; // "beginning position" of substring
	size_t epos = data.find(pattern); // "end position" of substring

	while (epos != std::string::npos)
	{
		temp = data.substr(bpos, (epos+=pattern.length())); // get a single patient node
		//std::cout << temp << std::endl;
		// parse data, create Patient and insert Patient into database
		Patient newPatient;
		//newPatient.setXMLTags(temp);
		newPatient.readData(temp);
		pDB.addPatient(newPatient);

		// sets epos so string::find looks for next occurrence instead of previous one
		bpos = epos; // also sets bpos to one index past the last occurrence of </patient>
		epos = data.find(pattern, epos);
	}

	/* doesn't work
	std::sregex_token_iterator begin(data.begin(), data.end(), patientRegex);
	std::sregex_token_iterator end;

	for (auto i = begin; i != end; ++i)
	{
		Patient newPatient;
		newPatient.setXMLTags(i->str());
		newPatient.readData(newPatient.getXMLTags());
		pDB->addPatient(newPatient);
	}
	*/
}

bool SpecializedPatientParser::specializedParse(const std::string &filename, PatientDatabase &pDB)
{
	std::cout << "SPP OPENING FILE" << std::endl;
	// check if file opens
	std::ifstream ifs;
	ifs.open(filename);
	if (!ifs.is_open())
		return false;
	std::cout << "SPP OPENED FILE" << std::endl;
	// split file and parse all pieces concurrently
	short count = 0;
	std::string line;
	std::string chunk;

	while (!ifs.eof()) // read until end of file
	{
		std::cout << "SPP READING CHUNK" << std::endl;
		// Fill "chunk" string with a certain number of lines from file
		// where number of lines is specified by PATIENT_COUNT_SPLITTER
		while (++count <= PATIENT_COUNT_SPLITTER)
		{
			std::getline(ifs, line);
			//std::cout << line << std::endl;
			chunk.append(line);
			//std::cout << "\tDOOOOOOOOOOOOOOOOGE 4" << std::endl;
		}
		std::cout << "SPP STARTING NEW THREAD FOR CHUNK" << std::endl;

		// start a new thread that runs the member function parseAndInsertData,
		// using std::bind to bind the "this" pointer to the function call
		parserThreads.push_back(
			std::thread([&]{ SpecializedPatientParser::parseAndInsertData(chunk, pDB); })
		);
		//parseAndInsertData(chunk, pDB);
		std::cout << "\nSPP THREAD STARTED FOR CHUNK\n" << std::endl;

		// reset loop/temporary variables
		count = 0;
		chunk.clear();
	}

	/* doesn't work
	std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
	std::sregex_token_iterator begin(content.begin(), content.end(), splitterRegex);
	std::sregex_token_iterator end;

	for (auto i = begin; i != end; ++i)
	{
		// start a new thread that runs the member function parseAndInsertData,
		// using std::bind to bind the "this" pointer to the function call
		parserThreads.push_back(
			std::thread(
				std::bind(
					&SpecializedPatientParser::parseAndInsertData,
					std::string(i->str()),
					pDB
				)
			)
		);
	}
	*/

	// join all parser threads
	std::for_each(
		parserThreads.begin(),
		parserThreads.end(),
		[](std::thread &pthread) { pthread.join(); }
	);

	return true;
}

#endif // SPECIALIZED_PATIENT_PARSER_H_