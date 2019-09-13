//
// Created by brent on 14.08.18.
//

#ifndef CAS_PATH_H
#define CAS_PATH_H


#include <glm/vec3.hpp>
#include <vector>
#include <map>
#include <glm/detail/type_mat4x4.hpp>

class PathController;
class Line;
class OpenGLRenderer;

enum Mode { TIME, SPEED };

class Path {
public:
	Path(OpenGLRenderer* renderer, Mode mode, bool looping = true);
	~Path();

	void addPoint(glm::vec3 point, float seconds);
	void adjustPoint(int index, glm::vec3 point, float seconds);
	void removePoint(int index);

	virtual void calculate() = 0;
	virtual void setController(PathController* controller);

	virtual void render(float deltaMillis) = 0;
	virtual glm::vec3 interpolate(float secondsPassed) = 0;

protected:
	float m_seconds;
	int m_index;

	Mode m_mode;
	bool m_looping;

	std::vector<glm::vec3> m_points;
	std::vector<float> m_timestamp;

	PathController* m_controller;

	OpenGLRenderer* m_renderer;
};


#endif //CAS_PATH_H
