#include<list>
#include<mutex>
#include<atomic>

//请求队列，数据用list存储
//
//

template<class T>
class SyncQueue
{
public:
	SyncQueue(int maxSize) :m_maxSize(maxSize) {};
	~SyncQueue() {};

	void pushElement(const T&  x) { add(std::move(const_cast<T&>(x))); }
	void pushElement(const T&& x) { add(std::forward<T>(x)); }

	void takeElement(T& t)
	{
		std::unique_lock<std::mutex> locker(queue_mutex);
		m_notEmpty.wait(locker, [this] {return m_flag_stop || !m_queue.empty(); });
		t = std::move(m_queue.front());
		m_queue.pop_front();
		m_notFull.notify_one();
	}
	void takeQueue(std::list<T>& list)
	{
		std::unique_lock<std::mutex> locker(queue_mutex);
		m_notEmpty.wait(locker, [this] {return m_flag_stop || !m_queue.empty(); });
		if (m_flag_stop)return;
		list = std::move(m_queue);
		m_notFull.notify_one();
	}
	void stop() 
	{
		m_flag_stop = true;
		m_notEmpty.notify_all();
		m_notFull.notify_all();
	}
	bool empty() 
	{ 
		std::lock_guard<std::mutex> locker(queue_mutex);
		return m_queue.empty();
	}
	bool full() 
	{ 
		std::lock_guard<std::mutex> locker(queue_mutex);
		return m_queue.size() >= m_maxSize;
	}
	size_t size()
	{
		std::lock_guard<std::mutex> locker(queue_mutex);
		return m_queue.size();
	}

private:
	void add(T&& x)
	{
		std::unique_lock<std::mutex> locker(queue_mutex);
		m_notFull.wait(locker, [this] {return m_flag_stop || m_queue.size() < m_maxSize; });//如果队列不满就跳出等待
		m_queue.push_back(std::forward<T>(x));
		m_notEmpty.notify_one();
	}
private:
	const int m_maxSize;
	std::list<T> m_queue;
	std::mutex queue_mutex;
	std::condition_variable m_notFull;
	std::condition_variable m_notEmpty;
	std::atomic<bool> m_flag_stop;
};
