//
// Created by brent on 07.07.18.
//

#ifndef CAS_FLUIDPOINT_H
#define CAS_FLUIDPOINT_H

#include <glm/vec3.hpp>
#include <vector>
#include "../Renderables/Square.h"
#include "FluidCell.h"
#include "../Renderables/Cube.h"

class Texture;

enum Property {PRESSURE_CURRENT, PRESSURE_NEW, HEAT_CURRENT, HEAT_NEW, INK_CURRENT, INK_NEW, PROPERTIES_SIZE};

class FluidPoint {
public:
	FluidPoint();

	void init(GLuint shaderProgram, float x, float y, float z, float dimension);

	void diffusion(Property oldProperty, Property newProperty, float scale, FluidCell* neighbours);
	void velocityDiffusion(float scale, FluidCell* neighbours);

	void forwardAdvection(Property oldProperty, Property newProperty, float cellDiameter, float scale, FluidCell* target);
	void forwardVelocityAdvection(float cellDiameter, float scale, FluidCell* target);

	float getProperty(Property property);
	void setProperty(Property property, float value);
	void addProperty(Property property, float value);

	glm::vec3 getCurrentVelocity();
	void setCurrentVelocity(float x, float y, float z);
	void setCurrentVelocity(glm::vec3 velocity);
	void addCurrentVelocity(glm::vec3 velocity);

	glm::vec3 getNewVelocity();
	void setNewVelocity(float x, float y, float z);
	void setNewVelocity(glm::vec3 velocity);
	void addNewVelocity(glm::vec3 velocity);

	glm::vec3 getPosition();
	void setPosition(float x, float y, float z);
	void setPosition(glm::vec3 position);

	float getX();
	void setX(float x);
	float getY();
	void setY(float y);
	float getZ();
	void setZ(float z);

	void setTexture(Texture* texture);
	void render(float millis, glm::mat4& transMatrix);

private:
	glm::vec3 m_position;
	glm::vec3 m_currentVelocity;
	glm::vec3 m_newVelocity;

	std::vector<float> m_properties;

	Cube* m_cube;
};


#endif //CAS_FLUIDPOINT_H
