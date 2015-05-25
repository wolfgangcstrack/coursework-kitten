/*
Lab 4 - Graphs and Lambda Expressions
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This header file has the class definition of CoordinatePair, which extends
the XmlNode class.
*/

#ifndef COORDINATE_PAIR_H_
#define COORDINATE_PAIR_H_

#include "XmlNode.h"
#include <string>
using namespace std;

class CoordinatePair : XmlNode
{
private:
	string address;
	string city;
	string phone;
	pair<double, double> coordinates;
public:
	// constructors and destructor
	CoordinatePair();
	CoordinatePair(const CoordinatePair &cp);
	CoordinatePair(const string &adr, const string &c, const string &pnum, const string &cs);
	~CoordinatePair();
	// getters/setters
	const string & getAddress() const                   { return address; }
	const string & getCity() const                      { return city; }
	const string & getPhoneNumber() const               { return phone; }
	const pair<double, double> & getCoordinates() const { return coordinates; }
	double getLatitude() const                          { return coordinates.first; }
	double getLongitude() const                         { return coordinates.second; }
	void setAddress(const string &adr)                  { address = adr; }
	void setCity(const string &c)                       { city = c; }
	void setPhoneNumber(const string &pnum)             { phone = pnum; }
	void setCoordinates(const pair<double, double> &cs) { coordinates = cs; }
	void setLatitude(double latitude)                   { coordinates.first = latitude; }
	void setLongitude(double longitude)                 { coordinates.second = longitude; }
	// overridden methods from XmlNode
	void readData(const string &data);
};

#endif // COORDINATE_PAIR_H_