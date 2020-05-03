#pragma once
#include <glad/glad.h>
#include <list>
#include <unordered_map>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "utils/ShaderUtils.h"
#include "../interfaces/hasId.h"

class ShaderProgram :public hasId
{
	public:
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
	void setUniformMat4f(const std::string& name, glm::mat4& mat);
	int getUniformLocation(const std::string& name);
};
