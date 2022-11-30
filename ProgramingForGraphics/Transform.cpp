#include "Transform.h"

vec3 Transform::GetPos()
{
	return m_position;
}
vec3 Transform::GetRot()
{
	return m_rotation;
}
vec3 Transform::GetScale()
{
	return m_scale;
}
void Transform::SetPos(vec3 newPos) { m_position = newPos; }
void Transform::SetRot(vec3 newRot) { m_rotation = newRot; }
void Transform::SetScale(vec3 newScale) { m_scale = newScale; }
