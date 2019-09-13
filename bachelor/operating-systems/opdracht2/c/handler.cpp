/*
Besturingssystemen: opdracht 1
Academiejaar 2013-2014

Naam: Berghmans Brent
Nr: 1334252
*/

#include "buffer.h"
#include "handler.h"

Handler::Handler(Buffer &b, std::ostream &ostr) : buffer(b), ostr(ostr) {

}

void Handler::run() {
	Data *previous = 0;

	//As long as someone is producing data on the buffer we continue
	//If no one is producing there might be some last data, still continue
	while(buffer.isProducing()) {
		//Wait until we have new data.
		//Tried working with "signals", wasn't able to create 
		//a notify-when-new-data system, see info at bottom
		Data *d = buffer.getLastProducedData(previous);
		if(d == previous)
			continue;
		handleData(d);
		buffer.release(d);
		previous = d;
	}
}

void Handler::handleData(Data *d) {
	d->print(ostr);
	//Thread::sleep((float(rand()) / RAND_MAX) * 1000); // sleep between 0 and 1 sec
}

/*
Tried implementing pthread_cond_wait but it didn't work how I wanted it to work
Because the cond_wait uses a mutex it needs to be locked by the same thread that will unlock it.
That was almost impossible in this case.
Implementations I tried had random results.

Tried just working with a mutex, producer would lock mutex, create data
publish it, unlock mutex, sleep and repeat.
Handlers with old data would wait until this mutex got unlocked.
This did not work.

Thought about using semaphores, when a handler had to wait it would decrement
the semaphore, producer would then post the semaphore a couple of times to release 
the waiting handlers.
This would problably work but it seemed like a weird work-around.
Algorithm:
We keep track of the amount of waiting handler in integer $waiting.
We have a semaphore $waitSem that handlers and producer will use for notifying new data
We have a mutex $waitMutex that locks the integer $waiting.

Handler:
1) Lock $waitMutex
2) Check if there is newer data
3.1) If not increment $waiting, release $waitMutex, wait on $waitSem
3.2) If so, unlock and get new data

Producer:
1) Lock $waitMutex
2) Post new data
3) sem_post on $waitSem $waiting amount of times
4) reset $waiting
5) Release $waitMutex
*/