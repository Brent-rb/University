//
// Created by brent on 17-11-17.
//

#ifndef CAS_VERTEXPRIMITIVE_H
#define CAS_VERTEXPRIMITIVE_H

#include "Renderable.h"
#include "../Textures/Texture.h"
#include <GL/gl.h>
#include <string>
#include <vector>

class VertexPrimitive: public Renderable {
public:
	VertexPrimitive(GLuint shaderProgram, Texture* texture, int vertexDimension = 3, bool useNormals = true, bool useElementsArray = false);
	VertexPrimitive(GLuint shaderProgram, int vertexDimension = 3, bool useNormals = true, bool useTextures = false, bool useElementsArray = false);
	virtual ~VertexPrimitive();
	
	virtual void init();
	virtual void render(float millis);
	virtual void render(float millis, glm::mat4& transMatrix);
	
	void setDrawingMode(GLuint drawingMode);
	
	void setUseNormals(bool userNormals);
	void setUseTextures(bool useTextures);
	void setUseElementsArray(bool useElementsArray);
	
	unsigned int addVertexPart(float vertexPart);
	unsigned int addVertex(glm::vec2 vertex);
	unsigned int addVertex(glm::vec3 vertex);
	unsigned int addVertex(glm::vec4 vertex);
	
	void addElementPart(GLuint elementPart);
	void addElement(glm::vec2 element);
	void addElement(glm::vec3 element);
	void addElement(glm::vec4 element);

	void printInfo();

	void transform(FFD *ffd, glm::mat4& transMatrix) override;

protected:
	virtual void render(float millis, bool transform, glm::mat4& transMatrix);
	
	void clear();
	void clearGL();
	
	void setVertices(float* vertices, int size);
	void setElements(GLuint* elements, int size);
	
	void bindUniforms(glm::mat4& modelMatrix);
	
	virtual void beforeInit() = 0;
	virtual void afterInit() = 0;
	
	virtual void beforeRender() = 0;
	virtual void afterRender() = 0;
	
	virtual void beforeBindUniforms() = 0;
	virtual void afterBindUniforms() = 0;
	
private:
	void printVector(std::string name, std::vector<float>& vector, int dimension);
	void printVector(std::string name, std::vector<GLuint>& vector, int dimension);
	

	
protected:
	bool mUseNormals;
	bool mUseTextures;
	bool mUseElementsArray;
	
	int mVertexDimension;
	
	GLuint mShaderProgram;
	GLuint mDrawingMode;
	
	GLuint mVAO;
	GLuint mVBO;
	GLuint mEBO;
	
	GLint mPositionAttrib;
	GLint mNormalAttrib;
	GLint mTextureAttrib;
	GLint mModelMatrixUni;
	
	Texture* mTexture;
	
	std::vector<float> mVertices;
	std::vector<GLuint> mElements;

	std::vector<float> mRenderVertices;
};


#endif //CAS_VERTEXPRIMITIVE_H
