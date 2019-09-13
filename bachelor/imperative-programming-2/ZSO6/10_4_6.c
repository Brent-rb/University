#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void replaceChars(char []);

int main(void) {
	char string[255];

	fgets(string, 254, stdin);

	replaceChars(string);

	printf("%s", string);


	return 0;
}

void replaceChars(char string[]) {
	char prevChar = string[0];

	int i;

	for(i = 1; i < strlen(string); i++) {
		if(string[i] == prevChar)
			string[i] = '+';
		else
			prevChar = string[i];
	}

	return;
}
int main(int argc, char const *argv[])
{
	/* code *
	return 0;
}