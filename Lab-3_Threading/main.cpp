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
void useRobot(XmlRobot &robot);

int main()
{
	XmlNodeList rcList;
	vector<string> tags;
	string filename = "RobotData.xml";
	vector<unique_ptr<XmlNode>> robotCommands;
	XmlRegexIO xRIO("<command>\\n.*?<robot>.*\\n.*?<offon>.*\\n.*?<speed>.*\\n.*?<horizontal>.*\\n.*?<vertical>.*\\n.*?<time>.*\\n.*?</command>");

	cout << "This is a demonstration of Lab 3: Threading\n\n";

	readTagsFromFile(xRIO, filename, tags); // uses XmlRegexIO to read tags

	instantiateRobotCommands(xRIO, tags, rcList);

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
			A1 = thread(useRobot, *robot); // red console font
			A1.join();
			break;
		case '2':
			A2 = thread(useRobot, *robot); // blue console font
			A2.join();
			break;
		case '3':
			A3 = thread(useRobot, *robot); // green console font
			A3.join();
			break;
		case '4':
			A4 = thread(useRobot, *robot); // yellow console font
			A4.join();
			break;
		default:
			cout << "Robot number error!\n";
			return;
		}

		rcList.pop_front();
	}
}

void useRobot(XmlRobot &robot)
{
	robot.Execute();
}