/*
Lab 4 - Graphs and Lambda Expressions
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This file has the main application for this lab.
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

	cout << "Now testing the Coordinate Graph\n\n\n";
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
	cgraph.printAdjacencyList(cout);
}