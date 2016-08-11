#pragma once

template <class T>
class Graph
{
public:
	Graph();
	virtual ~Graph();

protected:
	std::vector< std::vector<T> > getMatrixGraph() const;
	std::vector< std::map< int, T> > getAdjlistGraph() const;


public:
	void addNode(T t);
	void addEdge(T& from, T& to ,float weight = 1);
	int getNodesize();
	int getEdgesize();
	int getMatrixGraphwidth() const;
	int getMatrixGraphhight() const;

protected:
	int Nodesize;
	int Edgesize;
	static int i;
	std::map< int, std::map<int, float> > AdjlistGraph;
	std::map< int, T > element;
};


