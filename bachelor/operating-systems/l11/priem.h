#ifndef PRIEM_H
#define PRIEM_H
#include <pthread.h>
#include <vector>
#include <map>
#include <set>
#include <semaphore.h>

class PriemGetallen {
public:
	PriemGetallen();
	~PriemGetallen();

	void addNumber(int number);
	void checkedNumber(int number);
	void removeNumber(int number);
	void clear();
	void print();

	std::vector<int> getNumbers();
	bool contains(int number);
	void waitOnNumber(int number);
	int getSize();

private:
	sem_t $dataMutex;
	sem_t $mapMutex;
	sem_t $checkedMutex;
	std::vector<int> $data;
	std::set<int> $checked;
	std::map<int, sem_t*> $waitList;
};



#endif