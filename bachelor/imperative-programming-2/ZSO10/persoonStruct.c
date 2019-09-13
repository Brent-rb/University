#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct persoon {
	char* naam;
	char* adres;
} persoon;


int main(int argc, char const *argv[])
{
	persoon* array = NULL;
	persoon* testArray;
	char* tempPointer;
	int i = 0;
	int j;
	int n = 0;
	char temp[255];
	
	do {
		n++;
		if(array == NULL) {
			array = malloc(sizeof(persoon));
		}
		else {
			testArray = realloc(array, sizeof(persoon) * n);
			if(testArray == NULL) {
				printf("Geen geheugen beschikbaar.\n");
				break;
			}
			else {
				array = testArray;
			}
		}


		printf("Geef de naam van de persoon in: ");
		fgets(temp, 254, stdin);
		if(temp[strlen(temp) - 1] == '\n') {
			temp[strlen(temp) - 1] = '\0';
		}

		tempPointer = (char*) malloc(strlen(temp) + 1);
		if(tempPointer == NULL) {
			printf("Geen geheugen gevonden.\n");
			break;
		}
		else {
			strcpy(tempPointer, temp);
			array[i].naam = tempPointer;
		}


		printf("Geef het adres van de persoon in: ");
		fgets(temp, 254, stdin);
		if(temp[strlen(temp) - 1] == '\n') {
			temp[strlen(temp) - 1] = '\0';
		}

		tempPointer = (char*) malloc(strlen(temp) + 1);
		if(tempPointer == NULL) {
			printf("Geen geheugen gevonden.\n");
			break;
		}
		else {
			strcpy(tempPointer, temp);
			array[i].adres = tempPointer;
		}



		printf("Geef nieuw in voor een nieuwe persoon of stop om te stoppen.\n");
		fgets(temp, 254, stdin);
		i++;
	} while(strcmp(temp, "stop\n") != 0);

	for(j = 0; j < i; j++) {
		printf("%s woont op %s\n", array[j].naam, array[j].adres);
		free(array[j].naam);
		free(array[j].adres);
		array[j].naam = NULL;
		array[j].adres = NULL;
	}
	free(array);

	array = NULL;
	testArray = NULL;
	return 0;
}