//
// Created by brent on 27.07.18.
//

#include <iostream>
#include <tiny_obj_loader.h>
#include "Model.h"
#include "../FFD.h"

Model::Model(ShaderProgram* shaderProgram, std::string filepath): m_shader(shaderProgram) {
	load(filepath);
}

void Model::load(std::string filepath) {
	clear();

	tinyobj::attrib_t attrib;
	std::string err;
	bool loaded = tinyobj::LoadObj(&attrib, &m_shapes, &m_materials, &err, filepath.c_str());

	if(!err.empty()) {
		std::cout << err << std::endl;
	}

	if(loaded) {
		m_positionAttrib = m_shader->getAttributeLocation("position");
		m_normalAttrib = m_shader->getAttributeLocation("normal");
		m_textureAttrib = m_shader->getAttributeLocation("inTexture1");

		unsigned int indexCounter = 0;

		for(int meshIndex = 0; meshIndex < m_shapes.size(); meshIndex++) {
			int indexOffset = 0;
			std::vector<float> vertexData;
			std::vector<GLuint> elementData;
			std::vector<unsigned int> faces;
			std::vector<unsigned int> materials;
			bool hasTexture = false;

			for(int faceIndex = 0; faceIndex < m_shapes[meshIndex].mesh.num_face_vertices.size(); faceIndex++) {
				int fv = m_shapes[meshIndex].mesh.num_face_vertices[faceIndex];

				for(int vertexIndex = 0; vertexIndex < fv; vertexIndex++) {
					tinyobj::index_t index = m_shapes[meshIndex].mesh.indices[indexOffset + vertexIndex];
					int vI = index.vertex_index;
					int nI = index.normal_index;
					int tI = index.texcoord_index;
					unsigned long hash;
					if(attrib.texcoords.size() > tI * 2)
						hash = nI + tI * attrib.normals.size() + vI * attrib.normals.size() * attrib.texcoords.size();
					else
						hash = nI + vI * attrib.normals.size();
					//std::cout << hash << std::endl;
					if(m_indexMap.count(hash) == 0) {
						vertexData.push_back(attrib.vertices[3 * vI + 0]);
						vertexData.push_back(attrib.vertices[3 * vI + 1]);
						vertexData.push_back(attrib.vertices[3 * vI + 2]);
						vertexData.push_back(attrib.normals[3 * nI + 0]);
						vertexData.push_back(attrib.normals[3 * nI + 1]);
						vertexData.push_back(attrib.normals[3 * nI + 2]);
						if(2 * tI < attrib.texcoords.size()) {
							hasTexture = true;
							vertexData.push_back(attrib.texcoords[2 * tI + 0]);
							vertexData.push_back(attrib.texcoords[2 * tI + 1]);
						}
						m_indexMap[hash] = indexCounter;
						indexCounter++;
					}
					elementData.push_back(m_indexMap[hash]);
				}

				indexOffset += fv;
				//std::cout << "FV: " << fv << std::endl;
				faces.push_back(fv);
				materials.push_back(m_shapes[meshIndex].mesh.material_ids[faceIndex]);
			}

			m_vertexDataArray.push_back(vertexData);
			m_elementBufferArray.push_back(elementData);
			m_faceArray.push_back(faces);
			m_faceMaterialsArray.push_back(materials);
			m_hasTexture.push_back(hasTexture);
		}
		init();
	}
	else {
		std::cout << "Not able to load: " << filepath << std::endl;
	}
}

void Model::clear() {

}

void Model::clearGL() {
	m_ebos.clear();
	m_vbos.clear();

	for(int i = 0; i < m_ebos.size(); i++) {
		glDeleteBuffers(1, &m_ebos[i]);
	}
	for(int i = 0; i < m_vbos.size(); i++) {
		glDeleteBuffers(1, &m_vbos[i]);
	}
	glDeleteVertexArrays(1, &m_vao);
}

void Model::init() {
	std::vector<std::vector<float>>& vertexArray = (m_renderVertexDataArray.empty() ? m_vertexDataArray : m_renderVertexDataArray);

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	for(int meshIndex = 0; meshIndex < vertexArray.size(); meshIndex++) {
		GLuint vbo = 0, ebo = 0;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vertexArray[meshIndex].size() * sizeof(float), vertexArray[meshIndex].data(), GL_STATIC_DRAW);

		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferArray[meshIndex].size() * sizeof(GLuint), m_elementBufferArray[meshIndex].data(), GL_STATIC_DRAW);


		int stride = (m_hasTexture[meshIndex] ? 8 : 6);
		int offset = 0;

		glEnableVertexAttribArray(m_positionAttrib);
		glVertexAttribPointer(m_positionAttrib, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), nullptr);
		offset += 3 * sizeof(float);

		glEnableVertexAttribArray(m_normalAttrib);
		glVertexAttribPointer(m_normalAttrib, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*) offset);
		offset += 3 * sizeof(float);

		if(m_hasTexture[meshIndex]) {
			glEnableVertexAttribArray(m_textureAttrib);
			glVertexAttribPointer(m_textureAttrib, 2, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void *) offset);
		}

		m_ebos.push_back(ebo);
		m_vbos.push_back(vbo);
	}
}

void Model::render(float deltaMillis) {
	glm::mat4 modelMatrix = getModelMatrix();
	render(deltaMillis, false, modelMatrix);
}

void Model::render(float deltaMillis, glm::mat4 &transMatrix) {
	render(deltaMillis, true, transMatrix);
}

void Model::render(float deltaMillis, bool transform, glm::mat4 &transMatrix) {
	glm::mat4 modelMatrix;

	glBindVertexArray(m_vao);

	if(transform) {
		modelMatrix = transMatrix * getModelMatrix();
	}
	else {
		modelMatrix = getModelMatrix();
	}

	m_shader->setUniform("modelMatrix", modelMatrix);

	std::vector<std::vector<float>>& vertexArray = (m_renderVertexDataArray.empty() ? m_vertexDataArray : m_renderVertexDataArray);
	for(int i = 0; i < vertexArray.size(); i++) {
		if(m_elementBufferArray[i].size() != 0) {
			glDrawElements(GL_TRIANGLES, m_elementBufferArray[i].size(), GL_UNSIGNED_INT, nullptr);
		}
		else {
			glDrawArrays(GL_TRIANGLES, 0, vertexArray[i].size());
		}
	}
}

void Model::transform(FFD *ffd, glm::mat4& transMatrix) {
	m_renderVertexDataArray.clear();
	int vertexSize = 3 + 3 + 2;
	glm::vec3 tempVec;

	glm::mat4 modelMatrix = getModelMatrix() * transMatrix;

	for(int i = 0; i < m_vertexDataArray.size(); i++) {
		std::vector<float> tempVertexArray;

		for(int j = 0; j < m_vertexDataArray[i].size(); j += vertexSize) {
			tempVec = glm::vec3(m_vertexDataArray[i][j], m_vertexDataArray[i][j + 1], m_vertexDataArray[i][j + 2]);
			glm::vec4 tempVec2(tempVec, 1);
			tempVec2 = modelMatrix * tempVec2;
			tempVec = glm::vec3(tempVec2);
			tempVec = ffd->transformPoint(tempVec);
			tempVec2 = glm::vec4(tempVec, 1);
			tempVec2 = glm::inverse(modelMatrix) * tempVec2;
			tempVertexArray.push_back(tempVec2.x);
			tempVertexArray.push_back(tempVec2.y);
			tempVertexArray.push_back(tempVec2.z);

			for(int k = 3; k < vertexSize; k++) {
				tempVertexArray.push_back(m_vertexDataArray[i][j + k]);
			}
		}

		m_renderVertexDataArray.push_back(tempVertexArray);
	}

	clearGL();
	init();
}
