//
// Created by brent on 16.08.18.
//

#ifndef CAS_ROTATIONPATH_H
#define CAS_ROTATIONPATH_H

#include "Path.h"

class RotationPath: public Path {
public:
	RotationPath(OpenGLRenderer* renderer, Mode mode, bool looping = true);

	void calculate() override;

	void render(float deltaMillis) override;

	glm::vec3 interpolate(float secondsPassed) override;

private:
	float m_seconds;
};


#endif //CAS_ROTATIONPATH_H
