//
// Created by brent on 27.07.18.
//

#ifndef CAS_BALL_H
#define CAS_BALL_H



#include "Renderable.h"
#include "../Shaders/ShaderProgram.h"
#include <vector>
#include <string>
#include <map>
#include <tiny_obj_loader.h>

class Model: public Renderable {
public:
	Model(ShaderProgram* shaderProgram, std::string filepath);

	void load(std::string filepath);
	void clear();

	void init() override;

	void render(float deltaMillis) override;

	void render(float deltaMillis, glm::mat4 &transMatrix) override;

	void render(float deltaMillis, bool transform, glm::mat4& transMatrix);

	void transform(FFD *ffd, glm::mat4& transMatrix) override;

private:
	void clearGL();

private:

	std::vector<tinyobj::shape_t> m_shapes;
	std::vector<tinyobj::material_t> m_materials;

	GLuint m_vao;
	std::vector<GLuint> m_ebos;
	std::vector<GLuint> m_vbos;

	std::vector<bool> m_hasTexture;
	std::vector<std::vector<float>> m_vertexDataArray;
	std::vector<std::vector<float>> m_renderVertexDataArray;
	std::vector<std::vector<GLuint>> m_elementBufferArray;
	std::vector<std::vector<unsigned int>> m_faceArray;
	std::vector<std::vector<unsigned int>> m_faceMaterialsArray;

	std::map<unsigned long, GLuint> m_indexMap;

	ShaderProgram* m_shader;
	GLint m_modelMatrixUni;
	GLint m_positionAttrib;
	GLint m_normalAttrib;
	GLint m_textureAttrib;
};


#endif //CAS_BALL_H
