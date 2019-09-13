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
void printList(intList*);


int main(int argc, char const *argv[])
{
	intList* list = NULL;
	int i;

	for(i = 0; i < 10; i++) {
		srand(time(NULL));
		addInFront(&list, 0, rand() % 10);
	}

	printList(list);

	return 0;
}

void addInFront(intList** list, int location, int value) {
	intList* tempPointer = NULL;
	intList* prevPointer = NULL;
	intList* pointer = NULL;
	int i = 0;

	if(*list == NULL) {
		tempPointer = (intList*) malloc(sizeof(struct intList));
		if(tempPointer == NULL) {
			printf("Geen geheugen beschikbaar.\n");
			return;
		}
		else {
			*list = tempPointer;
			*list->number = value;
			*list->next = NULL;
		}
	}
	else {
		tempPointer = *list;
		while(i < value && tempPointer->next != NULL) {
			i++;
			prevPointer = tempPointer;
			tempPointer = prevPointer->next;
		}
		if(prevPointer->next == NULL) {
			prevPointer = (intList*) malloc(sizeof(struct intList));
			if(prevPointer == NULL) {
				printf("Geen geheugen beschikbaar.\n");
				return;
			}
			else {
				prevPointer->next = *list;
				prevPointer->number = value;
				*list = prevPointer;
			}
		}
		else {
			pointer = (intList*) malloc(sizeof(struct intList));
			if(pointer == NULL) {
				printf("Geen geheugen beschikbaar.\n");
				return;
			}
			else {
				pointer->next = tempPointer;
				pointer->number = value;
				prevPointer->next = pointer;
			}
		}
	}
}
void printList(intList* list) {
	intList* pointer = *list;

	while(pointer->next != NULL) {
		printf("Value: %d\n", pointer->number);
		pointer = pointer->next;
	}
}