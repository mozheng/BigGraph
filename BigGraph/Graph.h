#pragma once

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
	int** igetMatrixGraph() const;		//��þ���㹹���ͼ������C++�Ĵ�ͳ������������int�ľ���
	float** fgetMatrixGraph() const;	//��þ���㹹���ͼ������C++�Ĵ�ͳ������������float�ľ���

	int getMatrixWidth() const;
	int getMatrixHeight() const;

	std::map< int, GraphEdge*> getAdjlistGraph() const;	//����ڽӱ����ͼ

protected:
	int NodeSize;					//��õ��С
	int EdgeSize;					//��ñߴ�С
	int NodeID;						//�ڵ����ֻ����ߣ�ֻ��������
	std::map< int, GraphEdge* > AdjlistGraph;
	
	//Ϊʲô�������ֻ���<_T, int>�أ�
	//��Ϊ���ǳ�����Ҫ�������ֻ��������Ƿ����ֻ���
	//ֱ�ӷ������ֻ��ĸ��ʲ�����������Ϊ����ʱ������
	//ԭʼ�������keyλ
	std::map<_T, int > element;
/*

/////////////////////////////
//��������ӽڵ���ߵķ���
//�����ظ��ĵ㲻��ɹ�
//�����ظ��ı�Ҳ����ɹ�
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

