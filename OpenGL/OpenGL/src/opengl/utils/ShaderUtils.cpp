#include "ShaderUtils.h"

void ShaderUtils::printErrors(unsigned int& id, GLenum errorType, GLenum shaderType)
{
	int success;
	glGetShaderiv(id, errorType, &success);

	if (!success)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)malloc(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);

		std::cout << "SHADER ERROR > ErrorType : " + getErrorType(errorType) + ", ShaderType : " + getShaderType(shaderType) + " :" << std::endl;
		std::cout << message << std::endl;

		glDeleteShader(id);
		free(message);
	}
}

std::string ShaderUtils::getShaderType(GLenum type)
{
	std::string res("Unknown");
	switch (type)
	{
		case GL_VERTEX_SHADER:
			res = "Vertex";
			break;
		case GL_FRAGMENT_SHADER:
			res = "Fragment";
			break;
		default:
			res = "Program";
			break;
	}

	return res;
}

std::string ShaderUtils::getErrorType(GLenum type)
{
	std::string res("Unknown");
	switch (type)
	{
		case GL_COMPILE_STATUS:
			res = "Compilation";
			break;
		case GL_LINK_STATUS:
			res = "Linking";
			break;
		default:
			break;
	}

	return res;
}