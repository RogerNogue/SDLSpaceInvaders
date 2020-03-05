#ifndef _MODULEMAINMENU_
#define _MODULEMAINMENU_

#include "Module.h"
#include <string>

class MenuText;

class ModuleMainMenu final:
	public Module
{
public:
	ModuleMainMenu();

	~ModuleMainMenu();

	bool Init()override;

	update_status Update() override;

	bool CleanUp()override;

public://variables
	MenuText* playButton;
};

#endif