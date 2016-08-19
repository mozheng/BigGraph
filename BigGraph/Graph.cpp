#include"Graph.h"
#include<map>
#include<iterator>
template<class _T>
inline Graph<_T>::Graph()
{
	NodeID = 0; 
	next = NULL;
	NodeSize = 0;
	EdgeSize = 0;
}

template<class _T>
Graph<_T>::~Graph()
{
}

template<class _T>
inline void Graph<_T>::addNode(_T& t)
{
	if (!isNodeinthisGraph<_T>(t))
	{
		element.insert(std::make_pair< int, GraphEdge* >(t, NodeID));
		AdjlistGraph.insert(std::make_pair< int, GraphEdge* >(NodeID, NULL));
		++NodeID;
		++NodeSize;
	}
}

//////////////
//
//
//
/////
template<class _T>
void Graph<_T>::addEdge(_T & from, _T & to, float weight)
{
	addNode<_T>(from);
	addNode<_T>(to);
	int fromvalue = element[from];
	int tovalue = element[to];
	GraphEdge* p = AdjlistGraph[fromvalue];
	//邻接链表为空时直接加入
	if (p == NULL)
	{
		AdjlistGraph[fromvalue] = new GraphEdge(tovalue, weight);
		++EdgeSize;
		return;
	}
	////邻接链表非空时，先查找，找不到再加。
	while (p ! =NULL)
	{
		if (p->node == tovalue)
			return;
		if (p->next==NULL)
		{
			p->next = new GraphEdge(tovalue,weight);
			++EdgeSize;
			return;
		}
	}
}

template<class _T>
bool Graph<_T>::isNodeinthisGraph(const _T & t)
{
	if (element.find(t) == element.end())
		return false;
	else
		return true;
}

template<class _T>
bool Graph<_T>::isEdgeinthisGraph(const _T & from, const _T & to)
{
	if (!isNodeinthisGraph<_T>(from) || !isNodeinthisGraph<_T>(to))
		return false;
	else
	{
		int fromvalue = element[from];
		int tovalue = element[to];
		GraphEdge* p = AdjlistGraph[fromvalue];
		while (p != NULL)
		{
			if (p->node == tovalue)
				return true;
			p = p->next;
		}
		return false;
	}

}
