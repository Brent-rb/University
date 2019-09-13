#include <stdio.h>

#define arraySize 12
int getFac(int);

int main() {
	int array[arraySize];
	int i;

	for(i = 1; i <= arraySize; i++) {
		array[i - 1] = getFac(i);
	}

	for(i = 0; i < arraySize; i++) {
		printf("%d \n", array[i]);
	}

	return 0;
}

int getFac(int number) {
	int i;
	int total = number;

	for(i = number - 1; i > 0; i--) {
		total *= i;
	}

	return total;
}