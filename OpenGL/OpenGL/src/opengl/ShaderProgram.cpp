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

void ShaderProgram::bind() const
{
	glUseProgram(this->id);
}

void ShaderProgram::unbind() const
{
	glUseProgram(0);
}

void ShaderProgram::setUniform4f(const std::string& name, glm::vec4& vec)
{
	glUniform4f(this->getUniformLocation(name), vec.x, vec.y, vec.z, vec.w);
}

int ShaderProgram::getUniformLocation(const std::string& name)
{
	if (this->uniformLocationCache.find(name) == uniformLocationCache.end())
	{
		int uniformLocation = glGetUniformLocation(this->id, name.c_str());
		// TODO JT : GERER -1 uniform n'éxiste pas
		this->uniformLocationCache[name] = uniformLocation;
	}

	return this->uniformLocationCache[name];
}