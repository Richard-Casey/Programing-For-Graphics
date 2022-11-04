#pragma once
#ifndef MESH_H
#define MESH_H

#include <glm\glm.hpp>
#include <glew.h>
#include "Transform.h"
#include "Vertex.h"

class Mesh
{
public:
	Transform trans;
	Mesh(Vertex* verts, unsigned int vertCount, unsigned int *indicies, unsigned int numIndicies);
	void Draw();
	~Mesh();
	int m_drawCount;
	
private:
	GLuint m_vertexBufferObjects[2];
	GLuint m_vertexArrayObject = 0;
};

#endif // !MESH_H