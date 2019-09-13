//
// Created by brent on 16.08.18.
//

#ifndef CAS_FFDCLICKABLE_H
#define CAS_FFDCLICKABLE_H

#include "Clickable.h";

class FFDClickable: public Clickable {
public:
	FFDClickable(OpenGLRenderer* renderer, Renderable* renderable, glm::vec3& editPoint, bool& changed, glm::mat4& modelMatrix);

protected:
public:
	virtual void update(InputBuffer *keyBuffer, glm::vec3 cameraPosition, glm::vec3 cameraDirection, float deltaMillis);

protected:
	virtual void onDeselected();

private:
	glm::mat4& m_modelMatrix;
	glm::vec3& m_editPoint;
	bool& m_changed;
};


#endif //CAS_FFDCLICKABLE_H
