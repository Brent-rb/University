//
// Created by brent on 10-11-17.
//

#include <fstream>
#include "OpenGLRenderer.h"
#include "InputBuffer/InputBuffer.h"
#include "GameObject.h"
#include "Cameras/Camera.h"
#include "Cameras/FirstPersonCamera.h"
#include "Textures/ImageLoader.h"
#include "Textures/SolidColorTexture.h"
#include "Renderables/Square.h"
#include "Renderables/Cube.h"
#include "Fluids/FluidGrid.h"
#include "Renderables/Model.h"
#include "Path/InterpolatedPath.h"
#include "Path/RotationPath.h";
#include "Path/LinearController.h"
#include "Clickable.h";
#include "SkyBox.h"
#include "Cameras/DirectedCamera.h"
#include "FFD.h"
#include "Path/EaseInEaseOut.h"
#include "ParticleEmitter.h"


OpenGLRenderer::OpenGLRenderer(int width, int height, float verticalFOV, std::string inFile, std::string outFile): mSelected(nullptr), mActiveCamera(nullptr), mIn(inFile), mOut(outFile) {
	registerShaders();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	mProjectionMatrix = glm::perspective(glm::radians(verticalFOV), ((float) width) / ((float) height), 0.1f, 1000.0f);
	init();
}

OpenGLRenderer::~OpenGLRenderer() {

}

void OpenGLRenderer::init() {
	glm::vec3 lightPosition(0, 50.0f, 100.0f);
	Path* path = new InterpolatedPath(this, SPEED);
	path->addPoint(glm::vec3(-50, 0, 0), 0.0f);
	path->addPoint(glm::vec3(50, 0, 0), 20.0f);
	Path* path2 = new InterpolatedPath(this, SPEED);

	path2->addPoint(glm::vec3(0, 0, 0), 0.0f);
	path2->addPoint(glm::vec3(30, 10, 0), 5.0f);
	path2->addPoint(glm::vec3(0, 20, 0), 10.0f);
	path2->addPoint(glm::vec3(-10, 10, 0), 15.0f);
	path2->addPoint(glm::vec3(0, 0, 0), 20.0f);

	path2->calculate();
	path->calculate();

	Path* rotationPath = new RotationPath(this, SPEED);
	rotationPath->addPoint(glm::vec3(0, 0, 0), 0.0f);
	rotationPath->addPoint(glm::vec3(90, 90, 0), 5.0f);
	rotationPath->addPoint(glm::vec3(180, 180, 0), 10.0f);
	rotationPath->addPoint(glm::vec3(270, 270, 0), 15.0f);
	rotationPath->addPoint(glm::vec3(360, 360, 0), 20.0f);
	rotationPath->calculate();

	Model* deerModel = new Model(getShaderProgram(), std::string("../Objects/deer.obj"));
	Model* model =  new Model(getShaderProgram(), std::string("/home/brent/Documents/CAS/Objects/ball.obj"));
	Texture* texture = ImageLoader::load2DTexture("/home/brent/Pictures/Korean Stuff/tzuyu.jpg");
	Texture* skyTexture = ImageLoader::load2DTexture("../Objects/sky.jpg");
	Texture* groundTexture = ImageLoader::load2DTexture("../Objects/ground.jpg");


	FFD* ffd = new FFD(this, 5, 5, 5, 5);
	mGameObjects.push_back(ffd);
	ffd->setPath(path);

	GameObject* deer2 = new GameObject(this, deerModel);
	deer2->setPath(path2);
	deer2->setRotationPath(rotationPath);
	addGameObject(deer2);

	SkyBox* skybox = new SkyBox(this, 1000);
	skybox->setTexture(TOP, skyTexture);
	skybox->setTexture(LEFT, skyTexture);
	skybox->setTexture(RIGHT, skyTexture);
	skybox->setTexture(FORWARD, skyTexture);
	skybox->setTexture(BACKWARD, skyTexture);
	skybox->setTexture(BOTTOM, groundTexture);
	mGameObjects.push_back(skybox);
	Square* square = new Square(getShaderProgram()->getProgram(), glm::vec3(-1, -1, 0), glm::vec3(1, -1, 0), glm::vec3(1, 1, 0), glm::vec3(-1, 1, 0), glm::vec3(0, 0 , 1));
	//square->setTexture(texture);
	Cube* cube = new Cube(mShaderProgram.getProgram(), glm::vec3(0.0f, 0.0f, 0.0f), 2.0f, texture);
	GameObject* cube1 = new GameObject(this, deerModel);
	cube1->setOpacity(1.0f);
	cube1->setColor(1.0f, 1.0f, 1.0f);
	//GameObject* cube2 = createGameObject(cube);
	//GameObject* cube3 = createGameObject(cube);
	//cube1->setLocation(0, 0.0, -10);
	//cube1->setPath(path2);
	//cube2->setLocation(0.0, 0.0, -30);
	//cube3->setLocation(10.0, 0.0, -30);
	/*
	mFluidGrid = new FluidGrid(this, nullptr, 20, 20, 20, 1.0f, 5);
	mFluidGrid->setLocation(-10, -10, -30);
	mGameObjects.push_back(mFluidGrid);
	 */

	ffd->addGameObject(cube1);

	Cube* lightCube = new Cube(mShaderProgram.getProgram(), glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, new SolidColorTexture(255, 255, 255));
	lightCube->setLocation(lightPosition.x, lightPosition.y, lightPosition.z);
	GameObject* obj = new GameObject(this, lightCube);
	addGameObject("lightCube", obj);

	setCamera("fps", new FirstPersonCamera(mShaderProgram.getProgram(), 10));

	Path* cameraPath = new RotationPath(this, SPEED, true);
	cameraPath->addPoint(glm::vec3(0, 0, 0), 0.0f);
	cameraPath->addPoint(glm::vec3(0, 0, 50), 5.0f);
	cameraPath->addPoint(glm::vec3(0, 0, 0), 10.0f);
	DirectedCamera* directedCamera = new DirectedCamera(this);
	directedCamera->setPath(cameraPath);
	directedCamera->setRotationPath(rotationPath);

	//setCamera("directed", directedCamera);



	Clickable* clickable = new Clickable(this, model);
	clickable->setLocation(0, 0, -50);
	addClickable(clickable);
	mGameObjects.push_back(clickable);

	//ParticleEmitter* emitter = new ParticleEmitter(this);
	//addGameObject(emitter);

	glUniform3f(glGetUniformLocation(mShaderProgram.getProgram(), "lightColor"), 1.0f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(mShaderProgram.getProgram(), "lightPosition"), lightPosition.x, lightPosition.y, lightPosition.z);
	glUniform3f(glGetUniformLocation(mShaderProgram.getProgram(), "objectProperties"), 0.2f, 0.8f, 0.0f);

}

void OpenGLRenderer::readIn() {
	json j;
	std::ifstream input(mIn);
	input >> j;

	for(json::iterator it = j.begin(); it != j.end(); ++it) {
		std::string key = it.key();
		if(key.compare("light") == 0) {
			readLight(it.value());
		}

		if(key.compare("channels") == 0) {
			readChannels(it.value());
		}
	}
}

void OpenGLRenderer::readLight(json j) {
	glm::vec3 position = readVec3(j["position"]);
	glm::vec3 color = readVec3(j["color"]);

	mShaderProgram.setUniform("lightPosition", position);
	mShaderProgram.setUniform("lightColor", color);
}

void OpenGLRenderer::readChannels(json j) {
	std::vector<json> channels = j;

	for(int i = 0; i < channels.size(); i++) {
		j = channels[i];

		std::string type = j["type"];

		if(type.compare("camera") == 0) {
			readCamera(j);
		}
		else if(type.compare("background") == 0) {
			readBackground(j);
		}
	}
}

void OpenGLRenderer::readCamera(json j) {
	DirectedCamera* camera = new DirectedCamera(this);
	camera->setPath(readPath(j["locationPath"]));
	camera->setRotationPath(readPath(j["rotationPath"]));
	setCamera("active", camera);
}

void OpenGLRenderer::readBackground(json j) {
	float distance = j["distance"];
	std::string skyTexture, groundTexture, zForwardTexture, zBackwardTexture, xLeft, xRight;
	skyTexture = j["sky"];
	groundTexture = j["ground"];
	zForwardTexture = j["forward"];
	zBackwardTexture = j["backward"];
	xLeft = j["left"];
	xRight = j["right"];

	SkyBox* skyBox = new SkyBox(this, distance);
	skyBox->setTexture(TOP, ImageLoader::load2DTexture(skyTexture.c_str()));
	skyBox->setTexture(BOTTOM, ImageLoader::load2DTexture(groundTexture.c_str()));
	skyBox->setTexture(FORWARD, ImageLoader::load2DTexture(zForwardTexture.c_str()));
	skyBox->setTexture(BACKWARD, ImageLoader::load2DTexture(zBackwardTexture.c_str()));
	skyBox->setTexture(LEFT, ImageLoader::load2DTexture(xLeft.c_str()));
	skyBox->setTexture(RIGHT, ImageLoader::load2DTexture(xRight.c_str()));

	addGameObject("skybox", skyBox);
}

Path* OpenGLRenderer::readPath(json j) {
	std::string type = j["type"];
	std::string mode = j["mode"];
	std::vector<json> points = j["points"];
	std::vector<float> timestamps = j["timestamps"];
	std::string controller = j["controller"];
	bool looping = j["looping"];

	Path* path;
	Mode modeEnum;
	if(mode.compare("speed") == 0) {
		modeEnum = SPEED;
	}
	else if(mode.compare("time") == 0) {
		modeEnum = TIME;
	}
	if(type.compare("interpolated") == 0) {
		path = new InterpolatedPath(this, modeEnum, looping);
	}
	else if(type.compare("simple") == 0) {
		path = new RotationPath(this, modeEnum, looping);
	}

	for(int i = 0; i < points.size(); i++) {
		path->addPoint(readVec3(points[i]), timestamps[i]);
	}

	if(controller.compare("easeineaseout") == 0) {
		path->setController(new EaseInEaseOut());
	}
	else if(controller.compare("linear") == 0) {
		path->setController(new LinearController());
	}
}

glm::vec3 OpenGLRenderer::readVec3(json j) {
	return glm::vec3(j["x"], j["y"], j["z"]);
}

void OpenGLRenderer::saveOut() {

}

void OpenGLRenderer::checkClickables(InputBuffer* keyBuffer) {
	Clickable* leastClickable = nullptr;
	float leastDistance = 100000000.0f;
	float distance;
	glm::vec3 cameraForward = glm::normalize(mActiveCamera->getForwardVector());
	cameraForward *= -1;

	for(int i = 0; i < mClickables.size() && mSelected == nullptr; i++) {
		distance = mClickables[i]->distanceFromCamera(mActiveCamera->getPosition(), cameraForward);
		if(distance > 0 && distance < leastDistance) {
			leastClickable = mClickables[i];
			leastDistance = distance;
		}
	}
	if(keyBuffer->getMouse()->isLeftMouseButtonDown()) {
		if(mSelected == nullptr && leastClickable != nullptr) {
			leastClickable->select();
			mSelected = leastClickable;
		}
		else if(mSelected != nullptr) {
			mSelected->deselect();
			mSelected = nullptr;
		}
	}
	else if(leastClickable != nullptr) {
		leastClickable->hover();
	}
}

void OpenGLRenderer::render(InputBuffer* keyBuffer, float deltaMillis) {
	if(mActiveCamera != nullptr) {
		mActiveCamera->update(keyBuffer, deltaMillis);

		glm::mat4 idMatrix;
		glm::vec3 cameraPosition = mActiveCamera->getPosition();
		glm::vec3 cameraDirection = mActiveCamera->getForwardVector();

		checkClickables(keyBuffer);

		for(int i = 0; i < mGameObjects.size(); i++) {
			mGameObjects[i]->update(keyBuffer, cameraPosition, cameraDirection, deltaMillis);
		}

		mShaderProgram.setUniform("cameraPosition", cameraPosition);
		mShaderProgram.setUniform("cameraForwardVector", cameraDirection);
		mShaderProgram.setUniform("projectionMatrix", mProjectionMatrix);

		mActiveCamera->apply();
		for(int i = 0; i < mGameObjects.size(); i++) {
			mGameObjects[i]->render(deltaMillis);
		}
	}
}

void OpenGLRenderer::registerShaders() {
	ShaderBase vertexShader("../Shaders/BasicVertexShader.vs.glsl", GL_VERTEX_SHADER);
	ShaderBase fragmentShader("../Shaders/BasicFragmentShader.fs.glsl", GL_FRAGMENT_SHADER);

	ShaderBase particeV("../Shaders/ParticleVertexShader.vs.glsl", GL_VERTEX_SHADER);
	ShaderBase particeF("../Shaders/ParticleFragmentShader.fs.glsl", GL_FRAGMENT_SHADER);
	
	mShaderProgram.attachShader(vertexShader);
	mShaderProgram.attachShader(fragmentShader);

	mParticleShader.attachShader(particeV);
	mParticleShader.attachShader(particeF);

	glLinkProgram(mShaderProgram.getProgram());
	glLinkProgram(mParticleShader.getProgram());
	useNormalShader();
}

void OpenGLRenderer::useNormalShader() {
	glBindFragDataLocation(mShaderProgram.getProgram(), 0, "outColor");
	//glLinkProgram(mShaderProgram.getProgram());
	glUseProgram(mShaderProgram.getProgram());
}

void OpenGLRenderer::useParticleShader() {
	glUseProgram(mParticleShader.getProgram());
}

ShaderProgram *OpenGLRenderer::getShaderProgram() {
	return &mShaderProgram;
}

void OpenGLRenderer::addGameObject(GameObject *gameObject) {
	mGameObjects.push_back(gameObject);
}

void OpenGLRenderer::addGameObject(std::string name, GameObject *gameObject) {
	addGameObject(gameObject);
	mGameObjectsMap[name] = gameObject;
}

GameObject* OpenGLRenderer::getGameObject(std::string name) {
	if(mGameObjectsMap.count(name) > 0) {
		return mGameObjectsMap[name];
	}
	return nullptr;
}

bool OpenGLRenderer::removeGameObject(GameObject *gameObject) {
	for(int i = 0; i < mGameObjects.size(); i++) {
		if(mGameObjects[i] == gameObject) {
			mGameObjects.erase(mGameObjects.begin() + i);
			return true;
		}
	}
	return false;
}

void OpenGLRenderer::addClickable(Clickable *clickable) {
	mClickables.push_back(clickable);
}

bool OpenGLRenderer::removeClickable(Clickable *clickable) {
	for(int i = 0; i < mClickables.size(); i++) {
		if(mClickables[i] == clickable) {
			mClickables.erase(mClickables.begin() + i);
			return true;
		}
	}
	return false;
}

void OpenGLRenderer::setCamera(std::string name) {
	if(mCameras.count(name) > 0) {
		mActiveCamera = mCameras[name];
	}
}

void OpenGLRenderer::setCamera(std::string name, Camera *camera) {
	registerCamera(name, camera);
	setCamera(name);
}

void OpenGLRenderer::registerCamera(std::string name, Camera *camera) {
	if(mCameras.count(name) > 0) {
		Camera* tempCamera = mCameras[name];
		if(mActiveCamera == tempCamera) {
			mActiveCamera = camera;
		}
		delete tempCamera;
	}
	mCameras[name] = camera;
}

Camera *OpenGLRenderer::getCamera(std::string name) {
	if(mCameras.count(name) > 0)
		return mCameras[name];
	return nullptr;
}


ShaderProgram *OpenGLRenderer::getParticleShader() {
	return &mParticleShader;
}
