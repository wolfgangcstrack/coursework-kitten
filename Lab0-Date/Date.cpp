/*
Lab 0 - Variant #3 (Date arithmetic)
Wolfgang C. Strack
16 April 2015
Windows 8 Visual C++ 2013

This is the implementation file for the Date class.
*/

#include "Date.h"


// constructors and destructor ------------------
Date::Date()
{
	year = 1;
	monthday = new Month_Day();
}

Date::Date(const Date &d)
{
	year = d.year;
	monthday = new Month_Day(*d.monthday);
}

Date::Date(int y, int m, int d)
{
	year = ((y > 0) ? y : 1);
	if (m < 1 || m>12) m = 1;
	monthday = new Month_Day(m, (validDay(year, m, d) ? d : 1));
}

Date::~Date() { delete monthday; }

// getters --------------------------------------
int Date::getYear() const { return year; }
int Date::getMonth() const { return monthday->month; }
int Date::getDay() const { return monthday->day; }
// setters --------------------------------------
void Date::setYear(int y) { year = (y > 0 ? y : 1); }
void Date::setMonth(int m) { monthday->month = ((m > 0 && m <= 12) ? static_cast<Month>(m) : January); }
void Date::setDay(int d) { if (validDay(year, monthday->month, d)) monthday->day = d; }

// operator overloads ---------------------------
Date & Date::operator=(const Date &d)
{
	year = d.year;
	monthday->month = d.monthday->month;
	monthday->day = d.monthday->day;
	return *this;
}

Date & Date::operator+=(long days)
{
	if (days < 0) return (*this -= -days);
	int currMonth = monthday->month;
	int offset = 0;
	while (!validDay(year, currMonth, days))
	{
		offset = getDays(year, currMonth);
		days -= offset;
		if (++currMonth > December)
		{
			currMonth = January;
			year++;
		}
	}
	monthday->day += days;
	if (!validDay(year, currMonth, monthday->day))
	{
		offset = getDays(year, currMonth);
		monthday->day -= offset;
		if (++currMonth > December)
		{
			currMonth = January;
			year++;
		}
	}
	monthday->month = static_cast<Month>(currMonth);
	return *this;
}

Date & Date::operator-=(long days)
{
	if (days < 0) return (*this += -days);
	int currMonth = monthday->month;
	int offset = 0;
	while (!validDay(year, currMonth, days))
	{
		if (--currMonth < January)
		{
			currMonth = December;
			year--;
		}
		offset = getDays(year, currMonth);
		days -= offset;
		
	}
	monthday->day -= days;
	if (monthday->day < 1)
	{
		if (--currMonth < January)
		{
			currMonth = December;
			year--;
		}
		offset = getDays(year, currMonth);
		monthday->day += offset;
	}
	monthday->month = static_cast<Month>(currMonth);
	return *this;
}

Date & Date::operator++() { return (*this += 1); }
Date & Date::operator--() { return (*this -= 1); }
const Date Date::operator+(long days) { return (Date(*this) += days); }
const Date Date::operator-(long days) { return (Date(*this) -= days); }

bool Date::operator==(const Date &right)
{
	return (year == right.year && 
		monthday->month == right.monthday->month && 
		monthday->day == right.monthday->day);
}

bool Date::operator!=(const Date &right) { return !(*this == right); }

bool Date::operator>(const Date &right)
{
	if (year == right.year)
	{
		if (monthday->month == right.monthday->month)
		{
			if (monthday->day == right.monthday->day)
				return false;
			return (monthday->day > right.monthday->day);
		}
		return (monthday->month > right.monthday->month);
	}
	return (year > right.year);
}

bool Date::operator<(const Date &right)
{
	if (year == right.year)
	{
		if (monthday->month == right.monthday->month)
		{
			if (monthday->day == right.monthday->day)
				return false;
			return (monthday->day < right.monthday->day);
		}
		return (monthday->month < right.monthday->month);
	}
	return (year < right.year);
}

std::ostream & operator<<(std::ostream &os, const Date &date)
{
	os << date.year << (date.monthday->month < 10 ? "-0" : "-") 
		<< date.monthday->month << (date.monthday->day < 10 ? "-0" : "-") 
		<< date.monthday->day;
	return os;
}

// static methods -------------------------------
bool Date::isLeapYear(int y)
{
	// Algorithm to determine leap year:
	// 1. If a year is divisible by 400, see 4 else see 2
	// 2. If a year is divisible by 100, see 5 else see 3
	// 3. If a year is divisible by 4, see 4 else see 5
	// 4. The year is a leap year
	// 5. The year is not a leap year
	return ((y % 400 == 0) || (y % 100 != 0 && y % 4 == 0));
}

bool Date::validDay(int y, int m, int d)
{
	if (d < 0)
		return false;
	switch (m)
	{
	case 4: case 6: case 9: case 11:
		if (d > 30)
			return false;
		break;
	case 2:
		if (Date::isLeapYear(y) && d > 29)
			return false;
		else if (d > 28)
			return false;
		break;
	default: // case 1, 3, 5, 7, 8, 10, and 12
		if (d > 31)
			return false;
	}
	return true;
}

int Date::getDays(int y, int m)
{
	switch (m)
	{
	case 4: case 6: case 9: case 11:
		return 30;
	case 2:
		if (Date::isLeapYear(y))
			return 29;
		else
			return 28;
	default: // case 1, 3, 5, 7, 8, 10, and 12
		return 31;
	}
}