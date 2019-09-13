//
// Created by brent on 18-11-17.
//

#include <iostream>
#include "FirstPersonCamera.h"
#include "../InputBuffer/InputBuffer.h"


FirstPersonCamera::FirstPersonCamera(GLuint shaderProgram, float movementSpeed) : Camera(shaderProgram), mMovementSpeed(movementSpeed) {
	init = false;
}

FirstPersonCamera::~FirstPersonCamera() {

}

void FirstPersonCamera::update(InputBuffer *buffer, float deltaMillis) {
	recalculateViewMatrix();
	deltaMillis /= 1000.0f;
	float speedMultiplier = 1.0f;
	
	glm::vec3 movementVector;
	Key* forwardKey = buffer->getKey(GLFW_KEY_W);
	Key* backwardKey = buffer->getKey(GLFW_KEY_S);
	Key* leftKey = buffer->getKey(GLFW_KEY_A);
	Key* rightKey = buffer->getKey(GLFW_KEY_D);
	Key* speedKey = buffer->getKey(GLFW_KEY_LEFT_SHIFT);
	Mouse* mouse = buffer->getMouse();
	
	if(speedKey->isDown()) {
		speedMultiplier = 10.0f;
	}
	if(forwardKey->isDown()) {
		movementVector.z += mMovementSpeed * deltaMillis * speedMultiplier;
	}
	if(backwardKey->isDown()) {
		movementVector.z -= mMovementSpeed * deltaMillis * speedMultiplier;
	}
	if(leftKey->isDown()) {
		movementVector.x -= mMovementSpeed * deltaMillis * speedMultiplier;
	}
	if(rightKey->isDown()) {
		movementVector.x += mMovementSpeed * deltaMillis * speedMultiplier;
	}
	if(buffer->getKey(GLFW_KEY_SPACE)->isDown()) {
		movementVector.y += mMovementSpeed * deltaMillis * speedMultiplier;
	}
	if(buffer->getKey(GLFW_KEY_LEFT_CONTROL)->isDown()) {
		movementVector.y -= mMovementSpeed * deltaMillis * speedMultiplier;
	}

	if(init) {
		rotateDegY(mouse->getDeltaX() * deltaMillis * 2.0f);
		rotateDegX(mouse->getDeltaY() * deltaMillis * 2.0f);
	}
	else {
		deadzone += deltaMillis;
		if(deadzone > 1.0f)
			init = true;
	}
	
	glm::vec3 forwardVector(mViewMatrix[0][2], mViewMatrix[1][2], mViewMatrix[2][2]);
	glm::vec3 verticalVector(mViewMatrix[0][1], mViewMatrix[1][1], mViewMatrix[2][1]);
	glm::vec3 strafeVector(mViewMatrix[0][0], mViewMatrix[1][0], mViewMatrix[2][0]);
	
	mLocation += (-movementVector.z * forwardVector + movementVector.x * strafeVector + movementVector.y * verticalVector);
	setRecalculateFlag();
}
