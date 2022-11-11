#pragma once
#include "Transform.h"
#include "Camera.h"

class Lightbase
{
public:
	Lightbase();
	~Lightbase();
	void Draw(Camera* Cam);
	vec3 M_Color;
	Transform m_Transform;
	Transform& GetTransform() { return m_Transform; };
private:
	
	
};