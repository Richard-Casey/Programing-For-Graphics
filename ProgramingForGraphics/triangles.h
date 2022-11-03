#define GLEW_STATIC

#include <glew.h> // needs to be first as openGL library relys on it
#include <SDL_opengl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SDL.h>
#include <iostream>
#include "window.h"
#include "mesh.h"
#include "Transform.h"

using namespace std;

class triangles
{
public:
	triangles();
	void CheckShaderError();
	~triangles();
};

