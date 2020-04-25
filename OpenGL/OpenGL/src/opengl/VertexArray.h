#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
	public:
	unsigned int id;
	VertexArray();
	~VertexArray();

	void bind() const;
	void unbind() const;
	void attachBuffer(const VertexBuffer& vb, const VertexBufferLayout& vbl);
};
