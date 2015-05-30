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
	Vertex(const Vertex<T> &copy);
	Vertex(T &d);
	~Vertex() {}
	// getters/setters
	T & getData() const                      { return *data; }
	bool isVisited() const                   { return visited; }
	const vector<Edge<T>> & getEdges() const { return edges; }
	void visit()                             { visited = true; }
	void unvisit()                           { visited = false; }
	void setData(const T &d)                 { *data = d; }
	// other methods
	bool connect(Vertex<T> &end, double w);
	bool disconnect(const Vertex<T> &end);
	void disconnectAll();
	bool isConnectedTo(const Vertex<T> &end);
	int getNumberOfEdges() const             { return edges.size(); }
	bool operator==(const Vertex<T> &right)  { return (*data == *right.data); }
	double getEdgeWeight(const Vertex<T> &end) const;
	friend ostream & operator<<(ostream &os, const Vertex<T> &vert)
	{
		os << vert.getData();

		for (auto iter = vert.edges.begin(); iter != vert.edges.end(); iter++)
		{
			os << "---" << iter->getWeight() << "---" << iter->getEndVertex().getData();
		}

		return os;
	}
};

template<class T>
Vertex<T>::Vertex(const Vertex<T> &copy)
{
	data = copy.data;
	visited = copy.visited;
	edges = copy.edges;
}

template<class T>
Vertex<T>::Vertex(T &d)
{
	data = shared_ptr<T>(new T(d));
	//*data = T(d);
	visited = false;
}

template<class T>
bool Vertex<T>::connect(Vertex<T> &end, double w)
{
	Edge<T> edge(*this, end, w);
	edges.push_back(edge);
	return true;
}

template<class T>
bool Vertex<T>::disconnect(const Vertex<T> &end)
{
	bool result = false;

	for (int index = 0; index < edges.size(); index++)
	{
		if (edges[index].getEndVertex() == end)
		{
			edges.erase(edges.begin() + index);
			result = true;
			break;
		}
	}

	return result;
}

template<class T>
void Vertex<T>::disconnectAll()
{
	for (int index = 0; index < edges.size(); index++)
	{
		edges[index].getEndVertex().disconnect(*this);
		edges.erase(edges.begin() + index);
	}
}

template<class T>
bool Vertex<T>::isConnectedTo(const Vertex<T> &end)
{
	for (int index = 0; index < edges.size(); index++)
	{
		if (edges[index].getEndVertex() == end)
		{
			return true;
		}
	}

	return false;
}

template<class T>
double Vertex<T>::getEdgeWeight(const Vertex<T> &end) const
{
	for (int index = 0; index < edges.size(); index++)
	{
		if (edges[index].getEndVertex() == end)
		{
			return edges[index].getWeight();
		}
	}
}

#endif // VERTEX_H_