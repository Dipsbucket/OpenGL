#pragma once
#include "ShaderManager.h"
#include "CameraManager.h"
#include "SceneManager.h"

class EventManager
{
	public:
	ShaderManager* shaderManager;
	CameraManager* cameraManager;
	SceneManager* sceneManager;

	EventManager();
	~EventManager();

	void createShaderManager();
	void createCameraManager(int width, int height);
	void createSceneManager();

	// Events
	void switchRenderingMode(int rmIndex);
	void switchDepthTest(bool enable);
	void switchShaders(int vsIndex, int fsIndex);
	void switchCamera(int cameraIndex);
	void manageScroll(double offset);
	void translateObject(unsigned int objectIndex, glm::vec3 translation);

	private:
	int currentRenderingMode, currentCameraIndex;
	bool enableDepthTest;
};
