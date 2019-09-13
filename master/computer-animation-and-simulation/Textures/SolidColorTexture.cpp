//
// Created by brent on 24-11-17.
//

#include "SolidColorTexture.h"

SolidColorTexture::SolidColorTexture(float r, float g, float b, GLuint textureNumber): Texture2D() {
	unsigned char* data = new unsigned char[3];
	data[0] = r;
	data[1] = g;
	data[2] = b;
	loadTexture(1, 1, "SolidColor", data, textureNumber, 0, GL_RGB);
	delete[] data;
}

SolidColorTexture::SolidColorTexture(float r, float g, float b, float a, GLuint textureNumber): Texture2D() {
	unsigned char* data = new unsigned char[4];
	data[0] = r;
	data[1] = g;
	data[2] = b;
	data[3] = a;
	loadTexture(1, 1, "SolidColor", data, textureNumber, 0, GL_RGBA);
	delete[] data;
}

SolidColorTexture::~SolidColorTexture() {

}
