#include"Graph.h"

#include<vector>
#include<map> 
#include<set>
template<class T>
Graph<T>::Graph()
{
	static
	{
		i = 0;
	}

}
template<class T>
void Graph::addNode(T t)
{
	element.insert(make_pair(t , &t));
}

template<class T>
void Graph<T>::addEdge(T & from, T & to, float weight = 1)
{
	
}



template<class T>
int Graph<T>::getNodesize()
{
	return 0;
}

template<class T>
int Graph<T>::getEdgesize()
{
	return 0;
}

template<class T>
int Graph<T>::getMatrixGraphwidth() const
{
	return 0;
}

template<class T>
int Graph<T>::getMatrixGraphhight() const
{
	return 0;
}
