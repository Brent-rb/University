#ifndef SWINDOW_H
#define SWINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <functional>

#include "InputBuffer/InputBuffer.h"

class SWindow {
public:
	SWindow(int width, int height, bool fullscreen, const char* name, const char* inFile, const char* outFile);
	virtual ~SWindow();
	
	void run();

private:
	static void errorCallback(int error, const char* description);
	static void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int modifiers);
	static void mouseCallback(GLFWwindow* window, int button, int action, int mods);

	void init();
	void createWindow();

private:
	int mWidth;
	int mHeight;
	bool mFullscreen;
	std::string mName;
	std::string mIn;
	std::string mOut;
	
	GLFWwindow* mWindow;
	InputBuffer* mKeyBuffer;

	std::function<void(int, const char*)> mErrorCallback;
};

#endif