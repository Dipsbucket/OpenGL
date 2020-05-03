#pragma once
#include "ShaderManager.h"
#include "CameraManager.h"

class EventManager
{
	public:
	ShaderManager* shaderManager;
	CameraManager* cameraManager;
	Object3D* scene;

	EventManager();
	~EventManager();

	void createShaderManager();
	void createCameraManager(int width, int height);

	// Events
	void switchRenderingMode(int rmIndex);
	void switchDepthTest(bool enable);
	void switchShaders(int vsIndex, int fsIndex);
	void switchCamera(int cameraIndex);
	void manageScroll(double offset);

	private:
	int currentRenderingMode, currentCameraIndex;
	bool enableDepthTest;
};
