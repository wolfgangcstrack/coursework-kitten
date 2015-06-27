/*
Lab 4 - Graphs and Lambda Expressions
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This header file has the class definition of Location, which extends
the XmlNode class.
*/

#ifndef COORDINATE_PAIR_H_
#define COORDINATE_PAIR_H_

#include "XmlNode.h"
#include <string>
using namespace std;

class Location : public XmlNode
{
private:
	string address;
	string city;
	string phone;
	string state;
	pair<double, double> coordinates;
public:
	// constructors and destructor
	Location() { coordinates = make_pair(0., 0.); }
	Location(const Location &cp);
	Location(
			const string &adr,
			const string &c,
			const string &pnum,
			const string &s,
			const pair<double, double> &cs);
	~Location() {}
	// getters/setters
	const string & getAddress() const                   { return address; }
	const string & getCity() const                      { return city; }
	const string & getPhoneNumber() const               { return phone; }
	const string & getState() const                     { return state; }
	const pair<double, double> & getCoordinates() const { return coordinates; }
	double getLatitude() const                          { return coordinates.first; }
	double getLongitude() const                         { return coordinates.second; }
	void setAddress(const string &adr)                  { address = adr; }
	void setCity(const string &c)                       { city = c; }
	void setPhoneNumber(const string &pnum)             { phone = pnum; }
	void setState(const string &s)                      { state = s; }
	void setCoordinates(const pair<double, double> &cs) { coordinates = cs; }
	void setLatitude(double latitude)                   { coordinates.first = latitude; }
	void setLongitude(double longitude)                 { coordinates.second = longitude; }
	// overridden methods from XmlNode
	void readData(const string &data);
	// other methods
	bool operator==(const Location &right)        { return (coordinates == right.coordinates); }
	friend ostream & operator<<(ostream &os, const Location &cpair);
};

Location::Location(const Location &cp)
{
	address = cp.address;
	city = cp.city;
	phone = cp.phone;
	state = cp.state;
	coordinates = cp.coordinates;
}

Location::Location(
		const string &adr,
		const string &c,
		const string &pnum,
		const string &s,
		const pair<double, double> &cs)
{
	address = adr;
	city = c;
	phone = pnum;
	state = s;
	coordinates = cs;
}

void Location::readData(const string &data)
{
	address = this->getString(data, "Address");
	city = this->getString(data, "City");
	phone = this->getString(data, "Phone");
	state = this->getString(data, "State");
	coordinates.first = stod(this->getString(data, "Latitude"));
	coordinates.second = stod(this->getString(data, "Longitude"));
}

ostream & operator<<(ostream &os, const Location &cpair)
{
	os << cpair.address << ", " << cpair.city << ", " << cpair.state
		<< ": (" << cpair.coordinates.first << ", " << cpair.coordinates.second << ")";

	return os;
}

#endif // COORDINATE_PAIR_H_