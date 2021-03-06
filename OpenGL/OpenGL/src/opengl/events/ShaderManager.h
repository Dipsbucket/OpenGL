#pragma once

#include "../ShaderProgram.h"
#include "../Shader.h"

class ShaderManager
{
	public:

	ShaderManager();
	~ShaderManager();

	void loadShaders();
	void compileShaders();
	void setUniforms();
	void setMVPUniforms(glm::mat4& model, glm::mat4& view, glm::mat4& projection);
	void setModelUniform(glm::mat4& model);

	void setCurrentVsIndex(unsigned int index);
	void setCurrentFsIndex(unsigned int index);
	std::vector<const char*> getNames(GLenum type);

	bool hasMVP();
	ShaderProgram* getShaderProgram();

	private:
	unsigned int current_vs_index, current_fs_index;
	ShaderProgram* shaderProgram;
	std::unordered_map<unsigned int, Shader*> vertexShaderCache;
	std::unordered_map<unsigned int, Shader*> fragmentShaderCache;

	void addShader(Shader* shader, GLenum type);
};
