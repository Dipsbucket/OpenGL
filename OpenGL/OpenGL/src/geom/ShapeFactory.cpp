#include "ShapeFactory.h"

Shape ShapeFactory::buildTriangle()
{
	std::string name = "Triangle";

	const int size_vertices = 9;
	const float array_vertices[] =
	{
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	const int size_indexes = 3;
	const int array_indexes[] = {
		0, 1, 2
	};

	std::vector<float> vertices;
	vertices.assign(array_vertices, array_vertices + size_vertices);

	std::vector<int> indexes;
	indexes.assign(array_indexes, array_indexes + size_indexes);

	return Shape(name, vertices, indexes);
}