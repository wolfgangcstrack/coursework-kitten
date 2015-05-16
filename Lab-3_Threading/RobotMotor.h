/*
Lab 3 - Threading
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This is the RobotMotor class which executes Robot commands in separate
threads for specific robots.
*/

#include "XmlNodeList.h"
#include "XmlRegexIO.h"
#include "XmlRobot.h"
#include <memory>
#include <string>
#include <map>
using namespace std;

class RobotMotor
{
private:
	map<string, XmlNodeList> robotArms;
	map<string, unique_ptr<thread>> threads;
public:
	// constructors and destructor
	RobotMotor() {}
	~RobotMotor() {}
	// getters/setters (mainly for debugging)
	const map<string, XmlNodeList> & getRobotArms() { return robotArms; }
	const map<string, unique_ptr<thread>> & getThreads() { return threads; }
	void setRobotArms(const map<string, XmlNodeList> &rA) { robotArms = rA; }
	void setThreads(const map<string, unique_ptr<thread>> ts) { threads = ts; }
	// other methods
	bool readCommands(const string &filename, XmlRegexIO xRIO);
	void executeCommands();
};

