# CIS29-Lab5-memory-and-maps
CIS29 Spring Quarter 2015 - Lab 5, dynamic memory operator overloads and STL maps

## Purpose
Overload dynamic memory operators and use STL maps

### Part 1
Overload operator new (scalar) and new[] (vector).

### Part 2
Overload operator delete (scalar) and delete[] (vector).

### Part 3
Write a class to monitor NEW and DELETE usage.  For NEW store the address and the number of bytes being allocated in an STL map.  Also increment a global byte counter.  For DELETE, find the address in the STL map, get the bytes allocated for that address, and decrement the global byte counter.

### Part 4
Incorporate your overloaded NEW and DELETE into a standard C++ program to monitor NEW and DELETE usage.  The purpose is to determine if there are any memory leaks in a C++ program that uses NEW and DELETE. 

##### Note
To test your memory checking utility program, use a C++ program that uses NEW in at least 10 different locations in the program.
