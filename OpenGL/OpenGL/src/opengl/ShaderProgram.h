#pragma once
#include <glad/glad.h>
#include <string>
#include <list>
#include <vector>
#include <iterator>
#include <unordered_map>
#include "glm/glm.hpp"
#include "Shader.h"
#include "utils/ShaderUtils.h"

class ShaderProgram
{
	public:
	unsigned int id;
	std::unordered_map<std::string, int> uniformLocationCache;
	ShaderProgram();
	~ShaderProgram();

	void attachShader(unsigned int& shaderId) const;
	void attachShaders(std::list<unsigned int> ids) const;
	void linkProgram();
	void validateProgram() const;
	void bind() const;
	void unbind() const;
	void clear() const;

	void setUniform4f(const std::string& name, glm::vec4& vec);
	int getUniformLocation(const std::string& name);
};
