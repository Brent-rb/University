//
// Created by brent on 24-11-17.
//

#include "Square.h"

Square::Square(GLuint shaderProgram, glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 point4, glm::vec3 normal, Texture *texture): VertexPrimitive(shaderProgram) {
	setUseNormals(true);
	setUseElementsArray(false);
	if(texture != nullptr) {

		createTexturedSquare(point1, point2, point3, point4, normal, texture);
	}
	else {
		createUntexturedSquare(point1, point2, point3, point4, normal);
	}
}

Square::~Square() {

}

void Square::setTexture(Texture *texture) {
	int offset = (mTexture != nullptr ? mTexture->getDimension() : 0);
	offset += 6;
	glm::vec3 points[4];
	
	points[0] = glm::vec3(mVertices[0], mVertices[1], mVertices[2]);
	points[1] = glm::vec3(mVertices[offset], mVertices[offset + 1], mVertices[offset + 2]);
	points[2] = glm::vec3(mVertices[offset * 2], mVertices[offset * 2 + 1], mVertices[offset * 2 + 2]);
	points[3] = glm::vec3(mVertices[offset * 5], mVertices[offset * 5 + 1], mVertices[offset * 5 + 2]);
	glm::vec3 normal = glm::vec3(mVertices[3], mVertices[4], mVertices[5]);
	clear();
	createTexturedSquare(points[0], points[1], points[2], points[3], normal, texture);
}

void Square::beforeInit() {

}

void Square::afterInit() {

}

void Square::beforeRender() {

}

void Square::afterRender() {

}

void Square::beforeBindUniforms() {

}

void Square::afterBindUniforms() {

}

void Square::createTexturedSquare(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 point4, glm::vec3 normal, Texture *texture) {
	setUseTextures(true);
	mTexture = texture;
	addPoint(point1);
	addPoint(normal);
	for(int i = 0; i < texture->getDimension(); i++)
		addVertexPart(0.0f);
	
	addPoint(point2);
	addPoint(normal);
	if(texture->getDimension() >= 1)
		addVertexPart(1.0f);
	if(texture->getDimension() >= 2)
		addVertexPart(0.0f);
	if(texture->getDimension() == 3)
		addVertexPart(0.0f);
	
	addPoint(point3);
	addPoint(normal);
	if(texture->getDimension() >= 1)
		addVertexPart(1.0f);
	if(texture->getDimension() >= 2)
		addVertexPart(1.0f);
	if(texture->getDimension() == 3)
		addVertexPart(0.0f);

	addPoint(point1);
	addPoint(normal);
	for(int i = 0; i < texture->getDimension(); i++)
		addVertexPart(0.0f);

	addPoint(point3);
	addPoint(normal);
	if(texture->getDimension() >= 1)
		addVertexPart(1.0f);
	if(texture->getDimension() >= 2)
		addVertexPart(1.0f);
	if(texture->getDimension() == 3)
		addVertexPart(0.0f);

	addPoint(point4);
	addPoint(normal);
	if(texture->getDimension() >= 1)
		addVertexPart(0.0f);
	if(texture->getDimension() >= 2)
		addVertexPart(1.0f);
	if(texture->getDimension() == 3)
		addVertexPart(0.0f);

	init();
}

void Square::createUntexturedSquare(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 point4, glm::vec3 normal) {
	setUseTextures(false);

	addPoint(point1);
	addPoint(normal);

	addPoint(point2);
	addPoint(normal);

	addPoint(point3);
	addPoint(normal);

	addPoint(point1);
	addPoint(normal);

	addPoint(point3);
	addPoint(normal);

	addPoint(point4);
	addPoint(normal);
	
	init();
}

void Square::addPoint(glm::vec3 point) {
	addVertex(point);
}
