//
// Created by brent on 25-11-17.
//

#ifndef CAS_CUBE_H
#define CAS_CUBE_H

#include "VertexPrimitive.h"

class Cube: public VertexPrimitive {
public:
	Cube(GLuint shaderProgram, glm::vec3 center, float length, Texture* texture = nullptr);
	~Cube();
	
	void setTexture(Texture* texture);

protected:
	void beforeInit() override;
	void afterInit() override;
	
	void beforeRender() override;
	void afterRender() override;
	
	void beforeBindUniforms() override;
	void afterBindUniforms() override;

private:
	void createCube(glm::vec3 center, float length, Texture* texture);
	void addPoint(glm::vec3 vertex, glm::vec3 normal, glm::vec2 textureCords);
};


#endif //CAS_CUBE_H
