#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void cat(char*, char*);

int main(void) {
	char string1[255] = "wij hebben";
	char string2[255] = " swag\n";
	char *pointer1 = string1;
	char *pointer2 = string2;
	cat(pointer1, pointer2);

	printf("%s", string1);

	return 0;
}

void cat(char *pointer1, char *pointer2) {
	int length1, length2;
	int i;

	for(length1 = 0; *(pointer1 + length1) != '\0'; length1++) {

	}

	for(length2 = 0; *(pointer2 + length2) != '\0'; length2++) {

	}

	for(i = length1; i < length1 + length2; i++) {
		*(pointer1 + i) = *(pointer2 + (i - length1));
	}

	return;
}