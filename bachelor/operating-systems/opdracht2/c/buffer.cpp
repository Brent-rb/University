/*
Besturingssystemen: opdracht 1
Academiejaar 2013-2014

Naam: Berghmans Brent
Nr: 1334252
*/

#include "buffer.h"
#include "data.h"

Buffer::Buffer(): lastProduced(0), prodsWorking(0), handlersWaiting(0) {
	pthread_mutex_init(&prodsWorkingMutex, NULL);
	pthread_mutex_init(&lastProducedMutex, NULL);
	pthread_mutex_init(&handlerMutex, NULL);
	sem_init(&waitSem, 0, 0);
}

Data* Buffer::getEmptyDataElement() {
	// Empty data element
	Data *d = 0;

	//Loop over buffer
	for (int i = 0; i < BUFFERSIZE; i++)  {
		// Locking/Unlocking occurs inside the loop to reduce
		// The chance of starvation
		// We lock lastProduced in the case of multiple producers working
		pthread_mutex_lock(&lastProducedMutex);

		//Storage slot should be different from lastProduced
		//Because there's a chance the handler is just in the middle
		//Of getLastProducedData and we test .isUnused just before 
		//The refcounter is increased.
		//And thus it would not really be empty.
		if ((&storage[i]) != lastProduced && storage[i].isUnused()) {
			d = &storage[i];
			//Unlock because of break
			pthread_mutex_unlock(&lastProducedMutex);
			break;
		}
		pthread_mutex_unlock(&lastProducedMutex);
	}

	return d;
}

Data *Buffer::getLastProducedData(Data* previous) {
	bool wait;

	//Lock so we don't read in the middle of publish
	pthread_mutex_lock(&lastProducedMutex);
	Data *d = lastProduced;
	pthread_mutex_unlock(&lastProducedMutex);
	//Same data, so wait
	while (previous == d && isProducing()) {
		waitForNewElement();
		pthread_mutex_lock(&lastProducedMutex);
		d = lastProduced;
		pthread_mutex_unlock(&lastProducedMutex);
	}

	d->ref();
	return d;
}

void Buffer::waitForNewElement() {
	pthread_mutex_lock(&handlerMutex);
	handlersWaiting++;
	pthread_mutex_unlock(&handlerMutex);
	sem_wait(&waitSem);
}

void Buffer::newElement() {
	pthread_mutex_lock(&handlerMutex);
	for(int i = 0; i < handlersWaiting; i++) {
		sem_post(&waitSem);
	}
	pthread_mutex_unlock(&handlerMutex);
}

/* update last produced, so getLastProducedData returns the correct element */
void Buffer::publish(Data *d) {
	//Lock so we block reads and know no one is reading.
	pthread_mutex_lock(&lastProducedMutex);
	lastProduced = d;
	pthread_mutex_unlock(&lastProducedMutex);
	newElement();
}

/* update handled element, to make it available via getEmptyDataElement */
void Buffer::release(Data *d) {
	d->unref();
}

void Buffer::registerProducer() {
	//This could happen async so we need to lock against dirty read/writes
	pthread_mutex_lock(&prodsWorkingMutex);
	prodsWorking++;
	pthread_mutex_unlock(&prodsWorkingMutex);
}

void Buffer::releaseProducer() {
	//See registerProducer
	pthread_mutex_lock(&prodsWorkingMutex);
	prodsWorking--;
	pthread_mutex_unlock(&prodsWorkingMutex);
}

bool Buffer::isProducing() {
	bool outcome;

	//Lock because a producer could be registering or releasing
	//Prevents dirty read/writes
	pthread_mutex_lock(&prodsWorkingMutex);
	outcome = prodsWorking != 0;
	pthread_mutex_unlock(&prodsWorkingMutex);

	return outcome;
}

bool Buffer::hasNewerDataThan(Data* prev) {
	bool outcome;

	//Lock so we don't read in the middle of publish();
	pthread_mutex_lock(&lastProducedMutex);
	outcome = (lastProduced != prev) && (lastProduced != NULL);
	pthread_mutex_unlock(&lastProducedMutex);

	return outcome;
}