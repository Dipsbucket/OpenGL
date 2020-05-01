#pragma once
#include <glad/glad.h>
#include <string>
#include <iterator>
#include <vector>
#include <unordered_map>

#include "glm/glm.hpp"
#include "ShaderProgram.h"
#include "Shader.h"

class ShaderLoader
{
	public:
	ShaderLoader();
	~ShaderLoader();

	void loadShaders();
	void compileShaders();
	void setUniforms();

	void setCurrentVsIndex(unsigned int index);
	void setCurrentFsIndex(unsigned int index);
	std::vector<const char*> getNames(GLenum type);
	ShaderProgram* getShaderProgram();

	private:
	unsigned int current_vs_index, current_fs_index;
	ShaderProgram* shaderProgram;
	std::unordered_map<unsigned int, Shader*> vertexShaderCache;
	std::unordered_map<unsigned int, Shader*> fragmentShaderCache;

	void addShader(Shader* shader, GLenum type);
};
