//
// Created by brent on 01.08.18.
//
#include <cmath>
#include "Help.h"
#include <cstdlib>

bool Help::equals(float left, float right) {
	return (fabs(right - left) < 0.00001f);
}

float Help::length(glm::vec3 vec) {
	return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

float Help::random(float min, float max) {
	float random = ((float) rand()) / (float) RAND_MAX;
	float diff = max - min;
	float r = random * diff;
	return min + r;
}
