#include "ModuleGameLoop.h"

#include "ModuleMainMenu.h"
#include "ModuleGame.h"
#include "ModuleEndGameMenu.h"
#include "ModuleCollisions.h"

#include "Globals.h"


ModuleGameLoop::ModuleGameLoop() : Module()
{

}
ModuleGameLoop::~ModuleGameLoop()
{
}

bool ModuleGameLoop::Init()
{
	mainMenu = new ModuleMainMenu();
	if (!mainMenu->Init())
	{
		return false;
	}

	game = new ModuleGame();

	collisions = new ModuleCollisions();
	if (!collisions->Init())
	{
		return false;
	}

	endMenu = new ModuleEndGameMenu();
	if (!endMenu->Init())
	{
		return false;
	}
}

update_status ModuleGameLoop::Update()
{
	gameState initialState = currentState;
	update_status retValue = UPDATE_STOP;
	switch (currentState)
	{
	case MAIN_MENU:
		retValue = mainMenu->Update();
		//check state switching
		if (currentState == INGAME)
		{
			game->NewGameInit();
			mainMenu->LeaveMenu();
			game->EnterMenu();
			score = 0;
		}
		break;
	case INGAME:
		retValue = collisions->Update();
		retValue = game->Update();
		if (currentState == END_MENU)
		{
			if (score > topScore)
			{
				topScore = score;
			}
			game->LeaveMenu();
			endMenu->EnterMenu();
			game->CleanUp();
			collisions->CleanUp();
		}
		break;
	case END_MENU:
		retValue = endMenu->Update();
		if (currentState == MAIN_MENU)
		{
			endMenu->LeaveMenu();
			mainMenu->EnterMenu();
		}
		break;
	}
	return retValue;
}

bool ModuleGameLoop::CleanUp()
{
	mainMenu->CleanUp();
	game->CleanUp();
	collisions->CleanUp();
	endMenu->CleanUp();
	SAFE_RELEASE(mainMenu);
	SAFE_RELEASE(game);
	SAFE_RELEASE(collisions);
	SAFE_RELEASE(endMenu);
	return true;
}