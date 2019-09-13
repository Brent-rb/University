#ifndef AFSPRAAK_H
#define AFSPRAAK_H
#include "datum.h"

struct Afspraak {
	struct Datum dateStruct;
	char* description;
};

int readAfspraak(struct Afspraak** afspraakStruct);
int writeAfspraak(struct Afspraak* const afspraakStruct);
int freeAfspraak(struct Afspraak** afspraakStruct);
#endif