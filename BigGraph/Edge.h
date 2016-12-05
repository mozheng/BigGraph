#pragma once
template<class _T>
class Edge :public Node
{
public:
	Edge() :weight(1.0) {};
	float weight;
	Edge *next;
};