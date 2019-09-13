#include <stdio.H>

#define MIN(x,y) ((x) < (y) ? (x) : (y))
#define ABS(x) ((x) >= (0) ? (x) : ((x) * (-1)))

int main() {
	for (int i = -5; i <= 5; i++) {
		printf("%d\n", ABS(i));

	}
	return 0;
}