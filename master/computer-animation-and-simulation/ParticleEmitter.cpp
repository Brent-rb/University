//
// Created by brent on 17.08.18.
//

#include "ParticleEmitter.h"
#include "Particle.h"
#include "Help.h"

#include "Renderables/Square.h"
#include "OpenGLRenderer.h"

ParticleEmitter::ParticleEmitter(OpenGLRenderer *renderer) : GameObject(renderer) {
	setAmount(500);
	setSpread(10);
	setVelocity(10);
	setDirection(glm::vec3(0, 1, 0));
	setTexture(nullptr);
	setGravity(0);
	setLifetime(5);
	setFade(0.02);
	setColor(glm::vec4(1, 1, 1, 1));
	mMesh = new Square(renderer->getParticleShader()->getProgram(), glm::vec3(-1, -1, 0), glm::vec3(1, -1, 0), glm::vec3(1, 1, 0), glm::vec3(-1, 1, 0), glm::vec3(0, 0, -1));
}

void ParticleEmitter::setAmount(int amount) {
	mParticleAmount = amount;
	mParticles.clear();
	for(int i = 0; i < amount; i++) {
		createParticle();
	}
}

void ParticleEmitter::setSpread(float spread) {
	mSpread = spread;
}

void ParticleEmitter::setVelocity(float velocity) {
	mVelocity = velocity;
}

void ParticleEmitter::setDirection(glm::vec3 direction) {
	mDirection = direction;
}

void ParticleEmitter::setTexture(Texture *texture) {
	mParticleTexture = texture;
}

void ParticleEmitter::setGravity(float gravity) {
	mGravity = gravity;
}

void ParticleEmitter::setLifetime(float lifetime) {
	mLifetime = lifetime;
}

void ParticleEmitter::setColor(glm::vec4 color) {
	mColor = color;
}

void ParticleEmitter::setFade(float fade) {
	mFade = fade;
}

void ParticleEmitter::update(InputBuffer *keyBuffer, glm::vec3 cameraPosition, glm::vec3 cameraDirection,
                             float deltaMillis) {
	GameObject::update(keyBuffer, cameraPosition, cameraDirection, deltaMillis);
	for(int i = 0; i < mParticles.size(); i++) {
		if(mParticles[i].isDead()) {
			initParticle(i);
		}
	}
}

void ParticleEmitter::render(float deltaMillis, bool transform, glm::mat4 &transMatrix) {
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	mRenderer->useParticleShader();
	for(int i = 0; i < mParticles.size(); i++) {
		mParticles[i].render();
	}
	mRenderer->useNormalShader();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ParticleEmitter::createParticle() {
	mParticles.push_back(Particle());
	initParticle(mParticles.size() - 1);
}

void ParticleEmitter::initParticle(int index) {
	float xRandom = Help::random(-mSpread, mSpread);
	float yRandom = Help::random(-mSpread, mSpread);
	float zRandom = Help::random(-mSpread, mSpread);
	Particle& particle = mParticles[index];
	mDirection.y += mGravity;
	particle.setMesh(mMesh);
	particle.setVelocity((mDirection * (mVelocity * Help::random(0.5, 1.5))));
	particle.setColor(mColor);
	particle.setPosition(glm::vec3(xRandom, yRandom, zRandom));
	particle.setLife(mLifetime * Help::random(0.8, 1.2));
	particle.setFade(mFade * Help::random(0.8, 1.2));
	particle.setShaderProgram(mRenderer->getParticleShader());
}
