/*
Lab 4 - Graphs and Lambda Expressions
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This file has the main application for this lab.

NOTE: Execution results for this lab have been appended to the end of this file.
*/

#include "CoordinateGraph.h"
#include "Location.h"
#include "XmlNodeList.h"
#include "XmlRegexIO.h"
#include "XmlNode.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

bool readTagsFromFile(XmlRegexIO &xrio, const string &filename, vector<string> &tags);
bool instantiateLocationNodes(XmlRegexIO &xrio, const vector<string> &tags, XmlNodeList &cpairs);
bool createCoordinateGraph(XmlNodeList &cpairs, CoordinateGraph &cgraph);
void testCoordinateGraph(CoordinateGraph &cgraph);

int main()
{
	// pattern matches everything (including newline)
	// between opening and closing <Location> tags
	XmlRegexIO xrio("<Location>(.\|\\n)*?</Location>");
	string filename = "Coordinates.xml";
	vector<string> tags;
	XmlNodeList cpairs;
	CoordinateGraph cgraph;

	cout << "Now reading tags from file...\n\n\n";
	if (!readTagsFromFile(xrio, filename, tags))
	{
		cout << "Error: something went wrong when reading the tags from the file!\n";
		return 1;
	}

	cout << "Now instantiating Location XML nodes...\n\n\n";
	if (!instantiateLocationNodes(xrio, tags, cpairs))
	{
		cout << "Error: something went wrong when instantiating the Location Nodes!\n";
		return 2;
	}

	cout << "Now creating the Coordinate Graph...\n\n\n";
	if (!createCoordinateGraph(cpairs, cgraph))
	{
		cout << "Error: something went wrong while creating Coordinate graph from data!\n";
		return 3;
	}

	cout << "Now testing the Coordinate Graph:\n\n\n";
	testCoordinateGraph(cgraph);

	return 0;
}

bool readTagsFromFile(XmlRegexIO &xrio, const string &filename, vector<string> &tags)
{
	return xrio.getAllMatches(filename, tags);
}

bool instantiateLocationNodes(XmlRegexIO &xrio, const vector<string> &tags, XmlNodeList &cpairs)
{
	for (int i = 0; i < tags.size(); i++)
	{
		shared_ptr<XmlNode> cpairPtr(new Location());
		cpairPtr->setXMLTags(tags[i]);

		if (!xrio.getXmlDataFromString(tags[i], *cpairPtr))
		{
			return false;
		}

		cpairs.push_back(cpairPtr);
	}

	return true;
}

bool createCoordinateGraph(XmlNodeList &cpairs, CoordinateGraph &cgraph)
{
	while (!cpairs.empty())
	{
		// cast the XmlNode pointer to a Location pointer,
		// dereference the pointer,
		// and finally add the Location object to the CoordinateGraph
		shared_ptr<Location> loc(dynamic_pointer_cast<Location>(cpairs.front()));
		cgraph.add(*loc);

		cpairs.pop_front();
	}

	return true;
}

void testCoordinateGraph(CoordinateGraph &cgraph)
{
	cout << "Printing Coordinate Graph adjacency list (currently has no edges):\n\n";
	cgraph.printAdjacencyList(cout);

	cout << "\n\nConnecting all vertices in graph...\n";
	cgraph.connectAllVertices();
	cout << "All vertices have been connected. This is done in preparation for the Kruskal MST algorithm.\n\n\n";

	cout << "Now generating minimal spanning tree using Kruskal's algorithm...\n";
	CoordinateGraph kruskalMST = cgraph.getKruskalMST();
	
	cout << "Kruskal MST has been generated. Printing the adjacency list for the Kruskal MST:\n\n";
	kruskalMST.printAdjacencyList(cout);
}

/* EXECUTION RESULTS
Now reading tags from file...


Now instantiating Location XML nodes...


Now creating the Coordinate Graph...


Now testing the Coordinate Graph:


Printing Coordinate Graph adjacency list (currently has no edges):

4257 Isleta Blvd. SW, Albuquerque, NM: (35.01, -106.68)
5210 Gibson SE,  Albuquerque, NM: (35.05, -106.58)
2435 Southern Blvd, Rio Rancho, NM: (35.06, -106.64)
425 Eubank NE. Albuquerque, Albuquerque, NM: (35.07, -106.53)
301 Coors Blvd. NW, Albuquerque, NM: (35.08, -106.71)
740 Juan Tabo Blvd. NE, Albuquerque, NM: (35.08, -106.51)
2235 Wyoming NE, Albuquerque, NM: (35.1, -106.55)
3240 Coors NW, Albuquerque, NM: (35.11, -106.7)
2809 Juan Tabo Blvd. NE,  Albuquerque, NM: (35.11, -106.51)
7600 Jefferson NE, Albuquerque, NM: (35.16, -106.59)
8111 Wyoming NE,  Albuquerque, NM: (35.17, -106.56)
9358 Eagle Ranch Rd. NW, Albuquerque, NM: (35.18, -106.66)
2301 Menaul Blvd. NE, Albuquerque, NM: (35.19, -106.61)
4101 Ridge Rock Rd. SE, Rio Rancho, NM: (35.25, -106.65)
130 Hwy. 550, East Bernalillo, NM: (35.31, -106.54)
10555 S. Parker Rd,  Parker, CO: (39.52, -104.76)
1535 East Evans Ave., Denver, CO: (39.67, -104.96)
1750 S Buckley Rd,  Aurora, CO: (39.68, -104.79)
11355 West Colfax Ave.,  Lakewood, CO: (39.74, -105.12)


Connecting all vertices in graph...
All vertices have been connected. This is done in preparation for the Kruskal MST algorithm.


Now generating minimal spanning tree using Kruskal's algorithm...
Kruskal MST has been generated. Printing the adjacency list for the Kruskal MST:

5210 Gibson SE,  Albuquerque, NM: (35.05, -106.58)
2435 Southern Blvd, Rio Rancho, NM: (35.06, -106.64)
425 Eubank NE. Albuquerque, Albuquerque, NM: (35.07, -106.53)
301 Coors Blvd. NW, Albuquerque, NM: (35.08, -106.71)
740 Juan Tabo Blvd. NE, Albuquerque, NM: (35.08, -106.51)
2235 Wyoming NE, Albuquerque, NM: (35.1, -106.55)
3240 Coors NW, Albuquerque, NM: (35.11, -106.7)
2809 Juan Tabo Blvd. NE,  Albuquerque, NM: (35.11, -106.51)
7600 Jefferson NE, Albuquerque, NM: (35.16, -106.59)
8111 Wyoming NE,  Albuquerque, NM: (35.17, -106.56)
9358 Eagle Ranch Rd. NW, Albuquerque, NM: (35.18, -106.66)
2301 Menaul Blvd. NE, Albuquerque, NM: (35.19, -106.61)
4101 Ridge Rock Rd. SE, Rio Rancho, NM: (35.25, -106.65)
130 Hwy. 550, East Bernalillo, NM: (35.31, -106.54)
10555 S. Parker Rd,  Parker, CO: (39.52, -104.76)
1535 East Evans Ave., Denver, CO: (39.67, -104.96)
1750 S Buckley Rd,  Aurora, CO: (39.68, -104.79)
11355 West Colfax Ave.,  Lakewood, CO: (39.74, -105.12)
Press any key to continue . . .
*/