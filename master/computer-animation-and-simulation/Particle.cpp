//
// Created by brent on 17.08.18.
//

#include "Particle.h"
#include "Shaders/ShaderProgram.h"
#include "Renderables/Renderable.h"

Particle::Particle() {

}

void Particle::setPosition(glm::vec3 position) {
	mPosition = position;
}

void Particle::setVelocity(glm::vec3 velocity) {
	mVelocity = velocity;
}

void Particle::setColor(glm::vec4 color) {
	mColor = color;
}

void Particle::setLife(float life) {
	mLife = life;
}

void Particle::setFade(float fade) {
	mFade = fade;
}

bool Particle::isDead() {
	return mLife <= 0.0f;
}

void Particle::update(float deltaMillis) {
	mPosition += mVelocity * deltaMillis;
	mColor.a -= mFade * deltaMillis;
	mLife -= deltaMillis;
}

void Particle::setMesh(Renderable *renderable) {
	mRenderable = renderable;
}

void Particle::render() {
	mShaderProgram->setUniform("offset", mPosition);
	mShaderProgram->setUniform("color", mColor);
	mRenderable->render(0);
}

void Particle::setShaderProgram(ShaderProgram *shaderProgram) {
	mShaderProgram = shaderProgram;
}
