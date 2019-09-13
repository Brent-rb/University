#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

struct ploeg {
	char naam[255];
	int gewonnenPunten;
	int gespeeld;
};

typedef struct ploeg ploeg;

struct date {
	int day;
	int month;
	int year;
};

typedef struct date date;

struct wedstrijd {
	ploeg ploeg1;
	ploeg ploeg2;
	int gewonnen;
	int teWinnenPunten;
	int gespeeld;
	date datum;
};

typedef struct wedstrijd wedstrijd;

void writeCalender(wedstrijd[], ploeg[]);
void rank(ploeg[]);
void sortCalender(wedstrijd[]);
void fillCalender(wedstrijd[], ploeg[]);

#define CALENDERSIZE 6
#define PLOEGENSIZE 4


int main(int argc, char const *argv[])
{	
	srand(time(NULL));
	
	int i;


	ploeg ploegen[PLOEGENSIZE];
	strcpy(ploegen[0].naam, "FC. De Doefkes");
	strcpy(ploegen[1].naam, "KRC. De Swaggers");
	strcpy(ploegen[2].naam, "Niggers United");
	strcpy(ploegen[3].naam, "The Yolo McSwaggings");

	for(i = 0; i < PLOEGENSIZE; i++) {
		int r = rand() % 100;
		int s = rand() % 6;
		ploegen[i].gewonnenPunten = r;
		ploegen[i].gespeeld = s;
	}

	wedstrijd wedstrijden[CALENDERSIZE];
	fillCalender(wedstrijden, ploegen);
	sortCalender(wedstrijden);
	writeCalender(wedstrijden, ploegen);
	return 0;
}

void fillCalender(wedstrijd match[], ploeg ploegen[]) {
	int i, j;
	char temp[255];
	int calenderI = 0;

	for(i = 0; i < PLOEGENSIZE; i++) {
		for(j = i + 1; j < PLOEGENSIZE; j++, calenderI++) {
			match[calenderI].ploeg1 = ploegen[i];
			match[calenderI].ploeg2 = ploegen[j];
			printf("Match: %s vs. %s.\n", match[calenderI].ploeg1.naam, match[calenderI].ploeg2.naam);
			printf("Geef de datum van deze match(dag maand jaar): ");
			scanf("%d %d %d", &match[calenderI].datum.day, &match[calenderI].datum.month, &match[calenderI].datum.year);
			printf("Geef het te winnen punten: ");
			scanf("%d", &match[calenderI].teWinnenPunten);
			printf("Is hij al gespeeld? 0 = nee, 1 = ja: ");
			scanf("%d", &match[calenderI].gespeeld);
			match[i].gewonnen = 0;
		}
	}
}

void rank(ploeg ploeg[]) {
	int i, j, place;
	struct ploeg temp;

	for(i = 0; i < PLOEGENSIZE; i++) {
		temp = ploeg[i];
		place = i;
		for(j = i + 1; j < PLOEGENSIZE; j++) {
			if(temp.gewonnenPunten > ploeg[j].gewonnenPunten) {
				temp = ploeg[j];
				place = j;
			}
			else if(temp.gewonnenPunten == ploeg[j].gewonnenPunten && temp.gespeeld > ploeg[j].gespeeld) {
				temp = ploeg[j];
				place = j;
			}
		}

		ploeg[place] = ploeg[i];
		ploeg[i] = temp;
	}
}
void sortCalender(wedstrijd westrijden[]) {
	int i, j;
	wedstrijd temp;
	int place;

	for(i = 0; i < CALENDERSIZE; i++) {
		temp = westrijden[i];
		place = i;
		for(j = i + 1; j < CALENDERSIZE; j++) {
			if (temp.datum.year > westrijden[j].datum.year) {
				temp = westrijden[j];
				place = j;
			}
			else if (temp.datum.month > westrijden[j].datum.month) {
				temp = westrijden[j];
				place = j;
			}
			else if (temp.datum.day > westrijden[j].datum.day) {
				temp = westrijden[j];
				place = j;
			}
		}
		westrijden[place] = westrijden[i];
		westrijden[i] = temp;
	}
}
void writeCalender(wedstrijd weststrijden[], ploeg ploegen[]) {
	int i;

	for(i = 0; i < CALENDERSIZE; i++) {
		printf("Match: %s vs. %s, te winnen punten: %d, op datum: %d/%d/%d is ", weststrijden[i].ploeg1.naam, weststrijden[i].ploeg2.naam, weststrijden[i].teWinnenPunten, weststrijden[i].datum.day, weststrijden[i].datum.month, weststrijden[i].datum.year);
		if(weststrijden[i].gespeeld == 0)
			printf("nog niet gespeeld.\n");
		else {
			printf("al gespeeld en");
			if(weststrijden[i].gewonnen == 0)
				printf(" %s hebben gewonnen.\n", weststrijden[i].ploeg1.naam);
			else
				printf(" %s hebben gewonnen.\n", weststrijden[i].ploeg2.naam);

		}

	}
}