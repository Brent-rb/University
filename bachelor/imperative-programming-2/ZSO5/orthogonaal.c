#include <stdio.h>
#include <stdlib.h>
#include <time.h>



void fillVector(float []);
float getInProduct(float [], float []);

#define TABLESIZE 10

int main(void) {
	float vector1[TABLESIZE];
	float vector2[TABLESIZE];
	float result = 0.0f;

	fillVector(vector1);
	fillVector(vector2);

	result = getInProduct(vector1, vector2);

	int i;

	for(i = 0; i < TABLESIZE; i++) {
		printf("vector1[%d]:\t%f\n", i, vector1[i]);
	}
	for(i = 0; i < TABLESIZE; i++) {
		printf("vector2[%d]:\t%f\n", i, vector2[i]);
	}

	if(result == 0.0f)
		printf("Het resultaat was: %f dus het is %s\n", result, "orthogonaal.");
	else
		printf("Het resultaat was: %f dus het is %s\n", result, "niet orthogonaal.");
}

void fillVector(float table[]) {
	int i;
	float *pTable = NULL;
	pTable = table;
	srand(time(NULL));

	for(i = 0; i < TABLESIZE; i++) {
		*(pTable + i) = ((float)rand() / 10000000.0f);
	}

}

float getInProduct(float vector1[], float vector2[]) {
	int i;
	float *pVector1 = NULL; 
	float *pVector2 = NULL;
	float result = 0.0f;

	pVector2 = vector2;
	pVector1 = vector1;

	for(i = 0; i < TABLESIZE; i++) {
		result += *(pVector1 + i) * *(pVector2 + i);
	}

	return result;
}
