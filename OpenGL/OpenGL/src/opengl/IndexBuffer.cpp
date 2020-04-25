#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const void* data, unsigned int count)
{
	this->count = count;

	// Création du buffer
	glGenBuffers(1, &this->id);

	// Binding du buffer pour le rendre actif
	this->bind();

	// Déclaration de la taille des données contenues et pointeur vers les données
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->count, data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &this->id);
}

void IndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
}

void IndexBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}