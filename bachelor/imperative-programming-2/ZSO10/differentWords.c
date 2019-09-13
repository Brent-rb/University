#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int isDouble(char**, int, char*);
char** makeNoDouble(char[][32], char**, int*);

#define arraySize 5

int main(int argc, char const *argv[])
{
	char array[arraySize][32] = {"dit", "kaka", "stom", "stome", "dite"};
	char** dynamic = NULL;
	int i, temp;
	temp = 0;
	int* amountOfWords;
	amountOfWords = &temp;
	
	dynamic = makeNoDouble(array, dynamic, amountOfWords);

	for(i = 0; i < *amountOfWords; i++) {
		printf("%s\n", dynamic[i]);
		free(dynamic[i]);
	}

	free(dynamic);




	return 0;
}

char** makeNoDouble(char array[][32], char** dynamic, int* amount) {
	int i = 0;
	char** temp;

	for(i = 0; i < arraySize; i++) {
		if(dynamic == NULL) {
			dynamic = (char**) malloc(sizeof(char*));
			dynamic[*amount] = (char*) malloc(strlen(array[i]) + 1);
			strcpy(dynamic[*amount], array[i]);
			*amount += 1;
		}
		else {
			if(isDouble(dynamic, *amount, array[i]) == 0) {
				temp = (char**) realloc(dynamic, (sizeof(char*) * (*amount + 1)));
				if(temp == NULL) {
					printf("Geen geheugen beschikbaar.\n");
					break;
				}
				else {
					dynamic = temp;
					dynamic[*amount] = (char*) malloc(strlen(array[i]) + 1);
					strcpy(dynamic[*amount], array[i]);
					*amount += 1;
				}
			}
		}
	}

	return dynamic;

}

int isDouble(char** dynamic, int length, char* search) {
	int i;
	int found = 0;

	for(i = 0; i < length & found == 0; i++) {
		if(strcmp(dynamic[i], search) == 0)
			found = 1;
	}

	return found;
}