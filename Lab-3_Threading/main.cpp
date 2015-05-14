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

// the following methods are called from executeRobotCommands()
void useRobotA1(XmlRobot &robot); // use thread 1, red
void useRobotA2(XmlRobot &robot); // use thread 2, blue
void useRobotA3(XmlRobot &robot); // use thread 3, green
void useRobotA4(XmlRobot &robot); // use thread 4, yellow

// the following method is called by the useRobotA# commands and is a wrapper that supports console color
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
			useRobotA1(*robot); // red console font
			break;
		case '2':
			useRobotA2(*robot); // blue console font
			break;
		case '3':
			useRobotA3(*robot); // green console font
			break;
		case '4':
			useRobotA4(*robot); // yellow console font
			break;
		default:
			cout << "Robot number error!\n";
			return;
		}

		rcList.pop_front();
	}
}


void useRobotA1(XmlRobot &robot) // use thread 1, red
{
	thread A1(useRobot, robot);
	A1.join();
}

void useRobotA2(XmlRobot &robot) // use thread 2, blue
{
	thread A2(useRobot, robot);
	A2.join();
}

void useRobotA3(XmlRobot &robot) // use thread 3, green
{
	thread A3(useRobot, robot);
	A3.join();
}

void useRobotA4(XmlRobot &robot) // use thread 4, yellow
{
	thread A4(useRobot, robot);
	A4.join();
}

void useRobot(XmlRobot &robot)
{
	robot.Execute();
}