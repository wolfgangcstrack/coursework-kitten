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
	virtual int getNumberOfVertices() const = 0;
	virtual int getNumberOfEdges() const = 0;
	virtual bool add(T &start, T &end) = 0;
	virtual bool remove(T &start, T &end) = 0;
	virtual double getEdgeWeight(T &start, T &end) = 0;
};

#endif // GRAPH_H_