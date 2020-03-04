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
	switch (currentState)
	{
	case MAIN_MENU:

		break;
	case INGAME:
		return game->Update();
		break;
	case END_MENU:

		break;
	}

	//game in no state, should probably stop
	return UPDATE_STOP;
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