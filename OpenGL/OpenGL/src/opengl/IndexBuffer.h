#pragma once
#include <glad\glad.h>

class IndexBuffer
{
	private:
	unsigned int id;

	public:
	IndexBuffer(const void* data, unsigned int size);
	~IndexBuffer();

	void bind() const;
	void unbind() const;
};
