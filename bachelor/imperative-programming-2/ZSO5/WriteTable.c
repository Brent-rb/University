#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void fillInt(int [2][2]);
void multiply2x2(int [2][2], int [2][2], int [2][2]);

#define SIZE 2

int main(void) {
	int table1[SIZE][SIZE];
	int table2[SIZE][SIZE];
	int result[SIZE][SIZE];

	fillInt(table1);
	fillInt(table2);

	multiply2x2(table1, table2, result);

	printTable()
	return 0;
}

void fillInt(int table[2][2]) {
	int row = 0, column = 0;

	for(row = 0; row < SIZE; row++) {
		for(column = 0; column < SIZE; column++) {
			table[row][column] = (int)(rand() % 100);
		}
	}
}

void multiply2x2(int table1[2][2], int table2[2][2], int result[2][2]) {
	int row, column, row2, column2, result = 0;
	
}
