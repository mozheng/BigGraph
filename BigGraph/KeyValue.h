#pragma once
/*
	_Key,_Value���ͱ����п������캯�������ƹ��캯��
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
	void* pvoid;	//���Ǹ�Ԥ���������ڹؼ�ʱ���м������á�
					//����������Ϳ�㣬hashtable�ĳ�ͻ��⡣
	`				//Ϊ�˼��ݣ�������ָ������,ֵΪ0
};
