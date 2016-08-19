#pragma once
/*
	_Key,_Value类型必须有拷贝构造函数，或复制构造函数
*/
template <class _Key, class _Value>
class KeyValue
{
public:
	_Value  value;   
	_Key    key; 

	KeyValue() :preserve((void*)0) {};
	KeyValue(_Value v,_Key k):value(v),key(k),preserve((void*)0) {};


	KeyValue(const KeyValue & kv)
	{
		value = kv.value;
		key = kv.key;
	}
	KeyValue & operator=(const KeyValue & kv)
	{
		if (*this == kv) return *this;
		value = kv.value;
		key = kv.key;
		return *this;
	}
public:
	void* pvoid;	//这是个预留参数，在关键时刻有极佳作用。
					//例如红黑树的涂点，hashtable的冲突检测。
	`				//为了兼容，我们用指针类型,值为0
};
