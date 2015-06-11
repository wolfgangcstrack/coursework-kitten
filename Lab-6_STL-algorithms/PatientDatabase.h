/*
Lab 6 - STL Containers and Algorithms
Wolfgang C. Strack
Windows 8 Visual C++ 2013


*/

#ifndef PATIENT_DATABASE_H_
#define PATIENT_DATABASE_H_

#include "PatientHash.h"
#include "PatientTree.h"

class PatientDatabase
{
private:
	PatientHash *phash;
	PatientTree *ptree;

	static PatientDatabase *instance;

	PatientDatabase()  { phash = PatientHashSingleton::getInstance(); ptree = PatientTreeSingleton::getInstance(); }
	~PatientDatabase() { PatientHashSingleton::resetInstance(); PatientTreeSingleton::resetInstance(); }
public:
	static PatientDatabase * getInstance() { if (instance) instance = new PatientDatabase(); return instance; }
	static void resetInstance()            { delete instance; instance = 0; }
	static bool exists()                   { return (instance != 0); }
	static bool componentsExist()          { return (PatientHashSingleton::exists() && PatientTreeSingleton::exists()); }
};

PatientDatabase * PatientDatabase::instance = 0;

#endif // PATIENT_DATABASE_H_