//
// Created by brent on 11-11-17.
//

#include "Triangle.h"

Triangle::Triangle(GLuint shaderProgram, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, Texture* texture): VertexPrimitive(shaderProgram) {
	if(texture != nullptr) {
		createTexturedTriangle(x1, y1, z1, x2, y2, z2, x3, y3, z3, texture);
	}
	else {
		createUntexturedTriangle(x1, y1, z1, x2, y2, z2, x3, y3, z3);
	}
}

Triangle::~Triangle() {

}

void Triangle::setTexture(Texture *texture) {
	int textureDimension = (mTexture != nullptr ? mTexture->getDimension() : 0);
	float x1, x2, x3, y1, y2, y3, z1, z2, z3;
	int index = 0;
	setUseTextures(true);
	
	x1 = mVertices[index];
	y1 = mVertices[index + 1];
	z1 = mVertices[index + 2];
	index += textureDimension;
	
	x2 = mVertices[index];
	y2 = mVertices[index + 1];
	z2 = mVertices[index + 2];
	index += textureDimension;
	
	x3 = mVertices[index];
	y3 = mVertices[index + 1];
	z3 = mVertices[index + 2];
	
	clear();
	createTexturedTriangle(x1, y1, z1, x2, y2, z2, x3, y3, z3, texture);
}

void Triangle::createTexturedTriangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, Texture *texture) {
	setUseTextures(true);
	mTexture = texture;
	
	addPoint(x1, y1, z1);
	for(int i = 0; i < texture->getDimension(); i++)
		addVertexPart(0.0f);
	
	addPoint(x2, y2, z2);
	if(texture->getDimension() >= 1)
		addVertexPart(0.5f);
	if(texture->getDimension() >= 2)
		addVertexPart(1.0f);
	if(texture->getDimension() == 3)
		addVertexPart(0.5f);
	
	addPoint(x3, y3, z3);
	if(texture->getDimension() >= 1)
		addVertexPart(1.0f);
	if(texture->getDimension() >= 2)
		addVertexPart(0.0f);
	if(texture->getDimension() == 3)
		addVertexPart(1.0f);
		
	init();
}

void Triangle::createUntexturedTriangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3) {
	addPoint(x1, y1, z1);
	addPoint(x2, y2, z2);
	addPoint(x3, y3, z3);
	
	init();
}

void Triangle::addPoint(float x, float y, float z) {
	int element = addVertexPart(x);
	addVertexPart(y);
	addVertexPart(z);
	addElementPart(element);
}

void Triangle::beforeInit() {

}

void Triangle::afterInit() {

}

void Triangle::beforeRender() {

}

void Triangle::afterRender() {

}

void Triangle::beforeBindUniforms() {

}

void Triangle::afterBindUniforms() {

}
