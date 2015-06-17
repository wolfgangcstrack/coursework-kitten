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
	~Patient() {}
	// getters/setters
	const string & getName() const          { return get<1>(*data); }
	int getAge() const                      { return get<2>(*data); }
	char getGender() const                  { return get<3>(*data); }
	char getBloodtype() const               { return get<4>(*data); }
	const string & getMaritalStatus() const { return get<5>(*data); }
	int getIncome() const                   { return get<6>(*data); }
	int getDependents() const               { return get<7>(*data); }
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

void Patient::readData(const string &xmlData)
{
	std::get<0>(*data).setBarcode(this->get_ulong(xmlData, regex("^[0-9]*?$")));
	get<1>(*data) = this->getString(xmlData, "name");
	get<2>(*data) = this->get_ulong(xmlData, "age");
	get<3>(*data) = this->getString(xmlData, "gender").at(0);
	get<4>(*data) = this->getString(xmlData, "bloodtype").at(0);
	get<5>(*data) = this->getString(xmlData, "maritalstatus");
	get<6>(*data) = this->get_ulong(xmlData, "income");
	get<7>(*data) = this->get_ulong(xmlData, "dependents");
}

#endif // PATIENT_H_