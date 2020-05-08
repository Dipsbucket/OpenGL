#include "Transform.h"

Transform::Transform()
{
	// Initialisation matrice d'identité
	this->transform = glm::mat4(1.0f);
	this->translation = glm::mat4(1.0f);

	this->orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	this->rotation = glm::mat4(1.0f);

	this->modified = false;
}

Transform::~Transform()
{
}

void Transform::computeTransform()
{
	// TODO JT : TEST
	//this->transform = this->scale * this->rotation * this->translation;
	this->transform = this->rotation * this->translation;

	int size = this->transformationsCache.size();
	if (size > 0)
	{
		glm::mat4 previousTransform = this->transformationsCache[size - 1];
		this->transform = this->transform * previousTransform;
	}
}

void Transform::translate(glm::mat4& translation, bool reset)
{
	if (reset)
	{
		this->translation = translation * glm::mat4(1.0f);
	}
	else
	{
		this->translation = translation * this->translation;
	}

	this->computeTransform();
	this->modified = true;
}

void Transform::rotate(glm::quat& rotation)
{
	this->orientation = rotation * this->orientation;
	this->rotation = glm::toMat4(this->orientation);

	this->computeTransform();
	this->modified = true;
}

void Transform::resetTransform()
{
	this->transform = glm::mat4(1.0f);
	this->translation = glm::mat4(1.0f);

	this->orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	this->rotation = glm::mat4(1.0f);

	this->modified = false;
}

void Transform::clearTransform()
{
	this->resetTransform();
	this->transformationsCache.clear();
}

void Transform::saveTransform()
{
	if (this->modified)
	{
		this->transformationsCache.push_back(this->transform);
	}
	this->resetTransform();
}