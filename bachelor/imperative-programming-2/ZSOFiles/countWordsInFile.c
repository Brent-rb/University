#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define bufferSize 1024

int main(int argc, char const *argv[])
{
	FILE *inputFile;
	FILE *outputFile;
	char buffer[bufferSize];
	char *tokens = "., !?;\r\n";
	char tokString[bufferSize];
	char *tokPointer;
	int endOfFile;
	int wordCounter = 0;
	
	inputFile = fopen("testfile.txt", "r");
	if (inputFile == NULL) {
		error("Unable to open file.");
	}

	while (fgets(buffer, bufferSize - 1, inputFile)) {
		strcpy(tokString, buffer);
		tokPointer = strtok(tokString, tokens);
		while (tokPointer != NULL) {
			wordCounter++;
			printf("Woord[%d]: %s\n",wordCounter, tokPointer);
			tokPointer = strtok(NULL, tokens);
		}
	}

	printf("\nEr zaten %d woorden in dit bestand.\n", wordCounter);

	fclose(inputFile);

	return 0;
}