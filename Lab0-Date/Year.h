/*
Lab 0 - Variant #3 (Date arithmetic)
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This is the Year header file. Implementation is included here
instead of in a separate .cpp file.
*/

#pragma once

class Year
{
private:
	int year;
	bool isLeap;
public:
	// constructors
	Year() { year = 1; isLeap = isLeapYear(year); }
	Year(const Year &y) { year = y.year; isLeap = y.isLeap; }
	Year(int y) { year = ((y > 0) ? y : 1); isLeap = isLeapYear(year); }
	~Year() {}
	// getters
	int getYear() { return year; }
	bool isLeap() { return isLeap; }
	// setters
	void setYear(int y) { if (y > 0) year = y; isLeap = isLeapYear(year); }
	// other methods
	static bool isLeapYear(int yr) { return ((y % 400 == 0) || (y % 100 != 0 && y % 4 == 0)); }
};