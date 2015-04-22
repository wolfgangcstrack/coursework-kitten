/*
Lab 0 - Variant #3 (Date arithmetic)
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This is the Month header file. Implementation is included here
instead of in a separate .cpp file.
*/

#pragma once

#include "Day.h"

class Month
{
private:
	enum MonthName
	{
		January = 1, February = 2, March = 3, April = 4,
		May = 5, June = 6, July = 7, August = 8,
		September = 9, October = 10, November = 11, December = 12
	};
	MonthName month;
	Day *days;
	int numdays;

	int getValidDay()
	{
		switch (month)
		{
		case 4: case 6: case 9: case 11:
			return 30;
		case 2:
			return 28;
		default: // case 1, 3, 5, 7, 8, 10, and 12
			return 31;
		}
	}
public:
	// constructors and destructor
	Month() { month = January; numdays = 1; days = new Day[numdays]; }
	Month(const Month &m)
	{
		month = m.month;
		numdays = m.numdays;
		delete[] days;
		days = new Day[numdays];
		for (int i = 0; i < numdays; i++)
			days[i] = Day(m.days[i]);
	}
	Month(int m)
	{
		month = static_cast<MonthName>(m >= 1 && m <= 12 ? m : 1);
		numdays = getValidDay();
		days = new Day[numdays];
		for (int i = 0; i < numdays; i++)
			days[i].setDay(i + 1);
	}
	Month(int m, int d)
	{
		month = static_cast<MonthName>(m >= 1 && m <= 12 ? m : 1);
		numdays = (d > 0 ? d : 1);
		days = new Day[numdays];
		for (int i = 0; i < numdays; i++)
			days[i].setDay(i + 1);
	}
	~Month() { delete[] days; }
	// getter
	int getMonth() const { return month; }
	int getNumberOfDays() const { return numdays; }
	// setter
	void setMonth(int m) { if (m >= 1 && m <= 12) month = static_cast<MonthName>(m); }
	void setNumberOfDays(int d)
	{
		if (d < 1)
			return;
		delete[] days;
		numdays = d;
		days = new Day[numdays];
		for (int i = 0; i < numdays; i++)
			days[i].setDay(i + 1);
	}
};