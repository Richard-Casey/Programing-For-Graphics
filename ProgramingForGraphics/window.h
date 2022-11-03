#pragma once
#include <SDL.h>
#include <stdio.h>
#include <string>
#include "Camera.h"
#include "Input.h"
#include "mesh.h"
#include "Transform.h"
#include "triangles.h"

class window
{
public:
	void createWindow();
	SDL_Window* m_window();
};