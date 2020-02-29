#ifndef _MODULE_
#define _MODULE_

#include "Globals.h"
#include "Module.h"

/*
Base class from where all the game modules will be done
*/

class Module
{
public:
	Module() 
	{

	}

	virtual ~Module()
	{

	}

	virtual bool Init()
	{
		return true;
	}

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

