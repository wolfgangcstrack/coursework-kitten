/*
Lab 3 - Threading
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This is the header file for the Robot class, implementation included.

NOTE: a single change was made to the Command class - commenting out the
"private" access specifier. In doing so, Command's member variables are
now "protected" rather than "private" so that derived classes can access
and use these member variables.
*/

#ifndef ROBOT_H_
#define ROBOT_H_

#include <bitset>
#include <thread>
#include <iostream>
using namespace std;

/* XML Excerpt

<command>
	<robot>A4</robot>
	<offon>On</offon>
	<speed>Low</speed>
	<horizontal>CounterClockwise</horizontal>
	<vertical>Up</vertical>
	<time>190</time>
</command>

*/

enum properties 
{
	ZERO=0,
	OFF=0, ON=1, 
	INVALID=0, OK=1,
	LOW=1, HIGH=2,
	CLOCKWISE=1, COUNTERCLOCKWISE=2,
	UP=1, DOWN=2,
	MINTIME=1, MAXTIME=255
};

class Command
{
public:
	Command() { Reset(); }
	// bit 0
	void setOffOn(int value) { offon = value; }
	// bit 1
	void setError(int value) { errorcode = value; }
	// bits 2 & 3
	void setSpeed(int value) { speed = value; }
	// bits 4 & 5
	void setHorizontal(int value) { horizontal = value; }
	// bits 6 & 7
	void setVertical(int value) { vertical = value; }
	// bits 8 - 15
	void setTime(int value) { time = value; }
	bool Execute()
	{
		bool bvalid = Validate();
		if (errorcode == OK)
		{
			cout << *this;
			this_thread::sleep_for(chrono::milliseconds(time.to_ulong()));
		}
		Reset();
		return bvalid;
	}
	friend ostream& operator << (ostream& out, Command& command)
	{
		out << "Command = On: " << command.offon << '\t';
		out << "Speed: " << command.speed << '\t';
		out << "Horizontal: " << command.horizontal << '\t';
		out << "Vertical: " << command.vertical << '\t';
		out << "Time: " << command.time.to_ulong() << endl;
		return out;
	}
protected:
	bool testValue(int value,int mask)
	{
		if (value && (value ^ mask))
			return true;
		return false;
	}
	bool Validate()
	{
		bool bvalid = false;
		if (offon.to_ulong() & ON)
		{
			bvalid = true;
			if (!testValue(speed.to_ulong(),0x03))
				bvalid = false;
			if (!testValue(horizontal.to_ulong(),0x03))
				bvalid = false;
			if (!testValue(vertical.to_ulong(),0x03))
				bvalid = false;
			if (!testValue(time.to_ulong(),0xFF))
				bvalid = false;
		}
		if (!bvalid)
			errorcode = INVALID;
		return errorcode.to_ullong();
	}
	void Reset()
	{
		offon = OFF;
		errorcode = OK;
		speed = ZERO;
		horizontal = ZERO;
		vertical = ZERO;
		time = ZERO;
	}
//private:
	// 0 = off 1 = on
	bitset<1> offon;
	// 0 = invalid 1 = ok
	bitset<1> errorcode;
	// 1 = low 2 = high
	bitset<2> speed;
	// 1 = clockwise 2 = counter-clockwise
	bitset<2> horizontal;
	// 1 = up 2 = down
	bitset<2> vertical;
	// time (maximum 255 ms)
	bitset<8> time;
};

class Robot
{
public:
	Robot() { }
	virtual bool Execute() { return command.Execute(); }
	virtual void setOffOn(int value) { command.setOffOn(value); }
	virtual void setError(int value) { command.setError(value); }
	virtual void setSpeed(int value) { command.setSpeed(value); }
	virtual void setHorizontal(int value) { command.setHorizontal(value); }
	virtual void setVertical(int value) { command.setVertical(value); }
	virtual void setTime(int value) { command.setTime(value); }
private:
	Command command;
};

/*// Test Bench
void RobotTest()
{
	Robot robot;

	// invalid
	cout << ((robot.Execute() == OK) ? "OK\n" : "EROR\n");

	// valid
	robot.setOffOn(ON);
	robot.setSpeed(HIGH);
	robot.setHorizontal(COUNTERCLOCKWISE);
	robot.setVertical(UP);
	robot.setTime(128);
	cout << ((robot.Execute() == OK) ? "OK\n" : "EROR\n"); 
}

void main()
{
	RobotTest();
}
*/

#endif // ROBOT_H_