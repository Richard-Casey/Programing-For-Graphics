#include "Lightbase.h"

Lightbase::Lightbase()
{
	M_Color = vec3(1, 1, 1);
}

Lightbase::~Lightbase()
{
}

void Lightbase::Draw(Camera* Cam)
{
	glUseProgram(0);

	glMatrixMode(GL_PROJECTION);
	mat4 temp = Cam->GetPerspective();
	glLoadMatrixf((const GLfloat*)&temp);
	glMatrixMode(GL_MODELVIEW);
	glm::mat4 MV = Cam->GetViewMatrix() * m_Transform.GetModel();
	glLoadMatrixf((const GLfloat*)&MV[0]);

	glBegin(GL_LINES);
	glm::vec3 p1 = this->m_Transform.GetPos();
	glm::vec3 p2 = p1;

	glColor3f(1, 0, 0);
	glVertex3fv(&p1.x);
	p2 = p1 + glm::vec3(1, 0, 0) * 0.1f;
	glColor3f(1, 0, 0);
	glVertex3fv(&p2.x);

	glColor3f(0, 1, 0);
	glVertex3fv(&p1.x);
	p2 = p1 + glm::vec3(0, 1, 0) * 0.1f;
	glColor3f(0, 1, 0);
	glVertex3fv(&p2.x);

	glColor3f(0, 0, 1);
	glVertex3fv(&p1.x);
	p2 = p1 + glm::vec3(0, 0, 1) * 0.1f;
	glColor3f(0, 0, 1);
	glVertex3fv(&p2.x);

	glEnd();
}