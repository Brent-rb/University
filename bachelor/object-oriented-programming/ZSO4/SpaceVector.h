#ifndef SPACEVECTOR_H
#define SPACEVECTOR_H
#include "Vector.h"

class SpaceVector: public Vector {
public:
	SpaceVector();
	~SpaceVector();
	SpaceVector Cross(SpaceVector const &vec2);
};

#endif