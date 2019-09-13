#ifndef KEY_H
#define KEY_H

#include <GLFW/glfw3.h>

class Key {
public:
	Key(int key, int scanCode, int action, int modifiers);
	Key();
	virtual ~Key();

	bool isKey(int key);
	bool isScanCode(int scanCode);
	
	bool isPressed();
	bool isRepeated();
	bool isDown();
	bool isReleased();

	int getAction();
	int getLastAction();
	void setLastAction(int action);

	bool hasModifiers(int modifiers);

	void set(int key, int scanCode, int action, int modifiers);
	void setKey(int key);
	void setScanCode(int scanCode);
	void setAction(int action);
	void setModifiers(int modifiers);

private:
	int mKey;
	int mScanCode;
	int mAction;
	int mLastAction;
	int mModifiers;
};

#endif