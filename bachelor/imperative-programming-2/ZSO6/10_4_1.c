#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* backWards(char *);

int main(void) {
	char string[] = "wij hebben swag\n";
	char *pointer = string;
	pointer = backWards(pointer);
	printf("%s", string);

	return 0;
}

char* backWards(char *string) {
	int i;
	char temp;
	int length = strlen(string);

	for(i = 0; i < length / 2; i++) {
		temp = *(string + i);
		*(string + i) = *(string + (length - (i + 2)));
		*(string + (length - (i + 2))) = temp;
	}

	return string;
}