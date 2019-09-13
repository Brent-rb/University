#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkPalin(char*, char*);

int main(void) {
	char string[] = "lespel";
	char *pointerLeft = string;
	char *pointerRight = &string[strlen(string) - 1];
	int isPalin = checkPalin(pointerLeft, pointerRight);

	if(isPalin == 1)
		printf("%s is een palindroom.\n", string);
	else
		printf("%s is geen palindroom.\n", string);

	return 0;
}

int checkPalin(char* pointerLeft, char* pointerRight) {
	int result;
	if(pointerRight <= pointerLeft)
		return 1;
	if(*pointerLeft == *pointerRight)
		result = 1 * checkPalin(pointerLeft + 1, pointerRight - 1);
	else
		return 0;

	return result;
}