#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

unsigned char leftShift(unsigned char);
unsigned char rightShift(unsigned char);
unsigned char shift(unsigned char, int);

int main(int argc, char const *argv[])
{
	int x = -4;
	unsigned char c = 0b10011001;
	printf("%0x ", c);
	c = shift(c , x);
	printf("%0x\n", c);
	return 0;
}

unsigned char shift(unsigned char c, int x) {
	int i;

	if(x > 0) {
		for(i = 0; i < x; i++) {
			c = leftShift(c);
		}
	}
	else if(x < 0) {
		for(i = 0; i > x; i--) {
			c = rightShift(c);
		}
	}

	return c;
}

unsigned char leftShift(unsigned char c) {
	unsigned char andMask = 0b10000000;
	unsigned char orMask = 0b00000001;

	if((andMask & c) == andMask) {
		c <<= 1;
		c = c | orMask;
	}
	else
		c <<= 1;

	return c;
}

unsigned char rightShift(unsigned char c) {
	unsigned char orMask = 0b10000000;
	unsigned char andMask = 0b00000001;

	if((andMask & c) == andMask) {
		c >>= 1;
		c = c | orMask;
	}
	else
		c >>= 1;

	return c;
}