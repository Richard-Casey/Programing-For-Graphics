#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <glm\glm.hpp>
#include <glew.h>
#include "Transform.h"

class Camera
{
public:
	//Transform transCamera;
	Camera(float fov, float aspect, float zNear, float zFar, const vec3& pos = vec3(),
		const vec3& rot = vec3(),
		const vec3& scale = vec3()) :
		c_Position(pos),
		c_Rotation(rot),
		c_Scale(scale)
	{
		perspective = glm::perspective(fov, aspect, zNear, zFar);
	}

	vec3 GetCamPos();
	vec3 GetCamRot();
	vec3 GetCamScale();
	void SetCamPos(vec3);
	void SetCamRot(vec3);
	void SetCamScale(vec3);
	void Draw();
	~Camera();

	mat4 getCamerView() 
	{
		m_Forward = normalize(vec3(0) - c_Position);
		m_Right = normalize(cross(vec3(0,1,0), m_Forward));
		m_Up = cross(m_Forward, m_Right);

		return glm::lookAt(c_Position, vec3(0), m_Up);

	}

	mat4 GetPerspective()
	{
		return perspective;
	}

private:
	vec3 c_Position;
	vec3 c_Rotation;
	vec3 c_Scale;
	GLuint c_vertexBufferObject = 0;
	GLuint c_vertexArrayObject = 0;
	mat4 perspective;

	vec3 m_Forward;
	vec3 m_Right;
	vec3 m_Up;
};

#endif