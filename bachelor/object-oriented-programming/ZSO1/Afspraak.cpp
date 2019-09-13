#include <iostream>
#include "Afspraak.h"
#include <string.h>
#include <stdlib.h>
#include "Datum.h"

Afspraak::Afspraak(char* description, Datum date) {
	this->description = (char*) malloc(strlen(description) + 1);
	strcpy(this->description, description);

	this->date = date;
}

Afspraak::~Afspraak() {
	free(this->description);
}

void Afspraak::PrintAfspraak() {
	std::cout << "Beschrijving: " << this->description << "\nOp datum: " << this->date.GetDay() << "/" << this->date.GetMonth() << "/" << this->date.GetYear() << "\n";
}
int main() {

	Datum date("10/12/1995");
	Afspraak afspraak("Dit is een hele slechte omschrijving.", date);
	afspraak.PrintAfspraak();

	return 0;
}