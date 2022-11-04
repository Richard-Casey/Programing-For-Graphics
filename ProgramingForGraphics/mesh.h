#pragma once
#ifndef MESH_H
#define MESH_H

#include <glm\glm.hpp>
#include <glew.h>
#include "Transform.h"

class Mesh
{
public:
	Transform trans;
	Mesh(float* verts, unsigned int vertCount);
	void Draw();
	~Mesh();
	
private:
	GLuint m_vertexBufferObject = 0;
	GLuint m_vertexArrayObject = 0;
};

#endif // !MESH_H