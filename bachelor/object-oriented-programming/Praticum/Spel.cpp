#include "Spel.h"
#include <stdio.h>


void PrintUitleg();

int main(int argc, char const *argv[])
{
	int selection;

	printf("____________________________\nWelkom bij het beste schaakspel ooit.\n____________________________\n\n");

	do {
		printf("Selectie:\n\t[1] Spel beginnen.\n\t[2] Uitleg.\n\n");
		scanf("%d", &selection);
		if(selection == 2)
			PrintUitleg();
	} while(selection != 1);

	Spel spel;
	spel.Engine();
	return 0;
}


void PrintUitleg() {
	printf("\n\n\n1) Een pion wordt voorgesteld door de letter P.\n2) Een zwarte pion wordt aangegeven door 2 punten naast de letter bv: .P. is een zwarte pion.\n");
}

Spel::Spel() {
	int amount;
	do {
		printf("\nHoeveel pionnen wil je op het bord? (Kleiner of gelijk aan 16)\n");
		scanf("%d", &amount);
	} while(amount > 16);

	this->spelbord = new Spelbord();

	int i = 0, j = 0, k = 0;

	while(k < amount) {
		if(i == 8) {
			i = 0;
			j++;
		}

		spelbord->AddPion(j, i, ZWART);
		i++;
		k++;
	}

	i = 0; 
	j = 0; 
	k = 0;

	while(k < amount) {
		if(i == 8) {
			i = 0;
			j++;
		}
		spelbord->AddPion(7 - j, 7 - i, WIT);
		i++;
		k++;
	}
	
	spelbord->PrintBord();

	printf("\nLet the games begin!\n");
	
}

void Spel::Engine() {

}