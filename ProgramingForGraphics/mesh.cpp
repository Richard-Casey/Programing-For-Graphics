#include "mesh.h"
#include "Transform.h"
#include "Vertex.h"

Mesh::Mesh(Vertex* verts, unsigned int vertCount, unsigned int* indicies, unsigned int numIndicies)
{
	m_drawCount = numIndicies;

	/*float SquareVerticies[]
	{
		-0.5,0.05f,0.0f,
		0.5f, 0.5f, 0.0f,
		-0.5f,-0.5f,0.0f,
		0.5f,-0.5f,0.0f
	};*/

	/*unsigned int SquareIndecies[]
	{
		0,1,2,0,2,3
	};*/


	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);
	glEnableVertexAttribArray(0);

	glGenBuffers(2, m_vertexBufferObjects);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObjects[0]);
	glBufferData(GL_ARRAY_BUFFER, vertCount  * sizeof(Vertex),
		verts, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexBufferObjects[1]); 
	// binding to [1] so as not to overwrite the position information from m_vertexBufferObjects[0]
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndicies * sizeof(unsigned int), indicies, GL_STATIC_DRAW);

	glBindVertexArray(0); // For safety apparently!

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
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

