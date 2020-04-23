#include "Shape.h"

Shape::Shape()
{
	this->name = "Unknown";
}

Shape::Shape(std::string name, std::vector<float> vertices, std::vector<unsigned int> indexes)
{
	this->name = !name.empty() ? name : "Unknown";
	this->vertices = vertices;
	this->verticesSize = vertices.size() * sizeof(float);
	this->indexes = indexes;
	this->indexesSize = indexes.size() * sizeof(unsigned int);
}

Shape::~Shape()
{
	this->name.clear();
	this->vertices.clear();
	this->colors.clear();
	this->normals.clear();
	this->indexes.clear();
}

std::string Shape::getName()
{
	return this->name;
}

std::string Shape::toString()
{
	std::string res("Shape :\n");
	res.append("name : " + this->name + "\n");
	res.append("vertices : " + StringUtils::toString(this->vertices) + "\n");
	res.append("indexes : " + StringUtils::toString(this->indexes) + "\n");
	res.append("normals : " + StringUtils::toString(this->normals) + "\n");
	res.append("colors : " + StringUtils::toString(this->colors) + "\n");

	return res;
}