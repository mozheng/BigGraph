#include "ThreadPool.h"


void ThreadPool::addTask(const std::function<void()> task)
{
	m_queue.pushElement(task);
}

void ThreadPool::RunInThread()
{

	while (m_running)
	{
		std::list< std::function<void()> > list;
		m_queue.takeQueue(list);
		
		for (auto& task : list)
		{
			if (!m_running)return;
			std::lock_guard<std::mutex> locker(m_execute);
			task();
		}

	}

}

void ThreadPool::start(int numThread)
{
	m_running = true;
	for (int i = 0; i < numThread; ++i)
	{
		m_threadgroup.push_back(std::make_shared<std::thread>(&ThreadPool::RunInThread, this));
	}
}

void ThreadPool::StopThreadGroup()
{
	m_queue.stop();
	m_running = false;
	for (auto thread : m_threadgroup)
	{
		if (thread)
			thread->join();
	}
	m_threadgroup.clear();
}
