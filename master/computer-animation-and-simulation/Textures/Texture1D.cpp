//
// Created by brent on 24-11-17.
//

#include "Texture1D.h"

Texture1D::Texture1D(int length, std::string filename, unsigned char *data, int textureNumber, int mipmapLevel, int textureFormat) {
	loadTexture(length, filename, data, textureNumber, mipmapLevel, textureFormat);
}

Texture1D::~Texture1D() {

}

Texture1D::Texture1D() {

}

void Texture1D::loadTexture(int length, std::string filename, unsigned char *data, int textureNumber, int mipmapLevel, int textureFormat) {
	mLength = length;
	mFilename = filename;
	mTextureMode = GL_TEXTURE_1D;
	mTextureNumber = textureNumber;
	mTextureFormat = textureFormat;
	mMipmapLevel = mipmapLevel;
	
	glGenTextures(1, &mTexture);
	glBindTexture(mTextureMode, mTexture);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glTexImage1D(mTextureMode, mMipmapLevel, GL_RGB, mLength, 0, mTextureFormat, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(mTextureMode);
}

int Texture1D::getDimension() {
	return 1;
}

