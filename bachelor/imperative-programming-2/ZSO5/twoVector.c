#include <stdio.h>
#include <stdlib.h>

void fillVectors(float []);
void multiplyVectors(float [], float[], float[]);

#define FLOATSIZE 10

int main(void) {
	float vector1[FLOATSIZE];
	float vector2[FLOATSIZE];
	float vector3[FLOATSIZE];

	fillVectors(vector1);
	fillVectors(vector2);

	multiplyVectors(vector1, vector2, vector3);

	int i;

	for(i = 0; i < FLOATSIZE; i++) {
		printf("%f\t*\t%f\t=\t%f\n", vector1[i], vector2[i], vector3[i]);
	}



	return 0;
}

void fillVectors(float table[]) {
	int i;

	for(i = 0; i < FLOATSIZE; i++) {
		table[i] = ((float)rand() / 10000000.0f);
	}

}

void multiplyVectors(float vector1[], float vector2[], float resultVector[]) {
	float *pVector1 = NULL;
	float *pVector2 = NULL;
	float *pResult = NULL;
	int i;

	pVector1 = vector1;
	pVector2 = vector2;
	pResult = resultVector;

	for(i = 0; i < FLOATSIZE; i++) {
		*(pResult + i) = *(pVector1 + i) * *(pVector2 + i);
	}
}
