#define GLEW_STATIC

#include <glew.h> // needs to be first as openGL library relys on it
#include <SDL_opengl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SDL.h>
#include <iostream>
#include "window.h"


using namespace std;


void window::createWindow()
{
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32); // 32 bit inc RGBA
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16); // Depth is not 32 bit

	SDL_Window* m_window = SDL_CreateWindow(
		"Lets try this again ...",	// Window title
		SDL_WINDOWPOS_CENTERED,		// initial x position
		SDL_WINDOWPOS_CENTERED,		// initial y position
		800,						// width in pixels
		600,						// height in pixels
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);	// window behaviour flags
	SDL_GLContext GLContext = SDL_GL_CreateContext(m_window);
	

	glewExperimental = GL_TRUE;
	GLenum status = glewInit();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	if (status != GLEW_OK)
	{
		cout << "GLEW failed to initialise!" << endl;
	}

	while (true)
	{
		glClearColor(0.0f, 0.15f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, 800, 600);

		SDL_GL_SwapWindow(m_window);
	}

	/*SDL_GL_DeleteContext(GLContext);
	SDL_DestroyWindow(m_window);
	m_window = NULL;
	SDL_Quit();*/
}
