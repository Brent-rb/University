//
// Created by brent on 10-11-17.
//

#ifndef CAS_OPENGLRENDERER_H
#define CAS_OPENGLRENDERER_H

#include <GL/glew.h>
#include <chrono>
#include "Renderables/Triangle.h"
#include "Shaders/ShaderProgram.h"
#include "json.hpp"

using json = nlohmann::json;

class GameObject;
class Camera;
class InputBuffer;
class Clickable;
class Path;

class OpenGLRenderer {
public:
	OpenGLRenderer(int width, int height, float verticalFOV, std::string inFile, std::string outFile);
	virtual ~OpenGLRenderer();
	
	void render(InputBuffer* keyBuffer, float deltaMillis);
	void registerShaders();

	void useNormalShader();
	void useParticleShader();

	void setCamera(std::string name);
	void setCamera(std::string name, Camera* camera);
	void registerCamera(std::string name, Camera* camera);
	Camera* getCamera(std::string name);

	ShaderProgram* getShaderProgram();
	ShaderProgram* getParticleShader();
	void addClickable(Clickable* clickable);
	void addGameObject(GameObject* gameObject);
	void addGameObject(std::string name, GameObject* gameObject);
	GameObject* getGameObject(std::string);

	bool removeGameObject(GameObject* gameObject);
	bool removeClickable(Clickable* clickable);

protected:
	void checkClickables(InputBuffer* buffer);

	void readIn();
	void saveOut();

	void init();

	void readLight(json j);
	void readChannels(json j);
	void readCamera(json j);
	void readBackground(json j);
	Path* readPath(json j);
	glm::vec3 readVec3(json j);
	
private:
	ShaderProgram mShaderProgram;
	ShaderProgram mParticleShader;
	
	glm::mat4 mProjectionMatrix;

	Clickable* mSelected;
	std::vector<GameObject*> mGameObjects;
	std::vector<Clickable*> mClickables;
	Camera* mActiveCamera;

	std::map<std::string, GameObject*> mGameObjectsMap;
	std::map<std::string, Camera*> mCameras;

	std::string mIn;
	std::string mOut;
};


#endif //CAS_OPENGLRENDERER_H
