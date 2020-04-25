#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const void* data, unsigned int count)
{
	this->count = count;

	// Cr�ation du buffer
	glGenBuffers(1, &this->id);

	// Binding du buffer pour le rendre actif
	this->bind();

	// D�claration de la taille des donn�es contenues et pointeur vers les donn�es
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