/*
Lab 6 - STL Containers and Algorithms
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This file includes the PatientDatabase singleton class. It combines a hash
table and a tree that both point to the patient data and are both used for
different types of searches.
*/

#ifndef PATIENT_DATABASE_H_
#define PATIENT_DATABASE_H_

#include "PatientContainers.h"
#include <mutex>

class PatientDatabase
{
private:
	typedef std::pair<std::bitset<15>, std::shared_ptr<Patient>> BarcodeAndPatient;

	std::mutex pdb_mutex; // makes this database thread-safe
	PatientHash phash;

	static PatientDatabase *instance;

	PatientDatabase()  {}
	~PatientDatabase() {}
public:
	// singleton-type methods
	static PatientDatabase * getInstance();
	static void resetInstance()    { delete instance; instance = 0; }
	static bool exists()           { return (instance != 0); }
	// getter method (mutable)
	PatientHash * getPatientHash() { return &phash; }
	// other methods
	bool addPatient(const Patient patient);
};

// static class member initializer
PatientDatabase * PatientDatabase::instance = 0;

PatientDatabase * PatientDatabase::getInstance()
{
	if (!instance)
	{
		instance = new PatientDatabase();
	}

	return instance;
}

bool PatientDatabase::addPatient(const Patient patient)
{
	std::shared_ptr<Patient> ptr(new Patient(patient));
	BarcodeAndPatient bap(ptr->getBarcode().getBinaryBarcode(), ptr);

	pdb_mutex.lock();
	phash.insert(bap);
	pdb_mutex.unlock();

	return true;
}

#endif // PATIENT_DATABASE_H_