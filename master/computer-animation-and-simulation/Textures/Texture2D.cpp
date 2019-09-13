//
// Created by brent on 23-11-17.
//

#include "Texture2D.h"

Texture2D::Texture2D(int width, int height, std::string filename, unsigned char *data, int textureNumber, int mipmapLevel, int textureFormat) {
	loadTexture(width, height, filename, data, textureNumber, mipmapLevel, textureFormat);
}

Texture2D::Texture2D() {

}

Texture2D::~Texture2D() {

}

void Texture2D::loadTexture(int width, int height, std::string filename, unsigned char *data, int textureNumber, int mipmapLevel, int textureFormat) {
	mWidth = width;
	mHeight = height;
	mFilename = filename;
	mTextureMode = GL_TEXTURE_2D;
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
	
	glTexImage2D(mTextureMode, mMipmapLevel, textureFormat, mWidth, mHeight, 0, mTextureFormat, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(mTextureMode);
	mInit = true;
}

int Texture2D::getDimension() {
	return 2;
}
