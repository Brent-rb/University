#include <iostream>
#include "Boek.h"

/*int main(int argc, char const *argv[])
{
	Boek boek("Matthijs en de 7 Axel's.", 10, "Matthijs Kaminski", "154D56D65D4D");
	boek.PrintBoek();
	return 0;
}*/

void Boek::PrintBoek() {
	PrintArtikel();
	cout << "Auteur: " << auteur << "\n";
	cout << "ISBN:\t" << isbn << "\n";
}

void Boek::Toon() {
	cout << "Boek:\n\tNaam:\t" << this->title << "\n\tPrijs:\t" << this->price << "\n\tAuteur: " << auteur << "\n\tISBN:\t" << isbn << "\n";
}