#pragma once
#include <vector>
#include <iterator>
#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/quaternion.hpp"

#include "Transform.h"
#include "../../interfaces/hasId.h"
#include "../../interfaces/hasName.h"
#include "../utils/StringUtils.h"

class Object3D : public hasName, public hasId
{
	public:
	Object3D* parent;
	std::vector<Object3D*> children;

	glm::vec3 position, scale, up;
	glm::mat4 model;

	bool visible;

	Object3D();
	Object3D(std::string name, Object3D* parent);
	~Object3D();

	void init();
	bool isRootNode();
	bool hasChildren();
	void addChild(Object3D* child);

	glm::vec3 computePosition();
	void computeModel();

	void translate(glm::vec3 translationVector, bool reset);
	// TODO JT
	void rotate(glm::vec3 rotationVector);
	void rotateQuaternion(glm::quat rotation);

	void saveTransform();
	void clearTransform();

	virtual void draw() = 0;

	protected:
	Transform* transform;
};
