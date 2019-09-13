#include "SWindow.h"
#include "OpenGLRenderer.h"
#include <chrono>

static SWindow* instance = nullptr;

SWindow::SWindow(int width, int height, bool fullscreen, const char *name, const char* inFile, const char* outFile): mWidth(width), mHeight(height), mFullscreen(fullscreen), mName(name), mWindow(nullptr) {
	instance = this;
	if(inFile == nullptr)
		mIn = "";
	else
		mIn = inFile;

	if(outFile == nullptr)
		mOut = "";
	else
		mOut = outFile;

	init();
}

SWindow::~SWindow() {
	if(mWindow != nullptr) {
		glfwDestroyWindow(mWindow);
		glfwTerminate();
	}
}

void SWindow::errorCallback(int error, const char *description) {
	std::cerr << description << std::endl;
}

void SWindow::keyCallback(GLFWwindow* window, int key, int scanCode, int action, int modifiers) {
	instance->mKeyBuffer->keyCallback(window, key, scanCode, action, modifiers);
}

void SWindow::mouseCallback(GLFWwindow *window, int button, int action, int mods) {
	instance->mKeyBuffer->getMouse()->mouseCallback(window, button, action, mods);
}

void SWindow::init() {
	glfwSetErrorCallback(&SWindow::errorCallback);

	if(!glfwInit()) {
		std::cerr << "GLFW not initialized." << std::endl;
		exit(EXIT_FAILURE);
	}
	else {
		createWindow();
	}
}

void SWindow::createWindow() {
	// Use modern GL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	
	mWindow = glfwCreateWindow(mWidth, mHeight, mName.c_str(), (mFullscreen ? glfwGetPrimaryMonitor() : nullptr), nullptr);
	if(mWindow == nullptr) {
		std::cerr << "Could not create window." << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	else {
		mKeyBuffer = new InputBuffer(mWindow, mWidth, mHeight);
		glfwSetKeyCallback(mWindow, &SWindow::keyCallback);
		glfwSetMouseButtonCallback(mWindow, &SWindow::mouseCallback);
		glfwMakeContextCurrent(mWindow);
		glewExperimental = GL_TRUE;
		glewInit();
	}
}

void SWindow::run() {
	OpenGLRenderer renderer(mWidth, mHeight, 45.0f, mIn, mOut);
	
	std::chrono::high_resolution_clock::time_point lastFrameTime = std::chrono::high_resolution_clock::now(), now;
	std::chrono::duration<float> delta;
	float millis;
	
	Mouse* mouse = mKeyBuffer->getMouse();
	mouse->setDeltaMode(true);
	mouse->setHidden(true);
	
	while (!glfwWindowShouldClose(mWindow)) {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		now = std::chrono::high_resolution_clock::now();
		delta = now - lastFrameTime;
		millis = std::chrono::duration_cast<std::chrono::milliseconds>(delta).count();

		glfwPollEvents();
		renderer.render(mKeyBuffer, millis);

		glfwSwapBuffers(mWindow);


		mKeyBuffer->tick();
		mKeyBuffer->getMouse()->tick();
		mouse->update();

		if(mKeyBuffer->getKey(GLFW_KEY_ESCAPE)->isPressed()) {
			glfwSetWindowShouldClose(mWindow, GL_TRUE);
		}
		
		lastFrameTime = now;
	}
}
