#include "ModuleInput.h"

//sdl includes
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <SDL.h>
#include <SDL_image.h>
#elif defined(__APPLE__)
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#endif

ModuleInput::ModuleInput()
	:Module()
{
	keyboardState.Up = KEY_IDLE;
	keyboardState.Left = KEY_IDLE;
	keyboardState.Right = KEY_IDLE;
}

ModuleInput::~ModuleInput()
{

}
/*
	Method that sets the key parameter a certain value from a certain keyboard
*/
inline void SetKeyValue(int key, KeyState value, Command* keyboardState)
{
	switch (key)
	{
	case SDLK_UP:
		keyboardState->Up = value;
		break;
	case SDLK_w:
		keyboardState->Up = value;
		break;

	case SDLK_LEFT:
		keyboardState->Left = value;
		break;
	case SDLK_a:
		keyboardState->Left = value;
		break;

	case SDLK_RIGHT:
		keyboardState->Right = value;
		break;
	case SDLK_d:
		keyboardState->Right = value;
		break;
	}
}

update_status ModuleInput::PreUpdate()
{
	SDL_Event e;
	SDL_PollEvent(&e);
	switch (e.type) {
	case SDL_QUIT:
		return UPDATE_STOP;
		break;
	case SDL_MOUSEBUTTONDOWN:
		break;
	case SDL_KEYUP:
		SetKeyValue(e.key.keysym.sym, KEY_IDLE, &keyboardState);
		break;
	case SDL_KEYDOWN:
		SetKeyValue(e.key.keysym.sym, KEY_DOWN, &keyboardState);
		break;
	case SDL_USEREVENT:
		break;
	default:
		break;
	}
	return UPDATE_CONTINUE;
}

bool ModuleInput::Init()
{
	return true;
}

bool ModuleInput::CleanUp()
{
	return true;
}
