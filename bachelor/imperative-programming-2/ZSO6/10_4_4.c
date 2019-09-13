#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	char string[255];

	fgets(string, 254, stdin);

	int wordCounter = 0;
	char* tempPointer = strtok(string, " .,");
	printf("%s\n", tempPointer);
	while(tempPointer != NULL) {
		printf("%s\n", tempPointer);
		tempPointer = strtok(NULL, " .,");
		
		wordCounter++;
	}
	printf("\n %d \n", wordCounter);
	return 0;
}