/*
Lab 4 - Graphs and Lambda Expressions
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This header file has the class definition of Vertex.
*/

#ifndef VERTEX_H_
#define VERTEX_H_

#include "Edge.h"
#include <vector>
#include <memory>
#include <map>
using namespace std;

template<class T>
class Vertex
{
protected:
	shared_ptr<T> data;
	bool visited; // for MST algorithms
	vector<Edge<T>> edges;
public:
	// constructors and destructor
	Vertex() { data = 0; visited = 0; }
	Vertex(const T &d);
	~Vertex() {}
	// getters/setters
	const T & getData() const                { return *data; }
	bool isVisited() const                   { return visited; }
	const vector<Edge<T>> & getEdges() const { return edges; }
	void visit()                             { visited = true; }
	void unvisit()                           { visited = false; }
	void setData(const T &d)                 { *data = d; }
	// other methods
	bool connect(Vertex<T> &end, double w);
	//bool disconnect(const Vertex<T> &end);
	//bool disconnect(const Edge<T> &edge);
	//bool disconnectAll();
	int getNumberOfEdges() const             { return edges.size(); }
	bool operator==(const Vertex<T> &right)  { return (*data == *right.data); }
};

template<class T>
Vertex::Vertex(const T &d)
{
	*data = d;
	visited = false;
}

template<class T>
bool Vertex::connect(Vertex<T> &end, double w)
{
	Edge<T> edge(*this, end, w);
	edges.push_back(edge);
	return true;
}

#endif // VERTEX_H_