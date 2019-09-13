//
// Created by brent on 16.08.18.
//

#include "InterpolatedPath.h"
#include "../OpenGLRenderer.h"
#include "../Renderables/Line.h"
#include "../Help.h"
#include "PathController.h"

InterpolatedPath::InterpolatedPath(OpenGLRenderer *renderer, Mode mode, bool looping) : Path(renderer, mode, looping) {
	m_tau = 0.5f;
	m_matrix[0] = glm::vec4(-1,2,-1,0);
	m_matrix[1] = glm::vec4(3,-5,0,2);
	m_matrix[2] = glm::vec4(-3,4,1,0);
	m_matrix[3] = glm::vec4(1,-1,0,0);
	m_matrix *= m_tau;

	m_line = new Line(renderer->getShaderProgram()->getProgram(), 20.0f);
}

InterpolatedPath::~InterpolatedPath() {

}

void InterpolatedPath::setTau(float tau) {
	m_tau = tau;
}

float InterpolatedPath::getTau() {
	return m_tau;
}

void InterpolatedPath::calculate() {
	for(int sector = 0; sector < m_points.size() - 1; sector++) {
		glm::mat4 pointMatrix;

		if(sector - 1  < 0) {
			pointMatrix[0] = glm::vec4(0, 0, 0, 1);
		}
		if(sector + 1 >= m_points.size()) {
			pointMatrix[2] = glm::vec4(0, 0, 0, 1);
		}
		if(sector + 2 >= m_points.size()) {
			pointMatrix[3] = glm::vec4(0, 0, 0, 1.0f);
		}

		for(int i = 0; i < 4; i++) {
			int sectorIndex = sector + (i - 1);

			if(sectorIndex >= 0 && sectorIndex < m_points.size()) {
				pointMatrix[i] = glm::vec4(m_points[sectorIndex], 1);
			}
		}

		pointMatrix = glm::transpose(pointMatrix);

		float t0 = m_timestamp[sector];
		float t1 = m_timestamp[sector + 1];
		float dt = t1 - t0;
		std::map<float, float> samples;
		glm::vec3 prevVec = m_points[sector];
		float length = 0;
		float distance = 0;
		for(float timestamp = t0; timestamp < t1; timestamp += dt / 1000.0f) {
			float u = (timestamp - t0) / dt;
			glm::vec4 uVec(pow(u, 3), pow(u, 2), u, 1);
			glm::vec3 position = glm::vec3(uVec * m_matrix * pointMatrix);
			std::cout << "Position: " << position.x << " " << position.y << " " << position.z << std::endl;
			glm::vec3 dif = position - prevVec;
			distance += Help::length(dif);
			samples[u] = distance;
			m_line->addVertex(position);
		}

		m_samples.push_back(samples);
		m_sampleLengths.push_back(distance);
	}
	m_line->init();
	m_line->printInfo();
}

void InterpolatedPath::render(float deltaMillis) {
	glm::vec3 color = glm::vec3(255.0f, 0.0f, 0.0f);
	float opacity = 1.0f;
	m_renderer->getShaderProgram()->setUniform("objectOpacity", opacity);
	m_renderer->getShaderProgram()->setUniform("objectColor", color);
	m_line->render(deltaMillis);
}

glm::vec3 InterpolatedPath::interpolate(float secondsPassed) {
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

	//std::cout << "Seconds: " << m_seconds << std::endl;
	float u;
	glm::vec4 uVec;

	for(int i = m_index; i < m_timestamp.size() - 1; i++) {
		if(m_seconds >= m_timestamp[i] && m_seconds < m_timestamp[i + 1]) {
			m_index = i;
			break;
		}
	}
	u = m_controller->getValue(m_seconds, m_timestamp[m_index], m_timestamp[m_index + 1]);

	glm::mat4 pointMatrix;

	if(m_index - 1  < 0) {
		pointMatrix[0] = glm::vec4(0, 0, 0, 1);
	}
	if(m_index + 1 >= m_points.size()) {
		pointMatrix[2] = glm::vec4(0, 0, 0, 1);
	}
	if(m_index + 2 >= m_points.size()) {
		pointMatrix[3] = glm::vec4(0, 0, 0, 1);
	}

	for(int i = 0; i < 4; i++) {
		int sectorIndex = m_index + (i - 1);

		if(sectorIndex >= 0 && sectorIndex < m_points.size()) {
			pointMatrix[i] = glm::vec4(m_points[sectorIndex], 1);
		}
	}

	pointMatrix = glm::transpose(pointMatrix);

	if(m_mode == SPEED) {
		float timePercentage = u;
		bool init = false;
		float percentDiff, sampleU, sampleDistance = 0;
		float distance = m_sampleLengths[m_index];
		float wantedDistance = distance * timePercentage;
		float closestDistance, closestU, closestPercent, closestPercentDiff;

		for(auto it = m_samples[m_index].begin(); it != m_samples[m_index].end(); it++) {
			sampleU = it->first;
			sampleDistance = it->second;

			float percentage = sampleDistance / distance;
			percentDiff = fabs(timePercentage - percentage);
			if(!init) {
				init = true;
				closestDistance = sampleDistance;
				closestU = sampleU;
				closestPercent = percentage;
				closestPercentDiff = percentDiff;
			}
			else {
				if(percentDiff < closestPercentDiff) {
					closestDistance = sampleDistance;
					closestU = sampleU;
					closestPercent = percentage;
					closestPercentDiff = percentDiff;
				}
			}
		}

		u = closestU;
	}

	//std::cout << "U: " << u << std::endl;
	uVec = glm::vec4(pow(u, 3), pow(u, 2), u, 1);

	return glm::vec3(uVec * m_matrix * pointMatrix);
}
