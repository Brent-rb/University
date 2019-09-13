#include <iostream>
#include "Datum.h"
#include <stdio.h>

using namespace std;

Datum::Datum() {
	this->day = 0;
	this->month = 0;
	this->year = 0;
}

Datum::Datum(int day, int month, int year) {
	this->day = day;
	this->month = month;
	this->year = year;
}

Datum::Datum(char* dateString) {
	sscanf(dateString, "%d/%d/%d", &(this->day), &(this->month), &(this->year));
}

void Datum::SetDate(int day, int month, int year) {
	this->day = day;
	this->month = month;
	this->year = year;
}

void Datum::SetDay(int day) {
	this->day = day;
}

void Datum::SetMonth(int month) {
	this->month = month;
}

void Datum::SetYear(int year) {
	this->year = year;
}

int Datum::GetDay() {
	return this->day;
}

int Datum::GetMonth() {
	return this->month;
}

int Datum::GetYear() {
	return this->year;
}

Datum::~Datum() {
	printf("Het is gedeconstructd.\n");
}
