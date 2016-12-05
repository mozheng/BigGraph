#pragma once

template <class _T>
class Node
{
public:
	Node() {};
	Node(_T t) :data(t) {};
	~Node() {};
	_T data;
	bool operator<(const Node& n)
	{
		return this.data < n.data;
	}

private:

};