#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


int main(int argc, char const *argv[])
{
	char* testConcat;
	char* concat = NULL;
	char temp[255];

	do {
		printf("Geef een string in: \n");
		fgets(temp, 254, stdin);
		if(temp[strlen(temp) - 1] == '\n') {
			temp[strlen(temp) - 1] = '\0';
		}
		if(strcmp(temp, "stop") == 0) {
			break;
		}
		if(concat == NULL) {
			concat = (char*) malloc(strlen(temp) + 1);
			strcpy(concat, temp);
			printf("%s \n", concat);
		}
		else {
			testConcat = (char*) realloc(concat ,(strlen(concat) + strlen(temp) + 1) * sizeof(char));
			if(testConcat == NULL) {
				printf("Er is geen geheugen meer vrij. \n");
				break;
			}
			else {
				concat = testConcat;
				strcpy((concat + strlen(concat)), temp);
				printf("%s\n", concat);
			}
		}

	} while(strcmp(temp, "stop") != 0);

	free(concat);
	concat = NULL;
	testConcat = NULL;

	return 0;
}

/*
Beter de concat initialiseren op 1 char --> \0