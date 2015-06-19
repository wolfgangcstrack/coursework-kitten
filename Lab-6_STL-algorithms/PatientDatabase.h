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

#include "PatientList.h"
#include "PatientHash.h"
#include "PatientTree.h"
#include <thread>
#include <mutex>
#include <iostream>
static std::mutex pdb_mutex;

class PatientDatabase
{
private:
	typedef std::pair<std::bitset<15>, std::shared_ptr<Patient>> BarcodeAndPatient;

	/*static*/ PatientList plist;
	/*static*/ PatientHash phash;
	/*static*/ PatientTree ptree;

	static PatientDatabase *instance;

	PatientDatabase()
	{
		/*plist = PatientListSingleton::getInstance();
		phash = PatientHashSingleton::getInstance();
		ptree = PatientTreeSingleton::getInstance();*/
	}

	~PatientDatabase()
	{
		/*PatientListSingleton::resetInstance();
		PatientHashSingleton::resetInstance();
		PatientTreeSingleton::resetInstance();*/
	}

	static void plistInsert(std::shared_ptr<Patient> ptr, PatientList & pl) { pl.push_back(ptr); }
	static void phashInsert(BarcodeAndPatient &bp, PatientHash & ph) { ph.insert(bp); }
	static void ptreeInsert(BarcodeAndPatient &bp, PatientTree & pt) { pt.insert(bp); }
public:
	static PatientDatabase * getInstance();
	static void resetInstance()    { delete instance; instance = 0; }
	static bool exists()           { return (instance != 0); }
	static bool componentsExist()
	{
		return (PatientListSingleton::exists() && 
			PatientHashSingleton::exists() && 
			PatientTreeSingleton::exists());
	}

	PatientList * getPatientList() { return &plist; }
	PatientHash * getPatientHash() { return &phash; }
	PatientTree * getPatientTree() { return &ptree; }

	bool addPatient(const Patient patient);
};

//PatientList * PatientDatabase::plist = 0;
//PatientHash * PatientDatabase::phash = 0;
//PatientTree * PatientDatabase::ptree = 0;

PatientDatabase * PatientDatabase::instance = 0;

//std::mutex PatientDatabase::pdb_mutex;

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

	/*plist.push_back(ptr);
	phash.insert(bap);
	ptree.insert(bap);*/
	
	//std::cout << *ptr << std::endl;

	std::thread listInsert([&]{ plist.push_back(ptr); });
	std::thread hashInsert([&]{ phash.insert(bap); });
	std::thread treeInsert([&]{ ptree.insert(bap); });

	/*std::thread listInsert(&PatientDatabase::plistInsert, ptr, plist);
	std::thread hashInsert(&PatientDatabase::phashInsert, bap, phash);
	std::thread treeInsert(&PatientDatabase::ptreeInsert, bap, ptree);*/

	listInsert.join();
	hashInsert.join();
	treeInsert.join();

	pdb_mutex.unlock();

	return true;
}

#endif // PATIENT_DATABASE_H_