//
// Created by brent on 17-11-17.
//

#ifndef CAS_CAMERA_H
#define CAS_CAMERA_H

#include <glm/glm.hpp>
#include <GL/glew.h>

class InputBuffer;

class Camera {
public:
	Camera(GLuint shaderProgram);
	~Camera();
	
	void rotateDeg(float degreesX, float degreesY, float degreesZ);
	void rotateDegX(float degreesX);
	void rotateDegY(float degreesY);
	void rotateDegZ(float degreesZ);
	
	void rotateRad(float radX, float radY, float radZ);
	void rotateRadX(float radX);
	void rotateRadY(float radY);
	void rotateRadZ(float radZ);
	
	void translate(float x, float y, float z);
	void translateX(float x);
	void translateY(float y);
	void translateZ(float z);
	
	void setRotationDeg(float degreesX, float degreesY, float degreesZ);
	void setRotationDegX(float degreesX);
	void setRotationDegY(float degreesY);
	void setRotationDegZ(float degreesZ);
	
	void setRotationRad(float radX, float radY, float radZ);
	void setRotationRadX(float radX);
	void setRotationRadY(float radY);
	void setRotationRadZ(float radZ);
	
	void setLocation(float x, float y, float z);
	void setX(float x);
	void setY(float y);
	void setZ(float z);
	
	virtual void update(InputBuffer* buffer, float deltaMillis) = 0;
	void apply();
	
	virtual glm::vec3 getPosition();
	virtual glm::vec3 getForwardVector();
	
protected:
	void setRecalculateFlag();
	void calculateViewMatrix();
	void recalculateViewMatrix();

protected:
	GLuint mShaderProgram;
	GLint mCameraUni;
	
	glm::mat4 mViewMatrix;
	
	glm::vec3 mRotation;
	glm::vec3 mLocation;
	
	bool mRecalculateViewMatrix;
};

#endif //
