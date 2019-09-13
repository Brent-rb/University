//
// Created by brent on 19-1-18.
//

#include "Transformable.h"

Transformable::Transformable() {
	mRecalculateModelMatrix = true;
	setScale(1.0f, 1.0f, 1.0f);
}

Transformable::~Transformable() {

}

void Transformable::rotateDeg(float degreesX, float degreesY, float degreesZ) {
	rotateDegX(degreesX);
	rotateDegY(degreesY);
	rotateDegZ(degreesZ);
}

void Transformable::rotateDegX(float degreesX) {
	rotateRadX(glm::radians(degreesX));
}

void Transformable::rotateDegY(float degreesY) {
	rotateRadY(glm::radians(degreesY));
}

void Transformable::rotateDegZ(float degreesZ) {
	rotateRadZ(glm::radians(degreesZ));
}

void Transformable::rotateRad(float radX, float radY, float radZ) {
	rotateRadX(radX);
	rotateRadY(radY);
	rotateRadZ(radZ);
}

void Transformable::rotateRadX(float radX) {
	mRotation.x += radX;
	setRecalculateFlag();
}

void Transformable::rotateRadY(float radY) {
	mRotation.y += radY;
	setRecalculateFlag();
}

void Transformable::rotateRadZ(float radZ) {
	mRotation.z += radZ;
	setRecalculateFlag();
}

void Transformable::translate(float x, float y, float z) {
	translateX(x);
	translateY(y);
	translateZ(z);
}

void Transformable::translateX(float x) {
	mLocation.x += x;
	setRecalculateFlag();
}

void Transformable::translateY(float y) {
	mLocation.y += y;
	setRecalculateFlag();
}

void Transformable::translateZ(float z) {
	mLocation.z += z;
	setRecalculateFlag();
}

void Transformable::setScale(float scaleX, float scaleY, float scaleZ) {
	setScaleX(scaleX);
	setScaleY(scaleY);
	setScaleZ(scaleZ);
}

void Transformable::setScaleX(float scaleX) {
	mScale.x = scaleX;
	setRecalculateFlag();
}

void Transformable::setScaleY(float scaleY) {
	mScale.y = scaleY;
	setRecalculateFlag();
}

void Transformable::setScaleZ(float scaleZ) {
	mScale.z = scaleZ;
	setRecalculateFlag();
}

void Transformable::setRotationDeg(float degreesX, float degreesY, float degreesZ) {
	setRotationDegX(degreesX);
	setRotationDegY(degreesY);
	setRotationDegZ(degreesZ);
}

void Transformable::setRotationDegX(float degreesX) {
	setRotationRadX(glm::radians(degreesX));
}

void Transformable::setRotationDegY(float degreesY) {
	setRotationRadY(glm::radians(degreesY));
}

void Transformable::setRotationDegZ(float degreesZ) {
	setRotationRadZ(glm::radians(degreesZ));
}


void Transformable::setRotationRad(float radX, float radY, float radZ) {
	setRotationRadX(radX);
	setRotationRadY(radY);
	setRotationRadZ(radZ);
}

void Transformable::setRotationRadX(float radX) {
	mRotation.x = radX;
	setRecalculateFlag();
}

void Transformable::setRotationRadY(float radY) {
	mRotation.y = radY;
	setRecalculateFlag();
}

void Transformable::setRotationRadZ(float radZ) {
	mRotation.z = radZ;
	setRecalculateFlag();
}

void Transformable::setLocation(float x, float y, float z) {
	setX(x);
	setY(y);
	setZ(z);
}

void Transformable::setX(float x) {
	mLocation.x = x;
	setRecalculateFlag();
}

void Transformable::setY(float y) {
	mLocation.y = y;
	setRecalculateFlag();
}

void Transformable::setZ(float z) {
	mLocation.z = z;
	setRecalculateFlag();
}

void Transformable::calculateModelMatrix() {
	glm::mat4 matZ = glm::mat4(1.0f);
	glm::mat4 matX = glm::mat4(1.0f);
	glm::mat4 matY = glm::mat4(1.0f);
	
	matZ = glm::rotate(matZ, mRotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	matX = glm::rotate(matX, mRotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	matY = glm::rotate(matY, mRotation.y, glm::vec3(0.0f, 1.0f, 0.0f));;
	
	glm::mat4 rotationMat = matZ * matX * matY;
	glm::mat4 translationMat = glm::translate(glm::mat4(1.0f), mLocation);
	glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), mScale);
	
	mModelMatrix = translationMat * rotationMat * scaleMat;
	mRecalculateModelMatrix = false;
}

void Transformable::recalculateModelMatrix() {
	if(mRecalculateModelMatrix) {
		calculateModelMatrix();
	}
}

void Transformable::setRecalculateFlag() {
	mRecalculateModelMatrix = true;
}

glm::mat4 Transformable::getModelMatrix() {
	recalculateModelMatrix();
	return mModelMatrix;
}
