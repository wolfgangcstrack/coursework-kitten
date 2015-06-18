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
#include <string>
#include <tuple>

#define PATIENT_DATA_TYPES Barcode, std::string, int, char, char, std::string, int, int
#define PATIENT_DATA_PARAMS const Barcode &barcode,\
							const std::string &name,\
							int age,\
							char gender,\
							char bloodType,\
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
	4 char bloodType;
	5 std::string maritalStatus;
	6 int income;
	7 int dependents;
	*/
public:
	// constructors and destructor
	Patient()  {}
	Patient(PATIENT_DATA_PARAMS);
	~Patient() {}
	// getters/setters
	const Barcode &getBarcode() const            { return std::get<0>(data); }
	const std::string & getName() const          { return std::get<1>(data); }
	int getAge() const                           { return std::get<2>(data); }
	char getGender() const                       { return std::get<3>(data); }
	char getBloodtype() const                    { return std::get<4>(data); }
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
};

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
	std::get<0>(data).setBarcode(this->get_ulong(xmlData, std::regex("^[0-9]*?$")));
	std::get<1>(data) = this->getString(xmlData, "name");
	std::get<2>(data) = this->get_ulong(xmlData, "age");
	std::get<3>(data) = this->getString(xmlData, "gender").at(0);
	std::get<4>(data) = this->getString(xmlData, "bloodtype").at(0);
	std::get<5>(data) = this->getString(xmlData, "maritalstatus");
	std::get<6>(data) = this->get_ulong(xmlData, "income");
	std::get<7>(data) = this->get_ulong(xmlData, "dependents");
}

#endif // PATIENT_H_