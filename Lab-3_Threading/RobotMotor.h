/*
Lab 3 - Threading
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This is the RobotMotor class which executes Robot commands in separate
threads for specific robots.
*/

#include "Global.h"
#include "XmlNodeList.h"
#include "XmlRegexIO.h"
#include "XmlRobot.h"

class RobotMotor
{
private:
	// should have a 1:1 mapping of robotArm:thread with identical keys
	map<string, XmlNodeList> robotArms;
	map<string, shared_ptr<thread>> threads;

	// function to pass to separate threads
	void executeRobots(XmlNodeList &robotList, ostream& color(ostream &s))
	{
		string robotNum = dynamic_pointer_cast<XmlRobot>(robotList.front())->getClassName();
		for (int i = 0; i < robotList.size(); i++)
		{
			dynamic_pointer_cast<XmlRobot>(robotList[i])->Execute(color);
		}
	}
public:
	// constructors and destructor
	RobotMotor() {}
	~RobotMotor() {}
	// getters/setters (mainly for debugging)
	const map<string, XmlNodeList> & getRobotArms() { return robotArms; }
	const map<string, shared_ptr<thread>> & getThreads() { return threads; }
	void setRobotArms(const map<string, XmlNodeList> &rA) { robotArms = rA; }
	void setThreads(const map<string, shared_ptr<thread>> ts) { threads = ts; }
	// other methods
	bool readCommands(const string &filename, XmlRegexIO &xRIO);
	void executeCommands();
};

bool RobotMotor::readCommands(const string &filename, XmlRegexIO &xRIO)
{
	vector<string> tags;

	if (!xRIO.getAllMatches(filename, tags))
	{
		std::cout << "Error in file: " << filename << endl;
		return false;
	}

	for (int i = 0; i < tags.size(); i++)
	{
		shared_ptr<XmlNode> robotPtr(new XmlRobot());

		robotPtr->setXMLTags(tags[i]); // stores the tags being read from (mainly for debugging)

		if (!xRIO.getXmlDataFromString(tags[i], *robotPtr))
		{
			std::cout << "Error in instantiating Robots!\n";
			return false;
		}

		// cast the XmlNode to an XmlRobot to be able to call its method for getRobotNumber, which will be the key
		// then, accessing that key in the map, insert the XmlNode into the XmlNodeList at that point in the map
		robotArms[dynamic_pointer_cast<XmlRobot>(robotPtr)->getRobotNumber()].push_front(robotPtr);
	}
}

void RobotMotor::executeCommands()
{
	execution_guard.lock();
	int color = 0;
	ostream &col(ostream &s);

	for (map<string, XmlNodeList>::iterator it = robotArms.begin(); it != robotArms.end(); ++it)
	{
		std::cout << white;
		string robotKey = it->first;

		std::cout << "Robot " << robotKey << " will be printed in ";

		switch (color)
		{
		case 0:
			std::cout << yellow << "yellow";
			threads[robotKey] = shared_ptr<thread>(new thread(&RobotMotor::executeRobots, *this, it->second, yellow));
			break;
		case 1:
			std::cout << red << "red";
			threads[robotKey] = shared_ptr<thread>(new thread(&RobotMotor::executeRobots, *this, it->second, red));
			break;
		case 2:
			std::cout << blue << "blue";
			threads[robotKey] = shared_ptr<thread>(new thread(&RobotMotor::executeRobots, *this, it->second, blue));
			break;
		case 3:
			std::cout << green << "green";
			threads[robotKey] = shared_ptr<thread>(new thread(&RobotMotor::executeRobots, *this, it->second, green));
			break;
		case 4:
			std::cout << "white";
			threads[robotKey] = shared_ptr<thread>(new thread(&RobotMotor::executeRobots, *this, it->second, white));
			break;
		default:
			std::cout << "Error in color chooser." << endl;
		}
		std::cout << endl;

		if (++color == 5) // reset color chooser if it goes over 4
		{
			color = 0;
		}
	}

	cout << white;
	execution_guard.unlock();

	for (map<string, shared_ptr<thread>>::iterator it = threads.begin(); it != threads.end(); ++it)
	{
		it->second->join();
	}

	/*
	thread A1; // red console font
	thread A2; // blue console font
	thread A3; // green console font
	thread A4; // yellow console font

	while (!rcList.empty())
	{
		shared_ptr<XmlRobot> robot(dynamic_pointer_cast<XmlRobot>(rcList.front()));

		if (robot->getRobotNumber().length() < 2)
		{
			// std::cout statement mainly for debugging purposes
			std::cout << "Robot error: " << robot->getXMLTags() << endl;
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
			std::cout << white << "Robot number error!\n";
			return;
		}

		rcList.pop_front();
	}

	std::cout << white; // reset console font color
	*/
}