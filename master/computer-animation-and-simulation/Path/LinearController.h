//
// Created by brent on 14.08.18.
//

#ifndef CAS_LINEARCONTROLLER_H
#define CAS_LINEARCONTROLLER_H

#include "PathController.h"

class LinearController: public PathController {
public:
	float getValue(float current, float min, float max) override;
};


#endif //CAS_LINEARCONTROLLER_H
