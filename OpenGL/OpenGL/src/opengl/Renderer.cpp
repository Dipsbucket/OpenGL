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
	glClear(GL_COLOR_BUFFER_BIT);
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

void Renderer::draw(const Mesh& mesh)
{
	// Dessine avec VertexBuffer sans IndexBuffer
	// 1. Mode de dessin
	// 2. A partir de quel vertex on veut dessiner : offset possible
	// 3. Nombre de vertex a dessiner
	//glDrawArrays(GL_TRIANGLES, 0, 3);

	// Dessine avec VertexBuffer et IndexBuffer
	// 1. Mode de dessin
	// 2. Nombre d'indice à dessiner
	// 3. Type de données dans l'IndexBuffer
	// 4. Pointeur vers l'IndexBuffer. No need car bind dans le constructeur

	// TODO JT : A mettre dans Mesh
	glBindVertexArray(mesh.vao);
	glDrawElements(GL_TRIANGLES, mesh.indicesSize, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}