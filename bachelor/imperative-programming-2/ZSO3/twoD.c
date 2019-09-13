#include <stdio.h> 
#include <math.h>
#include <stdlib.h>

#define rows 5
#define columns 5

int getRandomNum(int);

int main() {
	int i, j;
	int array[rows][columns];
	int temp;

	for(i = 0; i < rows; i++) {
		for(j = 0; j < columns; j++) {
			array[i][j] = getRandomNum(50);
		}
	}
	/*
	pointer = array;
	printf("De array heeft als adres: \t%d\n", pointer);*/

	for(i = 0; i < rows; i++) {
		for(j = 0; j < columns; j++) {
			printf("Array(%d,%d) heeft als adres: \t%p\n", i, j, &array[i][j]);
		}
	}
}

int getRandomNum(int upperLimit) {
	int randomNum = rand() % upperLimit;
	return randomNum;
}