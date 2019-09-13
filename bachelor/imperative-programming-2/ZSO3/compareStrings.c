#include <stdio.h>
#include <string.h>
#include <ctype.h>

int vergelijkString(char[], char[]);
void toLowerCase(char[]);


int main() {
	char string1[] = {'D', 'e', 'r', 'p', '\0'};
	char string2[] = {'d', 'e', 'r', 'p', 'a', '\0'};

	int amountDifferent = vergelijkString(string1, string2);
	printf("Het aantal verschillende letters is: %d\n", amountDifferent);

	return 0;
}

int vergelijkString(char string1[], char string2[]) {
	toLowerCase(string1);
	toLowerCase(string2);
	int amountDifferent = strlen(string1) - strlen(string2);
	if(amountDifferent < 0)
		amountDifferent *= -1;
	for(int i = 0; i < strlen(string1) && i < strlen(string2); i++) {
		if(string1[i] != string2[i])
			amountDifferent++;
	}

	return amountDifferent;
}

void toLowerCase(char c[]) {
	for(int i = 0; i < strlen(c); i++){
		c[i] = tolower(c[i]);
	}
}