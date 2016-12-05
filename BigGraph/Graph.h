#pragma once
#include<map>
#include<list> 

#include "Node.h"
/*

///////////
//������ô��һ��ͼ
//===================================================================
//1.���ȸ�һ���ڵ�Ԫ�ر���map��ʽ���ڵ�������ֻ�����.
//	��NodeID��һ��ֻ��������int��������������ǽڵ㡣��
//	|NodeID	|  �ڵ�	|
//	|	1	|	è	|						
//	|	2	|	��	|
//	|	4	|	��	|	<-Ϊʲôû��3�����ܱ�ɾ�˰ɣ�O(��_��)O~
//===================================================================
//2.�ڽӾ���AdjlistGraph��Ҳ����map�ķ�ʽ
//	|NodeID	|��ָ��	|
//	|	1	|		|->|node=2|weight=1.0|  ������|è|---��Ȩ��=1.0--->|��| 
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
	//float** fgetMatrixGraph() const;	//��þ���㹹���ͼ������C++�Ĵ�ͳ������������float�ľ���

	//float** MatrixGraph;
	//std::map< int, GraphEdge*> getAdjlistGraph() const;	//����ڽӱ����ͼ
	
	
	/*

	/////////////////////////////
	//��������ӽڵ���ߵķ���
	//�����ظ��ĵ㲻��ɹ�
	//�����ظ��ı�Ҳ����ɹ�
	//////////////////////////////


	*/
public:
	int getNodesize() { return NodeSize; }
	int getEdgesize() { return EdgeSize; }

	//////
	//���ܣ������
	//����ֵ���ɹ�����true��ʧ�ܷ���false
	//˵���������û����ͼ���棬���Զ�����
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
	//���ܣ����������
	//����ֵ���ɹ�����true��ʧ�ܷ���false
	//˵����������ߵĵ�û����ͼ���棬�����Զ�����
	/////
	Graph& addEdge(Node<_T> & from, Node<_T> & to, float weight = 1.0)
	{
		if (!isEdgeinthisGraph(from, to))
		{
			addNode(from);
			addNode(to);
			int fromid = element[from.data];
			int toid = element[to.data];
			//�ڽ�����Ϊ��ʱֱ�Ӽ���
			AdjlistGraph[fromid].push_back(GraphEdge(toid, weight));
			++EdgeSize;
		}
		return *this;
	}

	//////////////
	//���ܣ��жϵ�t�ı��ڲ������ͼ����
	//����ֵ������ڷ���true�����ڷ���false
	/////
	bool isNodeinthisGraph(const Node<_T> & t)
	{
		if (element.find(t.data) == element.end())
			return false;
		else
			return true;
	}

	//////////////
	//���ܣ��жϵ�from����to�ı��ڲ������ͼ����
	//����ֵ������ڷ���true�����ڷ���false
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
	//���ܣ�ɾ���㣬��ĵ����ӵı�
	//����ֵ���ɹ�����true��ʧ�ܷ���false
	//˵���������û����ͼ���棬���Զ�����
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
	//���ܣ�ɾ������ߡ���ʹ�ñ߽�����һ���㣬Ҳ������ɾ����
	//����ֵ���ɹ�����true��ʧ�ܷ���false
	//˵����������ߵĵ�û����ͼ���棬�����Զ�����
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
	int NodeSize;					//��õ��С
	int EdgeSize;					//��ñߴ�С
	int NodeID;						//�ڵ����ֻ����ߣ�ֻ��������
	std::map< int, std::list<GraphEdge>> AdjlistGraph;
	
	//Ϊʲô�������ֻ���<_T, int>�أ�
	//��Ϊ���ǳ�����Ҫ�������ֻ��������Ƿ����ֻ���
	//ֱ�ӷ������ֻ��ĸ��ʲ�����������Ϊ����ʱ������
	//ԭʼ�������keyλ
	std::map<_T, int > element;

};


