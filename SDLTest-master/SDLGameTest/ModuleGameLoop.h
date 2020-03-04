#ifndef _MODULEGAMELOOP_
#define _MODULEGAMELOOP_
#include "Module.h"

enum gameState
{
	MAIN_MENU,
	INGAME,
	END_MENU
};

class ModuleMainMenu;
class ModuleGame;
class ModuleEndGameMenu;

class ModuleGameLoop final:
	public Module
{
public:
	ModuleGameLoop();

	~ModuleGameLoop();

	bool Init() override;

	update_status Update() override;

	inline gameState GetState() const { return currentState; }

	bool CleanUp() override;

public://variables

	ModuleMainMenu* mainMenu = nullptr;
	ModuleGame* game = nullptr;
	ModuleEndGameMenu* endMenu = nullptr;

private://variables
	gameState currentState = INGAME;

};

#endif
