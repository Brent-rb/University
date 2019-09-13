#include <stdio.H>

void getAnswer();

int main() {
	getAnswer();
	return 0;
}

void getAnswer() {
	char c = 'a', prevChar = ' ';
	int charCount = 0, wordCount = 0;

	while (c != '\n') {
		c = getchar();
		charCount++;
		if ((c == ' ' || c == '\t' || c == '\n') && (prevChar != ' ' && prevChar != '\t' && prevChar != '\n'))
			wordCount++;
		prevChar = c;
	}

	printf("De ingegeven zin bevatte %d karakters en %d woorden \n", charCount, wordCount);
	return;
}