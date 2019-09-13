#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

struct stringStruct {
	char string[32];
	int amount;
};

int removeDoubles(char [][32], struct stringStruct[]);
void printstruct(struct stringStruct[], int);

int main(void) {
	int k;
	char strings[10][32] = {"dit", "is", "zo", "een", "stomme", "oefening", "dit", "dit", "is", "stomme"};
	struct stringStruct nodoubles[10];
	k = removeDoubles(strings, nodoubles);
	printstruct(nodoubles, k);


	return 0;
}

int removeDoubles(char strings[][32], struct stringStruct stringStruct[]) {
	int i, j, k = 0, found = -1;
	char tempString[32];

	for(i = 0; i < 10; i++) {
		strcpy(tempString, strings[i]);
		found = -1;
		for(j = 0; j < k && found == -1; j++) {
			if(strcmp(stringStruct[j].string, tempString) == 0) {
				found = 1;
			}
		}
		if(found == 1) {
			stringStruct[j - 1].amount++;
		}
		else {
			strcpy(stringStruct[k].string, tempString); 
			stringStruct[k].amount = 1;
			k++;
		}
	}
	return k;
}

void printstruct(struct stringStruct stringStruct[], int k) {
	int i;
	for(i = 0; i < k; i++) {
		printf("De string: %s, komt %d keer voor.\n", stringStruct[i].string, stringStruct[i].amount);
	}
}