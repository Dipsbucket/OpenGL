#pragma once
#include "Mesh.h"

class MeshFactory
{
	public:

	// 2D
	static Mesh buildTriangle(unsigned int id);
	static Mesh buildQuad(unsigned int id);

	// 3D
	static Mesh buildTetrahedron(unsigned int id);
};
