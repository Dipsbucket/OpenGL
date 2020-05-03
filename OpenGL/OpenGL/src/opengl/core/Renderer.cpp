#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::clear() const
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::clearZone(unsigned int x, unsigned int y, unsigned int width, unsigned int height) const
{
	glDisable(GL_SCISSOR_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glScissor(x, y, width, height);
	glEnable(GL_SCISSOR_TEST);

	this->clear();
}

void Renderer::draw(Object3D* rootNode)
{
	rootNode->draw();

	for (std::vector<Object3D*>::iterator iterator = rootNode->children.begin(); iterator != rootNode->children.end(); ++iterator)
	{
		this->draw((*iterator));
	}
}