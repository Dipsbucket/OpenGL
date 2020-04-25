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

void Renderer::draw(const VertexArray& va, const IndexBuffer& ibo, const ShaderProgram& sp)
{
	sp.bind();
	va.bind();
	ibo.bind();

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
	glDrawElements(GL_TRIANGLES, ibo.count, GL_UNSIGNED_INT, nullptr);
}