#pragma once
#include <glad/glad.h>
#include "ShaderProgram.h"
#include "../geom/Mesh.h"

class Renderer
{
	public:
	Renderer();
	~Renderer();

	void clear() const;
	void clearZone(unsigned int x, unsigned int y, unsigned int width, unsigned int height) const;
	void draw(const Mesh& mesh);
};
