#pragma once
#include <vector>
#include <functional>

#include "SyncQueue.h"

class ThreadPool
{
public:
	ThreadPool(int maxtask, int numThreads = std::thread::hardware_concurrency()) :maxTaskCount(maxtask), currentthreadnum(0), m_queue(maxtask) { start(numThreads); }
	virtual ~ThreadPool() { stop(); }
	int getCurrentThreadnum() { return currentthreadnum; }
	void addTask(const std::function<void()> task);
	void stop() 
	{
		std::call_once(m_flag, [this] {StopThreadGroup(); });
	}

private:
	void RunInThread();
	void start(int numThread);
	void StopThreadGroup();


private:
	ThreadPool(ThreadPool& t);
	void operator= (ThreadPool& t) {};

private:
	std::list< std::shared_ptr<std::thread> > m_threadgroup;
	SyncQueue< std::function<void()> > m_queue;
	
	std::atomic<bool> m_running;
	std::atomic<int> currentthreadnum;
	const int maxTaskCount;
	std::once_flag m_flag;
	std::mutex m_execute;
};

