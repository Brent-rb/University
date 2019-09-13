/*
Besturingssystemen: opdracht 1
Academiejaar 2013-2014

Naam: Berghmans Brent
Nr: 1334252
*/

#ifndef DATA_H
#define DATA_H
#include <iostream>
#include <pthread.h>

class Data {
public:
	Data();
	void ref();
	void unref();
	bool isUnused();
	void setValue(int val);
	void print(std::ostream &ostr);

private:
	unsigned int refcount;
	// Value does not need to be locked because the producer can NEVER
	// Get a data slot that is going to be read
	int value;
	// Reffing and Unreffing occurs randomly when a thread starts
	// and this can cause dirty reads and writes
	pthread_mutex_t refMutex;
};

#endif