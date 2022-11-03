#define GLEW_STATIC

#include <glew.h> // needs to be first as openGL library relys on it
#include <SDL_opengl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SDL.h>
#include <iostream>
#include "triangles.h"
#include "window.h"
#include "mesh.h"
#include "Transform.h"


using namespace std;


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
		cerr << errorMessage << ": '" << error << " ' " << endl;
	}
}


triangles::triangles()
{


	float Verticies[]		// Define some points for the triangle
	{
		0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};

	GLuint VertexBufferObject = 0;			// Create a Vertex Buffer
	glGenBuffers(1, &VertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float),
		Verticies, GL_STATIC_DRAW);

	GLuint VertexArrayObject = 0;			// Create a vertex array object
	glGenVertexArrays(1, &VertexArrayObject);
	glBindVertexArray(VertexArrayObject);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);			// Bind vertex buffer object
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindVertexArray(0);

	const char* VertexShaderCode =			// shader code
		"#version 450\n"
		"in vec3 vp;"
		"void main() {"
		"gl_Position = vec4(vp, 1.0);"
		"}";

	const char* FragmentShaderCode =			// more shader code
		"#version 450\n"
		"out vec4 frag_colour;"
		"void main () {"
		"frag_colour = vec4(0.5, 0.0, 0.5, 1.0);"
		"}";

	GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);			// Linking and compiling the shaders
	glShaderSource(VertexShader, 1, &VertexShaderCode, NULL);		// Linking and compiling the shaders
	glCompileShader(VertexShader);									// Linking and compiling the shaders

	GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);		// Linking and compiling the shaders
	glShaderSource(FragmentShader, 1, &FragmentShaderCode, NULL);	// Linking and compiling the shaders
	glCompileShader(FragmentShader);								// Linking and compiling the shaders

	GLuint ShaderPrograme = glCreateProgram();		// Connect the shaders to a shader program
	glAttachShader(ShaderPrograme, VertexShader);	// Connect the shaders to a shader program
	glAttachShader(ShaderPrograme, FragmentShader);	// Connect the shaders to a shader program

	glLinkProgram(ShaderPrograme);
	CheckShaderError(ShaderPrograme, GL_LINK_STATUS, true,
	"Error: Program linking field: ");
	
	glValidateProgram(ShaderPrograme);
	CheckShaderError(ShaderPrograme, GL_VALIDATE_STATUS, true,
	"Error; Program is invalid: ");

	glClearColor(0.0f, 0.15f, 0.3f, 1.0f);
	glViewport(0, 0, 800, 600);

	while (true)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(ShaderPrograme);
		glBindVertexArray(VertexArrayObject);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		SDL_Delay(16);

		SDL_GL_SwapWindow(m_window);
	}

}

triangles::~triangles()
{
}
