#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define STUDENTENSIZE 20
typedef enum Score {SLECHT, MATIG, NEUTRAAL, GOED, UITSTEKEND} Score;

typedef struct Stem {
	int studentennummer;
	Score oordeel;
} Stem;

typedef struct StemmenPerScore {
	int aantal; 
	Stem stemmen[STUDENTENSIZE];
} StemmenPerScore;


void fillStudents(Stem*, int);
int isValid(char []);
void groepeer(Stem[], StemmenPerScore[]);
void writeTable(StemmenPerScore[]);

int main(int argc, char const *argv[])
{
	StemmenPerScore stats[5];
	Stem stemmen[STUDENTENSIZE];
	fillStudents(stemmen, STUDENTENSIZE);
	groepeer(stemmen, stats);
	writeTable(stats);

	return 0;
}

void fillStudents(Stem *studentArray, int endPoint) {
	int i;
	char temp[11];
	int tempNumber;

	for(i = 0; i < endPoint; i++) {
		printf("Geef je studentennummer in en stem: ");
		scanf("%d %s", &tempNumber, temp);
		studentArray[i].studentennummer = tempNumber;
		while (isValid(temp) == -1) {
			printf("Ongeldigge stem, voer opnieuw in: ");
			scanf("%s", temp);
		}
		studentArray[i].oordeel = isValid(temp);
	}

}

void groepeer(Stem stemmen[], StemmenPerScore stats[]){
	int i, j;

	for(i = SLECHT; i <= UITSTEKEND; i++) {
		stats[i].aantal = 0;
		for(j = 0; j < STUDENTENSIZE; j++) {
			if(stemmen[j].oordeel == i) {
				stats[i].stemmen[stats[i].aantal] = stemmen[j];
				stats[i].aantal++;
			}
		}
	}
}

void writeTable(StemmenPerScore stats[]) {
	int i, j;
	char temp[11] = "";

	for(i = SLECHT; i <= UITSTEKEND; i++) {
		if (i == SLECHT)
			strcpy(temp, "slecht");
		else if (i == MATIG)
			strcpy(temp, "matig");
		else if (i == NEUTRAAL)
			strcpy(temp, "neutraal");
		else if (i == GOED)
			strcpy(temp, "goed");
		else if (i == UITSTEKEND)
			strcpy(temp, "uitstekend");
		printf("%s", temp);
		for(j = 0; j < 11 - strlen(temp); j++)
			printf(" ");
		for(j = 0; j < stats[i].aantal; j++) 
			printf("*");
		printf("\n");
	}
}

int isValid(char word[]) {
	if(strlen(word) >= 11)
		return -1;
	if (strcmp(word, "slecht") == 0)
		return SLECHT;
	else if (strcmp(word, "matig") == 0)
		return MATIG;
	else if (strcmp(word, "neutraal") == 0)
		return NEUTRAAL;
	else if (strcmp(word, "goed") == 0)
		return GOED;
	else if (strcmp(word, "uitstekend") == 0)
		return UITSTEKEND;
	else
		return -1;
}