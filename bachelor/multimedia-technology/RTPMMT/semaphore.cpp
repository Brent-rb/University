#include "semaphore.h"

semaphore::semaphore(unsigned long startCount) : $count(startCount) {

}

semaphore::semaphore() : $count(0) {

}

semaphore::~semaphore() {

}

void semaphore::notify() {
	std::unique_lock<std::mutex> lock($mutex);
	$count++;
	$conditionVar.notify_one();
}

void semaphore::wait() {
	std::unique_lock<std::mutex> lock($mutex);

	while ($count == 0) {
		$conditionVar.wait(lock);
	}
	$count--;
}