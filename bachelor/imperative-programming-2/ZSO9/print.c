#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define ROWSIZE 5
void printRow(int[], int);

int main(int argc, char const *argv[])
{
	int i, j, original = 0;
	int temp;
	srand(time(NULL));
	int rij[ROWSIZE];
	for(i = 0; i < ROWSIZE; i++) {
		do {
			temp = rand() % 10;
			original = 1;
			for (j = 0; j < i; j++) {
				if(temp == rij[j])
					original = 0;
			}
		} while(original == 0);
		rij[i] = temp;
	}

	printRow(rij, ROWSIZE);

	return 0;
}
void printRow(int row[], int amount) {
	int i, j, k;

	for(i = 0; i < amount - 2; i++) {
		for(j = i + 1; j < amount - 1; j++) {
			for(k = j + 1; k < amount; k++) {
				printf("%c%c%c\n", row[i] + '0', row[j] + '0', row[k] + '0');
			}
		}
	}
}