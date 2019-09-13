//
// Created by brent on 17-11-17.
//

#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera(GLuint shaderProgram): mShaderProgram(shaderProgram) {
	mCameraUni = glGetUniformLocation(shaderProgram, "viewMatrix");
	mLocation = glm::vec3(0, 0, 0);
	mRotation = glm::vec3(0, 0, 0);
}

Camera::~Camera() {

}

void Camera::rotateDeg(float degreesX, float degreesY, float degreesZ) {
	rotateDegX(degreesX);
	rotateDegY(degreesY);
	rotateDegZ(degreesZ);
}

void Camera::rotateDegX(float degreesX) {
	rotateRadX(glm::radians(degreesX));
}

void Camera::rotateDegY(float degreesY) {
	rotateRadY(glm::radians(degreesY));
}

void Camera::rotateDegZ(float degreesZ) {
	rotateRadZ(glm::radians(degreesZ));
}

void Camera::rotateRad(float radX, float radY, float radZ) {
	rotateRadX(radX);
	rotateRadY(radY);
	rotateRadZ(radZ);
}

void Camera::rotateRadX(float radX) {
	mRotation.x += radX;
	setRecalculateFlag();
}

void Camera::rotateRadY(float radY) {
	mRotation.y += radY;
	setRecalculateFlag();
}

void Camera::rotateRadZ(float radZ) {
	mRotation.z += radZ;
	setRecalculateFlag();
}

void Camera::translate(float x, float y, float z) {
	translateX(x);
	translateY(y);
	translateZ(z);
}

void Camera::translateX(float x) {
	mLocation.x += x;
	setRecalculateFlag();
}

void Camera::translateY(float y) {
	mLocation.y += y;
	setRecalculateFlag();
}

void Camera::translateZ(float z) {
	mLocation.z += z;
	setRecalculateFlag();
}


void Camera::setRotationDeg(float degreesX, float degreesY, float degreesZ) {
	setRotationDegX(degreesX);
	setRotationDegY(degreesY);
	setRotationDegZ(degreesZ);
}

void Camera::setRotationDegX(float degreesX) {
	setRotationRadX(glm::radians(degreesX));
}

void Camera::setRotationDegY(float degreesY) {
	setRotationRadY(glm::radians(degreesY));
}

void Camera::setRotationDegZ(float degreesZ) {
	setRotationRadZ(glm::radians(degreesZ));
}


void Camera::setRotationRad(float radX, float radY, float radZ) {
	setRotationRadX(radX);
	setRotationRadY(radY);
	setRotationRadZ(radZ);
}

void Camera::setRotationRadX(float radX) {
	mRotation.x = radX;
	setRecalculateFlag();
}

void Camera::setRotationRadY(float radY) {
	mRotation.y = radY;
	setRecalculateFlag();
}

void Camera::setRotationRadZ(float radZ) {
	mRotation.z = radZ;
	setRecalculateFlag();
}

void Camera::setLocation(float x, float y, float z) {
	setX(x);
	setY(y);
	setZ(z);
}

void Camera::setX(float x) {
	mLocation.x = x;
	setRecalculateFlag();
}

void Camera::setY(float y) {
	mLocation.y = y;
	setRecalculateFlag();
}

void Camera::setZ(float z) {
	mLocation.z = z;
	setRecalculateFlag();
}

void Camera::calculateViewMatrix() {
	glm::mat4 matZ = glm::mat4(1.0f);
	glm::mat4 matX = glm::mat4(1.0f);
	glm::mat4 matY = glm::mat4(1.0f);
	
	matX = glm::rotate(matX, mRotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	matY = glm::rotate(matY, mRotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	matZ = glm::rotate(matZ, mRotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	
	glm::mat4 rotationMat = matZ * matX * matY;
	glm::mat4 translationMat = glm::translate(glm::mat4(1.0f), -mLocation);
	
	mViewMatrix = rotationMat * translationMat;
	mRecalculateViewMatrix = false;
}

void Camera::recalculateViewMatrix() {
	if(mRecalculateViewMatrix) {
		calculateViewMatrix();
	}
}

void Camera::setRecalculateFlag() {
	mRecalculateViewMatrix = true;
}

void Camera::apply() {
	recalculateViewMatrix();
	glUniformMatrix4fv(mCameraUni, 1, GL_FALSE, glm::value_ptr(mViewMatrix));
}

glm::vec3 Camera::getPosition() {
	return mLocation;
}

glm::vec3 Camera::getForwardVector() {
	glm::vec3 forwardVector(mViewMatrix[0][2], mViewMatrix[1][2], mViewMatrix[2][2]);
	return forwardVector;
}