//
// Created by brent on 07.07.18.
//

#ifndef CAS_FLUIDGRID_H
#define CAS_FLUIDGRID_H

#include "../GameObject.h";
#include "../Textures/SolidColorTexture.h"
#include "../Renderables/Cube.h"
#include "../Renderables/Model.h"

#include <map>

enum Property {PRESSURE, HEAT, INK, PROPERTIES_SIZE};


class FluidGrid: public GameObject {
public:
	FluidGrid(OpenGLRenderer *renderer, Renderable *renderable, float width, float height, float depth, float dimensions, int wallResolution);

	void createGrid(float width, float height, float depth, float dimensions, int wallResolution);

	/*
	void createNeighbours();
	void createCells();
	 */

	void clear();

	void
	update(InputBuffer *keyBuffer, glm::vec3 cameraPosition, glm::vec3 cameraDirection, float deltaMillis) override;

	void render(float deltaMillis, bool transform, glm::mat4& transMatrix);

protected:
	void update(float deltaMillis);

	/*
	void updatePoint(float deltaMillis, int x, int y, int z);
	void updatePoint2(float deltaMillis, int x, int y, int z);
	void updatePoint3(float deltaMillis, int x, int y, int z);
	void swapValues(int x, int y, int z);

	void initNeighbours(int x, int y, int z);
	void initCell(int x, int y, int z);


	FluidCell* getCell(float x, float y, float z);
	FluidCell* getCell(glm::vec3 position);
	 */

	int getLength();
	int getWallLength();
	int getIndex(int x, int y, int z);
	int getPropertyIndex(Property property, int x, int y, int z);
	int getPropertyIndex(Property property, int index);
	glm::vec3 getCordinates(int index);
	glm::vec3 getWallCordinates(int index);
	glm::vec3 getPropertyCordinates(Property property, int index);
	glm::vec3 getTarget(int& x, int& y, int& z, int& index, float scale);

	void diffusion(Property property, int x, int y, int z, float scale = 1.0f);
	void diffusion(int x, int y, int z, float scale = 1.0f);

	void advection(Property property, int x, int y, int z, float scale = 1.0f);
	void advection(int x, int y, int z, float scale = 1.0f);

	void prepareReverseAdvection(int x, int y, int z, float scale = 1.0f);
	void reverseAdvection(Property property, int x, int y, int z);
	void reverseAdvection(int x, int y, int z);

	void pressureAcceleration(float scale);
	void velocityFriction(float scale);

	void copyProperties(float* from, float* to);
	void copyVelcities(glm::vec3* from, glm::vec3* to);

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
	int m_wallResolution;

	float m_cellDimension;

	glm::vec3* m_currentVelocities;
	glm::vec3* m_newVelocities;
	glm::vec3* m_reverseAdvectionVelocities;
	float* m_currentProperties;
	float* m_newProperties;
	float* m_reverseAdvectionDemand;
	float* m_reverseAdvectionFractions;
	int* m_reverseAdvectionTargets;
	Cube* m_cube;
	Model* m_ball;
	GameObject** m_cubes;
	GameObject** m_balls;
	bool* m_blocked;

	SolidColorTexture* m_texture;

	float m_diffusionScale;
	float m_advectionScale;
	float m_pressureScale;

	float m_velocityFrictionA;
	float m_velocityFrictionB;
	float m_velocityFrictionC;

	bool m_simulating;
};


#endif //CAS_FLUIDGRID_H
