#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <glm\glm.hpp>
#include <glew.h>
#include "Transform.h"

class Camera
{
public:
	Transform transCamera;
	Camera(float* verts, unsigned int vertCount);
	void Draw();
	~Camera();

private:
	GLuint c_vertexBufferObject = 0;
	GLuint c_vertexArrayObject = 0;
};

#endif