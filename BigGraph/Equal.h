#pragma once
/*
	����һ���º�����������Ĭ�ϱȽϲ����ġ���������˫�Ⱥ�==
	Ĭ�ϵľ�����ô�����ܣ�����Ļ��Լ�����ȥ��.O(��_��)O!!!!!
*/
template <class _T>
class Equal
{
public:
	bool operator()(const _T & A, const _T & B)
	{
		if (A == B)
			return true;    
		else
			return false;
	}
};