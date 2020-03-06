#ifndef _MODULEENDGAMEMENU_
#define _MODULEENDGAMEMENU_

#include "Module.h"
class ModuleEndGameMenu final:
	public Module
{
public:
	ModuleEndGameMenu();

	~ModuleEndGameMenu();

	bool Init()override;

	update_status Update() override;

	bool CleanUp()override;

	void EnterMenu();

	void LeaveMenu();


};

#endif