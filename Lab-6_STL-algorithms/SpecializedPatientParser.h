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

class SpecializedPatientParser : public XmlRegexIO
{
public:
	// constructors and destructor
	SpecializedPatientParser() : XmlRegexIO() {}
	SpecializedPatientParser(const std::string &pattern) : XmlRegexIO(pattern) {}
	~SpecializedPatientParser () {}
	// other methods
	bool specializedParse(const std::string &fileName, PatientDatabase *pDB);
};

#endif // SPECIALIZED_PATIENT_PARSER_H_