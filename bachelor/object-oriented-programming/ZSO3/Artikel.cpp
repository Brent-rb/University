#include "Artikel.h"
#include <iostream>


/*int main(int argc, char const *argv[])
{
	Artikel artikel("Brent", 500000);
	artikel.PrintArtikel();
	Artikel artikel2(artikel);
	artikel2.PrintArtikel();
	Artikel artikel3;
	artikel3.SetTitle("Matthijs");
	artikel3.SetPrice(1);
	artikel3.PrintArtikel();
	return 0;
}*/

Artikel::Artikel(): title(""), price(0) {

}

Artikel::Artikel(string title, int price): title(title), price(price) {

}

Artikel::Artikel(Artikel &artikel): title(artikel.GetTitle()), price(artikel.GetPrice()) {

}

void Artikel::SetTitle(string title) {
	this->title = title;
}

void Artikel::SetPrice(int price) {
	this->price = price;
}

int Artikel::GetPrice() {
	return this->price;
}

string Artikel::GetTitle() {
	return this->title;
}

void Artikel::PrintArtikel() {
	cout << "Naam:\t" << this->title << "\n";
	cout << "Prijs:\t" << this->price << "\n";
}
