#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

struct complex {
		int x;
		int i;
	}; 
void product(struct complex*, struct complex*, struct complex*);
void printComplex(struct complex*);

int main(void) {

	
	struct complex z1 = { 5, 3 };
	struct complex z2 = { 5, -3 };
	struct complex answer;

	product(&z1, &z2, &answer);
	printComplex(&answer);
	return 0;
}


void product(struct complex* z1, struct complex* z2, struct complex* answer) {
	int real;
	int complex;
	real = ((z1->x) * (z2->x)) - ((z1->i) * (z2->i));
	complex = ((z1->x) * (z2->i)) + ((z2->x) * (z1->i));
	answer->x = real;
	answer->i = complex;
}

void printComplex(struct complex* z) {
	printf("Het reeële gedeelte is: %d\nHet complexe gedeelte is: %d\n", z->x, z->i);
}
