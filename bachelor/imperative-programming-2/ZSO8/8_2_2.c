//Decimaal naar binair recursief

#include <stdio.h>

void getAnswer();
void getBin();

int main() {
	getAnswer();
	return 0;
}

void getAnswer() {
	int input = 0;

	printf("Geef een getal in: ");
	scanf_s("%d", &input);
	getBin(input);
	printf("\n");
	return;
}

void getBin(int input) {
	if (input == 1) {
		printf("1");
		return;
	}

	if (input % 2 == 0){
		getBin(input / 2);
		printf("0");
	}
	else {
		getBin(input / 2);
		printf("1");
	}
}