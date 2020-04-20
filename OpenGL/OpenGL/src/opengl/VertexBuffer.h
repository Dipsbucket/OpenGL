#pragma once
#include <glad\glad.h>
#include <GLFW/glfw3.h>

class VertexBuffer
{
	private:
	unsigned int id;

	public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void bind() const;
	void unbind() const;
};