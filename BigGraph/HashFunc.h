#pragma once
/*
	这是一个仿函数，用来做默认hash函数。
	默认的要小于号可用，所以有时需要重载类型小于号
*/
template<class _T >
class HashFunc
{
public:
	int operator()(const _T & key)
	{
		long key_address= (long)&key;//不管因为key的类型如何，地址总是唯一的，所以用他做hash最好。（共用体什么的一边去）
									 //因为程序集中性原理，总是集中分配内存，所以建议使用时直接截取。为了兼容将long截成int
		/*
		|这是内存|
		|		| <-key 开始部分	
		|		|
		|		|
		*/
		return (int)(key_address);
	}
};