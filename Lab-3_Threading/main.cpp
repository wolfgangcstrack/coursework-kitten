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
void openDataFile(ifstream &ifs, const string &filename);
void readTagsFromFile(const ifstream &ifs, vector<string> &tags);
void instantiateRobotCommands(const vector<string> &tags, vector<unique_ptr<XmlNode>> &robotCommands);
void executeRobotCommands(const vector<unique_ptr<XmlNode>> &robotCommands);

// the following methods are called from executeRobotCommands()
void useRobotA1(const XmlRobot &robot); // use thread 1
void useRobotA2(const XmlRobot &robot); // use thread 2
void useRobotA3(const XmlRobot &robot); // use thread 3
void useRobotA4(const XmlRobot &robot); // use thread 4

int main()
{
	string filename = "RobotData.xml";
	vector<string> tags;
	vector<unique_ptr<XmlNode>> robotCommands;
	ifstream ifs;

	openDataFile(ifs, filename);
	readTagsFromFile(ifs, tags);
	instantiateRobotCommands(tags, robotCommands);
	executeRobotCommands(robotCommands); // calls the useRobot methods
}