#ifndef BOEK_H
#define BOEK_H

#include "Artikel.h"
#include <string>
using namespace std;

class Boek: public Artikel {
public:
	Boek(): auteur(""), isbn(""){};
	Boek(string title, int price, string auteur, string isbn): Artikel(title, price), auteur(auteur), isbn(isbn){};
	Boek(Boek &boek): Artikel(boek.GetTitle(), boek.GetPrice()), auteur(boek.GetAuteur()), isbn(boek.GetIsbn()){};
	void SetAuteur(string auteur) {this->auteur = auteur;}
	void SetIsbn(string isbn) {this->isbn = isbn;}
	string GetIsbn() {return this->isbn;}
	string GetAuteur() {return this->auteur;}
	void PrintBoek();
	void Toon();
private:
	string auteur;
	string isbn;
	
};


#endif
