#include "HashMap.h"

template<class _Key, class _Value, class _HashFunc, class _EqualKey>
HashMap<_Key, _Value, _HashFunc, _EqualKey>::HashMap()
{
	hashfunc = new _HashFunc();
	equalkey = new _EqualKey();
	capacity = 57;//直接这样写快一点，本代码经过优化。否则应该写capacity=GetNextPrime(0)；
	hashtable = new KeyValue<_Key, _Value>[capacity + 1];
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
	int index = hashfunc(Key) % capacity;
	hashtable + index->value = std::move(value);
	hashtable + index->key = std::move(key);


	return false;
}
