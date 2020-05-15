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

	int currentObject;

	EventManager();
	~EventManager();

	void createShaderManager();
	void createCameraManager(int width, int height);
	void createSceneManager();

	// Events
	void switchRenderingMode(int rmIndex);
	void switchDepthTest(bool enable);
	void switchMultiSampling(bool enable);
	void switchShaders(int vsIndex, int fsIndex);
	void switchCamera(int cameraIndex);
	void switchObject(int objectIndex);
	void manageScroll(double offset);
	void manageRotateCamera(double xOffset, double yOffset);
	// TODO JT : TEST
	void manageRotateCameraArcBall(float viewportWidth, float viewportHeight, float x, float y, float z);
	void translateObject(unsigned int objectIndex, glm::vec3 translation, bool reset);
	void rotateObject(unsigned int objectIndex, glm::vec3 rotation);
	void saveTransforms();
	void clearTransform(unsigned int id);
	void clearTransforms();

	private:
	int currentRenderingMode, currentCameraIndex;
	bool enableDepthTest, enableMultiSampling;
};
