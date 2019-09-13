//
// Created by brent on 14.08.18.
//

#ifndef CAS_DIRECTEDCAMERA_H
#define CAS_DIRECTEDCAMERA_H

#include "Camera.h"

class OpenGLRenderer;
class Path;

class DirectedCamera: public Camera {
public:
	DirectedCamera(OpenGLRenderer* renderer);

	void update(InputBuffer *buffer, float deltaMillis) override;

	void setPath(Path* path);
	void setRotationPath(Path* path);

private:
	Path* m_path;
	Path* m_rotationPath;
};


#endif //CAS_DIRECTEDCAMERA_H
