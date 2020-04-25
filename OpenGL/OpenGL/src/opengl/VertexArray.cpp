#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &this->id);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &this->id);
}

void VertexArray::bind() const
{
	glBindVertexArray(this->id);
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::attachBuffer(const VertexBuffer& vb, const VertexBufferLayout& vbl)
{
	this->bind();
	vb.bind();

	const auto& attributeDataTypes = vbl.attributeDataTypes;
	for (unsigned int i = 0; i < attributeDataTypes.size(); i++)
	{
		AttributeDataType adt = attributeDataTypes[i];
		unsigned int offset = 0;

		// Active le vertex attribute array d'indice i
		// 0 : vertex.position
		glEnableVertexAttribArray(i);

		// Doit être appelé pour chaque attribute, ici attribute = vertex.positions
		// 1. index de l'attribute : 0 pour vertex.positions
		//	1.1	Doit match avec le layout 0 du VertexShader !!!
		// 2. vertex.positions > nombre de float pour une coordonnée, ici xyz donc 3
		// 3. type de la donnée
		// 4. Forcer la normalisation
		// 5. vertex.positions > nb bytes séparant 2 coordonnées, ici 3 float par coordonnée
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glVertexAttribPointer(i, adt.count, adt.type, adt.normalized, adt.size, (const void*)offset);

		offset = adt.count * adt.size;
	}
}