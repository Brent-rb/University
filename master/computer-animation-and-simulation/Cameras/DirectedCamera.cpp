//
// Created by brent on 14.08.18.
//

#include "DirectedCamera.h"
#include "../OpenGLRenderer.h"
#include "../Path/Path.h"

DirectedCamera::DirectedCamera(OpenGLRenderer *renderer): Camera(renderer->getShaderProgram()->getProgram()), m_path(nullptr), m_rotationPath(nullptr) {

}

void DirectedCamera::update(InputBuffer *buffer, float deltaMillis) {
	recalculateViewMatrix();
	if(m_path != nullptr) {
		glm::vec3 position = m_path->interpolate(deltaMillis / 1000.0);
		setLocation(position.x, position.y, position.z);
		setRecalculateFlag();
	}

	if(m_rotationPath != nullptr) {
		glm::vec3 rotation = m_rotationPath->interpolate(deltaMillis / 1000.0);
		setRotationDeg(rotation.x, rotation.y, rotation.z);
		setRecalculateFlag();
	}
}

void DirectedCamera::setPath(Path *path) {
	m_path = path;
}

void DirectedCamera::setRotationPath(Path *path) {
	m_rotationPath = path;
}
