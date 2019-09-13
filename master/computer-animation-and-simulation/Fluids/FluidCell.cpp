//
// Created by brent on 07.07.18.
//

#include <iostream>
#include "FluidCell.h"
#include "FluidPoint.h"

FluidCell::FluidCell() {

}

void FluidCell::clear() {
	m_points.clear();
}

void FluidCell::addPoint(FluidPoint *point) {
	m_points.push_back(point);
}

int FluidCell::size() {
	return m_points.size();
}

FluidPoint *FluidCell::getPoint(int index) {
	return m_points[index];
}

void FluidCell::print() {
	std::cout << "Fluid cell[" << size() << "]" << std::endl;
	for(int i = 0; i < size(); i++) {
		FluidPoint* point = getPoint(i);
		std::cout << "\tFluidPoint[" << point->getX() << ", " << point->getY() << ", " << point->getZ() << "]" << std::endl;
	}
}
