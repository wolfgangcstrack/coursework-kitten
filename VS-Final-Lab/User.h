/*
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This header file contains the User class, the data in this lab which is
represented in XML nodes.
*/

#ifndef XML_USER_H_
#define XML_USER_H_

#include "XmlNode.h"
#include <string>

class User : public XmlNode
{
private:
	enum dataLabels {USERNAME, LASTNAME, FIRSTNAME};

	std::string data [3];
public:
	// constructors and destructor
	User() {}
	User(const User &user) { std::copy(user.data, user.data + 3, data); }
	~User() {}
	// getters/setters
	const std::string & getUserName() const       { return data[USERNAME]; }
	const std::string & getLastName() const       { return data[LASTNAME]; }
	const std::string & getFirstName() const      { return data[FIRSTNAME]; }
	void setUserName(const std::string &newName)  { data[USERNAME] = newName; }
	void setLastName(const std::string &newName)  { data[LASTNAME] = newName; }
	void setFirstName(const std::string &newName) { data[FIRSTNAME] = newName; }
	// overloaded method from XmlNode
	void readData(const std::string &data);
	std::string toString();
};

void User::readData(const std::string &data)
{
	size_t bpos = data.find("<username>") + 10, length = data.find("</username>") - bpos;
	this->data[USERNAME] = data.substr(bpos, length);

	bpos = data.find("<last>") + 6, length = data.find("</last>") - bpos;
	this->data[LASTNAME] = data.substr(bpos, length);

	bpos = data.find("<first>") + 7, length = data.find("</first>") - bpos;
	this->data[FIRSTNAME] = data.substr(bpos, length);
}

std::string User::toString()
{
	return "Username: " + data[USERNAME] + '\n'
		+ "\tName (last, first): " + data[LASTNAME] + ", " + data[FIRSTNAME];
}

#endif // XML_USER_H_