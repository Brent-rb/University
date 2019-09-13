#include <stdlib.h>
#include <stdio.h>
#include <time.h>


#define ROWSIZE 10
#define COLUMNSIZE 10


void writeTable2D(int [][COLUMNSIZE], int, int);
void fillTable(int [][COLUMNSIZE], int , int);

int main(void) {
	int table[ROWSIZE][COLUMNSIZE];
	fillTable(table, ROWSIZE, COLUMNSIZE);
	writeTable2D(table, ROWSIZE, COLUMNSIZE);

	return 0;
}

void writeTable2D(int table[][COLUMNSIZE], int rowsize, int columnsize) {
	
	int row, column;
	int i = 0;
	int amountSpaces;
	int number; 
	int amountStripes = 3;

	for(row = 0; row < rowsize; row++) {
		for(column = 0; column < columnsize; column++) {
			if(row == 0) {
				if(column == 0)
					printf("┏━━━");
				else if(column != columnsize - 1)
 					printf("┳━━━");
				else if(column == columnsize - 1)
					printf("┳━━━┓");
			}
			else {
				if(column == 0)
					printf("┣━━━");
				else if(column != columnsize - 1)
					printf("╋━━━");
				else if(column == columnsize - 1)
					printf("╋━━━┫");
			}
		}
		printf("\n");

		for(column = 0; column < columnsize; column++) {
			number = table[row][column];
			amountSpaces = 0;
			while(number > 0) {
				number = (int)(number / 10.0);
				amountSpaces++;
			}
			amountSpaces = amountStripes - amountSpaces;
			printf("┃");
			if(amountSpaces == 1)
				printf(" ");
			for(i = 0; i < amountSpaces/2; i++) {
				printf(" ");
			}
			printf("%d", table[row][column]);
			for(i = 0; i < amountSpaces/2; i++) {
				printf(" ");
			}
			if(column == columnsize - 1)
				printf("┃");
		}

		printf("\n");

		for(column = 0; column < columnsize; column++) {
			if(row == rowsize - 1) {
				if(column == 0)
					printf("┗━━━");
				else if(column != columnsize - 1)
					printf("┻━━━");
				else if(column == columnsize - 1)
					printf("┻━━━┛");
			}
			
		}
	}
	printf("\n");
}

void fillTable(int table[][COLUMNSIZE], int rowsize, int columnsize) {
	int row = 0, column = 0;

	for(row = 0; row < rowsize; row++) {
		for(column = 0; column < columnsize; column++) {
			table[row][column] = (int)(rand() % 1000);

		}
	}

}
