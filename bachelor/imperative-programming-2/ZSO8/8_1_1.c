#include <stdio.h>

double getAnswer();
int getFac();
double getPow();

int main() {
	double i;

	for (i = 0.1; i <= 1.0; i = i + 0.1){
		printf("Voor de waarde %0.1f is de uitkomst: %f \n", i, getAnswer(i));

	}

	return 0;
}

double getAnswer(double x) {
	double total = 0.0f; 
	int n;

	for (n = 0; n <= 10; n++) {
		total += getPow(x, n) / getFac(n);

	}

	return(total);
}

double getPow(double x, int n) {
	double total = x;
	if (n == 0)
		return 0.0f;

	for (int i = 1; i < n; i++) {
		total *= x;

	}

	return total;
}

int getFac(int n) {
	int total = n;
	if (n == 0)
		return 1;

	for (int i = n - 1; i > 0; i--){
		total *= i;

	}

	return total;
}


