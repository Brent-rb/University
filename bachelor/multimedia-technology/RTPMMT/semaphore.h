#pragma once
#include <mutex>
#include <condition_variable>

//Inspired by http://stackoverflow.com/questions/4792449/c0x-has-no-semaphores-how-to-synchronize-threads
class semaphore {
public:
	semaphore(unsigned long startCount);
	semaphore();
	~semaphore();

	void notify();
	void wait();

private:
	std::mutex $mutex;
	std::condition_variable $conditionVar;
	unsigned long $count;
};