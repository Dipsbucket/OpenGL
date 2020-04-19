#include "ShaderUtils.h"

void ShaderUtils::createProgram(unsigned int& program, std::list<unsigned int> ids)
{
	program = glCreateProgram();

	if (!ids.empty())
	{
		std::list <unsigned int>::iterator iter;
		for (iter = ids.begin(); iter != ids.end(); ++iter)
		{
			glAttachShader(program, *iter);
		}
	}
}

void ShaderUtils::linkProgram(unsigned int& program)
{
	glLinkProgram(program);
}

void ShaderUtils::validateProgram(unsigned int& program)
{
	glValidateProgram(program);
}

unsigned int ShaderUtils::createShader(const std::string filePath, GLenum type)
{
	std::string source = FileUtils::parseFile(filePath);
	const char* src = source.c_str();

	unsigned int id = glCreateShader(type);
	glShaderSource(id, 1, &src, NULL);
	glCompileShader(id);

	// TODO JT : handle if error
	printErrors(id, GL_COMPILE_STATUS, type);

	//glAttachShader(program, id);
	//glDeleteShader(id);
	return id;
}

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