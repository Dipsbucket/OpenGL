#pragma once
#include <iostream>
#include <glad/glad.h>

class ShaderUtils
{
	public:
	static void printShaderErrors(unsigned int& id, GLenum errorType, GLenum shaderType);
	static void printShaderProgramErrors(unsigned int& id, GLenum errorType);
	static std::string getShaderType(GLenum type);
	static std::string getErrorType(GLenum type);
};
