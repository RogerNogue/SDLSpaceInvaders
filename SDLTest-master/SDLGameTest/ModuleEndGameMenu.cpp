#include "ModuleEndGameMenu.h"

#include "ModuleInput.h"
#include "ModuleGameLoop.h"
#include "Application.h"
#include "ModuleRender.h"
#include <string>

ModuleEndGameMenu::ModuleEndGameMenu()
{

}

ModuleEndGameMenu::~ModuleEndGameMenu()
{

}

bool ModuleEndGameMenu::Init()
{
	//score texts
	scoreText = new MenuText(200, 50, 50, 100, "Score: ");
	std::string scoreValueStr = std::to_string(App->gameLoop->score);
	scoreValue = new MenuText(300, 50, 50, 30, scoreValueStr.c_str());
	App->renderer->AddTextToRender(scoreText);
	App->renderer->AddTextToRender(scoreValue);
	scoreText->Disable();
	scoreValue->Disable();

	//top score texts
	topScoreText = new MenuText(200, 150, 50, 100, "Top Score: ");
	scoreValueStr = std::to_string(App->gameLoop->topScore);
	topScoreValue = new MenuText(300, 150, 50, 30, scoreValueStr.c_str());
	App->renderer->AddTextToRender(topScoreText);
	App->renderer->AddTextToRender(topScoreValue);
	topScoreText->Disable();
	topScoreValue->Disable();

	//other texts
	gameEndedText = new MenuText(200, 0, 50, 150, "Game Ended:");
	continueText = new MenuText(0, 300, 50, 512, "Press Space, left and right to continue");
	App->renderer->AddTextToRender(gameEndedText);
	App->renderer->AddTextToRender(continueText);
	gameEndedText->Disable();
	continueText->Disable();

	return true;
}

update_status ModuleEndGameMenu::Update()
{
	if (App->input->keyboardState.Fire == KEY_DOWN &&
		App->input->keyboardState.Left == KEY_DOWN &&
		App->input->keyboardState.Right == KEY_DOWN)
	{
		//we play, so we disable menu stuff
		App->gameLoop->currentState = MAIN_MENU;
	}
	return UPDATE_CONTINUE;
}


bool ModuleEndGameMenu::CleanUp()
{
	return true;
}

void ModuleEndGameMenu::EnterMenu()
{
	//update score values
	topScoreValue->SetText(std::to_string(App->gameLoop->topScore).c_str(),
		App->renderer->renderer);
	scoreValue->SetText(std::to_string(App->gameLoop->score).c_str(),
		App->renderer->renderer);

	gameEndedText->Enable();
	scoreText->Enable();
	scoreValue->Enable();
	topScoreText->Enable();
	topScoreValue->Enable();
	continueText->Enable();
}

void ModuleEndGameMenu::LeaveMenu()
{
	gameEndedText->Disable();
	scoreText->Disable();
	scoreValue->Disable();
	topScoreText->Disable();
	topScoreValue->Disable();
	continueText->Disable();
}