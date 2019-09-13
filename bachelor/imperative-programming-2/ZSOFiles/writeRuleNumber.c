#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define bufferSize 1024
#define fileName "testfile.txt\0"

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
	
	inputFile = fopen(fileName, "r");
	if (inputFile == NULL) {
		error("Unable to open file.");
	}

	outputFile = fopen("RuledFile.txt", "w");
	if (outputFile == NULL) {
		error("Failed to create file");
	}



	while (fgets(buffer, bufferSize - 1, inputFile)) {
		wordCounter++;
		printf("Line[%d]: %s", wordCounter, buffer);
		fprintf(outputFile, "%d %s", wordCounter, buffer);
	}

	fclose(inputFile);
	fclose(outputFile);


	return 0;
}