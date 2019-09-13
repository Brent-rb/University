//
// Created by brent on 07.07.18.
//

#include <iostream>
#include "FluidPoint.h"
#include "../Textures/SolidColorTexture.h"

bool fequals(float left, float right, float deviation = 0.001f) {
	return (fabs(left - right) < deviation);
}

FluidPoint::FluidPoint() {
	for(int i = 0; i < PROPERTIES_SIZE; i++) {
		m_properties.push_back(0.0f);
	}
}

void FluidPoint::init(GLuint shaderProgram, float x, float y, float z, float dimension) {
	float half = dimension / 2.0f;

	m_cube = new Cube(shaderProgram, glm::vec3(0, 0, 0), sqrt(2 * half * half));
	m_cube->setLocation(x, y, z);
	setPosition(x, y, z);
}

void FluidPoint::diffusion(Property oldProperty, Property newProperty, float scale, FluidCell* neighbours) {
	float value = 0.0f;

	for(int i = 0; i < neighbours->size(); i++) {
		value += neighbours->getPoint(i)->getProperty(oldProperty);
	}

	value -= neighbours->size() * getProperty(oldProperty);
	setProperty(newProperty, getProperty(oldProperty) + scale * value);
}

void FluidPoint::forwardAdvection(Property oldProperty, Property newProperty, float cellDimension, float scale, FluidCell* target) {
	float originalValue = getProperty(oldProperty);
	float deductedValue = 0;
	float value;
	glm::vec3 velocity = getCurrentVelocity();
	glm::vec3 position = getPosition() + velocity * scale;

	if(target != nullptr && target->size() == 8) {
		FluidPoint* xMinyMinzMin = target->getPoint(0);
		FluidPoint* xMinyMinzMax = target->getPoint(1);
		FluidPoint* xMinyMaxzMin = target->getPoint(2);
		FluidPoint* xMinyMaxzMax = target->getPoint(3);
		FluidPoint* xMaxyMinzMin = target->getPoint(4);
		FluidPoint* xMaxyMinzMax = target->getPoint(5);
		FluidPoint* xMaxyMaxzMin = target->getPoint(6);
		FluidPoint* xMaxyMaxzMax = target->getPoint(7);

		glm::vec3 fractions = position - xMinyMinzMin->getPosition();
		fractions /= cellDimension;
		value = originalValue * (1.0f - fractions.x) * (1.0f - fractions.y) * (1.0f - fractions.z);
		xMinyMinzMin->addProperty(newProperty, value);
		deductedValue -= value;

		value = originalValue *  (1.0f - fractions.x) * (1.0f - fractions.y) * fractions.z;
		xMinyMinzMax->addProperty(newProperty, value);
		deductedValue -= value;

		value = originalValue *  (1.0f - fractions.x) * (fractions.y) * (1.0f - fractions.z);
		xMinyMaxzMin->addProperty(newProperty, value);
		deductedValue -= value;

		value = originalValue *  (1.0f - fractions.x) * (fractions.y) * fractions.z;
		xMinyMaxzMax->addProperty(newProperty, value);
		deductedValue -= value;

		value = originalValue * (fractions.x) * (1.0f - fractions.y) * (1.0f - fractions.z);
		xMaxyMinzMin->addProperty(newProperty, value);
		deductedValue -= value;

		value = originalValue *  (fractions.x) * (1.0f - fractions.y) * fractions.z;
		xMaxyMinzMax->addProperty(newProperty, value);
		deductedValue -= value;

		value = originalValue *  (fractions.x) * (fractions.y) * (1.0f - fractions.z);
		xMaxyMaxzMin->addProperty(newProperty, value);
		deductedValue -= value;

		value = originalValue *  (fractions.x) * (fractions.y) * fractions.z;
		xMaxyMaxzMax->addProperty(newProperty, value);
		deductedValue -= value;
	}
	/*
	else if(target != nullptr && target->size() == 4) {
		bool xSame = true, ySame = true, zSame = true;
		float x, y, z;
		for(int i = 0; i < 4; i++) {
			FluidPoint* point = target->getPoint(i);
			if(i == 0) {
				x = point->getX();
				y = point->getY();
				z = point->getZ();
			}
			else {
				xSame = xSame && fequals(x, point->getX());
				ySame = ySame && fequals(y, point->getY());
				zSame = zSame && fequals(z, point->getZ());
			}
		}

		FluidPoint* point1 = target->getPoint(0);
		FluidPoint* point2 = target->getPoint(1);
		FluidPoint* point3 = target->getPoint(2);
		FluidPoint* point4 = target->getPoint(3);
		float value1, value2, value3, value4;
		float sub1, sub2;

		glm::vec3 fractions = position - point1->getPosition();
		fractions /= cellDimension;
		if(xSame) {
			sub1 = fractions.y;
			sub2 = fractions.z;
		}
		else if(ySame) {
			sub1 = fractions.x;
			sub2 = fractions.z;
		}
		else if(zSame) {
			sub1 = fractions.x;
			sub2 = fractions.z;
		}

		value1 = originalValue * (1.0f - sub1) * (1.0f - sub2);
		value2 = originalValue * (1.0f - sub1) * (sub2);
		value3 = originalValue * (sub1) * (1.0 - sub2);
		value4 = originalValue * (sub1) * (sub2);

		point1->addProperty(newProperty, value1);
		point2->addProperty(newProperty, value2);
		point3->addProperty(newProperty, value3);
		point4->addProperty(newProperty, value4);
		deductedValue -= (value1 + value2 + value3 + value4);
	}
	 */

	addProperty(newProperty, deductedValue);
}

void FluidPoint::forwardVelocityAdvection(float cellDimension, float scale, FluidCell* target) {
	glm::vec3 originalValue = getCurrentVelocity();
	glm::vec3 deductedValue;
	glm::vec3 value;
	glm::vec3 velocity = getCurrentVelocity();
	glm::vec3 position = getPosition() + velocity * scale;

	if(target != nullptr && target->size() == 8) {
		FluidPoint* xMinyMinzMin = target->getPoint(0);
		FluidPoint* xMinyMinzMax = target->getPoint(1);
		FluidPoint* xMinyMaxzMin = target->getPoint(2);
		FluidPoint* xMinyMaxzMax = target->getPoint(3);
		FluidPoint* xMaxyMinzMin = target->getPoint(4);
		FluidPoint* xMaxyMinzMax = target->getPoint(5);
		FluidPoint* xMaxyMaxzMin = target->getPoint(6);
		FluidPoint* xMaxyMaxzMax = target->getPoint(7);

		glm::vec3 fractions = position - xMinyMinzMin->getPosition();
		fractions /= cellDimension;
		value = originalValue * (1.0f - fractions.x) * (1.0f - fractions.y) * (1.0f - fractions.z);
		xMinyMinzMin->addNewVelocity(value);
		deductedValue -= value;

		value = originalValue *  (1.0f - fractions.x) * (1.0f - fractions.y) * fractions.z;
		xMinyMinzMax->addNewVelocity(value);
		deductedValue -= value;

		value = originalValue *  (1.0f - fractions.x) * (fractions.y) * (1.0f - fractions.z);
		xMinyMaxzMin->addNewVelocity(value);
		deductedValue -= value;

		value = originalValue *  (1.0f - fractions.x) * (fractions.y) * fractions.z;
		xMinyMaxzMax->addNewVelocity(value);
		deductedValue -= value;

		value = originalValue * (fractions.x) * (1.0f - fractions.y) * (1.0f - fractions.z);
		xMaxyMinzMin->addNewVelocity(value);
		deductedValue -= value;

		value = originalValue *  (fractions.x) * (1.0f - fractions.y) * fractions.z;
		xMaxyMinzMax->addNewVelocity(value);
		deductedValue -= value;

		value = originalValue *  (fractions.x) * (fractions.y) * (1.0f - fractions.z);
		xMaxyMaxzMin->addNewVelocity(value);
		deductedValue -= value;

		value = originalValue *  (fractions.x) * (fractions.y) * fractions.z;
		xMaxyMaxzMax->addNewVelocity(value);
		deductedValue -= value;
	}
	/*
	else if(target != nullptr && target->size() == 4) {
		bool xSame = true, ySame = true, zSame = true;
		float x, y, z;
		for(int i = 0; i < 4; i++) {
			FluidPoint* point = target->getPoint(i);
			if(i == 0) {
				x = point->getX();
				y = point->getY();
				z = point->getZ();
			}
			else {
				xSame = xSame && fequals(x, point->getX());
				ySame = ySame && fequals(y, point->getY());
				zSame = zSame && fequals(z, point->getZ());
			}
		}

		FluidPoint* point1 = target->getPoint(0);
		FluidPoint* point2 = target->getPoint(1);
		FluidPoint* point3 = target->getPoint(2);
		FluidPoint* point4 = target->getPoint(3);
		glm::vec3 value1, value2, value3, value4;
		float sub1, sub2;

		glm::vec3 fractions = position - point1->getPosition();
		fractions /= cellDimension;
		if(xSame) {
			sub1 = fractions.y;
			sub2 = fractions.z;
		}
		else if(ySame) {
			sub1 = fractions.x;
			sub2 = fractions.z;
		}
		else if(zSame) {
			sub1 = fractions.x;
			sub2 = fractions.z;
		}

		value1 = originalValue * (1.0f - sub1) * (1.0f - sub2);
		value2 = originalValue * (1.0f - sub1) * (sub2);
		value3 = originalValue * (sub1) * (1.0f - sub2);
		value4 = originalValue * (sub1) * (sub2);

		point1->addNewVelocity(value1);
		point2->addNewVelocity(value2);
		point3->addNewVelocity(value3);
		point4->addNewVelocity(value4);
		deductedValue -= (value1 + value2 + value3 + value4);
	}
	 */

	addNewVelocity(deductedValue);
}

void FluidPoint::velocityDiffusion(float scale, FluidCell* neighbours) {
	glm::vec3 value(0, 0, 0);

	for(int i = 0; i < neighbours->size(); i++) {
		value += neighbours->getPoint(i)->getCurrentVelocity();
	}

	value -= ((float) neighbours->size()) * getCurrentVelocity();
	setNewVelocity(getCurrentVelocity() + (value * scale));
}

float FluidPoint::getProperty(Property property) {
	return m_properties[property];
}

void FluidPoint::setProperty(Property property, float value) {
	m_properties[property] = value;
}

void FluidPoint::addProperty(Property property, float value) {
	if(m_properties[property] < std::numeric_limits<float>::max())
		m_properties[property] = m_properties[property] + value;
}

glm::vec3 FluidPoint::getCurrentVelocity(){
	return m_currentVelocity;
}

void FluidPoint::setCurrentVelocity(float x, float y, float z){
	m_currentVelocity.x = x;
	m_currentVelocity.y = y;
	m_currentVelocity.z = z;
}

void FluidPoint::setCurrentVelocity(glm::vec3 velocity) {
	setCurrentVelocity(velocity.x, velocity.y, velocity.z);
}

void FluidPoint::addCurrentVelocity(glm::vec3 velocity) {
	m_currentVelocity += velocity;
}

glm::vec3 FluidPoint::getNewVelocity() {
	return m_newVelocity;
}

void FluidPoint::setNewVelocity(float x, float y, float z) {
	m_newVelocity.x = x;
	m_newVelocity.y = y;
	m_newVelocity.z = z;
}

void FluidPoint::setNewVelocity(glm::vec3 velocity) {
	setNewVelocity(velocity.x, velocity.y, velocity.z);
}

void FluidPoint::addNewVelocity(glm::vec3 velocity) {
	m_newVelocity += velocity;
}

glm::vec3 FluidPoint::getPosition() {
	return m_position;
}

void FluidPoint::setPosition(float x, float y, float z) {
	setX(x);
	setY(y);
	setZ(z);
}

void FluidPoint::setPosition(glm::vec3 position) {
	setPosition(position.x, position.y, position.z);
}

float FluidPoint::getX() {
	return m_position.x;
}

void FluidPoint::setX(float x) {
	m_position.x = x;
}

float FluidPoint::getY() {
	return m_position.y;
}

void FluidPoint::setY(float y) {
	m_position.y = y;
}

float FluidPoint::getZ() {
	return m_position.z;
}

void FluidPoint::setZ(float z) {
	m_position.z = z;
}

void FluidPoint::setTexture(Texture *texture) {
	m_cube->setTexture(texture);
}

void FluidPoint::render(float millis, glm::mat4 &transMatrix) {
	//m_cube->setScale(getProperty(INK_CURRENT), getProperty(INK_CURRENT), getProperty(INK_CURRENT));
	m_cube->render(millis, transMatrix);
}
