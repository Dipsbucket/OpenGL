#pragma once
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <glad/glad.h>

#include "glm/glm.hpp"
#include <glm/gtx/string_cast.hpp>
#include "../interfaces/hasName.h"

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

class Mesh :public hasName
{
	public:
	std::string name;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	unsigned int verticesSize, indicesSize;
	unsigned int vao;

	Mesh();
	Mesh(std::string name, std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	~Mesh();

	std::string getName();
	const char* getNameAsChar();
	std::string toString();

	private:
	unsigned int vbo, ebo;

	void init();
};
