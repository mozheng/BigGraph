#pragma once
#include"KeyValue.h"
#include"Utility.h"
// ��ʵ����hashtable���õ��ǿ�����, ���ڴ沼������
////////////////////////////////////////////////////////////////////////////////
// ���ڲ�����ϣ��ͻ�Ľ��, ���ǲ�ȡ����λ��ά��һ������Ŵ���֮
//
//  -----------------------------------------------------------------------------------
//  |һ��ָ��|      |      |      |      | ..... |      |      |      |      |����hashtable����ָ��
//  --------------------------------------------------------------------------------
//      |             |                                   |
//      ��             ��                                   ��
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
	int size;				//��ǰmap��С
	int capacity;			//Hashtable���������

};

