#include "Object3D.h"

Object3D::Object3D()
{
	this->id = 0;
	this->name = "";

	this->parent = nullptr;

	this->init();
}

Object3D::Object3D(unsigned int id, std::string name, Object3D* parent)
{
	this->id = id;
	this->name = name;

	this->parent = parent;

	this->init();
}

Object3D::~Object3D()
{
}

void Object3D::setQuaternion(glm::quat orientation)
{
	this->orientation = orientation;
}

void Object3D::init()
{
	this->position = glm::vec3(0.0f);
	this->scale = glm::vec3(1.0f);
	this->up = glm::vec3(0.0f, 1.0f, 0.0f);

	this->orientation = glm::quat();

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

void Object3D::computeModel(bool fromParent)
{
	glm::mat4 parentTransform = this->parent == nullptr ? glm::mat4(1.0f) : this->parent->model;
	this->model = this->transform->transform * parentTransform;

	// Application aux enfants
	if (this->hasChildren())
	{
		for (std::vector<Object3D*>::iterator iterator = this->children.begin(); iterator != this->children.end(); iterator++)
		{
			(*iterator)->computeModel(true);
		}
	}
}

glm::vec3 Object3D::computePosition()
{
	glm::mat4 model = glm::mat4(this->model);
	glm::vec4 p_position = glm::vec4(model * glm::vec4(this->position, 1.0f));
	return glm::vec3(p_position);
}

void Object3D::translate(glm::vec3 translationVector)
{
	glm::mat4 translation = glm::translate(translationVector);
	this->transform->addTranslation(translation);
	this->computeModel(true);
	this->computePosition();
}