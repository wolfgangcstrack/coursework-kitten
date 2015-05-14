/*
Lab 3 - Threading
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This is the main application for this lab.
*/

#include "XmlNodeList.h"
#include "XmlRegexIO.h"
#include "XmlRobot.h" // XmlRobot class extends the given Robot class for this lab
#include "ConsoleColor.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// the following methods are called from main()
void readTagsFromFile(XmlRegexIO &xRIO, const string &filename, vector<string> &tags);
void instantiateRobotCommands(XmlRegexIO &xRIO, const vector<string> &tags, XmlNodeList &rcList);
void executeRobotCommands(XmlNodeList &rcList);

// the following method is called from executeRobotCommands()
// In essence, it is a "wrapper" function that supports console color
void useRobot(XmlRobot &robot, ostream& color(ostream &s));

int main()
{
	XmlNodeList rcList;
	vector<string> tags;
	string filename = "RobotData.xml";
	vector<unique_ptr<XmlNode>> robotCommands;
	XmlRegexIO xRIO("<command>\\n.*?<robot>.*\\n.*?<offon>.*\\n.*?<speed>.*\\n.*?<horizontal>.*\\n.*?<vertical>.*\\n.*?<time>.*\\n.*?</command>");

	cout << "This is a demonstration of Lab 3: Threading\n\n";
	cout << "Robot A1 (thread 1) will be executed with the color " << red << "red.\n" << white;
	cout << "Robot A2 (thread 2) will be executed with the color " << blue << "blue.\n" << white;
	cout << "Robot A3 (thread 3) will be executed with the color " << green << "green.\n" << white;
	cout << "Robot A4 (thread 4) will be executed with the color " << yellow << "yellow.\n\n" << white;

	cout << "Reading tags from file " << filename << "...\n\n" << endl;
	readTagsFromFile(xRIO, filename, tags); // uses XmlRegexIO to read tags

	cout << "Instantiating Robots...\n\n" << endl;
	instantiateRobotCommands(xRIO, tags, rcList);

	cout << "Execution started:\n\n" << endl;
	executeRobotCommands(rcList); // calls the useRobot methods

	return 0;
}

void readTagsFromFile(XmlRegexIO &xRIO, const string &filename, vector<string> &tags)
{
	if (!xRIO.getAllMatches(filename, tags))
	{
		cout << "Error in file: " << filename << endl;
		return;
	}
}

void instantiateRobotCommands(XmlRegexIO &xRIO, const vector<string> &tags, XmlNodeList &rcList)
{
	for (int i = 0; i < tags.size(); i++)
	{
		shared_ptr<XmlNode> robotPtr(new XmlRobot());
		robotPtr->setXMLTags(tags[i]);
		if (!xRIO.getXmlDataFromString(tags[i], *robotPtr))
		{
			cout << "Error in instantiating Robots!\n";
			return;
		}
		rcList.push_back(robotPtr);
	}
}

void executeRobotCommands(XmlNodeList &rcList)
{
	thread A1; // red console font
	thread A2; // blue console font
	thread A3; // green console font
	thread A4; // yellow console font

	while (!rcList.empty())
	{
		shared_ptr<XmlRobot> robot(dynamic_pointer_cast<XmlRobot>(rcList.front()));

		if (robot->getRobotNumber().length() < 2)
		{
			cout << "Robot error: " << robot->getXMLTags() << endl;
			return;
		}

		switch (robot->getRobotNumber()[1])
		{
		case '1':
			A1 = thread(useRobot, *robot, red); // red console font
			A1.join();
			break;
		case '2':
			A2 = thread(useRobot, *robot, blue); // blue console font
			A2.join();
			break;
		case '3':
			A3 = thread(useRobot, *robot, green); // green console font
			A3.join();
			break;
		case '4':
			A4 = thread(useRobot, *robot, yellow); // yellow console font
			A4.join();
			break;
		default:
			cout << white << "Robot number error!\n";
			return;
		}

		rcList.pop_front();
	}

	cout << white; // reset console font color
}

void useRobot(XmlRobot &robot, ostream& color(ostream &s))
{
	robot.Execute(color);
}