//
// Created by brent on 19-1-18.
//

#ifndef CAS_SHADERPROGRAM_H
#define CAS_SHADERPROGRAM_H

#include <GL/glew.h>
#include "ShaderBase.h"
#include <iostream>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/detail/type_mat.hpp>

#include <map>

class ShaderProgram {
public:
	ShaderProgram();
	ShaderProgram(ShaderBase& vertexShader, ShaderBase& fragmentShader);
	~ShaderProgram();
	
	void attachShader(ShaderBase& shader);
	
	void setUniform(const std::string &name, bool& value);
	void setUniform(const std::string &name, int& value);
	void setUniform(const std::string &name, float& value);
	void setUniform(const std::string &name, glm::vec3& vec);
	void setUniform(const std::string &name, glm::vec4& vec);
	void setUniform(const std::string &name, glm::mat3& mat);
	void setUniform(const std::string &name, glm::mat4& mat);

	void setUniform(const char* name, bool& value);
	void setUniform(const char* name, int& value);
	void setUniform(const char* name, float& value);
	void setUniform(const char* name, glm::vec3& vec);
	void setUniform(const char* name, glm::vec4& vec);
	void setUniform(const char* name, glm::mat3& mat);
	void setUniform(const char* name, glm::mat4& mat);

	GLint getAttributeLocation(const char* name);
	GLint getAttributeLocation(std::string name);

	GLuint getProgram();

protected:
	GLint getUniform(const char* name);
	GLint getUniform(const std::string& name);

protected:
	GLuint mProgram;

	std::map<std::string, GLint> mAttribCache;
	std::map<std::string, GLint> mUniformCache;
	std::map<GLint, float> mFloatCache;
	std::map<GLint, bool> mBoolCache;
	std::map<GLint, int> mIntCache;
	std::map<GLint, glm::vec3> mVec3Cache;
	std::map<GLint, glm::vec4> mVec4Cache;
};


#endif //CAS_SHADERPROGRAM_H
