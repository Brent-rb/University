#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

typedef struct intList {
	int number;
	struct intList* next;
} intList;

void addInFront(intList** list, int location, int value);
void addBehind(intList** list, int location, int value);
void addList(intList** list, int mode, int search, int value);
intList* searchElement(intList* start, int value);
void deleteElement(intList** list, int mode, int value);
void deleteFirst(intList** list);
void deleteLast(intList** list);
void deleteValue(intList** list, int value);
void deletaAll(intList** list);
void printListRecursive(intList*);
void printListNormal(intList*);
void freeMemory(intList**);


int main(int argc, char const *argv[])
{
	intList* list = NULL;
	int i;

	for (i = 0; i < 1; i++) {
		addBehind(&list, i, i);
	}
	printListNormal(list);
	deleteElement(&list, 0, 5);
	printListNormal(list);
	deleteElement(&list, 2, 0);
	printListNormal(list);
	deleteElement(&list, 1, 0);
	printListNormal(list);
	deleteElement(&list, -1, 0);


	return 0;
}

void addList(intList** list, int mode, int search, int value) {
	int location = 0;
	intList* pointer = *list;
	if(*list == NULL) {
		printf("Lijst is leeg.\n");
		return;
	}

	while(pointer->next != NULL && pointer->number != search) {
		pointer = pointer->next;
		location++;
	}

	if(pointer->next == NULL && pointer->number != search) {
		printf("Waarde niet gevonden. Niets toegevoegd aan de lijst.\n");
		return;
	}

	if(mode == 0) {
		addInFront(list, location, value);
	}
	else if(mode == 1) {
		addBehind(list, location, value);
	}


}

void addInFront(intList** list, int location, int value) {
	intList* tempPointer = NULL;
	intList* prevPointer = NULL;
	intList* pointer = NULL;
	int i = 0;

	pointer = (intList*) malloc(sizeof(struct intList));
	if(pointer == NULL) {
		printf("Geen geheugen beschikbaar.\n");
		return;
	}

	if (*list == NULL) {
		*list = pointer;
		(*list)->number = value;
		(*list)->next = NULL;
	}
	else {
		tempPointer = *list;
		while (i < location && tempPointer->next != NULL) {
			i++;
			prevPointer = tempPointer;
			tempPointer = prevPointer->next;
		}
		if (prevPointer == NULL) {
			pointer->next = *list;
			pointer->number = value;
			*list = pointer;
		}
		else {
			pointer->next = tempPointer;
			pointer->number = value;
			prevPointer->next = pointer;
		}
	}
}

void addBehind(intList** list, int location, int value) {
	intList* tempPointer = NULL;
	intList* prevPointer = NULL;
	intList* pointer = NULL;
	int i = 0;

	pointer = (intList*) malloc(sizeof(intList));
	if (pointer == NULL) {
		printf("Geen geheugen beschikbaar.\n");
		return;
	}

	if(*list == NULL) {
		pointer->number = value;
		pointer->next = NULL;
		*list = pointer;
	}
	else {
		tempPointer = (*list)->next;
		prevPointer = *list;
		while(i <= location && prevPointer->next != NULL) {
			i++;
			prevPointer = tempPointer;
			tempPointer = prevPointer->next;
		}
		if(prevPointer->next == NULL) {
			pointer->number = value;
			pointer->next = NULL;
			prevPointer->next = pointer;
		}
		else {
			pointer->number = value;
			pointer->next = tempPointer;
			prevPointer->next = pointer;
		}
	}


}


void printListRecursive(intList* pointer) {
	if (pointer == NULL)
		return;
	printListRecursive(pointer->next);
	printf("Value: %d\n", pointer->number);
	return;
}

void printListNormal(intList* pointer) {
	if (pointer == NULL) 
		return;

	printf("\n|======| Begin List |======|\n");
	while(pointer != NULL) {
		printf("\t  Value: %d\n", pointer->number);
		pointer = pointer->next;
	}

	printf("|=======| End List |=======|\n");
}



void deleteAll(intList** list) {
	intList* pointer = *list;
	intList* prevPointer = NULL;

	if (pointer == NULL) {
		printf("Lege lijst, kan de lijst niet leegmaken.\n");
		return;
	}

	while (pointer != NULL) {
		prevPointer = pointer;
		pointer = pointer->next;
		free(prevPointer);
	}

	*list = NULL;
	printf("\nLijst succesvol leeg gemaakt.\n");
	return;
}

intList* searchElement(intList* start, int value) {
	//Geeft null terug als het element niet gevonden is.
	intList* pointer = start;

	while(pointer != NULL && pointer->number != value) {
		pointer = pointer->next;
	}

	return pointer;
}

void deleteElement(intList** list, int mode, int value) {
	if(*list == NULL) {
		printf("Lege lijst, hierin kunnen we niets verwijderen. Aborting.\n");
		return;
	}
	if(mode == 0)
		deleteValue(list, value);
	else if(mode == 1)
		deleteFirst(list);
	else if(mode == 2)
		deleteLast(list);
	else if(mode == -1)
		deleteAll(list);

}
void deleteFirst(intList** list) {
	intList* start = *list;
	*list = (*list)->next;

	free(start);
}
void deleteLast(intList** list) {
	intList* pointer = *list;
	intList* prevPointer = NULL;

	while(pointer->next != NULL) {
		prevPointer = pointer;
		pointer = pointer->next;
	}

	if(prevPointer != NULL)
		prevPointer->next = NULL;
	else 
		*list = NULL;

	free(pointer);

	printf("\nHet laatste element is succesvol verwijdert.\n");
}
void deleteValue(intList** list, int value) {
	intList* pointer = *list;
	intList* prevPointer = NULL;

	while(pointer != NULL && pointer->number != value) {
		prevPointer = pointer;
		pointer = pointer->next;
	}

	if(pointer == NULL) {
		printf("Te verwijderen element niet gevonden.\n");
		return;
	}

	if(prevPointer == NULL) {
		*list = (*list)->next;
	}
	else {
		prevPointer->next = pointer->next;
	} 

	free(pointer);	

	printf("\nVerwijderen van element met waarde %d succesvol voltooid.\n", value);
}