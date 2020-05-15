#include "MeshFactory.h"
#include "../../Constants.cpp"

Mesh MeshFactory::buildLinesCoordinateSystem(int depth)
{
	std::string name = "Lines Coordinate System";

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	unsigned int cpt = 0;
	glm::vec3 color = glm::vec3(0.0f);

	// Construction des lignes verticales
	for (float i = (float)-depth; i <= (float)depth; i += 0.25f)
	{
		if (i == (int)i)
		{
			color = glm::vec3(0.0f, 0.0f, 0.0f);
		}
		else
		{
			color = glm::vec3(1.0f, 1.0f, 1.0f);
		}

		// vertical.z negatif
		Vertex v0 =
		{
			glm::vec3(i, 0.0f, -depth),
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(color.r, color.g, color.b)
		};

		// vertical.z positif
		Vertex v1 =
		{
			glm::vec3(i, 0.0f, depth),
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(color.r, color.g, color.b)
		};

		// horizontal.x negatif
		Vertex v2 =
		{
			glm::vec3(-depth, 0.0f, i),
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(color.r, color.g, color.b)
		};

		// horizontal.x negatif
		Vertex v3 =
		{
			glm::vec3(depth, 0.0f, i),
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(color.r, color.g, color.b)
		};

		vertices.push_back(v0);
		vertices.push_back(v1);
		vertices.push_back(v2);
		vertices.push_back(v3);

		indices.push_back(cpt);
		cpt++;
		indices.push_back(cpt);
		cpt++;
		indices.push_back(cpt);
		cpt++;
		indices.push_back(cpt);
		cpt++;
	}

	Mesh linesCoordinateSystem = Mesh(name, nullptr, vertices, indices, std::vector<Texture>());
	linesCoordinateSystem.drawPrimitive = GL_LINES;
	return linesCoordinateSystem;
}

Mesh MeshFactory::buildLinesUnit()
{
	std::string name = "Lines Unit";

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	Vertex centreX =
	{
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 1.f)
	};

	Vertex unitX =
	{
		glm::vec3(1.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 1.f)
	};
	vertices.push_back(centreX);
	vertices.push_back(unitX);
	indices.push_back(0);
	indices.push_back(1);

	Vertex centreY =
	{
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(1.f, 0.f, 0.f)
	};

	Vertex unitY =
	{
		glm::vec3(0.f, 1.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(1.f, 0.f, 0.f)
	};
	vertices.push_back(centreY);
	vertices.push_back(unitY);
	indices.push_back(2);
	indices.push_back(3);

	Vertex centreZ =
	{
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 1.f, 0.f)
	};

	Vertex unitZ =
	{
		glm::vec3(0.f, 0.f, 1.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 1.f, 0.f)
	};
	vertices.push_back(centreZ);
	vertices.push_back(unitZ);
	indices.push_back(4);
	indices.push_back(5);

	Mesh linesUnit = Mesh(name, nullptr, vertices, indices, std::vector<Texture>());
	linesUnit.drawPrimitive = GL_LINES;
	return linesUnit;
}

Mesh MeshFactory::buildPolygon(std::string name, unsigned int nbPoints)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	unsigned int count = nbPoints;
	constexpr float PI = glm::pi<float>();
	float radius = 1.0f;
	float theta = PI / 2.f;
	float dtheta = (2 * PI) / count;

	float x, y = 0.0f, z;
	float r = 0.0f, g, b;

	// Ajout du centre
	Vertex centre =
	{
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(1.f, 0.f, 0.f)
	};
	vertices.push_back(centre);

	// Calcul des points du polygone
	for (unsigned int i = 0; i < count; i++)
	{
		x = radius * glm::cos(theta);
		z = radius * glm::sin(theta);
		theta += dtheta;

		g = i % 2 == 0 ? 1.0f : 0.0f;
		b = i % 2 == 1 ? 1.0f : 0.0f;

		Vertex v =
		{
			glm::vec3(x, y, z),
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(r, g, b)
		};

		vertices.push_back(v);
	}

	// Calcul de la topologie
	for (unsigned int i = 1; i <= count; i++)
	{
		indices.push_back(0);
		indices.push_back(i);
		indices.push_back((i % count) + 1);
	}

	return Mesh(name, nullptr, vertices, indices, std::vector<Texture>());
}

Mesh MeshFactory::buildSphere(unsigned int meridians, unsigned int parallels)
{
	std::string name = "Sphere";

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	constexpr float PI = glm::pi<float>();
	float radius = 1.0f;

	float theta = 0;
	float phi = PI / 2;

	float dtheta = (2 * PI) / (float)meridians;
	float dphi = (PI / (float)(parallels + 1));

	// Calcul des points de la sphère
	for (unsigned int i = 0; i < meridians; i++)
	{
		phi = PI / 2 - dphi;
		for (unsigned int j = 0; j < parallels; j++)
		{
			float x = radius * glm::cos(phi) * glm::sin(theta);
			float y = radius * glm::sin(phi);
			float z = radius * glm::cos(phi) * glm::cos(theta);

			// TODO JT : TEST
			float r = j % 2 == 0 ? 1.0f : 0.0f;
			float g = i % 2 == 0 ? 1.0f : 0.0f;

			Vertex v =
			{
				glm::vec3(x, y, z),
				glm::vec3(0.f, 0.f, 0.f),
				glm::vec3(0.f, 0.f, 0.f),
				glm::vec3(0.f, 0.f, 0.f),
				glm::vec3(0.f, 0.f, 0.f),
				glm::vec3(r, g, 0.0f)
			};
			vertices.push_back(v);

			phi -= dphi;
		}
		theta += dtheta;
	}

	// Calcul de la topologie
	for (unsigned int i = 0; i < meridians; i++)
	{
		for (unsigned int j = 0; j < parallels - 1; j++)
		{
			int indice_1 = i * meridians + j;
			int indice_2 = i * meridians + j + 1;
			int indice_3 = ((i + 1) * meridians + j + 1) % (meridians * parallels);
			int indice_4 = ((i + 1) * meridians + j) % (meridians * parallels);

			// TODO JT : TEST
			indices.push_back(indice_1);
			indices.push_back(indice_2);
			indices.push_back(indice_3);
			indices.push_back(indice_4);
		}
	}

	Mesh sphere = Mesh(name, nullptr, vertices, indices, std::vector<Texture>());
	//sphere.drawPrimitive = GL_QUADS;
	return sphere;
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

	return Mesh(name, nullptr, vertices, indices, std::vector<Texture>());
}