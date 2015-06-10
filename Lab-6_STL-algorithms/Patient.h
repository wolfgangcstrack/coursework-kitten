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
#include <memory>
#include <string>
#include <bitset>
using namespace std;

class Patient : public XmlNode
{
private:
	int encryptedBarcode;
	unique_ptr<bitset<15>> binaryBarcode;

	unique_ptr<string> name;
	int age;
	char gender;
	char bloodType;
	unique_ptr<string> maritalStatus;
	int income;
	int dependents;
public:
	// constructors and destructor
	Patient() : encryptedBarcode(0),
		age(0), gender(0), bloodType(0),
		income(0), dependents(0) {}
	~Patient() {}
	// getters/setters
	const string & getName() const          { return *name; }
	int getAge() const                      { return age; }
	char getGender() const                  { return gender; }
	char getBloodtype() const               { return bloodType; }
	const string & getMaritalStatus() const { return *maritalStatus; }
	int getIncome() const                   { return income; }
	int getDependents() const               { return dependents; }
	void setName(const string &n)           { *name = n; }
	void setAge(int a)                      { age = a; }
	void setGender(char g)                  { gender = g; }
	void setBloodType(char bt)              { bloodType = bt; }
	void setMaritalStatus(const string &ms) { *maritalStatus = ms; }
	void setIncome(int i)                   { income = i; }
	void setDependents(int d)               { dependents = d; }
	// overridden methods from XmlNode
	void readData(const string &data);
};

void Patient::readData(const string &data)
{
	encryptedBarcode = this->get_ulong(data, regex("^[0-9]*?$"));
	binaryBarcode.reset(new bitset<15>(encryptedBarcode));
	name.reset(new string(this->getString(data, "name")));
	age = this->get_ulong(data, "age");
	gender = this->getString(data, "gender").at(0);
	bloodType = this->getString(data, "bloodtype").at(0);
	maritalStatus.reset(new string(this->getString(data, "maritalstatus")));
	income = this->get_ulong(data, "income");
	dependents = this->get_ulong(data, "dependents");
}

#endif // PATIENT_H_