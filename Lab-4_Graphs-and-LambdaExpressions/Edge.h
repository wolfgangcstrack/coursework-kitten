/*
Lab 4 - Graphs and Lambda Expressions
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This header file has the class definition of Edge. In this implementation,
Edge is weighted and undirected.
*/

#ifndef EDGE_H_
#define EDGE_H_

#include "Vertex.h"
#include <memory>
using namespace std;

template<class T>
class Edge
{
protected:
	shared_ptr<Vertex<T>> start;
	shared_ptr<Vertex<T>> end;
	double weight;
public:
	// constructors and destructor
	Edge();
	Edge(const Vertex<T> &s, const Vertex<T> &e, double w);
	~Edge();
	// getters/setters
	const Vertex<T> & getStartVertex() const { return *start; }
	const Vertex<T> & getEndVertex() const   { return *end; }
	double getWeight() const                 { return weight; }
	void setWeight(double w)                 { weight = w; }
};

#endif // EDGE_H_