#include <stdio.h>
#include <string.h>

void cleanString(char[]);
void printString(char[]);
void strdelete(char str[], int n);

int main() {
	char c[] = {'N', 'i', 'g', 'g', 'a', ' ', '\t', 'd', 'o', ' ', ' ', 'y', 'o', 'u', ' ', 'e', 'v', 'e', 'n', ' ', 'l', 'i', 'f', 't', '?', '\0'};

	printString(c);
	cleanString(c);
	printString(c);

	return 0;
}

void cleanString(char c[]) {
	size_t length = strlen(c);
	int i = 0;

	while(i < strlen(c)) {
		if(c[i] == ' ' || c[i] == '\t' || c[i] == '\n') {
			strdelete(c, i);
		}
		else 
			i++;
	}
}

void printString(char c[]) {
	size_t length = strlen(c);
	int i;

	for(i = 0; i < length; i++) {
		printf("%c", c[i]);
	}

	printf("\n");
}

void strdelete(char str[], int n) {
	strcpy( &str[n], &str[n + 1]);
}
