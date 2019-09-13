//
// Created by brent on 14.08.18.
//
#include "Path.h"
#include "EaseInEaseOut.h"
#include "../OpenGLRenderer.h"
#include <iostream>
#include "../Help.h"

Path::Path(OpenGLRenderer* renderer, Mode mode, bool looping): m_renderer(renderer), m_mode(mode), m_looping(looping) {
	m_controller = new EaseInEaseOut();
	m_seconds = 0.0f;
	m_mode = SPEED;
	m_index = 0;
}

Path::~Path() {

}

void Path::addPoint(glm::vec3 point, float seconds) {
	m_points.push_back(point);
	m_timestamp.push_back(seconds);
}

void Path::adjustPoint(int index, glm::vec3 point, float seconds) {
	m_points[index] = point;
	m_timestamp[index] = seconds;
}

void Path::removePoint(int index) {
	m_points.erase(m_points.begin() + index);
	m_timestamp.erase(m_timestamp.begin() + index);
}

void Path::setController(PathController *controller) {
	m_controller = controller;
}

