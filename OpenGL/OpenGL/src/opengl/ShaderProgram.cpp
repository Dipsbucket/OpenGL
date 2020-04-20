#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
{
	this->id = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(this->id);
}

void ShaderProgram::attachShader(unsigned int& shaderId) const
{
	glAttachShader(this->id, shaderId);
}

void ShaderProgram::attachShaders(std::list<unsigned int> ids) const
{
	if (!ids.empty())
	{
		std::list <unsigned int>::iterator iter;
		for (iter = ids.begin(); iter != ids.end(); ++iter)
		{
			glAttachShader(this->id, *iter);
		}
	}
}

void ShaderProgram::linkProgram() const
{
	glLinkProgram(this->id);
}

void ShaderProgram::validateProgram() const
{
	glValidateProgram(this->id);
}

void ShaderProgram::bind()
{
	glUseProgram(this->id);
}

void ShaderProgram::unbind()
{
	glUseProgram(0);
}