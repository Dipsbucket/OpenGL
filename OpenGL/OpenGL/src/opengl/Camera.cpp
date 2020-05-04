#include "Camera.h"

Camera::Camera(unsigned int id, std::string name, Object3D* parent, CameraType type, float width, float height) : Object3D(id, name, parent)
{
	this->vWidth = width;
	this->vHeight = height;
	this->aspectRatio = vWidth / vHeight;
	this->type = type;

	this->init();
}

Camera::~Camera()
{
}

void Camera::init()
{
	this->position = glm::vec3(0.0f, 0.0f, 3.0f);
	this->target = glm::vec3(0.0f, 0.0f, 0.0f);

	this->model = glm::mat4(1.0f);
	this->view = glm::mat4(1.0f);

	switch (this->type)
	{
		case CameraType::ORTHOGRAPHIC:
			this->initOrthographic();
			break;
		case CameraType::PERSPECTIVE:
			this->initPerspective();
			break;
		default:
			break;
	}
}

void Camera::initOrthographic()
{
	this->right = 5.0f;
	this->left = -this->right;
	this->top = this->right * this->aspectRatio;
	this->bottom = -this->top;
	this->near = -5.0f;
	this->far = 5.0f;

	this->computeProjection();
}

void Camera::initPerspective()
{
	this->near = 0.1f;
	this->far = 100.0f;

	this->computeView();
	this->computeProjection();
}

void Camera::computeView()
{
	// Compute lookAt : position, target, up
	this->view = glm::lookAt(this->position, this->target, this->up);
}

void Camera::computeProjection()
{
	switch (this->type)
	{
		case CameraType::ORTHOGRAPHIC:
			this->projection = glm::ortho(this->left, this->right, this->bottom, this->top, this->near, this->far);
			break;
		case CameraType::PERSPECTIVE:
			this->projection = glm::perspective(glm::radians(45.0f), this->vWidth / this->vHeight, this->near, this->far);
			break;
		default:
			break;
	}
}

void Camera::zoom(bool in)
{
	switch (this->type)
	{
		case CameraType::ORTHOGRAPHIC:
			this->zoomOrthographic(in);
			break;
		case CameraType::PERSPECTIVE:
			this->zoomPerspective(in);
		default:
			break;
	}
}

void Camera::zoomOrthographic(bool in)
{
	if (in)
	{
		if (this->right - 1 > 0)
		{
			this->right--;
		}
	}
	else
	{
		this->right++;
	}

	this->left = -this->right;
	this->top = this->right * this->aspectRatio;
	this->bottom = -this->top;
	this->computeProjection();
}

void Camera::zoomPerspective(bool in)
{
	glm::vec3 pNorm = glm::normalize(glm::vec3(this->position));

	if (in)
	{
		if (glm::length(this->position - pNorm) > 0)
		{
			this->position = this->position - pNorm;
			this->computeView();
		}
	}
	else
	{
		this->position = this->position + pNorm;
		this->computeView();
	}
}

void Camera::draw()
{
	// Non implémenté
}