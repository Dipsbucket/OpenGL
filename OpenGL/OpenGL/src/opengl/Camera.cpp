#include "Camera.h"
#include "../Constants.cpp"

Camera::Camera(std::string name, Object3D* parent, CameraType type, float width, float height) : Object3D(name, parent)
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
	// TODO JT : TEST
	this->position = glm::vec3(0.0f, 3.0f, 3.0f);
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

void Camera::rotate(double yaw, double pitch)
{
	// TODO JT : TEST
	double computedPitch = pitch;
	double comptedYaw = yaw * TransformConstants::ROTATION_SENSITIVITY;
	computedPitch *= TransformConstants::ROTATION_SENSITIVITY;
	glm::vec3 rotation = glm::vec3((float)computedPitch, -(float)comptedYaw, 0.0f);
	// Reset de la rotation actuelle et calcul de la nouvelle
	this->transform->resetTransform();
	this->Object3D::rotate(rotation);
	// Maj de la position et de la view Matrix
	this->position = this->Object3D::computePosition();
	// TODO JT : TEST Compute UpVector?
	this->computeView();
}

void Camera::test(float viewportWidth, float viewportHeight, float x, float y, float z)
{
	// TODO JT : 1
	//glm::mat4 projection = this->projection;
	//glm::mat4 view = this->view;
	//glm::mat4 invVP = glm::inverse(projection * view);

	////glm::vec4 screenPos = glm::vec4(0, 0, 1.0f, 1.0f);
	//glm::vec4 screenPos = glm::vec4(0, 0, 0.0f, 1.0f);
	//glm::vec4 worldPos = invVP * screenPos;
	//int a = 0;
	// TODO JT : 2
	//  TODO JT : TEST > Attention commence peut-être en bas a gauche, inverser Y (height - Y)
	//int xPos = (int)(viewportWidth / 2);
	//int yPos = (int)(viewportHeight / 2);
	//glm::vec3 screenPos2 = glm::vec3(xPos, yPos, 1.0f);
	glm::vec3 position = this->position;
	glm::vec3 screenPos2 = glm::vec3(x, viewportHeight - y, z);
	glm::vec4 viewport = glm::vec4(0, 0, viewportWidth, viewportHeight);
	glm::vec3 worldPos2 = glm::unProject(screenPos2, view, projection, viewport);

	// Calcul de la direction du ray
	//glm::vec3 direction = worldPos2 - position;

	glm::vec3 from = glm::normalize(this->position);
	//glm::vec3 to = glm::normalize(glm::vec3(3.f, 3.f, 0.f));
	glm::vec3 to = glm::normalize(worldPos2);
	glm::quat test = glm::quat(from, to);

	// Reset de la rotation actuelle et calcul de la nouvelle
	this->transform->resetTransform();
	this->Object3D::rotateQuaternion(test);
	// Maj de la position et de la view Matrix
	//this->position = this->Object3D::computePosition();
	glm::vec3 newPosition = test * this->position;
	this->position = newPosition;
	// TODO JT : TEST Compute UpVector?
	this->computeView();

	int b = 0;
}

void Camera::draw()
{
	// Non implémenté
}