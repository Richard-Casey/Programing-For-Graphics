#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <glm\glm.hpp>
#include <glew.h>
#include "Transform.h"
#include <SDL.h>

class Camera
{
public:
	Camera(float fov, float aspect, float zNear, float zFar, const vec3& pos = vec3(),
		const vec3& rot = vec3(),
		const vec3& scale = vec3()) :
		c_Position(pos),
		c_Rotation(rot),
		c_Scale(scale)
		
	{
		perspective = glm::perspective(fov, aspect, zNear, zFar);
	}

	void MouseMoveTarget();
	vec3 GetCamPos();
	Transform M_Transform;
	vec3 target{ 0,0,0 };
	vec3 m_CurrentTarget;
	vec3 GetCamRot();
	vec3 GetCamScale();
	vec3 GetLookingAt();
	void SetCamPos(vec3);
	void SetCamRot(vec3);
	void SetCamScale(vec3);
	void Draw();
	~Camera();	

	void UpdateLocalAxis()
	{
		m_Right = normalize(cross(vec3(0, 1, 0), m_Forward));
		m_Up = cross(m_Forward, m_Right);
	}

	mat4 GetViewMatrix();

	mat4 GetPerspective()
	{
		return perspective;
	}

private:
	vec3 c_Position;
	vec3 c_Rotation;
	vec3 c_Scale;

	vec3 LookingAt = c_Position;
	
	GLuint c_vertexBufferObject = 0;
	GLuint c_vertexArrayObject = 0;
	mat4 perspective;

public:
	vec3 m_Forward;
	vec3 m_Right;
	vec3 m_Up;
};

#endif