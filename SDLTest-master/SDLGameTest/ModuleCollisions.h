#ifndef _MODULECOLLISIONS_
#define	_MODULECOLLISIONS_

#include "Module.h"
#include "Globals.h"
#include <list>

//fwd declarations
class Projectile;

class ModuleCollisions final:
	public Module
{
public:
	ModuleCollisions();

	~ModuleCollisions();

	bool Init() override;

	update_status Update() override;

	bool CleanUp() override;

public:
	//since elements will be deleted frequently, list is better than vector
	std::list<Projectile*> listProjectiles;
};

#endif // !_MODULECOLLISIONS_