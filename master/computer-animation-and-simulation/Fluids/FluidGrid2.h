//
// Created by brent on 21.07.18.
//

#ifndef CAS_FLUIDGRID2_H
#define CAS_FLUIDGRID2_H


#include "../OpenGLRenderer.h"
#include "../Renderables/Cube.h"
#include "../Textures/SolidColorTexture.h"
#include "../GameObject.h"

enum Property {PRESSURE, PROPERTIES_SIZE};

class FluidGrid2: public GameObject {
public:
	FluidGrid2(OpenGLRenderer *renderer, Renderable *renderable, float width, float height, float depth, float dimensions);

	void createGrid(float width, float height, float depth, float dimensions);

	void clear();

	void update(InputBuffer *keyBuffer, float deltaMillis) override;

	void render(float deltaMillis, bool transform, glm::mat4& transMatrix);

protected:
	void update(float deltaMillis);
	void velocityStep(float deltaMillis);
	void densityStep(float deltaMillis);

	int getLength();
	int getIndex(int x, int y, int z);
	int getPropertyIndex(Property property, int x, int y, int z);
	int getPropertyIndex(Property property, int index);
	glm::vec3 getCordinates(int index);
	glm::vec3 getPropertyCordinates(Property property, int index);
	glm::vec3 getTarget(int& x, int& y, int& z, int& index, float scale);

	void diffusion(int iterations, float deltaMillis);
	void diffusionVelocity(int itertaions, float deltaMillis);

	void advection(float deltaMillis);
	void advectionVelocity(float deltaMillis);

	void project(float deltaMillis);

	void copyProperties(float* from, float* to);
	void copyVelcities(glm::vec3* from, glm::vec3* to);

	void addSource(glm::vec3* from, glm::vec3* to, float deltaMillis);
	void curl();
	void vorticityConfinement();


	void swap();
	void swapProperties();
	void swapVelocity();
	void swapReverseAdvectionVelocity();

private:
	int calculateIndex(int x, int y, int z);

private:
	float m_width;
	float m_height;
	float m_depth;

	int m_widthBlocks;
	int m_heightBlocks;
	int m_depthBlocks;

	float m_cellDimension;

	glm::vec3* m_currentVelocities;
	glm::vec3* m_newVelocities;
	glm::vec3* m_reverseAdvectionVelocities;
	glm::vec3* m_curls;
	float* m_currentProperties;
	float* m_newProperties;
	float* m_div;
	float* m_p;

	Cube** m_cubes;
	SolidColorTexture* m_texture;

	float m_diffusionScale;
	float m_advectionScale;
};


#endif //CAS_FLUIDGRID2_H
