#include "Key.h"

Key::Key(int key, int scanCode, int action, int modifiers) {
	set(key, scanCode, action, modifiers);
}

Key::Key() {
	mAction = -1;
	mLastAction = -1;
	set(0, 0, 0, 0);
}

Key::~Key() {

}

bool Key::isKey(int key) {
	return mKey == key;
}

bool Key::isScanCode(int scanCode) {
	return mScanCode == scanCode;
}

bool Key::isPressed() {
	return mAction == GLFW_PRESS;
}

bool Key::isRepeated() {
	return mAction == GLFW_REPEAT;
}

bool Key::isDown() {
	return isPressed() || isRepeated();
}

bool Key::isReleased() {
	return mAction == GLFW_RELEASE;
}

bool Key::hasModifiers(int modifiers) {
	return (mModifiers | modifiers) == mModifiers;
}

void Key::set(int key, int scanCode, int action, int modifiers) {
	setKey(key);
	setScanCode(scanCode);
	setAction(action);
	setModifiers(modifiers);
}

void Key::setKey(int key) {
	mKey = key;
} 

void Key::setScanCode(int scanCode) {
	mScanCode = scanCode;
}

void Key::setAction(int action) {
	mAction = action;
}

void Key::setLastAction(int action) {
	mLastAction = action;
}

void Key::setModifiers(int modifiers) {
	mModifiers = modifiers;
}

int Key::getAction() {
	return mAction;
}

int Key::getLastAction() {
	return mLastAction;
}
