#ifndef DATUM_H
#define DATUM_H

struct Datum {
	int dag;
	int maand;
	int jaar;
};

int readDate(struct Datum* dateStruct);
int writeDate(struct Datum* const dateStruct);

#endif