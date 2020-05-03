#pragma once
#include <iterator>
#include <vector>
#include <glad/glad.h>

#include "../core/Object3D.h"

class Renderer
{
	public:
	Renderer();
	~Renderer();

	void clear() const;
	void clearZone(unsigned int x, unsigned int y, unsigned int width, unsigned int height) const;
	void draw(Object3D* rootNode);
};
