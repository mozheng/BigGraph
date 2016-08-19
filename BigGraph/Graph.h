#pragma once

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
	Graph();
	virtual ~Graph();

public:
	class GraphEdge
	{
		public:
			GraphEdge() { next = NULL; };
			GraphEdge(int n, int w) :node(n), weigh(w) { next = NULL; };
			~GraphEdge();
			int node;
			float weight;
			GraphEdge* next;
	};
	int** igetMatrixGraph() const;		//获得矩阵点构造的图，运用C++的传统命名法。返回int的矩阵
	float** fgetMatrixGraph() const;	//获得矩阵点构造的图，运用C++的传统命名法。返回float的矩阵

	int getMatrixWidth() const;
	int getMatrixHeight() const;

	std::map< int, GraphEdge*> getAdjlistGraph() const;	//获得邻接表构造的图

protected:
	int NodeSize;					//获得点大小
	int EdgeSize;					//获得边大小
	int NodeID;						//节点数字化工具，只增不减。
	std::map< int, GraphEdge* > AdjlistGraph;
	
	//为什么对象数字化用<_T, int>呢？
	//因为我们常常需要对象数字化，而不是反数字化。
	//直接访问数字化的概率不大，所以设置为更耗时操作。
	//原始对象放在key位
	std::map<_T, int > element;
/*

/////////////////////////////
//下面是添加节点与边的方法
//加入重复的点不会成功
//加入重复的边也不会成功
//////////////////////////////


*/
public:
	void addNode(_T& t);
	void addEdge(_T& from, _T& to, float weight = 1);
	int getNodesize();
	int getEdgesize();
	int getMatrixGraphwidth() const;
	int getMatrixGraphhight() const;
	
	bool isNodeinthisGraph(const _T& t);
	bool isEdgeinthisGraph(const _T& from, const _T& to);
};

