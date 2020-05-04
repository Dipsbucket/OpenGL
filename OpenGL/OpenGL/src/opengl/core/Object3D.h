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
	glm::quat orientation;
	glm::mat4 model;
	Transform* transform;
	bool visible;

	Object3D();
	Object3D(unsigned int id, std::string name, Object3D* parent);
	~Object3D();

	void setQuaternion(glm::quat orientation);

	void init();
	bool isRootNode();
	bool hasChildren();
	void addChild(Object3D* child);

	void computeModel(bool fromParent);
	glm::vec3 computePosition();
	void translate(glm::vec3 translationVector);

	virtual void draw() = 0;
};
