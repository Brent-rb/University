//
// Created by brent on 14.08.18.
//

#include "LinearController.h"

float LinearController::getValue(float current, float min, float max) {
	return (current - min) / (max - min);
}
