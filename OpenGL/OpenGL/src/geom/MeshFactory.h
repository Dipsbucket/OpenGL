#pragma once
#include "Mesh.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class MeshFactory
{
	enum class DebugShape
	{
		TRIANGLE = 0,
		QUAD = 1
	};

	public:
	static Mesh createDefault(DebugShape debugShape);

	static Mesh buildTriangle();
	static Mesh buildQuad();

	static Mesh buildTetrahedron();
};
