//
// Created by brent on 17.08.18.
//

#ifndef CAS_PARTICLEEMITTER_H
#define CAS_PARTICLEEMITTER_H

#include "GameObject.h"

class Particle;
class Texture;
class Square;

class ParticleEmitter: public GameObject {
public:
	ParticleEmitter(OpenGLRenderer* renderer);

	void setAmount(int amount);
	void setSpread(float spread);
	void setVelocity(float velocity);
	void setDirection(glm::vec3 direction);
	void setTexture(Texture* texture);
	void setGravity(float gravity);
	void setLifetime(float lifetime);
	void setColor(glm::vec4 color);
	void setFade(float fade);

	void
	update(InputBuffer *keyBuffer, glm::vec3 cameraPosition, glm::vec3 cameraDirection, float deltaMillis) override;

protected:
	void render(float deltaMillis, bool transform, glm::mat4 &transMatrix) override;
	void createParticle();
	void initParticle(int index);


private:
	std::vector<Particle> mParticles;
	Texture* mParticleTexture;
	Square* mMesh;

	int mParticleAmount;
	float mSpread;
	float mGravity;
	float mVelocity;
	float mLifetime;
	float mFade;
	glm::vec3 mDirection;
	glm::vec4 mColor;
};


#endif //CAS_PARTICLEEMITTER_H
