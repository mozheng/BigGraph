#pragma once
#include"KeyValue.h"
#include"Utility.h"


template <class _Key, class _Value, class _HashFunc = HashFunc<_Key>, class _EqualKey = Equal<_Key> >
class HashMap
{
public:
	HashMap();
	~HashMap();
	bool insert(const _Key& key, const _Value& value);
	bool remove(const _Key& key);
	Value& find(const _Key& key);
	const Value& operator [](const _Key& key) const;
	Value& operator [](const _Key& key);

private:
	_HashFunc hashfunc;
	_EqualKey equalkey;
	KeyValue<_Key, _Value> *hashtable;
	int size;				//当前map大小
	int capacity;			//Hashtable数组的容量

};

