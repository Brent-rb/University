//
// Created by brent on 21-11-17.
//

#include <iostream>
#include "Mouse.h"

Mouse::Mouse(GLFWwindow *window, int width, int height): Mouse(window, width, height, GLFW_CURSOR, GLFW_CURSOR_NORMAL) {

}

Mouse::Mouse(GLFWwindow *window, int width, int height, int cursor, int mode): mWindow(window), mWidth(width), mHeight(height), mCursor(cursor), mMode(mode) {
	mHidden = mMode != GLFW_CURSOR_NORMAL;
	mConstrained = mMode == GLFW_CURSOR_DISABLED;
	determineMode();
}

Mouse::~Mouse() {

}

void Mouse::update() {
	double xNow, yNow, deltaX, deltaY;
	glfwGetCursorPos(mWindow, &xNow, &yNow);
	deltaX = xNow - mPosition.x;
	deltaY = yNow - mPosition.y;
	mDelta.x = deltaX;
	mDelta.y = deltaY;
	mPosition.x = xNow;
	mPosition.y = yNow;
	
	if(mDeltaMode) {
		glfwSetCursorPos(mWindow, ((float) mWidth) / 2.0f, ((float) mHeight) / 2.0f);
		glfwGetCursorPos(mWindow, &xNow, &yNow);
		mPosition.x = xNow;
		mPosition.y = yNow;
	}
}

void Mouse::tick() {
	int lastAction, currentAction;
	int button;
	for(auto it = mButtons.begin(); it != mButtons.end(); it++) {
		button = it->first;
		currentAction = it->second;

		mButtons[button] = -1;
	}
}

void Mouse::setPosition(glm::vec2 position) {
	setPosition(position.x, position.y);
}

void Mouse::setPosition(double xPos, double yPos) {
	mPosition.x = xPos;
	mPosition.y = yPos;
	glfwSetCursorPos(mWindow, xPos, yPos);
}

void Mouse::setMouseInMiddle() {
	glfwSetCursorPos(mWindow, ((float) mWidth) / 2.0f, ((float) mHeight) / 2.0f);
}

void Mouse::setHidden(bool hidden) {
	mHidden = hidden;
	determineMode();
}

void Mouse::setConstrained(bool constrained) {
	mConstrained = constrained;
	if(mConstrained)
		mHidden = true;
	determineMode();
}

void Mouse::setDeltaMode(bool deltaMode) {
	mDeltaMode = deltaMode;
}

glm::vec2 Mouse::getPosition() {
	return mPosition;
}

double Mouse::getX() {
	return mPosition.x;
}

double Mouse::getY() {
	return mPosition.y;
}

glm::vec2 Mouse::getDelta() {
	return mDelta;
}

double Mouse::getDeltaX() {
	return mDelta.x;
}

double Mouse::getDeltaY() {
	return mDelta.y;
}

bool Mouse::isHidden() {
	return mHidden;
}

bool Mouse::isConstrained() {
	return mConstrained;
}

bool Mouse::isDeltaMode() {
	return mDeltaMode;
}

void Mouse::determineMode() {
	if(mConstrained) {
		setMode(GLFW_CURSOR_DISABLED);
	}
	else if(mHidden) {
		setMode(GLFW_CURSOR_HIDDEN);
	}
	else {
		setMode(GLFW_CURSOR_NORMAL);
	}
}

void Mouse::setMode(int mode) {
	mMode = mode;
	glfwSetInputMode(mWindow, mCursor, mMode);
}

void Mouse::mouseCallback(GLFWwindow *window, int button, int action, int mods) {
	mButtons[button] = action;
}

bool Mouse::isLeftMouseButtonDown() {
	return mButtons.count(GLFW_MOUSE_BUTTON_LEFT) > 0 && mButtons[GLFW_MOUSE_BUTTON_LEFT] == GLFW_PRESS;
}

bool Mouse::isRightMouseButtonDown() {
	return mButtons.count(GLFW_MOUSE_BUTTON_RIGHT) > 0 && mButtons[GLFW_MOUSE_BUTTON_RIGHT] == GLFW_PRESS;
}
