/*
Lab 4 - Graphs and Lambda Expressions
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This file has the main application for this lab.
*/

#include "CoordinateGraph.h"
#include "CoordinatePair.h"
#include "XmlRegexIO.h"
#include "XmlNode.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

bool openInputfile(ifstream &ifs);
bool readCoords(ifstream &ifs, vector<XmlNode> &cpairs);
bool createCoordinateGraph(vector<XmlNode> &cpairs, CoordinateGraph &cgraph);
void testCoordinateGraph(CoordinateGraph &cgraph);

int main()
{
	ifstream ifs;
	vector<XmlNode> cpairs;
	CoordinateGraph cgraph;
	
	if (!openInputfile(ifs))
	{
		cout << "Error: something went wrong when opening the input file!\n";
		return 1;
	}

	if (!readCoords(ifs, cpairs))
	{
		cout << "Error: something went wrong when reading the Coordinate Nodes!\n";
		return 2;
	}

	if (!createCoordinateGraph(cpairs, cgraph))
	{
		cout << "Error: something went wrong while creating Coordinate graph from data!\n";
		return 3;
	}

	testCoordinateGraph(cgraph);

	return 0;
}

bool openInputfile(ifstream &ifs)
{
	string filename;
	cout << "Please enter filename to read from: ";
	getline(cin, filename);
	ifs.open(filename);
	return ifs.is_open();
}

bool readCoords(ifstream &ifs, vector<XmlNode> &cpairs)
{

}