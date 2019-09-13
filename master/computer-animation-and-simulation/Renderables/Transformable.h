//
// Created by brent on 19-1-18.
//

#ifndef CAS_TRANSFORMABLE_H
#define CAS_TRANSFORMABLE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Transformable {
public:
	Transformable();
	virtual ~Transformable();
	
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
	
	void setScale(float scaleX, float scaleY, float scaleZ);
	void setScaleX(float scaleX);
	void setScaleY(float scaleY);
	void setScaleZ(float scaleZ);
	
	glm::mat4 getModelMatrix();

protected:
	void setRecalculateFlag();
	void calculateModelMatrix();
	void recalculateModelMatrix();

protected:
	glm::mat4 mModelMatrix;
	
	glm::vec3 mRotation;
	glm::vec3 mLocation;
	glm::vec3 mScale;
	
	bool mRecalculateModelMatrix;
};


#endif //CAS_TRANSFORMABLE_H
