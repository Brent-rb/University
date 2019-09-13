/*
Besturingssystemen: opdracht 1
Academiejaar 2013-2014

Naam: Berghmans Brent
Nr: 1334252
*/

#ifndef PRODUCER_H
#define PRODUCER_H
#include "thread.h"

//Forward dec
class Buffer;

class Producer : public Thread {
public:
	Producer(Buffer &b, long sequenceNumber);
	virtual ~Producer();

private:
	void run();
	void produceData(Data *d);
	
	Buffer &buffer;
	long sequenceNumber;
};

#endif