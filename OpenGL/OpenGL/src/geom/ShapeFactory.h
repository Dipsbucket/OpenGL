#pragma once
#include "ShapeConstants.h"
#include "Shape.h"

class ShapeFactory
{
	public:
	static Shape createDefault(ShapeConstants::DebugShape debugShape);
	static Shape buildTriangle();
};
