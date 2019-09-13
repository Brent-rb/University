#include <stdio.h>
#include <string.h>
#include <ctype.h>

void printString(char c[]);

int main() {
	char c[7] = "string";
	printString(c);

}

void printString(char c[]) {
	size_t length = strlen(c);
	int i;

	for(i = 0; i < length; i++) {
		printf("%c", c[i]);
	}

	printf("\n");
}