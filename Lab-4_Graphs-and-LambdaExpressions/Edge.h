/*
Lab 4 - Graphs and Lambda Expressions
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This header file has the class definition of Edge. In this implementation,
Edge is weighted and undirected.
*/

#ifndef EDGE_H_
#define EDGE_H_

#include <memory>
using namespace std;

template<class T>
class Vertex;

template<class T>
class Edge
{
protected:
	shared_ptr<Vertex<T>> start;
	shared_ptr<Vertex<T>> end;
	double weight;
public:
	// constructors and destructor
	Edge() { start = 0; end = 0; weight = 0; }
	Edge(Vertex<T> &s, Vertex<T> &e, double w);
	~Edge() {}
	// getters/setters
	Vertex<T> & getStartVertex() const       { return *start; }
	Vertex<T> & getEndVertex() const         { return *end; }
	double getWeight() const                 { return weight; }
	void setWeight(double w)                 { weight = w; }
	// other methods
	bool operator==(const Edge &right);
	bool operator!=(const Edge &right);
};

template<class T>
Edge<T>::Edge(Vertex<T> &s, Vertex<T> &e, double w)
{
	start = shared_ptr<Vertex<T>>(new Vertex<T>(s));
	end = shared_ptr<Vertex<T>>(new Vertex<T>(e));
	weight = w;
}

template<class T>
bool Edge<T>::operator==(const Edge &right)
{
	return (((start == right.start && end == right.end) ||
		(start == right.end && end == right.start))
		&& weight == right.weight);
}

template<class T>
bool Edge<T>::operator!=(const Edge &right)
{
	return !(*this == right);
}

#endif // EDGE_H_