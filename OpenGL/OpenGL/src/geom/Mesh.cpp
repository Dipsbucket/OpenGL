#include "Mesh.h"

Mesh::Mesh()
{
	this->name = "Unknown";
}

Mesh::Mesh(std::string name, std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
	this->name = !name.empty() ? name : "Unknown";
	this->vertices = vertices;
	this->verticesSize = vertices.size() * sizeof(float);
	this->indices = indices;
	this->indicesSize = indices.size() * sizeof(unsigned int);

	this->init();
}

Mesh::~Mesh()
{
	this->name.clear();
	this->vertices.clear();
	this->indices.clear();
}

std::string Mesh::getName()
{
	return this->name;
}

const char* Mesh::getNameAsChar()
{
	return this->name.c_str();
}

std::string Mesh::toString()
{
	std::string res("Shape :\n");
	res.append("name : " + this->name + "\n");

	if (!this->vertices.empty())
	{
		res.append("vertices :\n");
		for (std::vector<Vertex>::iterator iterator = this->vertices.begin(); iterator != this->vertices.end(); ++iterator)
		{
			res.append(iterator->toString());
		}
	}

	return res;
}

void Mesh::init()
{
	// Création des buffers et de l'array
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	// Bind du Vao : association du vbo et de l'ebo au vao
	glBindVertexArray(vao);

	// Bind et envoie des données au vbo
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	// Bind et envoie des données au ebo
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	// Normales
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	// Coordonnées des textures
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoordinates));

	// Tangente
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));

	// Bitangente
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));

	// Color
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	glBindVertexArray(0);
}