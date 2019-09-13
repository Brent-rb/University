#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <queue>

void* fac(void *arg);

int main(int argc, char const *argv[]) {
	std::queue<pthread_t*> threadQueue;
	pthread_t* curThread;
	int number;
	int* copy;

	do {
		std::cout << "Enter a number: ";
		std::cin >> number;
		if(number > 0) {
			copy = new int;
			*copy = number;
			curThread = new pthread_t;
			pthread_create(curThread, NULL, fac, copy);
			threadQueue.push(curThread);
		}
	} while(number > 0);

	while(!threadQueue.empty()) {
		curThread = threadQueue.front();
		threadQueue.pop();
		pthread_join(*curThread, NULL);
		delete curThread;
	}

	return 0;
}

void* fac(void *arg) {
	int fac = (*(int*) arg);
	delete (int*) arg;
	int total = 0;

	for(int i = 0; i < fac; i++) {
		total += i;
		sleep(1);
	}

	std::cout << "Fibbonaci " << fac << " is: " << total << std::endl;
}