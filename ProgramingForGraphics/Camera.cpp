#include "Camera.h"


vec3 Camera::GetCamPos()
{
	return c_Position;
}
vec3 Camera::GetCamRot()
{
	return c_Rotation;
}
vec3 Camera::GetCamScale()
{
	return c_Scale;
}

vec3 Camera::GetLookingAt()
{
	return LookingAt;
}

void Camera::SetCamPos(vec3 newPos) { c_Position = newPos; }
void Camera::SetCamRot(vec3 newRot) { c_Rotation = newRot; }
void Camera::SetCamScale(vec3 newScale) { c_Scale = newScale; }










/*Camera::Camera(float* verts, unsigned int vertCount)
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
}*/

