/*
Lab 4 - Graphs and Lambda Expressions
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This header file has the virtual class definition of Graph.
*/

#ifndef GRAPH_H_
#define GRAPH_H_

template<class T>
class Graph
{
public:
	int getNumberOfVertices() const = 0;
	int getNumberOfEdges() const = 0;
	bool add(T &start, T &end, double edgeWeight) = 0;
	bool remove(T &start, T &end) = 0;
	double getEdgeWeight(T &start, T &end) = 0;
};

#endif // GRAPH_H_