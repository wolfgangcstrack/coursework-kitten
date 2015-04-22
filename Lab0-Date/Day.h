/*
Lab 0 - Variant #3 (Date arithmetic)
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This is the Day header file. Implementation is included here
instead of in a separate .cpp file.
*/

#pragma once

class Day
{
private:
	int day;
public:
	// constructors and destructor
	Day() { day = 1; }
	Day(const Day &d) { day = d.day; }
	Day(int d) { day = (d > 0 ? d : 1); }
	~Day() {}
	// getter
	int getDay() const { return day; }
	// setter
	void setDay(int d) { if (d > 0) day = d; }
};