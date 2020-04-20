#pragma once
#include <glad/glad.h>
#include <list>
#include <iterator>

class ShaderProgram
{
	public:
	unsigned int id;
	ShaderProgram();
	~ShaderProgram();

	void attachShader(unsigned int& shaderId) const;
	void attachShaders(std::list<unsigned int> ids) const;
	void linkProgram() const;
	void validateProgram() const;
	void bind();
	void unbind();
};
