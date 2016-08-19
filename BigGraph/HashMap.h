#pragma once
#include"KeyValue.h"
#include"Utility.h"
// 本实作的hashtable采用的是开链法, 其内存布局如下
////////////////////////////////////////////////////////////////////////////////
// 对于产生哈希冲突的结点, 我们采取在其位置维护一个链表才处理之
//
//  -----------------------------------------------------------------------------------
//  |一级指针|      |      |      |      | ..... |      |      |      |      |这是hashtable二级指针
//  --------------------------------------------------------------------------------
//      |             |                                   |
//      ↓             ↓                                   ↓
//  --------       --------  --------  --------        --------
//  | next |->0    | next |->| next |->| next |->0     | next |->0
//  --------       --------  --------  --------        --------
//  | k, v |       | k, v |  | k, v |  | k, v |        | k, v |
//  --------       --------  --------  --------        --------
/////////////////////////////////////////////////////////////////////////////////
template <class _Key, class _Value, class _HashFunc = HashFunc<_Key>, class _EqualKey = Equal<_Key> >
class HashMap
{
public:
	HashMap();
	HashMap(int hashkey);
	~HashMap();
	bool insert(const _Key& key, const _Value& value);
	bool remove(const _Key& key);
	Value& find(const _Key& key);
	const Value& operator [](const _Key& key) const;
	Value& operator [](const _Key& key);

private:
	_HashFunc hashfunc;
	_EqualKey equalkey;
	KeyValue<_Key, _Value>** hashtable;
	int size;				//当前map大小
	int capacity;			//Hashtable数组的容量

};

