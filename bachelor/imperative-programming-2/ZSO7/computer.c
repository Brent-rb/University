#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


struct persoon {
	char voornaam[32];
	char naam[32];
};

struct computer {
	int hdd;
	struct persoon eigenaar; 
};

void read(struct computer*);
void print(struct computer*);

int main(void) {
	struct computer pc1;
	struct computer pc2;
	
	read(&pc1);
	read(&pc2);

	print(&pc1);
	print(&pc2);


	return 0;
}

void read(struct computer* pc) {
	printf("Geef de hdd grootte in in GB: ");
	scanf(" %d", &pc->hdd);
	printf("Geef de naam in van de eigenaar(voornaam, naam): ");
	scanf(" %s , %s", pc->eigenaar.voornaam, pc->eigenaar.naam);
}

void print(struct computer* pc) {
	printf("Hdd: %dGB, Voornaam: %s, Naam: %s \n", pc->hdd, pc->eigenaar.voornaam, pc->eigenaar.naam);
}