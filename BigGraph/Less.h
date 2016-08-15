#pragma once
/*
	这是一个仿函数，用来做默认比较操作的。方法就是小于号<
	默认的就是这么不智能，不想的话自己重载去啊.O(∩_∩)O!!!!!
*/
template <class _T>
class Less
{
public:
	bool operator()(const _T & A, const _T & B)
	{
		if (A < B)
			return true;
		else
			return false;
	}
};