//
// Created by brent on 22-11-17.
//
#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include "stb_image.h"
#include "ImageLoader.h"
#include "Texture2D.h"

std::map<std::string, Texture*> ImageLoader::mCachedTextures;

Texture* ImageLoader::load2DTexture(const char *filename) {
	std::string filenameString(filename);
	Texture *newTexture;

	if(ImageLoader::mCachedTextures.count(filenameString) == 0) {
		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
		if (data != nullptr) {
			std::cout << "Width: " << width << " Height: " << height << " NR: " << nrChannels << std::endl;
			if(nrChannels == 4)
				newTexture = new Texture2D(width, height, filenameString, data);
			else if(nrChannels == 3)
				newTexture = new Texture2D(width, height, filenameString, data, GL_TEXTURE0, 0, GL_RGB);
			ImageLoader::mCachedTextures[filenameString] = newTexture;
			stbi_image_free(data);
		}
		else {
			std::cout << "Failed to load: " << filenameString << std::endl;
			return nullptr;
		}
	}
	return ImageLoader::mCachedTextures[filenameString];
}
