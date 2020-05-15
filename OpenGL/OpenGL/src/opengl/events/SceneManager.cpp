#include "SceneManager.h"

SceneManager::SceneManager()
{
	// Création de la scène
	this->scene = new Mesh("Scene", nullptr);
	this->objectCache.insert({ 0, this->scene });
}

SceneManager::~SceneManager()
{
}

std::unordered_map<unsigned int, std::string> SceneManager::getNamesById()
{
	std::unordered_map<unsigned int, std::string> res;

	for (std::unordered_map<unsigned int, Object3D*>::iterator iterator = this->objectCache.begin(); iterator != this->objectCache.end(); ++iterator)
	{
		res.insert({ iterator->second->id, iterator->second->name });
	}

	return res;
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

Object3D* SceneManager::getObject(unsigned int key)
{
	return this->objectCache.at(key);
}

/*******************************************************************************
 * Adds an object to the scene and to it's parent
 *
 * @param key : parent's id
 * @param object : object to add
 ******************************************************************************/
void SceneManager::addObject(unsigned int key, Object3D* object)
{
	// Ajout au parent
	(*this->objectCache.at(key)).addChild(object);

	// Déterminer l'id et ajout de l'objet
	object->id = this->objectCache.size();
	this->objectCache.insert({ object->getId(), object });
}

/*******************************************************************************
 * Saves the transforms of all the objects in the scene
 *
 ******************************************************************************/
void SceneManager::saveTransforms()
{
	for (std::unordered_map<unsigned int, Object3D*>::iterator iterator = this->objectCache.begin(); iterator != this->objectCache.end(); ++iterator)
	{
		iterator->second->saveTransform();
	}
}

/*******************************************************************************
 * Clear the transform of the object
 *
 * @param key : id of the object
 ******************************************************************************/
void SceneManager::clearTransform(unsigned int key)
{
	this->objectCache.at(key)->clearTransform();
}

/*******************************************************************************
 * Clear the transforms of all the objects in the scene
 *
 * @param key : id of the object
 ******************************************************************************/
void SceneManager::clearTransforms()
{
	for (std::unordered_map<unsigned int, Object3D*>::iterator iterator = this->objectCache.begin(); iterator != this->objectCache.end(); ++iterator)
	{
		iterator->second->clearTransform();
	}
}