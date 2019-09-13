//
// Created by brent on 19-1-18.
//

#ifndef CAS_SHADERBASE_H
#define CAS_SHADERBASE_H

#include <GL/glew.h>
#include <string>

class ShaderBase {
public:
	ShaderBase(const GLchar* shaderPath, GLenum shaderType);
	virtual ~ShaderBase();
	
	GLuint getShader();
	const GLchar* getPath();
	GLenum getType();
	
	std::string getShaderError();
	std::string getStringType();
	
protected:
	char* getCode();
	bool createShader(const char* shaderCode);

protected:
	GLuint mShader;
	const GLchar* mShaderPath;
	GLenum mShaderType;
};


#endif //CAS_SHADERBASE_H
