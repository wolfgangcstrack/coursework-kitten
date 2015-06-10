/*
Lab 6 - STL Containers and Algorithms
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This header file contains the Patient class, which is an XmlNode in this
lab. It extends the XmlNode class.
*/

#ifndef PATIENT_HASH_MAP_H_
#define PATIENT_HASH_MAP_H_

#include "Patient.h"
#include <unordered_map>
using namespace std;

// Hash function declared as a functor instead of lambda mainly for reuse
struct patientHash
{
	unsigned long operator()(const bitset<15> &barcode)
	{
		return barcode.to_ulong();
	}
};

typedef public unordered_map<bitset<15>, Patient, patientHash> Patient_HashMap;

#endif // PATIENT_HASH_MAP_H_