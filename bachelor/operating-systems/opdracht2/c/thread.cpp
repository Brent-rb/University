/*
Besturingssystemen: opdracht 1
Academiejaar 2013-2014

Naam: Berghmans Brent
Nr: 1334252
*/

#include "thread.h"
#include <stdlib.h>
#include <iostream>

#ifdef WIN32
	#include <process.h>
#else
	#include <time.h>
#endif

void Error(const char *str) {
	std::cerr << str << std::endl;
	exit(0);
}

void* start_thread(void *t) {
	reinterpret_cast<Thread *>(t)->run();
	return 0;
}

Thread::Thread(): tid(0) {

}

void Thread::start() {
	if(pthread_create(&tid, 0, start_thread, (void*)this) != 0)
		Error("Error: failed to create thread");
}

void Thread::wait() {
	void *status;
	pthread_join(tid, &status);
}

void Thread::sleep(unsigned int msecs) {
#ifdef WIN32
	if(SleepEx(msecs, TRUE) != 0)
		Error("Error: SleepEx interrupted");
#else
	// timeout value for wait function
    struct timespec timeout; 

    // prepare timeout value
    timeout.tv_sec = msecs / 1000;
	msecs -= timeout.tv_sec * 1000;
    timeout.tv_nsec = (1000 * msecs) * 1000;

	if( nanosleep(&timeout, 0) != 0)
		Error("Error: nanosleep interrupted or failed");
#endif
}