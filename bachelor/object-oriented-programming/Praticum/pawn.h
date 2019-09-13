#ifndef PION_H
#define PION_H
enum Kleur{WIT,ZWART};
class Pion{
public:
	Pion(Kleur kleur){this->kleur = kleur; this->moved = false;}
	bool hasMoved(){return this->moved;}
	Kleur geefKleur(){return this->kleur;}
private:
	Kleur kleur;
	bool moved;
};

#endif