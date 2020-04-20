#pragma once
#include <iostream>
#include <glad/glad.h>

class ShaderUtils
{
	public:
	static void printErrors(unsigned int& id, GLenum errorType, GLenum shaderType);
	static std::string getShaderType(GLenum type);
	static std::string getErrorType(GLenum type);
};
