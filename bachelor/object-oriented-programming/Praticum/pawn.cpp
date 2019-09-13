#include "pawn.h"
#include "zet.h"


 Pion::Pion(Kleur kleur) {
 	this->kleur = kleur; 
 	this->moved = false; 
 	zet = new Zet;
 }

 bool Pion::ControleerMove(int x, int y, int newX, int newY, Spelbord* spelbord){ return this->zet->ControleerMove(x, y, newX, newY, spelbord);}