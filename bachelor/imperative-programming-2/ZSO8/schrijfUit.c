#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define length 8

void schrijfUit(char[8], char unsigned);
int todec(char[], int);

int main(int argc, char const *argv[]) {
	

	char woord[255];
	strcpy(woord, argv[1]);
	char temp[255];
	strcpy(temp, argv[2]);
	int x = todec(temp, 2);
	printf("%d\n", x);
	char unsigned vlag = (char unsigned)x;
	printf("%0x\n", vlag);
	schrijfUit(woord, vlag);

	return 0;
}

void schrijfUit(char woord[8], char unsigned vlag) {
	char unsigned mask = 0x80;
	int i;

	for(i = 0; i < strlen(woord); i++) {
		if((mask & vlag) == mask)
			printf("%c", woord[i]);
		mask >>= 1;
	}
	printf("\n");
}


int todec(char woord[], int talstelsel) {
	int binary = 1;
	int i;
	int temp;
	int number = 0;

	for(i = strlen(woord) - 1; i >= 0; i--) {
		temp = woord[i] - '0';
		if(temp > 10)
			temp -= ('A' - '0') - 10;
		number += (binary * temp);
		binary *= talstelsel;
	}

	return number;
}