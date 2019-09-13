//
// Created by brent on 14.08.18.
//

#ifndef CAS_PATHCONTROLLER_H
#define CAS_PATHCONTROLLER_H


class PathController {
public:
	virtual float getValue(float current, float min, float max) = 0;
};


#endif //CAS_PATHCONTROLLER_H
