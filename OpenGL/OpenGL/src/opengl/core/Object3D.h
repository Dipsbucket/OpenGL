#pragma once
#include <vector>
#include <iterator>

#include "glm/glm.hpp"
#include "glm/gtx/quaternion.hpp"
#include "../../interfaces/hasId.h"
#include "../../interfaces/hasName.h"

class Object3D : public hasName, public hasId
{
	public:
	Object3D* parent;
	std::vector<Object3D*> children;

	glm::vec3 position, scale, up;
	glm::quat orientation;
	glm::mat4 transform, model;

	bool visible;

	Object3D();
	Object3D(unsigned int id, std::string name, Object3D* parent);
	~Object3D();

	void init();
	bool isRootNode();
	bool hasChildren();
	void addChild(Object3D* child);

	virtual void draw() = 0;
};
