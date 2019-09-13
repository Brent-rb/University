//
// Created by brent on 14.08.18.
//

#include <cmath>
#include "EaseInEaseOut.h"

float EaseInEaseOut::getValue(float current, float min, float max) {
	float delta = max - min;
	current -= min;
	current /= delta;

	if(current <= 0.5f) {
		return 2.0f * pow(current, 2);
	}
	current -= 0.5f;

	return 2.0f * current * (1.0f - current) + 0.5f;
}
