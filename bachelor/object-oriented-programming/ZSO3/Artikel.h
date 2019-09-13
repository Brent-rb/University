#ifndef ARTIKEL_H
#define ARTIKEL_H

#include <string>

using namespace std;

class Artikel {
public:
	Artikel();
	Artikel(string title, int price);
	Artikel(Artikel &artikel);
	void SetTitle(string title);
	void SetPrice(int price);
	int GetPrice();
	string GetTitle();
	void PrintArtikel();
private:
	string title;
	int price;
};

#endif