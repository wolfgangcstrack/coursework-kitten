/*
Lab 6 - STL Containers and Algorithms
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This file contains the PatientHash/PatientTree/PatientList typedefs and
related functions/functors.
*/

#ifndef PATIENT_CONTAINERS_H_
#define PATIENT_CONTAINERS_H_

#include "Patient.h"
#include <unordered_map>
#include <bitset>
#include <memory>
#include <list>
#include <map>

// Hash function declared as a functor instead of inline lambda mainly for reuse
struct patientHashFunction
{
	unsigned long operator()(const std::bitset<15> &barcode)
	{
		return barcode.to_ulong();
	}
};
typedef std::unordered_map<std::bitset<15>, std::shared_ptr<Patient>, patientHashFunction> PatientHash;

// Compare function declared as a functor instead of inline lambda mainly for reuse
struct patientTreeCompareFunction
{
	bool operator()(const std::bitset<15> &lhs, const std::bitset<15> &rhs)
	{
		return (lhs.to_ulong() < rhs.to_ulong());
	}
};
typedef std::map<std::bitset<15>, std::shared_ptr<Patient>, patientTreeCompareFunction> PatientTree;

typedef std::list<std::shared_ptr<Patient>> PatientList;

#endif // PATIENT_CONTAINERS_H_