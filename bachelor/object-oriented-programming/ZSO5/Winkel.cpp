#include <iostream>
#include "Winkel.h"
#include "AudioCD.h"
#include "Boek.h"

using namespace std;

int main(int argc, char const *argv[])
{
	/*Boek boek1("Matthijs en de 71 Axel's.", 10, "Matthijs Kaminski", "154D56D65D4D");
	Boek boek2("Matthijs en de 72 Axel's.", 10, "Matthijs Kaminski", "154D56D65D4D");
	Boek boek3("Matthijs en de 7 3Axel's.", 10, "Matthijs Kaminski", "154D56D65D4D");
	Boek boek4("Matthijs en de 7 A4xel's.", 10, "Matthijs Kaminski", "154D56D65D4D");
	Boek boek5("Matthijs en de 7 Ax5el's.", 10, "Matthijs Kaminski", "154D56D65D4D");
	AudioCD cd1("Brent en de 81 negers", 14, "Brent", 1);
	AudioCD cd2("Brent en de 8 2negers", 14, "Brent", 1);
	AudioCD cd3("Brent en de 8 n3egers", 14, "Brent", 1);
	AudioCD cd4("Brent en de 8 ne4gers", 14, "Brent", 1);
	AudioCD cd5("Brent en de 8 neg5ers", 14, "Brent", 1);
	Winkel winkel;

	winkel.AddArticle(0, &boek1);
	winkel.AddArticle(4, &boek2);
	winkel.AddArticle(4, &boek3);
	winkel.AddArticle(4, &boek4);
	winkel.AddArticle(4, &boek5);
	winkel.AddArticle(4, &cd1);
	winkel.AddArticle(4, &cd2);
	winkel.AddArticle(4, &cd3);
	winkel.AddArticle(4, &cd4);
	winkel.AddArticle(4, &cd5);
	winkel.DeleteArticle(4);

	winkel.PrintAll();*/

	Winkel winkel;

	cout << sizeof(winkel) << "\n";

	return 0;
}

void Winkel::AddArticle(int place, Artikel* newArticle) {
	int oldCounter = 0;
	int newCounter = 0;
	if(place > max) {
		cout << "Place is bigger than size of array -> Adding article as last item\n";
		place = max;
	}
	if(newArticle == NULL) {
		cout << "Article is empty, returning.\n";
		return;
	}

	Artikel** tempArray = new Artikel* [max + 1];
	
	while(newCounter < (max + 1)) {
		if(oldCounter == place) {
			place = -1;
			tempArray[newCounter] = newArticle;
			newCounter++;
			continue;
		}
		else {
			tempArray[newCounter] = articles[oldCounter];
		}

		newCounter++;
		oldCounter++;
	}

	delete articles;
	articles = tempArray;
	max++;
	cout << "Succesfully added new item.\n";
}

void Winkel::AddArticle(Artikel* newArticle) {
	AddArticle(max, newArticle);
}

void Winkel::DeleteArticle(int place) {
	int oldCounter = 0;
	int newCounter = 0;
	if(place > max) {
		cout << "Place is bigger than size of array -> Deleting article as last item\n";
		place = max - 1;
	}

	Artikel** tempArray = new Artikel*[max - 1];
	
	while(oldCounter < max) {
		if(oldCounter == place) {
			place = -1;
			oldCounter++;
			continue;
		}
		else {
			tempArray[newCounter] = articles[oldCounter];
		}

		newCounter++;
		oldCounter++;
	}

	delete articles;
	articles = tempArray;
	max--;
	cout << "Succesfully added new item.\n";
}

void Winkel::DeleteLast() {
	DeleteArticle(max - 1);
}

void Winkel::PrintAll() {
	for(int i = 0; i < max; i++) {
		if(articles[i] != NULL)
			articles[i]->Toon();
		else
			cout << "Null\n";
	}
}
