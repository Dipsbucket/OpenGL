#pragma once
#include "Mesh.h"

class MeshFactory
{
	public:

	// 2D
	static Mesh buildLinesCoordinateSystem(int depth);
	static Mesh buildLinesUnit();
	static Mesh buildPolygon(std::string name, unsigned int nbPoints);

	// 3D
	static Mesh buildSphere(unsigned int meridians, unsigned int parallels);
	static Mesh buildTetrahedron(unsigned int id);
};
