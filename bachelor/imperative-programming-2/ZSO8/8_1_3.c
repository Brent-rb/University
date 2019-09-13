#include <stdio.h>

void getAnswer();

int main() {
	getAnswer();

	return 0;
}

void getAnswer() {
	char c = '*', prevChar = ' ', longestChar = '*';
	int longestSeq = 0, currentSeq = 1;

	while (c != '\n') {
		c = getchar();
		if (c != ' ' && c != '\t' && prevChar == c)
			currentSeq++;
		else {
			if (currentSeq > longestSeq){
				longestSeq = currentSeq;
				longestChar = prevChar;
			}
			currentSeq = 1;
		}
		prevChar = c;
	}

	printf("De langste sequentie van %d was met letter %c\n", longestSeq, longestChar);
	return;
}