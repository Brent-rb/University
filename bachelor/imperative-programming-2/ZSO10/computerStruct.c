#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct computer {
	int cpuSpeed;
	int amountRam;

} computer;

#define SIZE 3

computer* makeStruct(void);
void readStruct(computer*);

int main(int argc, char const *argv[])
{
	int i;
	computer* pcs[SIZE];

	for(i = 0; i < SIZE; i++) {
		pcs[i] = NULL;
	}

	for(i = 0; i < SIZE; i++) {
		if(pcs[i] == NULL)
			pcs[i] = makeStruct();
		readStruct(pcs[i]);
	}

	for(i = 0; i < SIZE; i++) {
		printf("\nPointer van PC(%d) is : %p\n", i, pcs[i]);
		printf("PC(%d) Heeft %dMhz kloksnelheid en %dGb geheugen.\n", i + 1, pcs[i]->cpuSpeed, pcs[i]->amountRam);
		free(pcs[i]);
		pcs[i] = NULL;
		printf("\nPointer van PC(%d) is : %p\n", i, pcs[i]);
	}


	return 0;
}

computer* makeStruct(void) {
	computer* newPointer = (computer*) malloc(sizeof(computer));
	return newPointer;
}

void readStruct(computer* pointer) {
	printf("Geef de kloksnelheid: ");
	scanf("%d", &pointer->cpuSpeed);
	printf("Geef de hoeveelheid ram: ");
	scanf("%d", &pointer->amountRam);
}