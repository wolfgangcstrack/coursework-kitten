/*
Lab 3 - Threading
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This is the header file for the XmlRobot class, which extends both the
given Robot class for this lab and the XmlNode class created in Lab 2 so
that XmlRobot nodes can be created by the XmlRegexIO class.
*/

#ifndef XML_ROBOT_H_
#define XML_ROBOT_H_

#include "Robot.h"
#include "XmlNode.h"

class XmlRobot : public Robot, public XmlNode
{
public:
	XmlRobot() {}
	~XmlRobot() {}
	// methods from Robot class
	bool Execute() { return command.Execute(); }
	void setOffOn(int value) { command.setOffOn(value); }
	void setError(int value) { command.setError(value); }
	void setSpeed(int value) { command.setSpeed(value); }
	void setHorizontal(int value) { command.setHorizontal(value); }
	void setVertical(int value) { command.setVertical(value); }
	void setTime(int value) { command.setTime(value); }
	// methods from XmlNode class
	void readData(const string &data);
private:
	// member variables from Robot
	Command command;
};

void XmlRobot::readData(const string &data)
{

}

#endif // XML_ROBOT_H_