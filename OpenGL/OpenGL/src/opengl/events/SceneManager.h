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

	std::vector<const char*> getNames();
	Object3D* getObject(unsigned int index);

	void addObject(unsigned int parentIndex, Object3D* object);
};
