#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

void fromdec(char[], int);
void todec(char[], int);
enum talstelsel {BINAIR = 2, OCTAAL = 8, DECIMAAL = 10, HEXADECIMAAL = 16};

int main(int argc, char const *argv[])
{
	char temp[32];
	strcpy(temp, argv[2]);
	if(strcmp("decbin", argv[1]) == 0)
		fromdec(temp, BINAIR);
	if(strcmp("decoct", argv[1]) == 0)
		fromdec(temp, OCTAAL);
	if(strcmp("dechex", argv[1]) == 0)
		fromdec(temp, HEXADECIMAAL);

	if(strcmp("bindec", argv[1]) == 0)
		todec(temp, BINAIR);
	if(strcmp("octdec", argv[1]) == 0)
		todec(temp, OCTAAL);
	if(strcmp("hexdec", argv[1]) == 0)
		todec(temp, HEXADECIMAAL);
	return 0;
}

void fromdec(char woord[], int deler) {
	int number = atoi(woord);
	char temp[255] = "";
	while(number != 0) {
		strcpy(&temp[1], temp);
		if((number % deler) < 10)
			temp[0] = (number % deler) + '0';
		else
			temp[0] = (((number % deler) - 10) + 'A');
		number /= deler;
	}

	printf("%s\n", temp);
}

void todec(char woord[], int talstelsel) {
	int binary = 1;
	int i;
	int temp;
	int number = 0;

	for(i = strlen(woord) - 1; i >= 0; i--) {
		if(woord[i] <= 'f' && woord[i] >= 'a') {
			temp = woord[i] - 'a' + 10;
		}
		else if(woord[i] <= 'F' && woord[i] >= 'a') {
			temp = woord[i] - 'A' + 10;
		}
		else {
			temp = woord[i] - '0';
		}
		number += (binary * temp);
		binary *= talstelsel;
	}

	printf("%d\n", number);
}