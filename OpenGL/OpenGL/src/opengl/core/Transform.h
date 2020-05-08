#pragma once
#include <iterator>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtx/quaternion.hpp"

#include "../utils/StringUtils.h"
#include "../utils/MathUtils.h"

class Transform
{
	public:
	glm::mat4 transform;

	Transform();
	~Transform();

	void computeTransform();

	void translate(glm::mat4& translation, bool reset);
	void rotate(glm::quat& rotation);

	void resetTransform();
	void clearTransform();
	void saveTransform();

	private:
	bool modified;
	glm::quat orientation;

	glm::mat4 translation;
	glm::mat4 rotation;
	std::vector<glm::mat4> transformationsCache;
};
