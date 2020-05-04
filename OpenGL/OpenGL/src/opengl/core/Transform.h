#pragma once
#include <iterator>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtx/quaternion.hpp"

class Transform
{
	public:
	glm::mat4 transform;

	Transform();
	~Transform();

	void computeTransform();

	void addTranslation(glm::mat4& translation);
	void addRotation(glm::mat4& rotation);
	void addScale(glm::mat4& scale);

	void resetTranslation();
	void resetRotation();
	void resetScale();

	glm::mat4 translation;
	private:

	glm::mat4 rotation;
	glm::mat4 scale;

	std::vector<glm::mat4> translations;
	std::vector<glm::mat4> rotations;
	std::vector<glm::mat4> scales;

	void computeTranslations();
	void computeRotations();
	void computeScale();
};
