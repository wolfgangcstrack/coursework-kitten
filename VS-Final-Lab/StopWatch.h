/*
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This file contains the StopWatch class used for this lab.
*/

#ifndef STOP_WATCH_H_
#define STOP_WATCH_H_

#include <ctime>
#include <list>

class StopWatch
{
protected:
	std::list<double> laps;

	std::clock_t startTime, begin, end;

	bool isRunning, isReset;
public:
	// constuctor/destructor
	StopWatch()   { reset(); }
	~StopWatch()  {}
	// other methods
	void   start();
	double stop();
	double time();
	double lap();
	void   reset();
};

void StopWatch::start()
{
	if (!isRunning)
	{
		begin = std::clock();
		isRunning = true;
	}

	if (isReset)
	{
		startTime = begin;
		isReset = false;
	}
}

double StopWatch::stop()
{
	end = (isRunning ? clock() : 0);
	isRunning = false;
	return time();
}

double StopWatch::time()
{
	return double(begin - end) / CLOCKS_PER_SEC;
}

double StopWatch::lap()
{
	double lapTime = time();
	laps.push_back(lapTime);
	return lapTime;
}

void StopWatch::reset()
{
	laps.clear();
	startTime = begin = end = 0;
	isRunning = false;
	isReset = true;
}

#endif // STOP_WATCH_H_