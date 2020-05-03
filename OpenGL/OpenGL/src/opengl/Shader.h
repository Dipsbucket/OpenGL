#pragma once
#include <glad/glad.h>
#include <string>
#include "utils/ShaderUtils.h"
#include "../utils/FileUtils.h"
#include "../interfaces/hasId.h"
#include "../interfaces/hasName.h"

enum class ShaderType
{
	NONE = 0,

	// Vertex shader
	MVP = 1,

	// Fragment Shader
	COLOR_INTERPOLATION = 2
};

class Shader :public hasId, public hasName
{
	public:
	ShaderType type;
	Shader(const std::string& filePath, std::string name, ShaderType type);
	~Shader();

	void compile(GLenum type);

	private:
	std::string source;
};
