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
Date::Date() {}

Date::Date(const Date &d)
{
	year = Year(d.year);
	month = Month(d.month);
	day = Day(d.day);
}

Date::Date(int y, int m, int d)
{
	year = Year(((y > 0) ? y : 1));
	month = Month(m >= 1 && m <= 12 ? m : 1);
	month.setNumberOfDays(getDaysOfMonth(year.getYear(), month.getMonth()));
	day = Day(validDay(year.getYear(), month.getMonth(), d) ? d : 1);
}

Date::~Date() {}

// getters --------------------------------------
int Date::getYear() const { return year.getYear(); }
int Date::getMonth() const { return month.getMonth(); }
int Date::getDay() const { return day.getDay(); }
// setters --------------------------------------
void Date::setYear(int y) { year.setYear(y); }
void Date::setMonth(int m)
{
	month.setMonth(m);
	month.setNumberOfDays(getDaysOfMonth(year.getYear(), month.getMonth()));
	if (day.getDay() > month.getNumberOfDays())
		day.setDay(1);
}
void Date::setDay(int d) { if (validDay(year.getYear(), month.getMonth(), d)) day.setDay(d); }

// operator overloads ---------------------------
Date & Date::operator=(const Date &d)
{
	year = Year(d.year);
	month = Month(d.month);
	day = Day(d.day);
	return *this;
}

Date & Date::operator+=(long days)
{
	if (days < 0)
		return (*this -= -days);

	int currYear = year.getYear();
	int currMonth = month.getMonth();
	int currDay = day.getDay();
	int offset = 0;

	while (!validDay(currYear, currMonth, days))
	{
		offset = getDaysOfMonth(currYear, currMonth);
		days -= offset;
		if (++currMonth > 12)
		{
			currMonth = 1;
			currYear++;
		}
	}
	currDay += days;
	if (!validDay(currYear, currMonth, currDay))
	{
		offset = getDaysOfMonth(currYear, currMonth);
		currDay -= offset;
		if (++currMonth > 12)
		{
			currMonth = 1;
			currYear++;
		}
	}

	if (currYear < 1)
		currYear = currMonth = currDay = 1;

	year.setYear(currYear);
	month.setMonth(currMonth);
	month.setNumberOfDays(getDaysOfMonth(currYear, currMonth));
	day.setDay(currDay);

	return *this;
}

Date & Date::operator-=(long days)
{
	if (days < 0)
		return (*this += -days);

	int currYear = year.getYear();
	int currMonth = month.getMonth();
	int currDay = day.getDay();
	int offset = 0;

	while (!validDay(currYear, currMonth, days))
	{
		if (--currMonth < 1)
		{
			currMonth = 12;
			currYear--;
		}
		offset = getDaysOfMonth(currYear, currMonth);
		days -= offset;
		
	}
	currDay -= days;
	if (currDay < 1)
	{
		if (--currMonth < 1)
		{
			currMonth = 12;
			currYear--;
		}
		offset = getDaysOfMonth(currYear, currMonth);
		currDay += offset;
	}

	if (currYear < 1)
		currYear = currMonth = currDay = 1;

	year.setYear(currYear);
	month.setMonth(currMonth);
	month.setNumberOfDays(getDaysOfMonth(currYear, currMonth));
	day.setDay(currDay);

	return *this;
}

Date & Date::operator++() { return (*this += 1); }
Date & Date::operator--() { return (*this -= 1); }
const Date Date::operator+(long days) { return (Date(*this) += days); }
const Date Date::operator-(long days) { return (Date(*this) -= days); }

bool Date::operator==(const Date &right)
{
	return (getYear() == right.getYear() && 
		getMonth() == right.getMonth() && 
		getDay() == right.getDay());
}

bool Date::operator!=(const Date &right) { return !(*this == right); }

bool Date::operator>(const Date &right)
{
	if (getYear() == right.getYear())
	{
		if (getMonth() == right.getMonth())
		{
			if (getDay() == right.getDay())
				return false;
			return (getDay() > right.getDay());
		}
		return (getMonth() > right.getMonth());
	}
	return (getYear() > right.getYear());
}

bool Date::operator<(const Date &right)
{
	if (getYear() == right.getYear())
	{
		if (getMonth() == right.getMonth())
		{
			if (getDay() == right.getDay())
				return false;
			return (getDay() < right.getDay());
		}
		return (getMonth() < right.getMonth());
	}
	return (getYear() < right.getYear());
}

bool Date::operator>=(const Date &right) { return (*this == right || *this > right); }
bool Date::operator<=(const Date &right) { return (*this == right || *this < right); }

std::ostream & operator<<(std::ostream &os, const Date &date)
{
	os << date.getYear() << (date.getMonth() < 10 ? "/0" : "/") 
		<< date.getMonth() << (date.getDay() < 10 ? "/0" : "/") 
		<< date.getDay();
	return os;
}

// other methods --------------------------------
void Date::addYears(int y)
{
	setYear(getYear() + y);
	if (getYear() < 1)
	{
		setYear(1);
		setMonth(1);
		setDay(1);
	}
}

void Date::addMonths(int m)
{
	int currYear = getYear();
	int currMonth = getMonth();

	while (m > 0)
	{
		m--;
		if (++currMonth > 12)
		{
			currMonth = 1;
			currYear++;
		}
	}
	while (m < 0)
	{
		if (--currMonth < 1)
		{
			currMonth = 12;
			currYear--;
		}
		m++;
	}

	if (currYear < 1)
	{
		currYear = currMonth = 1;
		setDay(1);
	}

	year.setYear(currYear);
	month.setMonth(currMonth);
	month.setNumberOfDays(getDaysOfMonth(currYear, currMonth));
}

void Date::addDays(long d) // same as using operator+= or operator-=
{
	*this += d;
}

// static methods -------------------------------
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
		if (Year::isLeapYear(y) && d > 29)
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
		if (Year::isLeapYear(y))
			return 29;
		else
			return 28;
	default: // case 1, 3, 5, 7, 8, 10, and 12
		return 31;
	}
}
