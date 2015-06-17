/*
Lab 6 - STL Containers and Algorithms
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This file contains the PatientList typedef and a class that manages
a PatientList instance as a singleton.
*/

#ifndef PATIENT_LIST_H_
#define PATIENT_LIST_H_

#include "Patient.h"
#include <bitset>
#include <memory>
#include <list>
using namespace std;

typedef list<shared_ptr<Patient>> PatientList;

class PatientListSingleton
{
private:
	static PatientList *instance;

	PatientListSingleton()  {}
	~PatientListSingleton() {}
public:
	static PatientList * getInstance() { if (instance) instance = new PatientList(); return instance; }
	static void resetInstance()        { delete instance; instance = 0; }
	static bool exists()               { return (instance != 0); }
};

PatientList * PatientListSingleton::instance = 0;

#endif // PATIENT_LIST_H_