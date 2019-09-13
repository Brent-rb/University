//
// Created by brent on 15.08.18.
//

#ifndef CAS_CLICKABLE_H
#define CAS_CLICKABLE_H

#include "GameObject.h"

class Clickable: public GameObject {
public:
	Clickable(OpenGLRenderer* renderer, bool hoverable = true, bool draggable = true, glm::vec3 hoverColor = glm::vec3(142, 194, 252), float hoverScale = 1.0f);
	Clickable(OpenGLRenderer* renderer, Renderable* renderable, bool hoverable = true, bool draggable = true, glm::vec3 hoverColor = glm::vec3(142, 194, 252), float hoverScale = 1.0f);

public:
	float distanceFromCamera(glm::vec3 cameraPosition, glm::vec3 cameraDirection);
	void hover();
	void select();
	void deselect();

public:
	virtual void update(InputBuffer *keyBuffer, glm::vec3 cameraPosition, glm::vec3 cameraDirection, float deltaMillis);

protected:
	virtual void render(float deltaMillis, bool transform, glm::mat4 &transMatrix);

	virtual void onSelected();
	virtual void onDeselected();

protected:
	bool m_selected;
	bool m_draggable;
	bool m_hoverable;
	bool m_hovering;
	bool m_hoveringLast;

	glm::vec3 m_hoverColor;
	glm::vec3 m_hoverScale;
	glm::vec3 m_originalScale;
	glm::vec3 m_originalColor;

	float m_deadzone;
	float m_lastDistance;
};


#endif //CAS_CLICKABLE_H
