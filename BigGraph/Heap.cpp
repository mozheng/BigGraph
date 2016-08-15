#include "Heap.h"

#include<vector>

template<class T>
Heap<T>::Heap()
{
	h.push_pack(0);
}

template<class T>
void Heap<T>::pop()
{
	*h.begin() = *h.end();
	h.pop_back();
	int size = h.size() - 1;
	int now = 1;
	int next = now << 1;
	while (next < size)
	{

	}

	
}

template<class T>
void Heap<T>::push(T t)
{
	h.push(t);
	int now = h.size() - 1;
	int next = now>>1;
	while (next)
	{
		if (h[next] < t)
		{
			h[now] = h[next];
			h[next] = t;
			now = next;
		}
		else
			break;
		next = next >> 1;
	}

}

template<class T>
T Heap<T>::top()
{

	T t = new T();
	return std::move(t);
}




