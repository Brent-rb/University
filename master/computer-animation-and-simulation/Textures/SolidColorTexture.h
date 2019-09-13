//
// Created by brent on 24-11-17.
//

#ifndef CAS_SOLIDCOLORTEXTURE_H
#define CAS_SOLIDCOLORTEXTURE_H

#include "Texture2D.h"

class SolidColorTexture: public Texture2D {
public:
	SolidColorTexture(float r, float g, float b, GLuint textureNumber = GL_TEXTURE0);
	SolidColorTexture(float r, float g, float b, float a, GLuint textureNumber = GL_TEXTURE0);
	virtual ~SolidColorTexture();
};


#endif //CAS_SOLIDCOLORTEXTURE_H
