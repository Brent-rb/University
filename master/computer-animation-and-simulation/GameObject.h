//
// Created by brent on 18-11-17.
//

#ifndef CAS_GAMEOBJECT_H
#define CAS_GAMEOBJECT_H

#include <vector>
#include "Renderables/Transformable.h"


class Renderable;
class InputBuffer;
class OpenGLRenderer;

class Path;
class FFD;

class GameObject: public Transformable {
public:
	GameObject(OpenGLRenderer* renderer);
	GameObject(OpenGLRenderer* renderer, Renderable* renderable);
	virtual ~GameObject();

	virtual void update(InputBuffer* keyBuffer, glm::vec3 cameraPosition, glm::vec3 cameraDirection, float deltaMillis);
	void render(float deltaMillis);
	void render(float deltaMillis, glm::mat4& transMatrix);
	
	void addRenderable(Renderable* renderable);
	void addGameObject(GameObject* gameObject);
	
	void removeRenderable(Renderable* renderable);
	void removeGameObject(GameObject* gameObject);

	void setOpacity(float opacity);
	void setColor(float r, float g, float b);

	void setPath(Path* path);
	void setRotationPath(Path* path);

	glm::vec3 getColor();
	float getColorR();
	float getColorG();
	float getColorB();
	float getOpacity();

	void transform(FFD* ffd, glm::mat4& transMatrix);
	
protected:
	virtual void render(float deltaMillis, bool transform, glm::mat4& transMatrix);
	void setParent(GameObject* parent);
	
protected:
	OpenGLRenderer* mRenderer;
	std::vector<Renderable*> mRenderables;
	std::vector<GameObject*> mChildren;
	
	GameObject* mParent;

	Path* m_locationPath;
	Path* m_rotationPath;

	glm::vec3 mColor;
	glm::vec3 mLightProperties;
	float mOpacity;
};


#endif //CAS_GAMEOBJECT_H
