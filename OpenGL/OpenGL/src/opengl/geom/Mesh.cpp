#include "Mesh.h"

Mesh::Mesh(std::string name, Object3D* parent) : Object3D(name, parent)
{
	// Ne pas utiliser
}

Mesh::Mesh(std::string name, Object3D* parent, std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) : Object3D(name, parent)
{
	this->vertices = vertices;
	this->verticesSize = vertices.size() * sizeof(float);
	this->indices = indices;
	this->indicesSize = indices.size() * sizeof(unsigned int);

	this->drawPrimitive = GL_TRIANGLES;

	this->init();
}

Mesh::~Mesh()
{
}

void Mesh::draw()
{
	// Dessine avec VertexBuffer sans IndexBuffer
	// 1. Mode de dessin
	// 2. A partir de quel vertex on veut dessiner : offset possible
	// 3. Nombre de vertex a dessiner
	//glDrawArrays(GL_TRIANGLES, 0, 3);

	// Dessine avec VertexBuffer et IndexBuffer
	// 1. Mode de dessin
	// 2. Nombre d'indice à dessiner
	// 3. Type de données dans l'IndexBuffer
	// 4. Pointeur vers l'IndexBuffer. No need car bind dans le constructeur
	if (!this->isRootNode())
	{
		glBindVertexArray(this->vao);
		glDrawElements(this->drawPrimitive, this->indicesSize, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
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