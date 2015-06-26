/*
Lab 0 - Variant #3 (Date arithmetic)
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This is the Year header file. Implementation is included here
instead of in a separate .cpp file.
*/

#pragma once

#include "Month.h"

class Year
{
private:
	int year;
	bool isLeap;

	Month *months;
public:
	// constructors and destructor
	Year() { year = 1; isLeap = isLeapYear(year); }
	Year(const Year &y) { year = y.year; isLeap = y.isLeap; }
	Year(int y) { year = ((y > 0) ? y : 1); isLeap = isLeapYear(year); }
	~Year() {}
	// getters
	int getYear() const { return year; }
	bool isLeapYear() const { return isLeap; }
	// setters
	void setYear(int y) { if (y > 0) year = y; isLeap = isLeapYear(year); }
	// other methods
	static bool isLeapYear(int yr) { return ((yr % 400 == 0) || (yr % 100 != 0 && yr % 4 == 0)); }
};