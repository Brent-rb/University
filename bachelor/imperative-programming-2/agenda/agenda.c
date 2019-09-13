#include "afspraak.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>



int main(int argc, char const *argv[])
{
	test();
	return 0;
}

int test() {
	struct Afspraak* list[5];
	int i;

	for(i = 0; i < 5; i++) {
		readAfspraak(&list[i]);
	}

	for(i = 0; i < 5; i++) {
		writeAfspraak(list[i]);
		freeAfspraak(&list[i]);
	}
}