#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define bufferSize 1024

int main(int argc, char const *argv[])
{
	char list[32][15] = {"auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","if","int","long","register","return","short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void","volatile","while"};
	int amount[32];
	FILE *inputFile;
	int i;
	char buffer[bufferSize];
	char *tokens = "., !?;\r\n";
	char *tokPointer;
	char tokString[bufferSize];
	int wordCounter = 0;
	
	for(i = 0; i < 32; i++) {
		amount[i] = 0;
	}

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
			for(i = 0; i < 32; i++) {
				if(strcmp(list[i], tokPointer) == 0) {
					amount[i]++;
				}
			}
			tokPointer = strtok(NULL, tokens);
		}
	}

	for(i = 0; i < 32; i++) {
		printf("Keyword: %s komt %d keer voor.\n", list[i], amount[i]);
	}

	fclose(inputFile);

	return 0;
}