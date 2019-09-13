/*
Besturingssystemen: opdracht 1
Academiejaar 2013-2014

Naam: Berghmans Brent
Nr: 1334252
*/

#ifndef BUFFER_H
#define BUFFER_H
#include "data.h"
#include <pthread.h>
#include <semaphore.h>

class Buffer {
public:
	Buffer();

	Data *getEmptyDataElement();
	Data *getLastProducedData(Data* previous);
	void publish(Data *d);
	void release(Data *d);
	void registerProducer();
	void releaseProducer();
	void enableWait();
	void waitForNewElement();
	void newElement();
	bool isProducing();
	bool hasNewerDataThan(Data* previous);

private:
	static const unsigned int BUFFERSIZE = 10;
	Data storage[BUFFERSIZE];
	Data* lastProduced;

	//To know if someone is still producing something
	unsigned int prodsWorking;
	unsigned int handlersWaiting;

	// For locking prodsWorking
	pthread_mutex_t prodsWorkingMutex;
	// For locking lastProduced
	pthread_mutex_t lastProducedMutex;
	// Lock the handlerswaiting
	pthread_mutex_t handlerMutex;
	// 
	sem_t waitSem;
};

#endif