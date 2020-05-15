#pragma once
#include <unordered_map>

#include "../geom/Mesh.h"

class SceneManager
{
	public:
	Mesh* scene;
	std::unordered_map<unsigned int, Object3D*> objectCache;

	SceneManager();
	~SceneManager();

	std::unordered_map<unsigned int, std::string> getNamesById();
	std::vector<const char*> getNames();
	Object3D* getObject(unsigned int key);

	void addObject(unsigned int key, Object3D* object);
	void saveTransforms();
	void clearTransform(unsigned int key);
	void clearTransforms();
};
