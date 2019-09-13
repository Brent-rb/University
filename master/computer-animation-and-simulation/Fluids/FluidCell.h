//
// Created by brent on 07.07.18.
//

#ifndef CAS_FLUIDCELL_H
#define CAS_FLUIDCELL_H

#include <vector>

class FluidPoint;

class FluidCell {
public:
	FluidCell();

	void print();
	void clear();
	void addPoint(FluidPoint* point);

	int size();
	FluidPoint* getPoint(int index);

private:
	std::vector<FluidPoint*> m_points;
};


#endif //CAS_FLUIDCELL_H
