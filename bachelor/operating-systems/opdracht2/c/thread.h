/*
Besturingssystemen: opdracht 1
Academiejaar 2013-2014

Naam: Berghmans Brent
Nr: 1334252
*/

#ifndef THREAD_H
#define THREAD_H
#include <pthread.h>

void *start_thread(void *t);
void Error(const char* string);

class Thread {
public:
	Thread();

	void start();
	void wait();
	static void sleep(unsigned int msecs);
	virtual void run() = 0;

private:
	pthread_t tid;
};

#endif