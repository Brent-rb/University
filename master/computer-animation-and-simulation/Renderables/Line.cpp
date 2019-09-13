//
// Created by brent on 15.08.18.
//

#include <iostream>
#include "Line.h"

void Line::beforeInit() {

}

void Line::afterInit() {

}

void Line::beforeRender() {
	glLineWidth(m_width);
}

void Line::afterRender() {

}

void Line::beforeBindUniforms() {

}

void Line::afterBindUniforms() {

}

Line::Line(GLuint shaderProgram, float width): VertexPrimitive(shaderProgram, 3, false, false, false) {
	mDrawingMode = GL_LINE_STRIP;
	m_width = width;

}

void Line::createLine() {

}
