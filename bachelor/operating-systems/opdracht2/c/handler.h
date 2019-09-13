/*
Besturingssystemen: opdracht 1
Academiejaar 2013-2014

Naam: Berghmans Brent
Nr: 1334252
*/

#ifndef HANDLER_H
#define HANDLER_H
#include "thread.h"
#include <iostream>

class Buffer;

class Handler : public Thread {
public:
	Handler(Buffer &b, std::ostream &ostr);

private:
	void run();
	void handleData(Data *d);

	Buffer &buffer;
	std::ostream &ostr;
};

#endif