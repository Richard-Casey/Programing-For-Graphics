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
#include <vector>
#include "Vertex.h"
#include "Shader.h"
#include "Texture.h"
#include "Lightbase.h"
#include "OBJLoader.h"
using namespace std;
#undef main


int main(int argc, char* argv[])
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

	vector<Vertex> SquareVerticies;

	SquareVerticies.push_back(Vertex(vec3(-0.5f, 0.5f, -1.0f), vec2(0, 0)));		// Top Left
	SquareVerticies.push_back(Vertex(vec3(0.5f, 0.5f, -1.0f), vec2(1, 0)));			// Top Right
	SquareVerticies.push_back(Vertex(vec3(0.5f, -0.5f, -1.0f), vec2(1, 1)));		// Bottom Right
	SquareVerticies.push_back(Vertex(vec3(-0.5f, -0.5f, -1.0f), vec2(0, 1)));		// Bottom Left

	unsigned int SquareIndecies[]
	{
		0,1,2,0,2,3
	};

	Camera camera(70.0f, 800.0f / 600.0f, 0.01f, 500.0f);
	camera.SetCamPos(vec3(0, 0, 0));


	string directoryUni = "C:\\Users\\Administrator\\Desktop\\s233122\\Programing For Graphics\\resources\\";
	string directoryHome = "C:\\Users\\riche\\OneDrive\\Desktop\\s233122\\Programing-For-Graphics\\resources\\";

	Camera* camLookAt = new Camera(70.0f, 800.0f / 600.0f, 0.01f, 500.0f);

	Shader* basicShader = new Shader(directoryHome + "Basic", camera);
	Texture* texture = new Texture();
	texture->LoadTexture(directoryHome + "Image.jpg");
	Mesh Tri1(&SquareVerticies[0], SquareVerticies.size(), &SquareIndecies[0], 6);
	Lightbase* light = new Lightbase();

	string AmbiantLoc; // Be aware the following code may need to be moved into its own .h and .ccp
	string DiffuseLoc;
	string SpecLoc;
	string NormalLoc;

	vector <uint> Indecies;

	vector<Vertex> LoadedVerts = OBJLoader::LoadOBJ("../resources", "blocks_01.obj",
		AmbiantLoc, DiffuseLoc, SpecLoc, NormalLoc, Indecies);

	GLuint AmbiantTextureID = texture->LoadTexture("../resources/" + AmbiantLoc);
	GLuint DiffuseTextureID = texture->LoadTexture("../resources/" + DiffuseLoc);
	GLuint SpeculerTextureID = texture->LoadTexture("../resources/" + SpecLoc);
	GLuint NormalTextureID = texture->LoadTexture("../resources/" + NormalLoc); //End of code that will prob get moved :/

	Mesh Cube(&LoadedVerts[0], LoadedVerts.size(), &Indecies[0], Indecies.size());

	Mesh Square1(&SquareVerticies[0], SquareVerticies.size(), &SquareIndecies[0], 6);
	Square1.trans.SetScale(Square1.trans.GetScale() * 50.0f);
	Square1.trans.SetRot(vec3(radians(90.0f), 0.0f, 0.0f));
	Square1.trans.SetPos(vec3(0, -1.0, 0));

	Cube.trans.SetScale(Cube.trans.GetScale() * 0.06f);
	Cube.trans.SetPos(vec3(0, -1, 3));
	
	glClearColor(0.0f, 0.15f, 0.3f, 1.0f);
	glViewport(0, 0, 800, 600);
		
	Tri1.trans.SetPos(vec3(1.0, 0, 0));
	Tri1.trans.SetRot(vec3(0, 4.73, 0));

	Input* input = new Input();

	while (true)
	{
		camera.UpdateLocalAxis();
		// This moves the camera

		input->Update();

		if (input->KeyIsPressed(KEY_D))
		{
			vec3  pos = camera.M_Transform.GetPos();
			pos += -camera.m_Right * 0.04f;
			camera.M_Transform.SetPos(pos);
		}

		if (input->KeyIsPressed(KEY_W))
		{
			vec3  pos = camera.M_Transform.GetPos();
			pos += camera.m_Forward * 0.04f;
			camera.M_Transform.SetPos(pos);
		}

		if (input->KeyIsPressed(KEY_A))
		{
			vec3  pos = camera.M_Transform.GetPos();
			pos += camera.m_Right * 0.04f;
			camera.M_Transform.SetPos(pos);
		}

		if (input->KeyIsPressed(KEY_S))
		{

			vec3  pos = camera.M_Transform.GetPos();
			pos += -camera.m_Forward * 0.04f;
			camera.M_Transform.SetPos(pos);

		}

		if (input->KeyIsPressed(KEY_ESCAPE))
		{
			printf("QUITTING GAME THINGY");
			SDL_GL_DeleteContext(GLContext); // All Clean up but in theory should never get here due to infinate loop
			SDL_DestroyWindow(window);
			window = NULL;
			SDL_Quit();
			return 0;
		}

		camera.MouseMoveTarget();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		static float i;
		i += 0.01;
		light->GetTransform().SetPos(vec3(sin(i), 0, 0));
		light->Draw(&camera);

		basicShader->Bind();

		// we only have 32 texture units availible to us. 0 to 31
		glActiveTexture(GL_TEXTURE0);
		GLuint TextureLoc = glGetUniformLocation(basicShader->GetProgram(), "texture_diffuse");
		glUniform1i(TextureLoc, 0); // 0 for location 0
		glBindTexture(GL_TEXTURE_2D, DiffuseTextureID);
		basicShader->Update(Tri1.trans, *light);

		glActiveTexture(GL_TEXTURE1);
		TextureLoc = glGetUniformLocation(basicShader->GetProgram(), "texture_normal");
		glUniform1i(TextureLoc, 1);	// 1 for location 1
		glBindTexture(GL_TEXTURE_2D, NormalTextureID);

		glActiveTexture(GL_TEXTURE2);
		TextureLoc = glGetUniformLocation(basicShader->GetProgram(), "texture_spec");
		glUniform1i(TextureLoc, 2);	// 2 for location 2
		glBindTexture(GL_TEXTURE_2D, SpeculerTextureID);

		Tri1.Draw();

		Square1.Draw();

		basicShader->Update(Cube.trans, *light);

		Cube.Draw();

		SDL_GL_SwapWindow(window);
		
		SDL_Delay(16);

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
		SDL_Delay(500);

	}

	SDL_GL_DeleteContext(GLContext);
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();


	return 0;


}
