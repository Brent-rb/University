#ifndef SPELBORD_H
#define SPELBORD_H

#include "pawn.h"

#define MAX_ROWS 8
#define MAX_COLUMNS 8

class Spelbord {
public:
	Spelbord();
	void AddPion(int x, int y, Kleur kleur);
	void DeletePion(int x, int y);
	bool MovePion(int x, int y, int xNew, int yNew, Kleur kleur);
	bool HasPion(int x, int y);
	bool InBoundries(int x, int y);
	void PrintBord();
private:
	Pion* pionnen[MAX_ROWS][MAX_COLUMNS];
	int aantalPionnen;
};


#endif