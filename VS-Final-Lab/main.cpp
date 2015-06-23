/*
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This file contains the main application for this lab.
*/

#include "ThreadedUserParser.h"
#include "UserDecryptor.h"
#include "XmlNode.h"
#include "User.h"
#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

void displayNodeList(XmlNodeList &nodelist, bool andDelete = false);
void decryptUserData(XmlNodeList &nodelist);

int main()
{
	// this for-loop is in place in case there are more than 8 files
	const int NUMBER_OF_FILES = 8;
	string allFileNames[NUMBER_OF_FILES];
	for (int i = 1; i <= NUMBER_OF_FILES; i++)
	{
		allFileNames[i - 1] = "users_";
		allFileNames[i - 1] += to_string(i);
		allFileNames[i - 1] += ".xml";
	}

	vector<string> filenames(allFileNames, allFileNames + NUMBER_OF_FILES);

	ThreadedUserParser userParser("<user>(.|\\n)*?</user>");

	cout << "Now parsing all files...";
	XmlNodeList nodelist = userParser.parseUserFiles(filenames);
	cout << "Finished parsing all files\n\n\n";

	cout << "Now displaying all user data (encrypted):\n\n";
	displayNodeList(nodelist);
	cout << "\n\n\n\n\n";

	cout << "Decrypting all user data...";
	decryptUserData(nodelist);
	cout << "Finished decrypting all user data\n\n\n\n\n";

	cout << "Now displaying user data (decrypted):\n\n";
	displayNodeList(nodelist, true);
	
	cout << "\n\n\nNow exiting...\n\n";

	return 0;
}


void displayNodeList(XmlNodeList &nodelist, bool andDelete)
{
	for (auto i = nodelist.begin(); i != nodelist.end(); ++i)
	{
		cout << (*i)->toString() << endl;

		if (andDelete)
			delete (*i);
	}
}

void decryptUserData(XmlNodeList &nodelist)
{
	UserDecryptor decryptor;

	for (auto i = nodelist.begin(); i != nodelist.end(); ++i)
	{
		// "*i" dereferences the XmlNode* which is then
		// casted to a User*, which finally is dereferenced
		// to the User instance and passed to decryptor.convert()
		decryptor.convert(*dynamic_cast<User*>(*i));
	}
}