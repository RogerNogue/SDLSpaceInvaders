#ifndef _MODULEINPUT_
#define _MODULEINPUT_

#include "Module.h"
#include "Globals.h"

enum KeyState
{
	KEY_IDLE,
	KEY_DOWN
};

struct keyboard
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

	update_status Update() override;

	bool CleanUp() override;


public://variables
	keyboard keyboardState;
};

#endif

