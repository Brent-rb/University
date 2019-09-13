/*
Besturingssystemen: opdracht 1
Academiejaar 2013-2014

Naam: Berghmans Brent
Nr: 1334252
*/

/* 
Lees aandachtig de commentaar in de code! 

Je mag overal waar je dat nodig acht code aanvullen, 
dus niet enkel op de plaatsen waar commentaar staat.
*/


/**
NOTES

1--------------------------------------------------------------------
There's a possibility of starvation if the producer works very fast.
This is because the handlers do not get very much time to read before
the producer locks the mutexes for his next write.

I could solve this by denying access to the producer in Buffer until 
the handler have read the latest data.
But this would make the producer wait and that would not make sense
because of the context given in the assignment.
---------------------------------------------------------------------

2--------------------------------------------------------------------
This implementation should support multiple producers running at the 
same time. Though this is not that heavily tested.
---------------------------------------------------------------------

3--------------------------------------------------------------------
I prefer to write comments in English, if this is annoying let me know.
---------------------------------------------------------------------
**/


#include "buffer.h"
#include "producer.h"
#include "handler.h"
#include <iostream>
#include <fstream>

int main(int argc, char const* argv[]) {
	Buffer buff;
	srand(time(NULL));

	std::ofstream file1;
	std::ofstream file2;
	file1.open("file1.txt");
	file2.open("file2.txt");
	
	// open the files

	Producer p(buff, 0);
	//Producer p2(buff, 500);
	Handler h1(buff, std::cout);
	Handler h2(buff, file1);
	Handler h3(buff, file1);

	p.start();
	//p2.start();
	h1.start();
	h2.start();
	h3.start();

	p.wait();
	//p2.start();
	h1.wait();
	h2.wait();
	h3.wait();
	// wait until producers stopped producing and handlers handled all produced data

	return EXIT_SUCCESS;
}
