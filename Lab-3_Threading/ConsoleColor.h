#pragma once
#include <iostream>
#include <windows.h>

using namespace std;

inline ostream& blue(ostream &s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
    return s;
}

inline ostream& red(ostream &s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleTextAttribute(hStdout, FOREGROUND_RED|FOREGROUND_INTENSITY);
    return s;
}

inline ostream& green(ostream &s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN|FOREGROUND_INTENSITY);
    return s;
}

inline ostream& yellow(ostream &s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
    return s;
}

inline ostream& white(ostream &s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleTextAttribute(hStdout, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
    return s;
}

struct color 
{
    color(WORD attribute) : m_color(attribute) { };
    WORD m_color;
};

template <class _Elem, class _Traits>
basic_ostream<_Elem,_Traits>& operator<<(basic_ostream<_Elem,_Traits>& s, color& c)
{
    HANDLE hStdout=GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleTextAttribute( hStdout, c.m_color );
    return s;
}

