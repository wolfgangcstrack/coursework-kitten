/*
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This header file contains the ThreadedXmlRegexIO class. This class extends
the XmlRegexIO class and adds multithreaded support as well as a new method
for parsing multiple files at once.
*/

#ifndef THREADED_USER_PARSER_H_
#define THREADED_USER_PARSER_H_

#include "XmlRegexIO.h"
#include "XmlNode.h"
#include "User.h"
#include <thread>
#include <mutex>
#include <list>

class ThreadedUserParser : public XmlRegexIO
{
private:
	std::mutex nodelist_mutex;
	XmlNodeList nodelist;

	void parseFile(const std::string &filename); // used by threads to parse multiple file at once
public:
	// constructor/destructor
	ThreadedUserParser() {}
	~ThreadedUserParser(){}
	// new methods
	const XmlNodeList & parseUserFiles(std::vector<std::string> filenames);
	// other methods used are inherited from XmlRegexIO
};

void ThreadedUserParser::parseFile(const std::string &filename)
{
	std::vector<std::string> tags;
	this->getAllMatches(filename, tags);

	for (auto i = tags.begin(); i != tags.end(); ++i)
	{
		// parse user from file
		XmlNode *newUser = new User;
		newUser->setXMLTags(*i);
		newUser->readData(*i);

		// insert new user node to thread-safe nodelist
		nodelist_mutex.lock();
		nodelist.push_back(newUser);
		nodelist_mutex.unlock();
	}
}

const XmlNodeList & ThreadedUserParser::parseUserFiles(std::vector<std::string> filenames)
{
	std::list<std::thread> threads;

	// run separate thread for each file
	for (auto filename = filenames.begin(); filename != filenames.end(); ++filename)
	{
		threads.push_back(
			std::thread(&ThreadedUserParser::parseFile, *this, *filename));
		// parseFile() modified this->nodelist, which
		// will be the return value of this function
	}

	// join threads
	for (auto i = threads.begin(); i != threads.end(); ++i)
	{
		i->join();
	}

	return nodelist;
}

#endif // THREADED_USER_PARSER_H_