#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

void genFile(void);
void binToText(char*);
void textToBin(char*);
char hexToChar(char*);

#define bufferSize 1024

int main(int argc, char const *argv[])
{
	genFile();
	textToBin("TextInput.txt");
	binToText("BinText.txt");
	return 0;
}

void genFile(void) {
	FILE* openFile;

	openFile = fopen("BinText.txt", "wb");
	if(openFile == NULL) {
		printf("Failed to generate file\n");
		return;
	}

	int i = 'a';

	while(i < 'z') {
		fprintf(openFile,"%3x", i);
		i++;
	}

	fclose(openFile);

	return;
}

void binToText(char* input) {
	FILE* openFile;
	FILE *outputFile;
	char buffer[bufferSize];
	char *tokens = " ";
	char tokString[bufferSize];
	char *tokPointer;
	int endOfFile;
	int wordCounter = 0;
	char tempString[10];
	

	openFile = fopen(input, "rb");
	outputFile = fopen("TextOutput.txt", "w");
	if(openFile == NULL || outputFile == NULL) {
		printf("Errortje\n");
	}

	while (fgets(buffer, bufferSize - 1, openFile)) {
		strcpy(tokString, buffer);
		tokPointer = strtok(tokString, tokens);
		while (tokPointer != NULL) {
			wordCounter++;
			strcpy(tempString, tokPointer);
			if(hexToChar(tempString) != 152);
				fprintf(outputFile, "%c", hexToChar(tempString));
			tokPointer = strtok(NULL, tokens);

		}
	}


	fclose(openFile);
	fclose(outputFile);
}
void textToBin(char* input) {
	FILE* inputFile;
	FILE* outputFile;
	char c;
	int number;

	inputFile = fopen(input, "r");
	outputFile = fopen("BinText.txt", "wb");
	if(inputFile == NULL || outputFile == NULL) {
		printf("Error!\n");
		return;
	}

	while(!feof(inputFile)) {
		c = getc(inputFile);
		fprintf(outputFile, "%3x", c);
	}

	fclose(inputFile);
	fclose(outputFile);
}

char hexToChar(char *woord) {
	char outCome;

	int binary = 1;
	int i;
	int temp;
	int number = 0;
	int talstelsel = 16;

	for(i = strlen(woord) - 1; i >= 0; i--) {
		if(woord[i] <= 'f' && woord[i] >= 'a') {
			temp = woord[i] - 'a' + 10;
		}
		else if(woord[i] <= 'F' && woord[i] >= 'a') {
			temp = woord[i] - 'A' + 10;
		}
		else {
			temp = woord[i] - '0';
		}
		number += (binary * temp);
		binary *= talstelsel;
	}


	outCome = (char) number;

	return outCome;

}
