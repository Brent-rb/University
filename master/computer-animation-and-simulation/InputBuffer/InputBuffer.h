#ifndef INPUTBUFFER_H
#define INPUTBUFFER_H

#include <map>
#include "Key.h"
#include "Mouse.h"
#include "../ObjectPool.h"

class InputBuffer {
public:
	InputBuffer(GLFWwindow* window, int width, int height);
	virtual ~InputBuffer();

	void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int modifiers);

	Key* getKey(int key);
	Key* getScanCode(int scanCode);

	void tick();
	
	Mouse* getMouse();

	void clear();

private:
	GLFWwindow* mWindow;
	
	std::map<int, Key*> mKeys;
	std::map<int, Key*> mScanCodes;
	Mouse mMouse;
	ObjectPool<Key> mKeyPool;

	Key* mDummyKey;
};

#endif