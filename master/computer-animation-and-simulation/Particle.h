//
// Created by brent on 17.08.18.
//

#ifndef CAS_PARTICLE_H
#define CAS_PARTICLE_H


#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

class Renderable;
class ShaderProgram;

class Particle {
public:
	Particle();

	void setMesh(Renderable* renderable);

	void setPosition(glm::vec3 position);
	void setVelocity(glm::vec3 velocity);

	void setColor(glm::vec4 color);
	void setLife(float life);

	void setFade(float fade);

	void setShaderProgram(ShaderProgram* shaderProgram);

	bool isDead();

	void update(float deltaMillis);

	void render();

protected:
	glm::vec3 mPosition;
	glm::vec3 mVelocity;
	glm::vec4 mColor;

	float mLife;
	float mFade;

	Renderable* mRenderable;
	ShaderProgram* mShaderProgram;
};


#endif //CAS_PARTICLE_H
