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



//glm::mat4 Camera::getCameraView()
//{
//	LookingAt = c_Target;
//	if (!m_Target)
//	{
//		LookingAt = m_Transform.GetPosition() + m_Forward;
//	}
//
//	return glm::lookAt(m_Transform.GetPosition(), m_CurrentTarget, m_Up);
//}


