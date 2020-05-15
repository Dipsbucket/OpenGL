#include "CameraManager.h"

CameraManager::CameraManager(int width, int height)
{
	this->current_camera_index = 0;

	// Création des caméras
	Camera* perspectiveCamera = new Camera("Default Perspective", nullptr, CameraType::PERSPECTIVE, (float)width, (float)height);
	Camera* orthographicCamera = new Camera("Default Orthographic", nullptr, CameraType::ORTHOGRAPHIC, (float)width, (float)height);

	this->addCamera(perspectiveCamera);
	this->addCamera(orthographicCamera);
}

CameraManager::~CameraManager()
{
}

Camera* CameraManager::getCurrentCamera()
{
	return this->cameraCache.at(this->current_camera_index);
}

void CameraManager::setCurrentCamera(unsigned int index)
{
	this->current_camera_index = index;

	CameraType type = (*this->cameraCache.at(this->current_camera_index)).type;
	this->updateCurrentCamera(type);
}

void CameraManager::updateCurrentCamera(CameraType type)
{
	this->cameraCache.at(this->current_camera_index)->init();
}

std::vector<const char*> CameraManager::getNames()
{
	std::vector<const char*> res;

	for (std::unordered_map<unsigned int, Camera*>::iterator iterator = this->cameraCache.begin(); iterator != this->cameraCache.end(); ++iterator)
	{
		res.push_back(iterator->second->getNameAsChar());
	}

	return res;
}

void CameraManager::addCamera(Camera* camera)
{
	unsigned int size = this->cameraCache.size();
	camera->id = size;
	this->cameraCache.insert({ size, camera });
}