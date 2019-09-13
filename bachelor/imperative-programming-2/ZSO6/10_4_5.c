#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void zoekStrings(char [], char []);

int main(void) {
	char bronString[] = "Oefeningen C";
	char zoekString[] = "en";

	zoekStrings(bronString, zoekString);

	return 0;
}

void zoekStrings(char bronString[], char zoekString[]) {
	char* bronPointer = bronString;
	char* tempPointer;


	while(bronPointer != NULL && strlen(bronPointer) > 0) {
		tempPointer = strstr(bronPointer, zoekString);
		if(tempPointer != NULL) {
			printf("%s\n", tempPointer);
			bronPointer = tempPointer + strlen(zoekString);
		}
		else
			break;
	}

	return;
}
