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

class SpecializedPatientParser : public XmlRegexIO
{
private:
	static const int PATIENT_COUNT_SPLITTER = 500;
	static const std::regex splitterRegex;
	static const std::regex patientRegex;

	std::list<std::thread> parserThreads;

	// private method used by threads
	static void parseAndInsertData(const std::string data, PatientDatabase *&pDB);
public:
	// constructors and destructor
	SpecializedPatientParser()  {}
	~SpecializedPatientParser() {}
	// other methods
	bool specializedParse(const std::string &fileName, PatientDatabase *&pDB);
};

// static variable initializers
const std::regex SpecializedPatientParser::splitterRegex(
	std::string("([0-9]*\\n<patient>[\\s\\S]*?</patient>\\n*?){") +
	std::to_string(PATIENT_COUNT_SPLITTER) + 
	std::string("}")
);
const std::regex SpecializedPatientParser::patientRegex("[0-9]*\\n<patient>(.|\\n)*?</patient>");

// private method used by threads
void SpecializedPatientParser::parseAndInsertData(const std::string data, PatientDatabase *&pDB)
{
	std::sregex_token_iterator begin(data.begin(), data.end(), patientRegex);
	std::sregex_token_iterator end;

	for (auto i = begin; i != end; ++i)
	{
		Patient newPatient;
		newPatient.setXMLTags(i->str());
		newPatient.readData(newPatient.getXMLTags());
		pDB->addPatient(newPatient);
	}
}

bool SpecializedPatientParser::specializedParse(const std::string &filename, PatientDatabase *&pDB)
{
	// check if file opens
	std::ifstream ifs;
	ifs.open(filename);
	if (!ifs.is_open())
		return false;

	// split file and parse all pieces concurrently
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

	// join all parser threads
	std::for_each(
		parserThreads.begin(),
		parserThreads.end(),
		[](std::thread &pthread) { pthread.join(); }
	);

	return true;
}

#endif // SPECIALIZED_PATIENT_PARSER_H_