#pragma once

#include <SDL.h>
#include <stdio.h>
#include <string>
#include "Camera.h"
#include "Input.h"
#include "mesh.h"
#include "Transform.h"

using namespace std;

struct SDL_Window;

class window
{
public:
	SDL_Window* m_window;
	void createWindow();
};