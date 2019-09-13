#include <stdio.h>

void incrementShort(short *pShort);

int main() {
	short shorty = 0;

	for(int i = 0; i < 30; i++) {
		printf("Shorty is: %d\n", shorty);
		incrementShort(&shorty);
	}

	return 0;

}

void incrementShort(short *pShort) {
	*pShort += 1;
}