#pragma once
#include <iostream>
#include <list>
#include <iterator>
#include <glad/glad.h>
#include "FileUtils.h"

class ShaderUtils
{
	public:
	static void createProgram(unsigned int& program, std::list <unsigned int> ids);
	static void linkProgram(unsigned int& program);
	static void validateProgram(unsigned int& program);
	static unsigned int createShader(const std::string filePath, GLenum type);
	static void printErrors(unsigned int& id, GLenum errorType, GLenum shaderType);
	static std::string getShaderType(GLenum type);
	static std::string getErrorType(GLenum type);
};
