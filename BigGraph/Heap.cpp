#include "Heap.h"

#include<vector>

template<class T>
void Heap<T>::pop()
{


	
}

template<class T>
void Heap<T>::push(T t)
{
	h.push(t);
	int now = h.size();
	int n = now;
	while (n >> 1)
	{
		if (h[n] < t)
		{
			h[now] = h[n];
			h[n] = t;
			now = n;
		}
		else
			break;
	}

}

template<class T>
T Heap<T>::top()
{

	T t = new T();
	return std::move(t);
}




