//
// Created by brent on 16.08.18.
//

#include "FFDClickable.h"

FFDClickable::FFDClickable(OpenGLRenderer *renderer, Renderable* renderable, glm::vec3& editPoint, bool& changed, glm::mat4& modelMatrix): Clickable(renderer, renderable), m_editPoint(editPoint), m_changed(changed), m_modelMatrix(modelMatrix) {

}

void FFDClickable::onDeselected() {
	Clickable::onDeselected();
	glm::mat4 inv = glm::inverse(m_modelMatrix);

	m_editPoint = glm::vec3(inv * glm::vec4(mLocation, 1));
	m_changed = true;
}

void
FFDClickable::update(InputBuffer *keyBuffer, glm::vec3 cameraPosition, glm::vec3 cameraDirection, float deltaMillis) {
	Clickable::update(keyBuffer, cameraPosition, cameraDirection, deltaMillis);

	if(m_selected) {
		m_editPoint = mLocation;
		m_changed = true;
	}
}
