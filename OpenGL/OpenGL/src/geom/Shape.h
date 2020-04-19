#pragma once
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

#include "../interfaces/hasName.h"
#include "../utils/StringUtils.h"

class Shape :public hasName
{
	private:
	std::string name;
	std::vector<float> vertices, colors, normals;
	std::vector<int> indexes;

	public:
	unsigned int VBO;

	Shape(std::string name, std::vector<float> vertices, std::vector<int> indexes);
	~Shape();

	std::string getName();
	std::string toString();
};
