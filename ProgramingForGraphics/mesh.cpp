#include "mesh.h"
#include "Transform.h"
#include "Vertex.h"

Mesh::Mesh(Vertex* verts, unsigned int vertCount, unsigned int* indices, unsigned int numIndices)
{
	m_drawCount = numIndices;

	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	glGenBuffers(NUM_BUFFERS, m_vertexBufferObjects);

	//position
	glEnableVertexAttribArray(POSITION_VB);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObjects[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, vertCount * sizeof(Vertex),
		&verts[0], GL_STATIC_DRAW);
	glVertexAttribPointer(POSITION_VB, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);

	//index
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexBufferObjects[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(unsigned int),
		indices, GL_STATIC_DRAW);

	glBindVertexArray(0);


}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::Draw()
{
	glBindVertexArray(m_vertexArrayObject);
	glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

