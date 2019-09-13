#include "InputBuffer.h"

InputBuffer::InputBuffer(GLFWwindow* window, int width, int height): mWindow(window), mMouse(window, width, height, GLFW_CURSOR, GLFW_CURSOR_NORMAL) {
	mDummyKey = new Key(-1, -1, -1, 0);
}

InputBuffer::~InputBuffer() {

}

void InputBuffer::keyCallback(GLFWwindow *window, int keyCode, int scanCode, int action, int modifiers) {
	if(keyCode != GLFW_KEY_UNKNOWN) {
		Key* key;
		if(mKeys.count(keyCode) > 0) {
			key = mKeys[keyCode];
		}
		else {
			key = mKeyPool.get();
		}
		key->set(keyCode, scanCode, action, modifiers);
		mKeys[keyCode] = key;
	}
	else {
		Key* key;
		if(mScanCodes.count(scanCode) > 0) {
			key = mScanCodes[scanCode];
		}
		else {
			key = mKeyPool.get();
		}
		key->set(keyCode, scanCode, action, modifiers);
		mScanCodes[scanCode] = key;
	}
}

void InputBuffer::tick() {
	Key* key;
	int lastAction, currentAction;

	for(auto it = mKeys.begin(); it != mKeys.end(); it++) {
		key = it->second;
		lastAction = key->getLastAction();
		currentAction = key->getAction();

		if(lastAction != -1){
			if(lastAction == currentAction) {
				if(key->isPressed())
					key->setAction(GLFW_REPEAT);
				else if(key->isReleased())
					key->setAction(-1);
			}
			else {
				if(lastAction == GLFW_PRESS) {
					if(currentAction != GLFW_REPEAT && currentAction != GLFW_RELEASE) {
						key->setAction(GLFW_RELEASE);
					}

				}
			}
		}
		key->setLastAction(currentAction);
	}

}

Key* InputBuffer::getKey(int key) {
	if(mKeys.count(key) > 0) {
		return mKeys[key];
	}
	else {
		return mDummyKey;
	}
}

Key* InputBuffer::getScanCode(int scanCode) {
	if(mScanCodes.count(scanCode) > 0) {
		return mScanCodes[scanCode];
	}
	else {
		return mDummyKey;
	}
}

Mouse *InputBuffer::getMouse() {
	return &mMouse;
}

void InputBuffer::clear() {
	for(auto iterator = mKeys.begin(); iterator != mKeys.end(); iterator++) {
		Key* key = iterator->second;
		mKeyPool.release(key);
	}
	for(auto iterator = mScanCodes.begin(); iterator != mScanCodes.end(); iterator++) {
		Key* key = iterator->second;
		mKeyPool.release(key);
	}
	mKeys.clear();
	mScanCodes.clear();
}