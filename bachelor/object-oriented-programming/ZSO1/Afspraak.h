#ifndef AFSPRAAK_H
#define AFSPRAAK_H
#include "Datum.h"

class Afspraak {
public:
	Afspraak(char* description, Datum date);
	~Afspraak();
	void PrintAfspraak();

private:
	char* description;
	Datum date;
};

#endif