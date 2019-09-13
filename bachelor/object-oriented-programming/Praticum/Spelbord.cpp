#include "Spelbord.h"
#include <iostream>
#include <stdio.h>

using namespace std;

Spelbord::Spelbord(){
	this->aantalPionnen = 0;

	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			this->pionnen[i][j] = NULL;
}



void Spelbord::AddPion(int x, int y, Kleur kleur){
	if(InBoundries(x, y)) {
		if(!HasPion(x, y)) {
			Pion* pion = new Pion(kleur);

			this->pionnen[x][y] = pion;
			this->aantalPionnen++;
		}
		else 
			cout << "Op de locatie (" << x << "," << y << ") staat al een pion, geef een geldige locatie in.\n";
	}
	else {
		cout << "De locatie (" << x << "," << y << ") is ongeldig, gelive een geldige locatie in te geven.\n";
	}
}

void Spelbord::DeletePion(int x, int y){
	if(InBoundries(x, y)) {
		if(HasPion(x, y)) {
			delete this->pionnen[x][y];
			this->pionnen[x][y] = NULL;
			this->aantalPionnen--;
			cout << "Pion succesvol verwijdert.\n";
		}
		else 
			cout << "Op de locatie (" << x << "," << y << ") staat geen pion, geef een geldige locatie in.\n";
	}
	else {
		cout << "De locatie (" << x << "," << y << ") is ongeldig, gelieve een geldige locatie in te geven.\n";
	}
}

bool Spelbord::MovePion(int x, int y, int xNew, int yNew, Kleur kleur){
	if(!InBoundries(x, y)) {
		cout << "De locatie (" << x << "," << y << ") is ongeldig, gelieve een geldige locatie in te geven.\n";
		return false;
	}
	if(!HasPion(x, y)) {
		cout << "Op de locatie (" << x << "," << y << ") staat geen pion, geef een geldige locatie in.\n";
		return false;
	}

	if(kleur != this->pionnen[x][y]->geefKleur()) {
		cout << "De kleur van de te verplaatsen pion is verschillend van de kleur van de speler.\n";
		return false;
	}

	this->pionnen[xNew][yNew] = this->pionnen[x][y];
	this->pionnen[x][y] = NULL;

	return true;
}

bool Spelbord::HasPion(int x, int y) {
	return(this->pionnen[x][y] != NULL);
}

bool Spelbord::InBoundries(int x, int y) {
	if(x >= 0 && x < 8 && y >= 0 && y < 8)
		return true;
	else
		return false;
}

void Spelbord::PrintBord() {
	int row, colomn, i = 0;
	for (row = 0; row < MAX_ROWS; row++) {
		for(i = 0; i < MAX_COLUMNS; i++) {
			if(row == 0) {
				if (i < MAX_COLUMNS)
					cout << " _____";
				if (i == MAX_COLUMNS-1) {
					cout << "\n";
				}
			}
		}
		for (i = 0; i < MAX_COLUMNS; i++) {
			if (i == 0)
				cout << "|     |";
			else
				cout << "     |";
		}
		cout << "\n";
		for (colomn = 0; colomn < MAX_COLUMNS; colomn++) {
			if (this->pionnen[row][colomn] != NULL) {
				if(this->pionnen[row][colomn]->geefKleur() == ZWART) {
					if(colomn != MAX_COLUMNS-1)
						cout << "| .P. ";
					else
						cout << "| .P. |\n";
				}
				else {
					if(colomn != MAX_COLUMNS-1)
						cout << "|  P  ";
					else
						cout << "|  P  |\n";
				}
			}
			else {
				if(colomn != MAX_COLUMNS-1)
					cout << "|     ";
				else
					cout << "|     |\n";
			}
		}
		for (i = 0; i < MAX_COLUMNS; i++) {
			if(i == 0)
				cout << "|_____|";
			else
				cout << "_____|";
		}
		cout << "\n";
	}
}