#include "Camera.h"
#include "Transform.h"

Camera::Camera(float* verts, unsigned int vertCount)
{
	glGenVertexArrays(1, &c_vertexArrayObject);
	glBindVertexArray(c_vertexArrayObject);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &c_vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, c_vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, vertCount * 3 * sizeof(float),
		verts, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindVertexArray(0);
}

Camera::~Camera()
{
	glDeleteVertexArrays(1, &c_vertexArrayObject);
}

