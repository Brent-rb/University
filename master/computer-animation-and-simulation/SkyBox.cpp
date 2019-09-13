//
// Created by brent on 16.08.18.
//


#include "SkyBox.h"
#include "Renderables/Square.h"
#include "OpenGLRenderer.h"

SkyBox::SkyBox(OpenGLRenderer *renderer, float distance): GameObject(renderer), m_distance(distance), m_squares(nullptr) {
	mLightProperties = glm::vec3(1.0f, 0.0f, 0.0f);
	m_squares = new Square*[FACES];
	float distance2 = distance / 2.0f;
	m_squares[TOP] = new Square(renderer->getShaderProgram()->getProgram(), glm::vec3(-distance2, 0, distance2), glm::vec3(distance2, 0, distance2), glm::vec3(distance2, 0, -distance2), glm::vec3(-distance2, 0, -distance2), glm::vec3(0, -1, 0));
	m_squares[BOTTOM] = new Square(renderer->getShaderProgram()->getProgram(), glm::vec3(-distance2, 0, distance2), glm::vec3(distance2, 0, distance2), glm::vec3(distance2, 0, -distance2), glm::vec3(-distance2, 0, -distance2), glm::vec3(0, 1, 0));
	m_squares[FORWARD] = new Square(renderer->getShaderProgram()->getProgram(), glm::vec3(-distance2, -distance2, 0), glm::vec3(distance2, -distance2, 0), glm::vec3(distance2, distance2, 0), glm::vec3(-distance2, distance2, 0), glm::vec3(0, 0, 1));
	m_squares[BACKWARD] = new Square(renderer->getShaderProgram()->getProgram(), glm::vec3(-distance2, -distance2, 0), glm::vec3(distance2, -distance2, 0), glm::vec3(distance2, distance2, 0), glm::vec3(-distance2, distance2, 0), glm::vec3(0, 0, -1));
	m_squares[LEFT] = new Square(renderer->getShaderProgram()->getProgram(), glm::vec3(0, -distance2, distance2), glm::vec3(0, distance2, distance2), glm::vec3(0, distance2, -distance2), glm::vec3(0, -distance2, -distance2), glm::vec3(1, 0, 0));
	m_squares[RIGHT] = new Square(renderer->getShaderProgram()->getProgram(), glm::vec3(0, -distance2, distance2), glm::vec3(0, distance2, distance2), glm::vec3(0, distance2, -distance2), glm::vec3(0, -distance2, -distance2), glm::vec3(1, 0, 0));
	m_squares[LEFT]->rotateDegX(90);
	m_squares[RIGHT]->rotateDegX(90);
}

void SkyBox::setTexture(Face face, Texture *texture) {
	m_squares[face]->setTexture(texture);
}

void SkyBox::update(InputBuffer *keyBuffer, glm::vec3 cameraPosition, glm::vec3 cameraDirection, float deltaMillis) {
	GameObject::update(keyBuffer, cameraPosition, cameraDirection, deltaMillis);
	m_squares[TOP]->setLocation(cameraPosition.x, cameraPosition.y + m_distance / 2.0f, cameraPosition.z);
	m_squares[BOTTOM]->setLocation(cameraPosition.x, cameraPosition.y - m_distance / 2.0f, cameraPosition.z);
	m_squares[FORWARD]->setLocation(cameraPosition.x, cameraPosition.y, cameraPosition.z - m_distance / 2.0f);
	m_squares[BACKWARD]->setLocation(cameraPosition.x, cameraPosition.y, cameraPosition.z + m_distance / 2.0f);
	m_squares[LEFT]->setLocation(cameraPosition.x - m_distance / 2.0f, cameraPosition.y, cameraPosition.z);
	m_squares[RIGHT]->setLocation(cameraPosition.x + m_distance / 2.0f, cameraPosition.y, cameraPosition.z);
}

void SkyBox::render(float deltaMillis, bool transform, glm::mat4 &transMatrix) {
	GameObject::render(deltaMillis, transform, transMatrix);
	glCullFace(GL_FRONT);
	m_squares[TOP]->render(deltaMillis);
	m_squares[BACKWARD]->render(deltaMillis);
	m_squares[LEFT]->render(deltaMillis);
	glCullFace(GL_BACK);
	m_squares[BOTTOM]->render(deltaMillis);
	m_squares[RIGHT]->render(deltaMillis);
	m_squares[FORWARD]->render(deltaMillis);
	//glCullFace(GL_FRONT);
}
