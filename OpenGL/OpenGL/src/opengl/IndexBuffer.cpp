#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const void* data, unsigned int size)
{
	// Création du buffer
	glGenBuffers(1, &this->id);

	// Binding du buffer pour le rendre actif
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);

	// Déclaration de la taille des données contenues et pointeur vers les données
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
}

void IndexBuffer::bind() const
{
}

void IndexBuffer::unbind() const
{
}