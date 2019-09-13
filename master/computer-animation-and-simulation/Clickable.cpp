//
// Created by brent on 15.08.18.
//

#include "Clickable.h"
#include "OpenGLRenderer.h"
#include "Help.h"

Clickable::Clickable(OpenGLRenderer *renderer, bool hoverable, bool draggable, glm::vec3 hoverColor, float hoverScale): GameObject(renderer), m_hoverable(hoverable), m_draggable(draggable)  {
	m_hoverColor = hoverColor;
	m_hoverScale = glm::vec3(hoverScale, hoverScale, hoverScale);
	m_deadzone = 2.0f;

	m_selected = false;
	m_hovering = false;
	m_hoveringLast = false;

	setColor(1, 1, 1);
	m_hoverColor = glm::vec3(0.4, 0.4, 1);
}

Clickable::Clickable(OpenGLRenderer *renderer, Renderable *renderable, bool hoverable, bool draggable, glm::vec3 hoverColor, float hoverScale) : GameObject(renderer, renderable), m_hoverable(hoverable), m_draggable(draggable) {
	m_hoverColor = hoverColor;
	m_hoverScale = glm::vec3(hoverScale, hoverScale, hoverScale);
	m_deadzone = 2.0f;

	m_selected = false;
	m_hovering = false;
	m_hoveringLast = false;

	setColor(1, 1, 1);
	m_hoverColor = glm::vec3(255.0f, 1.0f, 1.0f);
}

void Clickable::update(InputBuffer *keyBuffer, glm::vec3 cameraPosition, glm::vec3 cameraDirection, float deltaMillis) {
	//GameObject::update(keyBuffer, cameraPosition, cameraDirection, deltaMillis);

	if(!m_hovering && m_hoveringLast) {
		mScale = m_originalScale;
		mColor = m_originalColor;
	}

	if(m_selected) {
		mLocation = cameraPosition + (-cameraDirection * m_lastDistance);
		setLocation(mLocation.x, mLocation.y, mLocation.z);
	}

	m_hoveringLast = m_hovering;
	m_hovering = false;
}

void Clickable::render(float deltaMillis, bool transform, glm::mat4 &transMatrix) {
	GameObject::render(deltaMillis, transform, transMatrix);
	m_hovering = false;
}

float Clickable::distanceFromCamera(glm::vec3 cameraPosition, glm::vec3 cameraDirection) {
	glm::vec3 location = mLocation;
	glm::vec3 diff = cameraPosition - location;

	glm::vec3 nearestCameraPosition;
	float cameraDistance = Help::length(diff);
	nearestCameraPosition = cameraPosition + cameraDirection * cameraDistance;
	diff = nearestCameraPosition - location;
	float diffDistance = Help::length(diff);
	if(diffDistance < m_deadzone) {
		m_lastDistance = cameraDistance;
		return cameraDistance;
	}
	return -1.0f;
}

void Clickable::hover() {
	if(!m_hoveringLast) {
		m_originalScale = mScale;
		m_originalColor = mColor;
		setScale(m_hoverScale.x * m_originalScale.x, m_hoverScale.y * m_originalScale.y, m_hoverScale.z * m_originalScale.z);
		setColor(m_hoverColor.r, m_hoverColor.g, m_hoverColor.b);
	}
	m_hovering = true;
}

void Clickable::select() {
	m_selected = true;
	onSelected();
}

void Clickable::deselect() {
	m_selected = false;
	onDeselected();
}

void Clickable::onSelected() {

}

void Clickable::onDeselected() {

}
