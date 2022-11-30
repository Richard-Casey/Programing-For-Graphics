#pragma once
#include <SDL.h>
#include "Camera.h"

enum KEYS_PRESSED_LIST
{
	KEY_ESCAPE, KEY_W, KEY_S, KEY_A, KEY_D, SIZE_OF_KEYS_PRESSED_ENUM
};

class Input
{
public:
	SDL_Event m_Event;
	void Update(void);
	Input();
	~Input();
	bool m_KeysPressed[SIZE_OF_KEYS_PRESSED_ENUM] = {};
	bool KeyIsPressed(KEYS_PRESSED_LIST key);
	SDL_Event e;	
};

