#ifndef SPEL_H
#define SPEL_H
#include "Spelbord.h"

class Spel {
public:
	Spel();
	void MovePiece();
	void Engine();
private:
	bool whiteTurn;
	Spelbord* spelbord;
};


#endif