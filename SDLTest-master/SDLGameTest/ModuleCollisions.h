#ifndef _MODULECOLLISIONS_
#define	_MODULECOLLISIONS_

#include "Module.h"
#include "Globals.h"

class ModuleCollisions final:
	public Module
{
public:
	ModuleCollisions();

	~ModuleCollisions();

	bool Init() override;

	update_status Update() override;

	bool CleanUp() override;
};

#endif // !_MODULECOLLISIONS_