#include "Object3D.h"

Object3D::Object3D()
{
	this->id = 0;
	this->name = "";

	this->parent = nullptr;

	this->init();
}

Object3D::Object3D(std::string name, Object3D* parent)
{
	this->id = id;
	this->name = name;

	this->parent = parent;

	this->init();
}

Object3D::~Object3D()
{
}

void Object3D::init()
{
	this->position = glm::vec3(0.0f);
	this->scale = glm::vec3(1.0f);
	this->up = glm::vec3(0.0f, 1.0f, 0.0f);

	this->transform = new Transform();
	this->model = glm::mat4(1.0f);

	this->visible = true;
}

bool Object3D::isRootNode()
{
	return this->parent == nullptr;
}

bool Object3D::hasChildren()
{
	return this->children.size() > 0;
}

void Object3D::addChild(Object3D* child)
{
	child->parent = this;
	this->children.push_back(child);
}

glm::vec3 Object3D::computePosition()
{
	glm::mat4 model = glm::mat4(this->model);
	glm::vec4 p_position = glm::vec4(model * glm::vec4(this->position, 1.0f));
	return glm::vec3(p_position);
}

void Object3D::computeModel()
{
	// Calcul de la transformation appliquée
	this->transform->computeTransform();

	glm::mat4 parentTransform = this->parent == nullptr ? glm::mat4(1.0f) : this->parent->model;
	this->model = this->transform->transform * parentTransform;

	// Application aux enfants
	if (this->hasChildren())
	{
		for (std::vector<Object3D*>::iterator iterator = this->children.begin(); iterator != this->children.end(); iterator++)
		{
			(*iterator)->computeModel();
		}
	}
}

void Object3D::translate(glm::vec3 translationVector, bool reset)
{
	glm::mat4 translation = glm::translate(translationVector);
	this->transform->translate(translation, reset);
	this->computeModel();
}

void Object3D::rotate(glm::vec3 rotationVector)
{
	float radians = 0.0f;
	glm::quat xRotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	glm::quat yRotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	glm::quat zRotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);

	if (rotationVector.x != 0.0f)
	{
		radians = glm::radians(rotationVector.x);
		xRotation = glm::angleAxis(radians, glm::vec3(1.0f, 0.0f, 0.0f));
	}
	if (rotationVector.y != 0.0f)
	{
		radians = glm::radians(rotationVector.y);
		yRotation = glm::angleAxis(radians, glm::vec3(0.0f, 1.0f, 0.0f));
	}
	if (rotationVector.z != 0.0f)
	{
		radians = glm::radians(rotationVector.z);
		zRotation = glm::angleAxis(radians, glm::vec3(0.0f, 0.0f, 1.0f));
	}

	glm::quat rotation = xRotation * yRotation * zRotation;
	this->transform->rotate(rotation);
	this->computeModel();
}

void Object3D::rotateQuaternion(glm::quat rotation)
{
	this->transform->rotate(rotation);
	this->computeModel();
}

void Object3D::saveTransform()
{
	this->transform->saveTransform();
}

void Object3D::clearTransform()
{
	this->transform->clearTransform();
	this->computeModel();
}