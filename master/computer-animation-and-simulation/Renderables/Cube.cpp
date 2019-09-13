//
// Created by brent on 25-11-17.
//

#include <iostream>
#include "Cube.h"

Cube::Cube(GLuint shaderProgram, glm::vec3 center, float length, Texture *texture): VertexPrimitive(shaderProgram) {
	setUseNormals(true);
	setUseElementsArray(false);
	createCube(center, length, texture);
}

Cube::~Cube() {

}

void Cube::setTexture(Texture *texture) {
	mTexture = texture;
	setUseTextures(true);
}

void Cube::beforeInit() {

}

void Cube::afterInit() {

}

void Cube::beforeRender() {

}

void Cube::afterRender() {

}

void Cube::beforeBindUniforms() {

}

void Cube::afterBindUniforms() {

}

void Cube::createCube(glm::vec3 center, float length, Texture* texture) {
	bool hasTexture = (texture != nullptr);
	glm::vec3 bottomBottomLeft, bottomTopLeft, bottomBottomRight, bottomTopRight, topTopLeft, topBottomLeft, topBottomRight, topTopRight;
	glm::vec2 bottomLeftT(0.0f, 0.0f), bottomRightT(1.0f, 0.0f), topLeftT(0.0f, 1.0f), topRightT(1.0f, 1.0f);
	glm::vec3 frontNormal(0.0f, 0.0f, -1.0f), backNormal(0.0f, 0.0f, 1.0f), leftNormal(-1.0f, 0.0f, 0.0f), rightNormal(1.0f, 0.0f, 0.0f), topNormal(0.0f, 1.0f, 0.0f), bottomNormal(0.0f, -1.0f, 0.0f);
	float diagonal = (length / 2.0f) / glm::sin(glm::radians(45.0f));
	
	if(hasTexture) {
		mTexture = texture;
		setUseTextures(true);
	}
	
	bottomBottomLeft = center + glm::vec3(-diagonal, -diagonal, -diagonal);
	bottomTopLeft = center + glm::vec3(-diagonal, -diagonal, diagonal);
	bottomBottomRight = center + glm::vec3(diagonal, -diagonal, -diagonal);
	bottomTopRight = center + glm::vec3(diagonal, -diagonal, diagonal);
	
	topBottomLeft = center + glm::vec3(-diagonal, diagonal, -diagonal);
	topTopLeft = center + glm::vec3(-diagonal, diagonal, diagonal);
	topBottomRight = center + glm::vec3(diagonal, diagonal, -diagonal);
	topTopRight = center + glm::vec3(diagonal, diagonal, diagonal);
	
	//BOTTOM
	addPoint(bottomTopLeft, bottomNormal, topLeftT);
	addPoint(bottomBottomLeft, bottomNormal, bottomLeftT);
	addPoint(bottomBottomRight, bottomNormal, bottomRightT);
	
	addPoint(bottomTopRight, bottomNormal, topRightT);
	addPoint(bottomTopLeft, bottomNormal, topLeftT);
	addPoint(bottomBottomRight, bottomNormal, bottomRightT);
	
	//TOP
	addPoint(topBottomLeft, topNormal, bottomLeftT);
	addPoint(topTopLeft, topNormal, topLeftT);
	addPoint(topBottomRight, topNormal, bottomRightT);
	
	addPoint(topTopLeft, topNormal, topLeftT);
	addPoint(topTopRight, topNormal, topRightT);
	addPoint(topBottomRight, topNormal, bottomRightT);
	
	//LEFT
	addPoint(bottomBottomLeft, leftNormal, bottomRightT);
	addPoint(bottomTopLeft, leftNormal, bottomLeftT);
	addPoint(topBottomLeft, leftNormal, topRightT);
	
	addPoint(topTopLeft, leftNormal, topLeftT);
	addPoint(topBottomLeft, leftNormal, topRightT);
	addPoint(bottomTopLeft, leftNormal, bottomLeftT);
	
	//RIGHT
	addPoint(bottomTopRight, rightNormal, bottomRightT);
	addPoint(bottomBottomRight, rightNormal, bottomLeftT);
	addPoint(topBottomRight, rightNormal, topLeftT);
	
	addPoint(topBottomRight, rightNormal, topLeftT);
	addPoint(topTopRight, rightNormal, topRightT);
	addPoint(bottomTopRight, rightNormal, bottomRightT);
	
	//FRONT
	addPoint(bottomBottomRight, frontNormal, bottomRightT);
	addPoint(bottomBottomLeft, frontNormal, bottomLeftT);
	addPoint(topBottomLeft, frontNormal, topLeftT);
	
	addPoint(bottomBottomRight, frontNormal, bottomRightT);
	addPoint(topBottomLeft, frontNormal, topLeftT);
	addPoint(topBottomRight, frontNormal, topRightT);
	
	//BACK
	addPoint(bottomTopLeft, backNormal, bottomLeftT);
	addPoint(bottomTopRight, backNormal, bottomRightT);
	addPoint(topTopLeft, backNormal, topLeftT);

	addPoint(topTopLeft, backNormal, topLeftT);
	addPoint(bottomTopRight, backNormal, bottomRightT);
	addPoint(topTopRight, backNormal, topRightT);
	
	init();
}

void Cube::addPoint(glm::vec3 vertex, glm::vec3 normal, glm::vec2 textureCords) {
	addVertex(vertex);
	addVertex(normal);
	if(mUseTextures)
		addVertex(textureCords);
	
}
