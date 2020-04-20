#pragma once
#include <glad/glad.h>
#include <string>
#include "utils/ShaderUtils.h"
#include "../utils/FileUtils.h"

class Shader
{
	public:
	unsigned int id;
	Shader(const std::string& filePath, GLenum type);
	~Shader();
};
