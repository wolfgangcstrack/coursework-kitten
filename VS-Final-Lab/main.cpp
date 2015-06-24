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
#include <vector>
#include <string>
using namespace std;

vector<string> getFileNames(int numFiles);
void displayNodeList(XmlNodeList &nodelist);
void decryptUserData(XmlNodeList &nodelist);

int main()
{
	const int NUMBER_OF_FILES = 4; // can change if more/less than 4 files
	vector<string> filenames = getFileNames(NUMBER_OF_FILES);

	ThreadedUserParser userParser("<user>(.|\\n)*?</user>");

	cout << "Starting timer...\n\n\n";
	clock_t begin = clock(); // start timer

	cout << "Now parsing all files...";
	XmlNodeList nodelist = userParser.parseUserFiles(filenames);

	clock_t end = clock();
	cout << "Finished parsing all files." << endl
		<< "\nTotal number of users: " << nodelist.size() << endl
		<< "Total time taken to parse: " << double(end - begin) / CLOCKS_PER_SEC << " seconds\n\n\n";

	cout << "\n\nNow displaying all user data (encrypted):\n\n";
	displayNodeList(nodelist);
	cout << "\n\n\n\n\n";

	cout << "Decrypting all user data...";
	decryptUserData(nodelist);
	cout << "Finished decrypting all user data.\n\n\n";

	cout << "\n\nNow displaying user data (decrypted):\n\n";
	displayNodeList(nodelist);
	
	cout << "\n\n\nNow exiting...\n\n";

	return 0;
}

vector<string> getFileNames(int numFiles)
{
	vector<string> filenames;

	string temp;
	for (int i = 1; i <= numFiles; i++)
	{
		temp = "users_";
		temp += to_string(i);
		temp += "_encrypted.xml";

		filenames.push_back(temp);
	}

	return filenames;
}

void displayNodeList(XmlNodeList &nodelist)
{
	for (auto i = nodelist.begin(); i != nodelist.end(); ++i)
	{
		cout << (*i)->toString() << endl;
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