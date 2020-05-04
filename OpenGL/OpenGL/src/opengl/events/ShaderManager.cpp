#include "ShaderManager.h"
#include "../Constants.cpp"

ShaderManager::ShaderManager()
{
	this->current_vs_index = 0;
	this->current_fs_index = 0;
}

ShaderManager::~ShaderManager()
{
	// TODO JT : Clear ressources
}

void ShaderManager::loadShaders()
{
	// Création des vertex shaders par défaut
	Shader* default_vs = new Shader("res/shaders/vertex/default.vert", "Default", ShaderType::NONE);
	Shader* defaultProjection_vs = new Shader("res/shaders/vertex/defaultProjection.vert", "Default Projection", ShaderType::MVP);
	this->addShader(default_vs, GL_VERTEX_SHADER);
	this->addShader(defaultProjection_vs, GL_VERTEX_SHADER);

	Shader* default_fs = new Shader("res/shaders/fragment/default.frag", "Default", ShaderType::NONE);
	Shader* colorInterpolation_fs = new Shader("res/shaders/fragment/colorInterpolation.frag", "Color Interpolation", ShaderType::COLOR_INTERPOLATION);
	this->addShader(default_fs, GL_FRAGMENT_SHADER);
	this->addShader(colorInterpolation_fs, GL_FRAGMENT_SHADER);
}

void ShaderManager::compileShaders()
{
	// Création du Shader program et assignation des shaders
	Shader* vs = this->vertexShaderCache.at(this->current_vs_index);
	Shader* fs = this->fragmentShaderCache.at(this->current_fs_index);

	vs->compile(GL_VERTEX_SHADER);
	fs->compile(GL_FRAGMENT_SHADER);

	this->shaderProgram = new ShaderProgram();
	this->shaderProgram->attachShader(vs->id);
	this->shaderProgram->attachShader(fs->id);
	this->shaderProgram->linkProgram();
	this->shaderProgram->validateProgram();

	glDetachShader(this->shaderProgram->id, vs->id);
	glDetachShader(this->shaderProgram->id, fs->id);
	glDeleteShader(vs->id);
	glDeleteShader(fs->id);

	this->shaderProgram->bind();
	this->setUniforms();
}

void ShaderManager::setUniforms()
{
	// Pour set l'uniform le shaderProgram doit etre bind
	if ((*this->fragmentShaderCache.at(this->current_fs_index)).type == ShaderType::NONE)
	{
		glm::vec4 color(0.9f, 0.0f, 0.0f, 1.0f);
		this->shaderProgram->setUniform4f(ShaderConstants::uColor, color);
	}
}

void ShaderManager::setMVPUniforms(glm::mat4& model, glm::mat4& view, glm::mat4& projection)
{
	// Pour set l'uniform le shaderProgram doit etre bind
	if ((*this->vertexShaderCache.at(this->current_vs_index)).type == ShaderType::MVP)
	{
		this->setModelUniform(model);
		this->shaderProgram->setUniformMat4f(ShaderConstants::uView, view);
		this->shaderProgram->setUniformMat4f(ShaderConstants::uProjection, projection);
	}
}

void ShaderManager::setModelUniform(glm::mat4& model)
{
	// Pour set l'uniform le shaderProgram doit etre bind
	if ((*this->vertexShaderCache.at(this->current_vs_index)).type == ShaderType::MVP)
	{
		this->shaderProgram->setUniformMat4f(ShaderConstants::uModel, model);
	}
}

void ShaderManager::setCurrentVsIndex(unsigned int index)
{
	this->current_vs_index = index;
}

void ShaderManager::setCurrentFsIndex(unsigned int index)
{
	this->current_fs_index = index;
}

std::vector<const char*> ShaderManager::getNames(GLenum type)
{
	std::vector<const char*> res;

	switch (type)
	{
		case GL_VERTEX_SHADER:
			for (std::unordered_map<unsigned int, Shader*>::iterator iterator = this->vertexShaderCache.begin(); iterator != this->vertexShaderCache.end(); ++iterator)
			{
				res.push_back(iterator->second->getNameAsChar());
			}
			break;
		case GL_FRAGMENT_SHADER:
			for (std::unordered_map<unsigned int, Shader*>::iterator iterator = this->fragmentShaderCache.begin(); iterator != this->fragmentShaderCache.end(); ++iterator)
			{
				res.push_back(iterator->second->getNameAsChar());
			}
			break;
		default:
			break;
	}

	return res;
}

bool ShaderManager::hasMVP()
{
	return (*this->vertexShaderCache.at(this->current_vs_index)).type == ShaderType::MVP;
}

ShaderProgram* ShaderManager::getShaderProgram()
{
	return this->shaderProgram;
}

void ShaderManager::addShader(Shader* shader, GLenum type)
{
	unsigned int size;

	switch (type)
	{
		case GL_VERTEX_SHADER:
			size = this->vertexShaderCache.size();
			this->vertexShaderCache.insert({ size, shader });
			break;
		case GL_FRAGMENT_SHADER:
			size = this->fragmentShaderCache.size();
			this->fragmentShaderCache.insert({ size, shader });
			break;
		default:
			break;
	}
}