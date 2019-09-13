/*
Besturingssystemen: opdracht 1
Academiejaar 2013-2014

Naam: Berghmans Brent
Nr: 1334252
*/

#include "data.h"

Data::Data(): refcount(0), value(0) {
	pthread_mutex_init(&refMutex, NULL);
}

void Data::ref() { 
	//Pre-caution against dirty read/writes
	pthread_mutex_lock(&refMutex);
	refcount++; 
	pthread_mutex_unlock(&refMutex);
}

void Data::unref() { 
	//Pre-caution against dirty read/writes
	pthread_mutex_lock(&refMutex);
	refcount--; 
	pthread_mutex_unlock(&refMutex); 
}

bool Data::isUnused() {
	//We need to use a boolean to remember the result
	//Because we cant unlock the mutex after a return
	bool outcome;

	//Pre-caution against dirty read/writes
	pthread_mutex_lock(&refMutex);
	outcome = refcount == 0;
	pthread_mutex_unlock(&refMutex);

	return outcome;
}

void Data::setValue(int val) { 
	value = val;
}

void Data::print(std::ostream &ostr) { 
	ostr << value << std::endl; 
}
