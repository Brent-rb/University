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

typedef struct student student;
#define aantalStudenten 3
void readIn(struct student*);
void sortNr(struct student[]);
void printStudent(struct student*);
int lexographic(student*, student*);
int number(student, student);


int main(void) {
	struct student studenten1[aantalStudenten];
	int i;

	for(i = 0; i < aantalStudenten; i++) {
		readIn(studenten1[i]);
	}

	qsort(studenten1, aantalStudenten, sizeof(student), lexographic);

	for(i = 0; i < aantalStudenten; i++) {
		printStudent(studenten1[i]);
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
		printf("De punten van het %d jaar: %lf\n", i,
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

int lexographic(student* nr1 , student* nr2) {
	int i;
	int answer = 0;

	for(i = 0; i < strlen(nr1->naam) && i < strlen(nr2->naam); i++) {
		if(nr1->naam[i] < nr2->naam[i]) {
			answer = -1;
			break;
		}
		else if(nr2->naam[i] < nr1->naam[i]) {
			answer = i;
			break;
		}
	}
	if(answer == 0) {
		if(strlen(nr1->naam) < strlen(nr2->naam))
			answer = -1;
		else if(strlen(nr2->naam) < strlen(nr1->naam)) {
			answer = 1;
		}
	}

	return answer;
}

int number(student nr1, student nr2) {
	if(nr1.studentnr < nr2.studentnr)
		return -1;
	else
		return 1;
}


