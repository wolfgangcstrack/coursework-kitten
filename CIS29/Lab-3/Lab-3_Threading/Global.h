/*
Lab 3 - Threading
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This file holds global values for this lab.
*/

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <memory>
#include <string>
#include <vector>
#include <mutex>
#include <map>
using namespace std;

// mutex for locking Robot.Execute()
static mutex execution_guard;

#endif // GLOBAL_H_