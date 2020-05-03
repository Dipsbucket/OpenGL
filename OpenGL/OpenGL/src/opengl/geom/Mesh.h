#pragma once
#include <glad/glad.h>

#include "glm/glm.hpp"
#include <glm/gtx/string_cast.hpp>
#include "../core/Object3D.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoordinates;
	glm::vec3 tangent;
	glm::vec3 bitangent;
	glm::vec3 color;

	std::string toString()
	{
		std::string res("");
		res.append("Position : " + glm::to_string(this->position) + "\n");
		res.append("Normal : " + glm::to_string(this->normal) + "\n");
		res.append("Texture Coordinates : " + glm::to_string(this->textureCoordinates) + "\n");
		res.append("Tangent : " + glm::to_string(this->tangent) + "\n");
		res.append("Bitangent : " + glm::to_string(this->bitangent) + "\n");
		res.append("Color : " + glm::to_string(this->color) + "\n");

		return res;
	}
};

struct Texture
{
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh :public Object3D
{
	public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	unsigned int verticesSize, indicesSize;
	unsigned int vao;

	Mesh(unsigned int id, std::string name, Object3D* parent);
	Mesh(unsigned int id, std::string name, Object3D* parent, std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	virtual ~Mesh();

	void draw() override;

	// Surcharges
	std::string toString() override;

	private:
	unsigned int vbo, ebo;

	void init();
};
