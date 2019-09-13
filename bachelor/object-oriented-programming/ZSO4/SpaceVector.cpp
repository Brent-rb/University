#include "SpaceVector.h"

SpaceVector::SpaceVector() {
	Allocate(3);
}

SpaceVector SpaceVector::Cross(SpaceVector const & vec2) const {
	SpaceVector temp;

	temp.vectorArray[0] = (vectorArray[1] * vec2.vectorArray[2] - vectorArray[2] * vec2.vectorArray[1]);
	temp.vectorArray[1] = (vectorArray[2] * vec2.vectorArray[0] - vectorArray[0] * vec2.vectorArray[2]);
	temp.vectorArray[2] = (vectorArray[0] * vec2.vectorArray[1] - vectorArray[1] * vec2.vectorArray[0]);


	return temp;
}

SpaceVector::~SpaceVector() {
}