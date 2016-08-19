#include "HashMap.h"

#include<functional>
template<class _Key, class _Value, class _HashFunc, class _EqualKey>
HashMap<_Key, _Value, _HashFunc, _EqualKey>::HashMap()
{
	hashfunc = new _HashFunc();
	equalkey = new _EqualKey();
	capacity = 57;					//直接这样写快一点，默认57。否则应该写capacity=GetNextPrime(0)；
	hashtable = new KeyValue<_Key, _Value>*[capacity + 1] = NULL;
	size = 0;
}

template<class _Key, class _Value, class _HashFunc, class _EqualKey>
HashMap<_Key, _Value, _HashFunc, _EqualKey>::HashMap(int hashkey)
{
	hashfunc = new _HashFunc();
	equalkey = new _EqualKey();
	capacity = GetNextPrime(hashkey);					
	hashtable = new KeyValue<_Key, _Value>*[capacity + 1] = NULL;
	size = 0;
}

template<class _Key, class _Value, class _HashFunc, class _EqualKey>
HashMap<_Key, _Value, _HashFunc, _EqualKey>::~HashMap()
{
	delete[] hashtable;
}

template<class _Key, class _Value, class _HashFunc, class _EqualKey>
inline bool HashMap<_Key, _Value, _HashFunc, _EqualKey>::insert(const _Key & key, const _Value & value)
{
	int index = std::hash<_Key>()(key) % capacity;
	if (hashtable[index]==NULL)
	{
		hashtable[index] = new KeyValue<_Key, _Value>(key, value);
	}
	else
	{
		KeyValue<_Key, _Value>* p = hashtable[index];
		while(p->pvoid != (void*)0)
		{
			p = (KeyValue<_Key, _Value>*)p->pvoid;
		}
		p->pvoid = new KeyValue<_Key, _Value>(key, value);
	}
	++size;
	return false;
}

template<class _Key, class _Value, class _HashFunc, class _EqualKey>
Value & HashMap<_Key, _Value, _HashFunc, _EqualKey>::find(const _Key & key)
{
	int index = std::hash<_Key>()(key) % capacity;
	if (hashtable[index] != NULL)
	{
		KeyValue<_Key, _Value>* p = hashtable[index];
		while (p != (void*)0)
		{
			if (p->key == key)
				return p->value;
			else
				p = (KeyValue<_Key, _Value>*)p->pvoid;
		}
	}
	return nullptr;
}
