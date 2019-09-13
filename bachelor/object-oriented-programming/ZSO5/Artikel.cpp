#include "Artikel.h"
#include <iostream>
#include <fstream>
#include <string>



int main(int argc, char const *argv[])
{
	ifstream file("testFile.txt");
	Artikel artikel;
	artikel.fReadArtikel(file);
	artikel.PrintArtikel();
	artikel.fReadArtikel(file);
	artikel.PrintArtikel();
	artikel.fReadArtikel(file);
	artikel.PrintArtikel();
	artikel.fReadArtikel(file);
	artikel.PrintArtikel();
	return 0;
}

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

void Artikel::fPrintArtikel(const char* fileName) {
	ofstream file(fileName, ios::app);
	if(file.is_open()) {
		file << "Naam:\t" << this->title << "\n";
		file << "Prijs:\t" << this->price << "\n";
		file.close();
	}
	else 
		cout << "Could not open file: " << fileName << "\n";
}

void Artikel::fReadArtikel(ifstream & file) {
	string buffer;
	if(file.is_open()) {
		if(getline(file, buffer)) {
			this->title = buffer.substr(6);
			if(getline(file, buffer)) {
				buffer = buffer.substr(7);
				this->price = strToI(buffer);
			}
			else {
				cout << "Could not read price, aborting.\n";
				this->title = "";
				return;
			}
		}
		else {
			cout << "Could not read title, aborting.\n";
			return;
		}
	}
}

int Artikel::strToI(string str) {
	int length = str.length();
	length--;
	int number = 0, mul = 0;

	for(int i = 0; i <= length; i++) {
		mul = str[length - i] - '0';
		for(int j = 0; j < i; j++) {
			mul *= 10;
		}
		number += mul;
	}

	return number;
}

void Artikel::Toon() {
	cout << "Artikel:\n\tNaam:\t" << this->title << "\n\tPrijs:\t" << this->price << "\n";
}
