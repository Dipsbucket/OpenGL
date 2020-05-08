#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"

class MathUtils
{
	public:
	static void mat4ToArray(float** arrayPointer, glm::mat4 value);
	static bool isIdentity(float** arrayPointer, int dimension);
};