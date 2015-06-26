/*
Lab 3 - Threading
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This is the main application for this lab.

NOTE: An excerpt of the execution results is included at the end of this
file. It is only an excerpt due to the length of the execution results and
the fact that ConsoleColor.h is used.
*/

#include "Global.h"

#include "ConsoleColor.h"
#include "XmlNodeList.h"
#include "XmlRegexIO.h"
#include "RobotMotor.h"
#include "XmlRobot.h" // XmlRobot class extends the given Robot class for this lab

// the following methods are called from main()
void readTagsFromFile(XmlRegexIO &xRIO, const string &filename, vector<string> &tags);
void instantiateRobotCommands(XmlRegexIO &xRIO, const vector<string> &tags, XmlNodeList &rcList);
void executeRobotCommands(XmlNodeList &rcList);

// the following method is called from executeRobotCommands()
// In essence, it is a "wrapper" function that supports console color
void useRobot(XmlRobot &robot, ostream& color(ostream &s));

int main()
{
	RobotMotor rMotor;
	string filename = "RobotData.xml";
	XmlRegexIO xRIO("<command>\\n.*?<robot>.*\\n.*?<offon>.*\\n.*?<speed>.*\\n.*?<horizontal>.*\\n.*?<vertical>.*\\n.*?<time>.*\\n.*?</command>");

	cout << "This is a demonstration of Lab 3: Threading\n\n";

	cout << "Reading data and instantiating Robots from file " << filename << "...\n\n" << endl;
	rMotor.readCommands(filename, xRIO);

	cout << "Execution started:\n\n" << endl;
	rMotor.executeCommands();

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
			// cout statement mainly for debugging purposes
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
	//robot.Execute(color);
}

/* EXCERPT OF EXECUTION RESULTS
This is a demonstration of Lab 3: Threading

Robot A1 (thread 1) will be executed with the color red.
Robot A2 (thread 2) will be executed with the color blue.
Robot A3 (thread 3) will be executed with the color green.
Robot A4 (thread 4) will be executed with the color yellow.

Reading tags from file RobotData.xml...


Instantiating Robots...


Execution started:


Command = On: 1 Speed: 10       Horizontal: 10  Vertical: 01    Time: 231
Command = On: 1 Speed: 10       Horizontal: 10  Vertical: 01    Time: 206
Command = On: 1 Speed: 01       Horizontal: 01  Vertical: 01    Time: 5
Command = On: 1 Speed: 01       Horizontal: 10  Vertical: 10    Time: 154
Command = On: 1 Speed: 01       Horizontal: 10  Vertical: 10    Time: 84
Command = On: 1 Speed: 01       Horizontal: 10  Vertical: 01    Time: 101
Command = On: 1 Speed: 01       Horizontal: 10  Vertical: 01    Time: 190
Command = On: 1 Speed: 01       Horizontal: 10  Vertical: 01    Time: 92
Command = On: 1 Speed: 01       Horizontal: 10  Vertical: 10    Time: 246
Command = On: 1 Speed: 01       Horizontal: 01  Vertical: 01    Time: 17
Command = On: 1 Speed: 10       Horizontal: 10  Vertical: 10    Time: 135
Command = On: 1 Speed: 10       Horizontal: 10  Vertical: 10    Time: 184
Command = On: 1 Speed: 10       Horizontal: 10  Vertical: 10    Time: 114
Command = On: 1 Speed: 01       Horizontal: 01  Vertical: 10    Time: 143
Command = On: 1 Speed: 10       Horizontal: 10  Vertical: 01    Time: 147
Command = On: 1 Speed: 10       Horizontal: 01  Vertical: 01    Time: 203
Command = On: 1 Speed: 01       Horizontal: 01  Vertical: 01    Time: 128
Command = On: 1 Speed: 10       Horizontal: 10  Vertical: 01    Time: 21
Command = On: 1 Speed: 01       Horizontal: 01  Vertical: 10    Time: 23
Command = On: 1 Speed: 01       Horizontal: 01  Vertical: 01    Time: 3
Command = On: 1 Speed: 01       Horizontal: 10  Vertical: 10    Time: 135
Command = On: 1 Speed: 10       Horizontal: 10  Vertical: 01    Time: 220
Command = On: 1 Speed: 01       Horizontal: 01  Vertical: 01    Time: 224
Command = On: 1 Speed: 01       Horizontal: 10  Vertical: 01    Time: 47
Command = On: 1 Speed: 10       Horizontal: 10  Vertical: 01    Time: 213
Command = On: 1 Speed: 10       Horizontal: 01  Vertical: 10    Time: 10
Command = On: 1 Speed: 10       Horizontal: 01  Vertical: 01    Time: 232
Command = On: 1 Speed: 01       Horizontal: 10  Vertical: 10    Time: 99
Command = On: 1 Speed: 10       Horizontal: 01  Vertical: 10    Time: 101
Command = On: 1 Speed: 01       Horizontal: 01  Vertical: 10    Time: 253
Command = On: 1 Speed: 01       Horizontal: 01  Vertical: 10    Time: 162
.
.
.
*/