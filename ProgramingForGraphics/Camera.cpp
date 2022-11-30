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

Camera::~Camera()
{
}


glm::mat4 Camera::GetViewMatrix()
{
	m_CurrentTarget = target;
	m_CurrentTarget = M_Transform.GetPos() + m_Forward;
	
	//current target
	return glm::lookAt(M_Transform.GetPos(), m_CurrentTarget, m_Up);
}

bool firstMove = true;
GLint lastX;	// GLint is an int through GL - basically the same thing
GLint lastY;	// Declared GLint for lastX and last Y but not defined until later


void Camera::MouseMoveTarget()
{
	
		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY); // "&" before a variable returns the reference to it instead of returning a value
		if (firstMove)
		{
			lastX = mouseX;
			lastY = mouseY;
			firstMove = false;
		}

		GLfloat xOffset = mouseX - lastX; // GLfloat is a float through openGL - you get the idea...
		GLfloat yOffset = lastY - mouseY;
		lastX = mouseX;
		lastY = mouseY;

		GLfloat sensitivity = 0.3;

		xOffset *= sensitivity;
		yOffset *= sensitivity;


		//stop gimmble lock (rotation crazyness!!)
		vec3 TargetRot = M_Transform.GetRot();
		TargetRot.y += xOffset;
		TargetRot.x += yOffset;

		if (TargetRot.x > 89.0f)
			TargetRot.x = 89.0f;
		if (TargetRot.x < -89.0f)
			TargetRot.x = -89.0f;
		M_Transform.SetRot(TargetRot);

		vec3 front;
		front.x = cos(radians(M_Transform.GetRot().y)) * cos(radians(M_Transform.GetRot().x));
		front.y = sin(radians(M_Transform.GetRot().x));
		front.z = sin(radians(M_Transform.GetRot().y)) * cos(radians(M_Transform.GetRot().x));

		m_Forward = normalize(front);
			
}