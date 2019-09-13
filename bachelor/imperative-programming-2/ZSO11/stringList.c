#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct Knoop {
	char* string;
	struct Knoop* previous;
	struct Knoop* next;
} Knoop;

Knoop* arrayToList(Knoop list[]);
void readNew(Knoop** list);
void addNew(Knoop** list, char* stringPointer);
void addSorted(Knoop** list, char* stringPointer);
void printList(Knoop* pointer);
void deleteElement(Knoop** startPointer, Knoop* pointer);
void removeDouble(Knoop** startPointer);
void clearList(Knoop** startPointer);
int compareStrings(char const [], char const []);

int main(int argc, char const *argv[])
{
	int i;
	Knoop* list = NULL;	
	for(i = 0; i < 5; i++) {
		readNew(&list);
	}
	printList(list);

	removeDouble(&list);

	printList(list);

	clearList(&list);

	return 0;
}


Knoop* arrayToList(Knoop list[]){
	int i;
	Knoop* beginPointer = NULL;

	for(i = 0; i < ARRAYSIZE; i++){
		addSorted(&beginPointer, list[i].string);
	}

	return beginPointer;
}
void readNew(Knoop** list){
	char tempString[256];
	char* tempPointer = NULL;

	printf("Geef een string in met minder dan 255 letters.\n");
	fgets(tempString, 255, stdin);

	if(tempString[strlen(tempString) - 1] == '\n')
		tempString[strlen(tempString) - 1] = '\0';

	tempPointer = (char*) malloc(strlen(tempString) + 1);
	if(tempPointer == NULL) {
		printf("Error: Geen geheugen beschikbaar.\n");
	}
	else {
		strcpy(tempPointer, tempString);
		addSorted(list, tempPointer);
	}
	return;
}
void addNew(Knoop** list, char* stringPointer){
	Knoop* structPointer = (Knoop*) malloc(sizeof(Knoop));
	Knoop* pointer = *list;
	structPointer->string = stringPointer;
	structPointer->next = NULL;

	if(*list == NULL) {
		*list = structPointer;
		(*list)->previous = NULL;
	}
	else {
		while(pointer->next != NULL) {
			pointer = pointer->next;
		}
		pointer->next = structPointer;
		structPointer->previous = pointer;
	}

	return;
}

void addSorted(Knoop** list, char* stringPointer) {
	Knoop* structPointer = (Knoop*) malloc(sizeof(Knoop));
	Knoop* pointer = *list;
	structPointer->string = stringPointer;
	structPointer->next = NULL;
	structPointer->previous = NULL;

	if(*list == NULL) {
		*list = structPointer;
	}
	else {
		while(pointer->next != NULL && compareStrings(pointer->string, structPointer->string) == 0) {
			pointer = pointer->next;
		}
		//We zitten op het einde in dit geval
		if(compareStrings(pointer->string, structPointer->string) == 0) {
			pointer->next = structPointer;
			structPointer->previous = pointer;
		}
		else {
			structPointer->next = pointer;
			structPointer->previous = pointer->previous;
			if(pointer->previous != NULL) {
				pointer->previous->next = structPointer;
			}
			else {
				*list = structPointer;
			}
			pointer->previous = structPointer;
		}
	}

}

void printList(Knoop* pointer){
	if(pointer == NULL) {
		printf("Lege lijst -> kan niets printen\n");
		return;
	}
	printf("\n|=======================================|\n");
	while(pointer != NULL) {
		printf("String: %s\n", pointer->string);
		pointer = pointer->next;
	}
	printf("|=======================================|\n");

	return;
}
void deleteElement(Knoop** startPointer, Knoop* pointer){
	if(*startPointer == NULL) {
		printf("Lege lijst kan niets verwijderen.\n");
		return;
	}
	if(pointer == NULL) {
		printf("NULL pointer \n");
		return;
	}

	if(pointer->previous == NULL) {
		*startPointer = pointer->next;
		(*startPointer)->previous = NULL;
	}
	else {
		pointer->previous->next = pointer->next;
		if(pointer->next != NULL)
			pointer->next->previous = pointer->previous;
	}

	free(pointer->string);
	free(pointer);

	return;
}
void removeDouble(Knoop** startPointer){
	Knoop* tempPointer = (*startPointer)->next;

	while(tempPointer != NULL) {
		if(strcmp(tempPointer->string, tempPointer->previous->string) == 0) {
			if(tempPointer->next != NULL) {
				tempPointer = tempPointer->next;
				deleteElement(startPointer, tempPointer->previous);
			}
			else {
				deleteElement(startPointer, tempPointer);
				tempPointer = NULL;
			}
		}
		else {
			tempPointer = tempPointer->next;
		}
	}

	return;
}

void clearList(Knoop** startPointer) {
	Knoop* pointer = (*startPointer)->next;

	*startPointer = NULL;

	while(pointer != NULL && pointer->next != NULL) {
		free(pointer->previous->string);
		free(pointer->previous);
		pointer = pointer->next;
	}

	free(pointer->previous->string);
	free(pointer->previous);
	free(pointer->string);
	free(pointer);

	return;
}

int compareStrings(char const stringLeft[], char const stringRight[]) {
	int outcome = -1;
	int i;
	int lengthLeft = strlen(stringLeft); 
	int lengthRight = strlen(stringRight);


	for(i = 0; i < lengthLeft && i < lengthRight && outcome == -1; i++) {
		if(stringLeft[i] < stringRight[i])
			outcome = 0;
		else if(stringRight[i] < stringLeft[i])
			outcome = 1;
	}

	if(outcome == -1) {
		if(lengthLeft < lengthRight)
			outcome = 0;
		else
			outcome = 1;
	}

	return outcome;
}