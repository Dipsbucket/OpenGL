#include "ShapeFactory.h"

Shape ShapeFactory::createDefault(ShapeConstants::DebugShape debugShape)
{
	Shape shape;
	switch (debugShape)
	{
		case ShapeConstants::DebugShape::TRIANGLE:
			shape = buildTriangle();
			break;
		default:
			break;
	}

	return shape;
}

Shape ShapeFactory::buildTriangle()
{
	std::string name = "Triangle";

	const int size_vertices = 9;
	const float array_vertices[] =
	{
		-0.5f, -0.5f, 0.0f, // 0
		 0.5f, -0.5f, 0.0f, // 1
		 0.0f,  0.5f, 0.0f  // 2
	};

	const int size_indexes = 3;
	const int array_indexes[] = {
		0, 1, 2
	};

	std::vector<float> vertices;
	vertices.assign(array_vertices, array_vertices + size_vertices);

	std::vector<unsigned int> indexes;
	indexes.assign(array_indexes, array_indexes + size_indexes);

	return Shape(name, vertices, indexes);
}

Shape ShapeFactory::buildQuad()
{
	std::string name = "Quad";

	const int size_vertices = 12;
	const float array_vertices[] =
	{
		-0.5f, -0.5f, 0.0f, // 0
		 0.5f, -0.5f, 0.0f, // 1
		 0.5f,  0.5f, 0.0f, // 2
		-0.5f,  0.5f, 0.0f  // 3
	};

	const int size_indexes = 6;
	const int array_indexes[] = {
		0, 1, 2,
		2, 3, 0
	};

	std::vector<float> vertices;
	vertices.assign(array_vertices, array_vertices + size_vertices);

	std::vector<unsigned int> indexes;
	indexes.assign(array_indexes, array_indexes + size_indexes);

	return Shape(name, vertices, indexes);
}