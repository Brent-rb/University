#include "Bestuurder.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>

Bestuurder::Bestuurder(char* name, int age) {
	this->name = (char*) malloc(strlen(name) + 1);
	strcpy(this->name, name);

	this->age = age;
}

Bestuurder::~Bestuurder() {
	free(this->name);
}

void Bestuurder::PrintBestuurder() {
	std::cout << "\nDe bestuurder: " << this->name << "\nAge: " << this->age << " jaar oud.\n\n";
}