#pragma once
#include <iterator>
#include <vector>
#include <glad/glad.h>

#include "../events/EventManager.h"

class Renderer
{
	public:
	Renderer();
	~Renderer();

	void clear() const;
	void clearZone(unsigned int x, unsigned int y, unsigned int width, unsigned int height) const;
	void draw(EventManager* eventManager, Object3D* node);
};
