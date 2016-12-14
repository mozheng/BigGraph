#include <iostream>
#include <chrono> 
#include "ThreadPool.h"
using namespace std;


int main()

{
	ThreadPool pool(100);
	std::thread thd1([&pool] {
		for (int i = 0; i < 10; ++i)
		{
			auto threadid = this_thread::get_id();
			pool.addTask([threadid,i](){
				cout << "thread1,ID" << i << ":" << threadid << endl;
			});
		}
	});
	std::thread thd2([&pool] {
		for (int i = 0; i < 10; ++i)
		{
			auto threadid = this_thread::get_id();
			pool.addTask([threadid,i](){
				cout << "thread2,ID" << i << ":" << threadid << endl;
			});
		}
	});
	this_thread::sleep_for(chrono::seconds(4));
	thd1.join();
	thd2.join();
	pool.stop();
	return 0;
}