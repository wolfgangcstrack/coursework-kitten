/*
Lab 6 - STL Containers and Algorithms
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This file contains the PatientTree typedef and a class that manages
a PatientTree instance as a singleton.
*/

#ifndef PATIENT_TREE_H_
#define PATIENT_TREE_H_

#include "Patient.h"
#include <bitset>
#include <memory>
#include <map>
using namespace std;

typedef map<bitset<15>, shared_ptr<Patient>> PatientTree;

class PatientTreeSingleton
{
private:
	static PatientTree *instance;

	PatientTreeSingleton()  {}
	~PatientTreeSingleton() {}
public:
	static PatientTree * getInstance() { if (instance) instance = new PatientTree(); return instance; }
	static void resetInstance()        { delete instance; instance = 0; }
	static bool exists()               { return (instance != 0); }
};

PatientTree * PatientTreeSingleton::instance = 0;

#endif // PATIENT_TREE_H_