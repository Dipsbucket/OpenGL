#include "Transform.h"

Transform::Transform()
{
	// Initialisation matrice d'identité
	this->transform = glm::mat4(1.0f);
	this->translation = glm::mat4(1.0f);
	this->rotation = glm::mat4(1.0f);
	this->scale = glm::mat4(1.0f);
}

Transform::~Transform()
{
}

void Transform::computeTransform()
{
	// TODO JT : PARENT
	this->transform = this->scale * this->rotation * this->translation;
}

void Transform::addTranslation(glm::mat4& translation)
{
	this->translations.push_back(translation);
	this->translation = translation * this->translation;

	this->computeTransform();
}

void Transform::addRotation(glm::mat4& rotation)
{
	this->rotations.push_back(rotation);
}

void Transform::addScale(glm::mat4& scale)
{
	this->scales.push_back(scale);
}

void Transform::resetTranslation()
{
}

void Transform::resetRotation()
{
}

void Transform::resetScale()
{
}

void Transform::computeTranslations()
{
	// TODO JT : TEST Historique
	//this->translation = glm::mat4(1.0f);
	//for (std::vector<glm::mat4>::iterator iterator = this->translations.end(); iterator != this->translations.begin(); iterator--)
	//{
	//	this->translation *= (*iterator);
	//}
}

void Transform::computeRotations()
{
}

void Transform::computeScale()
{
}