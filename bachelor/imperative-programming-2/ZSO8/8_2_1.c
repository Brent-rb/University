//Maak een power(x, n) die x^n berekent

#include <stdio.h>

void getAnswer();
int power();

int main() {
	getAnswer();
	return 0;
}

void getAnswer() {
	int x = 0;
	int n = 0;
	printf("Geef x en n in gescheiden door een spatie (vb: 5 2): ");
	scanf_s("%d %d", &x, &n);
	printf("%d^%d = %d\n",x, n, power(x, n));
	return;
}

int power(int x, int n) {
	int total;
	if (n == 0)
		return 1;
	total = x * power(x, n - 1);

	return total;
}