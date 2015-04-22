/*
Lab 0 - Variant #3 (Date arithmetic)
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This is the header file for the Date class.
*/

#pragma once

#include "Year.h"
#include <iostream>

class Date
{
private:
	Year year;
	Month month;
	Day day;
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
	bool operator>=(const Date &right);
	bool operator<=(const Date &right);
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