#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

struct student {
	char naam[32];
	char voornaam[32];
	int studentnr;
	double punten[5];
	int jaar;
};
#define aantalStudenten 3
void readIn(struct student*);
void sortNr(struct student[]);
void printStudent(struct student*);
void addPoint(struct student[], int, double);


int main(void) {
	struct student studenten[aantalStudenten];
	int i;
	for(i = 0; i < aantalStudenten; i++) {
		readIn(&studenten[i]);
	}
	for(i = 0; i < aantalStudenten; i++) {
		printStudent(&studenten[i]);
	}
	sortNr(studenten);
	for(i = 0; i <aantalStudenten; i++){ 
		printStudent(&studenten[i]);
	}
	for(i = 0; i < aantalStudenten; i++) {
		printStudent(&studenten[i]);)
	}

	return 0;
}

void readIn(struct student* st) {
	int i;
	printf("Geef de voornaam en naam van de student(voornaam naam): ");
	scanf("%s %s", st->voornaam, st->naam);
	printf("Geef de studentennummer: ");
	scanf("%d", &st->studentnr);
	printf("Geef het jaar: ");
	scanf("%d", &st->jaar);
	for (i = 0; i < st->jaar; ++i)
	{
		printf("Geef het punten van het %d jaar: ", i);
		scanf("%lf", &st->punten[i]);
	}
}

void printStudent(struct student* st) {
	int i;
	printf("\nDe voornaam en naam van de student(voornaam naam): %s %s\n", st->voornaam, st->naam);
	printf("De studentennummer: %d\n", st->studentnr);
	printf("Het jaar: %d\n", st->jaar);
	for (i = 0; i < st->jaar; ++i)
	{
		printf("De punten van het %d jaar: %lf\n", i, st->punten[i]);
	}
}

void sortNr(struct student st[]) {
	int i, j, lowest;
	struct student temp;
	for(i = 0; i < aantalStudenten; i++) {
		temp = st[i];
		lowest = i;
		for(j = i; j < aantalStudenten; j++) {
			if(temp.studentnr > st[j].studentnr) {
				temp = st[j];
				lowest = j;
			}
		}
		st[lowest] = st[i];
		st[i] = temp;
	}
}

void addPoint(struct student studenten[], int studentNummer, double punt) {
	int realStudent = -1;
	int i;
	for(i = 0; i < aantalStudenten; i++) {
		if(studenten[i].studentnr == studentNummer)
			realStudent = i;
	}
	if(realStudent == -1) {
		printf("Ongeldigge stundentennummer ingegeven. \n");
	}
	else {
		if(studenten[realStudent].jaar >= 5) {
			printf("De student is al afgestudeerd.\n");
		}
		else {
			studenten[realStudent].punten[studenten[realStudent].jaar] = punt;
			studenten[realStudent].jaar++;
		}
	}
	
}