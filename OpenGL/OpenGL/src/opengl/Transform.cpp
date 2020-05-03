#include "Transform.h"

Transform::Transform()
{
	// Initialisation en matrice d'identité
	this->model = glm::mat4(1.0f);

	// TODO JT : TEST
	glm::quat test = glm::quat(1.0f, 1.0f, 1.0f, 1.0f);
}

Transform::~Transform()
{
}