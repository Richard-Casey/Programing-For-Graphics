#define GLEW_STATIC

#include <glew.h>
#include <SDL_opengl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SDL.h>
#include <iostream>
#include "mesh.h"
#include "Transform.h"
#include "main.h"
#include "Input.h"
#include "Camera.h"

using namespace std;
#undef main

void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		cerr << errorMessage << "; '" << error << " ' " << endl;
	}
}


int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32); // 32 bit inc RGBA
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16); // Depth is not 32 bit

	SDL_Window* window = SDL_CreateWindow("My Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	SDL_GLContext GLContext = SDL_GL_CreateContext(window);

	glewExperimental = GL_TRUE;
	GLenum status = glewInit();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	if (status != GLEW_OK)
	{
		cout << "GLEW failed to initialise!" << endl;
	}
	
	float Verticies[]{

		0.5f, 1.0f, 0.5f,
		1.0f, 0.0f, 0.5f,
		0.0f, 0.0f, 0.5f

	};

	float Verticies2[]{

		-0.5f, 0.0f, -0.5f,
		0.0f, -1.0f, -0.5f,
		-1.0f, -1.0f, -0.5f

	};

	Camera* cam = new Camera(70.0f, 800.0f/600.0f,0.5f,100.0f);
	cam->SetCamPos(vec3(0, 0, -5));

	Camera* camLookAt = new Camera(70.0f, 800.0f / 600.0f, 0.1f, 100.0f);
	
	Mesh Tri1(Verticies, 3);
	
	GLuint VertexBufferObject = 0;
	glGenBuffers(1, &VertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float),
		Verticies2, GL_STATIC_DRAW);

	GLuint VertexArrayObject = 0;
	glGenVertexArrays(1, &VertexArrayObject);
	glBindVertexArray(VertexArrayObject);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VertexArrayObject);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindVertexArray(0);

	GLuint VertexBufferObject1 = 0;
	glGenBuffers(1, &VertexBufferObject1);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject1);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float),
		Verticies, GL_STATIC_DRAW);

	GLuint VertexArrayObject1 = 0;
	glGenVertexArrays(1, &VertexArrayObject1);
	glBindVertexArray(VertexArrayObject1);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VertexArrayObject1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindVertexArray(0);

	const char* VertexShaderCode =
		
		"#version 450\n"
		"in vec3 vp;"
		"uniform mat4 model;"
		"uniform mat4 view;"
		"uniform mat4 perspective;"
		"void main() {"
		"   gl_Position = perspective * view * model * vec4(vp, 1.0);"
		"}";

	const char* FragmentShaderCode =
		"#version 450\n"
		"out vec4 frag_colour;"
		"void main() {"
		"   frag_colour = vec4(0.0, 0.5, 1.0, 1.0);" // Fill colour in RGBA
		"}";

	GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShader, 1, &VertexShaderCode, NULL);
	glCompileShader(VertexShader);
	GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShader, 1, &FragmentShaderCode, NULL);
	glCompileShader(FragmentShader);

	GLuint ShaderPrograme = glCreateProgram();
	glAttachShader(ShaderPrograme, VertexShader);
	glAttachShader(ShaderPrograme, FragmentShader);

	glLinkProgram(ShaderPrograme);
	CheckShaderError(ShaderPrograme, GL_LINK_STATUS, true,
		"Error: Program linking field: ");
	glValidateProgram(ShaderPrograme);
	CheckShaderError(ShaderPrograme, GL_VALIDATE_STATUS, true,
		"Error; Program is invalid: ");

	glClearColor(0.0f, 0.15f, 0.3f, 1.0f);
	glViewport(0, 0, 800, 600);

	Tri1.Draw();

	Tri1.trans.SetPos(vec3 (0, 0, 0));
	
	Input* input = new Input();
	
	while (true)
	{
		cam->UpdateLocalAxis();
		// This moves the camera
		input->Update();

		if (input->KeyIsPressed(KEY_D))
		{
			vec3  pos = cam->M_Transform.GetPos();
			pos += -cam->m_Right * 0.1f;
			cam->M_Transform.SetPos(pos);
		}

		if (input->KeyIsPressed(KEY_W))
		{
			vec3  pos = cam->M_Transform.GetPos();
			pos += cam->m_Forward * 0.1f;
			cam->M_Transform.SetPos(pos);
		}

		if (input->KeyIsPressed(KEY_A))
		{
			// Back
			vec3  pos = cam->M_Transform.GetPos();
			pos += cam->m_Right * 0.1f;
			cam->M_Transform.SetPos(pos);
		}

		if (input->KeyIsPressed(KEY_S))
		{

			vec3  pos = cam->M_Transform.GetPos();
			pos += -cam->m_Forward * 0.1f;
			cam->M_Transform.SetPos(pos);

		}

		cam->MouseMoveTarget();



		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(ShaderPrograme);
		
		vec3 SlowRotate = Tri1.trans.GetRot();
		SlowRotate[0] += 0.01;
		Tri1.trans.SetRot(SlowRotate);

		glBindVertexArray(VertexArrayObject);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		glUseProgram(ShaderPrograme);

		GLint modelLoc = glGetUniformLocation(ShaderPrograme, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &Tri1.trans.GetModel()[0][0]);

		GLint ViewLoc = glGetUniformLocation(ShaderPrograme, "view");
		glUniformMatrix4fv(ViewLoc, 1, GL_FALSE, &cam->GetViewMatrix()[0][0]);

		GLint perspectivLoc = glGetUniformLocation(ShaderPrograme, "perspective");
		glUniformMatrix4fv(perspectivLoc, 1, GL_FALSE, &cam->GetPerspective()[0][0]);

		glBindVertexArray(VertexArrayObject1);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		SDL_Delay(16);

		SDL_GL_SwapWindow(window);
		
	}

	SDL_GL_DeleteContext(GLContext); // All Clean up but in theory should never get here due to infinate loop
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();
	return 0;

	while (true)
	{
		glClearColor(0.0f, 0.15f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, 800, 600);

		SDL_GL_SwapWindow(window);
		SDL_Delay (500);

		glClearColor(0.75f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, 800, 600);

		SDL_GL_SwapWindow(window);
		SDL_Delay(500);
	}

	SDL_GL_DeleteContext(GLContext);
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();


	return 0;

	
}
