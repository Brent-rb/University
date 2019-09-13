//
// Created by brent on 18-11-17.
//

#include "GameObject.h"
#include "Renderables/Renderable.h"
#include "OpenGLRenderer.h"
#include <algorithm>
#include "Path/Path.h"

GameObject::GameObject(OpenGLRenderer *renderer): mRenderer(renderer), mColor(glm::vec3(1.0f, 1.0f, 1.0f)), mLightProperties(0.2f, 0.7f, 0.2f), mOpacity(1.0f), m_locationPath(nullptr), m_rotationPath(nullptr) {

}

GameObject::GameObject(OpenGLRenderer *renderer, Renderable *renderable): mRenderer(renderer), mColor(glm::vec3(1.0f, 1.0f, 1.0f)), mLightProperties(0.2f, 0.7f, 0.2f), mOpacity(1.0f), m_locationPath(nullptr), m_rotationPath(nullptr) {
	addRenderable(renderable);
}

GameObject::~GameObject() {

}

void GameObject::update(InputBuffer *keyBuffer, glm::vec3 cameraPosition, glm::vec3 cameraDirection, float deltaMillis) {
	if(m_locationPath != nullptr) {
		glm::vec3 position = m_locationPath->interpolate(deltaMillis / 1000.0f);
		setLocation(position.x, position.y, position.z);
	}
	if(m_rotationPath != nullptr) {
		glm::vec3 rotation = m_rotationPath->interpolate(deltaMillis / 1000.0f);
		setRotationDeg(rotation.x, rotation.y, rotation.z);
	}
	for(int i = 0; i < mChildren.size(); i++) {
		mChildren[i]->update(keyBuffer, cameraPosition, cameraDirection, deltaMillis);
	}
}

void GameObject::render(float deltaMillis) {
	glm::mat4 modelMatrix = getModelMatrix();
	render(deltaMillis, false, modelMatrix);
}

void GameObject::render(float deltaMillis, glm::mat4 &transMatrix) {
	render(deltaMillis, true, transMatrix);
}

void GameObject::render(float deltaMillis, bool transform, glm::mat4 &transMatrix) {
	glm::mat4 modelMatrix = (transform ? transMatrix * getModelMatrix() : getModelMatrix());

	mRenderer->getShaderProgram()->setUniform("objectColor", mColor);
	mRenderer->getShaderProgram()->setUniform("objectOpacity", mOpacity);
	mRenderer->getShaderProgram()->setUniform("objectProperties", mLightProperties);
	for(int i = 0; i < mRenderables.size(); i++) {
		mRenderables[i]->render(deltaMillis, modelMatrix);
	}
	for(int i = 0; i < mChildren.size(); i++) {
		mChildren[i]->render(deltaMillis, modelMatrix);
	}

	if(m_locationPath != nullptr) {
		m_locationPath->render(deltaMillis);
	}
}

void GameObject::addRenderable(Renderable *renderable) {
	mRenderables.push_back(renderable);
}

void GameObject::addGameObject(GameObject *gameObject) {
	mChildren.push_back(gameObject);
}

void GameObject::removeRenderable(Renderable *renderable) {
	auto position = std::find(mRenderables.begin(), mRenderables.end(), renderable);
	if (position != mRenderables.end()) // Element found
		mRenderables.erase(position);
}

void GameObject::removeGameObject(GameObject *gameObject) {
	auto position = std::find(mChildren.begin(), mChildren.end(), gameObject);
	if (position != mChildren.end()) // Element found
		mChildren.erase(position);
}

void GameObject::setParent(GameObject *parent) {
	mParent = parent;
}

void GameObject::setOpacity(float opacity) {
	mOpacity = opacity;
}

void GameObject::setColor(float r, float g, float b) {
	mColor = glm::vec3(r, g, b);
}

void GameObject::setPath(Path *path) {
	m_locationPath = path;
}

glm::vec3 GameObject::getColor() {
	return mColor;
}

float GameObject::getColorR() {
	return mColor.r;
}

float GameObject::getColorG() {
	return mColor.g;
}

float GameObject::getColorB() {
	return mColor.b;
}

float GameObject::getOpacity() {
	return mOpacity;
}

void GameObject::setRotationPath(Path *path) {
	m_rotationPath = path;
}

void GameObject::transform(FFD *ffd, glm::mat4& transMatrix) {
	glm::mat4 modelMatrix = getModelMatrix() * transMatrix;

	for(int i = 0; i < mRenderables.size(); i++) {
		mRenderables[i]->transform(ffd, modelMatrix);
	}

	for(int i = 0; i < mChildren.size(); i++) {
		mChildren[i]->transform(ffd, modelMatrix);
	}
}
