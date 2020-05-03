#include "Shader.h"

Shader::Shader(const std::string& filePath, std::string name, ShaderType type)
{
	this->source = FileUtils::parseFile(filePath);
	this->name = name;
	this->type = type;
}

Shader::~Shader()
{
	glDeleteShader(this->id);
}

void Shader::compile(GLenum type)
{
	this->id = glCreateShader(type);
	const char* src = this->source.c_str();
	glShaderSource(this->id, 1, &src, NULL);
	glCompileShader(this->id);

	// TODO JT : handle if error
	ShaderUtils::printShaderErrors(this->id, GL_COMPILE_STATUS, type);
}