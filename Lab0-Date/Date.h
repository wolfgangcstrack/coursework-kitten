/*
Lab 0 - Variant #3 (Date arithmetic)
Wolfgang C. Strack
16 April 2015
Windows 8 Visual C++ 2013

This is the header file for the Date class.
*/

#pragma once

#include <iostream>

class Date
{
private:
	// define month member variable type
	enum Month {
		January=1, February=2, March=3, April=4,
		May=5, June=6, July=7, August=8,
		September=9, October=10, November=11, December=12
	};
	struct Month_Day
	{
		Month month;
		int day;

		Month_Day() { month = January; day = 1; }
		Month_Day(const Month_Day &m) { month = m.month; day = m.day; }
		Month_Day(int m, int d) { month = static_cast<Month>(m); day = d; }
	};

	// member variables
	int year;
	Month_Day *monthday; // includes day
public:
	// constructors and destructor
	Date();
	Date(const Date &d);
	Date(int y, int m, int d);
	~Date();
	// getters
	int getYear() const;
	int getMonth() const;
	int getDay() const;
	// setters
	void setYear(int y);
	void setMonth(int m);
	void setDay(int d);
	// operator overloads
	Date & operator=(const Date &date);
	Date & operator+=(long days);
	Date & operator-=(long days);
	Date & operator++();
	Date & operator--();
	const Date operator+(long days);
	const Date operator-(long days);
	bool operator==(const Date &right);
	bool operator!=(const Date &right);
	bool operator>(const Date &right);
	bool operator<(const Date &right);
	friend std::ostream & operator<<(std::ostream &os, const Date &date);
	// other methods
	void addYears(int y);
	void addMonths(int m);
	void addDays(long d);
	// static methods
	static bool isLeapYear(int y);
	static bool validDay(int y, int m, int d); // checks if d is a valid number of days in mm/yyyy
	static int getDaysOfMonth(int y, int m); // returns the number of days in mm/yyyy
};