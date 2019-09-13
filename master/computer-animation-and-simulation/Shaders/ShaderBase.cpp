//
// Created by brent on 19-1-18.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include "ShaderBase.h"

ShaderBase::ShaderBase(const GLchar *shaderPath, GLenum shaderType): mShaderPath(shaderPath), mShaderType(shaderType) {
	char* code = getCode();
	if(code != nullptr && createShader(code)) {
		std::cout << "Shader '" << shaderPath << "' compiled succesfully." << std::endl;
	}
	else {
		if(code == nullptr) {
			std::cout << "No shader code found at '" << shaderPath << "'." << std::endl;
		}
		else {
			std::cout << "Shader '" << shaderPath << "' failed to compile." << std::endl;
			std::cout << "\t" << getShaderError() << std::endl;
		}
	}
	delete[] code;
}

ShaderBase::~ShaderBase() {
	glDeleteShader(mShader);
}

GLuint ShaderBase::getShader() {
	return mShader;
}

const GLchar *ShaderBase::getPath() {
	return mShaderPath;
}

GLenum ShaderBase::getType() {
	return mShaderType;
}

std::string ShaderBase::getShaderError() {
	char errorLog[512];
	
	glGetShaderInfoLog(mShader, 512, nullptr, errorLog);
	return std::string(errorLog);
}

std::string ShaderBase::getStringType() {
	switch(mShaderType) {
		case GL_VERTEX_SHADER:
			return std::string("VertexShader");
		case GL_FRAGMENT_SHADER:
			return std::string("FragmentShader");
		default:
			return std::string("UnknownShader");
	}
}

char* ShaderBase::getCode() {
	std::string code;
	std::ifstream shaderFile;
	
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		// Open file
		shaderFile.open(mShaderPath);
		
		// Read content into streams
		std::stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();
		
		// Close file
		shaderFile.close();
		code = shaderStream.str();
	}
	catch(std::ifstream::failure& e) {
		return nullptr;
	}
	
	auto* returnString = new char[code.size() + 1];
	strcpy(returnString, code.c_str());
	return returnString;
}

bool ShaderBase::createShader(const char* shaderCode) {
	int success;
	
	mShader = glCreateShader(mShaderType);
	glShaderSource(mShader, 1, &shaderCode, nullptr);
	glCompileShader(mShader);
	
	glGetShaderiv(mShader, GL_COMPILE_STATUS, &success);
	
	return success != 0;
}
