/*
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This file contains the main application for this lab.
*/

#include "XmlRegexIO.h"
#include "XmlNode.h"
#include "User.h"
#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

void fillList(const vector<string> &tags, XmlNodeList &nodelist);
void displayNodeList(XmlNodeList &nodelist, bool andDelete = false);
void decryptUserData(XmlNodeList &nodelist);

int main()
{
	const string filename = "../VS-Final-Lab/users_1.xml";
	XmlRegexIO xrio("<user>(.|\\n)*?</user>");
	XmlNodeList nodelist;
	vector<string> tags;

	cout << "Now parsing file...\n\n\n";
	if (!xrio.getAllMatches(filename, tags)) {
		cout << "Something went wrong while parsing the file." << endl;
		return 1;
	}
	fillList(tags, nodelist);

	cout << "Now displaying user data (encrypted)...\n\n\n";
	displayNodeList(nodelist);

	cout << "Now decrypting user data...\n\n\n";
	decryptUserData(nodelist);

	cout << "Now displaying user data (decrypted)...\n\n\n";
	displayNodeList(nodelist, true);

	return 0;
}


void fillList(const vector<string> &tags, XmlNodeList &nodelist)
{
	for (auto i = tags.begin(); i != tags.end(); ++i)
	{
		XmlNode *newUser = new User;
		newUser->setXMLTags(*i);
		newUser->readData(*i);
		nodelist.push_back(newUser);
	}
}

void displayNodeList(XmlNodeList &nodelist, bool andDelete)
{
	for (auto i = nodelist.begin(); i != nodelist.end(); ++i)
	{
		cout << (*i)->toString() << endl << endl;

		if (andDelete)
			delete *i;
	}
}


void decryptUserData(XmlNodeList &nodelist)
{

}