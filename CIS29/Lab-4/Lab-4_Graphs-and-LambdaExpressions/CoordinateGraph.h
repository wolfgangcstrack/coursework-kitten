/*
Lab 4 - Graphs and Lambda Expressions
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This header file has the class definition of CoordinateGraph. This graph
implementation is weighted and undirected. The single minimal spanning tree
algorithm it uses for now is Kruskal's algorithm.

Note: the Edge class this graph implementation uses is directed, but the
implementation doubly links connected vertices to emulate an undirected
graph.
*/

#ifndef COORDINATE_GRAPH_H_
#define COORDINATE_GRAPH_H_

#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include "Location.h"
#include <vector>
#include <cmath>
#include <map>
using namespace std;

static const int ERADIUS = 6371; // Earth's radius in km
static const double PI = 3.141592653589;

class CoordinateGraph : public Graph <Location>
{
private:
	typedef pair<double, double> coordinates;
	typedef Vertex<Location> VLocation;

	map<coordinates, VLocation> graph;

	// define functor
	struct degreesToRadians
	{
		degreesToRadians() {}
		double operator()(double degrees) { return (degrees * (PI / 180)); }
	};

	double haversine(pair<double, double> cp1, pair<double, double> cp2)
	{
		degreesToRadians d2r; // functor

		double dlat = d2r(cp2.first - cp1.first);
		double dlon = d2r(cp2.second - cp1.second);
		double a = pow(sin(dlat / 2.), 2.) +
				cos(d2r(cp1.first)) * cos(d2r(cp2.first)) *
				pow(sin(dlon / 2.), 2.);
		double c = 2. * atan2(sqrt(a), sqrt(1. - a));
		double distance = ERADIUS * c;

		return distance;
	}
public:
	// constructors and destructor
	CoordinateGraph()  {}
	~CoordinateGraph() {}
	// getters/setters
	const Location & getLocation(const pair<double, double> &latitudeAndLongitude);
	// overloaded methods from Graph class
	bool add(Location &cp1, Location &cp2);
	bool remove(Location &cp1, Location &cp2);
	int getNumberOfVertices() const;
	int getNumberOfEdges() const;
	double getEdgeWeight(Location &cp1, Location &cp2);
	// other methods
	bool add(Location &cpair);
	bool remove(Location &cpair);
	bool connect(Location &cp1, Location &cp2);
	void connectAllVertices();
	CoordinateGraph getKruskalMST();
	void printAdjacencyList(ostream &os);
};

const Location & CoordinateGraph::getLocation(const pair<double, double> &latitudeAndLongitude)
{
	return graph[latitudeAndLongitude].getData();
}

bool CoordinateGraph::add(Location &cp1, Location &cp2)
{
	// Construct the vertices
	VLocation loc1(cp1);
	VLocation loc2(cp2);

	// get the map keys to insert the vertices
	auto coord1 = cp1.getCoordinates();
	auto coord2 = cp2.getCoordinates();

	// if any of the Locations are already in the graph, return false
	if (graph.find(coord1) != graph.end() || graph.find(coord2) != graph.end())
	{
		return false;
	}

	// calculate edge weight
	auto edgeweight = haversine(coord1, coord2);

	connect(cp1, cp2);

	// insert the two vertices into the graph
	graph[coord1] = loc1;
	graph[coord2] = loc2;

	return true;
}

bool CoordinateGraph::remove(Location &cp1, Location &cp2)
{
	// get the coordinate pairs and vertices
	auto coord1 = cp1.getCoordinates();
	auto coord2 = cp2.getCoordinates();
	auto vert1 = graph[coord1];
	auto vert2 = graph[coord2];

	// disconnect the edges between the vertices
	vert1.disconnect(vert2);
	vert2.disconnect(vert1);

	// erase the vertices from the CoordinateGraph
	auto iter = graph.find(coord1);
	if (iter == graph.end())
	{
		return false;
	}
	graph.erase(iter);

	iter = graph.find(coord2);
	if (iter == graph.end())
	{
		return false;
	}
	graph.erase(iter);

	return true;
}

int CoordinateGraph::getNumberOfVertices() const
{
	return graph.size();
}

int CoordinateGraph::getNumberOfEdges() const
{
	int doubleEdges = 0;

	for (auto iter = graph.begin(); iter != graph.end(); ++iter)
	{
		doubleEdges += iter->second.getNumberOfEdges();
	}

	return (doubleEdges / 2);
}

double CoordinateGraph::getEdgeWeight(Location &cp1, Location &cp2)
{
	return graph[cp1.getCoordinates()].getEdgeWeight(graph[cp2.getCoordinates()]);
}

bool CoordinateGraph::add(Location &cpair)
{
	VLocation loc(cpair);
	auto coord = cpair.getCoordinates();

	// if the Location is already in the graph, return false
	if (graph.find(coord) != graph.end())
	{
		return false;
	}

	graph[coord] = loc;
	return true;
}

bool CoordinateGraph::remove(Location &cpair)
{
	auto coord = cpair.getCoordinates();
	auto iter = graph.find(coord);

	// if Location is not in the graph, return false
	if (iter == graph.end())
	{
		return false;
	}

	// disconnect all the edges connected to this vertex
	iter->second.disconnectAll();
	// remove vertex from graph
	graph.erase(iter);

	return true;
}

bool CoordinateGraph::connect(Location &cp1, Location &cp2)
{
	// get the map keys of the vertices that hold the locations
	auto coord1 = cp1.getCoordinates();
	auto coord2 = cp2.getCoordinates();

	// if any of the Locations are not in the graph, return false
	if (graph.find(coord1) == graph.end() || graph.find(coord2) == graph.end())
	{
		return false;
	}

	// calculate edge weight
	auto edgeweight = haversine(coord1, coord2);

	// connect the two vertices "undirectedly"
	graph[coord1].connect(graph[coord2], edgeweight);
	graph[coord2].connect(graph[coord2], edgeweight);

	return true;
}

void CoordinateGraph::connectAllVertices()
{
	for (auto iter = graph.begin(); iter != graph.end(); ++iter)
	{
		auto toBeginIter = iter;
		auto toEndIter = iter;

		// loop through all other vertices besides the current one pointed to by iter
		while (toBeginIter != graph.begin() && --toBeginIter != graph.begin())
		{
			this->connect(iter->second.getData(), toBeginIter->second.getData());
		}
		while (toEndIter != graph.end() && ++toEndIter != graph.end())
		{
			this->connect(iter->second.getData(), toEndIter->second.getData());
		}
	}
}

CoordinateGraph CoordinateGraph::getKruskalMST()
{
	CoordinateGraph ncgraph;
	vector<Edge<Location>> edges;

	for (auto iter = graph.begin(); iter != graph.end(); ++iter)
	{
		vector<Edge<Location>> *toAppend = &(iter->second.getEdges());
		edges.insert(edges.end(), toAppend->begin(), toAppend->end());
	}

	sort(edges.begin(), edges.end(), [](Edge<Location> a, Edge<Location> b) {return (a.getWeight() < b.getWeight()); });
	edges.erase(unique(edges.begin(), edges.end()), edges.end());

	for (int i = 0; i < edges.size(); i++)
	{
		ncgraph.add(edges[i].getStartVertex().getData(),
			edges[i].getEndVertex().getData());
	}

	return ncgraph;
}

void CoordinateGraph::printAdjacencyList(ostream &os)
{
	for (auto iter = graph.begin(); iter != graph.end(); iter++)
	{
		os << iter->second << endl;
	}
}

#endif // COORDINATE_GRAPH_H_