#ifndef _MODULE_
#define _MODULE_

#include "Globals.h"

/*
Base class from where all the game modules will be done
*/

class Module
{
	Module();

	virtual ~Module();

	virtual update_status PreUpdate()
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status Update()
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status PostUpdate()
	{
		return UPDATE_CONTINUE;
	}

	virtual bool CleanUp()
	{
		return true;
	}
};

#endif

