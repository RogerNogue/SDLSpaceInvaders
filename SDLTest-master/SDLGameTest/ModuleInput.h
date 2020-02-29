#ifndef _MODULEINPUT_
#define _MODULEINPUT_

#include "Module.h"
#include "Globals.h"

enum KeyState
{
	KEY_IDLE,
	KEY_DOWN
};

struct Command
{
	KeyState Up;
	KeyState Left;
	KeyState Right;
};

class ModuleInput final:
	public Module
{
public:
	ModuleInput();
	~ModuleInput();

	bool Init() override;

	update_status PreUpdate() override;

	bool CleanUp() override;


public://variables
	Command keyboardState;
};

#endif

