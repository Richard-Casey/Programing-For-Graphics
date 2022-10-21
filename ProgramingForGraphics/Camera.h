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
	vec3 GetLookingAt();
	void SetCamPos(vec3);
	void SetCamRot(vec3);
	void SetCamScale(vec3);
	//void SetLookingAt(vec3);
	SDL_Event MouseMoveTarget;
	void Draw();
	~Camera();
	

	mat4 getCameraView() 
	{
		m_Forward = normalize(vec3(0) - c_Position);
		m_Right = normalize(cross(vec3(0,1,0), m_Forward));
		m_Up = cross(m_Forward, m_Right);

		return glm::lookAt(c_Position, vec3(LookingAt += m_Forward), m_Up);

	}

	mat4 GetPerspective()
	{
		return perspective;
	}

	//glm::mat4 GetViewMatrix()
	//{
	//	m_CurrentTarget = m_Target;
	//	if (!m_UseTarget)
	//	{
	//		m_CurrentTarget = M_Transfrom.GetPosition() + m_Forward;
	//	}
	//	//current target
	//		//	\/
	//	return glm::lookAt(M_Transfrom.GetPosition(), m_CurrentTarget, m_Up);
	//}

	//bool firstMove = true;
	//GLint lastX; //GLint is an int through GL - basically the same thing
	//GLint lastY;// Declared GLint for lastX and last Y but not defined until later


	//void MouseMoveTarget(SDL_Event* e)
	//{
	//	if (!m_UseTarget)
	//	{
	//		int mouseX, mouseY;
	//		SDL_GetMouseState(&mouseX, &mouseY); // "&" before a variable returns the reference to itinstead of returning a value
	//		if (firstMove)
	//		{
	//			lastX = mouseX;
	//			lastY = mouseY;
	//			firstMove = false;
	//		}

	//		GLfloat xOffset = mouseX - lastX; // GLfloat is a float through openGL - you get the idea...
	//		GLfloat yOffset = lastY - mouseY;
	//		lastX = mouseX;
	//		lastY = mouseY;

	//		GLfloat sensitivity = 0.5;

	//		xOffset *= sensitivity;
	//		yOffset *= sensitivity;

	//		M_Transform.GetRotation().y += xOffset;
	//		M_Transfrom.GetRotation().x += yOffset; 

	//		//stop gimmble lock (rotation crazyness!!)
	//		if (M_Transfrom.GetRotation().x > 89.0f)
	//			M_Transfrom.GetRotation().x = 89.0f;
	//		if (M_Transfrom.GetRotation().x < -89.0f)
	//			M_Transfrom.GetRotation().x = -89.0f;

	//		vec3 front;
	//		front.x = cos(radians(M_Transfrom.GetRotation().y)) * cos(radians(M_Transfrom.GetRotation().x));
	//		front.y = sin(radians(M_Transfrom.GetRotation().x));
	//		front.z = sin(radians(M_Transfrom.GetRotation().y)) * cos(radians(M_Transfrom.GetRotation().x));

	//		m_Forward = normalize(front);
	//		//cout << m_Forward.x <<" "<<m_Forward.y <<" "<<m_Forward.z << endl;
	//	}
	//}



private:
	vec3 c_Position;
	vec3 c_Rotation;
	vec3 c_Scale;

	vec3 LookingAt = c_Position;
	
	GLuint c_vertexBufferObject = 0;
	GLuint c_vertexArrayObject = 0;
	mat4 perspective;

	vec3 m_Forward;
	vec3 m_Right;
	vec3 m_Up;
};

#endif