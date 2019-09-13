//
// Created by brent on 18-11-17.
//

#ifndef CAS_FIRSTPERSONCAMERA_H
#define CAS_FIRSTPERSONCAMERA_H

#include "Camera.h"

class FirstPersonCamera: public Camera {
public:
	FirstPersonCamera(GLuint shaderProgram, float movementSpeed);
	~FirstPersonCamera();
	
	void update(InputBuffer *buffer, float deltaMillis) override;

protected:
	float mMovementSpeed;
	bool init;
	float deadzone;
};


#endif //CAS_FIRSTPERSONCAMERA_H
