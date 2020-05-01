#include "MeshFactory.h"

Mesh MeshFactory::createDefault(DebugShape debugShape)
{
	Mesh shape;
	switch (debugShape)
	{
		case DebugShape::TRIANGLE:
			shape = buildTriangle();
			break;
		case DebugShape::QUAD:
			shape = buildQuad();
			break;
		default:
			break;
	}

	return shape;
}

Mesh MeshFactory::buildTriangle()
{
	std::string name = "Triangle";

	Vertex v0 =
	{
		glm::vec3(-0.5f, -0.5f, 0.0f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(1.f, 0.f, 0.f)
	};

	Vertex v1 =
	{
		glm::vec3(0.5f, -0.5f, 0.0f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 1.f, 0.f)
	};

	Vertex v2 =
	{
		glm::vec3(0.0f,  0.5f, 0.0f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 1.f)
	};

	std::vector<Vertex> vertices;
	vertices.push_back(v0);
	vertices.push_back(v1);
	vertices.push_back(v2);

	std::vector<unsigned int> indices;
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	return Mesh(name, vertices, indices, std::vector<Texture>());
}

Mesh MeshFactory::buildQuad()
{
	// TODO JT
	//std::string name = "Quad";

	//const int size_vertices = 12;
	//const float array_vertices[] =
	//{
	//	-0.5f, -0.5f, 0.0f, // 0
	//	 0.5f, -0.5f, 0.0f, // 1
	//	 0.5f,  0.5f, 0.0f, // 2
	//	-0.5f,  0.5f, 0.0f  // 3
	//};

	//const int size_indexes = 6;
	//const int array_indexes[] = {
	//	0, 1, 2,
	//	2, 3, 0
	//};

	//std::vector<float> vertices;
	//vertices.assign(array_vertices, array_vertices + size_vertices);

	//std::vector<unsigned int> indexes;
	//indexes.assign(array_indexes, array_indexes + size_indexes);

	//return Mesh(name, vertices, indexes);
	return Mesh();
}

Mesh MeshFactory::buildTetrahedron()
{
	// TODO JT
	//std::string name = "Tetrahedron";

	//std::vector<float> vertices;

	//unsigned int count = 3;
	//constexpr float PI = glm::pi<float>();
	//float radius = 1.f;
	//float theta = 0;
	//float dtheta = (2 * PI) / count;

	//// Ajout du top
	//vertices.push_back(0.f);
	//vertices.push_back(0.5f);
	//vertices.push_back(0.f);

	//float x, y = -0.5f, z;
	//// Calcul des points à la base du tétrahedre
	//for (unsigned int i = 0; i < count; i++)
	//{
	//	x = radius * glm::cos(theta);
	//	z = radius * glm::sin(theta);
	//	theta += dtheta;

	//	vertices.push_back(x);
	//	vertices.push_back(y);
	//	vertices.push_back(z);
	//}

	//const int size_indexes = 12;
	//const int array_indexes[] = {
	//	0, 1, 2,
	//	0, 2, 3,
	//	0, 3, 1,
	//	1, 2, 3
	//};

	//std::vector<unsigned int> indexes;
	//indexes.assign(array_indexes, array_indexes + size_indexes);

	//return Mesh(name, vertices, indexes);
	return Mesh();
}