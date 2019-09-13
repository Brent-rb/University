#include <stdio.h>
#include <string.h>

int getLastOccurance(char[], char);

int main() {
	char c[] = {'N', 'i', 'g', 'g', 'a', ' ', '\t', 'd', 'o', ' ', ' ', 'y', 'o', 'u', ' ', 'e', 'v', 'e', 'n', ' ', 'l', 'i', 'f', 't', '?', '\0'};

	int lastOccurance = getLastOccurance(c, 'l');

	printf("The numba is: %d", lastOccurance);

	return 0;
}

int getLastOccurance(char c[], char findLetter) {
	int location = -1;
	int i;

	for(i = 0; i < strlen(c); i++) {
		if(c[i] == findLetter)
			location = i;
	}

	return location;
}