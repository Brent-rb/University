//
// Created by brent on 21.07.18.
//

#include "FluidGrid2.h"

bool equals(float left, float right, float deviation = 0.001f) {
	return (fabs(left - right) < deviation);
}

FluidGrid2::FluidGrid2(OpenGLRenderer *renderer, Renderable *renderable, float width, float height, float depth,
                       float dimensions): GameObject(renderer, renderable) {
	m_currentVelocities = nullptr;
	m_newVelocities = nullptr;
	m_reverseAdvectionVelocities = nullptr;
	m_currentProperties = nullptr;
	m_newProperties = nullptr;
	m_cubes = nullptr;
	m_div = nullptr;
	m_curls = nullptr;
	m_p = nullptr;

	m_diffusionScale = 0.0f;
	m_advectionScale = 1.0f;
	//m_pressureScale = 1.0f;

	m_texture = new SolidColorTexture(255, 255, 255);
	createGrid(width, height, depth, dimensions);
}

void FluidGrid2::createGrid(float width, float height, float depth, float dimensions) {
	int widthBlocks = (int) floor(width / dimensions), heightBlocks = (int) floor(height/ dimensions), depthBlocks = (int) floor(depth / dimensions);
	if(!(equals(widthBlocks, width / dimensions) && equals(heightBlocks, height / dimensions) && equals(depthBlocks, depth / dimensions))) {
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
	std::cout << "Created grid with " << m_widthBlocks * m_heightBlocks * m_depthBlocks << " blocks." << std::endl;

	int index = getIndex(0, 1, 2);
	glm::vec3 cords = getCordinates(index);
	if(!(equals(cords.x, 0.0f) && equals(cords.y, 1.0f) && equals(cords.z, 2.0f))) {
		std::cout << "Your fuctions sucks: " << index << " " << cords.x << " " << cords.y << " " << cords.z << std::endl;
		return;
	}
	index = getPropertyIndex(PRESSURE, 0, 1, 2);
	cords = getPropertyCordinates(PRESSURE, index);
	if(!(equals(cords.x, 0.0f) && equals(cords.y, 1.0f) && equals(cords.z, 2.0f))) {
		std::cout << "Your fuctions sucks: " << index << " " << cords.x << " " << cords.y << " " << cords.z << std::endl;
		return;
	}

	m_currentVelocities = new glm::vec3[getLength()];
	m_newVelocities = new glm::vec3[getLength()];
	m_reverseAdvectionVelocities = new glm::vec3[getLength()];
	m_curls = new glm::vec3[getLength()];
	m_currentProperties = new float[getLength() * PROPERTIES_SIZE];
	m_newProperties = new float[getLength() * PROPERTIES_SIZE];
	m_cubes = new Cube*[getLength()];
	m_div = new float[getLength()];
	m_p = new float[getLength()];

	memset(m_currentProperties, 0, sizeof(float) * getLength() * PROPERTIES_SIZE);
	memset(m_newProperties, 0, sizeof(float) * getLength() * PROPERTIES_SIZE);
	memset(m_div, 0, sizeof(float) * getLength());

	for(int i = 0; i < getLength(); i++) {
		m_cubes[i] = new Cube(mRenderer->getShaderProgram()->getProgram(), glm::vec3(), sqrt(2* ((m_cellDimension / 2.0) * (m_cellDimension / 2.0))), m_texture);
		glm::vec3 position = getCordinates(i) * m_cellDimension;
		m_cubes[i]->setLocation(position.x, position.y, position.z);
	}


	int x = m_widthBlocks / 2;
	int y = m_heightBlocks / 2;
	//int z = m_depthBlocks / 2;
	for(int z = 0; z < m_depthBlocks; z++) {
		index = getPropertyIndex(PRESSURE, x, y, z);
		int velIndex = getIndex(x, y, z);
		m_currentProperties[index] = 1.0f;
		//m_currentProperties[getPropertyIndex(PRESSURE, x, y, z)] = 1.0f;
		m_currentVelocities[velIndex] = glm::vec3(-10.0f, 0.0f, 0.0f);
	}
}

void FluidGrid2::clear() {
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
	if(m_reverseAdvectionVelocities != nullptr) {
		delete[] m_reverseAdvectionVelocities;
		m_reverseAdvectionVelocities = nullptr;
	}
	if(m_div != nullptr) {
		delete[] m_div;
		m_div = nullptr;
	}
	if(m_curls != nullptr) {
		delete[] m_curls;
		m_curls = nullptr;
	}
	if(m_p != nullptr) {
		delete[] m_p;
		m_p = nullptr;
	}
	if(m_cubes != nullptr) {
		for(int i = 0; i < getLength(); i++) {
			delete m_cubes[i];
		}
		delete[] m_cubes;
	}
}

void FluidGrid2::update(InputBuffer *keyBuffer, float deltaMillis) {
	update(deltaMillis);
}

void FluidGrid2::render(float deltaMillis, bool transform, glm::mat4 &transMatrix) {
	glm::mat4 modelMatrix = (transform ? transMatrix * getModelMatrix() : getModelMatrix());


	for(int i = 0; i < getLength(); i++) {
		float ink = m_currentProperties[getPropertyIndex(PRESSURE, i)];
		if(ink > 0.001f) {
			glUniform1f(glGetUniformLocation(mRenderer->getShaderProgram()->getProgram(), "opacity"),
			            m_currentProperties[getPropertyIndex(PRESSURE, i)]);
			m_cubes[i]->render(deltaMillis, modelMatrix);
		}
	}
}

void FluidGrid2::update(float deltaMillis) {
	deltaMillis /= 1000.0f;
	std::cout << "X Velocity: " << m_currentVelocities[getIndex(m_widthBlocks / 2, m_heightBlocks / 2, m_depthBlocks / 2)].x << std::endl;

	velocityStep(deltaMillis);
	std::cout << "X Velocity2: " << m_currentVelocities[getIndex(m_widthBlocks / 2, m_heightBlocks / 2, m_depthBlocks / 2)].x << std::endl;

	densityStep(deltaMillis);
}

void FluidGrid2::velocityStep(float deltaMillis) {
	int iterations = 10;
	diffusionVelocity(iterations, deltaMillis / iterations);
	project(deltaMillis);
	swapVelocity();
	advectionVelocity(deltaMillis);
	project(deltaMillis);
	swapVelocity();
}

void FluidGrid2::densityStep(float deltaMillis) {
	int iterations = 10;
	diffusion(iterations, deltaMillis / iterations);
	swapProperties();
	advection(deltaMillis);
	swapProperties();
}

int FluidGrid2::getLength() {
	return m_widthBlocks * m_heightBlocks * m_depthBlocks;
}

int FluidGrid2::getIndex(int x, int y, int z) {
	return x + y * m_widthBlocks + z * m_widthBlocks * m_heightBlocks;
}

int FluidGrid2::getPropertyIndex(Property property, int x, int y, int z) {
	return (property * getLength()) + getIndex(x, y, z);
}

int FluidGrid2::getPropertyIndex(Property property, int index) {
	return (property * getLength()) + index;
}

glm::vec3 FluidGrid2::getCordinates(int index) {
	int z = index / (m_widthBlocks * m_heightBlocks);
	int temp = index % (m_widthBlocks * m_heightBlocks);
	int y = temp / m_widthBlocks;
	int x = temp % m_widthBlocks;
	return glm::vec3(x, y, z);
}

glm::vec3 FluidGrid2::getPropertyCordinates(Property property, int index) {
	index -= property * getLength();
	int z = index / (m_widthBlocks * m_heightBlocks);
	index %= (m_widthBlocks * m_heightBlocks);
	int y = index / m_widthBlocks;
	int x = index % m_widthBlocks;
	return glm::vec3(x, y, z);
}

glm::vec3 FluidGrid2::getTarget(int &x, int &y, int &z, int &index, float scale) {
	glm::vec3 velocity = m_currentVelocities[index];
	glm::vec3 position(x, y, z);
	return position + (velocity * scale);
}

void FluidGrid2::addSource(glm::vec3 *from, glm::vec3 *to, float deltaMillis) {
	for(int i = 0; i < getLength(); i++) {
		to[i] += from[i] * deltaMillis;
	}
}

void FluidGrid2::curl() {
	int index;
	float dzdy, dydz, dxdz, dzdx, dydx, dxdy;

	for(int z = 1; z < m_depthBlocks - 1; z++) {
		for(int y = 1; y < m_heightBlocks - 1; y++) {
			for(int x = 1; x < m_widthBlocks - 1; x++) {
				index = getIndex(x, y, z);

				dzdy = (m_currentVelocities[getIndex(x, y + 1, z)].z - m_currentVelocities[getIndex(x, y - 1, z)].z) * 0.5f;
				dydz = (m_currentVelocities[getIndex(x, y, z + 1)].y - m_currentVelocities[getIndex(x, y, z - 1)].y) * 0.5f;
				m_curls[index].x = dzdy - dydz;

				dxdz = (m_currentVelocities[getIndex(x, y, z + 1)].x - m_currentVelocities[getIndex(x, y, z - 1)].x) * 0.5f;
				dzdx = (m_currentVelocities[getIndex(x + 1, y, z)].z - m_currentVelocities[getIndex(x - 1, y, z)].z) * 0.5f;
				m_curls[index].y = dxdz - dzdx;

				dydx = (m_currentVelocities[getIndex(x + 1, y, z)].y - m_currentVelocities[getIndex(x - 1, y, z)].y) * 0.5f;
				dxdy = (m_currentVelocities[getIndex(x, y + 1, z)].x - m_currentVelocities[getIndex(x, y - 1, z)].x) * 0.5f;
				m_curls[index].z = dydx - dxdy;
			}
		}
	}
}

void FluidGrid2::vorticityConfinement() {
	int index, xLeft, xRight, yDown, yUp, zBack, zForward;
	float dzdx, dzdy, dzdz, length;

	glm::vec4 a, b, c, sqrt1, sqrt2;
	glm::vec3 temp;

	for(int z = 2; z < m_depthBlocks - 2; z++) {
		for(int y = 2; y < m_heightBlocks - 2; y++) {
			for(int x = 2; x < m_widthBlocks - 2; x++) {
				index = getIndex(x, y, z);
				xLeft = getIndex(x - 1, y, z);
				xRight = getIndex(x + 1, y, z);
				yDown = getIndex(x, y - 1, z);
				yUp = getIndex(x, y + 1, z);
				zBack = getIndex(x, y, z - 1);
				zForward = getIndex(x, y, z + 1);

				dzdx = (sqrt(m_curls[xRight].x * m_curls[xRight].x + m_curls[xRight].y * m_curls[xRight].y + m_curls[xRight].z + m_curls[xRight].z) -
						sqrt(m_curls[xLeft].x * m_curls[xLeft].x + m_curls[xLeft].y * m_curls[xLeft].y + m_curls[xLeft].z + m_curls[xLeft].z)) * 0.5f;

				dzdy = (sqrt(m_curls[yUp].x * m_curls[yUp].x + m_curls[yUp].y * m_curls[yUp].y + m_curls[yUp].z + m_curls[yUp].z) -
				        sqrt(m_curls[yDown].x * m_curls[yDown].x + m_curls[yDown].y * m_curls[yDown].y + m_curls[yDown].z + m_curls[yDown].z)) * 0.5f;

				dzdz = (sqrt(m_curls[zForward].x * m_curls[zForward].x + m_curls[zForward].y * m_curls[zForward].y + m_curls[zForward].z + m_curls[zForward].z) -
				        sqrt(m_curls[zBack].x * m_curls[zBack].x + m_curls[zBack].y * m_curls[zBack].y + m_curls[zBack].z + m_curls[zBack].z)) * 0.5f;

				a = glm::vec4(m_curls[xRight].x, m_curls[yUp].x, m_curls[zForward].x, 1.0f);
				a = a * a;

				b = glm::vec4(m_curls[xRight].y, m_curls[yUp].y, m_curls[zForward].y, 1.0f);
				b = b * b;

				c = glm::vec4(m_curls[xRight].z, m_curls[yUp].z, m_curls[zForward].z, 1.0f);
				z = z * z;

				sqrt1 = a + b + c;
				sqrt1 = glm::sqrt(sqrt1);

				a = glm::vec4(m_curls[xLeft].x, m_curls[yDown].x, m_curls[zBack].x, 1.0f);
				a = a * a;

				b = glm::vec4(m_curls[xLeft].y, m_curls[yDown].y, m_curls[zBack].y, 1.0f);
				b = b * b;

				c = glm::vec4(m_curls[xLeft].z, m_curls[yDown].z, m_curls[zBack].z, 1.0f);
				z = z * z;

				sqrt2 = a + b + c;
				sqrt2 = glm::sqrt(sqrt2);

				a = (sqrt1 - sqrt2) * 0.5f;

				length = 1.0f / (a.length() + 0.0000001f);

				dzdx *= length;
				dzdy *= length;
				dzdz *= length;

				temp = m_curls[index];

				m_currentVelocities[index] = glm::vec3(dzdy * temp.z - dzdz * temp.y, dzdz * temp.x - dzdx * temp.z, dzdx * temp.y - dzdy * temp.x);
			}
		}
	}
}

void FluidGrid2::diffusion(int iterations, float deltaMillis) {
	float scale = deltaMillis * m_diffusionScale * m_cellDimension;
	int count, xMin, xMax, yMin, yMax, zMin, zMax, x, y, z;
	float value;
	glm::vec3 cords, tempVelocity;

	for(int iteration = 0; iteration < iterations; iteration++) {
		for(int propertyI = PRESSURE; propertyI < PROPERTIES_SIZE; propertyI++) {
			Property property = (Property) propertyI;
			for (int i = 0; i < getLength(); i++) {
				count = 0;
				value = 0.0f;
				cords = getCordinates(i);

				x = (int) cords.x;
				y = (int) cords.y;
				z = (int) cords.z;

				xMin = x - 1; xMax = x + 1;
				yMin = y - 1; yMax = y + 1;
				zMin = z - 1; zMax = z + 1;

				if(xMin >= 0) {
					value += m_newProperties[getPropertyIndex(property, xMin, y, z)];
					count++;
				}
				if(yMin >= 0) {
					value += m_newProperties[getPropertyIndex(property, x, yMin, z)];
					count++;
				}
				if(zMin >= 0) {
					value += m_newProperties[getPropertyIndex(property, x, y, zMin)];
					count++;
				}
				if(xMax < m_widthBlocks) {
					value += m_newProperties[getPropertyIndex(property, xMax, y, z)];
					count++;
				}
				if(yMax < m_heightBlocks) {
					value += m_newProperties[getPropertyIndex(property, x, yMax, z)];
					count++;
				}
				if(zMax < m_depthBlocks) {
					value += m_newProperties[getPropertyIndex(property, x, y, zMax)];
					count++;
				}

				m_newProperties[getPropertyIndex(property, i)] = (m_currentProperties[getPropertyIndex(property, i)] + (scale * value)) / (1.0f + (float)(count) * scale);
			}
		}
	}
}

void FluidGrid2::diffusionVelocity(int iterations, float deltaMillis) {
	float scale = deltaMillis * m_diffusionScale * m_cellDimension;
	int count, xMin, xMax, yMin, yMax, zMin, zMax, x, y, z;
	float value;
	glm::vec3 cords, tempVelocity;

	for(int iteration = 0; iteration < iterations; iteration++) {
		for (int i = 0; i < getLength(); i++) {
			count = 0;
			tempVelocity = glm::vec3();
			cords = getCordinates(i);

			x = (int) cords.x;
			y = (int) cords.y;
			z = (int) cords.z;

			xMin = x - 1; xMax = x + 1;
			yMin = y - 1; yMax = y + 1;
			zMin = z - 1; zMax = z + 1;

			if(xMin <= 0) {
				tempVelocity += m_newVelocities[getIndex(xMin, y, z)];
				count++;
			}
			if(yMin <= 0) {
				tempVelocity += m_newVelocities[getIndex(x, yMin, z)];
				count++;
			}
			if(zMin <= 0) {
				tempVelocity += m_newVelocities[getIndex(x, y, zMin)];
				count++;
			}
			if(xMax < m_widthBlocks) {
				tempVelocity += m_newVelocities[getIndex(xMax, y, z)];
				count++;
			}
			if(yMax < m_heightBlocks) {
				tempVelocity += m_newVelocities[getIndex(x, yMax, z)];
				count++;
			}
			if(zMax < m_depthBlocks) {
				tempVelocity += m_newVelocities[getIndex(x, y, zMax)];
				count++;
			}

			m_newProperties[i] = (m_currentProperties[i] + scale * value) / (1.0f + count * scale);
		}
	}
}

void FluidGrid2::advection(float deltaMillis) {
	for(int propertyIndex = PRESSURE; propertyIndex < PROPERTIES_SIZE; propertyIndex++) {
		Property property = (Property) propertyIndex;

		float scale = deltaMillis * m_advectionScale;
		float value = 0;
		glm::vec3 cords, target, velocity, vScale;
		int x, y, z, xMin, yMin, zMin, xMax, yMax, zMax;

		for (int index = 0; index < getLength(); index++) {
			cords = getCordinates(index);
			value = 0;
			x = (int) cords.x;
			y = (int) cords.y;
			z = (int) cords.z;

			velocity = m_currentVelocities[index];
			target = cords - (velocity * scale);

			xMin = floor(target.x);
			xMax = xMin + 1;
			yMin = floor(target.y);
			yMax = yMin + 1;
			zMin = floor(target.z);
			zMax = zMin + 1;

			if (xMin < 0) {
				xMin = 0;
				xMax = 1;
				target.x = xMin;
			}
			if (xMax >= m_widthBlocks) {
				xMax = m_widthBlocks - 1;
				xMin = m_widthBlocks - 2;
				target.x = xMax;
			}
			if (yMin < 0) {
				yMin = 0;
				yMax = 1;
				target.y = yMin;
			}
			if (yMax >= m_heightBlocks) {
				yMax = m_heightBlocks - 1;
				yMin = m_heightBlocks - 2;
				target.y = yMax;
			}
			if (zMin < 0) {
				zMin = 0;
				zMax = 1;
				target.z = zMin;
			}
			if (zMax >= m_depthBlocks) {
				zMax = m_depthBlocks - 1;
				zMin = m_depthBlocks - 2;
				target.z = zMax;
			}


			glm::vec3 fractions(target.x - xMin, target.y - yMin, target.z - zMin);
			value += m_currentProperties[getPropertyIndex(property, xMin, yMin, zMin)] * (1.0f - fractions.x) *
			         (1.0f - fractions.y) * (1.0f - fractions.z);

			value += m_currentProperties[getPropertyIndex(property, xMin, yMin, zMax)] * (1.0f - fractions.x) *
			         (1.0f - fractions.y) * fractions.z;

			value += m_currentProperties[getPropertyIndex(property, xMin, yMax, zMin)] * (1.0f - fractions.x) *
			         (fractions.y) * (1.0f - fractions.z);

			value += m_currentProperties[getPropertyIndex(property, xMin, yMax, zMax)] * (1.0f - fractions.x) *
			         (fractions.y) * fractions.z;

			value += m_currentProperties[getPropertyIndex(property, xMax, yMin, zMin)] * (fractions.x) *
			         (1.0f - fractions.y) * (1.0f - fractions.z);

			value += m_currentProperties[getPropertyIndex(property, xMax, yMin, zMax)] * (fractions.x) *
			         (1.0f - fractions.y) * fractions.z;

			value += m_currentProperties[getPropertyIndex(property, xMax, yMax, zMin)] * (fractions.x) * (fractions.y) *
			         (1.0f - fractions.z);

			value += m_currentProperties[getPropertyIndex(property, xMax, yMax, zMax)] * (fractions.x) * (fractions.y) *
			         fractions.z;

			m_newProperties[getPropertyIndex(property, x, y, z)] = value;
		}
	}
}

void FluidGrid2::advectionVelocity(float deltaMillis) {
	float scale = deltaMillis * m_advectionScale;
	glm::vec3 value;
	glm::vec3 cords, target, velocity, vScale;
	int x, y, z, xMin, yMin, zMin, xMax, yMax, zMax;

	for (int index = 0; index < getLength(); index++) {
		cords = getCordinates(index);
		value = glm::vec3(0);
		x = (int) cords.x;
		y = (int) cords.y;
		z = (int) cords.z;

		velocity = m_currentVelocities[index];
		target = cords - (velocity * scale);

		xMin = floor(target.x);
		xMax = xMin + 1;
		yMin = floor(target.y);
		yMax = yMin + 1;
		zMin = floor(target.z);
		zMax = zMin + 1;

		if (xMin < 0) {
			xMin = 0;
			xMax = 1;
			target.x = xMin;
		}
		if (xMax >= m_widthBlocks) {
			xMax = m_widthBlocks - 1;
			xMin = m_widthBlocks - 2;
			target.x = xMax;
		}
		if (yMin < 0) {
			yMin = 0;
			yMax = 1;
			target.y = yMin;
		}
		if (yMax >= m_heightBlocks) {
			yMax = m_heightBlocks - 1;
			yMin = m_heightBlocks - 2;
			target.y = yMax;
		}
		if (zMin < 0) {
			zMin = 0;
			zMax = 1;
			target.z = zMin;
		}
		if (zMax >= m_depthBlocks) {
			zMax = m_depthBlocks - 1;
			zMin = m_depthBlocks - 2;
			target.z = zMax;
		}


		glm::vec3 fractions(target.x - xMin, target.y - yMin, target.z - zMin);
		value += m_currentVelocities[getIndex(xMin, yMin, zMin)] * (1.0f - fractions.x) *
		         (1.0f - fractions.y) * (1.0f - fractions.z);

		value += m_currentVelocities[getIndex(xMin, yMin, zMax)] * (1.0f - fractions.x) *
		         (1.0f - fractions.y) * fractions.z;

		value += m_currentVelocities[getIndex(xMin, yMax, zMin)] * (1.0f - fractions.x) *
		         (fractions.y) * (1.0f - fractions.z);

		value += m_currentVelocities[getIndex(xMin, yMax, zMax)] * (1.0f - fractions.x) *
		         (fractions.y) * fractions.z;

		value += m_currentVelocities[getIndex(xMax, yMin, zMin)] * (fractions.x) *
		         (1.0f - fractions.y) * (1.0f - fractions.z);

		value += m_currentVelocities[getIndex(xMax, yMin, zMax)] * (fractions.x) *
		         (1.0f - fractions.y) * fractions.z;

		value += m_currentVelocities[getIndex(xMax, yMax, zMin)] * (fractions.x) * (fractions.y) *
		         (1.0f - fractions.z);

		value += m_currentVelocities[getIndex(xMax, yMax, zMax)] * (fractions.x) * (fractions.y) *
		         fractions.z;

		m_newVelocities[getIndex(x, y, z)] = value;
	}
}

void FluidGrid2::project(float deltaMillis) {
	float w = 1.0f / m_widthBlocks, h = 1.0f / m_heightBlocks, d = 1.0f / m_depthBlocks;
	float xMin, xMax, yMin, yMax, zMin, zMax;
	int x, y, z;
	glm::vec3 cords;

	memset(m_p, sizeof(float) * getLength(), 0);
	for(int index = 0; index < getLength(); index++) {
		cords = getCordinates(index);
		x = cords.x;
		y = cords.y;
		z = cords.z;

		if(x - 1 < 0)
			xMin = 0;
		else
			xMin = m_newVelocities[getIndex(x - 1, y, z)].x;

		if(y - 1 < 0)
			yMin = 0;
		else
			yMin = m_newVelocities[getIndex(x, y - 1, z)].y;

		if(z - 1 < 0)
			zMin = 0;
		else
			zMin = m_newVelocities[getIndex(x, y, z - 1)].z;

		if(x + 1 >= m_widthBlocks)
			xMax = 0;
		else
			xMax = m_newVelocities[getIndex(x + 1, y, z)].x;

		if(y + 1 >= m_heightBlocks)
			yMax = 0;
		else
			yMax = m_newVelocities[getIndex(x, y + 1, z)].y;

		if(z + 1 > m_depthBlocks)
			zMax = 0;
		else
			zMax = m_newVelocities[getIndex(x, y, z + 1)].z;


		m_div[index] = -0.5f * (
				                       (xMax - xMin) / m_cellDimension +
				                       (yMax - yMin) / m_cellDimension +
				                       (zMax - zMin) / m_cellDimension
				);
	}

	float value;
	int count;
	for(int iteration = 0; iteration < 20; iteration++) {
		int xMin, xMax, yMin, yMax, zMin, zMax;
		for(int index = 0; index < getLength(); index++) {
			cords = getCordinates(index);
			x = cords.x;
			y = cords.y;
			z = cords.z;

			xMin = x - 1;
			xMax = x + 1;
			yMin = y - 1;
			yMax = y + 1;
			zMin = z - 1;
			zMax = z + 1;

			value = 0;
			count = 0;

			if(xMin >= 0) {
				value += m_currentVelocities[getIndex(xMin, y, z)].x;
				count++;
			}
			if(yMin >= 0) {
				value += m_currentVelocities[getIndex(x, yMin, z)].x;
				count++;
			}
			if(zMin >= 0) {
				value += m_currentVelocities[getIndex(x, y, zMin)].x;
				count++;
			}
			if(xMax < m_widthBlocks) {
				value += m_currentVelocities[getIndex(xMax, y, z)].x;
				count++;
			}
			if(yMax < m_heightBlocks) {
				value += m_currentVelocities[getIndex(x, yMax, z)].x;
				count++;
			}
			if(zMax < m_depthBlocks) {
				value += m_currentVelocities[getIndex(x, y, zMax)].x;
				count++;
			}

			m_currentVelocities[getIndex(x, y, z)].x = (m_currentVelocities[getIndex(x, y, z)].y + value) / (float) count;
		}
	}

	for(int index = 0; index < getLength(); index++) {
		cords = getCordinates(index);
		x = cords.x;
		y = cords.y;
		z = cords.z;

		if(x - 1 < 0)
			xMin = 0;
		else
			xMin = m_currentVelocities[getIndex(x - 1, y, z)].x;

		if(y - 1 < 0)
			yMin = 0;
		else
			yMin = m_currentVelocities[getIndex(x, y - 1, z)].x;

		if(z - 1 < 0)
			zMin = 0;
		else
			zMin = m_currentVelocities[getIndex(x, y, z - 1)].x;

		if(x + 1 >= m_widthBlocks)
			xMax = 0;
		else
			xMax = m_currentVelocities[getIndex(x + 1, y, z)].x;

		if(y + 1 >= m_heightBlocks)
			yMax = 0;
		else
			yMax = m_currentVelocities[getIndex(x, y + 1, z)].x;

		if(z + 1 > m_depthBlocks)
			zMax = 0;
		else
			zMax = m_currentVelocities[getIndex(x, y, z + 1)].x;

		m_newVelocities[getIndex(x, y, z)] -= glm::vec3(
				m_cellDimension * (xMax - xMin) / w,
				m_cellDimension * (yMax - yMin) / h,
				m_cellDimension * (zMax - zMin) / d
		);
	}
}

void FluidGrid2::swap() {
	swapProperties();
	swapVelocity();
}

void FluidGrid2::swapProperties() {
	float* currentProperties = m_currentProperties;
	m_currentProperties = m_newProperties;
	m_newProperties = currentProperties;
}

void FluidGrid2::swapVelocity() {
	glm::vec3* currentVelocities = m_currentVelocities;
	m_currentVelocities = m_newVelocities;
	m_newVelocities = currentVelocities;
}

void FluidGrid2::swapReverseAdvectionVelocity() {
	glm::vec3* currentVelocities = m_currentVelocities;
	m_currentVelocities = m_reverseAdvectionVelocities;
	m_reverseAdvectionVelocities = currentVelocities;
}

void FluidGrid2::copyProperties(float *from, float *to) {
	memcpy(to, from, sizeof(float) * getLength() * PROPERTIES_SIZE);
}

void FluidGrid2::copyVelcities(glm::vec3 *from, glm::vec3 *to) {
	memcpy(to, from, sizeof(glm::vec3) * getLength());
}


int FluidGrid2::calculateIndex(int x, int y, int z) {
	return 0;
}
