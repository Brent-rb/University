//
// Created by brent on 22-11-17.
//

#include "Texture.h"

Texture::Texture() {
	mInit = false;
}

Texture::~Texture() {

}

void Texture::apply() {
	if(mInit) {
		glActiveTexture(mTextureNumber);
		glBindTexture(mTextureMode, mTexture);
	}
}