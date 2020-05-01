#pragma once
#include <glad/glad.h>
#include <string>
#include "utils/ShaderUtils.h"
#include "../utils/FileUtils.h"
#include "../interfaces/hasName.h"

class Shader :public hasName
{
	public:
	std::string name;
	unsigned int id;

	Shader(const std::string& filePath, std::string name);
	~Shader();

	void compile(GLenum type);

	std::string getName();
	const char* getNameAsChar();
	std::string toString();

	private:
	std::string source;
};
