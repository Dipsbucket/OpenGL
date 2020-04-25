#pragma once
#include "Shape.h"

class ShapeFactory
{
	enum class DebugShape
	{
		TRIANGLE = 0,
		QUAD = 1
	};

	public:
	static Shape createDefault(DebugShape debugShape);
	static Shape buildTriangle();
	static Shape buildQuad();
};
