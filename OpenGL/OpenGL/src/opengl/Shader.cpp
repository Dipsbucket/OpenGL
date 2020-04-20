#include "Shader.h"

Shader::Shader(const std::string& filePath, GLenum type)
{
	std::string source = FileUtils::parseFile(filePath);
	const char* src = source.c_str();

	this->id = glCreateShader(type);
	glShaderSource(this->id, 1, &src, NULL);
	glCompileShader(this->id);

	// TODO JT : handle if error
	ShaderUtils::printErrors(this->id, GL_COMPILE_STATUS, type);
}

Shader::~Shader()
{
	glDeleteShader(this->id);
}