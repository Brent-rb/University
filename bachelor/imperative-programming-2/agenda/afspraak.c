#include "afspraak.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define STRINGBUFFERSIZE 256

int readAfspraak(struct Afspraak** afspraakStruct) {
	char tempString[256];
	char* tempPointer;
	int outcome;
	struct Afspraak* newPointer = NULL;
	newPointer = (struct Afspraak*) malloc(sizeof(struct Afspraak));
	if(newPointer == NULL)
		return 0;

	outcome = readDate(&(newPointer->dateStruct));
	if(outcome == 0)
		return 0;

	printf("Geef de beschrijving.\n");
	fgets(tempString, 255, stdin);

	if(tempString[strlen(tempString) - 1] == '\n')
		tempString[strlen(tempString) - 1] = '\0';

	tempPointer = (char*) malloc(strlen(tempString) + 1);
	if(tempPointer == NULL)
		return 0;



	strcpy(tempPointer, tempString);
	newPointer->description = tempPointer;

	*afspraakStruct = newPointer;

	return 1;

}

int writeAfspraak(struct Afspraak* const afspraakStruct) {
	printf("\n_______________________________________\n");
	writeDate(&(afspraakStruct->dateStruct));
	printf("Description:\n");
	printf("%s", afspraakStruct->description);
	printf("_______________________________________\n");
}

int freeAfspraak(struct Afspraak** afspraakStruct) {
	free((*afspraakStruct)->description);
	free(*afspraakStruct);
	*afspraakStruct = NULL;
}
