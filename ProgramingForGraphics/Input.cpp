#include "Input.h"

void Input::Update(void) // Full comments through Game Engine Design input.ccp
{
	while (SDL_PollEvent(&m_Event) != NULL)
	{
		if (m_Event.type == SDL_KEYDOWN)
		{
			// Cache the code of key we pressed for easier debugging
			SDL_Keycode keyPressed = m_Event.key.keysym.sym;

			//update keys
			switch (keyPressed)
			{
			case SDLK_ESCAPE:
				m_KeysPressed[KEY_ESCAPE] = true;
				break;

			case SDLK_w:
				m_KeysPressed[KEY_W] = true;
				break;

			case SDLK_s:
				m_KeysPressed[KEY_S] = true;
				break;

			case SDLK_a:
				m_KeysPressed[KEY_A] = true;
				break;

			case SDLK_d:
				m_KeysPressed[KEY_D] = true;
				break;

			}


		}

		else if (m_Event.type == SDL_KEYUP)
		{
			SDL_Keycode keyPressed = m_Event.key.keysym.sym;

			//update keys
			switch (keyPressed)
			{
			case SDLK_w:
				m_KeysPressed[KEY_W] = false;
				break;

			case SDLK_a:
				m_KeysPressed[KEY_A] = false;
				break;

			case SDLK_s:
				m_KeysPressed[KEY_S] = false;
				break;

			case SDLK_d:
				m_KeysPressed[KEY_D] = false;
				break;


			}
		}
	}

	

}

Input::Input()
{

}

Input::~Input()
{

}

bool Input::KeyIsPressed(KEYS_PRESSED_LIST key)
{
	return m_KeysPressed[key];
}