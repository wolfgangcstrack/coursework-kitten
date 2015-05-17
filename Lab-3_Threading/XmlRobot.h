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

#include "Global.h"

#include "Robot.h"
#include "XmlNode.h"
#include "ConsoleColor.h"

class ColorCommand : public Command
{
public:
	ColorCommand() { Reset(); }

	// overloaded methods from Command class
	bool Execute(ostream& color(ostream &s))
	{
		bool bvalid = Validate();
		if (errorcode == OK)
		{
			execution_guard.lock();
			std::cout << color << *this << endl;
			execution_guard.unlock();
			this_thread::sleep_for(chrono::milliseconds(time.to_ulong()));
		}
		Reset();
		return bvalid;
	}

	friend ostream& operator << (ostream& out, ColorCommand& command)
	{
		out << "Command = On: " << command.offon << '\t';
		out << "Speed: " << command.speed << '\t';
		out << "Horizontal: " << command.horizontal << '\t';
		out << "Vertical: " << command.vertical << '\t';
		out << "Time: " << command.time.to_ulong() << endl;
		return out;
	}
};

class XmlRobot : public Robot, public XmlNode
{
public:
	XmlRobot() {}
	~XmlRobot() {}

	// methods from Robot class
	bool Execute(ostream& color(ostream &s)) { return command.Execute(color); }
	void setOffOn(int value) { command.setOffOn(value); }
	void setError(int value) { command.setError(value); }
	void setSpeed(int value) { command.setSpeed(value); }
	void setHorizontal(int value) { command.setHorizontal(value); }
	void setVertical(int value) { command.setVertical(value); }
	void setTime(int value) { command.setTime(value); }

	// methods from XmlNode class
	void readData(const string &data);

	// other methods
	const string & getRobotNumber() const { return robotnum; }
	void setRobotNumber(const string &rnum) { robotnum = rnum; }
private:
	// member variables from Robot
	ColorCommand command;

	// extra member variable for Robot number (A1, A2, A3, A4)
	string robotnum;
};

/*
This method sets XmlRobot's member ColorCommand variable values instead of
setting hard-coded member types like they were set in the custom classes
for Lab 2.
*/
void XmlRobot::readData(const string &data)
{
	setRobotNumber(getString(data, regex("<robot>.*?</robot>")));
	command.setOffOn(getString(data, regex("<offon>.*?</offon>")) == "On" ? ON : OFF);
	command.setSpeed(getString(data, regex("<speed>.*?</speed>")) == "High" ? HIGH : LOW);
	command.setHorizontal(getString(data, regex("<horizontal>.*?</horizontal>")) == "Clockwise" ? CLOCKWISE : COUNTERCLOCKWISE);
	command.setVertical(getString(data, regex("<vertical>.*?</vertical>")) == "Up" ? UP : DOWN);
	command.setTime(get_ulong(data, regex("<time>[0-9]*")));
}

#endif // XML_ROBOT_H_