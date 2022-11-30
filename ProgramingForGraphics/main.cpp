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
#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_opengl3.h"
#include "Imgui/imgui_impl_sdl.h"
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

	// Initialise ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForOpenGL(window, GLContext);
	ImGui_ImplOpenGL3_Init();

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

	string directory = "../resources/";

	Camera* camLookAt = new Camera(70.0f, 800.0f / 600.0f, 0.01f, 500.0f);

	string AmbiantLoc; 
	string DiffuseLoc;
	string SpecLoc;
	string NormalLoc;
	Texture* texture = new Texture();
	Mesh Tri1(&SquareVerticies[0], SquareVerticies.size(), &SquareIndecies[0], 6);
	vector <Lightbase*> lights;
	lights.push_back(new Lightbase());
	lights.push_back(new Lightbase());
	lights[0]->GetTransform().SetPos(vec3(1.0, 0.5, 1.0));// Setting first light position
	lights[1]->GetTransform().SetPos(vec3(-1.0, -0.5, -1.0)); // Setting second light position

	vector <uint> Indecies;

	vector<Vertex> LoadedVerts = OBJLoader::LoadOBJ("../resources", "blocks_01.obj",
		AmbiantLoc, DiffuseLoc, SpecLoc, NormalLoc, Indecies);

	Shader* basicShader = new Shader(directory + "Basic", camera, AmbiantLoc, DiffuseLoc, SpecLoc, NormalLoc);

	Mesh Cube(&LoadedVerts[0], LoadedVerts.size(), &Indecies[0], Indecies.size());

	Mesh Square1(&SquareVerticies[0], SquareVerticies.size(), &SquareIndecies[0], 6);
	Square1.trans.SetScale(Square1.trans.GetScale() * 50.0f);
	Square1.trans.SetRot(vec3(radians(90.0f), 0.0f, 0.0f));
	Square1.trans.SetPos(vec3(0, -1.0, 0));

	Cube.trans.SetScale(Cube.trans.GetScale() * 0.06f);
	Cube.trans.SetPos(vec3(0, -1, 3));

	float br=0.1f, bg=0.1f, bb=0.1f;
	
	glClearColor(br, bg, bb, 1.0f);
	glViewport(0, 0, 800, 600);
		
	Tri1.trans.SetPos(vec3(1.0, 0, 0));
	Tri1.trans.SetRot(vec3(0, 4.73, 0));

	Input* input = new Input();

	float lightScaler = 1;

	while (true)
	{
		glClearColor(br, bg, bb, 1.0f);
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

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(window);
		ImGui::NewFrame();
		ImGui::SetWindowSize(ImVec2(400, 200));
		ImGui::Begin("MyWindow");
		//Code Go here for ImGui (Anything between Begn and End will display in GUI)
		if (ImGui::Button("Move Cube")) {
			Cube.trans.SetPos(camera.M_Transform.GetPos());
		}
		ImGui::DragFloat("Red BG", &br, 0.01f, 0, 1);
		ImGui::DragFloat("Green BG", &bg, 0.01f, 0, 1);
		ImGui::DragFloat("Blue BG", &bb, 0.01f, 0, 1);
		
		ImGui::End();

		camera.MouseMoveTarget();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		

		static float i;
		i += 0.01;
		for (int i = 0; i < lights.size(); i++)
		{
			lights[i]->Draw(&camera);
		}
		
		basicShader->Bind();
		Tri1.Draw();
		Square1.Draw();
		basicShader->Update(Cube.trans, lights);
		Cube.Draw();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		SDL_GL_SwapWindow(window);
		SDL_Delay(16);

	}

	SDL_GL_DeleteContext(GLContext); // All Clean up but in theory should never get here due to infinate loop
	SDL_DestroyWindow(window);
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
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
