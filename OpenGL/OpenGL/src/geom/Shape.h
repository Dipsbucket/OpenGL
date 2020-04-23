#pragma once
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

#include "../interfaces/hasName.h"
#include "../utils/StringUtils.h"

class Shape :public hasName
{
	public:
	std::string name;
	unsigned int verticesSize, indexesSize;
	std::vector<float> vertices, colors, normals;
	std::vector<unsigned int> indexes;

	Shape();
	Shape(std::string name, std::vector<float> vertices, std::vector<unsigned int> indexes);
	~Shape();

	std::string getName();
	std::string toString();
};
