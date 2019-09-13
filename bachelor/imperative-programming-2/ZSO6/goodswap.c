#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void goodswap(int **p1, int **p2);

int main(void) {
	int a = 3;
	int b = 5;
	int *ap = &a;
	int *bp = &b;


	goodswap(&ap, &bp);
	printf("a: %d, b: %d\n", *ap, *bp);

	return 0;
}

void goodswap(int **p1, int **p2) {
	int *tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}