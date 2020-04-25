#pragma once
#include <vector>
#include <glad/glad.h>

struct AttributeDataType
{
	unsigned int count;
	unsigned int type;
	unsigned int normalized;
	unsigned int size;
};

class VertexBufferLayout
{
	public:
	std::vector<AttributeDataType> attributeDataTypes;
	unsigned int stride;

	VertexBufferLayout();
	~VertexBufferLayout();

	template<typename T>
	void push(unsigned int count)
	{
		static_assert(false);
	}

	template< >
	void push<float>(unsigned int count)
	{
		this->attributeDataTypes.push_back({ count, GL_FLOAT, GL_FALSE, count * sizeof(float) });
	}
};
