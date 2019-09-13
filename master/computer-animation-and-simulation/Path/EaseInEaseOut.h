//
// Created by brent on 14.08.18.
//

#ifndef CAS_EASEINEASEOUT_H
#define CAS_EASEINEASEOUT_H

#include "PathController.h"

class EaseInEaseOut: public PathController {
public:
	float getValue(float current, float min, float max) override;
};


#endif //CAS_EASEINEASEOUT_H
