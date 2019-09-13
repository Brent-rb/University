//
// Created by brent on 24-11-17.
//

#ifndef CAS_SQUARE_H
#define CAS_SQUARE_H

#include "VertexPrimitive.h"

class Square: public VertexPrimitive {
public:
	Square(GLuint shaderProgram, glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 point4, glm::vec3 normal, Texture* texture = nullptr);
	~Square();
	
	void setTexture(Texture* texture);

protected:
	void beforeInit() override;
	void afterInit() override;
	
	void beforeRender() override;
	void afterRender() override;
	
	void beforeBindUniforms() override;
	void afterBindUniforms() override;

private:
	void createTexturedSquare(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 point4, glm::vec3 normal, Texture* texture);
	void createUntexturedSquare(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 point4, glm::vec3 normal);
	
	void addPoint(glm::vec3 point);
};


#endif //CAS_SQUARE_H
