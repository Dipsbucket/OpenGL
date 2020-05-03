#include "MeshFactory.h"
#include "../../Constants.cpp"

Mesh MeshFactory::buildTriangle(unsigned int id)
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

	return Mesh(id, name, nullptr, vertices, indices, std::vector<Texture>());
}

Mesh MeshFactory::buildQuad(unsigned int id)
{
	std::string name = "Quad";

	Vertex v0 =
	{
		glm::vec3(-0.5f, -0.5f, 0.0f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 1.f)
	};

	Vertex v1 =
	{
		glm::vec3(0.5f, -0.5f, 0.0f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 1.f, 1.f)
	};

	Vertex v2 =
	{
		glm::vec3(0.5f,  0.5f, 0.0f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(1.f, 1.f, 0.f)
	};

	Vertex v3 =
	{
		glm::vec3(-0.5f,  0.5f, 0.0f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(1.f, 0.f, 0.f)
	};

	std::vector<Vertex> vertices;
	vertices.push_back(v0);
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);

	std::vector<unsigned int> indices;
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(0);

	return Mesh(id, name, nullptr, vertices, indices, std::vector<Texture>());
}

Mesh MeshFactory::buildTetrahedron(unsigned int id)
{
	std::string name = "Tetrahedron";
	std::vector<Vertex> vertices, tmp;

	unsigned int count = 3;
	constexpr float PI = glm::pi<float>();
	float radius = 0.5f;
	float theta = 0;
	float dtheta = (2 * PI) / count;

	float x, y = -0.5f, z;
	float r, g, b;
	// Calcul des points à la base du tétrahedre
	for (unsigned int i = 0; i < count; i++)
	{
		x = radius * glm::cos(theta);
		z = radius * glm::sin(theta);
		theta += dtheta;

		r = i == 0 ? 1.0f : 0.0f;
		g = i == 1 ? 1.0f : 0.0f;
		b = i == 2 ? 1.0f : 0.0f;

		Vertex v =
		{
			glm::vec3(x, y, z),
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(r, g, b)
		};

		tmp.push_back(v);
	}

	// Calcul de la hauteur
	glm::vec3 pt1 = tmp[0].position;
	glm::vec3 pt2 = tmp[1].position;
	double length = glm::distance(pt1, pt2);
	float h = (float)(length * glm::sqrt(2 / 3));

	// Ajout du top
	Vertex v0 =
	{
		glm::vec3(0.0f, h, 0.0f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(1.f, 1.f, 0.f)
	};
	vertices.push_back(v0);
	vertices.insert(vertices.end(), tmp.begin(), tmp.end());
	tmp.clear();

	std::vector<unsigned int> indices;
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(3);

	indices.push_back(0);
	indices.push_back(3);
	indices.push_back(1);

	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(3);

	return Mesh(id, name, nullptr, vertices, indices, std::vector<Texture>());
}