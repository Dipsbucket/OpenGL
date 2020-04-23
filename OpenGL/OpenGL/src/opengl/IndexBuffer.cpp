#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const void* data, unsigned int size)
{
	// Cr�ation du buffer
	glGenBuffers(1, &this->id);

	// Binding du buffer pour le rendre actif
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);

	// D�claration de la taille des donn�es contenues et pointeur vers les donn�es
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