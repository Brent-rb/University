//
// Created by brent on 16.08.18.
//

#include <glm/geometric.hpp>
#include <iostream>
#include "RotationPath.h"
#include "PathController.h"


RotationPath::RotationPath(OpenGLRenderer *renderer, Mode mode, bool looping) : Path(renderer, mode, looping) {

}

void RotationPath::calculate() {

}

void RotationPath::render(float deltaMillis) {

}

glm::vec3 RotationPath::interpolate(float secondsPassed) {
	m_seconds += secondsPassed;
	if(m_seconds > m_timestamp[m_timestamp.size() - 1]) {
		if(m_looping) {
			std::cout << "Resetting: " << std::endl;
			m_seconds = 0;
			m_index = 0;
		}
		else {
			m_seconds -= secondsPassed;
		}
	}

	for(int i = m_index; i < m_timestamp.size() - 1; i++) {
		if(m_seconds >= m_timestamp[i] && m_seconds < m_timestamp[i + 1]) {
			m_index = i;
			break;
		}
	}

	float u = m_controller->getValue(m_seconds, m_timestamp[m_index], m_timestamp[m_index + 1]);

	glm::vec3 interpolated = m_points[m_index] + ((m_points[m_index + 1] - m_points[m_index]) * u);
	return interpolated;
}
