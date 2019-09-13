//
// Created by brent on 16.08.18.
//

#ifndef CAS_FFD_H
#define CAS_FFD_H

#include "GameObject.h"

class Clickable;
class Model;

class FFD: public GameObject {
public:
	FFD(OpenGLRenderer* renderer, int width, int height, int depth, float dimensions);

	void update(InputBuffer *keyBuffer, glm::vec3 cameraPosition, glm::vec3 cameraDirection, float deltaMillis) override;
	glm::vec3 transformPoint(glm::vec3 point);

protected:
	void render(float deltaMillis, bool transform, glm::mat4 &transMatrix) override;

	int m_width;
	int m_height;
	int m_depth;
	float m_dimensions;

	Model* m_model;
	Clickable**** m_editPoints;
	bool m_changed;
	glm::vec3*** m_positions;
};


#endif //CAS_FFD_H
