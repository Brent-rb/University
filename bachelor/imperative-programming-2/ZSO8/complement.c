#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

unsigned char writeComplement(unsigned char);

int main(void) {
	unsigned char c = 0b10011001;
	c = writeComplement(c);
	printf("%0x\n", c);
	return 0;
}

unsigned char writeComplement(unsigned char c) {
	c = ~c;
	return c;
}