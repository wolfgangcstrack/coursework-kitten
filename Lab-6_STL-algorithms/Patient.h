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
#include <memory>
#include <string>
#include <bitset>
#include <tuple>
using namespace std;

#define PATIENT_DATA_TYPES Barcode, string, int, char, char, string, int, int
#define PATIENT_DATA_PARAMS const Barcode &barcode,\
							const string &name,\
							int age,\
							char gender,\
							char bloodType,\
							const string &maritalStatus,\
							int income,\
							int dependents

class Patient : public XmlNode
{
private:
	unique_ptr<tuple<PATIENT_DATA_TYPES>> data;

	/* tuple data types for reference:
	0 Barcode barcode;
	1 string name;
	2 int age;
	3 char gender;
	4 char bloodType;
	5 string maritalStatus;
	6 int income;
	7 int dependents;
	*/
public:
	// constructors and destructor
	Patient()  {}
	Patient(PATIENT_DATA_PARAMS);
	~Patient() {}
	// getters/setters
	const Barcode &getBarcode() const       { return get<0>(*data); }
	const string & getName() const          { return get<1>(*data); }
	int getAge() const                      { return get<2>(*data); }
	char getGender() const                  { return get<3>(*data); }
	char getBloodtype() const               { return get<4>(*data); }
	const string & getMaritalStatus() const { return get<5>(*data); }
	int getIncome() const                   { return get<6>(*data); }
	int getDependents() const               { return get<7>(*data); }
	void setBarcode(const Barcode &bcode)   { get<0>(*data) = bcode; }
	void setName(const string &n)           { get<1>(*data) = n; }
	void setAge(int a)                      { get<2>(*data) = a; }
	void setGender(char g)                  { get<3>(*data) = g; }
	void setBloodType(char bt)              { get<4>(*data) = bt; }
	void setMaritalStatus(const string &ms) { get<5>(*data) = ms; }
	void setIncome(int i)                   { get<6>(*data) = i; }
	void setDependents(int d)               { get<7>(*data) = d; }
	// overridden methods from XmlNode
	void readData(const string &data);
};

Patient::Patient(PATIENT_DATA_PARAMS)
{
	get<0>(*data) = barcode;
	get<1>(*data) = name;
	get<2>(*data) = age;
	get<3>(*data) = gender;
	get<4>(*data) = bloodType;
	get<5>(*data) = maritalStatus;
	get<6>(*data) = income;
	get<7>(*data) = dependents;
}

void Patient::readData(const string &xmlData)
{
	get<0>(*data).setBarcode(this->get_ulong(xmlData, regex("^[0-9]*?$")));
	get<1>(*data) = this->getString(xmlData, "name");
	get<2>(*data) = this->get_ulong(xmlData, "age");
	get<3>(*data) = this->getString(xmlData, "gender").at(0);
	get<4>(*data) = this->getString(xmlData, "bloodtype").at(0);
	get<5>(*data) = this->getString(xmlData, "maritalstatus");
	get<6>(*data) = this->get_ulong(xmlData, "income");
	get<7>(*data) = this->get_ulong(xmlData, "dependents");
}

#endif // PATIENT_H_