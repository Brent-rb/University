//
// Created by brent on 24-11-17.
//

#ifndef CAS_TEXTURE1D_H
#define CAS_TEXTURE1D_H

#include "Texture.h"

class Texture1D: public Texture {
public:
	Texture1D(int length, std::string filename, unsigned char* data, int textureNumber = GL_TEXTURE0, int mipmapLevel = 0, int textureFormat = GL_RGB);
	virtual ~Texture1D();
	
	int getDimension() override;

protected:
	Texture1D();
	void loadTexture(int length, std::string filename, unsigned char* data, int textureNumber, int mipmapLevel, int textureFormat);

protected:
	int mLength;
	int mMipmapLevel;
	int mTextureFormat;
};


#endif //CAS_TEXTURE1D_H
