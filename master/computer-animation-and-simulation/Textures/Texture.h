//
// Created by brent on 22-11-17.
//

#ifndef CAS_TEXTURE_H
#define CAS_TEXTURE_H

#include <string>
#include <GL/glew.h>

class Texture {
public:
	Texture();
	virtual ~Texture();
	
	void apply();
	virtual int getDimension() = 0;
	
protected:
	GLuint mTexture;
	GLuint mTextureMode;
	GLuint mTextureNumber;
	
	bool mInit = false;
	
	std::string mFilename;
};


#endif //CAS_TEXTURE_H
