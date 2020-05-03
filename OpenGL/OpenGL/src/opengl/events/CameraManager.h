#pragma once
#include <unordered_map>
#include "../Camera.h"

class CameraManager
{
	public:
	CameraManager(int width, int height);
	~CameraManager();

	Camera* getCurrentCamera();
	void setCurrentCamera(unsigned int index);
	void updateCurrentCamera(CameraType type);
	std::vector<const char*> getNames();

	private:
	unsigned int current_camera_index;
	std::unordered_map<unsigned int, Camera*> cameraCache;

	void addCamera(Camera* camera);
};
