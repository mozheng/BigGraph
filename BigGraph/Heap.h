#pragma once
template<class T>
class Heap
{
public:
	Heap();
	void pop();
	void push(T t);
	T top();
	int size() { return h.size(); }
	virtual ~Heap();

private:
	std::vector<T> h;
};

