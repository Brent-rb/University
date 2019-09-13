#include <stdio.h>
#include <stdlib.h>

void fillTable(int table[], int size);
void fillPointers(int table1[], int *table2[], int size);

int main() {
	int tableLength = 30;
	int table1[tableLength];
	int *table2[tableLength];
	int i;

	fillTable(table1, tableLength);
	fillPointers(table1, table2, tableLength);

	for(i = 0; i < tableLength; i++) {
		printf("Table1[%d]:\t%d\n", i, table1[i]);
	}
	for( i = 0; i < tableLength; i++) {
		printf("Table2[%d]:\t%p\n", i, table2[i]);
	}
	printf("Pointer Start: %p\n", table1);

	return 0;
}

void fillTable(int table[], int size) {
	int i;
	for(i = 0; i < size; i++) {
		table[i] = (int)(rand() % 100);
	}
}

void fillPointers(int table1[], int *table2[], int size) {
	int lowestNum = 0, lowestPos = 0, pointerCount = 0;
	int booleanTable[size];
	int i;
	for(i = 0; i < size; i++) {
		booleanTable[i] = 1;
	}
	lowestNum = table1[0];
	for(pointerCount = 0; pointerCount < size; pointerCount++) {
		for(i = 0; i < size && booleanTable[i] == 0; i++){

		}
		lowestPos = i;
		lowestNum = table1[i];

		for(i = 0; i < size; i++) {
			if(table1[i] < lowestNum && booleanTable[i] == 1) {
				lowestNum = table1[i];
				lowestPos = i;
			}
		}
		booleanTable[lowestPos] = 0;
		table2[pointerCount] = &table1[lowestPos];
	}
}