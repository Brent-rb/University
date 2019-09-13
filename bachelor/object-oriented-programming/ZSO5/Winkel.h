#ifndef WINKEL_H
#define WINKEL_H
#include "Artikel.h"
#include "Boek.h"

class Winkel {
public:
	Winkel() {max = 0; articles = NULL;}
	~Winkel() {delete articles;}
	void virtual AddArticle(int place, Artikel* newArticle);
	void virtual AddArticle(Artikel* newArticle);
	void virtual DeleteArticle(int place);
	void DeleteLast();
	void PrintAll();
private:
	Artikel** articles;
	int max;
};


#endif