#include "Fiets.h"
#include "Bestuurder.h"
#include <stdlib.h>
#include <iostream>

Fiets::Fiets(char* name, int age) {
	this->driver = new Bestuurder(name, age);
}

void Fiets::Crash() {
	if(this->driver != NULL) {
		std::cout << "De bestuurder reed tegen een boom, viel in een ravijn, kwam terecht in een rivier, viel van een waterval af en verdronk :(\n";
		delete this->driver;
		this->driver = NULL;
	}
	else {
		std::cout << "De bestuurder is al dood :(.\n";
	}
}

Fiets::~Fiets() {
	if(this->driver != NULL)
		Crash();
}

void Fiets::PrintDriver() {
	if(this-> driver != NULL)
		this->driver->PrintBestuurder();
	else
		std::cout << "De bestuurder is overleden :(.\n";
}


int main() {
	Fiets fiets("Faggot", 15);
	fiets.PrintDriver();


	return 0;
}