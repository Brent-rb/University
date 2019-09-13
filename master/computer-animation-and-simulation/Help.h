//
// Created by brent on 01.08.18.
//

#ifndef CAS_HELP_H
#define CAS_HELP_H


#include <glm/vec3.hpp>

class Help {
public:
	static bool equals(float left, float right);
	static float length(glm::vec3 vec);
	static float random(float min, float max);
};


#endif //CAS_HELP_H
