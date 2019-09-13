//
// Created by brent on 23-11-17.
//

#ifndef CAS_TEXTURE2D_H
#define CAS_TEXTURE2D_H

#include "Texture.h"

class Texture2D: public Texture {
public:
	Texture2D(int width, int height, std::string filename, unsigned char* data, int textureNumber = GL_TEXTURE0, int mipmapLevel = 0, int textureFormat = GL_RGBA);
	~Texture2D();
	
	int getDimension() override;

protected:
	Texture2D();
	void loadTexture(int width, int height, std::string filename, unsigned char* data, int textureNumber, int mipmapLevel, int textureFormat);

protected:
	int mMipmapLevel;
	int mTextureFormat;

	int mWidth;
	int mHeight;
};


#endif //CAS_TEXTURE2D_H
