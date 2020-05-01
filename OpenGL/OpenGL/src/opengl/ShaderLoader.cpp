#include "ShaderLoader.h"
#include "../Constants.cpp"

ShaderLoader::ShaderLoader()
{
	this->current_vs_index = 0;
	this->current_fs_index = 0;
}

ShaderLoader::~ShaderLoader()
{
	// TODO JT : Clear ressources
}

void ShaderLoader::loadShaders()
{
	// Création des vertex shaders par défaut
	Shader* default_vs = new Shader("res/shaders/vertex/default.vert", "Default");
	this->addShader(default_vs, GL_VERTEX_SHADER);

	Shader* default_fs = new Shader("res/shaders/fragment/default.frag", "Default");
	Shader* colorInterpolation_fs = new Shader("res/shaders/fragment/colorInterpolation.frag", "Color Interpolation");
	this->addShader(default_fs, GL_FRAGMENT_SHADER);
	this->addShader(colorInterpolation_fs, GL_FRAGMENT_SHADER);
}

void ShaderLoader::compileShaders()
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

void ShaderLoader::setUniforms()
{
	// Pour set l'uniform le shaderProgram doit etre bind
	// TODO JT : améliorer gestion uniform
	if (this->current_fs_index == 0)
	{
		glm::vec4 color(0.9f, 0.0f, 0.0f, 1.0f);
		this->shaderProgram->setUniform4f(ShaderConstants::uColor, color);
	}
}

void ShaderLoader::setCurrentVsIndex(unsigned int index)
{
	this->current_vs_index = index;
}

void ShaderLoader::setCurrentFsIndex(unsigned int index)
{
	this->current_fs_index = index;
}

std::vector<const char*> ShaderLoader::getNames(GLenum type)
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

ShaderProgram* ShaderLoader::getShaderProgram()
{
	return this->shaderProgram;
}

void ShaderLoader::addShader(Shader* shader, GLenum type)
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