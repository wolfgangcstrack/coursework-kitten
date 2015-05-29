/*
Lab 4 - Graphs and Lambda Expressions
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This header file has the class definition of CoordinateGraph.
*/

#ifndef COORDINATE_GRAPH_H_
#define COORDINATE_GRAPH_H_

#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include "CoordinatePair.h"
#include <map>
using namespace std;

class CoordinateGraph : Graph <CoordinatePair>
{
private:
	typedef pair<double, double> coordinates;
	typedef Vertex<CoordinatePair> Location;

	map<coordinates, Location> graph;
public:
	// constructors and destructor
	CoordinateGraph();
	~CoordinateGraph();
	// getters/setters
	const CoordinatePair & getLocation(coordinates latitudeAndLongitude) const;
	// overloaded methods from Graph class
	bool add(CoordinatePair &start, CoordinatePair &end, double edgeWeight);
	bool remove(CoordinatePair &start, CoordinatePair &end);
	int getNumberOfVertices() const;
	int getNumberOfEdges() const;
	double getEdgeWeight(CoordinatePair &start, CoordinatePair &end);
	// other methods
	bool add(CoordinatePair &cpair);
	bool remove(CoordinatePair &cpair);
	CoordinateGraph getKruskalMST();
};

#endif // COORDINATE_GRAPH_H_