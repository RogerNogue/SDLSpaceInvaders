#ifndef _MODULEPLAYER_
#define _MODULEPLAYER_


#include "Module.h"
class ModulePlayer :
	public Module
{
public:
	ModulePlayer();

	~ModulePlayer();
	
	update_status Update() override;
};

#endif // !_MODULEPLAYER_