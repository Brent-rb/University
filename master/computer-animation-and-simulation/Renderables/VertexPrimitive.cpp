//
// Created by brent on 17-11-17.
//

#include <iostream>
#include "VertexPrimitive.h"
#include "../FFD.h"

VertexPrimitive::VertexPrimitive(GLuint shaderProgram, Texture *texture, int vertexDimension, bool useNormals, bool useElementsArray): mShaderProgram(shaderProgram), mDrawingMode(GL_TRIANGLES), mTexture(texture), mVertexDimension(vertexDimension), mUseNormals(useNormals), mUseTextures(true), mUseElementsArray(useElementsArray) {

}

VertexPrimitive::VertexPrimitive(GLuint shaderProgram, int vertexDimension, bool useNormals, bool useTextures, bool useElementsArray): mShaderProgram(shaderProgram), mDrawingMode(GL_TRIANGLES), mTexture(nullptr), mVertexDimension(vertexDimension), mUseNormals(useNormals), mUseTextures(useTextures), mUseElementsArray(useElementsArray) {

}

VertexPrimitive::~VertexPrimitive() {
	clear();
}

void VertexPrimitive::clear() {
	clearGL();
	mVertices.clear();
	mElements.clear();
}

void VertexPrimitive::clearGL() {
	if(!mElements.empty() && mEBO > 0) {
		glDeleteBuffers(1, &mEBO);
	}
	if(!mVertices.empty() && mVBO > 0) {
		glDeleteBuffers(1, &mVBO);
		glDeleteVertexArrays(1, &mVAO);
	}
}

void VertexPrimitive::init() {
	beforeInit();

	std::vector<float>& verticesReference = (mRenderVertices.empty() ? mVertices : mRenderVertices);

	if(!verticesReference.empty()) {
		glGenVertexArrays(1, &mVAO);
		glBindVertexArray(mVAO);

		glGenBuffers(1, &mVBO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBufferData(GL_ARRAY_BUFFER, verticesReference.size() * sizeof(float), verticesReference.data(), GL_STATIC_DRAW);
		
		if(!mElements.empty()) {
			glGenBuffers(1, &mEBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, mElements.size() * sizeof(GLuint), mElements.data(), GL_STATIC_DRAW);
		}
		
		mModelMatrixUni = glGetUniformLocation(mShaderProgram, "modelMatrix");
		mPositionAttrib = glGetAttribLocation(mShaderProgram, "position");
		mNormalAttrib = glGetAttribLocation(mShaderProgram, "normal");
		mTextureAttrib = glGetAttribLocation(mShaderProgram, "inTexture1");
		
		int stride = mVertexDimension;
		int offset = 0;
		
		if(mUseTextures) {
			stride += mTexture->getDimension();
		}
		if(mUseNormals) {
			stride += mVertexDimension;
		}
		
		glEnableVertexAttribArray(mPositionAttrib);
		glVertexAttribPointer(mPositionAttrib, mVertexDimension, GL_FLOAT, GL_FALSE, stride * sizeof(float), nullptr);
		offset += mVertexDimension * sizeof(float);
		
		if(mUseNormals) {
			glEnableVertexAttribArray(mNormalAttrib);
			glVertexAttribPointer(mNormalAttrib, mVertexDimension, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void *) offset);
			offset += mVertexDimension * sizeof(float);
		}
		
		if(mUseTextures) {
			glEnableVertexAttribArray(mTextureAttrib);
			glVertexAttribPointer(mTextureAttrib, mTexture->getDimension(), GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset));
			offset += mTexture->getDimension() * sizeof(float);
		}
	}
	afterInit();
}

void VertexPrimitive::render(float millis) {
	glm::mat4 modelMatrix = getModelMatrix();
	render(millis, false, modelMatrix);
}

void VertexPrimitive::render(float deltaMillis, glm::mat4& transMatrix) {
	render(deltaMillis, true, transMatrix);
}

void VertexPrimitive::render(float millis, bool transform, glm::mat4 &transMatrix) {
	glm::mat4 modelMatrix;
	
	beforeRender();
	
	if(mUseTextures)
		mTexture->apply();
	glBindVertexArray(mVAO);
	
	if(transform) {
		modelMatrix = transMatrix * getModelMatrix();
	}
	else {
		modelMatrix = getModelMatrix();
	}
	bindUniforms(modelMatrix);
	
	if(mUseElementsArray) {
		glDrawElements(mDrawingMode, mElements.size(), GL_UNSIGNED_INT, nullptr);
	}
	else {
		glDrawArrays(mDrawingMode, 0, mVertices.size());
	}
	
	afterRender();
}

void VertexPrimitive::bindUniforms(glm::mat4& modelMatrix) {
	beforeBindUniforms();

	recalculateModelMatrix();
	glUniformMatrix4fv(mModelMatrixUni, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	afterBindUniforms();
}

void VertexPrimitive::setDrawingMode(GLuint drawingMode) {
	mDrawingMode = drawingMode;
}

void VertexPrimitive::setUseNormals(bool userNormals) {
	mUseNormals = userNormals;
}

void VertexPrimitive::setUseTextures(bool useTextures) {
	mUseTextures = useTextures;
}

void VertexPrimitive::setUseElementsArray(bool useElementsArray) {
	mUseElementsArray = useElementsArray;
}

void VertexPrimitive::setVertices(float *vertices, int size) {
	mVertices.assign(vertices, vertices + size);
}

void VertexPrimitive::setElements(GLuint *elements, int size) {
	mElements.assign(elements, elements + size);
}

unsigned int VertexPrimitive::addVertexPart(float vertexPart) {
	unsigned int textureDimension = (mUseTextures ? mTexture->getDimension() : 0);
	unsigned int elementIndex = mVertices.size() / (mVertexDimension + textureDimension);

	mVertices.push_back(vertexPart);

	return elementIndex;
}

unsigned int VertexPrimitive::addVertex(glm::vec2 vertex) {
	unsigned int textureDimension = (mUseTextures ? mTexture->getDimension() : 0);
	unsigned int elementIndex = mVertices.size() / (mVertexDimension + textureDimension);
	
	mVertices.push_back(vertex.x);
	mVertices.push_back(vertex.y);
	
	return elementIndex;
}

unsigned int VertexPrimitive::addVertex(glm::vec3 vertex) {
	unsigned int textureDimension = (mUseTextures ? mTexture->getDimension() : 0);
	unsigned int elementIndex = mVertices.size() / (mVertexDimension + textureDimension);
	
	mVertices.push_back(vertex.x);
	mVertices.push_back(vertex.y);
	mVertices.push_back(vertex.z);
	
	return elementIndex;
}

unsigned int VertexPrimitive::addVertex(glm::vec4 vertex) {
	unsigned int textureDimension = (mUseTextures ? mTexture->getDimension() : 0);
	unsigned int elementIndex = mVertices.size() / (mVertexDimension + textureDimension);
	
	mVertices.push_back(vertex.x);
	mVertices.push_back(vertex.y);
	mVertices.push_back(vertex.z);
	mVertices.push_back(vertex.w);
	
	return elementIndex;
}

void VertexPrimitive::addElementPart(GLuint elementPart) {
	mElements.push_back(elementPart);
}

void VertexPrimitive::addElement(glm::vec2 element) {
	addElementPart(element.x);
	addElementPart(element.y);
}

void VertexPrimitive::addElement(glm::vec3 element) {
	addElementPart(element.x);
	addElementPart(element.y);
	addElementPart(element.z);
}

void VertexPrimitive::addElement(glm::vec4 element) {
	addElementPart(element.x);
	addElementPart(element.y);
	addElementPart(element.z);
	addElementPart(element.w);
}

void VertexPrimitive::printVector(std::string name, std::vector<float>& vector, int dimension) {
	std::cout << name << std::endl;
	for(int i = 0; i < vector.size(); i++) {
		if(i > 0 && i % dimension == 0) {
			std::cout << std::endl;
		}
		std::cout << "\t" << vector[i] << " ";
	}
}

void VertexPrimitive::printInfo() {
	printVector(std::string("Vertices"), mVertices, mVertexDimension + (mTexture != nullptr ? mTexture->getDimension() : 0));
	std::cout << std::endl;
	printVector(std::string("Elements"), mElements, 3);
	std::cout << std::endl;
	std::cout << "PositionAttrib: " << mPositionAttrib << std::endl;
	std::cout << "VAO, VBO, EBO: (" << mVAO << ", " << mVBO << ", " << mEBO << ")" << std::endl;
}

void VertexPrimitive::printVector(std::string name, std::vector<GLuint> &vector, int dimension) {
	std::cout << name << std::endl;
	for(int i = 0; i < vector.size(); i++) {
		if(i > 0 && i % dimension == 0) {
			std::cout << std::endl;
		}
		std::cout << "\t" << vector[i] << " ";
	}
}

void VertexPrimitive::transform(FFD *ffd, glm::mat4& transMatrix) {
	mRenderVertices.clear();
	int vertexSize = 3 + (mUseNormals ? 3: 0) + (mUseTextures ? mTexture->getDimension(): 0);
	glm::vec3 tempVec;

	glm::mat4 modelMatrix = getModelMatrix() * transMatrix;

	for(int i = 0; i < mVertices.size(); i += vertexSize) {
		tempVec = glm::vec3(mVertices[i], mVertices[i + 1], mVertices[i + 2]);
		glm::vec4 tempVec2(tempVec, 1);
		tempVec2 = modelMatrix * tempVec2;
		tempVec = glm::vec3(tempVec2);
		tempVec = ffd->transformPoint(tempVec);
		tempVec2 = glm::vec4(tempVec, 1);
		tempVec2 = glm::inverse(modelMatrix) * tempVec2;
		mRenderVertices.push_back(tempVec2.x);
		mRenderVertices.push_back(tempVec2.y);
		mRenderVertices.push_back(tempVec2.z);
		for(int j = 3; j < vertexSize; j++) {
			mRenderVertices.push_back(mVertices[i + j]);
		}
	}

	clearGL();
	init();
}
