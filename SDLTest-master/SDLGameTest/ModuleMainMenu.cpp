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
}

ModuleMainMenu::~ModuleMainMenu()
{

}

bool ModuleMainMenu::Init()
{
	topScoreText = new MenuText(117, 0, 50, 100, "Top Score: ");
	std::string scoreValue = std::to_string(App->gameLoop->topScore);
	topScoreValue = new MenuText(217, 0, 50, 30, scoreValue.c_str());
	playButton = new MenuText(0, 100, 50, 512, "Press Space + right arrow to continue");

	App->renderer->AddTextToRender(playButton);
	App->renderer->AddTextToRender(topScoreText);
	App->renderer->AddTextToRender(topScoreValue);
	
	return true;
}

void ModuleMainMenu::EnterMenu()
{
	topScoreValue->SetText(std::to_string(App->gameLoop->topScore).c_str(),
		App->renderer->renderer);

	playButton->Enable();
	topScoreText->Enable();
	topScoreValue->Enable();
}

void ModuleMainMenu::LeaveMenu()
{
	playButton->Disable();
	topScoreText->Disable();
	topScoreValue->Disable();
}

update_status ModuleMainMenu::Update()
{
	if (App->input->keyboardState.Fire == KEY_DOWN &&
		App->input->keyboardState.Right == KEY_DOWN)
	{
		//we play, so we disable menu stuff
		App->gameLoop->currentState = INGAME;
	}
	return UPDATE_CONTINUE;
}


bool ModuleMainMenu::CleanUp()
{
	//clean texts
	App->renderer->RemoveTextToRender(topScoreText);
	topScoreText->~MenuText();
	SAFE_RELEASE(topScoreText);

	App->renderer->RemoveTextToRender(topScoreValue);
	topScoreValue->~MenuText();
	SAFE_RELEASE(topScoreValue);
	
	App->renderer->RemoveTextToRender(playButton);
	playButton->~MenuText();
	SAFE_RELEASE(playButton);

	return true;
}