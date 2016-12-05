#pragma once
#include<map>
#include<list> 

#include "Node.h"
/*

///////////
//我们这么搞一个图
//===================================================================
//1.首先搞一个节点元素表，用map方式将节点对象数字化处理.
//	（NodeID是一个只增不减的int变量，用他来标记节点。）
//	|NodeID	|  节点	|
//	|	1	|	猫	|						
//	|	2	|	狗	|
//	|	4	|	猪	|	<-为什么没有3，可能被删了吧？O(∩_∩)O~
//===================================================================
//2.邻接矩阵AdjlistGraph，也是用map的方式
//	|NodeID	|邻指针	|
//	|	1	|		|->|node=2|weight=1.0|  含义是|猫|---边权重=1.0--->|狗| 
//	|	2	|		|
//	|		|		|
//===================================================================
///////////////
*/
template <class _T>
class Graph
{
public:
	Graph() 
	{
		NodeSize = 0;
		EdgeSize = 0;
		NodeID = 0;
	};
	virtual ~Graph() {};

public:
	class GraphEdge
	{
		public:
			GraphEdge() {};
			GraphEdge(int n, int w) :nodeid(n), weight(w) {};
			~GraphEdge() {};
			int nodeid;
			float weight;
	};
	//float** fgetMatrixGraph() const;	//获得矩阵点构造的图，运用C++的传统命名法。返回float的矩阵

	//float** MatrixGraph;
	//std::map< int, GraphEdge*> getAdjlistGraph() const;	//获得邻接表构造的图
	
	
	/*

	/////////////////////////////
	//下面是添加节点与边的方法
	//加入重复的点不会成功
	//加入重复的边也不会成功
	//////////////////////////////


	*/
public:
	int getNodesize() { return NodeSize; }
	int getEdgesize() { return EdgeSize; }

	//////
	//功能：加入点
	//返回值：成功返回true，失败返回false
	//说明：如果点没有在图里面，再自动加入
	/////
	Graph& addNode(Node<_T> & t)
	{
		if (!isNodeinthisGraph(t))
		{
			element.insert(std::make_pair(t.data, NodeID));
			std::list<GraphEdge> l;
			AdjlistGraph.insert(std::make_pair(NodeID, l));
			++NodeID;
			++NodeSize;
		}
		return *this;
	}

	//////////////
	//功能：加入有向边
	//返回值：成功返回true，失败返回false
	//说明如果边两边的点没有在图里面，可以自动加入
	/////
	Graph& addEdge(Node<_T> & from, Node<_T> & to, float weight = 1.0)
	{
		if (!isEdgeinthisGraph(from, to))
		{
			addNode(from);
			addNode(to);
			int fromid = element[from.data];
			int toid = element[to.data];
			//邻接链表为空时直接加入
			AdjlistGraph[fromid].push_back(GraphEdge(toid, weight));
			++EdgeSize;
		}
		return *this;
	}

	//////////////
	//功能：判断点t的边在不在这个图里面
	//返回值：如果在返回true，不在返回false
	/////
	bool isNodeinthisGraph(const Node<_T> & t)
	{
		if (element.find(t.data) == element.end())
			return false;
		else
			return true;
	}

	//////////////
	//功能：判断点from到点to的边在不在这个图里面
	//返回值：如果在返回true，不在返回false
	/////
	bool isEdgeinthisGraph(const Node<_T> & from, const Node<_T> & to)
	{
		if (!isNodeinthisGraph(from) || !isNodeinthisGraph(to))
			return false;
		else
		{
			int fromid = element[from.data];
			int toid = element[to.data];
			if (AdjlistGraph[fromid].empty())
				return false;
			for (std::list<GraphEdge>::iterator it = AdjlistGraph[fromid].begin(); it != AdjlistGraph[fromid].end(); ++it)
				if (it->nodeid == toid)
					return true;
		}
		return false;
	}

	//////
	//功能：删除点，与改点连接的边
	//返回值：成功返回true，失败返回false
	//说明：如果点没有在图里面，再自动加入
	/////
	Graph& deleteNode(Node<_T> & t)
	{
		if (isNodeinthisGraph(t))
		{
			int nodeid = element.find(t.data)->second;
			
			for (std::map< int, std::list<GraphEdge>>::iterator it = AdjlistGraph.begin(); it != AdjlistGraph.end(); )
			{
				if (it->first != nodeid)
				{
					for (std::list<GraphEdge>::iterator listit = (it->second).begin(); listit != (it->second).end(); ++listit) 
					{
						if (listit->nodeid == nodeid)
						{
							(it->second).erase(listit);
							--EdgeSize;
							break;
						}
					}
					++it;
				}
				else
				{
					EdgeSize = EdgeSize - AdjlistGraph[nodeid].size();
					it = AdjlistGraph.erase(it);
					--NodeSize;
				}
			}
		}
		return *this;
	}
	//////////////
	//功能：删除有向边。即使该边仅连接一个点，也不负责删除点
	//返回值：成功返回true，失败返回false
	//说明如果边两边的点没有在图里面，可以自动加入
	/////
	Graph& deleteEdge(Node<_T> & from, Node<_T> & to)
	{
		if (!isEdgeinthisGraph(from,to))
			return *this;
		else 
		{
			int fromid = element[from.data];
			int toid = element[to.data];
			for (std::list<GraphEdge>::iterator it = AdjlistGraph[fromid].begin(); it != AdjlistGraph[fromid].end();)
			{
				if (it->nodeid == toid)
				{
					AdjlistGraph[fromid].erase(it);
					--EdgeSize;
					break;
				}
				else
					++it;
			}
			return *this;
		}
	}
protected:
	int NodeSize;					//获得点大小
	int EdgeSize;					//获得边大小
	int NodeID;						//节点数字化工具，只增不减。
	std::map< int, std::list<GraphEdge>> AdjlistGraph;
	
	//为什么对象数字化用<_T, int>呢？
	//因为我们常常需要对象数字化，而不是反数字化。
	//直接访问数字化的概率不大，所以设置为更耗时操作。
	//原始对象放在key位
	std::map<_T, int > element;

};


