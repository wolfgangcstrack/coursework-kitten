/*
Lab 6 - STL Containers and Algorithms
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This file contains the PatientHash typedef and a class that manages
a PatientHash instance as a singleton.
*/

#ifndef PATIENT_HASH_
#define PATIENT_HASH_

#include "Patient.h"
#include <unordered_map>
#include <bitset>
#include <memory>

// Hash function declared as a functor instead of inline lambda mainly for reuse
struct patientHashFunction
{
	unsigned long operator()(const std::bitset<15> &barcode)
	{
		return barcode.to_ulong();
	}
};

typedef std::unordered_map<std::bitset<15>, std::shared_ptr<Patient>, patientHashFunction> PatientHash;

class PatientHashSingleton
{
private:
	static PatientHash *instance;

	PatientHashSingleton()  {}
	~PatientHashSingleton() {}
public:
	static PatientHash * getInstance() { if (instance) instance = new PatientHash(); return instance; }
	static void resetInstance()        { delete instance; instance = 0; }
	static bool exists()               { return (instance != 0); }
};

PatientHash * PatientHashSingleton::instance = 0;

#endif // PATIENT_HASH_