//
// Created by brent on 07.07.18.
//

#include <iostream>
#include "FluidGrid.h"
#include "FluidCell.h"
#include "../Renderables/Square.h"
#include "../OpenGLRenderer.h"
#include "../InputBuffer/InputBuffer.h"
#include "../Help.h"

FluidGrid::FluidGrid(OpenGLRenderer *renderer, Renderable *renderable, float width, float height, float depth, float dimensions, int wallResolution): GameObject(renderer, renderable) {
	/*
	m_grid = nullptr;
	m_cells = nullptr;
	m_neighbours = nullptr;
	 */
	m_currentVelocities = nullptr;
	m_newVelocities = nullptr;
	m_reverseAdvectionVelocities = nullptr;
	m_currentProperties = nullptr;
	m_newProperties = nullptr;
	m_cubes = nullptr;

	m_reverseAdvectionTargets = nullptr;
	m_reverseAdvectionFractions = nullptr;
	m_reverseAdvectionDemand = nullptr;

	m_simulating = false;

	m_diffusionScale = 1.0f;
	m_advectionScale = 1.0f;
	m_pressureScale = 1.0f;

	m_velocityFrictionA = 0.8f;
	m_velocityFrictionB = 0.03f;
	m_velocityFrictionC = 0.001f;
	m_cube = nullptr;
	m_balls = nullptr;
	m_blocked = nullptr;

	m_texture = new SolidColorTexture(255, 255, 255);
	m_ball = new Model(mRenderer->getShaderProgram(), std::string("/home/brent/Documents/CAS/Objects/ball.obj"));
	createGrid(width, height, depth, dimensions, wallResolution);
}

void FluidGrid::createGrid(float width, float height, float depth, float dimensions, int wallResolution) {
	int widthBlocks = (int) floor(width / dimensions), heightBlocks = (int) floor(height/ dimensions), depthBlocks = (int) floor(depth / dimensions);
	if(!(Help::equals(widthBlocks, width / dimensions) && Help::equals(heightBlocks, height / dimensions) && Help::equals(depthBlocks, depth / dimensions))) {
		std::cout << "Error width, height or depth is not properly divisible by " << dimensions << std::endl;
		return;
	}

	clear();
	m_width = width;
	m_height = height;
	m_depth = depth;
	m_widthBlocks = widthBlocks;
	m_heightBlocks = heightBlocks;
	m_depthBlocks = depthBlocks;
	m_cellDimension = dimensions;
	m_wallResolution = wallResolution;
	std::cout << "Created grid with " << m_widthBlocks * m_heightBlocks * m_depthBlocks << " blocks." << std::endl;

	int index = getIndex(0, 1, 2);
	glm::vec3 cords = getCordinates(index);
	if(!(Help::equals(cords.x, 0.0f) && Help::equals(cords.y, 1.0f) && Help::equals(cords.z, 2.0f))) {
		std::cout << "Your fuctions sucks: " << index << " " << cords.x << " " << cords.y << " " << cords.z << std::endl;
		return;
	}
	index = getPropertyIndex(INK, 0, 1, 2);
	cords = getPropertyCordinates(INK, index);
	if(!(Help::equals(cords.x, 0.0f) && Help::equals(cords.y, 1.0f) && Help::equals(cords.z, 2.0f))) {
		std::cout << "Your fuctions sucks: " << index << " " << cords.x << " " << cords.y << " " << cords.z << std::endl;
		return;
	}

	m_currentVelocities = new glm::vec3[getLength()];
	m_newVelocities = new glm::vec3[getLength()];
	m_reverseAdvectionVelocities = new glm::vec3[getLength()];
	m_currentProperties = new float[getLength() * PROPERTIES_SIZE];
	m_newProperties = new float[getLength() * PROPERTIES_SIZE];
	m_cube = new Cube(mRenderer->getShaderProgram()->getProgram(), glm::vec3(), sqrt(2* ((m_cellDimension / 2.0) * (m_cellDimension / 2.0))), m_texture);
	m_reverseAdvectionDemand = new float[getLength()];
	m_reverseAdvectionFractions = new float[getLength() * 8];
	m_reverseAdvectionTargets = new int[getLength() * 8];
	m_cubes = new GameObject*[getLength()];
	m_balls = new GameObject*[getWallLength()];
	m_blocked = new bool[getWallLength()];

	memset(m_currentProperties, 0, sizeof(float) * getLength() * PROPERTIES_SIZE);
	memset(m_newProperties, 0, sizeof(float) * getLength() * PROPERTIES_SIZE);

	for(int i = 0; i < getLength(); i++) {
		m_cubes[i] = new GameObject(mRenderer, m_cube);
		glm::vec3 position = getCordinates(i) * m_cellDimension;
		m_cubes[i]->setLocation(position.x, position.y, position.z);
		m_cubes[i]->setColor(255.0f, 0.0f, 0.0f);
	}

	glm::vec3 position;
	for(int i = 0; i < getWallLength(); i++) {
		m_blocked[i] = false;
		m_balls[i] = new GameObject(mRenderer, m_ball);
		position = getWallCordinates(i) * (float) m_wallResolution * m_cellDimension;
		m_balls[i]->setLocation(position.x, position.y, position.z);
		m_balls[i]->setScale(0.1f, 0.1f, 0.1f);
		m_balls[i]->setOpacity(0.5f);
	}


	int x = m_widthBlocks / 2;
	int y = m_heightBlocks / 2;
	//int z = m_depthBlocks / 2;
	for(int z = 0; z < m_depthBlocks; z++) {
		index = getPropertyIndex(INK, x, y, z);
		int velIndex = getIndex(x, y, z);
		m_currentProperties[index] = 20.0f;
		m_currentProperties[getPropertyIndex(PRESSURE, x, y, z)] = 0.2f;
		m_currentVelocities[velIndex] = glm::vec3(-20.0f, 0.0f, 0.0f);
	}

}

void FluidGrid::clear() {
	if(m_currentProperties != nullptr) {
		delete[] m_currentProperties;
		m_currentProperties = nullptr;
	}
	if(m_currentVelocities != nullptr) {
		delete[] m_currentVelocities;
		m_currentVelocities = nullptr;
	}
	if(m_newVelocities != nullptr) {
		delete[] m_newVelocities;
		m_newVelocities = nullptr;
	}
	if(m_newProperties != nullptr) {
		delete[] m_newProperties;
		m_newProperties = nullptr;
	}
	if(m_reverseAdvectionFractions != nullptr) {
		delete[] m_reverseAdvectionFractions;
		m_reverseAdvectionFractions = nullptr;
	}
	if(m_reverseAdvectionDemand != nullptr) {
		delete[] m_reverseAdvectionDemand;
		m_reverseAdvectionDemand = nullptr;
	}
	if(m_reverseAdvectionTargets != nullptr) {
		delete[] m_reverseAdvectionTargets;
		m_reverseAdvectionTargets = nullptr;
	}
	if(m_reverseAdvectionVelocities != nullptr) {
		delete[] m_reverseAdvectionVelocities;
		m_reverseAdvectionVelocities = nullptr;
	}
	if(m_cubes != nullptr) {
		for(int i = 0; i < getLength(); i++) {
			delete m_cubes[i];
		}
		delete[] m_cubes;
	}
	if(m_balls != nullptr) {
		for(int i = 0; i < getLength(); i++) {
			delete m_balls[i];
		}
		delete[] m_balls;
	}
	if(m_blocked != nullptr) {
		delete[] m_blocked;
	}
}

void FluidGrid::render(float deltaMillis, bool transform, glm::mat4 &transMatrix) {
	glm::mat4 modelMatrix = (transform ? transMatrix * getModelMatrix() : getModelMatrix());
	for(int i = 0; i < getWallLength(); i++) {
		m_balls[i]->render(deltaMillis, modelMatrix);
	}

	{
		for(int i = 0; i < getLength(); i++) {
			float ink = m_currentProperties[getPropertyIndex(INK, i)];
			if (ink > 0.001f) {
				m_cubes[i]->setOpacity(ink);
				m_cubes[i]->render(deltaMillis, modelMatrix);
			}
		}
	}
	//if(!m_simulating) {

	//}

}

void FluidGrid::update(float deltaMillis) {
	int x, y, z;
	deltaMillis /= 1000.0f;

	std::cout << "FPS: " << 1.0 / deltaMillis << std::endl;
	/*
	m_currentVelocities[getIndex(m_widthBlocks / 2, 0, m_depthBlocks / 2)] = glm::vec3(0, 10.0f, 0.0f);
	m_currentProperties[getPropertyIndex(INK, m_widthBlocks / 2, 0, m_depthBlocks / 2)] = 0.2f;
	m_currentProperties[getPropertyIndex(PRESSURE, m_widthBlocks / 2, 0, m_depthBlocks / 2)] = .2f;

	*/
	pressureAcceleration(m_pressureScale * deltaMillis);
	//velocityFriction(deltaMillis);

	for(int index = 0; index < getLength(); index++) {
		glm::vec3 cords = getCordinates(index);
		x = (int) cords.x;
		y = (int) cords.y;
		z = (int) cords.z;

		diffusion(x, y, z, m_diffusionScale * deltaMillis * m_cellDimension);
		diffusion(PRESSURE, x, y, z, m_diffusionScale * deltaMillis * m_cellDimension);
		//diffusion(HEAT, x, y, z, m_diffusionScale * deltaMillis);
		diffusion(INK, x, y, z, m_diffusionScale * deltaMillis * m_cellDimension);
	}

	copyProperties(m_newProperties, m_currentProperties);
	copyVelcities(m_newVelocities, m_currentVelocities);
	memset(m_reverseAdvectionDemand, 0, sizeof(float) * getLength());

	for(int index = 0; index < getLength(); index++) {
		glm::vec3 cords = getCordinates(index);
		x = (int) cords.x;
		y = (int) cords.y;
		z = (int) cords.z;

		advection(INK, x, y, z, m_advectionScale * deltaMillis * m_cellDimension);
		advection(PRESSURE, x, y, z, m_advectionScale * deltaMillis * m_cellDimension);
		advection(x, y, z, m_advectionScale * deltaMillis * m_cellDimension);
		prepareReverseAdvection(x, y, z, m_advectionScale * deltaMillis * m_cellDimension);
	}
	copyProperties(m_newProperties, m_currentProperties);
	copyVelcities(m_newVelocities, m_reverseAdvectionVelocities);
	//copyVelcities(m_newVelocities, m_currentVelocities);

	for(int index = 0; index < getLength(); index++) {
		glm::vec3 cords = getCordinates(index);
		x = (int) cords.x;
		y = (int) cords.y;
		z = (int) cords.z;

		reverseAdvection(INK, x, y, z);
		//other properties
		reverseAdvection(x, y, z);
		reverseAdvection(PRESSURE, x, y, z);
	}

	//swapProperties();
	swapReverseAdvectionVelocity();
	swapProperties();
}

int FluidGrid::getLength() {
	return m_widthBlocks * m_heightBlocks * m_depthBlocks;
}

int FluidGrid::getIndex(int x, int y, int z) {
	return x + y * m_widthBlocks + z * m_widthBlocks * m_heightBlocks;
}

int FluidGrid::getPropertyIndex(Property property, int x, int y, int z) {
	return (property * getLength()) + getIndex(x, y, z);
}

int FluidGrid::getPropertyIndex(Property property, int index) {
	return (property * getLength()) + index;
}

glm::vec3 FluidGrid::getCordinates(int index) {
	int z = index / (m_widthBlocks * m_heightBlocks);
	int temp = index % (m_widthBlocks * m_heightBlocks);
	int y = temp / m_widthBlocks;
	int x = temp % m_widthBlocks;
	return glm::vec3(x, y, z);
}

glm::vec3 FluidGrid::getWallCordinates(int index) {
	int z = index / ((m_widthBlocks / m_wallResolution) * (m_heightBlocks / m_wallResolution));
	int temp = index % ((m_widthBlocks / m_wallResolution) * (m_heightBlocks / m_wallResolution));
	int y = temp / (m_widthBlocks / m_wallResolution);
	int x = temp % (m_widthBlocks / m_wallResolution);
	return glm::vec3(x, y, z);
}

glm::vec3 FluidGrid::getPropertyCordinates(Property property, int index) {
	index -= property * getLength();
	int z = index / (m_widthBlocks * m_heightBlocks);
	index %= (m_widthBlocks * m_heightBlocks);
	int y = index / m_widthBlocks;
	int x = index % m_widthBlocks;
	return glm::vec3(x, y, z);
}

glm::vec3 FluidGrid::getTarget(int& x, int& y, int& z, int& index, float scale) {
	glm::vec3 velocity = m_currentVelocities[index];
	glm::vec3 position(x, y, z);
	return position + (velocity * scale);
}

int FluidGrid::calculateIndex(int x, int y, int z) {
	return 0;
}

void FluidGrid::diffusion(Property property, int x, int y, int z, float scale) {
	int count = 0;
	float value = 0.0f;

	int centerIndex = getPropertyIndex(property, x, y, z);
	int xMin = x - 1, xMax = x + 1;
	int yMin = y - 1, yMax = y + 1;
	int zMin = z - 1, zMax = z + 1;

	if(xMin >= 0) {
		value += m_currentProperties[centerIndex - 1];
		count++;
	}
	if(xMax < m_widthBlocks) {
		value += m_currentProperties[centerIndex + 1];
		count++;
	}
	if(yMin >= 0) {
		value += m_currentProperties[centerIndex - m_widthBlocks];
		count++;
	}
	if(yMax < m_heightBlocks) {
		value += m_currentProperties[centerIndex + m_widthBlocks];
		count++;
	}
	if(zMin >= 0) {
		value += m_currentProperties[centerIndex - m_widthBlocks * m_heightBlocks];
		count++;
	}
	if(zMax < m_depthBlocks) {
		value += m_currentProperties[centerIndex + m_widthBlocks * m_heightBlocks];
		count++;
	}

	value -= count * m_currentProperties[centerIndex];
	m_newProperties[centerIndex] = m_currentProperties[centerIndex] + scale * value;
}

void FluidGrid::diffusion(int x, int y, int z, float scale) {
	int count = 0;
	glm::vec3 value;

	int centerIndex = getIndex(x, y, z);
	int xMin = x - 1, xMax = x + 1;
	int yMin = y - 1, yMax = y + 1;
	int zMin = z - 1, zMax = z + 1;

	if(xMin >= 0) {
		value += m_currentVelocities[centerIndex - 1];
		count++;
	}
	if(xMax < m_widthBlocks) {
		value += m_currentVelocities[centerIndex + 1];
		count++;
	}
	if(yMin >= 0) {
		value += m_currentVelocities[centerIndex - m_widthBlocks];
		count++;
	}
	if(yMax < m_heightBlocks) {
		value += m_currentVelocities[centerIndex + m_widthBlocks];
		count++;
	}
	if(zMin >= 0) {
		value += m_currentVelocities[centerIndex - m_widthBlocks * m_heightBlocks];
		count++;
	}
	if(zMax < m_depthBlocks) {
		value += m_currentVelocities[centerIndex + m_widthBlocks * m_heightBlocks];
		count++;
	}

	value -= m_currentVelocities[centerIndex] * (float)count;
	m_newVelocities[centerIndex] = m_currentVelocities[centerIndex] + scale * value;
}

void FluidGrid::advection(Property property, int x, int y, int z, float scale) {
	int index = getPropertyIndex(property, x, y, z);
	int velIndex = getIndex(x, y, z);
	glm::vec3 velocity = m_currentVelocities[velIndex];
	if(Help::equals(velocity.x, 0.0f) && Help::equals(velocity.y, 0.0f) && Help::equals(velocity.z, 0.0f))
		return;

	float originalValue = m_currentProperties[index];
	float deductedValue = 0;
	float value;

	glm::vec3 position = getTarget(x, y, z, velIndex, scale / m_cellDimension);


	int xMin = (int) floor(position.x), xMax = xMin + 1;
	int yMin = (int) floor(position.y), yMax = yMin + 1;
	int zMin = (int) floor(position.z), zMax = zMin + 1;

	if (xMin < 0) {
		xMin = 0;
		xMax = 1;
		position.x = xMin;
	}
	if (xMax >= m_widthBlocks) {
		xMax = m_widthBlocks - 1;
		xMin = m_widthBlocks - 2;
		position.x = xMax;
	}
	if (yMin < 0) {
		yMin = 0;
		yMax = 1;
		position.y = yMin;
	}
	if (yMax >= m_heightBlocks) {
		yMax = m_heightBlocks - 1;
		yMin = m_heightBlocks - 2;
		position.y = yMax;
	}
	if (zMin < 0) {
		zMin = 0;
		zMax = 1;
		position.z = zMin;
	}
	if (zMax >= m_depthBlocks) {
		zMax = m_depthBlocks - 1;
		zMin = m_depthBlocks - 2;
		position.z = zMax;
	}

	glm::vec3 fractions(position.x - xMin, position.y - yMin, position.z - zMin);
	value = originalValue * (1.0f - fractions.x) * (1.0f - fractions.y) * (1.0f - fractions.z);
	m_newProperties[getPropertyIndex(property, xMin, yMin, zMin)] += value;
	deductedValue -= value;

	value = originalValue *  (1.0f - fractions.x) * (1.0f - fractions.y) * fractions.z;
	m_newProperties[getPropertyIndex(property, xMin, yMin, zMax)] += value;
	deductedValue -= value;

	value = originalValue *  (1.0f - fractions.x) * (fractions.y) * (1.0f - fractions.z);
	m_newProperties[getPropertyIndex(property, xMin, yMax, zMin)] += value;
	deductedValue -= value;

	value = originalValue *  (1.0f - fractions.x) * (fractions.y) * fractions.z;
	m_newProperties[getPropertyIndex(property, xMin, yMax, zMax)] += value;
	deductedValue -= value;

	value = originalValue * (fractions.x) * (1.0f - fractions.y) * (1.0f - fractions.z);
	m_newProperties[getPropertyIndex(property, xMax, yMin, zMin)] += value;
	deductedValue -= value;

	value = originalValue *  (fractions.x) * (1.0f - fractions.y) * fractions.z;
	m_newProperties[getPropertyIndex(property, xMax, yMin, zMax)] += value;
	deductedValue -= value;

	value = originalValue *  (fractions.x) * (fractions.y) * (1.0f - fractions.z);
	m_newProperties[getPropertyIndex(property, xMax, yMax, zMin)] += value;
	deductedValue -= value;

	value = originalValue *  (fractions.x) * (fractions.y) * fractions.z;
	m_newProperties[getPropertyIndex(property, xMax, yMax, zMax)] += value;
	deductedValue -= value;

	if(x == 3 && y == 3) {
		//std::cout << "Deducted value: " << deductedValue << std::endl;
	}
	m_newProperties[index] += deductedValue;
}

void FluidGrid::advection(int x, int y, int z, float scale) {
	int index = getIndex(x, y, z);
	bool xZero = false, yZero = false, zZero = false;
	glm::vec3 velocity = m_currentVelocities[index];
	if(Help::equals(velocity.x, 0.0f) && Help::equals(velocity.y, 0.0f) && Help::equals(velocity.z, 0.0f))
		return;

	glm::vec3 originalValue = m_currentVelocities[index];
	glm::vec3 deductedValue;
	glm::vec3 value;

	glm::vec3 position = getTarget(x, y, z, index, scale / m_cellDimension);

	int xMin = (int) floor(position.x), xMax = xMin + 1;
	int yMin = (int) floor(position.y), yMax = yMin + 1;
	int zMin = (int) floor(position.z), zMax = zMin + 1;

	if (xMin < 0) {
		xMin = 0;
		xMax = 1;
		position.x = xMin;

		if(x == 0) {
			xZero = true;
		}
	}
	if (xMax >= m_widthBlocks) {
		xMax = m_widthBlocks - 1;
		xMin = m_widthBlocks - 2;
		position.x = xMax;

		if(x == m_widthBlocks - 1) {
			xZero = true;
		}
	}
	if (yMin < 0) {
		yMin = 0;
		yMax = 1;
		position.y = yMin;

		if(y == 0) {
			yZero = true;
		}
	}
	if (yMax >= m_heightBlocks) {
		yMax = m_heightBlocks - 1;
		yMin = m_heightBlocks - 2;
		position.y = yMax;

		if(y == m_heightBlocks - 1) {
			yZero = true;
		}
	}
	if (zMin < 0) {
		zMin = 0;
		zMax = 1;
		position.z = zMin;

		if(z == 0) {
			zZero = true;
		}
	}
	if (zMax >= m_depthBlocks) {
		zMax = m_depthBlocks - 1;
		zMin = m_depthBlocks - 2;
		position.z = zMax;

		if(z == m_depthBlocks - 1) {
			zZero = true;
		}
	}

	glm::vec3 fractions(position.x - xMin, position.y - yMin, position.z - zMin);
	value = originalValue * (1.0f - fractions.x) * (1.0f - fractions.y) * (1.0f - fractions.z);
	m_newVelocities[getIndex(xMin, yMin, zMin)] += value;
	deductedValue -= value;

	value = originalValue *  (1.0f - fractions.x) * (1.0f - fractions.y) * fractions.z;
	m_newVelocities[getIndex(xMin, yMin, zMax)] += value;
	deductedValue -= value;

	value = originalValue *  (1.0f - fractions.x) * (fractions.y) * (1.0f - fractions.z);
	m_newVelocities[getIndex(xMin, yMax, zMin)] += value;
	deductedValue -= value;

	value = originalValue *  (1.0f - fractions.x) * (fractions.y) * fractions.z;
	m_newVelocities[getIndex(xMin, yMax, zMax)] += value;
	deductedValue -= value;

	value = originalValue * (fractions.x) * (1.0f - fractions.y) * (1.0f - fractions.z);
	m_newVelocities[getIndex(xMax, yMin, zMin)] += value;
	deductedValue -= value;

	value = originalValue *  (fractions.x) * (1.0f - fractions.y) * fractions.z;
	m_newVelocities[getIndex(xMax, yMin, zMax)] += value;
	deductedValue -= value;

	value = originalValue *  (fractions.x) * (fractions.y) * (1.0f - fractions.z);
	m_newVelocities[getIndex(xMax, yMax, zMin)] += value;
	deductedValue -= value;

	value = originalValue *  (fractions.x) * (fractions.y) * fractions.z;
	m_newVelocities[getIndex(xMax, yMax, zMax)] += value;
	deductedValue -= value;

	m_newVelocities[index] += deductedValue;
	if(xZero) {
		m_newVelocities[index].x = 0;
	}
	if(yZero) {
		m_newVelocities[index].y = 0;
	}
	if(zZero) {
		m_newVelocities[index].z = 0;
	}
}

void FluidGrid::prepareReverseAdvection(int x, int y, int z, float scale) {
	int index = getIndex(x, y, z);
	int targetIndex = index * 8;
	glm::vec3 velocity = m_currentVelocities[index];
	if(Help::equals(velocity.x, 0.0f) && Help::equals(velocity.y, 0.0f) && Help::equals(velocity.z, 0.0f)) {
		m_reverseAdvectionTargets[targetIndex] = -1;
		return;
	}

	glm::vec3 position = getTarget(x, y, z, index, -scale / m_cellDimension);

	int xMin = (int) floor(position.x), xMax = (int) ceil(position.x);
	int yMin = (int) floor(position.y), yMax = (int) ceil(position.y);
	int zMin = (int) floor(position.z), zMax = (int) ceil(position.z);

	if(xMin >= 0 && yMin >= 0 && zMin >= 0 && xMax < m_widthBlocks && yMax < m_heightBlocks && zMax < m_depthBlocks) {
		glm::vec3 fractions(position.x - xMin, position.y - yMin, position.z - zMin);
		m_reverseAdvectionFractions[targetIndex] = (1.0f - fractions.x) * (1.0f - fractions.y) * (1.0f - fractions.z);
		m_reverseAdvectionTargets[targetIndex] = getIndex(xMin, yMin, zMin);
		m_reverseAdvectionDemand[m_reverseAdvectionTargets[targetIndex]] += m_reverseAdvectionFractions[targetIndex];

		m_reverseAdvectionFractions[targetIndex + 1] = (1.0f - fractions.x) * (1.0f - fractions.y) * fractions.z;
		m_reverseAdvectionTargets[targetIndex + 1] = getIndex(xMin, yMin, zMax);
		m_reverseAdvectionDemand[m_reverseAdvectionTargets[targetIndex + 1]] += m_reverseAdvectionFractions[targetIndex + 1];

		m_reverseAdvectionFractions[targetIndex + 2] = (1.0f - fractions.x) * (fractions.y) * (1.0f - fractions.z);
		m_reverseAdvectionTargets[targetIndex + 2] = getIndex(xMin, yMax, zMin);
		m_reverseAdvectionDemand[m_reverseAdvectionTargets[targetIndex + 2]] += m_reverseAdvectionFractions[targetIndex + 2];

		m_reverseAdvectionFractions[targetIndex + 3] = (1.0f - fractions.x) * (fractions.y) * fractions.z;
		m_reverseAdvectionTargets[targetIndex + 3] = getIndex(xMin, yMax, zMax);
		m_reverseAdvectionDemand[m_reverseAdvectionTargets[targetIndex + 3]] += m_reverseAdvectionFractions[targetIndex + 3];

		m_reverseAdvectionFractions[targetIndex + 4] = (fractions.x) * (1.0f - fractions.y) * (1.0f - fractions.z);
		m_reverseAdvectionTargets[targetIndex + 4] = getIndex(xMax, yMin, zMin);
		m_reverseAdvectionDemand[m_reverseAdvectionTargets[targetIndex + 4]] += m_reverseAdvectionFractions[targetIndex + 4];

		m_reverseAdvectionFractions[targetIndex + 5] = (fractions.x) * (1.0f - fractions.y) * fractions.z;
		m_reverseAdvectionTargets[targetIndex + 5] = getIndex(xMax, yMin, zMax);
		m_reverseAdvectionDemand[m_reverseAdvectionTargets[targetIndex + 5]] += m_reverseAdvectionFractions[targetIndex + 5];

		m_reverseAdvectionFractions[targetIndex + 6] = (fractions.x) * (fractions.y) * (1.0f - fractions.z);
		m_reverseAdvectionTargets[targetIndex + 6] = getIndex(xMax, yMax, zMin);
		m_reverseAdvectionDemand[m_reverseAdvectionTargets[targetIndex + 6]] += m_reverseAdvectionFractions[targetIndex + 6];

		m_reverseAdvectionFractions[targetIndex + 7] = (fractions.x) * (fractions.y) * fractions.z;
		m_reverseAdvectionTargets[targetIndex + 7] = getIndex(xMax, yMax, zMax);
		m_reverseAdvectionDemand[m_reverseAdvectionTargets[targetIndex + 7]] += m_reverseAdvectionFractions[targetIndex + 7];
	}
	else {
		m_reverseAdvectionTargets[targetIndex] = -1;
	}
}

void FluidGrid::reverseAdvection(Property property, int x, int y, int z) {
	int propertyIndex = getPropertyIndex(property, x, y, z);
	int index = getIndex(x, y, z);
	int targetIndex = index * 8;

	if(m_reverseAdvectionTargets[targetIndex] != -1) {
		int propertyOffset = getLength() * property;
		int target0 = m_reverseAdvectionTargets[targetIndex] + propertyOffset, target1 = m_reverseAdvectionTargets[targetIndex + 1] + propertyOffset;
		int target2 = m_reverseAdvectionTargets[targetIndex + 2] + propertyOffset, target3 = m_reverseAdvectionTargets[targetIndex + 3] + propertyOffset;
		int target4 = m_reverseAdvectionTargets[targetIndex + 4] + propertyOffset, target5 = m_reverseAdvectionTargets[targetIndex + 5] + propertyOffset;
		int target6 = m_reverseAdvectionTargets[targetIndex + 6] + propertyOffset, target7 = m_reverseAdvectionTargets[targetIndex + 7] + propertyOffset;

		float divider0 = m_reverseAdvectionFractions[targetIndex] / (m_reverseAdvectionDemand[target0] < 1.0f ? 1.0f : m_reverseAdvectionDemand[target0]);
		float divider1 = m_reverseAdvectionFractions[targetIndex + 1] / (m_reverseAdvectionDemand[target1] < 1.0f ? 1.0f : m_reverseAdvectionDemand[target1]);
		float divider2 = m_reverseAdvectionFractions[targetIndex + 2] / (m_reverseAdvectionDemand[target2] < 1.0f ? 1.0f : m_reverseAdvectionDemand[target2]);
		float divider3 = m_reverseAdvectionFractions[targetIndex + 3] / (m_reverseAdvectionDemand[target3] < 1.0f ? 1.0f : m_reverseAdvectionDemand[target3]);
		float divider4 = m_reverseAdvectionFractions[targetIndex + 4] / (m_reverseAdvectionDemand[target4] < 1.0f ? 1.0f : m_reverseAdvectionDemand[target4]);
		float divider5 = m_reverseAdvectionFractions[targetIndex + 5] / (m_reverseAdvectionDemand[target5] < 1.0f ? 1.0f : m_reverseAdvectionDemand[target5]);
		float divider6 = m_reverseAdvectionFractions[targetIndex + 6] / (m_reverseAdvectionDemand[target6] < 1.0f ? 1.0f : m_reverseAdvectionDemand[target6]);
		float divider7 = m_reverseAdvectionFractions[targetIndex + 7] / (m_reverseAdvectionDemand[target7] < 1.0f ? 1.0f : m_reverseAdvectionDemand[target7]);


		m_newProperties[propertyIndex] += m_currentProperties[target0] * (divider0) +
		                                  m_currentProperties[target1] * (divider1) +
		                                  m_currentProperties[target2] * (divider2) +
		                                  m_currentProperties[target3] * (divider3) +
		                                  m_currentProperties[target4] * (divider4) +
		                                  m_currentProperties[target5] * (divider5) +
		                                  m_currentProperties[target6] * (divider6) +
		                                  m_currentProperties[target7] * (divider7);

		m_newProperties[target0] -= m_currentProperties[target0] * divider0;
		m_newProperties[target1] -= m_currentProperties[target1] * divider1;
		m_newProperties[target2] -= m_currentProperties[target2] * divider2;
		m_newProperties[target3] -= m_currentProperties[target3] * divider3;
		m_newProperties[target4] -= m_currentProperties[target4] * divider4;
		m_newProperties[target5] -= m_currentProperties[target5] * divider5;
		m_newProperties[target6] -= m_currentProperties[target6] * divider6;
		m_newProperties[target7] -= m_currentProperties[target7] * divider7;
	}
}

void FluidGrid::reverseAdvection(int x, int y, int z) {
	int index = getIndex(x, y, z);
	int targetIndex = index * 8;

	if(m_reverseAdvectionTargets[targetIndex] != -1) {
		int target0 = m_reverseAdvectionTargets[targetIndex], target1 = m_reverseAdvectionTargets[targetIndex + 1];
		int target2 = m_reverseAdvectionTargets[targetIndex + 2], target3 = m_reverseAdvectionTargets[targetIndex + 3];
		int target4 = m_reverseAdvectionTargets[targetIndex + 4], target5 = m_reverseAdvectionTargets[targetIndex + 5];
		int target6 = m_reverseAdvectionTargets[targetIndex + 6], target7 = m_reverseAdvectionTargets[targetIndex + 7];

		float divider0 = m_reverseAdvectionFractions[targetIndex] / (m_reverseAdvectionDemand[target0] < 1.0f ? 1.0f : m_reverseAdvectionDemand[target0]);
		float divider1 = m_reverseAdvectionFractions[targetIndex + 1] / (m_reverseAdvectionDemand[target1] < 1.0f ? 1.0f : m_reverseAdvectionDemand[target1]);
		float divider2 = m_reverseAdvectionFractions[targetIndex + 2] / (m_reverseAdvectionDemand[target2] < 1.0f ? 1.0f : m_reverseAdvectionDemand[target2]);
		float divider3 = m_reverseAdvectionFractions[targetIndex + 3] / (m_reverseAdvectionDemand[target3] < 1.0f ? 1.0f : m_reverseAdvectionDemand[target3]);
		float divider4 = m_reverseAdvectionFractions[targetIndex + 4] / (m_reverseAdvectionDemand[target4] < 1.0f ? 1.0f : m_reverseAdvectionDemand[target4]);
		float divider5 = m_reverseAdvectionFractions[targetIndex + 5] / (m_reverseAdvectionDemand[target5] < 1.0f ? 1.0f : m_reverseAdvectionDemand[target5]);
		float divider6 = m_reverseAdvectionFractions[targetIndex + 6] / (m_reverseAdvectionDemand[target6] < 1.0f ? 1.0f : m_reverseAdvectionDemand[target6]);
		float divider7 = m_reverseAdvectionFractions[targetIndex + 7] / (m_reverseAdvectionDemand[target7] < 1.0f ? 1.0f : m_reverseAdvectionDemand[target7]);

		m_reverseAdvectionVelocities[index] += m_newVelocities[target0] * (divider0) +
		                                       m_newVelocities[target1] * (divider1) +
		                                       m_newVelocities[target2] * (divider2) +
		                                       m_newVelocities[target3] * (divider3) +
		                                       m_newVelocities[target4] * (divider4) +
		                                       m_newVelocities[target5] * (divider5) +
		                                       m_newVelocities[target6] * (divider6) +
		                                       m_newVelocities[target7] * (divider7);

		m_reverseAdvectionVelocities[target0] -= m_newVelocities[target0] * divider0;
		m_reverseAdvectionVelocities[target1] -= m_newVelocities[target1] * divider1;
		m_reverseAdvectionVelocities[target2] -= m_newVelocities[target2] * divider2;
		m_reverseAdvectionVelocities[target3] -= m_newVelocities[target3] * divider3;
		m_reverseAdvectionVelocities[target4] -= m_newVelocities[target4] * divider4;
		m_reverseAdvectionVelocities[target5] -= m_newVelocities[target5] * divider5;
		m_reverseAdvectionVelocities[target6] -= m_newVelocities[target6] * divider6;
		m_reverseAdvectionVelocities[target7] -= m_newVelocities[target7] * divider7;
	}
}

void FluidGrid::pressureAcceleration(float scale) {
	int x, y, z;
	glm::vec3 temp;
	float forceX, forceY, forceZ, pressure;

	for(int i = 0; i < getLength(); i++) {
		temp = getCordinates(i);
		x = (int) temp.x;
		y = (int) temp.y;
		z = (int) temp.z;

		if(x < m_widthBlocks - 1 && y < m_heightBlocks - 1 && z < m_depthBlocks - 1) {
			pressure = m_currentProperties[getPropertyIndex(PRESSURE, i)];
			forceX = (pressure - m_currentProperties[getPropertyIndex(PRESSURE, x + 1, y, z)]) * scale;
			forceY = (pressure - m_currentProperties[getPropertyIndex(PRESSURE, x, y + 1, z)]) * scale;
			forceZ = (pressure - m_currentProperties[getPropertyIndex(PRESSURE, x, y, z + 1)]) * scale;

			m_currentVelocities[i] += glm::vec3(forceX, forceY, forceZ);
			m_currentVelocities[i + 1].x += forceX;
			m_currentVelocities[i + m_widthBlocks].y += forceY;
			m_currentVelocities[i + m_widthBlocks * m_heightBlocks].z += forceZ;
		}
	}
}

void FluidGrid::velocityFriction(float scale) {
	glm::vec3 velocity;
	float length, lengthRoot, sign;

	for(int i = 0; i < getLength(); i++) {
		velocity = m_currentVelocities[i];

		/*length = velocity.length();
		lengthRoot = sqrtf(length);
		if(length < 0.0f) {
			length = -length;
			sign = -1.0f;
		}
		else {
			sign = 1.0f;
		}

		lengthRoot -= scale * (m_velocityFrictionA * length + m_velocityFrictionB * lengthRoot + m_velocityFrictionC);
		if(lengthRoot < 0.0f)
			lengthRoot = 0.0f;

		velocity = glm::normalize(velocity) * lengthRoot;
		 */
		m_currentVelocities[i] = velocity * 0.99f;
	}
}

void FluidGrid::swap() {
	swapProperties();
	swapVelocity();
}

void FluidGrid::swapProperties() {
	float* currentProperties = m_currentProperties;
	m_currentProperties = m_newProperties;
	m_newProperties = currentProperties;
}

void FluidGrid::swapVelocity() {
	glm::vec3* currentVelocities = m_currentVelocities;
	m_currentVelocities = m_newVelocities;
	m_newVelocities = currentVelocities;
}

void FluidGrid::swapReverseAdvectionVelocity() {
	glm::vec3* currentVelocities = m_currentVelocities;
	m_currentVelocities = m_reverseAdvectionVelocities;
	m_reverseAdvectionVelocities = currentVelocities;
}

void FluidGrid::copyProperties(float *from, float *to) {
	memcpy(to, from, sizeof(float) * getLength() * PROPERTIES_SIZE);
}

void FluidGrid::copyVelcities(glm::vec3 *from, glm::vec3 *to) {
	memcpy(to, from, sizeof(glm::vec3) * getLength());
}

int FluidGrid::getWallLength() {
	return (m_widthBlocks / m_wallResolution) * (m_heightBlocks / m_wallResolution) * (m_depthBlocks / m_wallResolution);
}

/*
void FluidGrid::createGrid(float width, float height, float depth, int widthBlocks, int heightBlocks, int depthBlocks) {
	float dimensionWidth = width / widthBlocks, dimensionHeight = height / heightBlocks, dimensionDepth = depth / depthBlocks;
	if(!(Help::equals(dimensionWidth, dimensionHeight) && Help::equals(dimensionHeight, dimensionDepth))) {
		std::cout << "Error: " << "Cell dimensions are not even: " << dimensionWidth << " " << dimensionHeight << " " << dimensionDepth << std::endl;
		return;
	}
	clear();
	std::cout << "Dimension Width: " << dimensionWidth << std::endl;
	m_width = width;
	m_height = height;
	m_depth = depth;
	m_widthBlocks = widthBlocks;
	m_heightBlocks = heightBlocks;
	m_depthBlocks = depthBlocks;
	m_cellDimension = dimensionWidth;
	m_cellDiameter = sqrt(pow(sqrt(2 * pow(m_cellDimension, 2)), 2) + pow(m_cellDimension, 2));
	std::cout << "Diameter: " << m_cellDiameter << std::endl;

	m_grid = new FluidPoint**[m_widthBlocks];
	for(int x = 0; x < m_widthBlocks; x++) {
		m_grid[x] = new FluidPoint*[m_heightBlocks];
		for(int y = 0; y < m_heightBlocks; y++) {
			m_grid[x][y] = new FluidPoint[m_depthBlocks];
			for(int z = 0; z < m_depthBlocks; z++) {
				m_grid[x][y][z].init(mRenderer->getShaderProgram()->getProgram(), x * m_cellDimension, y * m_cellDimension, z * m_cellDimension, m_cellDimension);
				m_grid[x][y][z].setProperty(INK_CURRENT, 0.0f);
				m_grid[x][y][z].setProperty(INK_NEW, 0.0f);
				if(x == 3 && y == 3) {
					m_grid[x][y][z].setProperty(INK_CURRENT, 1.0f);
					//m_grid[x][y][z].setNewVelocity(5.0f, 5.0f, 0.0f);
					m_grid[x][y][z].setCurrentVelocity(0.0f, 1.0f, 5.0f);
				}
				m_grid[x][y][z].setTexture(m_texture);
			}
		}
	}

	createNeighbours();
	createCells();
}

void FluidGrid::createNeighbours() {
	m_neighbours = new FluidCell**[m_widthBlocks];
	for(int x = 0; x < m_widthBlocks; x++) {
		m_neighbours[x] = new FluidCell*[m_heightBlocks];
		for(int y = 0; y < m_heightBlocks; y++) {
			m_neighbours[x][y] = new FluidCell[m_depthBlocks];
			for(int z = 0; z < m_depthBlocks; z++) {
				initNeighbours(x, y, z);
			}
		}
	}
}

void FluidGrid::createCells() {
	m_cells = new FluidCell**[m_widthBlocks];
	for(int x = 0; x < m_widthBlocks; x++) {
		m_cells[x] = new FluidCell*[m_heightBlocks];
		for(int y = 0; y < m_heightBlocks; y++) {
			m_cells[x][y] = new FluidCell[m_depthBlocks];
			for(int z = 0; z < m_depthBlocks; z++) {
				initCell(x, y, z);
			}
		}
	}
}

void FluidGrid::createTextures() {

}


void FluidGrid::clear() {
	if(m_grid != nullptr) {
		for(int x = 0; x < m_widthBlocks; x++) {
			for(int y = 0; y < m_heightBlocks; y++) {
				delete[] m_grid[x][y];
			}
			delete[] m_grid[x];
		}
		delete[] m_grid;
	}

	if(m_neighbours != nullptr) {
		for(int x = 0; x < m_widthBlocks; x++) {
			for(int y = 0; y < m_heightBlocks; y++) {
				delete[] m_neighbours[x][y];
			}
			delete[] m_neighbours[x];
		}
		delete[] m_neighbours;
	}

	if(m_cells != nullptr) {
		for(int x = 0; x < m_widthBlocks - 1; x++) {
			for(int y = 0; y < m_heightBlocks - 1; y++) {
				delete[] m_cells[x][y];
			}
			delete[] m_cells[x];
		}
		delete[] m_cells;
	}
}

void FluidGrid::render(float deltaMillis, bool transform, glm::mat4 &transMatrix) {
	glm::mat4 modelMatrix = (transform ? transMatrix * getModelMatrix() : getModelMatrix());

	for(int x = 0; x < m_widthBlocks; x++) {
		for(int y = 0; y < m_heightBlocks; y++) {
			for(int z = 0; z < m_depthBlocks; z++) {
				float property = m_grid[x][y][z].getProperty(INK_CURRENT);
				glm::vec3 velocity = m_grid[x][y][z].getCurrentVelocity();
				glUniform1f(glGetUniformLocation(mRenderer->getShaderProgram()->getProgram(), "opacity"), property);
				m_grid[x][y][z].render(deltaMillis, modelMatrix);
			}
		}
	}

}

void FluidGrid::update(float deltaMillis) {
	std::cout << "FPS: " << 1000.0 / deltaMillis << std::endl;

	for(int x = 0; x < m_widthBlocks; x++) {
		for(int y = 0; y < m_heightBlocks; y++) {
			for(int z = 0; z < m_depthBlocks; z++) {
				updatePoint(deltaMillis, x, y, z);
			}
		}
	}

	for(int x = 0; x < m_widthBlocks; x++) {
		for(int y = 0; y < m_heightBlocks; y++) {
			for(int z = 0; z < m_depthBlocks; z++) {
				updatePoint2(deltaMillis, x, y, z);
			}
		}
	}

	for(int x = 0; x < m_widthBlocks; x++) {
		for(int y = 0; y < m_heightBlocks; y++) {
			for(int z = 0; z < m_depthBlocks; z++) {
				updatePoint3(deltaMillis, x, y, z);
			}
		}
	}

	for(int x = 0; x < m_widthBlocks; x++) {
		for(int y = 0; y < m_heightBlocks; y++) {
			for(int z = 0; z < m_depthBlocks; z++) {
				swapValues(x, y, z);
			}
		}
	}
}

void FluidGrid::updatePoint(float deltaMillis, int x, int y, int z) {
	deltaMillis /= 1000.0f;
	FluidPoint& point = m_grid[x][y][z];
	FluidCell* neighbours = &m_neighbours[x][y][z];

	point.velocityDiffusion(deltaMillis * m_velocityDiffusionScale, neighbours);
	point.diffusion(INK_CURRENT, INK_NEW, deltaMillis * m_inkDiffusionScale, neighbours);
}

void FluidGrid::updatePoint2(float deltaMillis, int x, int y, int z) {
	FluidPoint& point = m_grid[x][y][z];
	point.setProperty(INK_CURRENT, point.getProperty(INK_NEW));
}

void FluidGrid::updatePoint3(float deltaMillis, int x, int y, int z) {
	deltaMillis /= 1000.0f;
	FluidPoint& point = m_grid[x][y][z];
	FluidCell* forwardTarget,* backwardTarget;

	glm::vec3 pointPosition(x * m_cellDimension, y * m_cellDimension, z * m_cellDimension);
	glm::vec3 currentVelocity = point.getCurrentVelocity();
	glm::vec3 movement = currentVelocity * deltaMillis * m_velocityAdvectionScale;
	glm::vec3 forwardPoint = pointPosition + movement;
	glm::vec3 backwardPoint = pointPosition - movement;

	forwardTarget = getCell(forwardPoint);
	backwardTarget = getCell(backwardPoint);
	point.forwardAdvection(INK_CURRENT, INK_NEW, m_cellDimension, deltaMillis * m_inkAdvectionScale, forwardTarget);
	point.forwardVelocityAdvection(m_cellDimension, deltaMillis * m_velocityAdvectionScale, forwardTarget);
}

void FluidGrid::swapValues(int x, int y, int z) {
	FluidPoint& point = m_grid[x][y][z];
	point.setProperty(INK_CURRENT, point.getProperty(INK_NEW));
	point.setCurrentVelocity(point.getNewVelocity());
}

void FluidGrid::initNeighbours(int x, int y, int z) {
	FluidCell& neighbours = m_neighbours[x][y][z];
	int xMin = x - 1, xMax = x + 1, yMin = y - 1, yMax = y + 1, zMin = z - 1, zMax = z + 1;

	if(xMin >= 0) {
		neighbours.addPoint(&m_grid[xMin][y][z]);
	}
	if(xMax < m_widthBlocks) {
		neighbours.addPoint(&m_grid[xMax][y][z]);
	}

	if(yMin >= 0) {
		neighbours.addPoint(&m_grid[x][yMin][z]);
	}
	if(yMax < m_heightBlocks) {
		neighbours.addPoint(&m_grid[x][yMax][z]);
	}

	if(zMin >= 0) {
		neighbours.addPoint(&m_grid[x][y][zMin]);
	}
	if(zMax < m_depthBlocks) {
		neighbours.addPoint(&m_grid[x][y][zMax]);
	}
}

void FluidGrid::initCell(int x, int y, int z) {
	FluidCell& cell = m_cells[x][y][z];

	int xMin = x;
	int yMin = y;
	int zMin = z;
	int xMax = xMin + 1;
	int yMax = yMin + 1;
	int zMax = zMin + 1;
	/*
	if(zMax == m_depthBlocks) {
		zMin -= 1;
		zMax -= 1;
	}
	if(yMax == m_heightBlocks) {
		yMax -= 1;
		yMin -= 1;
	}
	if(xMax == m_widthBlocks) {
		xMin -= 1;
		xMax -= 1;
	}*/
/*
bool xMinValid = xMin >= 0 && xMin < m_widthBlocks, xMaxValid = xMax >= 0 && xMax < m_widthBlocks;
bool yMinValid = yMin >= 0 && yMin < m_heightBlocks, yMaxValid = yMax >= 0 && yMax < m_heightBlocks;
bool zMinValid = zMin >= 0 && zMin < m_depthBlocks, zMaxValid = yMax >= 0 && zMax < m_depthBlocks;

if(xMinValid) {
	if(yMinValid) {
		if(zMinValid) {
			cell.addPoint(&m_grid[xMin][yMin][zMin]);
		}
		if(zMaxValid) {
			cell.addPoint(&m_grid[xMin][yMin][zMax]);
		}
	}
	if(yMaxValid) {
		if(zMinValid) {
			cell.addPoint(&m_grid[xMin][yMax][zMin]);
		}
		if(zMaxValid) {
			cell.addPoint(&m_grid[xMin][yMax][zMax]);
		}
	}
}
if(xMaxValid) {
	if(yMinValid) {
		if(zMinValid) {
			cell.addPoint(&m_grid[xMax][yMin][zMin]);
		}
		if(zMaxValid) {
			cell.addPoint(&m_grid[xMax][yMin][zMax]);
		}
	}
	if(yMaxValid) {
		if(zMinValid) {
			cell.addPoint(&m_grid[xMax][yMax][zMin]);
		}
		if(zMaxValid) {
			cell.addPoint(&m_grid[xMax][yMax][zMax]);
		}
	}
}

if(z == 18 && x == 3 && (y == 3 || y == 4)) {
	cell.print();
}
}

FluidCell *FluidGrid::getCell(float x, float y, float z) {
int intX = (int) floor(x / m_cellDimension);
int intY = (int) floor(y / m_cellDimension);
int intZ = (int) floor(z / m_cellDimension);

if(intX >= 0 && intX < m_widthBlocks && intY >= 0 && intY < m_heightBlocks && intZ >= 0 && intZ < m_depthBlocks)
	return &m_cells[intX][intY][intZ];
else
	return nullptr;
}

FluidCell *FluidGrid::getCell(glm::vec3 position) {
return getCell(position.x, position.y, position.z);
}

int FluidGrid::calculateIndex(int x, int y, int z) {
return x * m_widthBlocks + y * m_widthBlocks * m_heightBlocks + z * m_widthBlocks * m_heightBlocks *  m_depthBlocks;
}
 */


void FluidGrid::update(InputBuffer *keyBuffer, glm::vec3 cameraPosition, glm::vec3 cameraDirection, float deltaMillis) {
	GameObject::update(keyBuffer, cameraPosition, cameraDirection, deltaMillis);
	if(keyBuffer->getKey(GLFW_KEY_TAB)->isPressed()) {
		std::cout << "Toggling simulation" << std::endl;
		m_simulating = !m_simulating;
	}
	if(m_simulating)
		update(deltaMillis);
}
