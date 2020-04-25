#pragma once
#include <glad\glad.h>

class IndexBuffer
{
	public:
	unsigned int id;
	unsigned int count;

	IndexBuffer(const void* data, unsigned int count);
	~IndexBuffer();

	void bind() const;
	void unbind() const;
};
