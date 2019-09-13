#include "priem.h"
#include <iostream>

PriemGetallen::PriemGetallen() {
	sem_init(&$dataMutex, 0, 1);
	sem_init(&$mapMutex, 0, 1);
	sem_init(&$checkedMutex, 0, 1);
}

PriemGetallen::~PriemGetallen() {
	sem_destroy(&$dataMutex);
	sem_destroy(&$mapMutex);
	sem_destroy(&$checkedMutex);
}

void PriemGetallen::addNumber(int number) {
	sem_wait(&$dataMutex);
	$data.push_back(number);
	sem_post(&$dataMutex);
}

void PriemGetallen::checkedNumber(int number) {
	//std::cout << "Checking " << number << std::endl;
	sem_wait(&$checkedMutex);
	$checked.insert(number);
	sem_post(&$checkedMutex);

	sem_wait(&$mapMutex);
	if($waitList.count(number) == 1) {
		sem_t* wait = $waitList[number];
		for(int i = 0; i < 20; i++)
			sem_post(wait);
	}
	delete $waitList[number];
	$waitList.erase(number);

	sem_post(&$mapMutex);
}

void PriemGetallen::removeNumber(int index) {
	sem_wait(&$dataMutex);
	//$data.erase(index);
	sem_post(&$dataMutex);

}

void PriemGetallen::clear() {
	sem_wait(&$dataMutex);
	$data.clear();
	sem_post(&$dataMutex);
}

void PriemGetallen::print() {
	sem_wait(&$dataMutex);
	std::vector<int>::iterator it = $data.begin();
	sem_post(&$dataMutex);
	int number;

	while(it != $data.end()) {
		sem_wait(&$dataMutex);
		number = (*it);
		sem_post(&$dataMutex);

		std::cout << number << std::endl;
		it++;
	}
}

std::vector<int> PriemGetallen::getNumbers() {
	std::vector<int> retArr;
	
	sem_wait(&$dataMutex);
	for(int i = 0; i < $data.size(); i++) {
		retArr.push_back($data[i]);
	}
	sem_post(&$dataMutex);

	return retArr;
}

int PriemGetallen::getSize() {
	int size;

	sem_wait(&$dataMutex);
	size = $data.size();
	sem_post(&$dataMutex);

	return size;
}

bool PriemGetallen::contains(int number) {
	bool result;
	sem_wait(&$checkedMutex);
	result = $checked.count(number) != 0;
	sem_post(&$checkedMutex);

	return result;
}

void PriemGetallen::waitOnNumber(int number) {
	
	sem_wait(&$mapMutex);
	//std::cout << "Thread waiting on " << number << std::endl;
	sem_t* ptr;
	if($waitList.count(number) != 0) {
		ptr = ($waitList[number]);
	}
	else {
		ptr = new sem_t();
		sem_init(ptr, 0, 0);
		$waitList.insert(std::pair<int, sem_t*>(number, ptr));
	}
	sem_post(&$mapMutex);
	sem_wait(ptr);
}
