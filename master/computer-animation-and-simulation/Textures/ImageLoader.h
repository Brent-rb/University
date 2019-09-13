//
// Created by brent on 22-11-17.
//

#ifndef CAS_IMAGELOADER_H
#define CAS_IMAGELOADER_H

#include "Texture.h"

#include <map>
#include <GL/gl.h>

class ImageLoader {
public:
	static Texture* load2DTexture(const char* filename);
	static std::map<std::string, Texture*> mCachedTextures;
};


#endif //CAS_IMAGELOADER_H
