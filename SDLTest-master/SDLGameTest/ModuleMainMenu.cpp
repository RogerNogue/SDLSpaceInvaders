#include "ModuleMainMenu.h"

#include "Application.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleGameLoop.h"

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
	playButton = new MenuText(1, 1, 50, 50, "Play");
}

ModuleMainMenu::~ModuleMainMenu()
{

}

bool ModuleMainMenu::Init()
{
	App->renderer->AddTextToRender(playButton);
	
	return true;
}

void ModuleMainMenu::EnterMenu()
{
	playButton->Enable();
}

void ModuleMainMenu::LeaveMenu()
{
	playButton->Disable();
}

update_status ModuleMainMenu::Update()
{
	if (App->input->keyboardState.Fire == KEY_DOWN)
	{
		//we play, so we disable menu stuff
		App->gameLoop->currentState = INGAME;
	}
	return UPDATE_CONTINUE;
}


bool ModuleMainMenu::CleanUp()
{
	//clean texts
	App->renderer->RemoveTextToRender(playButton);
	playButton->~MenuText();
	SAFE_RELEASE(playButton);

	return true;
}