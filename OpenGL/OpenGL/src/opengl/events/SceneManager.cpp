#include "SceneManager.h"

SceneManager::SceneManager()
{
	// Création de la scène
	this->scene = new Mesh(0, "Scene", nullptr);
	this->objectCache.insert({ this->scene->getId(), this->scene });
}

SceneManager::~SceneManager()
{
}

std::vector<const char*> SceneManager::getNames()
{
	std::vector<const char*> res;

	for (std::unordered_map<unsigned int, Object3D*>::iterator iterator = this->objectCache.begin(); iterator != this->objectCache.end(); ++iterator)
	{
		res.push_back(iterator->second->getNameAsChar());
	}

	return res;
}

Object3D* SceneManager::getObject(unsigned int index)
{
	return this->objectCache.at(index);
}

void SceneManager::addObject(unsigned int parentIndex, Object3D* object)
{
	(*this->objectCache.at(parentIndex)).addChild(object);
	this->objectCache.insert({ object->getId(), object });
}

void SceneManager::saveTransforms()
{
	for (std::unordered_map<unsigned int, Object3D*>::iterator iterator = this->objectCache.begin(); iterator != this->objectCache.end(); ++iterator)
	{
		iterator->second->saveTransform();
	}
}

void SceneManager::clearTransform(unsigned int id)
{
	this->objectCache.at(id)->clearTransform();
}

void SceneManager::clearTransforms()
{
	for (std::unordered_map<unsigned int, Object3D*>::iterator iterator = this->objectCache.begin(); iterator != this->objectCache.end(); ++iterator)
	{
		iterator->second->clearTransform();
	}
}