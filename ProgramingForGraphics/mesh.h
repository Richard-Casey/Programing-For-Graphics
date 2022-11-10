#pragma once
#ifndef MESH_H
#define MESH_H

#include <glm\glm.hpp>
#include <glew.h>
#include "Transform.h"
#include "Vertex.h"
#include <SDL.h>
#include <glm/gtx/normal.hpp>

class Mesh
{
public:
	Transform trans;
	Mesh(Vertex* verts, unsigned int vertCount, unsigned int *indicies, unsigned int numIndicies);
	void Draw();
	~Mesh();
	int m_drawCount;
	
private:

	enum
	{
		POSITION_VB,
		TEXCOORD_VB,
		INDEX_VB,
		NORMAL_VB,
		NUM_BUFFERS
	};	
	GLuint m_vertexBufferObjects[NUM_BUFFERS];
	GLuint m_vertexArrayObject = 0;
};

#endif // !MESH_H