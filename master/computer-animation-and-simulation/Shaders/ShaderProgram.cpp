//
// Created by brent on 19-1-18.
//

#include <glm/gtc/type_ptr.hpp>
#include "ShaderProgram.h"
#include "../Help.h"

ShaderProgram::ShaderProgram() {
	mProgram = glCreateProgram();
}

ShaderProgram::ShaderProgram(ShaderBase &vertexShader, ShaderBase &fragmentShader) {
	mProgram = glCreateProgram();
	attachShader(vertexShader);
	attachShader(fragmentShader);
}

ShaderProgram::~ShaderProgram() {

}

void ShaderProgram::attachShader(ShaderBase &shader) {
	glAttachShader(mProgram, shader.getShader());
}

void ShaderProgram::setUniform(const char* name, bool& value) {
	GLint loc = getUniform(name);
	if((mBoolCache.count(loc) > 0 && mBoolCache[loc] != value) || mBoolCache.count(loc) == 0) {
		mBoolCache[loc] = value;
		glUniform1i(getUniform(name), (int) value);
	}
}

void ShaderProgram::setUniform(const char* name, int& value) {
	GLint loc = getUniform(name);
	if(mIntCache.count(loc) == 0 || (mIntCache.count(loc) > 0 && mIntCache[loc] != value)) {
		mIntCache[loc] = value;
		glUniform1i(getUniform(name), value);
	}
}

void ShaderProgram::setUniform(const char* name, float& value) {
	GLint loc = getUniform(name);
	if(mFloatCache.count(loc) == 0 || (mFloatCache.count(loc) > 0 && !Help::equals(mFloatCache[loc], value))) {
		mFloatCache[loc] = value;
		glUniform1f(getUniform(name), value);
	}
}

void ShaderProgram::setUniform(const char* name, glm::vec3& vec) {
	GLint loc = getUniform(name);
	if(mVec3Cache.count(loc) == 0 || (mVec3Cache.count(loc) > 0 && vec != mVec3Cache[loc])) {
		mVec3Cache[loc] = vec;
		glUniform3f(getUniform(name), vec.x, vec.y, vec.z);
	}
}

void ShaderProgram::setUniform(const char* name, glm::vec4& vec) {
	GLint loc = getUniform(name);
	if(mVec4Cache.count(loc) == 0 || (mVec4Cache.count(loc) > 0 && vec != mVec4Cache[loc])) {
		mVec4Cache[loc] = vec;
		glUniform4f(getUniform(name), vec.x, vec.y, vec.z, vec.w);
	}
}

void ShaderProgram::setUniform(const char *name, glm::mat3 &mat) {
	glUniformMatrix3fv(getUniform(name), 1, GL_FALSE, glm::value_ptr(mat));
}

void ShaderProgram::setUniform(const char *name, glm::mat4 &mat) {
	glUniformMatrix4fv(getUniform(name), 1, GL_FALSE, glm::value_ptr(mat));
}

void ShaderProgram::setUniform(const std::string &name, bool& value) {
	setUniform(name.c_str(), value);
}

void ShaderProgram::setUniform(const std::string &name, int& value) {
	setUniform(name.c_str(), value);
}

void ShaderProgram::setUniform(const std::string &name, float& value) {
	setUniform(name.c_str(), value);
}

void ShaderProgram::setUniform(const std::string &name, glm::vec3& vec) {
	setUniform(name.c_str(), vec);
}

void ShaderProgram::setUniform(const std::string &name, glm::vec4& vec) {
	setUniform(name.c_str(), vec);
}

void ShaderProgram::setUniform(const std::string& name, glm::mat3 &mat) {
	setUniform(name.c_str(), mat);
}

void ShaderProgram::setUniform(const std::string& name, glm::mat4 &mat) {
	setUniform(name.c_str(), mat);
}

GLint ShaderProgram::getUniform(const char *name) {
	std::string strName(name);
	return getUniform(strName);
}

GLint ShaderProgram::getUniform(const std::string &name) {
	if(mUniformCache.count(name) > 0)
		return mUniformCache[name];
	else {
		GLint location = glGetUniformLocation(mProgram, name.c_str());
		mUniformCache[name] = location;
		return location;
	}
}

GLint ShaderProgram::getAttributeLocation(const char *name) {
	return glGetAttribLocation(mProgram, name);
}

GLint ShaderProgram::getAttributeLocation(std::string name) {
	if(mAttribCache.count(name) > 0) {
		return mAttribCache[name];
	}
	else {
		GLint attrib = glGetAttribLocation(mProgram, name.c_str());
		mAttribCache[name] = attrib;
		return attrib;
	}
}

GLuint ShaderProgram::getProgram() {
	return mProgram;
}
