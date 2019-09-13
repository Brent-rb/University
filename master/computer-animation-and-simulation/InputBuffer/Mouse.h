//
// Created by brent on 21-11-17.
//

#ifndef CAS_MOUSE_H
#define CAS_MOUSE_H


#include <glm/vec2.hpp>
#include <GLFW/glfw3.h>
#include <map>

class Mouse {
public:
	Mouse(GLFWwindow* window, int width, int height);
	Mouse(GLFWwindow* window, int width, int height, int cursor, int mode);
	~Mouse();
	
	void update();
	void tick();
	void mouseCallback(GLFWwindow* window, int button, int action, int mods);
	
	void setPosition(glm::vec2 position);
	void setPosition(double xPos, double yPos);
	void setHidden(bool hidden);
	void setConstrained(bool constrained);
	void setDeltaMode(bool deltaMode);
	void setMouseInMiddle();

	glm::vec2 getPosition();
	double getX();
	double getY();
	
	glm::vec2 getDelta();
	double getDeltaX();
	double getDeltaY();
	
	bool isHidden();
	bool isConstrained();
	bool isDeltaMode();

	bool isLeftMouseButtonDown();
	bool isRightMouseButtonDown();

protected:
	void determineMode();
	void setMode(int mode);

private:
	GLFWwindow* mWindow;
	int mWidth;
	int mHeight;
	int mCursor;
	int mMode;
	
	glm::vec2 mPosition;
	glm::vec2 mDelta;
	bool mHidden;
	bool mConstrained;
	bool mDeltaMode;

	std::map<int, int> mButtons;
	std::map<int, int> mButtonsLast;
};


#endif //CAS_MOUSE_H
