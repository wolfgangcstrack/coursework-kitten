/*
Lab 3 - Threading
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This is the main application for this lab.
*/

#include "Robot.h"
using namespace std;

void RobotTest()
{
	Robot robot;

	// invalid
	cout << ((robot.Execute() == OK) ? "OK\n" : "ERROR\n");

	// valid
	robot.setOffOn(ON);
	robot.setSpeed(HIGH);
	robot.setHorizontal(COUNTERCLOCKWISE);
	robot.setVertical(UP);
	robot.setTime(128);
	cout << ((robot.Execute() == OK) ? "OK\n" : "ERROR\n");
}

void main()
{
	RobotTest();
}