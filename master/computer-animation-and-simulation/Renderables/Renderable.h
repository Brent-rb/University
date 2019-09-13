//
// Created by brent on 11-11-17.
//

#ifndef CAS_RENDERABLE_H
#define CAS_RENDERABLE_H

#include <GL/glew.h>
#include "Transformable.h"

class FFD;

class Renderable: public Transformable {
public:
	Renderable();
	virtual ~Renderable();
	
	virtual void init() = 0;
	virtual void render(float deltaMillis) = 0;
	virtual void render(float deltaMillis, glm::mat4& transMatrix) = 0;

	virtual void transform(FFD* ffd, glm::mat4& transMatrix) = 0;
};


#endif //CAS_RENDERABLE_H
