//
// Created by brent on 11-11-17.
//

#ifndef CAS_TRIANGLE_H
#define CAS_TRIANGLE_H

#include "VertexPrimitive.h"

class Triangle: public VertexPrimitive {
public:
	Triangle(GLuint shaderProgram, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, Texture* texture = nullptr);
	~Triangle();
	
	void setTexture(Texture* texture);
	
protected:
	void beforeInit() override;
	void afterInit() override;
	
	void beforeRender() override;
	void afterRender() override;
	
	void beforeBindUniforms() override;
	void afterBindUniforms() override;
	
private:
	void createTexturedTriangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, Texture* texture);
	void createUntexturedTriangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);
	
	void addPoint(float x, float y, float z);
	
};


#endif //CAS_TRIANGLE_H
