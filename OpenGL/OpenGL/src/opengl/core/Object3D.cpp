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

void Object3D::init()
{
	this->position = glm::vec3(0.0f);
	this->scale = glm::vec3(1.0f);
	this->up = glm::vec3(0.0f, 1.0f, 0.0f);

	this->orientation = glm::quat();

	this->transform = glm::mat4(1.0f);
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