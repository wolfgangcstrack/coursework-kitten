/*
Lab 6 - STL Containers and Algorithms
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This header file contains the Patient class, which is an XmlNode in this
lab. It extends the XmlNode class.
*/

#ifndef PATIENT_H_
#define PATIENT_H_

#include "XmlNode.h"
#include "Barcode.h"
#include <iostream>
#include <ostream>
#include <string>
#include <tuple>

// some macros for parameter lists
#define PATIENT_DATA_TYPES Barcode, std::string, int, char, std::string, std::string, int, int
#define PATIENT_DATA_PARAMS const Barcode &barcode,\
							const std::string &name,\
							int age,\
							char gender,\
							const std::string &bloodType,\
							const std::string &maritalStatus,\
							int income,\
							int dependents

class Patient : public XmlNode
{
private:
	std::tuple<PATIENT_DATA_TYPES> data;

	/* tuple data types for reference:
	0 Barcode barcode;
	1 std::string name;
	2 int age;
	3 char gender;
	4 std::string bloodType;
	5 std::string maritalStatus;
	6 int income;
	7 int dependents;
	*/
public:
	// constructors and destructor
	Patient();
	Patient(const Patient &toCopy);
	Patient(PATIENT_DATA_PARAMS);
	~Patient() {}
	// getters/setters
	const Barcode &getBarcode() const            { return std::get<0>(data); }
	const std::string & getName() const          { return std::get<1>(data); }
	int getAge() const                           { return std::get<2>(data); }
	char getGender() const                       { return std::get<3>(data); }
	const std::string & getBloodtype() const     { return std::get<4>(data); }
	const std::string & getMaritalStatus() const { return std::get<5>(data); }
	int getIncome() const                        { return std::get<6>(data); }
	int getDependents() const                    { return std::get<7>(data); }
	void setBarcode(const Barcode &bcode)        { std::get<0>(data) = bcode; }
	void setName(const std::string &n)           { std::get<1>(data) = n; }
	void setAge(int a)                           { std::get<2>(data) = a; }
	void setGender(char g)                       { std::get<3>(data) = g; }
	void setBloodType(char bt)                   { std::get<4>(data) = bt; }
	void setMaritalStatus(const std::string &ms) { std::get<5>(data) = ms; }
	void setIncome(int i)                        { std::get<6>(data) = i; }
	void setDependents(int d)                    { std::get<7>(data) = d; }
	// overridden methods from XmlNode
	void readData(const std::string &xmlData);
	// other methods
	bool operator==(const Patient &right)        { return (this->data == right.data); }
	friend std::ostream & operator<<(std::ostream &os, const Patient &p);
};

std::ostream & operator<<(std::ostream &os, const Patient &p)
{
	os << "Patient " << std::get<0>(p.data).getEncryptedBarcode() << std::endl
		<< "\tName: " << std::get<1>(p.data) << std::endl
		<< "\tAge: " << std::get<2>(p.data) << std::endl
		<< "\tGender: " << std::get<3>(p.data) << std::endl
		<< "\tBlood type: " << std::get<4>(p.data) << std::endl
		<< "\tMarital status: " << std::get<5>(p.data) << std::endl
		<< "\tIncome: " << std::get<6>(p.data) << std::endl
		<< "\tDependents: " << std::get<7>(p.data);

	return os;
}

Patient::Patient()
{
	data = std::make_tuple(Barcode(), "NULL PATIENT", 0, '0', "n/a", "n/a", 0, 0);
}

Patient::Patient(const Patient &toCopy)
{
	data = toCopy.data;
}

Patient::Patient(PATIENT_DATA_PARAMS)
{
	std::get<0>(data) = barcode;
	std::get<1>(data) = name;
	std::get<2>(data) = age;
	std::get<3>(data) = gender;
	std::get<4>(data) = bloodType;
	std::get<5>(data) = maritalStatus;
	std::get<6>(data) = income;
	std::get<7>(data) = dependents;
}

void Patient::readData(const std::string &xmlData)
{
	size_t bpos = 0, epos = xmlData.find("<patient>");
	std::get<0>(data).setBarcode(std::stoi(xmlData.substr(bpos, epos - bpos)));

	bpos = xmlData.find("<name>", epos) + 6, epos = xmlData.find("</name>", bpos);
	std::get<1>(data) = xmlData.substr(bpos, epos - bpos);

	bpos = xmlData.find("<age>", epos) + 5, epos = xmlData.find("</age>", bpos);
	std::get<2>(data) = std::stoi(xmlData.substr(bpos, epos - bpos));

	bpos = xmlData.find("<gender>", epos) + 8, epos = xmlData.find("</gender>", bpos);
	std::get<3>(data) = xmlData.substr(bpos, epos - bpos).at(0);

	bpos = xmlData.find("<bloodtype>", epos) + 11, epos = xmlData.find("</bloodtype>", bpos);
	std::get<4>(data) = xmlData.substr(bpos, epos - bpos);

	bpos = xmlData.find("<maritalstatus>", epos) + 15, epos = xmlData.find("</maritalstatus>", bpos);
	std::get<5>(data) = xmlData.substr(bpos, epos - bpos);

	bpos = xmlData.find("<income>", epos) + 8, epos = xmlData.find("</income>", bpos);
	std::get<6>(data) = std::stoi(xmlData.substr(bpos, epos - bpos));

	bpos = xmlData.find("<dependents>", epos) + 12, epos = xmlData.find("</dependents>", bpos);
	std::get<7>(data) = std::stoi(xmlData.substr(bpos, epos - bpos));
}

#endif // PATIENT_H_