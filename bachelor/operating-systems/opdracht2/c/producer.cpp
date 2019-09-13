/*
Besturingssystemen: opdracht 1
Academiejaar 2013-2014

Naam: Berghmans Brent
Nr: 1334252
*/

#include "buffer.h"
#include "producer.h"
#include <iostream>

Producer::Producer(Buffer &b, long sequenceNumber): buffer(b), sequenceNumber(sequenceNumber) {
	
}

Producer::~Producer() {
	
}

void Producer::run() {
	//Register this producer so the buffer knows we're producing
	buffer.registerProducer();
	for(int i = 0; i < 100; i++) {
		//Get data slot
		Data *d = buffer.getEmptyDataElement();
		//Make some data
		produceData(d);
		//Publish it
		buffer.publish(d);
	}
	//Remove this producer so the buffer knows we're done
	buffer.releaseProducer();
	buffer.newElement();
}

void Producer::produceData(Data *d) {
	Thread::sleep((float(rand()) / RAND_MAX) * 1000); // sleep between 0 and 1 sec
	std::cout << "produced: " << sequenceNumber << std::endl;
	d->setValue(sequenceNumber++);
	//d->print(std::cout);
}
