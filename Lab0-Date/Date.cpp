/*
Lab 0 - Variant #3 (Date arithmetic)
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This is the implementation file for the Date class.
Methods are sorted in the same order as they are in
the Date header file.
*/

#include "Date.h"


// constructors and destructor ------------------
Date::Date()
{
	year = 1;
	month = January;
	day = 1;
}

Date::Date(const Date &d)
{
	year = d.year;
	month = d.month;
	day = d.day;
}

Date::Date(int y, int m, int d)
{
	year = ((y > 0) ? y : 1);
	month = static_cast<Month>((m >= 1 && m <= 12 ? m : 1));
	day = (validDay(year, month, d) ? d : 1);
}

Date::~Date() {}

// getters --------------------------------------
int Date::getYear() const { return year; }
int Date::getMonth() const { return month; }
int Date::getDay() const { return day; }
// setters --------------------------------------
void Date::setYear(int y) { year = (y > 0 ? y : 1); }
void Date::setMonth(int m) { month = ((m > 0 && m <= 12) ? static_cast<Month>(m) : January); }
void Date::setDay(int d) { if (validDay(year, month, d)) day = d; }

// operator overloads ---------------------------
Date & Date::operator=(const Date &d)
{
	year = d.year;
	month = d.month;
	day = d.day;
	return *this;
}

Date & Date::operator+=(long days)
{
	if (days < 0) return (*this -= -days);
	int currMonth = month;
	int offset = 0;
	while (!validDay(year, currMonth, days))
	{
		offset = getDaysOfMonth(year, currMonth);
		days -= offset;
		if (++currMonth > December)
		{
			currMonth = January;
			year++;
		}
	}
	day += days;
	if (!validDay(year, currMonth, day))
	{
		offset = getDaysOfMonth(year, currMonth);
		day -= offset;
		if (++currMonth > December)
		{
			currMonth = January;
			year++;
		}
	}

	month = static_cast<Month>(currMonth);
	if (year < 1)
	{
		year = 1;
		month = January;
		day = 1;
	}
	return *this;
}

Date & Date::operator-=(long days)
{
	if (days < 0) return (*this += -days);
	int currMonth = month;
	int offset = 0;
	while (!validDay(year, currMonth, days))
	{
		if (--currMonth < January)
		{
			currMonth = December;
			year--;
		}
		offset = getDaysOfMonth(year, currMonth);
		days -= offset;
		
	}
	day -= days;
	if (day < 1)
	{
		if (--currMonth < January)
		{
			currMonth = December;
			year--;
		}
		offset = getDaysOfMonth(year, currMonth);
		day += offset;
	}

	month = static_cast<Month>(currMonth);
	if (year < 1)
	{
		year = 1;
		month = January;
		day = 1;
	}
	return *this;
}

Date & Date::operator++() { return (*this += 1); }
Date & Date::operator--() { return (*this -= 1); }
const Date Date::operator+(long days) { return (Date(*this) += days); }
const Date Date::operator-(long days) { return (Date(*this) -= days); }

bool Date::operator==(const Date &right)
{
	return (year == right.year && 
		month == right.month && 
		day == right.day);
}

bool Date::operator!=(const Date &right) { return !(*this == right); }

bool Date::operator>(const Date &right)
{
	if (year == right.year)
	{
		if (month == right.month)
		{
			if (day == right.day)
				return false;
			return (day > right.day);
		}
		return (month > right.month);
	}
	return (year > right.year);
}

bool Date::operator<(const Date &right)
{
	if (year == right.year)
	{
		if (month == right.month)
		{
			if (day == right.day)
				return false;
			return (day < right.day);
		}
		return (month < right.month);
	}
	return (year < right.year);
}

bool Date::operator>=(const Date &right) { return (*this == right || *this > right); }
bool Date::operator<=(const Date &right) { return (*this == right || *this < right); }

std::ostream & operator<<(std::ostream &os, const Date &date)
{
	os << date.year << (date.month < 10 ? "/0" : "/") 
		<< date.month << (date.day < 10 ? "/0" : "/") 
		<< date.day;
	return os;
}

// other methods --------------------------------
void Date::addYears(int y)
{
	year += y;
	if (year < 1)
	{
		year = 1;
		month = January;
		day = 1;
	}
}

void Date::addMonths(int m)
{
	int currMonth = month;
	while (m > 0)
	{
		m--;
		if (++currMonth > December)
		{
			currMonth = January;
			year++;
		}
	}
	while (m < 0)
	{
		if (--currMonth < January)
		{
			currMonth = December;
			year--;
		}
		m++;
	}

	month = static_cast<Month>(currMonth);
	if (year < 1)
	{
		year = 1;
		month = January;
		day = 1;
	}
}

void Date::addDays(long d) // same as using operator+= or operator-=
{
	*this += d;
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

int Date::getDaysOfMonth(int y, int m)
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
