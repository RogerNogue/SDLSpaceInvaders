#include "ModuleGameLoop.h"

#include "ModuleMainMenu.h"
#include "ModuleGame.h"
#include "ModuleEndGameMenu.h"

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
	if (!game->Init())
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
			mainMenu->LeaveMenu();
			game->EnterMenu();
		}
		break;
	case INGAME:
		retValue =  game->Update();
		if (currentState == END_MENU)
		{
			game->LeaveMenu();
			endMenu->EnterMenu();
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
	endMenu->CleanUp();
	SAFE_RELEASE(mainMenu);
	SAFE_RELEASE(game);
	SAFE_RELEASE(endMenu);
	return true;
}