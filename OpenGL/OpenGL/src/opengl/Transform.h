#pragma once
#include <iterator>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtx/quaternion.hpp"

class Transform
{
	public:

	Transform();
	~Transform();

	private:
	std::vector<glm::mat4> transforms;
	glm::mat4 model;
};
