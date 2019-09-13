#include "priemcalculator.h"
#include "priem.h"
#include <cmath>
#include <iostream>

void init(int threadsC) {
	dataStore = PriemGetallen();
	threadCount = threadsC;
	threads = new pthread_t[threadsC];
	mutexList = new sem_t[threadsC];
	doneList = new bool[threadsC];

	for(int i = 0; i < threadsC; i++) {
		sem_init(&(mutexList[i]), 0, 1);
		doneList[i] = true;
	}

	sem_init(&threadsDone, 0, threadsC);
}

void destroy() {
	int* result;
	for(int i = 0; i < threadCount; i++) {
		pthread_join(threads[i], NULL);
	}
	delete[] threads;
	delete[] mutexList;
	delete[] doneList;
}

void calculate(int max) {
	dataStore.addNumber(2);
	dataStore.checkedNumber(1);
	dataStore.checkedNumber(2);
	dataStore.checkedNumber(3);
	dataStore.addNumber(3);
	for(int i = 2; i < max; i++) {
		sem_wait(&threadsDone);
		for(int j = 0; j < threadCount; j++) {
			bool result;
			sem_t* sema = &(mutexList[j]);
			sem_wait(sema);
			result = doneList[j];
			sem_post(sema);

			if(result) {
				launchThread(&threads[j], i, j);
				break;
			}
		}
	}
}

void launchThread(pthread_t* thread, int number, int threadIndex) {
	//std::cout << "Launched thread: " << threadIndex << std::endl;
	int* number2 = new int(number);
	int* threadIndex2 = new int(threadIndex); 
	int* args[2] = {number2, threadIndex2};
	sem_t* sema = &(mutexList[threadIndex]);
	sem_wait(sema);
	doneList[threadIndex] = false;
	sem_post(sema);
	pthread_create(thread, NULL, calculate2, (void*) args);
}

void* calculate2(void* args) {
	int** array = (int**) args;
	int* i = (array[0]);
	int* threadIndex = (array[1]);

	bool isPrime = true;
	int min = sqrt(*i) + 1;

	if(!dataStore.contains(min)) {
		dataStore.waitOnNumber(min);
	}

	std::vector<int> numbers = dataStore.getNumbers();
	for(int j = 0; j < numbers.size(); j++) {
		int number = numbers[j];
		if(min <= number) {
			break;
		}

		if(isDeelbaar(*i, number)) {
			isPrime = false;
			break;
		}
	}

	if(isPrime) {
		//std::cout << "Adding: " << i << std::endl;
		dataStore.addNumber(*i);
		//std::cout << "Added: " << i << std::endl;
	}
	dataStore.checkedNumber(*i);

	sem_post(&threadsDone);
	std::cout << "Index: " << *threadIndex << std::endl;
	sem_t* sema = NULL;
	sema = &(mutexList[*threadIndex]);
	//sema = NULL;
	bool result;
	sem_wait(sema);
	doneList[*threadIndex] = true;
	sem_post(sema);
	delete i;
	delete threadIndex;
}

void join() {
	
}

void print() {
	dataStore.print();
}

bool isDeelbaar(int left, int right) {
	return (left % right == 0);
}
