#ifndef PRIEMCALCULATOR_H
#define PRIEMCALCULATOR_H
#include <pthread.h>
#include "priem.h"
#include <map>
#include <semaphore.h>


void init(int threads);
void destroy();

void calculate(int max);
void* calculate2(void* args);
void join();
void print();
void launchThread(pthread_t* thread, int number, int threadIndex);
void* pthreadOnObject(void* args);

bool isDeelbaar(int left, int right);

static int threadCount;
static pthread_t* threads;
static sem_t* mutexList;
static sem_t threadsDone;
static bool* doneList;
static PriemGetallen dataStore;

#endif