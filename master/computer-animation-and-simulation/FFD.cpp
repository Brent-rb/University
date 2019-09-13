//
// Created by brent on 16.08.18.
//

#include "FFD.h"
#include "OpenGLRenderer.h"
#include "FFDClickable.h"
#include "Renderables/Model.h"
#include "Help.h"

void FFD::update(InputBuffer *keyBuffer, glm::vec3 cameraPosition, glm::vec3 cameraDirection, float deltaMillis) {
	GameObject::update(keyBuffer, cameraPosition, cameraDirection, deltaMillis);

	glm::mat4 modelMatrix = getModelMatrix();
	if(true) {
		for(int i = 0; i < mRenderables.size(); i++) {
			mRenderables[i]->transform(this, modelMatrix);
		}
		for(int i = 0; i < mChildren.size(); i++) {
			mChildren[i]->transform(this, modelMatrix);
		}
		m_changed = false;
	}

	float xMin = -m_width * m_dimensions / 2.0;
	float yMin = -m_height * m_dimensions / 2.0;
	float zMin = -m_depth * m_dimensions / 2.0;

	for(int x = 0; x < m_width; x++) {
		for(int y = 0; y < m_height; y++) {
			for(int z = 0; z < m_depth; z++) {
				glm::vec4 pos(m_positions[x][y][z], 1);
				pos = modelMatrix * pos;
				m_editPoints[x][y][z]->setLocation(pos.x, pos.y, pos.z);
				m_editPoints[x][y][z]->update(keyBuffer, cameraPosition, cameraDirection, deltaMillis);
			}
		}
	}
}

void FFD::render(float deltaMillis, bool transform, glm::mat4 &transMatrix) {
	glm::mat4 modelMatrix = getModelMatrix();

	for(int x = 0; x < m_width; x++) {
		for(int y = 0; y < m_height; y++) {
			for(int z = 0; z < m_depth; z++) {
				((GameObject*)m_editPoints[x][y][z])->render(deltaMillis);
			}
		}
	}

	for(int i = 0; i < mRenderables.size(); i++) {
		mRenderables[i]->render(deltaMillis);
	}

	for(int i = 0; i < mChildren.size(); i++) {
		mChildren[i]->render(deltaMillis);
	}
}

FFD::FFD(OpenGLRenderer *renderer, int width, int height, int depth, float dimensions): GameObject(renderer), m_width(width), m_height(height), m_depth(depth), m_dimensions(dimensions) {
	m_model =  new Model(renderer->getShaderProgram(), std::string("/home/brent/Documents/CAS/Objects/ball.obj"));
	m_model->setScale(0.5, 0.5, 0.5);
	m_editPoints = new Clickable***[width];
	m_positions = new glm::vec3**[width];

	float xMin = -width * dimensions / 2.0;
	float yMin = -height * dimensions / 2.0;
	float zMin = -depth * dimensions / 2.0;

	for(int i = 0; i < width; i++) {
		m_editPoints[i] = new Clickable**[height];
		m_positions[i] = new glm::vec3*[height];

		for(int j = 0; j < height; j++) {
			m_editPoints[i][j] = new Clickable*[depth];
			m_positions[i][j] = new glm::vec3[depth];

			for(int k = 0; k < depth; k++) {
				m_editPoints[i][j][k] = new FFDClickable(renderer, m_model, m_positions[i][j][k], m_changed, mModelMatrix);
				glm::vec3 pos(i * dimensions + xMin, j * dimensions + yMin, k * dimensions + zMin);
				m_editPoints[i][j][k]->setLocation(pos.x, pos.y, pos.z);
				m_positions[i][j][k] = pos;
				renderer->addClickable(m_editPoints[i][j][k]);
			}
		}
	}

	//setLocation(-width * dimensions / 2.0, -height * dimensions / 2.0, -depth * dimensions / 2);
}

glm::vec3 FFD::transformPoint(glm::vec3 point) {
	glm::vec3 delta(m_width * m_dimensions / 2.0, m_height * m_dimensions / 2.0, m_depth * m_dimensions / 2.0);
	glm::vec3 origPoint = point + delta;
	glm::vec3 tempPoint = origPoint / m_dimensions;
	int xMin = (int) floor(tempPoint.x);
	int yMin = (int) floor(tempPoint.y);
	int zMin = (int) floor(tempPoint.z);
	int xMax = xMin + 1;
	int yMax = yMin + 1;
	int zMax = zMin + 1;

	if(!(xMin >= 0 && xMin < m_width))
		return point;

	if(!(yMin >= 0 && yMin < m_height))
		return point;

	if(!(zMin >= 0 && zMin < m_depth))
		return point;

	if(!(xMax >= 0 && xMax < m_width))
		return point;

	if(!(yMax >= 0 && yMax < m_height))
		return point;

	if(!(zMax >= 0 && zMax < m_depth))
		return point;

	glm::vec3 fractions(tempPoint.x - xMin, tempPoint.y - yMin, tempPoint.z - zMin);
	float contrib1 = (1.0f - fractions.x) * (1.0f - fractions.y) * (1.0f - fractions.z);
	float contrib2 = (1.0f - fractions.x) * (1.0f - fractions.y) * fractions.z;
	float contrib3 = (1.0f - fractions.x) * (fractions.y) * (1.0f - fractions.z);
	float contrib4 = (1.0f - fractions.x) * (fractions.y) * fractions.z;
	float contrib5 = (fractions.x) * (1.0f - fractions.y) * (1.0f - fractions.z);
	float contrib6 = (fractions.x) * (1.0f - fractions.y) * fractions.z;
	float contrib7 = (fractions.x) * (fractions.y) * (1.0f - fractions.z);
	float contrib8 = (fractions.x) * (fractions.y) * fractions.z;

	glm::vec3 result = m_positions[xMin][yMin][zMin] * contrib1 +
			m_positions[xMin][yMin][zMax] * contrib2 +
			m_positions[xMin][yMax][zMin] * contrib3 +
			m_positions[xMin][yMax][zMax] * contrib4 +
			m_positions[xMax][yMin][zMin] * contrib5 +
			m_positions[xMax][yMin][zMax] * contrib6 +
			m_positions[xMax][yMax][zMin] * contrib7 +
			m_positions[xMax][yMax][zMax] * contrib8;

	return result;
}
