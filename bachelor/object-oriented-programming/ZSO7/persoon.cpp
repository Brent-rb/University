#include "persoon.h"
#include <cstring>
#include <iostream>
using namespace std;

int main() {
	Persoon brent("Brent", 18, MAN);
	brent.printPersoon();
	return 0;
}

Persoon::Persoon(char const name[], int const &age, Gender const &gender) {
	if(name != NULL)
		makeName(name);
	
	this->age = age;
	this->gender = gender;
}

Persoon::Persoon(Persoon const &persoon) {
	if(name != NULL)
		makeName(persoon.name);

	this->age = persoon.age;
	this->gender = persoon.gender;
}

Persoon::Persoon() {
	this->name = NULL;
	this->age = 0;
	this->gender = UNKNOWN;
}

Persoon::~Persoon() {
	freeName();
}


char* Persoon::getName() {
	return this->name;
}

int Persoon::getAge() {
	return this->age;
}

Gender Persoon::getGender() {
	return this->gender;
}


void Persoon::setName(char const name[]) {
	if(name == NULL)
		return;

	freeName();
	makeName(name);
}

void Persoon::setAge(int const age) {
	this->age = age;
}

void Persoon::setGender(Gender const gender) {
	this->gender = gender;
}

void Persoon::freeName() {
	if(this->name != NULL)
		delete this->name;
	this->name = NULL;
}

void Persoon::makeName(char const name[]) {
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

void Persoon::printPersoon() {
	cout << "Persoon:  " << this->name << "\nLeeftijd: " << this->age << "\nGeslacht: ";
	if(this->gender == MAN)
		cout << "Man\n";
	else if(this->gender == VROUW)
		cout << "Vrouw\n";
	else
		cout << "Onbekend\n";
}