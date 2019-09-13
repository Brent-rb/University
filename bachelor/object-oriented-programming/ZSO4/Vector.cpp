#include "Vector.h"
#include <iostream>
using namespace std;

Vector::Vector() {
	this->size = 0;
	this->vectorArray = NULL;
	this->state = NOT;
}

void Vector::Allocate(int amount) {
	char c;
	if(state == ALLOCATED) {
		cout << "Er is al een vector aangemaakt, overschrijven? y/n: ";
		cin >> c;
		if(c == 'n') {
			cout << "Tabel niet overschreven.\n";
			return; 
		}
		else {
			cout << "Tabel overschreven.\n";
			delete[] vectorArray;
			vectorArray = NULL;
			state = NOT;
		}
	}

	this->size = amount;
	this->vectorArray = new double[amount];
	for(int i = 0; i < this->size; i++) 
		this->vectorArray[i] = 0.0;
	state = ALLOCATED;
}

Vector::~Vector() {
	if(state == ALLOCATED)
		delete[] vectorArray;
}


void Vector::SchrijfUit() {
	if(state == ALLOCATED)
		for(int i = 0; i < this->size; i++)
			cout << "[" << i << "]:\t" << this->vectorArray[i] << "\n"; 
	else
		cout << "Geen tabel aangemaakt.\n";
}

bool Vector::IsAllocated() {
	if(state == ALLOCATED)
		return true;
	else
		return false;
}