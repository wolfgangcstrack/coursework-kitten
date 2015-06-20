/*
Lab 6 - STL Containers and Algorithms
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This file includes the PatientDatabase singleton class. This class is a
singleton-type due to the nature of databases to usually become large.
Therefore, accidentally copying the PatientDatabase anywhere would waste
resources and time.
*/

#ifndef PATIENT_DATABASE_H_
#define PATIENT_DATABASE_H_

#include "PatientContainers.h"
#include <mutex>

#include <iostream>

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
	bool insertPatient(const Patient patient);
	bool removePatient(const std::bitset<15> binaryBarcode);
	bool removePatient(const std::string binaryBarcode);
	const Patient & getPatient(const std::bitset<15> binaryBarcode);
	const Patient & getPatient(const std::string binaryBarcode);
	const Patient & getPatient(unsigned int encryptedBarcode);
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

bool PatientDatabase::insertPatient(const Patient patient)
{
	std::shared_ptr<Patient> ptr(new Patient(patient));
	BarcodeAndPatient bap(ptr->getBarcode().getBinaryBarcode(), ptr);

	pdb_mutex.lock();
	// the .second value is a bool that indicates successful insert or not
	bool successfulInsert = (phash.insert(bap)).second;
	pdb_mutex.unlock();

	return successfulInsert;
}

bool PatientDatabase::removePatient(const std::bitset<15> binaryBarcode)
{
	pdb_mutex.lock();
	bool successfulRemove = phash.erase(binaryBarcode);
	pdb_mutex.unlock();

	return successfulRemove;
}

#endif // PATIENT_DATABASE_H_