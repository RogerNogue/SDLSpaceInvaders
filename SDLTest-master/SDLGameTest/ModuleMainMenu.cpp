#include "ModuleMainMenu.h"
#include "ModuleRender.h"

//sdl includes
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <SDL.h>
#include <SDL_image.h>
#elif defined(__APPLE__)
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#endif

//////////Module Main Menu//////////

ModuleMainMenu::ModuleMainMenu()
{
	playButton = new MenuText(1, 1, 1, 1, "Play");
}

ModuleMainMenu::~ModuleMainMenu()
{

}

bool ModuleMainMenu::Init()
{
	return true;
}

update_status ModuleMainMenu::Update()
{
	return UPDATE_CONTINUE;
}


bool ModuleMainMenu::CleanUp()
{
	return true;
}