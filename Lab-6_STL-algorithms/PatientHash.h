/*
Lab 6 - STL Containers and Algorithms
Wolfgang C. Strack
Windows 8 Visual C++ 2013


*/

#ifndef PATIENT_HASH_
#define PATIENT_HASH_

#include "Patient.h"
#include <unordered_map>
#include <bitset>
using namespace std;

// Hash function declared as a functor instead of inline lambda mainly for reuse
struct patientHash
{
	unsigned long operator()(const bitset<15> &barcode)
	{
		return barcode.to_ulong();
	}
};

typedef unordered_map<bitset<15>, Patient, patientHash> PatientHash;

class PatientHashSingleton
{
private:
	static PatientHash *instance;

	PatientHashSingleton()  {}
	~PatientHashSingleton() {}
public:
	static PatientHash * getInstance() { return instance; }
	static void resetInstance()        { delete instance; instance = 0; }
	static bool exists()               { return (instance != 0); }
};

PatientHash * PatientHashSingleton::instance = 0;

#endif // PATIENT_HASH_