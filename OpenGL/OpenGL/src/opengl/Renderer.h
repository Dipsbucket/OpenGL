#pragma once
#include <glad/glad.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "ShaderProgram.h"

class Renderer
{
	public:
	Renderer();
	~Renderer();

	void clear() const;
	void draw(const VertexArray& va, const IndexBuffer& ibo, const ShaderProgram& sp);
};
