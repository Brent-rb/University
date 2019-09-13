#include "datum.h"
#include <stdio.h>
#include <string.h>

int readDate(struct Datum* dateStruct) {
	int tempDay = -1;
	int tempMonth = -1;
	int tempYear = -1;
	int i = 0;
	char temp[13];
	char* tokenizer = "/";
	char* tok;

	printf("Give the date: (dd/mm/yy): ");
	fgets(temp, 12, stdin);

	tok = strtok(temp, tokenizer); 
	while(tok != NULL) {
		if(i == 0)
			tempDay = atoi(tok);
		if(i == 1)
			tempMonth = atoi(tok);
		if(i == 2)
			tempYear = atoi(tok);
		tok = strtok(NULL, tokenizer);
		i++;
	}



	dateStruct->dag = tempDay;
	dateStruct->maand = tempMonth;
	dateStruct->jaar = tempYear;

	return 1;	
}

int writeDate(struct Datum* const dateStruct) {
	char* month;
	if(dateStruct->maand == 1)
		month = "Januari";
	else if(dateStruct->maand == 2) 
		month = "Februari";
	else if(dateStruct->maand == 3)
		month = "Maart";
	else if(dateStruct->maand == 4)
		month = "April";
	else if(dateStruct->maand == 5)
		month = "Mei";
	else if(dateStruct->maand == 6)
		month = "Juni";
	else if(dateStruct->maand == 7) 
		month = "Juli";
	else if(dateStruct->maand == 8)
		month = "Augustus";
	else if(dateStruct->maand == 9)
		month = "September";
	else if(dateStruct->maand == 10)
		month = "Oktober";
	else if(dateStruct->maand == 11)
		month = "November";
	else if(dateStruct->maand == 12)
		month = "December";

	printf("%d %s %d\n", dateStruct->dag, month, dateStruct->jaar);

	return 1;

}