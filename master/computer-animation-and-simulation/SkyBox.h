//
// Created by brent on 16.08.18.
//

#ifndef CAS_SKYBOX_H
#define CAS_SKYBOX_H

#include "GameObject.h"

enum Face {TOP, BOTTOM, LEFT, RIGHT, FORWARD, BACKWARD, FACES};
class Square;
class Texture;

class SkyBox: public GameObject {
public:
	SkyBox(OpenGLRenderer* renderer, float distance);

	void setTexture(Face face, Texture* texture);

	void update(InputBuffer *keyBuffer, glm::vec3 cameraPosition, glm::vec3 cameraDirection, float deltaMillis) override;

protected:
	void render(float deltaMillis, bool transform, glm::mat4 &transMatrix) override;

private:
	Square** m_squares;

	float m_distance;
};


#endif //CAS_SKYBOX_H
