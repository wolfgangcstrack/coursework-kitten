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

int main()
{
	const string filename = "users_1.xml";
	XmlRegexIO xrio("<user>(.|\\n)*?</user>");
	XmlNodeList nodelist;
	vector<string> tags;

	if (!xrio.getAllMatches(filename, tags)) {
		cout << "Something went wrong while parsing the file." << endl;
		return 1;
	}

	fillList(tags, nodelist);

	for (auto i = nodelist.begin(); i != nodelist.end(); ++i)
	{
		cout << (*i)->toString() << endl << endl;
	}

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